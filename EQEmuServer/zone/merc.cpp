#include "merc.h"
#include "masterentity.h"
#include "NpcAI.h"
#include "../common/packet_dump.h"
#include "../common/eq_packet_structs.h"
#include "../common/eq_constants.h"
#include "../common/skills.h"
#include "spdat.h"
#include "zone.h"
#include "StringIDs.h"
#include "../common/MiscFunctions.h"
#include "../common/rulesys.h"
#include "QuestParserCollection.h"
#include "watermap.h"

extern volatile bool ZoneLoaded;

Merc::Merc(const NPCType* d, float x, float y, float z, float heading)
	: NPC(d, 0, x, y, z, heading, 0, false), endupkeep_timer(1000), rest_timer(1)
{
	_baseAC = d->AC;
	_baseSTR = d->STR;
	_baseSTA = d->STA;
	_baseDEX = d->DEX;
	_baseAGI = d->AGI;
	_baseINT = d->INT;
	_baseWIS = d->WIS;
	_baseCHA = d->CHA;
	_baseATK = d->ATK;
	_baseRace = d->race;
	_baseGender = d->gender;
	_baseMR = d->MR;
	_baseCR = d->CR;
	_baseDR = d->DR;
	_baseFR = d->FR;
	_basePR = d->PR;
	_baseCorrup = d->Corrup;

	_medding = false;
	_suspended = false;
	p_depop = false;

	ourNPCData = d;

	LoadMercSpells();
	SetStance(MercStancePassive);
	rest_timer.Disable();

	int r;
	for(r = 0; r <= HIGHEST_SKILL; r++) {
		skills[r] = database.GetSkillCap(GetClass(),(SkillType)r,GetLevel());
	}

	CalcBonuses();

	SetHP(GetMaxHP());
	SetMana(GetMaxMana());
	SetEndurance(GetMaxEndurance());

	AI_Init();
	AI_Start();
}

Merc::~Merc() {
	safe_delete(ourNPCData); //Since mercs are dynamically alloc'd we should probably safe_delete the data they were made from. I'm not entirely sure this is safe to delete a const.
	entity_list.RemoveMerc(this->GetID());
	UninitializeBuffSlots();
}

void Merc::CalcBonuses()
{
	//_ZP(Merc_CalcBonuses);
	GenerateBaseStats();
	memset(&itembonuses, 0, sizeof(StatBonuses));
	memset(&aabonuses, 0, sizeof(StatBonuses));
	CalcItemBonuses(&itembonuses);

	CalcSpellBonuses(&spellbonuses);

	//_log(AA__BONUSES, "Calculating AA Bonuses for %s.", this->GetCleanName());
	//CalcAABonuses(&aabonuses);	//we're not quite ready for this
	//_log(AA__BONUSES, "Finished calculating AA Bonuses for %s.", this->GetCleanName());

	CalcAC();
	CalcATK();
	//CalcHaste();

	CalcSTR();
	CalcSTA();
	CalcDEX();
	CalcAGI();
	CalcINT();
	CalcWIS();
	CalcCHA();

	CalcMR();
	CalcFR();
	CalcDR();
	CalcPR();
	CalcCR();
	CalcCorrup();

	CalcMaxHP();
	CalcMaxMana();
	CalcMaxEndurance();

	rooted = FindType(SE_Root);
}

void Merc::GenerateBaseStats() {

	// base stats
	uint16 Strength = _baseSTR;
	uint16 Stamina = _baseSTA;
	uint16 Dexterity = _baseDEX;
	uint16 Agility = _baseAGI;
	uint16 Wisdom = _baseWIS;
	uint16 Intelligence = _baseINT;
	uint16 Charisma = _baseCHA;
	uint16 Attack = _baseATK;
	uint16 MagicResist = _baseMR;
	uint16 FireResist = _baseFR;
	uint16 DiseaseResist = _baseDR;
	uint16 PoisonResist = _basePR;
	uint16 ColdResist = _baseCR;
	uint16 CorruptionResist = _baseCorrup;

	switch(this->GetClass()) {
		case 1: // Warrior
			Strength += 10;
			Stamina += 20;
			Agility += 10;
			Dexterity += 10;
			Attack += 12;
			break;
		case 2: // Cleric
			Strength += 5;
			Stamina += 5;
			Agility += 10;
			Wisdom += 30;
			Attack += 8;
			break;
		case 4: // Ranger
			Strength += 15;
			Stamina += 10;
			Agility += 10;
			Wisdom += 15;
			Attack += 17;
			break;
		case 9: // Rogue
			Strength += 10;
			Stamina += 20;
			Agility += 10;
			Dexterity += 10;
			Attack += 12;
			break;
		case 12: // Wizard
			Stamina += 20;
			Intelligence += 30;
			Attack += 5;
			break;
	}

	float MercSize = GetSize();

	switch(this->GetRace()) {
			case 1: // Humans have no race bonus
				break;
			case 2: // Barbarian
				MercSize = 7.0;
				break;
			case 3: // Erudite
				break;
			case 4: // Wood Elf
				MercSize = 5.0;
				break;
			case 5: // High Elf
				break;
			case 6: // Dark Elf
				MercSize = 5.0;
				break;
			case 7: // Half Elf
				MercSize = 5.5;
				break;
			case 8: // Dwarf
				MercSize = 4.0;
				break;
			case 9: // Troll
				MercSize = 8.0;
				break;
			case 10: // Ogre
				MercSize = 9.0;
				break;
			case 11: // Halfling
				MercSize = 3.5;
				break;
			case 12: // Gnome
				MercSize = 3.0;
				break;
			case 128: // Iksar
				break;
			case 130: // Vah Shir
				MercSize = 7.0;
				break;
			case 330: // Froglok
				MercSize = 5.0;
				break;
			case 522: // Drakkin
				MercSize = 5.0;
				break;
	}

	this->_baseSTR = Strength;
	this->_baseSTA = Stamina;
	this->_baseDEX = Dexterity;
	this->_baseAGI = Agility;
	this->_baseWIS = Wisdom;
	this->_baseINT = Intelligence;
	this->_baseCHA = Charisma;
	this->_baseATK = Attack;
	this->_baseMR = MagicResist;
	this->_baseFR = FireResist;
	this->_baseDR = DiseaseResist;
	this->_basePR = PoisonResist;
	this->_baseCR = ColdResist;
	this->_baseCorrup = CorruptionResist;
	this->size = MercSize;
}

void Merc::GenerateAppearance() {
	// Randomize facial appearance
	int iFace = 0;
	if(this->GetRace() == 2) { // Barbarian w/Tatoo
		iFace = MakeRandomInt(0, 79);
	}
	else {
		iFace = MakeRandomInt(0, 7);
	}

	int iHair = 0;
	int iBeard = 0;
	int iBeardColor = 1;
	if(this->GetRace() == 522) {
		iHair = MakeRandomInt(0, 8);
		iBeard = MakeRandomInt(0, 11);
		iBeardColor = MakeRandomInt(0, 3);
	}
	else if(this->GetGender()) {
		iHair = MakeRandomInt(0, 2);
		if(this->GetRace() == 8) { // Dwarven Females can have a beard
			if(MakeRandomInt(1, 100) < 50) {
				iFace += 10;
			}
		}
	}
	else {
		iHair = MakeRandomInt(0, 3);
		iBeard = MakeRandomInt(0, 5);
		iBeardColor = MakeRandomInt(0, 19);
	}

	int iHairColor = 0;
	if(this->GetRace() == 522) {
		iHairColor = MakeRandomInt(0, 3);
	}
	else {
		iHairColor = MakeRandomInt(0, 19);
	}

	uint8 iEyeColor1 = (uint8)MakeRandomInt(0, 9);
	uint8 iEyeColor2 = 0;
	if(this->GetRace() == 522) {
		iEyeColor1 = iEyeColor2 = (uint8)MakeRandomInt(0, 11);
	}
	else if(MakeRandomInt(1, 100) > 96) {
		iEyeColor2 = MakeRandomInt(0, 9);
	}
	else {
		iEyeColor2 = iEyeColor1;
	}

	int iHeritage = 0;
	int iTattoo = 0;
	int iDetails = 0;
	if(this->GetRace() == 522) {
		iHeritage = MakeRandomInt(0, 6);
		iTattoo = MakeRandomInt(0, 7);
		iDetails = MakeRandomInt(0, 7);
	}

	this->luclinface = iFace;
	this->hairstyle = iHair;
	this->beard = iBeard;
	this->beardcolor = iBeardColor;
	this->haircolor = iHairColor;
	this->eyecolor1 = iEyeColor1;
	this->eyecolor2 = iEyeColor2;
	this->drakkin_heritage = iHeritage;
	this->drakkin_tattoo = iTattoo;
	this->drakkin_details = iDetails;
}

int Merc::CalcRecommendedLevelBonus(uint8 level, uint8 reclevel, int basestat)
{
	if( (reclevel > 0) && (level < reclevel) )
	{
		int32 statmod = (level * 10000 / reclevel) * basestat;

		if( statmod < 0 )
		{
			statmod -= 5000;
			return (statmod/10000);
		}
		else
		{
			statmod += 5000;
			return (statmod/10000);
		}
	}

	return 0;
}

void Merc::CalcItemBonuses(StatBonuses* newbon) {
	//memset assumed to be done by caller.


	unsigned int i;
	//should not include 21 (SLOT_AMMO)
	for (i=0; i<SLOT_AMMO; i++) {
		const ItemInst* inst = m_inv[i];
		if(inst == 0)
			continue;
		AddItemBonuses(inst, newbon);
	}

	//Power Source Slot
	if (GetClientVersion() >= EQClientSoF)
	{
		const ItemInst* inst = m_inv[9999];
		if(inst)
			AddItemBonuses(inst, newbon);
	}

	//tribute items
	for (i = 0; i < MAX_PLAYER_TRIBUTES; i++) {
		const ItemInst* inst = m_inv[TRIBUTE_SLOT_START + i];
		if(inst == 0)
			continue;
		AddItemBonuses(inst, newbon, false, true);
	}
	// Caps
	if(newbon->HPRegen > CalcHPRegenCap())
		newbon->HPRegen = CalcHPRegenCap();

	if(newbon->ManaRegen > CalcManaRegenCap())
		newbon->ManaRegen = CalcManaRegenCap();

	if(newbon->EnduranceRegen > CalcEnduranceRegenCap())
		newbon->EnduranceRegen = CalcEnduranceRegenCap();

	SetAttackTimer();
}

