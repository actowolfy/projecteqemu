alter table bots
drop column BodyType,
drop column HitPoints,
drop column HitPointsRegenRate,
drop column ManaRegenRate,
drop column RunSpeed,
add column BotCreateDate timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
add column LastSpawnDate datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
add column TotalPlayTime time NOT NULL DEFAULT '00:00:00',
modify column Race smallint(5) NOT NULL DEFAULT 0,
modify column Class tinyint(2) NOT NULL DEFAULT 0,
modify column Gender tinyint(2) NOT NULL DEFAULT 0,
modify column Face int(10) NOT NULL DEFAULT 1,
modify column LuclinHairStyle int(10) NOT NULL DEFAULT 1,
modify column LuclinHairColor int(10) NOT NULL DEFAULT 1,
modify column LuclinEyeColor int(10) NOT NULL DEFAULT 1,
modify column LuclinEyeColor2 int(10) NOT NULL DEFAULT 1,
modify column LuclinBeardColor int(10) NOT NULL DEFAULT 1,
modify column LuclinBeard int(10) NOT NULL DEFAULT 0,
modify column DrakkinHeritage int(10) NOT NULL DEFAULT 0,
modify column DrakkinTattoo int(10) NOT NULL DEFAULT 0,
modify column DrakkinDetails int(10) NOT NULL DEFAULT 0,
modify column STR mediumint(8) NOT NULL DEFAULT 75,
modify column STA mediumint(8) NOT NULL DEFAULT 75,
modify column DEX mediumint(8) NOT NULL DEFAULT 75,
modify column AGI mediumint(8) NOT NULL DEFAULT 75,
modify column _INT mediumint(8) NOT NULL DEFAULT 80,
modify column WIS mediumint(8) NOT NULL DEFAULT 75,
modify column CHA mediumint(8) NOT NULL DEFAULT 75;