	void Handle_Connect_OP_SetDataRate(const EQApplicationPacket *app);
	void Handle_Connect_OP_ZoneEntry(const EQApplicationPacket *app);
	void Handle_Connect_OP_SetServerFilter(const EQApplicationPacket *app);
	void Handle_Connect_OP_SendAATable(const EQApplicationPacket *app);
	void Handle_Connect_OP_SendTributes(const EQApplicationPacket *app);
	void Handle_Connect_OP_SendGuildTributes(const EQApplicationPacket *app);
	void Handle_Connect_OP_SendAAStats(const EQApplicationPacket *app);
	void Handle_Connect_0x3e33(const EQApplicationPacket *app);
	void Handle_Connect_OP_ReqClientSpawn(const EQApplicationPacket *app);
	void Handle_Connect_OP_SendExpZonein(const EQApplicationPacket *app);
	void Handle_Connect_OP_ZoneComplete(const EQApplicationPacket *app);
	void Handle_Connect_OP_ReqNewZone(const EQApplicationPacket *app);
	void Handle_Connect_OP_SpawnAppearance(const EQApplicationPacket *app);
	void Handle_Connect_OP_WearChange(const EQApplicationPacket *app);
	void Handle_Connect_OP_ClientUpdate(const EQApplicationPacket *app);
	void Handle_Connect_OP_ClientError(const EQApplicationPacket *app);
	void Handle_Connect_OP_ApproveZone(const EQApplicationPacket *app);
	void Handle_Connect_OP_ClientReady(const EQApplicationPacket *app);
	void Handle_Connect_OP_UpdateAA(const EQApplicationPacket *app);
	void Handle_Connect_OP_TGB(const EQApplicationPacket *app);
	void Handle_OP_ClientUpdate(const EQApplicationPacket *app);
	void Handle_OP_AutoAttack(const EQApplicationPacket *app);
	void Handle_OP_AutoAttack2(const EQApplicationPacket *app);
	void Handle_OP_Consent(const EQApplicationPacket *app);
	void Handle_OP_ConsentDeny(const EQApplicationPacket *app);
	void Handle_OP_TargetMouse(const EQApplicationPacket *app);
	void Handle_OP_TargetCommand(const EQApplicationPacket *app);
	void Handle_OP_Shielding(const EQApplicationPacket *app);
	void Handle_OP_Jump(const EQApplicationPacket *app);
	void Handle_OP_AdventureInfoRequest(const EQApplicationPacket *app);
	void Handle_OP_AdventureRequest(const EQApplicationPacket *app);
	void Handle_OP_LDoNButton(const EQApplicationPacket *app);
	void Handle_OP_LeaveAdventure(const EQApplicationPacket *app);
	void Handle_OP_Consume(const EQApplicationPacket *app);
	void Handle_OP_AdventureMerchantRequest(const EQApplicationPacket *app);
	void Handle_OP_AdventureMerchantPurchase(const EQApplicationPacket *app);
	void Handle_OP_ConsiderCorpse(const EQApplicationPacket *app);
	void Handle_OP_Consider(const EQApplicationPacket *app);
	void Handle_OP_Begging(const EQApplicationPacket *app);
	void Handle_OP_TestBuff(const EQApplicationPacket *app);
	void Handle_OP_Surname(const EQApplicationPacket *app);
	void Handle_OP_YellForHelp(const EQApplicationPacket *app);
	void Handle_OP_Assist(const EQApplicationPacket *app);
	void Handle_OP_GMTraining(const EQApplicationPacket *app);
	void Handle_OP_GMEndTraining(const EQApplicationPacket *app);
	void Handle_OP_GMTrainSkill(const EQApplicationPacket *app);
	void Handle_OP_DuelResponse(const EQApplicationPacket *app);
	void Handle_OP_DuelResponse2(const EQApplicationPacket *app);
	void Handle_OP_RequestDuel(const EQApplicationPacket *app);
	void Handle_OP_SpawnAppearance(const EQApplicationPacket *app);
	void Handle_OP_BazaarInspect(const EQApplicationPacket *app);
	void Handle_OP_Death(const EQApplicationPacket *app);
	void Handle_OP_MoveCoin(const EQApplicationPacket *app);
	void Handle_OP_ItemLinkClick(const EQApplicationPacket *app);
	void Handle_OP_ItemLinkResponse(const EQApplicationPacket *app);
	void Handle_OP_MoveItem(const EQApplicationPacket *app);
	void Handle_OP_Camp(const EQApplicationPacket *app);
	void Handle_OP_Logout(const EQApplicationPacket *app);
	void Handle_OP_SenseHeading(const EQApplicationPacket *app);
	void Handle_OP_LDoNOpen(const EQApplicationPacket *app);
	void Handle_OP_FeignDeath(const EQApplicationPacket *app);
	void Handle_OP_Sneak(const EQApplicationPacket *app);
	void Handle_OP_Hide(const EQApplicationPacket *app);
	void Handle_OP_ChannelMessage(const EQApplicationPacket *app);
	void Handle_OP_WearChange(const EQApplicationPacket *app);
	void Handle_OP_ZoneChange(const EQApplicationPacket *app);
	void Handle_OP_DeleteSpawn(const EQApplicationPacket *app);
	void Handle_OP_SaveOnZoneReq(const EQApplicationPacket *app);
	void Handle_OP_Save(const EQApplicationPacket *app);
	void Handle_OP_WhoAllRequest(const EQApplicationPacket *app);
	void Handle_OP_GMZoneRequest(const EQApplicationPacket *app);
	void Handle_OP_GMZoneRequest2(const EQApplicationPacket *app);
	void Handle_OP_EndLootRequest(const EQApplicationPacket *app);
	void Handle_OP_LootRequest(const EQApplicationPacket *app);
	void Handle_OP_Dye(const EQApplicationPacket *app);
	void Handle_OP_LootItem(const EQApplicationPacket *app);
	void Handle_OP_GuildDelete(const EQApplicationPacket *app);
	void Handle_OP_GuildPublicNote(const EQApplicationPacket *app);
	void Handle_OP_GetGuildsList(const EQApplicationPacket *app);
	void Handle_OP_SetGuildMOTD(const EQApplicationPacket *app);
	void Handle_OP_GuildPeace(const EQApplicationPacket *app);
	void Handle_OP_GuildWar(const EQApplicationPacket *app);
	void Handle_OP_GuildLeader(const EQApplicationPacket *app);
	void Handle_OP_GuildDemote(const EQApplicationPacket *app);
	void Handle_OP_GuildInvite(const EQApplicationPacket *app);
	void Handle_OP_GuildRemove(const EQApplicationPacket *app);
	void Handle_OP_GetGuildMOTD(const EQApplicationPacket *app);
	void Handle_OP_GuildManageBanker(const EQApplicationPacket *app);
	void Handle_OP_GuildInviteAccept(const EQApplicationPacket *app);
	void Handle_OP_ManaChange(const EQApplicationPacket *app);
	void Handle_OP_MemorizeSpell(const EQApplicationPacket *app);
	void Handle_OP_SwapSpell(const EQApplicationPacket *app);
	void Handle_OP_CastSpell(const EQApplicationPacket *app);
	void Handle_OP_DeleteItem(const EQApplicationPacket *app);
	void Handle_OP_CombatAbility(const EQApplicationPacket *app);
	void Handle_OP_Taunt(const EQApplicationPacket *app);
	void Handle_OP_InstillDoubt(const EQApplicationPacket *app);
	void Handle_OP_RezzAnswer(const EQApplicationPacket *app);
	void Handle_OP_GMSummon(const EQApplicationPacket *app);
	void Handle_OP_TradeRequest(const EQApplicationPacket *app);
	void Handle_OP_TradeRequestAck(const EQApplicationPacket *app);
	void Handle_OP_CancelTrade(const EQApplicationPacket *app);
	void Handle_OP_TradeAcceptClick(const EQApplicationPacket *app);
	void Handle_OP_BoardBoat(const EQApplicationPacket *app);
	void Handle_OP_LeaveBoat(const EQApplicationPacket *app);
	void Handle_OP_RandomReq(const EQApplicationPacket *app);
	void Handle_OP_Buff(const EQApplicationPacket *app);
	void Handle_OP_GMHideMe(const EQApplicationPacket *app);
	void Handle_OP_GMNameChange(const EQApplicationPacket *app);
	void Handle_OP_GMKill(const EQApplicationPacket *app);
	void Handle_OP_GMLastName(const EQApplicationPacket *app);
	void Handle_OP_GMToggle(const EQApplicationPacket *app);
	void Handle_OP_LFGCommand(const EQApplicationPacket *app);
	void Handle_OP_GMGoto(const EQApplicationPacket *app);
	void Handle_OP_TraderShop(const EQApplicationPacket *app);
	void Handle_OP_ShopRequest(const EQApplicationPacket *app);
	void Handle_OP_Bazaar(const EQApplicationPacket *app);
	void Handle_OP_ShopPlayerBuy(const EQApplicationPacket *app);
	void Handle_OP_ShopPlayerSell(const EQApplicationPacket *app);
	void Handle_OP_ShopEnd(const EQApplicationPacket *app);