void Merc::AddItemBonuses(const ItemInst *inst, StatBonuses* newbon, bool isAug, bool isTribute) {
	if(!inst || !inst->IsType(ItemClassCommon))
	{
		return;
	}

	if(inst->GetAugmentType()==0 && isAug == true)
	{
		return;
	}

	const Item_Struct *item = inst->GetItem();

	if(!isTribute && !inst->IsEquipable(GetBaseRace(),GetClass()))
	{
		if(item->ItemType != ItemTypeFood && item->ItemType != ItemTypeDrink)
			return;
	}

	if(GetLevel() < item->ReqLevel)
	{
		return;
	}

	if(GetLevel() >= item->RecLevel)
	{
		newbon->AC += item->AC;
		newbon->HP += item->HP;
		newbon->Mana += item->Mana;
		newbon->Endurance += item->Endur;
		newbon->STR += (item->AStr + item->HeroicStr);
		newbon->STA += (item->ASta + item->HeroicSta);
		newbon->DEX += (item->ADex + item->HeroicDex);
		newbon->AGI += (item->AAgi + item->HeroicAgi);
		newbon->INT += (item->AInt + item->HeroicInt);
		newbon->WIS += (item->AWis + item->HeroicWis);
		newbon->CHA += (item->ACha + item->HeroicCha);

		newbon->MR += (item->MR + item->HeroicMR);
		newbon->FR += (item->FR + item->HeroicFR);
		newbon->CR += (item->CR + item->HeroicCR);
		newbon->PR += (item->PR + item->HeroicPR);
		newbon->DR += (item->DR + item->HeroicDR);
		newbon->Corrup += (item->SVCorruption + item->HeroicSVCorrup);

		newbon->STRCapMod += item->HeroicStr;
		newbon->STACapMod += item->HeroicSta;
		newbon->DEXCapMod += item->HeroicDex;
		newbon->AGICapMod += item->HeroicAgi;
		newbon->INTCapMod += item->HeroicInt;
		newbon->WISCapMod += item->HeroicWis;
		newbon->CHACapMod += item->HeroicCha;
		newbon->MRCapMod += item->HeroicMR;
		newbon->CRCapMod += item->HeroicFR;
		newbon->FRCapMod += item->HeroicCR;
		newbon->PRCapMod += item->HeroicPR;
		newbon->DRCapMod += item->HeroicDR;
		newbon->CorrupCapMod += item->HeroicSVCorrup;

		newbon->HeroicSTR += item->HeroicStr;
		newbon->HeroicSTA += item->HeroicSta;
		newbon->HeroicDEX += item->HeroicDex;
		newbon->HeroicAGI += item->HeroicAgi;
		newbon->HeroicINT += item->HeroicInt;
		newbon->HeroicWIS += item->HeroicWis;
		newbon->HeroicCHA += item->HeroicCha;
		newbon->HeroicMR += item->HeroicMR;
		newbon->HeroicFR += item->HeroicFR;
		newbon->HeroicCR += item->HeroicCR;
		newbon->HeroicPR += item->HeroicPR;
		newbon->HeroicDR += item->HeroicDR;
		newbon->HeroicCorrup += item->HeroicSVCorrup;

	}
	else
	{
		int lvl = GetLevel();
		int reclvl = item->RecLevel;

		newbon->AC += CalcRecommendedLevelBonus( lvl, reclvl, item->AC );
		newbon->HP += CalcRecommendedLevelBonus( lvl, reclvl, item->HP );
		newbon->Mana += CalcRecommendedLevelBonus( lvl, reclvl, item->Mana );
		newbon->Endurance += CalcRecommendedLevelBonus( lvl, reclvl, item->Endur );
		newbon->STR += CalcRecommendedLevelBonus( lvl, reclvl, (item->AStr + item->HeroicStr) );
		newbon->STA += CalcRecommendedLevelBonus( lvl, reclvl, (item->ASta + item->HeroicSta) );
		newbon->DEX += CalcRecommendedLevelBonus( lvl, reclvl, (item->ADex + item->HeroicDex) );
		newbon->AGI += CalcRecommendedLevelBonus( lvl, reclvl, (item->AAgi + item->HeroicAgi) );
		newbon->INT += CalcRecommendedLevelBonus( lvl, reclvl, (item->AInt + item->HeroicInt) );
		newbon->WIS += CalcRecommendedLevelBonus( lvl, reclvl, (item->AWis + item->HeroicWis) );
		newbon->CHA += CalcRecommendedLevelBonus( lvl, reclvl, (item->ACha + item->HeroicCha) );

		newbon->MR += CalcRecommendedLevelBonus( lvl, reclvl, (item->MR + item->HeroicMR) );
		newbon->FR += CalcRecommendedLevelBonus( lvl, reclvl, (item->FR + item->HeroicFR) );
		newbon->CR += CalcRecommendedLevelBonus( lvl, reclvl, (item->CR + item->HeroicCR) );
		newbon->PR += CalcRecommendedLevelBonus( lvl, reclvl, (item->PR + item->HeroicPR) );
		newbon->DR += CalcRecommendedLevelBonus( lvl, reclvl, (item->DR + item->HeroicDR) );
		newbon->Corrup += CalcRecommendedLevelBonus( lvl, reclvl, (item->SVCorruption + item->HeroicSVCorrup) );

		newbon->STRCapMod += CalcRecommendedLevelBonus( lvl, reclvl, item->HeroicStr );
		newbon->STACapMod += CalcRecommendedLevelBonus( lvl, reclvl, item->HeroicSta );
		newbon->DEXCapMod += CalcRecommendedLevelBonus( lvl, reclvl, item->HeroicDex );
		newbon->AGICapMod += CalcRecommendedLevelBonus( lvl, reclvl, item->HeroicAgi );
		newbon->INTCapMod += CalcRecommendedLevelBonus( lvl, reclvl, item->HeroicInt );
		newbon->WISCapMod += CalcRecommendedLevelBonus( lvl, reclvl, item->HeroicWis );
		newbon->CHACapMod += CalcRecommendedLevelBonus( lvl, reclvl, item->HeroicCha );
		newbon->MRCapMod += CalcRecommendedLevelBonus( lvl, reclvl, item->HeroicMR );
		newbon->CRCapMod += CalcRecommendedLevelBonus( lvl, reclvl, item->HeroicFR );
		newbon->FRCapMod += CalcRecommendedLevelBonus( lvl, reclvl, item->HeroicCR );
		newbon->PRCapMod += CalcRecommendedLevelBonus( lvl, reclvl, item->HeroicPR );
		newbon->DRCapMod += CalcRecommendedLevelBonus( lvl, reclvl, item->HeroicDR );
		newbon->CorrupCapMod += CalcRecommendedLevelBonus( lvl, reclvl, item->HeroicSVCorrup );

		newbon->HeroicSTR += CalcRecommendedLevelBonus( lvl, reclvl, item->HeroicStr );
		newbon->HeroicSTA += CalcRecommendedLevelBonus( lvl, reclvl, item->HeroicSta );
		newbon->HeroicDEX += CalcRecommendedLevelBonus( lvl, reclvl, item->HeroicDex );
		newbon->HeroicAGI += CalcRecommendedLevelBonus( lvl, reclvl, item->HeroicAgi );
		newbon->HeroicINT += CalcRecommendedLevelBonus( lvl, reclvl, item->HeroicInt );
		newbon->HeroicWIS += CalcRecommendedLevelBonus( lvl, reclvl, item->HeroicWis );
		newbon->HeroicCHA += CalcRecommendedLevelBonus( lvl, reclvl, item->HeroicCha );
		newbon->HeroicMR += CalcRecommendedLevelBonus( lvl, reclvl, item->HeroicMR );
		newbon->HeroicFR += CalcRecommendedLevelBonus( lvl, reclvl, item->HeroicFR );
		newbon->HeroicCR += CalcRecommendedLevelBonus( lvl, reclvl, item->HeroicCR );
		newbon->HeroicPR += CalcRecommendedLevelBonus( lvl, reclvl, item->HeroicPR );
		newbon->HeroicDR += CalcRecommendedLevelBonus( lvl, reclvl, item->HeroicDR );
		newbon->HeroicCorrup += CalcRecommendedLevelBonus( lvl, reclvl, item->HeroicSVCorrup );
	}

	//FatherNitwit: New style haste, shields, and regens
	if(newbon->haste < (int16)item->Haste) {
		newbon->haste = item->Haste;
	}
	if(item->Regen > 0)
		newbon->HPRegen += item->Regen;

	if(item->ManaRegen > 0)
		newbon->ManaRegen += item->ManaRegen;

	if(item->EnduranceRegen > 0)
		newbon->EnduranceRegen += item->EnduranceRegen;

	if(item->Attack > 0) {

		int cap = RuleI(Character, ItemATKCap);
		cap += itembonuses.ItemATKCap + spellbonuses.ItemATKCap + aabonuses.ItemATKCap;

		if((newbon->ATK + item->Attack) > cap)
			newbon->ATK = RuleI(Character, ItemATKCap);
		else
			newbon->ATK += item->Attack;
	}
	if(item->DamageShield > 0) {
		if((newbon->DamageShield + item->DamageShield) > RuleI(Character, ItemDamageShieldCap))
			newbon->DamageShield = RuleI(Character, ItemDamageShieldCap);
		else
			newbon->DamageShield += item->DamageShield;
	}
	if(item->SpellShield > 0) {
		if((newbon->SpellShield + item->SpellShield) > RuleI(Character, ItemSpellShieldingCap))
			newbon->SpellShield = RuleI(Character, ItemSpellShieldingCap);
		else
			newbon->SpellShield += item->SpellShield;
	}
	if(item->Shielding > 0) {
		if((newbon->MeleeMitigation + item->Shielding) > RuleI(Character, ItemShieldingCap))
			newbon->MeleeMitigation = RuleI(Character, ItemShieldingCap);
		else
			newbon->MeleeMitigation += item->Shielding;
	}
	if(item->StunResist > 0) {
		if((newbon->StunResist + item->StunResist) > RuleI(Character, ItemStunResistCap))
			newbon->StunResist = RuleI(Character, ItemStunResistCap);
		else
			newbon->StunResist += item->StunResist;
	}
	if(item->StrikeThrough > 0) {
		if((newbon->StrikeThrough + item->StrikeThrough) > RuleI(Character, ItemStrikethroughCap))
			newbon->StrikeThrough = RuleI(Character, ItemStrikethroughCap);
		else
			newbon->StrikeThrough += item->StrikeThrough;
	}
	if(item->Avoidance > 0) {
		if((newbon->AvoidMeleeChance + item->Avoidance) > RuleI(Character, ItemAvoidanceCap))
			newbon->AvoidMeleeChance = RuleI(Character, ItemAvoidanceCap);
		else
			newbon->AvoidMeleeChance += item->Avoidance;
	}
	if(item->Accuracy > 0) {
		if((newbon->HitChance + item->Accuracy) > RuleI(Character, ItemAccuracyCap))
			newbon->HitChance = RuleI(Character, ItemAccuracyCap);
		else
			newbon->HitChance += item->Accuracy;
	}
	if(item->CombatEffects > 0) {
		if((newbon->ProcChance + item->CombatEffects) > RuleI(Character, ItemCombatEffectsCap))
			newbon->ProcChance = RuleI(Character, ItemCombatEffectsCap);
		else
			newbon->ProcChance += item->CombatEffects;
	}
	if(item->DotShielding > 0) {
		if((newbon->DoTShielding + item->DotShielding) > RuleI(Character, ItemDoTShieldingCap))
			newbon->DoTShielding = RuleI(Character, ItemDoTShieldingCap);
		else
			newbon->DoTShielding += item->DotShielding;
	}

	if(item->HealAmt > 0) {
		if((newbon->HealAmt + item->HealAmt) > RuleI(Character, ItemHealAmtCap))
			newbon->HealAmt = RuleI(Character, ItemHealAmtCap);
		else
			newbon->HealAmt += item->HealAmt;
	}
	if(item->SpellDmg > 0) {
		if((newbon->SpellDmg + item->SpellDmg) > RuleI(Character, ItemSpellDmgCap))
			newbon->SpellDmg = RuleI(Character, ItemSpellDmgCap);
		else
			newbon->SpellDmg += item->SpellDmg;
	}
	if(item->Clairvoyance > 0) {
		if((newbon->Clairvoyance + item->Clairvoyance) > RuleI(Character, ItemClairvoyanceCap))
			newbon->Clairvoyance = RuleI(Character, ItemClairvoyanceCap);
		else
			newbon->Clairvoyance += item->Clairvoyance;
	}

	if(item->DSMitigation > 0) {
		if((newbon->DSMitigation + item->DSMitigation) > RuleI(Character, ItemDSMitigationCap))
			newbon->DSMitigation = RuleI(Character, ItemDSMitigationCap);
		else
			newbon->DSMitigation += item->DSMitigation;
	}
	if (item->Worn.Effect>0 && (item->Worn.Type == ET_WornEffect)) { // latent effects
		ApplySpellsBonuses(item->Worn.Effect, item->Worn.Level, newbon, 0, true);
	}

	if (item->Focus.Effect>0 && (item->Focus.Type == ET_Focus)) { // focus effects
		ApplySpellsBonuses(item->Focus.Effect, item->Focus.Level, newbon, 0, true);
	}

	switch(item->BardType)
	{
	case 51: /* All (e.g. Singing Short Sword) */
		{
			if(item->BardValue > newbon->singingMod)
				newbon->singingMod = item->BardValue;
			if(item->BardValue > newbon->brassMod)
				newbon->brassMod = item->BardValue;
			if(item->BardValue > newbon->stringedMod)
				newbon->stringedMod = item->BardValue;
			if(item->BardValue > newbon->percussionMod)
				newbon->percussionMod = item->BardValue;
			if(item->BardValue > newbon->windMod)
				newbon->windMod = item->BardValue;
			break;
		}
	case 50: /* Singing */
		{
			if(item->BardValue > newbon->singingMod)
				newbon->singingMod = item->BardValue;
			break;
		}
	case 23: /* Wind */
		{
			if(item->BardValue > newbon->windMod)
				newbon->windMod = item->BardValue;
			break;
		}
	case 24: /* stringed */
		{
			if(item->BardValue > newbon->stringedMod)
				newbon->stringedMod = item->BardValue;
			break;
		}
	case 25: /* brass */
		{
			if(item->BardValue > newbon->brassMod)
				newbon->brassMod = item->BardValue;
			break;
		}
	case 26: /* Percussion */
		{
			if(item->BardValue > newbon->percussionMod)
				newbon->percussionMod = item->BardValue;
			break;
		}
	}

	if (item->SkillModValue != 0 && item->SkillModType <= HIGHEST_SKILL){
		if ((item->SkillModValue > 0 && newbon->skillmod[item->SkillModType] < item->SkillModValue) ||
			(item->SkillModValue < 0 && newbon->skillmod[item->SkillModType] > item->SkillModValue))
		{
			newbon->skillmod[item->SkillModType] = item->SkillModValue;
		}
	}

	// Add Item Faction Mods
	if (item->FactionMod1)
	{
		if (item->FactionAmt1 > 0 && item->FactionAmt1 > GetItemFactionBonus(item->FactionMod1))
		{
			AddItemFactionBonus(item->FactionMod1, item->FactionAmt1);
		}
		else if (item->FactionAmt1 < 0 && item->FactionAmt1 < GetItemFactionBonus(item->FactionMod1))
		{
			AddItemFactionBonus(item->FactionMod1, item->FactionAmt1);
		}
	}
	if (item->FactionMod2)
	{
		if (item->FactionAmt2 > 0 && item->FactionAmt2 > GetItemFactionBonus(item->FactionMod2))
		{
			AddItemFactionBonus(item->FactionMod2, item->FactionAmt2);
		}
		else if (item->FactionAmt2 < 0 && item->FactionAmt2 < GetItemFactionBonus(item->FactionMod2))
		{
			AddItemFactionBonus(item->FactionMod2, item->FactionAmt2);
		}
	}
	if (item->FactionMod3)
	{
		if (item->FactionAmt3 > 0 && item->FactionAmt3 > GetItemFactionBonus(item->FactionMod3))
		{
			AddItemFactionBonus(item->FactionMod3, item->FactionAmt3);
		}
		else if (item->FactionAmt3 < 0 && item->FactionAmt3 < GetItemFactionBonus(item->FactionMod3))
		{
			AddItemFactionBonus(item->FactionMod3, item->FactionAmt3);
		}
	}
	if (item->FactionMod4)
	{
		if (item->FactionAmt4 > 0 && item->FactionAmt4 > GetItemFactionBonus(item->FactionMod4))
		{
			AddItemFactionBonus(item->FactionMod4, item->FactionAmt4);
		}
		else if (item->FactionAmt4 < 0 && item->FactionAmt4 < GetItemFactionBonus(item->FactionMod4))
		{
			AddItemFactionBonus(item->FactionMod4, item->FactionAmt4);
		}
	}

	if (item->ExtraDmgSkill != 0 && item->ExtraDmgSkill <= HIGHEST_SKILL) {
		if((newbon->SkillDamageAmount[item->ExtraDmgSkill] + item->ExtraDmgAmt) > RuleI(Character, ItemExtraDmgCap))
			newbon->SkillDamageAmount[item->ExtraDmgSkill] = RuleI(Character, ItemExtraDmgCap);
		else
			newbon->SkillDamageAmount[item->ExtraDmgSkill] += item->ExtraDmgAmt;
	}

	if (!isAug)
	{
		int i;
		for(i = 0; i < MAX_AUGMENT_SLOTS; i++) {
			AddItemBonuses(inst->GetAugment(i),newbon,true);
		}
	}

}

int Merc::GroupLeadershipAAHealthEnhancement()
{
	Group *g = GetGroup();

	if(!g || (g->GroupCount() < 3))
		return 0;

	switch(g->GetLeadershipAA(groupAAHealthEnhancement))
	{
		case 0:
			return 0;
		case 1:
			return 30;
		case 2:
			return 60;
		case 3:
			return 100;
	}

	return 0;
}

int Merc::GroupLeadershipAAManaEnhancement()
{
	Group *g = GetGroup();

	if(!g || (g->GroupCount() < 3))
		return 0;

	switch(g->GetLeadershipAA(groupAAManaEnhancement))
	{
		case 0:
			return 0;
		case 1:
			return 30;
		case 2:
			return 60;
		case 3:
			return 100;
	}

	return 0;
}

int Merc::GroupLeadershipAAHealthRegeneration()
{
	Group *g = GetGroup();

	if(!g || (g->GroupCount() < 3))
		return 0;

	switch(g->GetLeadershipAA(groupAAHealthRegeneration))
	{
		case 0:
			return 0;
		case 1:
			return 4;
		case 2:
			return 6;
		case 3:
			return 8;
	}

	return 0;
}

int Merc::GroupLeadershipAAOffenseEnhancement()
{
	Group *g = GetGroup();

	if(!g || (g->GroupCount() < 3))
		return 0;

	switch(g->GetLeadershipAA(groupAAOffenseEnhancement))
	{
		case 0:
			return 0;
		case 1:
			return 10;
		case 2:
			return 19;
		case 3:
			return 28;
		case 4:
			return 34;
		case 5:
			return 40;
	}
	return 0;
}

int16 Merc::CalcSTR() {
	int16 val = _baseSTR + itembonuses.STR + spellbonuses.STR;

	int16 mod = aabonuses.STR;

	STR = val + mod;

	if(STR < 1)
		STR = 1;

	return(STR);
}

int16 Merc::CalcSTA() {
	int16 val = _baseSTA + itembonuses.STA + spellbonuses.STA;

	int16 mod = aabonuses.STA;

	STA = val + mod;

	if(STA < 1)
		STA = 1;

	return(STA);
}

int16 Merc::CalcAGI() {
	int16 val = _baseAGI + itembonuses.AGI + spellbonuses.AGI;
	int16 mod = aabonuses.AGI;

	int16 str = GetSTR();

	AGI = val + mod;

	if(AGI < 1)
		AGI = 1;

	return(AGI);
}

int16 Merc::CalcDEX() {
	int16 val = _baseDEX + itembonuses.DEX + spellbonuses.DEX;

	int16 mod = aabonuses.DEX;

	DEX = val + mod;

	if(DEX < 1)
		DEX = 1;

	return(DEX);
}

int16 Merc::CalcINT() {
	int16 val = _baseINT + itembonuses.INT + spellbonuses.INT;

	int16 mod = aabonuses.INT;

	INT = val + mod;

	if(INT < 1)
		INT = 1;

	return(INT);
}

int16 Merc::CalcWIS() {
	int16 val = _baseWIS + itembonuses.WIS + spellbonuses.WIS;

	int16 mod = aabonuses.WIS;

	WIS = val + mod;

	if(WIS < 1)
		WIS = 1;

	return(WIS);
}

int16 Merc::CalcCHA() {
	int16 val = _baseCHA + itembonuses.CHA + spellbonuses.CHA;

	int16 mod = aabonuses.CHA;

	CHA = val + mod;

	if(CHA < 1)
		CHA = 1;

	return(CHA);
}

//The AA multipliers are set to be 5, but were 2 on WR
//The resistant discipline which I think should be here is implemented
//in Mob::ResistSpell
int16	Merc::CalcMR()
{
	MR = _baseMR + itembonuses.MR + spellbonuses.MR + aabonuses.MR;

	if(MR < 1)
		MR = 1;

	return(MR);
}

int16	Merc::CalcFR()
{
	FR = _baseFR + itembonuses.FR + spellbonuses.FR + aabonuses.FR;

	if(FR < 1)
		FR = 1;

	return(FR);
}

int16	Merc::CalcDR()
{
	DR = _baseDR + itembonuses.DR + spellbonuses.DR + aabonuses.DR;

	if(DR < 1)
		DR = 1;

	return(DR);
}

int16	Merc::CalcPR()
{
	PR = _basePR + itembonuses.PR + spellbonuses.PR + aabonuses.PR;

	if(PR < 1)
		PR = 1;

	return(PR);
}

int16	Merc::CalcCR()
{
	CR = _baseCR + itembonuses.CR + spellbonuses.CR + aabonuses.CR;

	if(CR < 1)
		CR = 1;

	return(CR);
}

int16	Merc::CalcCorrup()
{
	Corrup = _baseCorrup + itembonuses.Corrup + spellbonuses.Corrup + aabonuses.Corrup;

	return(Corrup);
}

int16 Merc::CalcATK() {
	ATK = _baseATK + itembonuses.ATK + spellbonuses.ATK + aabonuses.ATK + GroupLeadershipAAOffenseEnhancement() + ((GetSTR() + GetSkill(OFFENSE)) * 9 / 10);
	return(ATK);
}

int16 Merc::CalcAC() {
	//spell AC bonuses are added directly to natural total
	AC = _baseAC + spellbonuses.AC;
	return(AC);
}

int32 Merc::CalcHPRegen() {
	int32 regen = hp_regen + itembonuses.HPRegen + spellbonuses.HPRegen;

	regen += aabonuses.HPRegen + GroupLeadershipAAHealthRegeneration();

	return (regen * RuleI(Character, HPRegenMultiplier) / 100);
}

int32 Merc::CalcHPRegenCap()
{
	int cap = RuleI(Character, ItemHealthRegenCap) + itembonuses.HeroicSTA/25;

	cap += aabonuses.ItemHPRegenCap + spellbonuses.ItemHPRegenCap + itembonuses.ItemHPRegenCap;

	return (cap * RuleI(Character, HPRegenMultiplier) / 100);
}

int32 Merc::CalcMaxHP() {
	float nd = 10000;
	max_hp = (CalcBaseHP() + itembonuses.HP);

	//The AA desc clearly says it only applies to base hp..
	//but the actual effect sent on live causes the client
	//to apply it to (basehp + itemhp).. I will oblige to the client's whims over
	//the aa description
	nd += aabonuses.MaxHP;	//Natural Durability, Physical Enhancement, Planar Durability

	max_hp = (float)max_hp * (float)nd / (float)10000; //this is to fix the HP-above-495k issue
	max_hp += spellbonuses.HP + aabonuses.HP;

	max_hp += GroupLeadershipAAHealthEnhancement();

	max_hp += max_hp * (spellbonuses.MaxHPChange + itembonuses.MaxHPChange) / 10000;

	if (cur_hp > max_hp)
		cur_hp = max_hp;

	int hp_perc_cap = spellbonuses.HPPercCap;
	if(hp_perc_cap) {
		int curHP_cap = (max_hp * hp_perc_cap) / 100;
		if (cur_hp > curHP_cap)
			cur_hp = curHP_cap;
	}

	return max_hp;
}

int32 Merc::CalcBaseHP()
{
	return base_hp;
}

int32 Merc::CalcMaxMana()
{
	switch(GetCasterClass())
	{
		case 'I':
		case 'W': {
			max_mana = (CalcBaseMana() + itembonuses.Mana + spellbonuses.Mana + GroupLeadershipAAManaEnhancement());
			break;
		}
		case 'N': {
			max_mana = 0;
			break;
		}
		default: {
			LogFile->write(EQEMuLog::Debug, "Invalid Class '%c' in CalcMaxMana", GetCasterClass());
			max_mana = 0;
			break;
		}
	}
	if (max_mana < 0) {
		max_mana = 0;
	}

	if (cur_mana > max_mana) {
		cur_mana = max_mana;
	}

	int mana_perc_cap = spellbonuses.ManaPercCap;
	if(mana_perc_cap) {
		int curMana_cap = (max_mana * mana_perc_cap) / 100;
		if (cur_mana > curMana_cap)
			cur_mana = curMana_cap;
	}

#if EQDEBUG >= 11
	LogFile->write(EQEMuLog::Debug, "Merc::CalcMaxMana() called for %s - returning %d", GetName(), max_mana);
#endif
	return max_mana;
}

int32 Merc::CalcBaseMana()
{
	return base_mana;
}

int32 Merc::CalcBaseManaRegen() 
{
	uint8 clevel = GetLevel();
	int32 regen = 0;
	if (IsSitting())
	{
		if(HasSkill(MEDITATE))
			regen = (((GetSkill(MEDITATE) / 10) + (clevel - (clevel / 4))) / 4) + 4;
		else
			regen = 2;
	}
	else {
		regen = 2;
	}
	return regen;
}

int32 Merc::CalcManaRegen() 
{
	int32 regen = 0;
	//this should be changed so we dont med while camping, etc...
	if (IsSitting())
	{
		BuffFadeBySitModifier();
		if(HasSkill(MEDITATE)) {
			this->_medding = true;
			regen = ((GetSkill(MEDITATE) / 10) + mana_regen);
			regen += spellbonuses.ManaRegen + itembonuses.ManaRegen;
		}
		else
			regen = mana_regen + spellbonuses.ManaRegen + itembonuses.ManaRegen;
	}
	else {
		this->_medding = false;
		regen = mana_regen + spellbonuses.ManaRegen + itembonuses.ManaRegen;
	}

	//AAs
	regen += aabonuses.ManaRegen;

	return (regen * RuleI(Character, ManaRegenMultiplier) / 100);
}

