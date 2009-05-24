CREATE TABLE `instance_lockout` (
  `id` int(11) NOT NULL auto_increment,
  `zone` int(11) unsigned NOT NULL default '0',
  `version` tinyint(4) unsigned NOT NULL default '0',
  `start_time` int(11) unsigned NOT NULL default '0',
  `duration` int(11) unsigned NOT NULL default '0',
  PRIMARY KEY  (`id`),
  UNIQUE KEY `id` (`id`),
  KEY `id_2` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

CREATE TABLE `instance_lockout_player` (
  `id` int(11) unsigned NOT NULL default '0',
  `charid` int(11) unsigned NOT NULL default '0',
  PRIMARY KEY  (`charid`,`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

ALTER TABLE `respawn_times` ADD `instance_id` SMALLINT DEFAULT '0' NOT NULL AFTER `duration`;
ALTER TABLE `respawn_times` DROP PRIMARY KEY, ADD PRIMARY KEY (`id`, `instance_id`);

ALTER TABLE `character_` ADD `instanceid` SMALLINT UNSIGNED DEFAULT '0' NOT NULL AFTER `zoneid`;
ALTER TABLE `character_` DROP `instZflagNum`;
ALTER TABLE `character_` DROP `instZOrgID`;

ALTER TABLE `spawn2` ADD `version` SMALLINT UNSIGNED DEFAULT '0' NOT NULL AFTER `zone`;

ALTER TABLE `player_corpses` ADD `instanceid` SMALLINT UNSIGNED DEFAULT '0' NOT NULL AFTER `zoneid`;
ALTER TABLE `player_corpses` ADD INDEX `instanceid` (`instanceid`);

ALTER TABLE `traps` ADD INDEX `zone` (`zone`);
ALTER TABLE `traps` ADD `version` SMALLINT UNSIGNED DEFAULT '0' NOT NULL AFTER `zone`;

ALTER TABLE `ground_spawns` ADD INDEX `zone` (`zoneid`);
ALTER TABLE `ground_spawns` ADD `version` SMALLINT UNSIGNED DEFAULT '0' NOT NULL AFTER `zoneid`;

ALTER TABLE `object` ADD INDEX `zone` (`zoneid`);
ALTER TABLE `object` ADD `version` SMALLINT UNSIGNED DEFAULT '0' NOT NULL AFTER `zoneid`;
ALTER TABLE `object` DROP `linked_list_addr_01`;
ALTER TABLE `object` DROP `linked_list_addr_02`;
ALTER TABLE `object` DROP `unknown88`;
DELETE FROM object WHERE object.type=1 AND object.itemid!=0;

ALTER TABLE `doors` ADD `version` SMALLINT UNSIGNED DEFAULT '0' NOT NULL AFTER `zone`;
ALTER TABLE `npc_types` ADD `adventure_template_id` INT UNSIGNED DEFAULT '0' NOT NULL AFTER `npc_faction_id`;

CREATE TABLE `adventure_template` (
  `id` int(10) unsigned NOT NULL,
  `zone` varchar(64) NOT NULL,
  `zone_version` tinyint(3) unsigned NOT NULL default '0',
  `is_hard` tinyint(3) unsigned NOT NULL default '0',
  `is_raid` tinyint(3) unsigned NOT NULL default '0',
  `min_level` tinyint(3) unsigned NOT NULL default '1',
  `max_level` tinyint(3) unsigned NOT NULL default '65',
  `type` tinyint(3) unsigned NOT NULL default '0',
  `type_data` int(10) unsigned NOT NULL default '0',
  `type_count` smallint(5) unsigned NOT NULL default '0',
  `text` varchar(512) NOT NULL,
  `duration` int(10) unsigned NOT NULL default '7200',
  `zone_in_time` int(10) unsigned NOT NULL default '1800',
  `win_points` smallint(5) unsigned NOT NULL default '0',
  `lose_points` smallint(5) unsigned NOT NULL default '0',
  `zone_in_zone_id` smallint(5) unsigned NOT NULL default '0',
  `zone_in_x` float NOT NULL default '0',
  `zone_in_y` float NOT NULL default '0',
  `zone_in_object_id` smallint(4) NOT NULL default '0',
  PRIMARY KEY  (`id`),
  UNIQUE KEY `id` (`id`),
  KEY `id_2` (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

CREATE TABLE `adventure_template_entry` (
  `id` int(10) unsigned NOT NULL,
  `template_id` int(10) unsigned NOT NULL,
  PRIMARY KEY  (`id`,`template_id`),
  KEY `id` (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;