//	void Handle_OP_CloseContainer(const EQApplicationPacket *app);
	void Handle_OP_ClickObjectAction(const EQApplicationPacket *app);
	void Handle_OP_ClickObject(const EQApplicationPacket *app);
	void Handle_OP_RecipesFavorite(const EQApplicationPacket *app);
	void Handle_OP_RecipesSearch(const EQApplicationPacket *app);
	void Handle_OP_RecipeDetails(const EQApplicationPacket *app);
	void Handle_OP_RecipeAutoCombine(const EQApplicationPacket *app);
	void Handle_OP_TradeSkillCombine(const EQApplicationPacket *app);
	void Handle_OP_ItemName(const EQApplicationPacket *app);
	void Handle_OP_AugmentItem(const EQApplicationPacket *app);
	void Handle_OP_ClickDoor(const EQApplicationPacket *app);
	void Handle_OP_CreateObject(const EQApplicationPacket *app);
	void Handle_OP_FaceChange(const EQApplicationPacket *app);
	void Handle_OP_GroupInvite(const EQApplicationPacket *app);
	void Handle_OP_GroupInvite2(const EQApplicationPacket *app);
	void Handle_OP_GroupAcknowledge(const EQApplicationPacket *app);
	void Handle_OP_GroupCancelInvite(const EQApplicationPacket *app);
	void Handle_OP_GroupFollow(const EQApplicationPacket *app);
	void Handle_OP_GroupFollow2(const EQApplicationPacket *app);
	void Handle_OP_GroupDisband(const EQApplicationPacket *app);
	void Handle_OP_GroupDelete(const EQApplicationPacket *app);
	void Handle_OP_GMEmoteZone(const EQApplicationPacket *app);
	void Handle_OP_InspectRequest(const EQApplicationPacket *app);
	void Handle_OP_InspectAnswer(const EQApplicationPacket *app);
	void Handle_OP_Medding(const EQApplicationPacket *app);
	void Handle_OP_DeleteSpell(const EQApplicationPacket *app);
	void Handle_OP_PetitionBug(const EQApplicationPacket *app);
	void Handle_OP_Bug(const EQApplicationPacket *app);
	void Handle_OP_Petition(const EQApplicationPacket *app);
	void Handle_OP_PetitionCheckIn(const EQApplicationPacket *app);
	void Handle_OP_PetitionResolve(const EQApplicationPacket *app);
	void Handle_OP_PetitionDelete(const EQApplicationPacket *app);
	void Handle_OP_PetCommands(const EQApplicationPacket *app);
	void Handle_OP_PetitionUnCheckout(const EQApplicationPacket *app);
	void Handle_OP_PetitionQue(const EQApplicationPacket *app);
	void Handle_OP_PDeletePetition(const EQApplicationPacket *app);
	void Handle_OP_PetitionCheckout(const EQApplicationPacket *app);
	void Handle_OP_PetitionRefresh(const EQApplicationPacket *app);
	void Handle_OP_ReadBook(const EQApplicationPacket *app);
	void Handle_OP_Emote(const EQApplicationPacket *app);
	void Handle_OP_Animation(const EQApplicationPacket *app);
	void Handle_OP_SetServerFilter(const EQApplicationPacket *app);
	void Handle_OP_GMDelCorpse(const EQApplicationPacket *app);
	void Handle_OP_GMKick(const EQApplicationPacket *app);
	void Handle_OP_GMServers(const EQApplicationPacket *app);
	void Handle_OP_Illusion(const EQApplicationPacket *app);
	void Handle_OP_GMBecomeNPC(const EQApplicationPacket *app);
	void Handle_OP_Fishing(const EQApplicationPacket *app);
	void Handle_OP_Forage(const EQApplicationPacket *app);
	void Handle_OP_Mend(const EQApplicationPacket *app);
	void Handle_OP_EnvDamage(const EQApplicationPacket *app);
	void Handle_OP_Damage(const EQApplicationPacket *app);
	void Handle_OP_AAAction(const EQApplicationPacket *app);
	void Handle_OP_TraderBuy(const EQApplicationPacket *app);
	void Handle_OP_Trader(const EQApplicationPacket *app);
	void Handle_OP_GMFind(const EQApplicationPacket *app);
	void Handle_OP_PickPocket(const EQApplicationPacket *app);
	void Handle_OP_Bind_Wound(const EQApplicationPacket *app);
	void Handle_OP_TrackTarget(const EQApplicationPacket *app);
	void Handle_OP_Track(const EQApplicationPacket *app);
	void Handle_OP_TrackUnknown(const EQApplicationPacket *app);
	void Handle_0x0193(const EQApplicationPacket *app);
	void Handle_0x01e7(const EQApplicationPacket *app);
	void Handle_OP_ClientError(const EQApplicationPacket *app);
	void Handle_OP_ReloadUI(const EQApplicationPacket *app);
	void Handle_OP_TGB(const EQApplicationPacket *app);
	void Handle_OP_Split(const EQApplicationPacket *app);
	void Handle_OP_SenseTraps(const EQApplicationPacket *app);
	void Handle_OP_DisarmTraps(const EQApplicationPacket *app);
	void Handle_OP_OpenTributeMaster(const EQApplicationPacket *app);
	void Handle_OP_OpenGuildTributeMaster(const EQApplicationPacket *app);
	void Handle_OP_TributeItem(const EQApplicationPacket *app);
	void Handle_OP_TributeMoney(const EQApplicationPacket *app);
	void Handle_OP_SelectTribute(const EQApplicationPacket *app);
	void Handle_OP_TributeUpdate(const EQApplicationPacket *app);
	void Handle_OP_TributeToggle(const EQApplicationPacket *app);
	void Handle_OP_TributeNPC(const EQApplicationPacket *app);
	void Handle_OP_ConfirmDelete(const EQApplicationPacket *app);
	void Handle_OP_CrashDump(const EQApplicationPacket *app);
	void Handle_OP_ControlBoat(const EQApplicationPacket *app);
	void Handle_OP_DumpName(const EQApplicationPacket *app);
	void Handle_OP_SetRunMode(const EQApplicationPacket *app);
	void Handle_OP_SafeFallSuccess(const EQApplicationPacket *app);
	void Handle_OP_Heartbeat(const EQApplicationPacket *app);
	void Handle_OP_SafePoint(const EQApplicationPacket *app);
	void Handle_OP_FindPersonRequest(const EQApplicationPacket *app);
	void Handle_OP_BankerChange(const EQApplicationPacket *app);
	void Handle_OP_LeadershipExpToggle(const EQApplicationPacket *app);
	void Handle_OP_SetTitle(const EQApplicationPacket *app);
	void Handle_OP_RequestTitles(const EQApplicationPacket *app);
	void Handle_OP_PurchaseLeadershipAA(const EQApplicationPacket *app);
	void Handle_OP_Ignore(const EQApplicationPacket *app);
	void Handle_OP_LoadSpellSet(const EQApplicationPacket *app);
	void Handle_OP_AutoFire(const EQApplicationPacket *app);
	void Handle_OP_Rewind(const EQApplicationPacket *app);
	void Handle_OP_RaidCommand(const EQApplicationPacket *app);
 	void Handle_OP_Translocate(const EQApplicationPacket *app);
 	void Handle_OP_Sacrifice(const EQApplicationPacket *app);
	void Handle_OP_AcceptNewTask(const EQApplicationPacket *app);
	void Handle_OP_CancelTask(const EQApplicationPacket *app);
	void Handle_OP_TaskHistoryRequest(const EQApplicationPacket *app);
	void Handle_OP_KeyRing(const EQApplicationPacket *app); 
	void Handle_OP_FriendsWho(const EQApplicationPacket *app);
	void Handle_OP_Bandolier(const EQApplicationPacket *app);
	void Handle_OP_PopupResponse(const EQApplicationPacket *app);
	void Handle_OP_PotionBelt(const EQApplicationPacket *app);
	void Handle_OP_LFGGetMatchesRequest(const EQApplicationPacket *app);
	void Handle_OP_LFPCommand(const EQApplicationPacket *app);
	void Handle_OP_LFPGetMatchesRequest(const EQApplicationPacket *app);