int32 Merc::CalcManaRegenCap()
{
	int32 cap = RuleI(Character, ItemManaRegenCap) + aabonuses.ItemManaRegenCap;
	switch(GetCasterClass())
	{
		case 'I':
			cap += (itembonuses.HeroicINT / 25);
			break;
		case 'W':
			cap += (itembonuses.HeroicWIS / 25);
			break;
	}

	return (cap * RuleI(Character, ManaRegenMultiplier) / 100);
}

void Merc::CalcMaxEndurance()
{
	max_end = CalcBaseEndurance() + spellbonuses.Endurance + itembonuses.Endurance;

	if (max_end < 0) {
		max_end = 0;
	}

	if (cur_end > max_end) {
		cur_end = max_end;
	}

	int end_perc_cap = spellbonuses.EndPercCap;
	if(end_perc_cap) {
		int curEnd_cap = (max_end * end_perc_cap) / 100;
		if (cur_end > curEnd_cap)
			cur_end = curEnd_cap;
	}
}

int32 Merc::CalcBaseEndurance()
{
	int32 base_end = 0;
	int32 base_endurance = 0;
	int32 ConvertedStats = 0;
	int32 sta_end = 0;
	int Stats = 0;

	if(GetClientVersion() >= EQClientSoD && RuleB(Character, SoDClientUseSoDHPManaEnd)) {
		int HeroicStats = 0;

		Stats = ((GetSTR() + GetSTA() + GetDEX() + GetAGI()) / 4);
		HeroicStats = ((GetHeroicSTR() + GetHeroicSTA() + GetHeroicDEX() + GetHeroicAGI()) / 4);

		if (Stats > 100) {
			ConvertedStats = (((Stats - 100) * 5 / 2) + 100);
			if (Stats > 201) {
				ConvertedStats -= ((Stats - 201) * 5 / 4);
			}
		}
		else {
			ConvertedStats = Stats;
		}

		if (GetLevel() < 41) {
			sta_end = (GetLevel() * 75 * ConvertedStats / 1000);
			base_endurance = (GetLevel() * 15);
		}
		else if (GetLevel() < 81) {
			sta_end = ((3 * ConvertedStats) + ((GetLevel() - 40) * 15 * ConvertedStats / 100));
			base_endurance = (600 + ((GetLevel() - 40) * 30));
		}
		else {
			sta_end = (9 * ConvertedStats);
			base_endurance = (1800 + ((GetLevel() - 80) * 18));
		}
		base_end = (base_endurance + sta_end + (HeroicStats * 10));
	}
	else
	{
		Stats = GetSTR()+GetSTA()+GetDEX()+GetAGI();
		int LevelBase = GetLevel() * 15;

		int at_most_800 = Stats;
		if(at_most_800 > 800)
			at_most_800 = 800;

		int Bonus400to800 = 0;
		int HalfBonus400to800 = 0;
		int Bonus800plus = 0;
		int HalfBonus800plus = 0;

		int BonusUpto800 = int( at_most_800 / 4 ) ;
		if(Stats > 400) {
			Bonus400to800 = int( (at_most_800 - 400) / 4 );
			HalfBonus400to800 = int( max( ( at_most_800 - 400 ), 0 ) / 8 );

			if(Stats > 800) {
				Bonus800plus = int( (Stats - 800) / 8 ) * 2;
				HalfBonus800plus = int( (Stats - 800) / 16 );
			}
		}
		int bonus_sum = BonusUpto800 + Bonus400to800 + HalfBonus400to800 + Bonus800plus + HalfBonus800plus;

		base_end = LevelBase;

		//take all of the sums from above, then multiply by level*0.075
		base_end += ( bonus_sum * 3 * GetLevel() ) / 40;
	}
	return base_end;
}

int32 Merc::CalcEnduranceRegen() {
	int32 regen = int32(GetLevel() * 4 / 10) + 2;
	regen += aabonuses.EnduranceRegen + spellbonuses.EnduranceRegen + itembonuses.EnduranceRegen;

	return (regen * RuleI(Character, EnduranceRegenMultiplier) / 100);
}

int32 Merc::CalcEnduranceRegenCap() {
	int cap = (RuleI(Character, ItemEnduranceRegenCap) + itembonuses.HeroicSTR/25 + itembonuses.HeroicDEX/25 + itembonuses.HeroicAGI/25 + itembonuses.HeroicSTA/25);

	return (cap * RuleI(Character, EnduranceRegenMultiplier) / 100);
}

void Merc::SetEndurance(int32 newEnd)
{
	/*Endurance can't be less than 0 or greater than max*/
	if(newEnd < 0)
		newEnd = 0;
	else if(newEnd > GetMaxEndurance()){
		newEnd = GetMaxEndurance();
	}

	cur_end = newEnd;
}

void Merc::DoEnduranceUpkeep() {
	int upkeep_sum = 0;

	int cost_redux = spellbonuses.EnduranceReduction + itembonuses.EnduranceReduction;

	uint32 buffs_i;
	uint32 buff_count = GetMaxTotalSlots();
	for (buffs_i = 0; buffs_i < buff_count; buffs_i++) {
		if (buffs[buffs_i].spellid != SPELL_UNKNOWN) {
			int upkeep = spells[buffs[buffs_i].spellid].EndurUpkeep;
			if(upkeep > 0) {
				if(cost_redux > 0) {
					if(upkeep <= cost_redux)
						continue;	//reduced to 0
					upkeep -= cost_redux;
				}
				if((upkeep+upkeep_sum) > GetEndurance()) {
					//they do not have enough to keep this one going.
					BuffFadeBySlot(buffs_i);
				} else {
					upkeep_sum += upkeep;
				}
			}
		}
	}

	if(upkeep_sum != 0)
		SetEndurance(GetEndurance() - upkeep_sum);
}

void Merc::CalcRestState() {

	// This method calculates rest state HP and mana regeneration.
	// The bot must have been out of combat for RuleI(Character, RestRegenTimeToActivate) seconds,
	// must be sitting down, and must not have any detrimental spells affecting them.
	//
	if(!RuleI(Character, RestRegenPercent))
		return;

	RestRegenHP = RestRegenMana = RestRegenEndurance = 0;

	if(IsEngaged() || !IsSitting())
		return;

	if(!rest_timer.Check(false))
		return;

	uint32 buff_count = GetMaxTotalSlots();
	for (unsigned int j = 0; j < buff_count; j++) {
		if(buffs[j].spellid != SPELL_UNKNOWN) {
			if(IsDetrimentalSpell(buffs[j].spellid) && (buffs[j].ticsremaining > 0))
				if(!DetrimentalSpellAllowsRest(buffs[j].spellid))
					return;
		}
	}

	RestRegenHP = (GetMaxHP() * RuleI(Character, RestRegenPercent) / 100);

	RestRegenMana = (GetMaxMana() * RuleI(Character, RestRegenPercent) / 100);

	if(RuleB(Character, RestRegenEndurance))
		RestRegenEndurance = (GetMaxEndurance() * RuleI(Character, RestRegenPercent) / 100);
}

bool Merc::HasSkill(SkillType skill_id) const {
	return((GetSkill(skill_id) > 0) && CanHaveSkill(skill_id));
}

bool Merc::CanHaveSkill(SkillType skill_id) const {
	return(database.GetSkillCap(GetClass(), skill_id, RuleI(Character, MaxLevel)) > 0);
	//if you don't have it by max level, then odds are you never will?
}

uint16 Merc::MaxSkill(SkillType skillid, uint16 class_, uint16 level) const {
	return(database.GetSkillCap(class_, skillid, level));
}

void Merc::FillSpawnStruct(NewSpawn_Struct* ns, Mob* ForWho) {
	if(ns) {
		Mob::FillSpawnStruct(ns, ForWho);

		ns->spawn.afk = 0;
		ns->spawn.lfg = 0;
		ns->spawn.anon = 0;
		ns->spawn.gm = 0;
		ns->spawn.guildID = 0xFFFFFFFF;		// 0xFFFFFFFF = NO GUILD, 0 = Unknown Guild
		ns->spawn.is_npc = 1;				// 0=no, 1=yes
		ns->spawn.is_pet = 0;
		ns->spawn.guildrank = 0;
		ns->spawn.showhelm = 1;
		ns->spawn.flymode = 0;
		ns->spawn.size = 0;
		ns->spawn.NPC = 1;					// 0=player,1=npc,2=pc corpse,3=npc corpse
		ns->spawn.IsMercenary = 1;
		/*const Item_Struct* item = 0;
		const ItemInst* inst = 0;

		uint32 spawnedmercid = 0;
		spawnedmercid = this->GetID();

		inst = GetBotItem(SLOT_HANDS);
		if(inst) {
			item = inst->GetItem();
			if(item) {
				ns->spawn.equipment[MATERIAL_HANDS]	= item->Material;
				ns->spawn.colors[MATERIAL_HANDS].color = GetEquipmentColor(MATERIAL_HANDS);
			}
		}

		inst = GetBotItem(SLOT_HEAD);
		if(inst) {
			item = inst->GetItem();
			if(item) {
				ns->spawn.equipment[MATERIAL_HEAD] = item->Material;
				ns->spawn.colors[MATERIAL_HEAD].color = GetEquipmentColor(MATERIAL_HEAD);
			}
		}

		inst = GetBotItem(SLOT_ARMS);
		if(inst) {
			item = inst->GetItem();
			if(item) {
				ns->spawn.equipment[MATERIAL_ARMS] = item->Material;
				ns->spawn.colors[MATERIAL_ARMS].color = GetEquipmentColor(MATERIAL_ARMS);
			}
		}

		inst = GetBotItem(SLOT_BRACER01);
		if(inst) {
			item = inst->GetItem();
			if(item) {
				ns->spawn.equipment[MATERIAL_BRACER] = item->Material;
				ns->spawn.colors[MATERIAL_BRACER].color	= GetEquipmentColor(MATERIAL_BRACER);
			}
		}

		inst = GetBotItem(SLOT_BRACER02);
		if(inst) {
			item = inst->GetItem();
			if(item) {
				ns->spawn.equipment[MATERIAL_BRACER] = item->Material;
				ns->spawn.colors[MATERIAL_BRACER].color	= GetEquipmentColor(MATERIAL_BRACER);
			}
		}

		inst = GetBotItem(SLOT_CHEST);
		if(inst) {
			item = inst->GetItem();
			if(item) {
				ns->spawn.equipment[MATERIAL_CHEST]	= item->Material;
				ns->spawn.colors[MATERIAL_CHEST].color = GetEquipmentColor(MATERIAL_CHEST);
			}
		}

		inst = GetBotItem(SLOT_LEGS);
		if(inst) {
			item = inst->GetItem();
			if(item) {
				ns->spawn.equipment[MATERIAL_LEGS] = item->Material;
				ns->spawn.colors[MATERIAL_LEGS].color = GetEquipmentColor(MATERIAL_LEGS);
			}
		}

		inst = GetBotItem(SLOT_FEET);
		if(inst) {
			item = inst->GetItem();
			if(item) {
				ns->spawn.equipment[MATERIAL_FEET] = item->Material;
				ns->spawn.colors[MATERIAL_FEET].color = GetEquipmentColor(MATERIAL_FEET);
			}
		}

		inst = GetBotItem(SLOT_PRIMARY);
		if(inst) {
			item = inst->GetItem();
			if(item) {
				if(strlen(item->IDFile) > 2)
					ns->spawn.equipment[MATERIAL_PRIMARY] = atoi(&item->IDFile[2]);
					ns->spawn.colors[MATERIAL_PRIMARY].color = GetEquipmentColor(MATERIAL_PRIMARY);
			}
		}

		inst = GetBotItem(SLOT_SECONDARY);
		if(inst) {
			item = inst->GetItem();
			if(item) {
				if(strlen(item->IDFile) > 2)
					ns->spawn.equipment[MATERIAL_SECONDARY] = atoi(&item->IDFile[2]);
					ns->spawn.colors[MATERIAL_SECONDARY].color = GetEquipmentColor(MATERIAL_SECONDARY);
			}
		}*/
	}
}

bool Merc::Process()
{
	if(IsStunned() && stunned_timer.Check())
	{
		this->stunned = false;
		this->stunned_timer.Disable();
	}

	if (p_depop)
    {
		SetOwnerID(0);
		SetMercID(0);
		return false;
    }

	if(!GetMercOwner()) {
		//p_depop = true;		//this was causing a crash - removed merc from entity list, but not group
		//return false;			//merc can live after client dies, not sure how long
	}

	if(IsSuspended()) {
		//return false;
	}

	if (HasGroup() && GetFollowID() == 0) {
		SetFollowID(GetMercOwner()->GetID());
	}


	SpellProcess();

	if(tic_timer.Check())
	{
		//6 seconds, or whatever the rule is set to has passed, send this position to everyone to avoid ghosting
		if(!IsMoving() && !IsEngaged())
		{
			SendPosition();
			if(IsSitting()) {
				if(!rest_timer.Enabled()) {
					rest_timer.Start(RuleI(Character, RestRegenTimeToActivate) * 1000);
				}
			}
		}

		BuffProcess();

		CalcRestState();

		if(GetHP() < GetMaxHP())
			SetHP(GetHP() + CalcHPRegen());

		if(GetMana() < GetMaxMana())
			SetMana(GetMana() + CalcManaRegen());

		if(GetEndurance() < GetMaxEndurance())
			SetEndurance(GetEndurance() + CalcEnduranceRegen());
	}

	if (sendhpupdate_timer.Check()) {
		SendHPUpdate();
	}

	if (endupkeep_timer.Check() && GetHP() > 0){
		DoEnduranceUpkeep();
	}

	if (IsStunned() || IsMezzed())
		return true;

	// Merc AI
	AI_Process();

	return true;
}

bool Merc::IsMercCasterCombatRange(Mob *target) {
	bool result = false;

	if(target) {
		float range = MercAISpellRange;

		range *= range;

		// half the max so the bot doesn't always stop at max range to allow combat movement
		range *= .5;

		float targetDistance = DistNoRootNoZ(*target);

		if(targetDistance > range)
			result = false;
		else
			result = true;
	}

	return result;
}

