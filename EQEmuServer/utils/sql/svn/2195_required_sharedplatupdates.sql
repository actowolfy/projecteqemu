ALTER TABLE `account`
MODIFY COLUMN `sharedplat`  int(11) UNSIGNED NOT NULL DEFAULT 0 AFTER `charname`;