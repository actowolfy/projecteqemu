-- Spell casting fury fix
REPLACE INTO `altadv_vars` (`skill_id`, `name`, `cost`, `max_level`, `hotkey_sid`, `hotkey_sid2`, `title_sid`, `desc_sid`, `type`, `spellid`, `prereq_skill`, `prereq_minpoints`, `spell_type`, `spell_refresh`, `classes`, `berserker`, `class_type`, `cost_inc`, `aa_expansion`, `special_category`, `sof_type`, `sof_cost_inc`, `sof_max_level`, `sof_next_skill`, `clientver`, `account_time_required`, `sof_current_level`,`sof_next_id`,`level_inc`) VALUES ('92', 'Spell Casting Fury', '2', '3', '4294967295', '4294967295', '13544', '13545', '2', '4294967295', '0', '0', '0', '0', '64892', '0', '55', '2', '3', '			4294967295', '2', '0', '3', '92', '1', '0', '0', '0', '0');

REPLACE INTO `altadv_vars` (`skill_id`, `name`, `cost`, `max_level`, `hotkey_sid`, `hotkey_sid2`, `title_sid`, `desc_sid`, `type`, `spellid`, `prereq_skill`, `prereq_minpoints`, `spell_type`, `spell_refresh`, `classes`, `berserker`, `class_type`, `cost_inc`, `aa_expansion`, `special_category`, `sof_type`, `sof_cost_inc`, `sof_max_level`, `sof_next_skill`, `clientver`, `account_time_required`, `sof_current_level`,`sof_next_id`,`level_inc`) VALUES ('637', 'Fury of Magic', '3', '3', '4294967295', '4294967295', '5738', '5739', '5', '4294967295', '92', '3', '0', '0', '27716', '0', '61', '3', '4', '				4294967295', '2', '0', '6', '637', '1', '0', '0', '770', '0');

REPLACE INTO `altadv_vars` (`skill_id`, `name`, `cost`, `max_level`, `hotkey_sid`, `hotkey_sid2`, `title_sid`, `desc_sid`, `type`, `spellid`, `prereq_skill`, `prereq_minpoints`, `spell_type`, `spell_refresh`, `classes`, `berserker`, `class_type`, `cost_inc`, `aa_expansion`, `special_category`, `sof_type`, `sof_cost_inc`, `sof_max_level`, `sof_next_skill`, `clientver`, `account_time_required`, `sof_current_level`,`sof_next_id`,`level_inc`) VALUES  ('770', 'Fury of Magic Mastery', '3', '3', '4294967295', '4294967295', '4294967295', '4294967295', '6', '0', '637', '3', '0', '0', '27716', '0', '65', '3', '7', '	4294967295', '2', '0', '6', '637', '1', '0', '3', '0', '0');


REPLACE INTO `altadv_vars` (`skill_id`, `name`, `cost`, `max_level`, `hotkey_sid`, `hotkey_sid2`, `title_sid`, `desc_sid`, `type`, `spellid`, `prereq_skill`, `prereq_minpoints`, `spell_type`, `spell_refresh`, `classes`, `berserker`, `class_type`, `cost_inc`, `aa_expansion`, `special_category`, `sof_type`, `sof_cost_inc`, `sof_max_level`, `sof_next_skill`, `clientver`, `account_time_required`, `sof_current_level`,`sof_next_id`,`level_inc`) VALUES ('267', 'Spell Casting Fury Mastery', '3', '3', '4294967295', '4294967295', '13803', '13804', '3', '4294967295', '92', '3', '0', '0', '4096', '0', '59', '3', '3', '	4294967295', '2', '0', '8', '267', '1', '0', '0', '640', '0');

REPLACE INTO `altadv_vars` (`skill_id`, `name`, `cost`, `max_level`, `hotkey_sid`, `hotkey_sid2`, `title_sid`, `desc_sid`, `type`, `spellid`, `prereq_skill`, `prereq_minpoints`, `spell_type`, `spell_refresh`, `classes`, `berserker`, `class_type`, `cost_inc`, `aa_expansion`, `special_category`, `sof_type`, `sof_cost_inc`, `sof_max_level`, `sof_next_skill`, `clientver`, `account_time_required`, `sof_current_level`,`sof_next_id`,`level_inc`) VALUES ('640', 'Fury of Magic Mastery', '2', '3', '4294967295', '4294967295', '5740', '5741', '5', '4294967295', '267', '3', '0', '0', '4096', '0', '61', '2', '4', '		4294967295', '2', '0', '8', '267', '1', '0', '3', '924', '0');

REPLACE INTO `altadv_vars` (`skill_id`, `name`, `cost`, `max_level`, `hotkey_sid`, `hotkey_sid2`, `title_sid`, `desc_sid`, `type`, `spellid`, `prereq_skill`, `prereq_minpoints`, `spell_type`, `spell_refresh`, `classes`, `berserker`, `class_type`, `cost_inc`, `aa_expansion`, `special_category`, `sof_type`, `sof_cost_inc`, `sof_max_level`, `sof_next_skill`, `clientver`, `account_time_required`, `sof_current_level`,`sof_next_id`,`level_inc`) VALUES ('924', 'Advanced Fury of Magic Mastery', '5', '2', '4294967295', '4294967295', '9265', '9266', '6', '4294967295', '640', '3', '0', '0', '4096', '0', '65', '0', '7', '	4294967295', '2', '0', '8', '267', '1', '0', '6', '0', '0');

-- Archery Mastery
REPLACE INTO `aa_effects` (`aaid`, `slot`, `effectid`, `base1`, `base2`) VALUES ( 199, 1, 301, 30, 0);
REPLACE INTO `aa_effects` (`aaid`, `slot`, `effectid`, `base1`, `base2`) VALUES ( 200, 1, 301, 60, 0);
REPLACE INTO `aa_effects` (`aaid`, `slot`, `effectid`, `base1`, `base2`) VALUES ( 201, 1, 301, 100, 0);