void Merc::AI_Process() {
	if(!IsAIControlled())
		return;

	if(IsCasting())
		return;

	// A bot wont start its AI if not grouped
	if(!GetOwner() || !HasGroup()) {
		return;
	}

	if(GetAppearance() == eaDead)
		return;

	Mob* MercOwner = GetOwner();

	// The bots need an owner
	if(!MercOwner)
		return;

	try {
		if(MercOwner->CastToClient()->IsDead()) {
			SetTarget(0);
			SetOwnerID(0);
			return;
		}
	}
	catch(...) {
		SetTarget(0);
		SetOwnerID(0);
		return;
	}

	if(!IsEngaged()) {
		if(GetFollowID()) {
			Group* g = GetGroup();
			if(g) {
				if(MercOwner && MercOwner->GetTarget() && MercOwner->GetTarget()->IsNPC() && (MercOwner->GetTarget()->GetHateAmount(MercOwner) || MercOwner->CastToClient()->AutoAttackEnabled()) && IsAttackAllowed(MercOwner->GetTarget())) {
						float range = g->HasRole(MercOwner, RolePuller) ? RuleI(Mercs, AggroRadiusPuller) : RuleI(Mercs, AggroRadius);
						range = range * range;
						if(MercOwner->GetTarget()->DistNoRootNoZ(*this) < range) {
							AddToHateList(MercOwner->GetTarget(), 1);
						}
				}
				else {
					for(int counter = 0; counter < g->GroupCount(); counter++) {
						if(g->members[counter]) {
							if(g->members[counter]->GetTarget() && g->members[counter]->GetTarget()->IsNPC() && g->members[counter]->GetTarget()->GetHateAmount(MercOwner) && IsAttackAllowed(MercOwner->GetTarget())) {
								float range = g->HasRole(g->members[counter], RolePuller) ? RuleI(Mercs, AggroRadiusPuller) : RuleI(Mercs, AggroRadius);
								range = range * range;
								if(g->members[counter]->GetTarget()->DistNoRootNoZ(*this) < range) {
									AddToHateList(g->members[counter]->GetTarget(), 1);
								}
							}
						}
					}
				}
			}
		}
	}

	if(IsEngaged())
	{
		_ZP(Mob_BOT_Process_IsEngaged);

		if(rest_timer.Enabled())
			rest_timer.Disable();

		if(IsRooted())
			SetTarget(hate_list.GetClosest(this));
		else
			FindTarget();

		if(!GetTarget())
			return;

		if(HasPet())
			GetPet()->SetTarget(GetTarget());

		if(!IsSitting())
			FaceTarget(GetTarget());

		if(DivineAura())
			return;

		// Let's check if we have a los with our target.
		// If we don't, our hate_list is wiped.
		// Else, it was causing the bot to aggro behind wall etc... causing massive trains.
		if(!CheckLosFN(GetTarget()) || GetTarget()->IsMezzed() || !IsAttackAllowed(GetTarget())) {
			WipeHateList();

			if(IsMoving()) {
				SetHeading(0);
				SetRunAnimSpeed(0);

				if(moved) {
					moved = false;
					SendPosition();
					SetMoving(false);
				}
			}

			return;
		}

		bool atCombatRange = false;

		float meleeDistance = GetMaxMeleeRangeToTarget(GetTarget());

		if(GetClass() == SHADOWKNIGHT || GetClass() == PALADIN || GetClass() == WARRIOR) {
			meleeDistance = meleeDistance * .30;
		}
		else {
			meleeDistance *= (float)MakeRandomFloat(.50, .85);
		}
		if(IsMercCaster() && GetLevel() > 12) {
			if(IsMercCasterCombatRange(GetTarget()))
				atCombatRange = true;
		}
		else if(DistNoRoot(*GetTarget()) <= meleeDistance) {
			atCombatRange = true;
		}

		if(atCombatRange) {
			if(IsMoving()) {
				SetHeading(CalculateHeadingToTarget(GetTarget()->GetX(), GetTarget()->GetY()));
				SetRunAnimSpeed(0);

				if(moved) {
					moved = false;
					SendPosition();
					SetMoving(false);
				}
			}

			if(AImovement_timer->Check()) {
				if(!IsMoving() && GetClass() == ROGUE && !BehindMob(GetTarget(), GetX(), GetY())) {
					// Move the rogue to behind the mob
					float newX = 0;
					float newY = 0;
					float newZ = 0;

					if(PlotPositionAroundTarget(GetTarget(), newX, newY, newZ)) {
						CalculateNewPosition2(newX, newY, newZ, GetRunspeed());
						return;
					}
				}
				else if(!IsMoving() && GetClass() != ROGUE && (DistNoRootNoZ(*GetTarget()) < GetTarget()->GetSize())) {
					// If we are not a rogue trying to backstab, let's try to adjust our melee range so we don't appear to be bunched up
					float newX = 0;
					float newY = 0;
					float newZ = 0;

					if(PlotPositionAroundTarget(GetTarget(), newX, newY, newZ, false) && GetArchetype() != ARCHETYPE_CASTER) {
						CalculateNewPosition2(newX, newY, newZ, GetRunspeed());
						return;
					}
				}

				if(IsMoving())
					SendPosUpdate();
				else
					SendPosition();
			}

			if(!IsMercCaster() && GetTarget() && !IsStunned() && !IsMezzed() && (GetAppearance() != eaDead)) {
				// we can't fight if we don't have a target, are stun/mezzed or dead..
				// Stop attacking if the target is enraged
				if(IsEngaged() && !BehindMob(GetTarget(), GetX(), GetY()) && GetTarget()->IsEnraged())
					return;
				//TODO: Implement Stances.
				/*if(GetBotStance() == BotStancePassive)
					return;*/

				// First, special attack per class (kick, backstab etc..)
				DoClassAttacks(GetTarget());

				//try main hand first
				if(attack_timer.Check()) {
					Attack(GetTarget(), SLOT_PRIMARY);

					bool tripleSuccess = false;

					if(GetOwner() && GetTarget() && CanThisClassDoubleAttack()) {

						if(GetOwner()) {
							Attack(GetTarget(), SLOT_PRIMARY, true);
						}

						if(GetOwner() && GetTarget() && SpecAttacks[SPECATK_TRIPLE]) {
							tripleSuccess = true;
							Attack(GetTarget(), SLOT_PRIMARY, true);
						}

						//quad attack, does this belong here??
						if(GetOwner() && GetTarget() && SpecAttacks[SPECATK_QUAD]) {
							Attack(GetTarget(), SLOT_PRIMARY, true);
						}
					}

					//Live AA - Flurry, Rapid Strikes ect (Flurry does not require Triple Attack).
					int16 flurrychance = aabonuses.FlurryChance + spellbonuses.FlurryChance + itembonuses.FlurryChance;

					if (GetTarget() && flurrychance)
					{
						if(MakeRandomInt(0, 100) < flurrychance)
						{
							Message_StringID(MT_NPCFlurry, 128);
							Attack(GetTarget(), SLOT_PRIMARY, false);
							Attack(GetTarget(), SLOT_PRIMARY, false);
						}
					}

					int16 ExtraAttackChanceBonus = spellbonuses.ExtraAttackChance + itembonuses.ExtraAttackChance + aabonuses.ExtraAttackChance;

					if (GetTarget() && ExtraAttackChanceBonus) {
								if(MakeRandomInt(0, 100) < ExtraAttackChanceBonus)
								{
									Attack(GetTarget(), SLOT_PRIMARY, false);
								}
							}
				}

				// TODO: Do mercs berserk? Find this out on live...
				//if (GetClass() == WARRIOR || GetClass() == BERSERKER) {
				//	if(GetHP() > 0 && !berserk && this->GetHPRatio() < 30) {
				//		entity_list.MessageClose_StringID(this, false, 200, 0, BERSERK_START, GetName());
				//		this->berserk = true;
				//	}
				//	if (berserk && this->GetHPRatio() > 30) {
				//		entity_list.MessageClose_StringID(this, false, 200, 0, BERSERK_END, GetName());
				//		this->berserk = false;
				//	}
				//}

				//now off hand
				if(GetTarget() && attack_dw_timer.Check() && CanThisClassDualWield()) {

						int weapontype = NULL;
						bool bIsFist = true;

						if(bIsFist || ((weapontype != ItemType2HS) && (weapontype != ItemType2HPierce) && (weapontype != ItemType2HB))) {
							float DualWieldProbability = 0.0f;

							int16 Ambidexterity = aabonuses.Ambidexterity + spellbonuses.Ambidexterity + itembonuses.Ambidexterity;
							DualWieldProbability = (GetSkill(DUAL_WIELD) + GetLevel() + Ambidexterity) / 400.0f; // 78.0 max
							int16 DWBonus = spellbonuses.DualWieldChance + itembonuses.DualWieldChance;
							DualWieldProbability += DualWieldProbability*float(DWBonus)/ 100.0f;

							float random = MakeRandomFloat(0, 1);

							if (random < DualWieldProbability){ // Max 78% of DW

								Attack(GetTarget(), SLOT_SECONDARY);	// Single attack with offhand

								if( CanThisClassDoubleAttack()) {
									if(GetTarget() && GetTarget()->GetHP() > -10)
										Attack(GetTarget(), SLOT_SECONDARY);	// Single attack with offhand
								}
							}
						}
					}
				}
			}// end in combat range
			else {
				if(GetTarget()->IsFeared() && !spellend_timer.Enabled()){
					// This is a mob that is fleeing either because it has been feared or is low on hitpoints
					//TODO: Implement Stances.
					//if(GetBotStance() != BotStancePassive)
						AI_PursueCastCheck();
				}

				if (AImovement_timer->Check()) {
					if(!IsRooted()) {
						mlog(AI__WAYPOINTS, "Pursuing %s while engaged.", GetTarget()->GetCleanName());
						CalculateNewPosition2(GetTarget()->GetX(), GetTarget()->GetY(), GetTarget()->GetZ(), GetRunspeed());
						return;
					}

					if(IsMoving())
						SendPosUpdate();
					else
						SendPosition();
				}
			} // end not in combat range

			if(!IsMoving() && !spellend_timer.Enabled()) {

				//TODO: Implement Stances.
				//if(GetBotStance() == BotStancePassive)
				//	return;

				if(AI_EngagedCastCheck()) {
					MercMeditate(false);
				}
				else if(GetArchetype() == ARCHETYPE_CASTER)
					MercMeditate(true);
			}
		} // end IsEngaged()
	else {
		// Not engaged in combat
		SetTarget(0);

		if(!IsMoving() && AIthink_timer->Check() && !spellend_timer.Enabled()) {

			//TODO: Implement passive stances.
			//if(GetBotStance() != BotStancePassive) {
			if(!AI_IdleCastCheck() && !IsCasting())
				MercMeditate(true);
		}

		if(AImovement_timer->Check()) {
			if(GetFollowID()) {
				Mob* follow = entity_list.GetMob(GetFollowID());

				if(follow) {
					float dist = DistNoRoot(*follow);
					float speed = GetRunspeed();

					if(dist < GetFollowDistance() + 1000)
						speed = GetWalkspeed();

					SetRunAnimSpeed(0);

					if(dist > GetFollowDistance()) {
						CalculateNewPosition2(follow->GetX(), follow->GetY(), follow->GetZ(), speed);
						if(rest_timer.Enabled())
							rest_timer.Disable();
						return;
					}
					else
					{
						if(moved)
						{
							moved=false;
							SendPosition();
							SetMoving(false);
						}
					}
				}
			}
		}
	}
}

void Merc::AI_Start(int32 iMoveDelay) {
	Mob::AI_Start(iMoveDelay);
	if (!pAIControlled)
		return;

	if (merc_spells.size() == 0) {
		AIautocastspell_timer = new Timer(1000);
		AIautocastspell_timer->Disable();
	} else {
		AIautocastspell_timer = new Timer(750);
		AIautocastspell_timer->Start(RandomTimer(0, 2000), false);
	}

	if (ourNPCData) {
		//AI_AddNPCSpells(ourNPCData->npc_spells_id);
		NPCSpecialAttacks(ourNPCData->npc_attacks,0);
	}

	SendTo(GetX(), GetY(), GetZ());
	SetChanged();
	SaveGuardSpot();
}

void Merc::AI_Stop() {
	NPC::AI_Stop();
	Mob::AI_Stop();
}

bool Merc::AI_EngagedCastCheck() {
	bool result = false;
	bool failedToCast = false;

	if (GetTarget() && AIautocastspell_timer->Check(false)) {
		_ZP(Merc_AI_Process_engaged_cast);

		AIautocastspell_timer->Disable();	//prevent the timer from going off AGAIN while we are casting.

		mlog(AI__SPELLS, "Engaged autocast check triggered (MERCS).");

		int8 mercClass = GetClass();

		switch(mercClass)
		{
			case TANK:
				if (!AICastSpell(GetChanceToCastBySpellType(SpellType_Nuke), SpellType_Nuke)) {
					if (!AICastSpell(GetChanceToCastBySpellType(SpellType_InCombatBuff), SpellType_InCombatBuff)) {
						failedToCast = true;
					}
				}
				break;
			case HEALER:
				if(!entity_list.Merc_AICheckCloseBeneficialSpells(this, GetChanceToCastBySpellType(SpellType_Heal), MercAISpellRange, SpellType_Heal)) {
					if(!entity_list.Merc_AICheckCloseBeneficialSpells(this, GetChanceToCastBySpellType(SpellType_Buff), MercAISpellRange, SpellType_Buff)) {
						failedToCast = true;
					}
				}
				break;
			case MELEEDPS:
				if (!AICastSpell(GetChanceToCastBySpellType(SpellType_Nuke), SpellType_Nuke)) {
					if (!AICastSpell(GetChanceToCastBySpellType(SpellType_InCombatBuff), SpellType_InCombatBuff)) {
						failedToCast = true;
					}
				}
				break;
			case CASTERDPS:
				failedToCast = true;
				break;
		}

		if(!AIautocastspell_timer->Enabled()) {
			AIautocastspell_timer->Start(RandomTimer(100, 250), false);
		}

		if(!failedToCast)
			result = true;
	}

	return result;
}

bool Merc::AI_IdleCastCheck() {
	bool result = false;
	bool failedToCast = false;

	if (AIautocastspell_timer->Check(false)) {
		_ZP(Merc_AI_IdleCastCheck);
#if MobAI_DEBUG_Spells >= 25
		cout << "Non-Engaged autocast check triggered: " << this->GetCleanName() << endl;
#endif
		AIautocastspell_timer->Disable();	//prevent the timer from going off AGAIN while we are casting.

		//Ok, IdleCastCheck depends of class.
		int8 mercClass = GetClass();

		switch(mercClass)
		{
			case TANK:
				failedToCast = true;
			break;
			case HEALER:
				if(!entity_list.Merc_AICheckCloseBeneficialSpells(this, 100, MercAISpellRange, SpellType_Heal)) {
					if(!entity_list.Merc_AICheckCloseBeneficialSpells(this, 100, MercAISpellRange, SpellType_Buff)) {
						failedToCast = true;
					}
				}
				result = true;
				break;
			case MELEEDPS:
				failedToCast = true;
				break;
			case CASTERDPS:
				failedToCast = true;
				break;
		}

		if(!AIautocastspell_timer->Enabled())
			AIautocastspell_timer->Start(RandomTimer(500, 1000), false);

		if(!failedToCast)
			result = true;
	}

	return result;
}

bool EntityList::Merc_AICheckCloseBeneficialSpells(Merc* caster, uint8 iChance, float iRange, uint16 iSpellTypes) {
	_ZP(EntityList_Merc_AICheckCloseBeneficialSpells);

	if((iSpellTypes&SpellTypes_Detrimental) != 0) {
		//according to live, you can buff and heal through walls...
		//now with PCs, this only applies if you can TARGET the target, but
		// according to Rogean, Live NPCs will just cast through walls/floors, no problem..
		//
		// This check was put in to address an idle-mob CPU issue
		_log(AI__ERROR, "Error: detrimental spells requested from AICheckCloseBeneficialSpells!!");
		return(false);
	}

	if(!caster)
		return false;

	if(!caster->AI_HasSpells())
		return false;

	if (iChance < 100) {
		int8 tmp = MakeRandomInt(1, 100);
		if (tmp > iChance)
			return false;
	}

	int8 mercCasterClass = caster->GetClass();

	if( iSpellTypes == SpellType_Heal )	{
		if( mercCasterClass == HEALER) {
			// check in group
			if(caster->HasGroup()) {
				if(caster->AICastSpell(100, SpellType_Heal))
					return true;
			}
		}
	}

	//Ok for the buffs..
	if( iSpellTypes == SpellType_Buff) {
		if(caster->HasGroup()) {
			if(caster->AICastSpell(100, SpellType_Buff))
				return true;
		}
	}

	return false;
}

bool Merc::AIDoSpellCast(uint16 spellid, Mob* tar, int32 mana_cost, uint32* oDontDoAgainBefore) {
	bool result = false;
	MercSpell mercSpell = GetMercSpellBySpellID(this, spellid);

	// manacost has special values, -1 is no mana cost, -2 is instant cast (no mana)
	int32 manaCost = mana_cost;

	if (manaCost == -1)
		manaCost = spells[spellid].mana;
	else if (manaCost == -2)
		manaCost = 0;

	int32 extraMana = 0;
	int32 hasMana = GetMana();

	float dist2 = 0;

	if (mercSpell.type & SpellType_Escape) {
		dist2 = 0;
	} else
		dist2 = DistNoRoot(*tar);

	if (((((spells[spellid].targettype==ST_GroupTeleport && mercSpell.type==SpellType_Heal)
				|| spells[spellid].targettype==ST_AECaster
				|| spells[spellid].targettype==ST_Group
				|| spells[spellid].targettype==ST_AEBard)
				&& dist2 <= spells[spellid].aoerange*spells[spellid].aoerange)
				|| dist2 <= GetActSpellRange(spellid, spells[spellid].range)*GetActSpellRange(spellid, spells[spellid].range)) && (mana_cost <= GetMana() || GetMana() == GetMaxMana()))
	{
		SetRunAnimSpeed(0);
		SendPosition();
		SetMoving(false);

		result = CastSpell(spellid, tar->GetID(), 1, -1, mana_cost, oDontDoAgainBefore, -1, -1, 0, 0);

		if(IsCasting() && IsSitting())
			Stand();
	}

	// if the spell wasn't casted, then take back any extra mana that was given to the bot to cast that spell
	if(!result) {
		SetMana(hasMana);
		extraMana = false;
	}
	else {  //handle spell recast and recast timers
		mercSpell.time_cancast = Timer::GetCurrentTime() + spells[spellid].recast_time;

		if(spells[spellid].EndurTimerIndex > 0) {
			//SetSpellRecastTimer(spells[spellid].EndurTimerIndex, spells[spellid].recast_time);
		}
	}

	return result;
}

bool Merc::AICastSpell(int8 iChance, int16 iSpellTypes) {
	_ZP(Bot_AICastSpell);

	if(!AI_HasSpells())
		return false;

	if (iChance < 100) {
		if (MakeRandomInt(0, 100) > iChance){
			return false;
		}
	}

	int8 mercClass = GetClass();
	uint8 mercLevel = GetLevel();

	bool checked_los = false;	//we do not check LOS until we are absolutely sure we need to, and we only do it once.

	bool castedSpell = false;

	if(HasGroup()) {
		Group *g = GetGroup();

		if(g) {
			MercSpell selectedMercSpell;
			selectedMercSpell.spellid = 0;
			selectedMercSpell.stance = 0;
			selectedMercSpell.type = 0;
			selectedMercSpell.slot = 0;
			selectedMercSpell.proc_chance = 0;
			selectedMercSpell.time_cancast = 0;

			switch (iSpellTypes) {
				case SpellType_Heal: {
					Mob* tar = NULL;
					int8 numToHeal = g->GetNumberNeedingHealedInGroup(IsEngaged() ? 75 : 95, true);
					int8 checkHPR = IsEngaged() ? 95 : 99;

					//todo: check stance to determine healing spell selection

					for(int i = 0; i < MAX_GROUP_MEMBERS; i++) {
						if(g->members[i] && !g->members[i]->qglobal) {
							int8 hpr = (int8)g->members[i]->GetHPRatio();

							if(hpr > checkHPR) {
								//they don't need to be healed
								continue;
							}

							if(IsEngaged() && (g->members[i]->GetClass() == NECROMANCER && hpr >= 50)
								|| (g->members[i]->GetClass() == SHAMAN && hpr >= 80)) {
								//allow necros to lifetap & shaman to canni without wasting mana
								continue;
							}

							if(g->members[i] == GetMercOwner()) {
								if(!tar || hpr < tar->GetHPRatio())
									tar = g->members[i];		//check owner first
							}
							else if(g->HasRole(g->members[i], RoleTank) && g->members[i]->GetHPRatio() < checkHPR){
								if(!tar || hpr < tar->GetHPRatio())
									tar = g->members[i];
							}
							else if(!tar || hpr < tar->GetHPRatio()) {
								tar = g->members[i];
							}

							if(g->members[i]->HasPet() && g->members[i]->GetPet()->GetHPRatio() < 50) {
								if(!tar || ((g->members[i]->GetPet()->GetHPRatio() + 25) < tar->GetHPRatio())) {
									tar = g->members[i]->GetPet();
								}
							}
						}
					}

					if(numToHeal > 2) {
						selectedMercSpell = GetBestMercSpellForGroupHeal(this);

						if(selectedMercSpell.spellid == 0) {
							selectedMercSpell = GetBestMercSpellForRegularSingleTargetHeal(this);
						}
					}

					if(tar && selectedMercSpell.spellid == 0) {
						if(tar->GetHPRatio() < 15) {
							//check for very fast heals first (casting time < 1 s)
							selectedMercSpell = GetBestMercSpellForVeryFastHeal(this);

							//check for fast heals next (casting time < 2 s)
							if(selectedMercSpell.spellid == 0) {
								selectedMercSpell = GetBestMercSpellForFastHeal(this);
							}

							//get regular heal
							if(selectedMercSpell.spellid == 0) {
								selectedMercSpell = GetBestMercSpellForRegularSingleTargetHeal(this);
							}
						}
						else if (tar->GetHPRatio() < 35) {
							//check for fast heals next (casting time < 2 s)
							selectedMercSpell = GetBestMercSpellForFastHeal(this);

							//get regular heal
							if(selectedMercSpell.spellid == 0) {
								selectedMercSpell = GetBestMercSpellForRegularSingleTargetHeal(this);
							}
						}
						else if (tar->GetHPRatio() < 75) {
							selectedMercSpell = GetBestMercSpellForPercentageHeal(this);

							//get regular heal
							if(selectedMercSpell.spellid == 0) {
								selectedMercSpell = GetBestMercSpellForRegularSingleTargetHeal(this);
							}
						}
						else {
							//check for heal over time. if not present, try it first
							if(!tar->FindType(SE_HealOverTime)) {
								selectedMercSpell = GetBestMercSpellForRegularSingleTargetHeal(this);
							}

							//get regular heal
							if(selectedMercSpell.spellid == 0) {
								selectedMercSpell = GetBestMercSpellForRegularSingleTargetHeal(this);
							}
						}

						if(selectedMercSpell.spellid == 0) {
							selectedMercSpell = GetFirstMercSpellForSingleTargetHeal(this);
						}
					}

					if(selectedMercSpell.spellid > 0) {
						if(AIDoSpellCast(selectedMercSpell.spellid, tar, -1))
							castedSpell =  true;
					}

					if(castedSpell) {
						char* gmsg = 0;

						if(tar != this)	{
							//we don't need spam of bots healing themselves
							MakeAnyLenString(&gmsg, "Casting %s on %s.", spells[selectedMercSpell.spellid].name, tar->GetCleanName());
							if(gmsg)
								MercGroupSay(this, gmsg);
						}
					}

					break;
				}
				case SpellType_Root: {
					break;
				}
				case SpellType_Buff: {

					if(GetManaRatio() < 50) {
						return false;			//mercs buff when Mana > 50%
					}

					std::list<MercSpell> buffSpellList = GetMercSpellsBySpellType(this, SpellType_Buff);

					for(std::list<MercSpell>::iterator itr = buffSpellList.begin(); itr != buffSpellList.end(); itr++) {
						MercSpell selectedMercSpell = *itr;

						if(!((spells[selectedMercSpell.spellid].targettype == ST_Target || spells[selectedMercSpell.spellid].targettype == ST_Pet ||
							spells[selectedMercSpell.spellid].targettype == ST_Group || spells[selectedMercSpell.spellid].targettype == ST_GroupTeleport ))) {
								continue;
						}

						for( int i = 0; i < MAX_GROUP_MEMBERS; i++) {
							if(g->members[i]) {
								int32 oDontDoAgainBefore;
								Mob* tar = g->members[i];

								if( !tar->IsImmuneToSpell(selectedMercSpell.spellid, this)
									&& (tar->CanBuffStack(selectedMercSpell.spellid, mercLevel, true) >= 0)) {

									if( tar->GetArchetype() == ARCHETYPE_MELEE && IsEffectInSpell(selectedMercSpell.spellid, SE_IncreaseSpellHaste)) {
										continue;
									}

									int32 TempDontBuffMeBeforeTime = tar->DontBuffMeBefore();

									if(AIDoSpellCast(selectedMercSpell.spellid, tar, -1))
										castedSpell =  true;
								}

								if(!castedSpell && tar->GetPet()) {

									if(!tar->GetPet()->IsImmuneToSpell(selectedMercSpell.spellid, this)
										&& (tar->GetPet()->CanBuffStack(selectedMercSpell.spellid, mercLevel, true) >= 0)) {

										int32 TempDontBuffMeBeforeTime = tar->DontBuffMeBefore();

										if(AIDoSpellCast(selectedMercSpell.spellid, tar->GetPet(), -1))
											castedSpell =  true;
									}
								}
							}
						}
					}
					break;
				}
				case SpellType_Nuke: {
					bool isDiscipline = false;
					switch(mercClass)
					{
						case TANK:
							//check for taunt
							if(CheckAETaunt()) {
								if(MERC_DEBUG > 0)
									GetOwner()->Message(7, "AE Taunting");
								//get AE taunt
								selectedMercSpell = GetBestMercSpellForAETaunt(this);
							}

							if(selectedMercSpell.spellid == 0 && CheckTaunt()) {
								//get taunt
								selectedMercSpell = GetBestMercSpellForTaunt(this);
							}

							//get hate disc
							if(selectedMercSpell.spellid == 0) {
								selectedMercSpell = GetBestMercSpellForHate(this);
							}

							isDiscipline = true;
						break;
						case HEALER:

						break;
						case MELEEDPS:
							isDiscipline = true;
						break;
						case CASTERDPS:

							break;
					}

					if(selectedMercSpell.spellid > 0) {
						if(isDiscipline) {
							if(UseDiscipline(selectedMercSpell.spellid, GetTarget()->GetID())) {
								castedSpell =  true;
							}
						}
						else {
							if(AIDoSpellCast(selectedMercSpell.spellid, GetTarget(), -1)) {
								castedSpell =  true;
							}
						}
					}

					break;
				}
				case SpellType_InCombatBuff: {
					break;
				}
			}
		}
	}

	return castedSpell;
}

