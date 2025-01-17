ALTER TABLE `rule_values` ADD `notes` text NOT NULL AFTER `rule_value`;


UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Character:MaxLevel';
UPDATE `rule_values` SET notes = 'Sets the Max Level attainable via Experience' WHERE rule_name = 'Character:MaxExpLevel';	
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Character:DeathExpLossLevel';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Character:DeathItemLossLevel';
UPDATE `rule_values` SET notes = 'Adjust how much exp is lost' WHERE rule_name = 'Character:DeathExpLossMultiplier';	
UPDATE `rule_values` SET notes = 'Adjust to use the above multiplier or to use code default.' WHERE rule_name = 'Character:UseDeathExpLossMult';	
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Character:CorpseDecayTimeMS';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Character:LeaveCorpses';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Character:LeaveNakedCorpses';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Character:ExpMultiplier';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Character:AAExpMultiplier';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Character:GroupExpMultiplier';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Character:RaidExpMultiplier';
UPDATE `rule_values` SET notes = '0=disabled' WHERE rule_name = 'Character:AutosaveIntervalS';	
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Character:HPRegenMultiplier';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Character:ManaRegenMultiplier';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Character:EnduranceRegenMultiplier';
UPDATE `rule_values` SET notes = 'item\'s hunger restored = this value * item\'s food level:100 = normal:50 = people eat 2x as fast:200 = people eat 2x as slow' WHERE rule_name = 'Character:ConsumptionMultiplier';	
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Character:HealOnLevel';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Character:FeignKillsPet';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Character:ItemManaRegenCap';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Character:ItemHealthRegenCap';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Character:ItemDamageShieldCap';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Character:ItemAccuracyCap';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Character:ItemAvoidanceCap';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Character:ItemCombatEffectsCap';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Character:ItemShieldingCap';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Character:ItemSpellShieldingCap';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Character:ItemDoTShieldingCap';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Character:ItemStunResistCap';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Character:ItemStrikethroughCap';
UPDATE `rule_values` SET notes = 'skill ups are at 100%' WHERE rule_name = 'Character:SkillUpModifier';	
UPDATE `rule_values` SET notes = 'off by default to prevent duping for now' WHERE rule_name = 'Character:SharedBankPlat';	
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Character:BindAnywhere';
UPDATE `rule_values` SET notes = 'Set to >0 to enable rest state bonus HP and mana regen.' WHERE rule_name = 'Character:RestRegenPercent';	 
UPDATE `rule_values` SET notes = 'Time in seconds for rest state regen to kick in.' WHERE rule_name = 'Character:RestRegenTimeToActivate';	 

UPDATE `rule_values` SET notes = 'Max number of members allowed in a single guild' WHERE rule_name = 'Guild:MaxMembers';
UPDATE `rule_values` SET notes = 'Highest skill level that tradeskills can be trained to from GM Trainers' WHERE rule_name = 'Skills:MaxTrainTradeskills';
UPDATE `rule_values` SET notes = 'Range at which a pet will respond to attack commands' WHERE rule_name = 'Pets:AttackCommandRange';
UPDATE `rule_values` SET notes = 'This setting overrides the minstatus setting in the zones table if set' WHERE rule_name = 'GM:MinStatusToZoneAnywhere';

UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'World:ZoneAutobootTimeoutMS';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'World:ClientKeepaliveTimeoutMS';
UPDATE `rule_values` SET notes = 'Toggle whether or not to check incoming client connections against the Banned_IPs table. Set this value to false to disable this feature.' WHERE rule_name = 'World:UseBannedIPsTable';	
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'World:EnableTutorialButton';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'World:EnableReturnHomeButton';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'World:MaxLevelForTutorial';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'World:TutorialZoneID';
UPDATE `rule_values` SET notes = '21600 seconds is 6 Hours' WHERE rule_name = 'World:MinOfflineTimeToReturnHome';	 
UPDATE `rule_values` SET notes = 'Maximum number of clients allowed to connect per IP address if account status is < AddMaxClientsStatus.  Default value: -1 (feature disabled)' WHERE rule_name = 'World:MaxClientsPerIP';	
UPDATE `rule_values` SET notes = 'Exempt accounts from the MaxClientsPerIP and AddMaxClientsStatus rules:if their status is >= this value.  Default value: -1 (feature disabled)' WHERE rule_name = 'World:ExemptMaxClientsStatus';	
UPDATE `rule_values` SET notes = 'Maximum number of clients allowed to connect per IP address if account status is < ExemptMaxClientsStatus.  Default value: -1 (feature disabled)' WHERE rule_name = 'World:AddMaxClientsPerIP';	
UPDATE `rule_values` SET notes = 'Accounts with status >= this rule will be allowed to use the amount of accounts defined in the AddMaxClientsPerIP.  Default value: -1 (feature disabled)' WHERE rule_name = 'World:AddMaxClientsStatus';	
UPDATE `rule_values` SET notes = 'cavedude: Clears temp merchant items when world boots.' WHERE rule_name = 'World:ClearTempMerchantlist';	
UPDATE `rule_values` SET notes = 'Max number of characters allowed on at once from a single account (-1 is disabled)' WHERE rule_name = 'World:AccountSessionLimit'; 	
UPDATE `rule_values` SET notes = 'Min status required to be exempt from multi-session per account limiting (-1 is disabled)' WHERE rule_name = 'World:ExemptAccountLimitStatus'; 	
UPDATE `rule_values` SET notes = 'Check ip list against GM Accounts:AntiHack GM Accounts.' WHERE rule_name = 'World:GMAccountIPList';	 
UPDATE `rule_values` SET notes = 'Minimum GM status to check against AntiHack list' WHERE rule_name = 'World:MinGMAntiHackStatus';	
UPDATE `rule_values` SET notes = 'Sets the Starting Zone for SoF Clients separate from Titanium Clients (-1 is disabled)' WHERE rule_name = 'World:SoFStartZoneID';	

