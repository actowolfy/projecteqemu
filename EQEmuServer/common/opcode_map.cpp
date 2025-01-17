#include "debug.h"
#include <map>
#include <string>

using namespace std;

map<unsigned long, string> opcode_map;

string get_opcode_name(unsigned long opcode)
{
map<unsigned long, string>::iterator itr;;

	return (itr=opcode_map.find(opcode))!=opcode_map.end() ? itr->second : "OP_Unknown";
}
void load_opcode_names()
{
	opcode_map[0x0176]="LiveOP_Heartbeat";
	opcode_map[0x02d7]="LiveOP_ReloadUI";
	opcode_map[0x01eb]="LiveOP_IncreaseStats";
	opcode_map[0x0134]="LiveOP_ApproveZone";
	opcode_map[0x01d5]="LiveOP_Dye";
	opcode_map[0x0168]="LiveOP_Stamina";
	opcode_map[0x014d]="LiveOP_ControlBoat";
	opcode_map[0x003e]="LiveOP_MobUpdate";
	opcode_map[0x0027]="LiveOP_ClientUpdate";
	opcode_map[0x0024]="LiveOP_ChannelMessage";
	opcode_map[0x01d7]="LiveOP_SimpleMessage";
	opcode_map[0x01d8]="LiveOP_FormattedMessage";
	opcode_map[0x01c6]="LiveOP_TGB";
	opcode_map[0x0285]="LiveOP_TestBuff";
	opcode_map[0x012d]="LiveOP_Bind_Wound";
	opcode_map[0x01ab]="LiveOP_Charm";
	opcode_map[0x014c]="LiveOP_Begging";
	opcode_map[0x0152]="LiveOP_MoveCoin";
	opcode_map[0x0292]="LiveOP_SpawnDoor";
	opcode_map[0x009d]="LiveOP_Sneak";
	opcode_map[0x0079]="LiveOP_ExpUpdate";
	opcode_map[0x027d]="LiveOP_DumpName";
	opcode_map[0x01ea]="LiveOP_RespondAA";
	opcode_map[0x01c9]="LiveOP_SendAAStats";
	opcode_map[0x0366]="LiveOP_SendAATable";
	opcode_map[0x01e9]="LiveOP_AAAction";
	opcode_map[0x00bb]="LiveOP_BoardBoat";
	opcode_map[0x00bc]="LiveOP_LeaveBoat";
	opcode_map[0x02b8]="LiveOP_AdventureInfoRequest";
	opcode_map[0x02b9]="LiveOP_AdventureInfo";
	opcode_map[0x02a6]="LiveOP_AdventureRequest";
	opcode_map[0x02a8]="LiveOP_AdventureDetails";
	opcode_map[0x02a9]="LiveOP_LDoNButton";
	opcode_map[0x02ba]="LiveOP_AdventureData";
	opcode_map[0x02c9]="LiveOP_AdventureFinish";
	opcode_map[0x02c6]="LiveOP_LeaveAdventure";
	opcode_map[0x02ce]="LiveOP_AdventureUpdate";
	opcode_map[0x002b]="LiveOP_SendExpZonein";
	opcode_map[0x01e4]="LiveOP_ZoneInSendName";
	opcode_map[0x01bf]="LiveOP_GuildLeader";
	opcode_map[0x009a]="LiveOP_GuildPeace";
	opcode_map[0x0132]="LiveOP_GuildRemove";
	opcode_map[0x0059]="LiveOP_GuildMemberList";
	opcode_map[0x026e]="LiveOP_GuildMemberUpdate";
	opcode_map[0x0130]="LiveOP_GuildInvite";
	opcode_map[0x01c0]="LiveOP_GuildMOTD";
	opcode_map[0x003c]="LiveOP_GuildPublicNote";
	opcode_map[0x027e]="LiveOP_GetGuildMOTD";
	opcode_map[0x0277]="LiveOP_GuildDemote";
	opcode_map[0x0131]="LiveOP_GuildInviteAccept";
	opcode_map[0x00a4]="LiveOP_GuildWar";
	opcode_map[0x0133]="LiveOP_GuildDelete";
	opcode_map[0x0233]="LiveOP_GuildManageRemove";
	opcode_map[0x022d]="LiveOP_GuildManageAdd";
	opcode_map[0x0039]="LiveOP_GuildManageStatus";
	opcode_map[0x01e8]="LiveOP_Trader";
	opcode_map[0x01e7]="LiveOP_Bazaar";
	opcode_map[0x01c4]="LiveOP_BecomeTrader";
	opcode_map[0x01f4]="LiveOP_BazaarInspect";
	opcode_map[0x006e]="LiveOP_TraderItemUpdate";
	opcode_map[0x017c]="LiveOP_TraderDelItem";
	opcode_map[0x01eb]="LiveOP_TraderShop";
	opcode_map[0x01ca]="LiveOP_TraderBuy";
	opcode_map[0x01ac]="LiveOP_PetCommands";
	opcode_map[0x0042]="LiveOP_TradeSkillCombine";
	opcode_map[0x02e5]="LiveOP_AugmentItem";
	opcode_map[0x0367]="LiveOP_ItemName";
	opcode_map[0x02cd]="LiveOP_ShopItem";
	opcode_map[0x0065]="LiveOP_ShopPlayerBuy";
	opcode_map[0x006a]="LiveOP_ShopPlayerSell";
	opcode_map[0x006d]="LiveOP_ShopDelItem";
	opcode_map[0x0f6d]="LiveOP_ShopEndConfirm";
	opcode_map[0x00f7]="LiveOP_ShopRequest";
	opcode_map[0x006c]="LiveOP_ShopEnd";
	opcode_map[0x02d1]="LiveOP_AdventureMerchantRequest";
	opcode_map[0x02d2]="LiveOP_AdventureMerchantResponse";
	opcode_map[0x02d3]="LiveOP_AdventureMerchantPurchase";
	opcode_map[0x02e3]="LiveOP_AdventurePointsUpdate";
	opcode_map[0x0270]="LiveOP_LFGCommand";
	opcode_map[0x01d0]="LiveOP_LFGAppearance";
	opcode_map[0x01b5]="LiveOP_MoneyUpdate";
	opcode_map[0x0721]="LiveOP_GroupDelete";
	opcode_map[0x0272]="LiveOP_GroupAcknowledge";
	opcode_map[0x024a]="LiveOP_GroupUpdate";
	opcode_map[0x025f]="LiveOP_GroupInvite";
	opcode_map[0x00ff]="LiveOP_GroupDisband";
	opcode_map[0x00d5]="LiveOP_GroupInvite2";
	opcode_map[0x025e]="LiveOP_GroupFollow";
	opcode_map[0x00d7]="LiveOP_GroupFollow2";
	opcode_map[0x00d6]="LiveOP_GroupCancelInvite";
	opcode_map[0x0156]="LiveOP_Split";
	opcode_map[0x00d8]="LiveOP_Jump";
	opcode_map[0x01d6]="LiveOP_ConsiderCorpse";
	opcode_map[0x0064]="LiveOP_SkillUpdate";
	opcode_map[0x0178]="LiveOP_GMEndTrainingResponse";
	opcode_map[0x013c]="LiveOP_GMEndTraining";
	opcode_map[0x0175]="LiveOP_GMTrainSkill";
	opcode_map[0x013b]="LiveOP_GMTraining";
	opcode_map[0x017b]="LiveOP_ConsumeAmmo";
	opcode_map[0x0171]="LiveOP_CombatAbility";
	opcode_map[0x009c]="LiveOP_TrackUnknown";
	opcode_map[0x0234]="LiveOP_TrackTarget";
	opcode_map[0x0286]="LiveOP_Track";
	opcode_map[0x0297]="LiveOP_ReadBook";
	opcode_map[0x001f]="LiveOP_ItemLinkClick";
	opcode_map[0x01f4]="LiveOP_ItemLinkResponse";
	opcode_map[0x01d9]="LiveOP_ItemLinkText";
	opcode_map[0x0a41]="LiveOP_RezzRequest";
	opcode_map[0x00e5]="LiveOP_RezzAnswer";
	opcode_map[0x019b]="LiveOP_RezzComplete";
	opcode_map[0x0128]="LiveOP_MoveDoor";
	opcode_map[0x0127]="LiveOP_ClickDoor";
	opcode_map[0x0247]="LiveOP_SendZonepoints";
	opcode_map[0x008c]="LiveOP_SetRunMode";
	opcode_map[0x0248]="LiveOP_InspectRequest";
	opcode_map[0x0249]="LiveOP_InspectAnswer";
	opcode_map[0x0187]="LiveOP_SenseTraps";
	opcode_map[0x018e]="LiveOP_DisarmTraps";
	opcode_map[0x01bc]="LiveOP_Assist";
	opcode_map[0x0240]="LiveOP_PickPocket";
	opcode_map[0x0119]="LiveOP_LootRequest";
	opcode_map[0x011a]="LiveOP_EndLootRequest";
	opcode_map[0x011b]="LiveOP_MoneyOnCorpse";
	opcode_map[0x0179]="LiveOP_LootComplete";
	opcode_map[0x013f]="LiveOP_LootItem";
	opcode_map[0x0151]="LiveOP_MoveItem";
	opcode_map[0x0056]="LiveOP_WhoAllRequest";
	opcode_map[0x0229]="LiveOP_WhoAllResponse";
	opcode_map[0x0167]="LiveOP_Consume";
	opcode_map[0x0172]="LiveOP_AutoAttack";
	opcode_map[0x0186]="LiveOP_AutoAttack2";
	opcode_map[0x0173]="LiveOP_TargetMouse";
	opcode_map[0x01ba]="LiveOP_TargetCommand";
	opcode_map[0x01d8]="LiveOP_TargetReject";
	opcode_map[0x009e]="LiveOP_Hide";
	opcode_map[0x012e]="LiveOP_Forage";
	opcode_map[0x0077]="LiveOP_Fishing";
	opcode_map[0x0246]="LiveOP_Bug";
	opcode_map[0x00f2]="LiveOP_Emote";
	opcode_map[0x0140]="LiveOP_EmoteAnim";
	opcode_map[0x015c]="LiveOP_Consider";
	opcode_map[0x01cb]="LiveOP_FaceChange";
	opcode_map[0x0197]="LiveOP_RandomReq";
	opcode_map[0x0087]="LiveOP_RandomReply";
	opcode_map[0x01c3]="LiveOP_Camp";
	opcode_map[0x0192]="LiveOP_YellForHelp";
	opcode_map[0x00ef]="LiveOP_SafePoint";
	opcode_map[0x0157]="LiveOP_Buff";
	opcode_map[0x00c0]="LiveOP_BuffFadeMsg";
	opcode_map[0x0440]="LiveOP_MultiLineMsg";
	opcode_map[0x021c]="LiveOP_SpecialMesg";
	opcode_map[0x0013]="LiveOP_Consent";
	opcode_map[0x029d]="LiveOP_ConsentResponse";
	opcode_map[0x02d4]="LiveOP_Deny";
	opcode_map[0x016c]="LiveOP_Stun";
	opcode_map[0x0021]="LiveOP_BeginCast";
	opcode_map[0x00be]="LiveOP_CastSpell";
	opcode_map[0x01a8]="LiveOP_InterruptCast";
	opcode_map[0x0105]="LiveOP_Death";
	opcode_map[0x023f]="LiveOP_FeignDeath";
	opcode_map[0x012b]="LiveOP_Illusion";
	opcode_map[0x0078]="LiveOP_LevelUpdate";
	opcode_map[0x0371]="LiveOP_LevelAppearance";
	opcode_map[0x00c2]="LiveOP_MemorizeSpell";
	opcode_map[0x0244]="LiveOP_HPUpdate";
	opcode_map[0x022e]="LiveOP_SendHPTarget";
	opcode_map[0x007d]="LiveOP_Mend";
	opcode_map[0x0160]="LiveOP_Taunt";
	opcode_map[0x0199]="LiveOP_GMDelCorpse";
	opcode_map[0x0047]="LiveOP_GMFind";
	opcode_map[0x0020]="LiveOP_GMServers";
	opcode_map[0x010b]="LiveOP_GMGoto";
	opcode_map[0x028c]="LiveOP_GMSummon";
	opcode_map[0x010a]="LiveOP_GMKick";
	opcode_map[0x0109]="LiveOP_GMKill";
	opcode_map[0x0b40]="LiveOP_GMNameChange";
	opcode_map[0x00a3]="LiveOP_GMLastName";
	opcode_map[0x01b3]="LiveOP_GMToggle";
	opcode_map[0x028f]="LiveOP_GMEmoteZone";
	opcode_map[0x0074]="LiveOP_GMBecomeNPC";
	opcode_map[0x00de]="LiveOP_GMHideMe";
	opcode_map[0x0184]="LiveOP_GMZoneRequest";
	opcode_map[0x0239]="LiveOP_GMZoneRequest2";
	opcode_map[0x0068]="LiveOP_Petition";
	opcode_map[0x0085]="LiveOP_PetitionRefresh";
	opcode_map[0x01ee]="LiveOP_PDeletePetition";
	opcode_map[0x0092]="LiveOP_PetitionBug";
	opcode_map[0x0069]="LiveOP_PetitionUpdate";
	opcode_map[0x0076]="LiveOP_PetitionCheckout";
	opcode_map[0x0056]="LiveOP_PetitionCheckout2";
	opcode_map[0x0091]="LiveOP_PetitionDelete";
	opcode_map[0x02b4]="LiveOP_PetitionResolve";
	opcode_map[0x007e]="LiveOP_PetitionCheckIn";
	opcode_map[0x0090]="LiveOP_PetitionUnCheckout";
	opcode_map[0x01ec]="LiveOP_PetitionQue";
	opcode_map[0x01bb]="LiveOP_SetServerFilter";
	opcode_map[0x0218]="LiveOP_NewSpawn";
	opcode_map[0x0140]="LiveOP_Animation";
	opcode_map[0x0142]="LiveOP_ZoneChange";
	opcode_map[0x00f3]="LiveOP_DeleteSpawn";
	opcode_map[0x0265]="LiveOP_CrashDump";
	opcode_map[0x00e8]="LiveOP_EnvDamage";
	opcode_map[0x0101]="LiveOP_Action";
	opcode_map[0x00e2]="LiveOP_Damage";
	opcode_map[0x00bf]="LiveOP_ManaChange";
	opcode_map[0x027c]="LiveOP_ClientError";
	opcode_map[0x00fb]="LiveOP_Save";
	opcode_map[0x0316]="LiveOP_LocInfo";
	opcode_map[0x0188]="LiveOP_Surname";
	opcode_map[0x018f]="LiveOP_SwapSpell";
	opcode_map[0x01db]="LiveOP_DeleteSpell";
	opcode_map[0x029f]="LiveOP_CloseContainer";
	opcode_map[0x029f]="LiveOP_ClickObjectAck";
	opcode_map[0x00fa]="LiveOP_CreateObject";
	opcode_map[0x00f9]="LiveOP_ClickObject";
	opcode_map[0x01c1]="LiveOP_ClearObject";
	opcode_map[0x0265]="LiveOP_ZoneUnavail";
	opcode_map[0x02e0]="LiveOP_ItemPacket";
	opcode_map[0x029a]="LiveOP_TradeRequest";
	opcode_map[0x0037]="LiveOP_TradeRequestAck";
	opcode_map[0x002d]="LiveOP_TradeAcceptClick";
	opcode_map[0x0162]="LiveOP_TradeMoneyUpdate";
	opcode_map[0x0036]="LiveOP_TradeCoins";
	opcode_map[0x002e]="LiveOP_CancelTrade";
	opcode_map[0x002f]="LiveOP_FinishTrade";
	opcode_map[0x00a1]="LiveOP_SaveOnZoneReq";
	opcode_map[0x0185]="LiveOP_Logout";
	opcode_map[0x0298]="LiveOP_RequestDuel";
	opcode_map[0x0a5d]="LiveOP_DuelResponse";
	opcode_map[0x016e]="LiveOP_DuelResponse2";
	opcode_map[0x007c]="LiveOP_InstillDoubt";
	opcode_map[0x00ac]="LiveOP_SafeFallSuccess";
	opcode_map[0x02fb]="LiveOP_DisciplineUpdate";
	opcode_map[0x02f2]="LiveOP_TributeUpdate";
	opcode_map[0x02f3]="LiveOP_TributeItem";
	opcode_map[0x02f4]="LiveOP_TributePointUpdate";
	opcode_map[0x02f5]="LiveOP_SendTributes";
	opcode_map[0x02f6]="LiveOP_TributeInfo";
	opcode_map[0x02f7]="LiveOP_SelectTribute";
	opcode_map[0x02f8]="LiveOP_TributeTimer";
	opcode_map[0x02f9]="LiveOP_StartTribute";
	opcode_map[0x02fa]="LiveOP_TributeNPC";
	opcode_map[0x02fe]="LiveOP_TributeMoney";
	opcode_map[0x0364]="LiveOP_TributeToggle";
	opcode_map[0x0322]="LiveOP_RecipesFavorite";
	opcode_map[0x01f9]="LiveOP_RecipesSearch";
	opcode_map[0x01fa]="LiveOP_RecipeReply";
	opcode_map[0x01fb]="LiveOP_RecipeDetails";
	opcode_map[0x01fc]="LiveOP_RecipeAutoCombine";
	opcode_map[0x02db]="LiveOP_FindPersonRequest";
	opcode_map[0x02dc]="LiveOP_FindPersonReply";
	opcode_map[0x01dd]="LiveOP_Shielding";
	opcode_map[0x0198]="LiveOP_SetDataRate";
	opcode_map[0x023b]="LiveOP_ZoneEntry";
	opcode_map[0x006b]="LiveOP_PlayerProfile";
	opcode_map[0x0291]="LiveOP_CharInventory";
	opcode_map[0x0170]="LiveOP_ZoneSpawns";
	opcode_map[0x0026]="LiveOP_TimeOfDay";
	opcode_map[0x015b]="LiveOP_Weather";
	opcode_map[0x00ec]="LiveOP_ReqNewZone";
	opcode_map[0x00eb]="LiveOP_NewZone";
	opcode_map[0x00fd]="LiveOP_ReqClientSpawn";
	opcode_map[0x012F]="LiveOP_SpawnAppearance";
	opcode_map[0x0086]="LiveOP_ClientReady";
	opcode_map[0x0086]="LiveOP_ZoneComplete";
	opcode_map[0x02db]="LiveOP_LoginComplete";
	opcode_map[0x0195]="LiveOP_ApproveWorld";
	opcode_map[0x035f]="LiveOP_LogServer";
	opcode_map[0x01b2]="LiveOP_MOTD";
	opcode_map[0x0251]="LiveOP_SendLoginInfo";
	opcode_map[0x00ea]="LiveOP_DeleteCharacter";
	opcode_map[0x0102]="LiveOP_SendCharInfo";
	opcode_map[0x00e1]="LiveOP_ExpansionInfo";
	opcode_map[0x0104]="LiveOP_CharacterCreate";
	opcode_map[0x02ab]="LiveOP_RandomNameGenerator";
	opcode_map[0x005d]="LiveOP_GuildsList";
	opcode_map[0x0125]="LiveOP_ApproveName";
	opcode_map[0x0261]="LiveOP_EnterWorld";
	opcode_map[0x015a]="LiveOP_World_Client_CRC1";
	opcode_map[0x015e]="LiveOP_World_Client_CRC2";
	opcode_map[0x0269]="LiveOP_SetChatServer";
	opcode_map[0x0264]="LiveOP_ZoneServerInfo";
	opcode_map[0x0017]="LiveOP_AckPacket";
	opcode_map[0x012c]="LiveOP_WearChange";
	opcode_map[0x1FA1]="LiveOP_WorldObjectsSent";
	opcode_map[0x39C4]="LiveOP_BlockedBuffs";
	opcode_map[0x4656]="LiveOP_SpawnPositionUpdate";
	opcode_map[0x4b61]="LiveOP_ManaUpdate";
	opcode_map[0x02d6]="LiveOP_EnduranceUpdate";
	opcode_map[0x2ac1]="LiveOP_MobManaUpdate";
	opcode_map[0x6c5f]="LiveOP_MobEnduranceUpdate";
	opcode_map[0x73a8]="LiveOP_SendMaxCharacters";
}