int8 Merc::GetChanceToCastBySpellType(int16 spellType) {
	int mercStance = (int)GetStance();
	int8 mercClass = GetClass();
	int8 chance = 0;

	switch (spellType) {
		case SpellType_Nuke: {
			switch(mercClass)
            {
                case TANK: {
                    chance = 100;
                    break;
                }
                case HEALER:{
                    break;
                }
                case MELEEDPS:{
                    break;
                }
                case CASTERDPS:{
                    chance = 100;
                    break;
                }
            }
			break;
		}
		case SpellType_Heal: {
			switch(mercClass)
            {
                case TANK: {
                    break;
                }
                case HEALER:{
                    chance = 100;
                    break;
                }
                case MELEEDPS:{
                    break;
                }
                case CASTERDPS:{
                    break;
                }
            }
			break;
		}
		case SpellType_Root: {
			switch(mercClass)
            {
                case TANK: {
                    break;
                }
                case HEALER:{
                    break;
                }
                case MELEEDPS:{
                    break;
                }
                case CASTERDPS:{
                    break;
                }
            }
			break;
		}
		case SpellType_Buff: {
			switch(mercClass)
            {
                case TANK: {
                    break;
                }
                case HEALER:{
                    chance = IsEngaged() ? 0 : 100;
                    break;
                }
                case MELEEDPS:{
                    break;
                }
                case CASTERDPS:{
                    break;
                }
            }
			break;
		}
		case SpellType_InCombatBuff: {
			switch(mercClass)
            {
                case TANK: {
                    chance = 50;
                    break;
                }
                case HEALER:{
                    break;
                }
                case MELEEDPS:{
                    break;
                }
                case CASTERDPS:{
                    break;
                }
            }
			break;
		}
		default:
			chance = 0;
			break;
	}

	return chance;
}

bool Merc::CheckStance(int16 stance) {

	if(stance == 0
		|| (stance > 0 && stance == GetStance())
		|| (stance < 0 && abs(stance) != GetStance())) {
		return true;
	}

	return false;
}

std::list<MercSpell> Merc::GetMercSpellsBySpellType(Merc* caster, int spellType) {
	std::list<MercSpell> result;

	if(caster && caster->AI_HasSpells()) {
		std::vector<MercSpell> mercSpellList = caster->GetMercSpells();

		for (int i = mercSpellList.size() - 1; i >= 0; i--) {
			if (mercSpellList[i].spellid <= 0 || mercSpellList[i].spellid >= SPDAT_RECORDS) {
				// this is both to quit early to save cpu and to avoid casting bad spells
				// Bad info from database can trigger this incorrectly, but that should be fixed in DB, not here
				continue;
			}

			if((mercSpellList[i].type & spellType) && caster->CheckStance(mercSpellList[i].stance)) {
				MercSpell mercSpell;
				mercSpell.spellid = mercSpellList[i].spellid;
				mercSpell.stance = mercSpellList[i].stance;
				mercSpell.type = mercSpellList[i].type;
				mercSpell.slot = mercSpellList[i].slot;
				mercSpell.proc_chance = mercSpellList[i].proc_chance;
				mercSpell.time_cancast = mercSpellList[i].time_cancast;

				result.push_back(mercSpell);
			}
		}
	}

	return result;
}

MercSpell Merc::GetFirstMercSpellBySpellType(Merc* caster, int spellType) {
	MercSpell result;

	result.spellid = 0;
	result.stance = 0;
	result.type = 0;
	result.slot = 0;
	result.proc_chance = 0;
	result.time_cancast = 0;

	if(caster && caster->AI_HasSpells()) {
		std::vector<MercSpell> mercSpellList = caster->GetMercSpells();

		for (int i = mercSpellList.size() - 1; i >= 0; i--) {
			if (mercSpellList[i].spellid <= 0 || mercSpellList[i].spellid >= SPDAT_RECORDS) {
				// this is both to quit early to save cpu and to avoid casting bad spells
				// Bad info from database can trigger this incorrectly, but that should be fixed in DB, not here
				continue;
			}

			if((mercSpellList[i].type & spellType)
				&& caster->CheckStance(mercSpellList[i].stance)
				&& CheckSpellRecastTimers(caster, mercSpellList[i].spellid)) {
				result.spellid = mercSpellList[i].spellid;
				result.stance = mercSpellList[i].stance;
				result.type = mercSpellList[i].type;
				result.slot = mercSpellList[i].slot;
				result.proc_chance = mercSpellList[i].proc_chance;
				result.time_cancast = mercSpellList[i].time_cancast;

				break;
			}
		}
	}

	return result;
}

MercSpell Merc::GetMercSpellBySpellID(Merc* caster, uint16 spellid) {
	MercSpell result;

	result.spellid = 0;
	result.stance = 0;
	result.type = 0;
	result.slot = 0;
	result.proc_chance = 0;
	result.time_cancast = 0;

	if(caster && caster->AI_HasSpells()) {
		std::vector<MercSpell> mercSpellList = caster->GetMercSpells();

		for (int i = mercSpellList.size() - 1; i >= 0; i--) {
			if (mercSpellList[i].spellid <= 0 || mercSpellList[i].spellid >= SPDAT_RECORDS) {
				// this is both to quit early to save cpu and to avoid casting bad spells
				// Bad info from database can trigger this incorrectly, but that should be fixed in DB, not here
				continue;
			}

			if((mercSpellList[i].spellid = spellid)
				&& caster->CheckStance(mercSpellList[i].stance)) {
				result.spellid = mercSpellList[i].spellid;
				result.stance = mercSpellList[i].stance;
				result.type = mercSpellList[i].type;
				result.slot = mercSpellList[i].slot;
				result.proc_chance = mercSpellList[i].proc_chance;
				result.time_cancast = mercSpellList[i].time_cancast;

				break;
			}
		}
	}

	return result;
}

std::list<MercSpell> Merc::GetMercSpellsForSpellEffect(Merc* caster, int spellEffect) {
	std::list<MercSpell> result;

	if(caster && caster->AI_HasSpells()) {
		std::vector<MercSpell> mercSpellList = caster->GetMercSpells();

		for (int i = mercSpellList.size() - 1; i >= 0; i--) {
			if (mercSpellList[i].spellid <= 0 || mercSpellList[i].spellid >= SPDAT_RECORDS) {
				// this is both to quit early to save cpu and to avoid casting bad spells
				// Bad info from database can trigger this incorrectly, but that should be fixed in DB, not here
				continue;
			}

			if(IsEffectInSpell(mercSpellList[i].spellid, spellEffect)) {
				MercSpell MercSpell;
				MercSpell.spellid = mercSpellList[i].spellid;
				MercSpell.stance = mercSpellList[i].stance;
				MercSpell.type = mercSpellList[i].type;
				MercSpell.slot = mercSpellList[i].slot;
				MercSpell.proc_chance = mercSpellList[i].proc_chance;
				MercSpell.time_cancast = mercSpellList[i].time_cancast;

				result.push_back(MercSpell);
			}
		}
	}

	return result;
}

std::list<MercSpell> Merc::GetMercSpellsForSpellEffectAndTargetType(Merc* caster, int spellEffect, SpellTargetType targetType) {
	std::list<MercSpell> result;

	if(caster && caster->AI_HasSpells()) {
		std::vector<MercSpell> mercSpellList = caster->GetMercSpells();

		for (int i = mercSpellList.size() - 1; i >= 0; i--) {
			if (mercSpellList[i].spellid <= 0 || mercSpellList[i].spellid >= SPDAT_RECORDS) {
				// this is both to quit early to save cpu and to avoid casting bad spells
				// Bad info from database can trigger this incorrectly, but that should be fixed in DB, not here
				continue;
			}

			if(IsEffectInSpell(mercSpellList[i].spellid, spellEffect)) {
				if(spells[mercSpellList[i].spellid].targettype == targetType) {
					MercSpell MercSpell;
					MercSpell.spellid = mercSpellList[i].spellid;
					MercSpell.stance = mercSpellList[i].stance;
					MercSpell.type = mercSpellList[i].type;
					MercSpell.slot = mercSpellList[i].slot;
					MercSpell.proc_chance = mercSpellList[i].proc_chance;
					MercSpell.time_cancast = mercSpellList[i].time_cancast;

					result.push_back(MercSpell);
				}
			}
		}
	}

	return result;
}

MercSpell Merc::GetBestMercSpellForVeryFastHeal(Merc* caster) {
	MercSpell result;

	result.spellid = 0;
	result.stance = 0;
	result.type = 0;
	result.slot = 0;
	result.proc_chance = 0;
	result.time_cancast = 0;

	if(caster) {
		std::list<MercSpell> mercSpellList = GetMercSpellsForSpellEffect(caster, SE_CurrentHP);

		for(std::list<MercSpell>::iterator mercSpellListItr = mercSpellList.begin(); mercSpellListItr != mercSpellList.end(); mercSpellListItr++) {
			// Assuming all the spells have been loaded into this list by level and in descending order
			if(IsVeryFastHealSpell(mercSpellListItr->spellid)
				&& CheckSpellRecastTimers(caster, mercSpellListItr->spellid)) {
				result.spellid = mercSpellListItr->spellid;
				result.stance = mercSpellListItr->stance;
				result.type = mercSpellListItr->type;
				result.slot = mercSpellListItr->slot;
				result.proc_chance = mercSpellListItr->proc_chance;
				result.time_cancast = mercSpellListItr->time_cancast;

				break;
			}
		}
	}

	return result;
}

MercSpell Merc::GetBestMercSpellForFastHeal(Merc* caster) {
	MercSpell result;

	result.spellid = 0;
	result.stance = 0;
	result.type = 0;
	result.slot = 0;
	result.proc_chance = 0;
	result.time_cancast = 0;

	if(caster) {
		std::list<MercSpell> mercSpellList = GetMercSpellsForSpellEffect(caster, SE_CurrentHP);

		for(std::list<MercSpell>::iterator mercSpellListItr = mercSpellList.begin(); mercSpellListItr != mercSpellList.end(); mercSpellListItr++) {
			// Assuming all the spells have been loaded into this list by level and in descending order
			if(IsFastHealSpell(mercSpellListItr->spellid)
				&& CheckSpellRecastTimers(caster, mercSpellListItr->spellid)) {
				result.spellid = mercSpellListItr->spellid;
				result.stance = mercSpellListItr->stance;
				result.type = mercSpellListItr->type;
				result.slot = mercSpellListItr->slot;
				result.proc_chance = mercSpellListItr->proc_chance;
				result.time_cancast = mercSpellListItr->time_cancast;

				break;
			}
		}
	}

	return result;
}

MercSpell Merc::GetBestMercSpellForHealOverTime(Merc* caster) {
	MercSpell result;

	result.spellid = 0;
	result.stance = 0;
	result.type = 0;
	result.slot = 0;
	result.proc_chance = 0;
	result.time_cancast = 0;

	if(caster) {
		std::list<MercSpell> botHoTSpellList = GetMercSpellsForSpellEffect(caster, SE_HealOverTime);
		std::vector<MercSpell> mercSpellList = caster->GetMercSpells();

		for(std::list<MercSpell>::iterator mercSpellListItr = botHoTSpellList.begin(); mercSpellListItr != botHoTSpellList.end(); mercSpellListItr++) {
			// Assuming all the spells have been loaded into this list by level and in descending order
			if(IsHealOverTimeSpell(mercSpellListItr->spellid)) {

				for (int i = mercSpellList.size() - 1; i >= 0; i--) {
					if (mercSpellList[i].spellid <= 0 || mercSpellList[i].spellid >= SPDAT_RECORDS) {
						// this is both to quit early to save cpu and to avoid casting bad spells
						// Bad info from database can trigger this incorrectly, but that should be fixed in DB, not here
						continue;
					}

					if(mercSpellList[i].spellid == mercSpellListItr->spellid
						&& (mercSpellList[i].type & SpellType_Heal)
						&& CheckSpellRecastTimers(caster, mercSpellListItr->spellid)) {
						result.spellid = mercSpellList[i].spellid;
						result.stance = mercSpellList[i].stance;
						result.type = mercSpellList[i].type;
						result.slot = mercSpellList[i].slot;
						result.proc_chance = mercSpellList[i].proc_chance;
						result.time_cancast = mercSpellList[i].time_cancast;
					}
				}

				break;
			}
		}
	}

	return result;
}

MercSpell Merc::GetBestMercSpellForPercentageHeal(Merc* caster) {
	MercSpell result;

	result.spellid = 0;
	result.stance = 0;
	result.type = 0;
	result.slot = 0;
	result.proc_chance = 0;
	result.time_cancast = 0;

	if(caster && caster->AI_HasSpells()) {
		std::vector<MercSpell> mercSpellList = caster->GetMercSpells();

		for (int i = mercSpellList.size() - 1; i >= 0; i--) {
			if (mercSpellList[i].spellid <= 0 || mercSpellList[i].spellid >= SPDAT_RECORDS) {
				// this is both to quit early to save cpu and to avoid casting bad spells
				// Bad info from database can trigger this incorrectly, but that should be fixed in DB, not here
				continue;
			}

			if(IsCompleteHealSpell(mercSpellList[i].spellid)
				&& CheckSpellRecastTimers(caster, mercSpellList[i].spellid)) {
				result.spellid = mercSpellList[i].spellid;
				result.stance = mercSpellList[i].stance;
				result.type = mercSpellList[i].type;
				result.slot = mercSpellList[i].slot;
				result.proc_chance = mercSpellList[i].proc_chance;
				result.time_cancast = mercSpellList[i].time_cancast;

				break;
			}
		}
	}

	return result;
}

MercSpell Merc::GetBestMercSpellForRegularSingleTargetHeal(Merc* caster) {
	MercSpell result;

	result.spellid = 0;
	result.stance = 0;
	result.type = 0;
	result.slot = 0;
	result.proc_chance = 0;
	result.time_cancast = 0;

	if(caster) {
		std::list<MercSpell> mercSpellList = GetMercSpellsForSpellEffect(caster, SE_CurrentHP);

		for(std::list<MercSpell>::iterator mercSpellListItr = mercSpellList.begin(); mercSpellListItr != mercSpellList.end(); mercSpellListItr++) {
			// Assuming all the spells have been loaded into this list by level and in descending order
			if(IsRegularSingleTargetHealSpell(mercSpellListItr->spellid)
				&& CheckSpellRecastTimers(caster, mercSpellListItr->spellid)) {
				result.spellid = mercSpellListItr->spellid;
				result.stance = mercSpellListItr->stance;
				result.type = mercSpellListItr->type;
				result.slot = mercSpellListItr->slot;
				result.proc_chance = mercSpellListItr->proc_chance;
				result.time_cancast = mercSpellListItr->time_cancast;

				break;
			}
		}
	}

	return result;
}