UPDATE `rule_values` SET notes = 'ms between intervals of sending a position update to the entire zone.' WHERE rule_name = 'Zone: NPCGlobalPositionUpdateInterval';	
UPDATE `rule_values` SET notes = 'the time a client remains link dead on the server after a sudden disconnection' WHERE rule_name = 'Zone: ClientLinkdeadMS';	
UPDATE `rule_values` SET notes = 'ms time until a player corpse is moved to a zone\'s graveyard:if one is specified for the zone' WHERE rule_name = 'Zone: GraveyardTimeMS';	
UPDATE `rule_values` SET notes = ' enables or disables the shadowrest zone feature for player corpses. Default is turned off.' WHERE rule_name = 'Zone:EnableShadowrest';	
UPDATE `rule_values` SET notes = 'Required status level to exempt the MQWarpDetector.  Set to -1 to disable this feature.' WHERE rule_name = 'Zone:MQWarpExemptStatus';	
UPDATE `rule_values` SET notes = 'Required status level to exempt the MQZoneDetector.  Set to -1 to disable this feature.' WHERE rule_name = 'Zone:MQZoneExemptStatus';	
UPDATE `rule_values` SET notes = 'Required status level to exempt the MQGateDetector.  Set to -1 to disable this feature.' WHERE rule_name = 'Zone:MQGateExemptStatus';	
UPDATE `rule_values` SET notes = 'Required status level to exempt the MGhostDetector.  Set to -1 to disable this feature.' WHERE rule_name = 'Zone:MQGhostExemptStatus';	
UPDATE `rule_values` SET notes = 'Enable the MQWarp Detector.  Set to False to disable this feature.' WHERE rule_name = 'Zone:EnableMQWarpDetector';	
UPDATE `rule_values` SET notes = 'Enable the MQZone Detector.  Set to False to disable this feature.' WHERE rule_name = 'Zone:EnableMQZoneDetector';	
UPDATE `rule_values` SET notes = 'Enable the MQGate Detector.  Set to False to disable this feature.' WHERE rule_name = 'Zone:EnableMQGateDetector';	
UPDATE `rule_values` SET notes = 'Enable the MQGhost Detector.  Set to False to disable this feature.' WHERE rule_name = 'Zone:EnableMQGhostDetector';	
UPDATE `rule_values` SET notes = 'Distance a player must travel between client to server location updates before a warp is registered.  30 allows for beyond GM speed without lag.' WHERE rule_name = 'Zone:MQWarpDetectorDistance';	
UPDATE `rule_values` SET notes = 'Distance beyond the Zone:MQWarpDetectorDistance that a player must travel within the MQWarpThresholdTimer amount of time before tripping the MQWarp detector.  Set to 0 to disable this feature.' WHERE rule_name = 'Zone:MQWarpLagThreshold';	
UPDATE `rule_values` SET notes = 'Amount of time before the warp_threshold resets to the Zone:MQWarpLagThreshold value.  Default: 90000 (900 seconds/15 minutes).  Set to -1 to disable this feature.' WHERE rule_name = 'Zone:MQWarpThresholdTimer';	
UPDATE `rule_values` SET notes = 'How long a dynamic zone stays loaded while empty' WHERE rule_name = 'Zone:AutoShutdownDelay';	

