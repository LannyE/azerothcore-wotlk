-- DB update 2025_05_12_00 -> 2025_05_12_01

-- Update comments and edit row 2.
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 28529;

DELETE FROM `smart_scripts` WHERE (`source_type` = 0 AND `entryorguid` = 28529);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `event_param5`, `event_param6`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_param4`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(28529, 0, 0, 0, 0, 0, 100, 0, 0, 0, 2000, 3000, 0, 0, 11, 6660, 64, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Scarlet Crusader - In Combat - Cast \'Shoot\''),
(28529, 0, 1, 0, 4, 0, 50, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Scarlet Crusader - On Aggro - Say Line 0'),
(28529, 0, 2, 0, 25, 0, 100, 0, 0, 0, 0, 0, 0, 0, 205, 23, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Scarlet Crusader - On Reset - Set combat distance to 23');