MercSpell Merc::GetFirstMercSpellForSingleTargetHeal(Merc* caster) {
	MercSpell result;

	result.spellid = 0;
	result.stance = 0;
	result.type = 0;
	result.slot = 0;
	result.proc_chance = 0;
	result.time_cancast = 0;

	if(caster) {
		std::list<MercSpell> mercSpellList = GetMercSpellsForSpellEffect(caster, SE_CurrentHP);

		for(std::list<MercSpell>::iterator mercSpellListItr = mercSpellList.begin(); mercSpellListItr != mercSpellList.end(); mercSpellListItr++) {
			// Assuming all the spells have been loaded into this list by level and in descending order
			if((IsRegularSingleTargetHealSpell(mercSpellListItr->spellid)
				|| IsFastHealSpell(mercSpellListItr->spellid))
				&& CheckSpellRecastTimers(caster, mercSpellListItr->spellid)) {
				result.spellid = mercSpellListItr->spellid;
				result.stance = mercSpellListItr->stance;
				result.type = mercSpellListItr->type;
				result.slot = mercSpellListItr->slot;
				result.proc_chance = mercSpellListItr->proc_chance;
				result.time_cancast = mercSpellListItr->time_cancast;

				break;
			}
		}
	}

	return result;
}

MercSpell Merc::GetBestMercSpellForGroupHeal(Merc* caster) {
    MercSpell result;

    result.spellid = 0;
	result.stance = 0;
	result.type = 0;
	result.slot = 0;
	result.proc_chance = 0;
	result.time_cancast = 0;

    if(caster) {
            std::list<MercSpell> mercSpellList = GetMercSpellsForSpellEffect(caster, SE_CurrentHP);

			for(std::list<MercSpell>::iterator mercSpellListItr = mercSpellList.begin(); mercSpellListItr != mercSpellList.end(); mercSpellListItr++) {
				// Assuming all the spells have been loaded into this list by level and in descending order
				if(IsRegularGroupHealSpell(mercSpellListItr->spellid)
					&& CheckSpellRecastTimers(caster, mercSpellListItr->spellid)) {
					result.spellid = mercSpellListItr->spellid;
					result.stance = mercSpellListItr->stance;
					result.type = mercSpellListItr->type;
					result.slot = mercSpellListItr->slot;
					result.proc_chance = mercSpellListItr->proc_chance;
					result.time_cancast = mercSpellListItr->time_cancast;

					break;
				}
			}
    }

    return result;
}

MercSpell Merc::GetBestMercSpellForGroupHealOverTime(Merc* caster) {
    MercSpell result;

    result.spellid = 0;
	result.stance = 0;
	result.type = 0;
	result.slot = 0;
	result.proc_chance = 0;
	result.time_cancast = 0;

    if(caster) {
			std::list<MercSpell> botHoTSpellList = GetMercSpellsForSpellEffect(caster, SE_HealOverTime);
			std::vector<MercSpell> mercSpellList = caster->GetMercSpells();

			for(std::list<MercSpell>::iterator mercSpellListItr = botHoTSpellList.begin(); mercSpellListItr != botHoTSpellList.end(); mercSpellListItr++) {
				// Assuming all the spells have been loaded into this list by level and in descending order
				if(IsGroupHealOverTimeSpell(mercSpellListItr->spellid)) {

					for (int i = mercSpellList.size() - 1; i >= 0; i--) {
						if (mercSpellList[i].spellid <= 0 || mercSpellList[i].spellid >= SPDAT_RECORDS) {
							// this is both to quit early to save cpu and to avoid casting bad spells
							// Bad info from database can trigger this incorrectly, but that should be fixed in DB, not here
							continue;
						}

						if(mercSpellList[i].spellid == mercSpellListItr->spellid
							&& (mercSpellList[i].type & SpellType_Heal)
							&& CheckSpellRecastTimers(caster, mercSpellListItr->spellid)) {
							result.spellid = mercSpellList[i].spellid;
							result.stance = mercSpellList[i].stance;
							result.type = mercSpellList[i].type;
							result.slot = mercSpellList[i].slot;
							result.proc_chance = mercSpellList[i].proc_chance;
							result.time_cancast = mercSpellList[i].time_cancast;
						}
					}

					break;
				}
			}
    }

    return result;
}

MercSpell Merc::GetBestMercSpellForGroupCompleteHeal(Merc* caster) {
    MercSpell result;

    result.spellid = 0;
	result.stance = 0;
	result.type = 0;
	result.slot = 0;
	result.proc_chance = 0;
	result.time_cancast = 0;

    if(caster) {
            std::list<MercSpell> mercSpellList = GetMercSpellsForSpellEffect(caster, SE_CompleteHeal);

			for(std::list<MercSpell>::iterator mercSpellListItr = mercSpellList.begin(); mercSpellListItr != mercSpellList.end(); mercSpellListItr++) {
				// Assuming all the spells have been loaded into this list by level and in descending order
				if(IsGroupCompleteHealSpell(mercSpellListItr->spellid)
					&& CheckSpellRecastTimers(caster, mercSpellListItr->spellid)) {
					result.spellid = mercSpellListItr->spellid;
					result.stance = mercSpellListItr->stance;
					result.type = mercSpellListItr->type;
					result.slot = mercSpellListItr->slot;
					result.proc_chance = mercSpellListItr->proc_chance;
					result.time_cancast = mercSpellListItr->time_cancast;

					break;
				}
			}
    }

	return result;
}

MercSpell Merc::GetBestMercSpellForAETaunt(Merc* caster) {
	MercSpell result;

	result.spellid = 0;
	result.stance = 0;
	result.type = 0;
	result.slot = 0;
	result.proc_chance = 0;
	result.time_cancast = 0;

	if(caster) {
		std::list<MercSpell> mercSpellList = GetMercSpellsForSpellEffect(caster, SE_Taunt);

		for(std::list<MercSpell>::iterator mercSpellListItr = mercSpellList.begin(); mercSpellListItr != mercSpellList.end(); mercSpellListItr++) {
			// Assuming all the spells have been loaded into this list by level and in descending order
			if((spells[mercSpellListItr->spellid].targettype == ST_AECaster
				|| spells[mercSpellListItr->spellid].targettype == ST_AETarget
				|| spells[mercSpellListItr->spellid].targettype == ST_UndeadAE)
				&& CheckSpellRecastTimers(caster, mercSpellListItr->spellid)) {
				result.spellid = mercSpellListItr->spellid;
				result.stance = mercSpellListItr->stance;
				result.type = mercSpellListItr->type;
				result.slot = mercSpellListItr->slot;
				result.proc_chance = mercSpellListItr->proc_chance;
				result.time_cancast = mercSpellListItr->time_cancast;

				break;
			}
		}
	}

	return result;
}

MercSpell Merc::GetBestMercSpellForTaunt(Merc* caster) {
	MercSpell result;

	result.spellid = 0;
	result.stance = 0;
	result.type = 0;
	result.slot = 0;
	result.proc_chance = 0;
	result.time_cancast = 0;

	if(caster) {
		std::list<MercSpell> mercSpellList = GetMercSpellsForSpellEffect(caster, SE_Taunt);

		for(std::list<MercSpell>::iterator mercSpellListItr = mercSpellList.begin(); mercSpellListItr != mercSpellList.end(); mercSpellListItr++) {
			// Assuming all the spells have been loaded into this list by level and in descending order
			if((spells[mercSpellListItr->spellid].targettype == ST_Target)
				&& CheckSpellRecastTimers(caster, mercSpellListItr->spellid)) {
				result.spellid = mercSpellListItr->spellid;
				result.stance = mercSpellListItr->stance;
				result.type = mercSpellListItr->type;
				result.slot = mercSpellListItr->slot;
				result.proc_chance = mercSpellListItr->proc_chance;
				result.time_cancast = mercSpellListItr->time_cancast;

				break;
			}
		}
	}

	return result;
}

MercSpell Merc::GetBestMercSpellForHate(Merc* caster) {
	MercSpell result;

	result.spellid = 0;
	result.stance = 0;
	result.type = 0;
	result.slot = 0;
	result.proc_chance = 0;
	result.time_cancast = 0;

	if(caster) {
		std::list<MercSpell> mercSpellList = GetMercSpellsForSpellEffect(caster, SE_Calm);

		for(std::list<MercSpell>::iterator mercSpellListItr = mercSpellList.begin(); mercSpellListItr != mercSpellList.end(); mercSpellListItr++) {
			// Assuming all the spells have been loaded into this list by level and in descending order
			if(CheckSpellRecastTimers(caster, mercSpellListItr->spellid)) {
				result.spellid = mercSpellListItr->spellid;
				result.stance = mercSpellListItr->stance;
				result.type = mercSpellListItr->type;
				result.slot = mercSpellListItr->slot;
				result.proc_chance = mercSpellListItr->proc_chance;
				result.time_cancast = mercSpellListItr->time_cancast;

				break;
			}
		}
	}

	return result;
}

void Merc::MercGroupSay(Mob *speaker, const char *msg, ...)
{

	char buf[1000];
	va_list ap;

	va_start(ap, msg);
	vsnprintf(buf, 1000, msg, ap);
	va_end(ap);

	if(speaker->HasGroup()) {
		Group *g = speaker->GetGroup();

		if(g)
			g->GroupMessage(speaker->CastToMob(), 0, 100, buf);
	}
}

bool Merc::UseDiscipline(int32 spell_id, int32 target) {
	// Dont let client waste a reuse timer if they can't use the disc
	if (IsStunned() || IsFeared() || IsMezzed() || IsAmnesiad())
	{
		return(false);
	}

	//make sure we can use it..
	if(!IsValidSpell(spell_id)) {
		return(false);
	}

	//can we use the spell?
	const SPDat_Spell_Struct &spell = spells[spell_id];
	int8 level_to_use = spell.classes[GetClass() - 1];
	if(level_to_use == 255) {
		return(false);
	}

	if(level_to_use > GetLevel()) {
		return(false);
	}

	if(GetEndurance() > spell.EndurCost) {
		SetEndurance(GetEndurance() - spell.EndurCost);
	} else {
		//too fatigued to use this skill right now.
		return(false);
	}

	if(spell.recast_time > 0)
	{
		if(CheckDisciplineRecastTimers(this, spells[spell_id].EndurTimerIndex)) {
			if(spells[spell_id].EndurTimerIndex > 0 && spells[spell_id].EndurTimerIndex < MAX_DISCIPLINE_TIMERS) {
				SetDisciplineRecastTimer(spells[spell_id].EndurTimerIndex, spell_id, spell.recast_time);
			}
		}
		else {
			return(false);
		}
	}

	if(IsCasting())
		InterruptSpell();

	CastSpell(spell_id, target, DISCIPLINE_SPELL_SLOT);

	return(true);
}

void Merc::SetSpellRecastTimer(uint16 timer_id, uint16 spellid, uint32 recast_delay) {
	if(timer_id > 0) {
		MercTimer timer;
		timer.timerid = timer_id;
		timer.timertype = 1;
		timer.spellid = spellid;
		timer.time_cancast = Timer::GetCurrentTime() + recast_delay;
		timers[timer_id] = timer;
	}
}

int32 Merc::GetSpellRecastTimer(Merc *caster, uint16 timer_id) {
	int32 result = 0;
	if(caster && timer_id > 0) {
		if(caster->timers.find(timer_id) != caster->timers.end()) {
			result = caster->timers[timer_id].time_cancast;
		}
	}
	return result;
}

bool Merc::CheckSpellRecastTimers(Merc *caster, uint16 spell_id) {
	if(caster) {
	    MercSpell mercSpell = GetMercSpellBySpellID(caster, spell_id);
		if(mercSpell.spellid > 0 && mercSpell.time_cancast < Timer::GetCurrentTime()) {  //checks spell recast
			if(GetSpellRecastTimer(caster, spells[spell_id].EndurTimerIndex) < Timer::GetCurrentTime()) {   //checks for spells on the same timer
				return true;    //can cast spell
			}
		}
	}
	return false;
}

void Merc::SetDisciplineRecastTimer(uint16 timer_id, uint16 spellid, uint32 recast_delay) {
	if(timer_id > 0) {
		MercTimer timer;
		timer.timerid = timer_id;
		timer.timertype = 2;
		timer.spellid = spellid;
		timer.time_cancast = Timer::GetCurrentTime() + recast_delay;
		timers[timer_id] = timer;
	}
}

int32 Merc::GetDisciplineRecastTimer(Merc *caster, uint16 timer_id) {
	int32 result = 0;
	if(caster && timer_id > 0) {
		if(caster->timers.find(timer_id) != caster->timers.end()) {
			result = caster->timers[timer_id].time_cancast;
		}
	}
	return result;
}

int32 Merc::GetDisciplineRemainingTime(Merc *caster, uint16 timer_id) {
	int32 result = 0;
	if(caster && timer_id > 0) {
	    int32 time_cancast = GetDisciplineRecastTimer(caster, timer_id);
		if(time_cancast > Timer::GetCurrentTime())
			result = time_cancast - Timer::GetCurrentTime();
	}
	return result;
}

bool Merc::CheckDisciplineRecastTimers(Merc *caster, uint16 spell_id) {
	if(caster) {
		MercSpell mercSpell = GetMercSpellBySpellID(caster, spell_id);
		if(mercSpell.spellid > 0 && mercSpell.time_cancast < Timer::GetCurrentTime()) {  //checks spell recast
			if(GetDisciplineRecastTimer(caster, spells[spell_id].EndurTimerIndex) < Timer::GetCurrentTime()) {   //checks for spells on the same timer
				return true;    //can cast spell
			}
		}
	}
	return false;
}

bool Merc::CheckTaunt() {
	Mob* tar = GetTarget();
	//Only taunt if we are not top on target's hate list
	//This ensures we have taunt available to regain aggro if needed
	if(tar && tar->GetHateTop() && tar->GetHateTop() != this) {
		return true;
	}
	return false;
}

bool Merc::CheckAETaunt() {
	//need to check area for mobs needing taunted
	return false;
}

void Merc::MercMeditate(bool isSitting) {
	if(isSitting) {
		// If the bot is a caster has less than 99% mana while its not engaged, he needs to sit to meditate
		if(GetManaRatio() < 99.0f)
		{
			if(!IsSitting())
				Sit();
		}
		else
		{
			if(IsSitting())
				Stand();
		}
	}
	else
	{
		if(IsSitting())
			Stand();
	}

	if(IsSitting()) {
		if(!rest_timer.Enabled()) {
			rest_timer.Start(RuleI(Character, RestRegenTimeToActivate) * 1000);
		}
	}
	else {
		rest_timer.Disable();
	}
}


void Merc::Sit() {
	if(IsMoving()) {
		moved = false;
		// SetHeading(CalculateHeadingToTarget(GetTarget()->GetX(), GetTarget()->GetY()));
		SendPosition();
		SetMoving(false);
		tar_ndx = 0;
	}

	SetAppearance(eaSitting);
}

void Merc::Stand() {
	SetAppearance(eaStanding);
}

bool Merc::IsSitting() {
	bool result = false;

	if(GetAppearance() == eaSitting && !IsMoving())
		result = true;

	return result;
}

bool Merc::IsStanding() {
	bool result = false;

	if(GetAppearance() == eaStanding)
		result = true;

	return result;
}

float Merc::GetMaxMeleeRangeToTarget(Mob* target) {
	float result = 0;

	if(target) {
		float size_mod = GetSize();
		float other_size_mod = target->GetSize();

		if(GetRace() == 49 || GetRace() == 158 || GetRace() == 196) //For races with a fixed size
			size_mod = 60.0f;
		else if (size_mod < 6.0)
			size_mod = 8.0f;

		if(target->GetRace() == 49 || target->GetRace() == 158 || target->GetRace() == 196) //For races with a fixed size
			other_size_mod = 60.0f;
		else if (other_size_mod < 6.0)
			other_size_mod = 8.0f;

		if (other_size_mod > size_mod) {
			size_mod = other_size_mod;
		}

		// this could still use some work, but for now it's an improvement....

		if (size_mod > 29)
			size_mod *= size_mod;
		else if (size_mod > 19)
			size_mod *= size_mod * 2;
		else
			size_mod *= size_mod * 4;

		// prevention of ridiculously sized hit boxes
		if (size_mod > 10000)
			size_mod = size_mod / 7;

		result = size_mod;
	}

	return result;
}

void Merc::DoClassAttacks(Mob *target) {
	if(target == NULL)
		return;	//gotta have a target for all these

	bool ca_time = classattack_timer.Check(false);

	//only check attack allowed if we are going to do something
	if(ca_time && !IsAttackAllowed(target))
		return;

	if(!ca_time)
		return;

	float HasteModifier = 0;
	if(GetHaste() > 0)
		HasteModifier = 10000 / (100 + GetHaste());
	else if(GetHaste() < 0)
		HasteModifier = (100 - GetHaste());
	else
		HasteModifier = 100;

	int level = GetLevel();
	int reuse = TauntReuseTime * 1000;	//make this very long since if they dont use it once, they prolly never will
	bool did_attack = false;
	//class specific stuff...
	switch(GetClass()) {
		case MELEEDPS:
			if(level >= 10) {
				reuse = BackstabReuseTime * 1000;
				TryBackstab(target, reuse);
				did_attack = true;
			}
			break;
		case TANK:{
			if(level >= RuleI(Combat, NPCBashKickLevel)){
				if(MakeRandomInt(0, 100) > 25) //tested on live, warrior mobs both kick and bash, kick about 75% of the time, casting doesn't seem to make a difference.
				{
					DoAnim(animKick);
					int32 dmg = 0;

					if(GetWeaponDamage(target, (const Item_Struct*)NULL) <= 0){
						dmg = -5;
					}
					else{
						if(target->CheckHitChance(this, KICK, 0)) {
							if(RuleB(Combat, UseIntervalAC))
								dmg = GetKickDamage();
							else
								dmg = MakeRandomInt(1, GetKickDamage());

						}
					}

					reuse = KickReuseTime * 1000;
					DoSpecialAttackDamage(target, KICK, dmg, 1, -1, reuse);
					did_attack = true;
				}
				else
				{
					DoAnim(animTailRake);
					int32 dmg = 0;

					if(GetWeaponDamage(target, (const Item_Struct*)NULL) <= 0){
						dmg = -5;
					}
					else{
						if(target->CheckHitChance(this, BASH, 0)) {
							if(RuleB(Combat, UseIntervalAC))
								dmg = GetBashDamage();
							else
								dmg = MakeRandomInt(1, GetBashDamage());
						}
					}

					reuse = BashReuseTime * 1000;
					DoSpecialAttackDamage(target, BASH, dmg, 1, -1, reuse);
					did_attack = true;
				}
			}
			break;
		}
	}

	classattack_timer.Start(reuse*HasteModifier/100);
}