UPDATE `rule_values` SET notes = 'increases zone boot times a bit to reduce hopping.' WHERE rule_name = 'Map:FixPathingZWhenLoading';		
UPDATE `rule_values` SET notes = 'alternative to `WhenLoading`:accomplishes the same thing but does it at each waypoint instead of once at boot time.' WHERE rule_name = 'Map:FixPathingZAtWaypoints';	
UPDATE `rule_values` SET notes = 'very CPU intensive:but helps hopping with widely spaced waypoints.' WHERE rule_name = 'Map:FixPathingZWhenMoving';		
UPDATE `rule_values` SET notes = 'try to repair Z coords in the SendTo routine as well.' WHERE rule_name = 'Map:FixPathingZOnSendTo';		
UPDATE `rule_values` SET notes = 'at runtime while pathing: max change in Z to allow the BestZ code to apply.' WHERE rule_name = 'Map:FixPathingZMaxDeltaMoving';	
UPDATE `rule_values` SET notes = 'at runtime at each waypoint: max change in Z to allow the BestZ code to apply.' WHERE rule_name = 'Map:FixPathingZMaxDeltaWaypoint';	
UPDATE `rule_values` SET notes = 'at runtime in SendTo: max change in Z to allow the BestZ code to apply.' WHERE rule_name = 'Map:FixPathingZMaxDeltaSendTo';	
UPDATE `rule_values` SET notes = 'while loading each waypoint: max change in Z to allow the BestZ code to apply.' WHERE rule_name = 'Map:FixPathingZMaxDeltaLoading';	

UPDATE `rule_values` SET notes = 'Does not apply BestZ as waypoints are loaded if they are in water' WHERE rule_name = 'Watermap:CheckWaypointsInWaterWhenLoading';	 
UPDATE `rule_values` SET notes = 'Check if a mob has moved into/out of water when at waypoints and sets flymode' WHERE rule_name = 'Watermap:CheckForWaterAtWaypoints'; 		 
UPDATE `rule_values` SET notes = 'Checks if a mob has moved into/out of water each time it\'s loc is recalculated' WHERE rule_name = 'Watermap:CheckForWaterWhenMoving';		 
UPDATE `rule_values` SET notes = 'Checks if a mob has moved into/out of water on SendTo' WHERE rule_name = 'Watermap:CheckForWaterOnSendTo';		 
UPDATE `rule_values` SET notes = 'Only lets a player fish near water (if a water map exists for the zone)' WHERE rule_name = 'Watermap:CheckForWaterWhenFishing';		 
UPDATE `rule_values` SET notes = 'How far in front of player water must be for fishing to work' WHERE rule_name = 'Watermap:FishingRodLength';			 
UPDATE `rule_values` SET notes = 'If water is more than this far below the player:it is considered too far to fish' WHERE rule_name = 'Watermap:FishingLineLength';			 

UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Spells:AutoResistDiff';
UPDATE `rule_values` SET notes = 'chance to resist given no resists and same level' WHERE rule_name = 'Spells:ResistChance';	
UPDATE `rule_values` SET notes = 'multiplier:chance to resist = this * ResistAmount' WHERE rule_name = 'Spells:ResistMod';	
UPDATE `rule_values` SET notes = 'The chance when a spell is resisted that it will partial hit.' WHERE rule_name = 'Spells:PartialHitChance';	
UPDATE `rule_values` SET notes = 'The chance when a fear spell is resisted that it will partial hit.' WHERE rule_name = 'Spells:PartialHitChanceFear';	
UPDATE `rule_values` SET notes = 'base % chance that everyone has to crit a spell' WHERE rule_name = 'Spells:BaseCritChance';	
UPDATE `rule_values` SET notes = 'base % bonus to damage on a successful spell crit. 100 = 2x damage' WHERE rule_name = 'Spells:BaseCritRatio';	
UPDATE `rule_values` SET notes = 'level wizards first get spell crits' WHERE rule_name = 'Spells:WizCritLevel';	
UPDATE `rule_values` SET notes = 'wiz\'s crit chance:on top of BaseCritChance' WHERE rule_name = 'Spells:WizCritChance';	
UPDATE `rule_values` SET notes = 'wiz\'s crit bonus:on top of BaseCritRatio (should be 0 for Live-like)' WHERE rule_name = 'Spells:WizCritRatio';	
UPDATE `rule_values` SET notes = '8.5 resist per level difference.' WHERE rule_name = 'Spells:ResistPerLevelDiff';	
UPDATE `rule_values` SET notes = 'If not zero:time in seconds to accept a Translocate.' WHERE rule_name = 'Spells:TranslocateTimeLimit';	 

