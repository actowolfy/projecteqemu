ALTER TABLE `npc_types`  ADD COLUMN `attack_count` SMALLINT NOT NULL DEFAULT '-1' AFTER `maxdmg`;
ALTER TABLE `npc_types`  ADD COLUMN `mana` INT(11) NOT NULL DEFAULT '0' AFTER `hp`;