bool Merc::Attack(Mob* other, int Hand, bool bRiposte, bool IsStrikethrough, bool IsFromSpell)
{

	_ZP(Client_Attack);

	if (!other) {
		SetTarget(NULL);
		LogFile->write(EQEMuLog::Error, "A null Mob object was passed to Merc::Attack() for evaluation!");
		return false;
	}

	return NPC::Attack(other, Hand, bRiposte, IsStrikethrough, IsFromSpell);
}

void Merc::Damage(Mob* other, int32 damage, uint16 spell_id, SkillType attack_skill, bool avoidable, int8 buffslot, bool iBuffTic)
{
	if(IsDead() || IsCorpse())
		return;

	if(spell_id==0)
		spell_id = SPELL_UNKNOWN;

	NPC::Damage(other, damage, spell_id, attack_skill, avoidable, buffslot, iBuffTic);

	//Not needed since we're using NPC damage.
	//CommonDamage(other, damage, spell_id, attack_skill, avoidable, buffslot, iBuffTic);
}

bool Merc::FindTarget() {
	bool found = false;
	Mob* target = GetHateTop();

	if(target) {
		found = true;
		SetTarget(target);
	}

	return found;
}

void Merc::SetTarget(Mob* mob) {
	NPC::SetTarget(mob);
}

Mob* Merc::GetOwnerOrSelf() {
	Mob* Result = 0;

	if(this->GetMercOwner())
		Result = GetMercOwner();
	else
		Result = this;

	return Result;
}

void Merc::Death(Mob* killerMob, int32 damage, uint16 spell, SkillType attack_skill)
{
	NPC::Death(killerMob, damage, spell, attack_skill);
	Save();

	Mob *give_exp = hate_list.GetDamageTop(this);
	Client *give_exp_client = NULL;

	if(give_exp && give_exp->IsClient())
		give_exp_client = give_exp->CastToClient();

	bool IsLdonTreasure = (this->GetClass() == LDON_TREASURE);

	//if (give_exp_client && !IsCorpse() && MerchantType == 0)
	//{
	//	Group *kg = entity_list.GetGroupByClient(give_exp_client);
	//	Raid *kr = entity_list.GetRaidByClient(give_exp_client);

	//	if(!kr && give_exp_client->IsClient() && give_exp_client->GetBotRaidID() > 0) {
	//		BotRaids *br = entity_list.GetBotRaidByMob(give_exp_client->CastToMob());
	//		if(br) {
	//			if(!IsLdonTreasure)
	//				br->SplitExp((EXP_FORMULA), this);

	//			if(br->GetBotMainTarget() == this)
	//				br->SetBotMainTarget(NULL);

	//			/* Send the EVENT_KILLED_MERIT event for all raid members */
	//			if(br->BotRaidGroups[0]) {
	//				for(int j=0; j<MAX_GROUP_MEMBERS; j++) {
	//					if(br->BotRaidGroups[0]->members[j] && br->BotRaidGroups[0]->members[j]->IsClient()) {
	//						parse->Event(EVENT_KILLED_MERIT, GetNPCTypeID(), "killed", this, br->BotRaidGroups[0]->members[j]);
	//						if(RuleB(TaskSystem, EnableTaskSystem)) {
	//							br->BotRaidGroups[0]->members[j]->CastToClient()->UpdateTasksOnKill(GetNPCTypeID());
	//						}
	//					}
	//				}
	//			}
	//		}
	//	}
	//}

	//corpse->Depop();

	//no corpse, no exp if we're a merc. We'll suspend instead, since that's what live does. I'm not actually sure live supports 'depopping' merc corpses.
	//if(entity_list.GetCorpseByID(GetID()))
	//	entity_list.GetCorpseByID(GetID())->Depop();

	if(Suspend())
	{
		//todo: perl event?
	}
}

Client* Merc::GetMercOwner() {
	Client* mercOwner = 0;

	if(GetOwner())
	{
		if(GetOwner()->IsClient())
		{
			mercOwner = GetOwner()->CastToClient();
		}
	}

	return mercOwner;
}

Mob* Merc::GetOwner() {
	Mob* Result = 0;

	Result = entity_list.GetMob(GetOwnerID());

	if(!Result) {
		this->SetOwnerID(0);
	}

	return Result->CastToMob();
}

const char* Merc::GetRandomName(){
	// creates up to a 10 char name
	static char name[17];
	char vowels[18]="aeiouyaeiouaeioe";
	char cons[48]="bcdfghjklmnpqrstvwxzybcdgklmnprstvwbcdgkpstrkd";
	char rndname[17]="\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
	char paircons[33]="ngrkndstshthphsktrdrbrgrfrclcr";
	bool valid = false;

	while(!valid) {
		int rndnum=MakeRandomInt(0, 75),n=1;
		bool dlc=false;
		bool vwl=false;
		bool dbl=false;
		if (rndnum>63)
		{	// rndnum is 0 - 75 where 64-75 is cons pair, 17-63 is cons, 0-16 is vowel
			rndnum=(rndnum-61)*2;	// name can't start with "ng" "nd" or "rk"
			rndname[0]=paircons[rndnum];
			rndname[1]=paircons[rndnum+1];
			n=2;
		}
		else if (rndnum>16)
		{
			rndnum-=17;
			rndname[0]=cons[rndnum];
		}
		else
		{
			rndname[0]=vowels[rndnum];
			vwl=true;
		}
		int namlen=MakeRandomInt(5, 10);
		for (int i=n;i<namlen;i++)
		{
			dlc=false;
			if (vwl)	//last char was a vowel
			{			// so pick a cons or cons pair
				rndnum=MakeRandomInt(0, 62);
				if (rndnum>46)
				{	// pick a cons pair
					if (i>namlen-3)	// last 2 chars in name?
					{	// name can only end in cons pair "rk" "st" "sh" "th" "ph" "sk" "nd" or "ng"
						rndnum=MakeRandomInt(0, 7)*2;
					}
					else
					{	// pick any from the set
						rndnum=(rndnum-47)*2;
					}
					rndname[i]=paircons[rndnum];
					rndname[i+1]=paircons[rndnum+1];
					dlc=true;	// flag keeps second letter from being doubled below
					i+=1;
				}
				else
				{	// select a single cons
					rndname[i]=cons[rndnum];
				}
			}
			else
			{		// select a vowel
				rndname[i]=vowels[MakeRandomInt(0, 16)];
			}
			vwl=!vwl;
			if (!dbl && !dlc)
			{	// one chance at double letters in name
				if (!MakeRandomInt(0, i+9))	// chances decrease towards end of name
				{
					rndname[i+1]=rndname[i];
					dbl=true;
					i+=1;
				}
			}
		}

		rndname[0]=toupper(rndname[0]);

		if(!database.CheckNameFilter(rndname)) {
			valid = false;
		}
		else if(rndname[0] < 'A' && rndname[0] > 'Z') {
			//name must begin with an upper-case letter.
			valid = false;
		}
		else if (database.CheckUsedName(rndname)) {
			valid = true;
		}
		else {
			valid = false;
		}
	}

	memset(name, 0, 17);
	strcpy(name, rndname);
	return name;
}


bool Compare_Merc_Spells(MercSpell i, MercSpell j);

bool Compare_Merc_Spells(MercSpell i, MercSpell j)
{
	return(i.slot > j.slot);
}

bool Merc::LoadMercSpells() {
	// loads mercs spells into list
	merc_spells.clear();

	std::list<MercSpellEntry> spellList = zone->merc_spells_list[GetClass()];

	if (spellList.size() == 0) {
		AIautocastspell_timer->Disable();
		return false;
	}

	uint32 proficiency_id = GetProficiencyID();
	int16 attack_proc_spell = -1;
	int8 proc_chance = 0;

	for (std::list<MercSpellEntry>::iterator mercSpellEntryItr = spellList.begin(); mercSpellEntryItr != spellList.end(); mercSpellEntryItr++) {
		if (proficiency_id == mercSpellEntryItr->proficiencyid && GetLevel() >= mercSpellEntryItr->minlevel && GetLevel() <= mercSpellEntryItr->maxlevel && mercSpellEntryItr->spellid > 0) {
			MercSpell mercSpell;

			mercSpell.spellid = mercSpellEntryItr->spellid;
			mercSpell.type = mercSpellEntryItr->type;
			mercSpell.stance = mercSpellEntryItr->stance;
			mercSpell.slot = mercSpellEntryItr->slot;
			mercSpell.proc_chance = mercSpellEntryItr->proc_chance;
			mercSpell.time_cancast = 0;

			merc_spells.push_back(mercSpell);

			if(mercSpellEntryItr->proc_chance > 0)
				AddProcToWeapon(mercSpellEntryItr->spellid, true, mercSpellEntryItr->proc_chance);
		}
	}
	std::sort(merc_spells.begin(), merc_spells.end(), Compare_Merc_Spells);

	if (merc_spells.size() == 0)
		AIautocastspell_timer->Disable();
	else {
		HasAISpell = true;
		AIautocastspell_timer->Trigger();
	}

	if(MERC_DEBUG > 0)
		Message(7, "Mercenary Debug: Loaded %i spells for merc.", merc_spells.size());

	return true;
}

Merc* Merc::LoadMerc(Client *c, MercTemplate* merc_template, uint32 merchant_id) {
	Merc* merc;

	if(c)
	{
		if(c->GetMercID()) {
			merc_template = zone->GetMercTemplate(c->GetEPP().mercTemplateID);
		}
	}

	//get mercenary data
	if(merc_template) {
		const NPCType* npc_type_to_copy = database.GetMercType(merc_template->MercNPCID, merc_template->RaceID, c->GetLevel()); //TODO: Maybe add a way of updating client merc stats in a seperate function? like, for example, on leveling up.
		if(npc_type_to_copy != NULL)
		{
			NPCType* npc_type = new NPCType; //This is actually a very terrible method of assigning stats, and should be changed at some point. See the comment in merc's deconstructor.
			memset(npc_type, 0, sizeof(NPCType));
			memcpy(npc_type, npc_type_to_copy, sizeof(NPCType));
			if(c)
			{
				if(c->GetEPP().merc_name[0] == 0)
				{
					snprintf(c->GetEPP().merc_name, 64, "%s", GetRandomName()); //sanity check.
				}
				snprintf(npc_type->name, 64, "%s", c->GetEPP().merc_name);
			}
			uint8 gender;
			if(merchant_id > 0) {
				NPC* tar = entity_list.GetNPCByID(merchant_id);
				if(tar) {
					gender = Mob::GetDefaultGender(npc_type->race, tar->GetGender());
				}
			}
			else {
				gender = c->GetEPP().mercGender;
			}

			sprintf(npc_type->lastname, "%s's %s", c->GetName(), "Mercenary");
			npc_type->gender = gender;
			npc_type->loottable_id = 0; // Loottable has to be 0, otherwise we'll be leavin' some corpses!
			npc_type->npc_id = 0; //NPC ID has to be 0, otherwise db gets all confuzzled.
			npc_type->race = merc_template->RaceID;
			npc_type->class_ = merc_template->ClassID;
			npc_type->maxlevel = 0; //We should hard-set this to override scalerate's functionality in the NPC class when it is constructed.

			Merc* merc = new Merc(npc_type, c->GetX(), c->GetY(), c->GetZ(), 0);
			merc->SetMercData( merc_template->MercTemplateID );
			merc->UpdateMercStats(c);
			return merc;
		}
	}

	return 0;
}

void Merc::UpdateMercStats(Client *c) {
	if(c->GetEPP().mercTemplateID >0)
	{
		const NPCType* npc_type = database.GetMercType( zone->GetMercTemplate(c->GetEPP().mercTemplateID)->MercNPCID, GetRace(), c->GetLevel());
		if (npc_type)
		{
			max_hp = (npc_type->max_hp * npc_type->scalerate) / 100;
			base_hp = (npc_type->max_hp * npc_type->scalerate) / 100;
			max_mana = (npc_type->max_hp * npc_type->scalerate) / 100;
			base_mana = (npc_type->max_hp * npc_type->scalerate) / 100;
			hp_regen = (npc_type->hp_regen * npc_type->scalerate) / 100;
			mana_regen = (npc_type->mana_regen * npc_type->scalerate) / 100;
			level = npc_type->level;
			max_dmg = (npc_type->max_dmg * npc_type->scalerate) / 100;
			min_dmg = (npc_type->min_dmg * npc_type->scalerate) / 100;
			_baseSTR = (npc_type->STR  * npc_type->scalerate) / 100;
			_baseSTA = (npc_type->STA * npc_type->scalerate) / 100;
			_baseDEX = (npc_type->DEX * npc_type->scalerate) / 100;
			_baseAGI = (npc_type->AGI * npc_type->scalerate) / 100;
			_baseWIS = (npc_type->WIS * npc_type->scalerate) / 100;
			_baseINT = (npc_type->INT * npc_type->scalerate) / 100;
			_baseCHA = (npc_type->CHA * npc_type->scalerate) / 100;
			_baseATK = (npc_type->ATK * npc_type->scalerate) / 100;
			_baseMR =  (npc_type->MR * npc_type->scalerate) / 100;
			_baseFR =  (npc_type->FR * npc_type->scalerate) / 100;
			_baseDR =  (npc_type->DR * npc_type->scalerate) / 100;
			_basePR =  (npc_type->PR * npc_type->scalerate) / 100;
			_baseCR =  (npc_type->CR * npc_type->scalerate) / 100;
			_baseCorrup =  (npc_type->Corrup * npc_type->scalerate) / 100;
			_baseAC =  (npc_type->AC * npc_type->scalerate) / 100;
			attack_speed = npc_type->attack_speed;
			attack_count = npc_type->attack_count;
			spellscale = npc_type->spellscale;
			healscale = npc_type->healscale;

			CalcBonuses();
			
			CalcMaxEndurance();
			CalcMaxHP();
			CalcMaxMana();
		}
	}
}

void Merc::UpdateMercAppearance(Client *c) {
}

bool Merc::Spawn(Client *owner) {
	if(!RuleB(Mercs, AllowMercs))
		return false;

	if(!owner)
		return false;

	MercTemplate* merc_template = zone->GetMercTemplate(GetMercTemplateID());

	if(!merc_template)
		return false;

	entity_list.AddMerc(this, true, true);

	SendPosition();

	//printf("Spawned Merc with ID %i\n", npc->GetID()); fflush(stdout);

	/*
	uint32 itemID = 0;
	uint8 materialFromSlot = 0xFF;
	for(int i=0; i<22; ++i) {
		itemID = GetMercItemBySlot(i);
		if(itemID != 0) {
			materialFromSlot = Inventory::CalcMaterialFromSlot(i);
			if(materialFromSlot != 0xFF) {
				this->SendWearChange(materialFromSlot);
			}
		}
	}
	*/

	return true;
}

void Client::UpdateMercTimer()
{
	Merc *merc =  GetMerc();

	if(merc && !merc->IsSuspended())
	{		
		if(merc_timer.Check())
		{
			uint32 upkeep = Merc::CalcUpkeepCost(merc->GetMercTemplateID(), GetLevel());
			//TakeMoneyFromPP((upkeep * 100), true);	// Upkeep is in gold
			GetEPP().mercTimerRemaining = RuleI(Mercs, UpkeepIntervalMS);
			SendMercTimerPacket(GetMercID(), 5, 0, RuleI(Mercs, UpkeepIntervalMS), RuleI(Mercs, SuspendIntervalMS));
			merc_timer.Start(RuleI(Mercs, UpkeepIntervalMS));

			// Send upkeep charge message and reset the upkeep timer
			if (GetClientVersion() < EQClientRoF)
				SendMercMerchantResponsePacket(10);
			else
				SendMercMerchantResponsePacket(11);

			/*
			uint32 upkeep_plat = 0;
			uint32 upkeep_gold = 0;

			if (upkeep >= 10)
				upkeep_plat = (int)(upkeep / 10);

			if (upkeep - (upkeep_plat * 10) >= 1)
				upkeep_gold = (int)((upkeep - (upkeep_plat * 10)) / 100);
			*/

			// Normal upkeep charge message
			//Message(7, "You have been charged a mercenary upkeep cost of %i plat, and %i gold and your mercenary upkeep cost timer has been reset to 15 minutes.", upkeep_plat, upkeep_gold, (int)(RuleI(Mercs, UpkeepIntervalMS) / 1000 / 60));

			// Message below given when too low level to be charged
			// Temporarily enabled for all upkeep costs until mercenary stuff is completed
			//Message(7, "Your mercenary waived an upkeep cost of %i plat, and %i gold or %i %s and your mercenary upkeep cost timer has been reset to %i minutes", upkeep_plat, upkeep_gold, 1, "Bayle Marks", (int)(RuleI(Mercs, UpkeepIntervalMS) / 1000 / 60));
		}
	}
}

void Client::CheckMercSuspendTimer()
{
	if(GetEPP().mercSuspendedTime != 0) {
			if(time(NULL) >= GetEPP().mercSuspendedTime){
			GetEPP().mercSuspendedTime = 0;
			SendMercSuspendResponsePacket(GetEPP().mercSuspendedTime);
			p_timers.Start(pTimerMercSuspend, RuleI(Mercs, SuspendIntervalS));
		}
	}
}

void Client::SuspendMercCommand()
{
	bool ExistsMerc = GetEPP().mercTemplateID != 0;
		if(ExistsMerc == true)
		{
			if(GetEPP().mercIsSuspended) {
				//p_timers.Enable(pTimerMercReuse);

				// Set time remaining to max on unsuspend - there is a charge for unsuspending as well
				// GetEPP().mercTimerRemaining = RuleI(Mercs, UpkeepIntervalMS);

				// Get merc, assign it to client & spawn
				Merc* merc = Merc::LoadMerc(this, &zone->merc_templates[GetEPP().mercTemplateID], 0);
				SpawnMerc(merc);
			}
			else
			{
				Merc* CurrentMerc = GetMerc();

				if(CurrentMerc && GetMercID()) {
					CurrentMerc->Suspend();
				}
			}
		}
}


// Handles all client zone change event
void Merc::ProcessClientZoneChange(Client* mercOwner) {
	if(mercOwner)
	{
		Zone();
	}
}

void Client::SpawnMercOnZone()
{
	if(!RuleB(Mercs, AllowMercs))
		return;

	if (GetMerc())
		return;

	bool ExistsMerc = GetEPP().mercTemplateID != 0;
	if(ExistsMerc == true)
	{
		if(!GetEPP().mercIsSuspended) {
			GetEPP().mercSuspendedTime = 0;
			// Get merc, assign it to client & spawn
			Merc* merc = Merc::LoadMerc(this, &zone->merc_templates[GetEPP().mercTemplateID], 0);
			SpawnMerc(merc);
		}
		else
		{
			// Send Mercenary Status/Timer packet
			SendMercTimerPacket(0, 1, GetEPP().mercSuspendedTime, RuleI(Mercs, UpkeepIntervalMS), RuleI(Mercs, SuspendIntervalMS));

			SendMercPersonalInfo();

			if(GetEPP().mercSuspendedTime != 0) {
				if(time(NULL) >= GetEPP().mercSuspendedTime){
					GetEPP().mercSuspendedTime = 0;
				}
			}
			SendMercSuspendResponsePacket(GetEPP().mercSuspendedTime);
		}
	}
}