UPDATE `rule_values` SET notes = 'The base crit chance for non warriors:NOTE: This will apply to NPCs as well' WHERE rule_name = 'Combat:BaseCritChance';	
UPDATE `rule_values` SET notes = 'The base crit chance for warriors and berserkers:only applies to clients' WHERE rule_name = 'Combat:WarBerBaseCritChance';	
UPDATE `rule_values` SET notes = 'The bonus base crit chance you get when you\'re berserk' WHERE rule_name = 'Combat:BerserkBaseCritChance';	
UPDATE `rule_values` SET notes = 'The level that npcs can KICK/BASH' WHERE rule_name = 'Combat:NPCBashKickLevel';	
UPDATE `rule_values` SET notes = 'The base crit chance for all clients:this will stack with warrior\'s/zerker\'s crit chance.' WHERE rule_name = 'Combat:ClientBaseCritChance';	
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Combat:UseIntervalAC';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Combat:PetAttackMagicLevel';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Combat:EnableFearPathing';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Combat:FleeHPRatio';
UPDATE `rule_values` SET notes = 'If false:mobs won\'t flee if other mobs are in combat with it.' WHERE rule_name = 'Combat:FleeIfNotAlone';	 
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Combat:AdjustProcPerMinute';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Combat:AvgProcsPerMinute';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Combat:ProcPerMinDexContrib';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Combat:BaseProcChance';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Combat:ProcDexDivideBy';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Combat:BaseHitChance';
UPDATE `rule_values` SET notes = 'hit will fall off up to 5% over the initial level range' WHERE rule_name = 'Combat:HitFalloffMinor';	
UPDATE `rule_values` SET notes = 'hit will fall off up to 7% over the three levels after the initial level range' WHERE rule_name = 'Combat:HitFalloffModerate';	
UPDATE `rule_values` SET notes = 'hit will fall off sharply if we\'re outside the minor and moderate range' WHERE rule_name = 'Combat:HitFalloffMajor';	
UPDATE `rule_values` SET notes = 'You gain this % of hit for every level you are above your target' WHERE rule_name = 'Combat:HitBonusPerLevel';	
UPDATE `rule_values` SET notes = 'For every weapon skill point that\'s not maxed you lose this % of hit' WHERE rule_name = 'Combat:WeaponSkillFalloff';	
UPDATE `rule_values` SET notes = 'Archery has a hit penalty to try to help balance it with the plethora of long term +hit modifiers for it' WHERE rule_name = 'Combat:ArcheryHitPenalty';	
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Combat:AgiHitFactor'; 
UPDATE `rule_values` SET notes = 'Minimum Distance to use Ranged Attacks ' WHERE rule_name = 'Combat:MinRangedAttackDist';	

UPDATE `rule_values` SET notes = 'level<55' WHERE rule_name = 'NPC:MinorNPCCorpseDecayTimeMS';	
UPDATE `rule_values` SET notes = 'level>=55' WHERE rule_name = 'NPC:MajorNPCCorpseDecayTimeMS';	
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'NPC:CorpseUnlockTimer';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'NPC:EmptyNPCCorpseDecayTimeMS';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'NPC:UseItemBonusesForNonPets';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'NPC:SayPauseTimeInSec';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'NPC:OOCRegen';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'NPC:BuffFriends';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'NPC:EnableNPCQuestJournal';

UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Aggro:SmartAggroList';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Aggro:SittingAggroMod';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Aggro:MeleeRangeAggroMod';
UPDATE `rule_values` SET notes = '0 will prefer our current target to any other, > 0 makes it harder for our npcs to switch targets.' WHERE rule_name = 'Aggro:CurrentTargetAggroMod';	
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Aggro:CriticallyWoundedAggroMod';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Aggro:SlowAggroMod';
UPDATE `rule_values` SET notes = 'mez:blind:charm etc etc' WHERE rule_name = 'Aggro:IncapacitateAggroMod';	
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Aggro:MovementImpairAggroMod';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Aggro:SpellAggroMod';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Aggro:SongAggroMod';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Aggro:PetSpellAggroMod';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Aggro:StunAggroMod';

UPDATE `rule_values` SET notes = 'Globally enable or disable the Task system' WHERE rule_name = 'TaskSystem:EnableTaskSystem';	 
UPDATE `rule_values` SET notes = 'Seconds between checks for failed tasks. Also used by the \'Touch\' activity' WHERE rule_name = 'TaskSystem:PeriodicCheckTimer';	 
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'TaskSystem:RecordCompletedTasks';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'TaskSystem:RecordCompletedOptionalActivities';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'TaskSystem:KeepOneRecordPerCompletedTask';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'TaskSystem:EnableTaskProximity';