void Client::SpawnMerc(Merc* merc)
{
	if(!RuleB(Mercs, AllowMercs))
		return;

	if(merc) {
		merc->Spawn(this);
		merc->SetSuspended(false);
		SetMerc(merc);
		merc->Unsuspend();
	}
}

bool Merc::Suspend() {
	Client* mercOwner;

	if(GetMercOwner()) {
		mercOwner = GetMercOwner();
	}

	if(!mercOwner)
		return false;

	SetSuspended(true);

	if(HasGroup()) {
		RemoveMercFromGroup(this, GetGroup());
	}

	//Save();

	mercOwner->GetEPP().mercIsSuspended = true;
	mercOwner->GetEPP().mercSuspendedTime = time(NULL) + RuleI(Mercs, SuspendIntervalS);
	mercOwner->GetEPP().mercTimerRemaining = mercOwner->GetMercTimer().GetRemainingTime();
	mercOwner->GetMercTimer().Disable();
	//mercOwner->UpdateMercTimer();
	mercOwner->SendMercSuspendResponsePacket(mercOwner->GetEPP().mercSuspendedTime);

	Depop();

	return true;
}

bool Merc::Unsuspend() {
	Client* mercOwner;

	if(GetMercOwner()) {
		mercOwner = GetMercOwner();
	}

	if(!mercOwner)
		return false;

	if(GetMercID()) {
		uint32 entityID = 0;
		uint32 mercState = 5;
		uint32 suspendedTime = 0;

		SetSuspended(false);
		mercOwner->GetEPP().mercIsSuspended = false;
		mercOwner->GetEPP().mercSuspendedTime = 0;

		mercOwner->SendMercenaryUnsuspendPacket(0);
		mercOwner->SendMercenaryUnknownPacket(1);

		mercOwner->SendMercTimerPacket(GetMercID(), mercState, suspendedTime, RuleI(Mercs, UpkeepIntervalMS), RuleI(Mercs, SuspendIntervalMS));

		mercOwner->GetMercTimer().Start(mercOwner->GetEPP().mercTimerRemaining);

		if(!mercOwner->GetPTimers().Expired(&database, pTimerMercSuspend, false))
			mercOwner->GetPTimers().Clear(&database, pTimerMercSuspend);

		mercOwner->SendMercPersonalInfo();

		if(!mercOwner->IsGrouped())
		{
			Group *g = new Group(mercOwner);
			if(AddMercToGroup(this, g))
			{
				entity_list.AddGroup(g);
				database.SetGroupLeaderName(g->GetID(), mercOwner->GetName());
				database.SetGroupID(mercOwner->GetName(), g->GetID(), mercOwner->CharacterID());
				database.SetGroupID(this->GetName(), g->GetID(), mercOwner->CharacterID(), true);
				database.RefreshGroupFromDB(mercOwner);
				g->SaveGroupLeaderAA();
			}
		}
		else if (AddMercToGroup(this, mercOwner->GetGroup()))
		{
			database.SetGroupID(GetName(), mercOwner->GetGroup()->GetID(), mercOwner->CharacterID(), true);
			database.RefreshGroupFromDB(mercOwner);
		}
		else
		{
			if(MERC_DEBUG > 0)
				mercOwner->Message(7, "Mercenary failed to join the group - Suspending");

			Suspend();
		}

		LoadMercSpells();
	}

	return true;
}

bool Merc::Dismiss() {
	Client* mercOwner;

	if(GetMercOwner()) {
		mercOwner = GetMercOwner();
	}

	if(!mercOwner)
		return false;

	mercOwner->SendClearMercInfo();
	mercOwner->SendMercTimerPacket(GetMercID(), 5, 0, RuleI(Mercs, UpkeepIntervalMS), RuleI(Mercs, SuspendIntervalMS));

	SetMercID(0);

	mercOwner->SetMerc(0);

	Depop();

	return true;
}

void Merc::Zone() {
	//Save();
	Depop();
}

void Merc::Depop() {
	WipeHateList();

	entity_list.RemoveFromHateLists(this);

	if(HasGroup())
		RemoveMercFromGroup(this, GetGroup());

	if(HasPet()) {
		GetPet()->Depop();
	}

	SetOwnerID(0);

	p_depop = true;

	NPC::Depop(false);
}

bool Merc::RemoveMercFromGroup(Merc* merc, Group* group) {
	bool Result = false;

	if(merc && group) {
		if(merc->HasGroup()) {
			if(!group->IsLeader(merc)) {
				merc->SetFollowID(0);

				if(group->DelMember(merc)) {
					if(merc->GetMercCharacterID() != 0)
						database.SetGroupID(merc->GetName(), 0, merc->GetMercCharacterID(), true);
				}

				if(group->GroupCount() <= 1 && ZoneLoaded)
				{
					group->DisbandGroup();
				}
			}
			else {
				for(int i = 0; i < MAX_GROUP_MEMBERS; i++) {
					if(!group->members[i])
						continue;

					if(!group->members[i]->IsMerc())
						continue;

					Merc* groupmerc = group->members[i]->CastToMerc();

					groupmerc->SetOwnerID(0);
				}

				group->DisbandGroup();
				database.SetGroupID(merc->GetCleanName(), 0, merc->GetMercCharacterID(), true);
			}

			Result = true;
		}
	}

	return Result;
}

bool Merc::AddMercToGroup(Merc* merc, Group* group) {
	bool Result = false;

	if(merc && group) {
		// Remove merc from current group if any
		if(merc->HasGroup()) {
			merc->RemoveMercFromGroup(merc, merc->GetGroup());
		}
		// Add merc to this group
		if(group->AddMember(merc)) {
			merc->SetFollowID(merc->GetMercOwner()->GetID());
			Result = true;
		}
		else
		{
			merc->Suspend();
		}

	}

	return Result;
}

Merc* Client::GetMerc() {
	if(GetMercID() == 0)
		return(NULL);

	Merc* tmp = entity_list.GetMercByID(GetMercID());
	if(tmp == NULL) {
		SetMercID(0);
		return(NULL);
	}

	if(tmp->GetOwnerID() != GetID()) {
		SetMercID(0);
		return(NULL);
	}

	return(tmp);
}

void Merc::SetMercData( uint32 template_id ) {
	MercTemplate* merc_template = zone->GetMercTemplate(template_id);
	SetMercTemplateID( merc_template->MercTemplateID );
	SetMercType( merc_template->MercType );
	SetMercSubType( merc_template->MercSubType );
	SetProficiencyID( merc_template->ProficiencyID );
	SetCostFormula( merc_template->CostFormula );
	SetMercNameType( merc_template->MercNameType );
}

MercTemplate* Zone::GetMercTemplate( uint32 template_id ) {
	return &merc_templates[template_id];
}

void Client::SetMerc(Merc* newmerc) {
	Merc* oldmerc = GetMerc();
	if (oldmerc) {
		oldmerc->SetOwnerID(0);
	}
	if (!newmerc) {
		SetMercID(0);
		GetEPP().mercTemplateID = 0;
		GetEPP().mercIsSuspended = false;
		GetEPP().mercSuspendedTime = 0;
		GetEPP().mercGender = 0;
		GetEPP().mercState = 0;
		GetEPP().mercTimerRemaining = 0;
		memset(GetEPP().merc_name, 0, 64);
	} else {
		SetMercID(newmerc->GetID());
		newmerc->SetMercID(newmerc->GetID());
		//Client* oldowner = entity_list.GetClientByID(newmerc->GetOwnerID());
		newmerc->SetOwnerID(this->GetID());
		newmerc->SetMercCharacterID(this->CharacterID());
		newmerc->SetClientVersion((uint8)this->GetClientVersion());
		GetEPP().mercTemplateID = newmerc->GetMercTemplateID();
		GetEPP().mercIsSuspended = newmerc->IsSuspended();
		GetEPP().mercSuspendedTime = 0;
		GetEPP().mercGender = newmerc->GetGender();
	}
}

void Client::UpdateMercLevel() {
	Merc* merc = GetMerc();
	if (merc) {
		merc->UpdateMercStats(this);
	}
}

void Client::SendMercMerchantResponsePacket(int32 response_type) {
	// This response packet brings up the Mercenary Manager window
	EQApplicationPacket *outapp = new EQApplicationPacket(OP_MercenaryHire, sizeof(MercenaryMerchantResponse_Struct));
	MercenaryMerchantResponse_Struct* mmr = (MercenaryMerchantResponse_Struct*)outapp->pBuffer;
	mmr->ResponseType = response_type;		// send specified response type

	DumpPacket(outapp);
	FastQueuePacket(&outapp);
}

void Client::SendMercenaryUnknownPacket(uint8 type) {
	EQApplicationPacket *outapp = new EQApplicationPacket(OP_MercenaryUnknown1, 1);
	outapp->WriteUInt8(type);

	DumpPacket(outapp);
	FastQueuePacket(&outapp);
}

void Client::SendMercenaryUnsuspendPacket(uint8 type) {
	EQApplicationPacket *outapp = new EQApplicationPacket(OP_MercenaryUnsuspendResponse, 1);
	outapp->WriteUInt8(type);

	DumpPacket(outapp);
	FastQueuePacket(&outapp);
}

void Client::SendMercSuspendResponsePacket(uint32 suspended_time) {
	EQApplicationPacket *outapp = new EQApplicationPacket(OP_MercenarySuspendResponse, sizeof(SuspendMercenaryResponse_Struct));
	SuspendMercenaryResponse_Struct* smr = (SuspendMercenaryResponse_Struct*)outapp->pBuffer;
	smr->SuspendTime = suspended_time;		// Seen 0 (not suspended) or c9 c2 64 4f (suspended on Sat Mar 17 11:58:49 2012) - Unix Timestamp

	DumpPacket(outapp);
	FastQueuePacket(&outapp);
}

void Client::SendMercTimerPacket(int32 entity_id, int32 merc_state, int32 suspended_time, int32 update_interval, int32 unk01) {

	if (GetClientVersion() == EQClientSoD) {
		update_interval = GetEPP().mercTimerRemaining;
	}

	// Send Mercenary Status/Timer packet
	EQApplicationPacket *outapp = new EQApplicationPacket(OP_MercenaryTimer, sizeof(MercenaryStatus_Struct));
	MercenaryStatus_Struct* mss = (MercenaryStatus_Struct*)outapp->pBuffer;
	mss->MercEntityID = entity_id; // Seen 0 (no merc spawned) or unknown value when merc is spawned
	mss->UpdateInterval = update_interval; // Seen 900000 - 15 minutes in ms
	mss->MercUnk01 = unk01; // Seen 180000 - 3 minutes in ms - Used for the unsuspend button refresh timer
	mss->MercState = merc_state; // Seen 5 (normal) or 1 (suspended)
	mss->SuspendedTime = suspended_time; // Seen 0 for not suspended or Unix Timestamp for suspended merc

	DumpPacket(outapp);
	FastQueuePacket(&outapp);
}

void Client::SendMercAssignPacket(uint32 entityID, uint32 unk01, uint32 unk02) {
	EQApplicationPacket *outapp = new EQApplicationPacket(OP_MercenaryAssign, sizeof(MercenaryAssign_Struct));
	MercenaryAssign_Struct* mas = (MercenaryAssign_Struct*)outapp->pBuffer;
	mas->MercEntityID = entityID;
	mas->MercUnk01 = unk01;
	mas->MercUnk02 = unk02;
	FastQueuePacket(&outapp);
}

void NPC::LoadMercTypes(){
	std::string errorMessage;
	char* Query = 0;
	char TempErrorMessageBuffer[MYSQL_ERRMSG_SIZE];
	MYSQL_RES* DatasetResult;
	MYSQL_ROW DataRow;

	if(!database.RunQuery(Query, MakeAnyLenString(&Query, "SELECT DISTINCT MTyp.dbstring, MTyp.clientversion FROM merc_merchant_entries MME, merc_merchant_template_entries MMTE, merc_types MTyp, merc_templates MTem WHERE MME.merchant_id = %i AND MME.merc_merchant_template_id = MMTE.merc_merchant_template_id AND MMTE.merc_template_id = MTem.merc_template_id AND MTem.merc_type_id = MTyp.merc_type_id;", GetNPCTypeID()), TempErrorMessageBuffer, &DatasetResult)) {
		errorMessage = std::string(TempErrorMessageBuffer);
	}
	else {
		while(DataRow = mysql_fetch_row(DatasetResult)) {
			MercType tempMercType;

			tempMercType.Type = atoi(DataRow[0]);
			tempMercType.ClientVersion = atoi(DataRow[1]);

			mercTypeList.push_back(tempMercType);
		}

		mysql_free_result(DatasetResult);
	}

	safe_delete(Query);
	Query = 0;

	if(!errorMessage.empty()) {
		LogFile->write(EQEMuLog::Error, "Error in NPC::LoadMercTypes()");
	}
}

void NPC::LoadMercs(){

	std::string errorMessage;
	char* Query = 0;
	char TempErrorMessageBuffer[MYSQL_ERRMSG_SIZE];
	MYSQL_RES* DatasetResult;
	MYSQL_ROW DataRow;

	if(!database.RunQuery(Query, MakeAnyLenString(&Query, "SELECT DISTINCT MTem.merc_template_id, MTyp.dbstring AS merc_type_id, MTem.dbstring AS merc_subtype_id, 0 AS CostFormula, CASE WHEN MTem.clientversion > MTyp.clientversion then MTem.clientversion ELSE MTyp.clientversion END AS clientversion, MTem.merc_npc_type_id FROM merc_merchant_entries MME, merc_merchant_template_entries MMTE, merc_types MTyp, merc_templates MTem WHERE MME.merchant_id = %i AND MME.merc_merchant_template_id = MMTE.merc_merchant_template_id AND MMTE.merc_template_id = MTem.merc_template_id AND MTem.merc_type_id = MTyp.merc_type_id;", GetNPCTypeID()), TempErrorMessageBuffer, &DatasetResult)) {
		errorMessage = std::string(TempErrorMessageBuffer);
	}
	else {
		while(DataRow = mysql_fetch_row(DatasetResult)) {
			MercData tempMerc;

			tempMerc.MercTemplateID = atoi(DataRow[0]);
			tempMerc.MercType = atoi(DataRow[1]);
			tempMerc.MercSubType = atoi(DataRow[2]);
			tempMerc.CostFormula = atoi(DataRow[3]);
			tempMerc.ClientVersion = atoi(DataRow[4]);
			tempMerc.NPCID = atoi(DataRow[5]);

			mercDataList.push_back(tempMerc);
		}

		mysql_free_result(DatasetResult);
	}

	safe_delete(Query);
	Query = 0;

	if(!errorMessage.empty()) {
		LogFile->write(EQEMuLog::Error, "Error in NPC::LoadMercTypes()");
	}
}

int NPC::GetNumMercTypes(uint32 clientVersion)
{
	int count = 0;
	std::list<MercType> mercTypeList = GetMercTypesList();

	for(std::list<MercType>::iterator mercTypeListItr = mercTypeList.begin(); mercTypeListItr != mercTypeList.end(); mercTypeListItr++) {
		if(mercTypeListItr->ClientVersion <= clientVersion)
			count++;
	}

	return count;
}

int NPC::GetNumMercs(uint32 clientVersion)
{
	int count = 0;
	std::list<MercData> mercDataList = GetMercsList();

	for(std::list<MercData>::iterator mercListItr = mercDataList.begin(); mercListItr != mercDataList.end(); mercListItr++) {
		if(mercListItr->ClientVersion <= clientVersion)
			count++;
	}

	return count;
}

std::list<MercType> NPC::GetMercTypesList(uint32 clientVersion) {
	std::list<MercType> result;

	if(GetNumMercTypes() > 0) {
		for(std::list<MercType>::iterator mercTypeListItr = mercTypeList.begin(); mercTypeListItr != mercTypeList.end(); mercTypeListItr++) {
			if(mercTypeListItr->ClientVersion <= clientVersion) {
				MercType mercType;
				mercType.Type = mercTypeListItr->Type;
				mercType.ClientVersion = mercTypeListItr->ClientVersion;
				result.push_back(mercType);
			}
		}
	}

	return result;
}

std::list<MercData> NPC::GetMercsList(uint32 clientVersion) {
	std::list<MercData> result;

	if(GetNumMercs() > 0) {
		for(std::list<MercData>::iterator mercListItr = mercDataList.begin(); mercListItr != mercDataList.end(); mercListItr++) {
			if(mercListItr->ClientVersion <= clientVersion) {
				MercTemplate *merc_template = zone->GetMercTemplate(mercListItr->MercTemplateID);

				if(merc_template) {
					MercData mercData;
					mercData.MercTemplateID = mercListItr->MercTemplateID;
					mercData.MercType = merc_template->MercType;
					mercData.MercSubType = merc_template->MercSubType;
					mercData.CostFormula = merc_template->CostFormula;
					mercData.ClientVersion = merc_template->ClientVersion;
					mercData.NPCID = merc_template->MercNPCID;
					result.push_back(mercData);
				}
			}
		}
	}

	return result;
}

uint32 Merc::CalcPurchaseCost( uint32 templateID , uint8 level, uint8 currency_type) {
	uint32 cost = 0;

	MercTemplate *mercData = zone->GetMercTemplate(templateID);

	if(mercData) {
		if(currency_type == 0) { //calculate cost in coin - cost in gold
			int levels_above_cutoff;
			switch (mercData->CostFormula) {
			case 0:
				levels_above_cutoff = level > 10 ? (level - 10) : 0;
				cost = levels_above_cutoff * 300;
				cost += level >= 10 ? 100 : 0;
				break;
			default:
				break;
			}
		}
		else if(currency_type == 19) {
			cost = 0;
		}
	}

	return cost/100;
}

uint32 Merc::CalcUpkeepCost( uint32 templateID , uint8 level, uint8 currency_type) {
	uint32 cost = 0;

	MercTemplate *mercData = zone->GetMercTemplate(templateID);

	if(mercData) {
		if(currency_type == 0) { //calculate cost in coin - cost in gold
			int levels_above_cutoff;
			switch (mercData->CostFormula) {
			case 0:
				levels_above_cutoff = level > 10 ? (level - 10) : 0;
				cost = levels_above_cutoff * 300;
				cost += level >= 10 ? 100 : 0;
				break;
			default:
				break;
			}
		}
		else if(currency_type == 19) { // cost in Bayle Marks
			cost = 1;
		}
	}

	return cost/100;
}