UPDATE `rule_values` SET notes = 'Adjust mana regen for bots:1 is fast and higher numbers slow it down 3 is about the same as players.' WHERE rule_name = 'EQOffline:BotManaRegen';	 
UPDATE `rule_values` SET notes = 'Allow for buffs to complete even if the bot caster is out of mana.  Only affects buffing out of combat.' WHERE rule_name = 'EQOffline:BotFinishBuffing';	 
UPDATE `rule_values` SET notes = 'Number of bots that each account can create' WHERE rule_name = 'EQOffline:CreateBotCount';	 
UPDATE `rule_values` SET notes = 'Number of bots a character can have spawned at one time:You + 71 bots is a 12 group raid' WHERE rule_name = 'EQOffline:SpawnBotCount';	 
UPDATE `rule_values` SET notes = 'Optional quest method to manage bot spawn limits using the quest_globals name bot_spawn_limit:see: /bazaar/Aediles_Thrall.pl' WHERE rule_name = 'EQOffline:BotQuest';	 

UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Chat:ServerWideOOC';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Chat:ServerWideAuction';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Chat:EnableVoiceMacros';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Chat:EnableMailKeyIPVerification';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Chat:EnableAntiSpam';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Chat:MinStatusToBypassAntiSpam';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Chat:MinimumMessagesPerInterval';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Chat:MaximumMessagesPerInterval';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Chat:MaxMessagesBeforeKick';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Chat:IntervalDurationMS';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Chat:KarmaUpdateIntervalMS';

UPDATE `rule_values` SET notes = 'Use faction/charisma price modifiers.' WHERE rule_name = 'Merchant:UsePriceMod';	 
UPDATE `rule_values` SET notes = 'Modifier for NPC sell price.' WHERE rule_name = 'Merchant:SellCostMod';	 
UPDATE `rule_values` SET notes = 'Modifier for NPC buy price.' WHERE rule_name = 'Merchant:BuyCostMod';	 
UPDATE `rule_values` SET notes = 'Determines maximum price bonus from having good faction/CHA. Value is a percent.' WHERE rule_name = 'Merchant:PriceBonusPct';	 
UPDATE `rule_values` SET notes = 'Determines maximum price penalty from having bad faction/CHA. Value is a percent.' WHERE rule_name = 'Merchant:PricePenaltyPct';	 
UPDATE `rule_values` SET notes = 'Determines CHA cap:from 104 CHA. 3.45 is 132 CHA at apprehensive. 0.34 is 400 CHA at apprehensive.' WHERE rule_name = 'Merchant:ChaBonusMod';	 
UPDATE `rule_values` SET notes = 'Determines CHA bottom:up to 102 CHA. 1.52 is 37 CHA at apprehensive. 0.98 is 0 CHA at apprehensive.' WHERE rule_name = 'Merchant:ChaPenaltyMod';	 

UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Bazaar:AuditTrail';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Bazaar:MaxSearchResults';
UPDATE `rule_values` SET notes = 'notation' WHERE rule_name = 'Bazaar:EnableWarpToTrader';
UPDATE `rule_values` SET notes = 'The max results returned in the /barter search' WHERE rule_name = 'Bazaar:MaxBarterSearchResults';	 

UPDATE `rule_values` SET notes = 'If false:client wont bring up the Mail window.' WHERE rule_name = 'Mail:EnableMailSystem';	 
UPDATE `rule_values` SET notes = 'Time in seconds. 0 will delete all messages in the trash when the mailserver starts' WHERE rule_name = 'Mail:ExpireTrash';	 
UPDATE `rule_values` SET notes = '1 Year. Set to -1 for never' WHERE rule_name = 'Mail:ExpireRead';	 
UPDATE `rule_values` SET notes = '1 Year. Set to -1 for never' WHERE rule_name = 'Mail:ExpireUnread';	 

UPDATE `rule_values` SET notes = 'Required status to administer chat channels' WHERE rule_name = 'Channels:RequiredStatusAdmin';	 
UPDATE `rule_values` SET notes = 'Required status to list all chat channels' WHERE rule_name = 'Channels:RequiredStatusListAll';	 
UPDATE `rule_values` SET notes = 'Empty password protected channels will be deleted after this many minutes' WHERE rule_name = 'Channels:DeleteTimer';	 

UPDATE `rule_values` SET notes = 'Record sales from a player to an NPC merchant in eventlog table' WHERE rule_name = 'EventLog:RecordSellToMerchant';	 
UPDATE `rule_values` SET notes = 'Record purchases by a player from an NPC merchant in eventlog table' WHERE rule_name = 'EventLog:RecordBuyFromMerchant';
