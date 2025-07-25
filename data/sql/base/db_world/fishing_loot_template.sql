-- MySQL dump 10.13  Distrib 8.4.3, for Win64 (x86_64)
--
-- Host: localhost    Database: acore_world
-- ------------------------------------------------------
-- Server version	8.4.3

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `fishing_loot_template`
--

DROP TABLE IF EXISTS `fishing_loot_template`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `fishing_loot_template` (
  `Entry` int unsigned NOT NULL DEFAULT '0',
  `Item` int unsigned NOT NULL DEFAULT '0',
  `Reference` int NOT NULL DEFAULT '0',
  `Chance` float NOT NULL DEFAULT '100',
  `QuestRequired` tinyint NOT NULL DEFAULT '0',
  `LootMode` smallint unsigned NOT NULL DEFAULT '1',
  `GroupId` tinyint unsigned NOT NULL DEFAULT '0',
  `MinCount` tinyint unsigned NOT NULL DEFAULT '1',
  `MaxCount` tinyint unsigned NOT NULL DEFAULT '1',
  `Comment` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`Entry`,`Item`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci COMMENT='Loot System';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `fishing_loot_template`
--

LOCK TABLES `fishing_loot_template` WRITE;
/*!40000 ALTER TABLE `fishing_loot_template` DISABLE KEYS */;
INSERT INTO `fishing_loot_template` VALUES
(1,11000,11000,100,0,1,1,1,1,'(ReferenceTable)'),
(1,11799,11799,100,0,32768,1,1,1,'(ReferenceTable)'),
(2,11003,11003,100,0,1,1,1,1,'(ReferenceTable)'),
(8,11006,11006,100,0,1,1,1,1,'(ReferenceTable)'),
(10,11004,11004,100,0,1,1,1,1,'(ReferenceTable)'),
(11,11004,11004,100,0,1,1,1,1,'(ReferenceTable)'),
(12,11000,11000,100,0,1,1,1,1,'(ReferenceTable)'),
(14,11001,11001,100,0,1,1,1,1,'(ReferenceTable)'),
(15,11006,11006,100,0,1,1,1,1,'(ReferenceTable)'),
(16,11008,11008,100,0,1,1,1,1,'(ReferenceTable)'),
(17,11003,11003,100,0,1,1,1,1,'(ReferenceTable)'),
(28,11008,11008,100,0,1,1,1,1,'(ReferenceTable)'),
(33,11006,11006,100,0,1,1,1,1,'(ReferenceTable)'),
(33,11150,11150,33,0,1,1,1,1,'(ReferenceTable)'),
(35,11007,11007,100,0,1,1,1,1,'(ReferenceTable)'),
(36,11006,11006,100,0,1,1,1,1,'(ReferenceTable)'),
(38,6317,0,25,0,1,0,1,1,'Raw Loch Frenzy'),
(38,11002,11002,100,0,1,1,1,1,'(ReferenceTable)'),
(40,11002,11002,100,0,1,1,1,1,'(ReferenceTable)'),
(41,11017,11017,100,0,1,1,1,1,'(ReferenceTable)'),
(43,11007,11007,100,0,1,1,1,1,'(ReferenceTable)'),
(44,1467,0,100,1,1,0,1,1,'Spotted Sunfish'),
(44,11004,11004,100,0,1,1,1,1,'(ReferenceTable)'),
(45,11006,11006,100,0,1,1,1,1,'(ReferenceTable)'),
(46,11010,11010,100,0,1,1,1,1,'(ReferenceTable)'),
(47,11008,11008,100,0,1,1,1,1,'(ReferenceTable)'),
(65,11020,11020,100,0,1,0,1,1,'(ReferenceTable)'),
(85,11099,11099,100,0,1,1,1,1,'(ReferenceTable)'),
(104,11007,11007,100,0,1,1,1,1,'(ReferenceTable)'),
(115,11003,11003,100,0,1,1,1,1,'(ReferenceTable)'),
(117,11007,11007,100,0,1,1,1,1,'(ReferenceTable)'),
(122,11007,11007,100,0,1,1,1,1,'(ReferenceTable)'),
(130,11099,11099,100,0,1,1,1,1,'(ReferenceTable)'),
(139,11010,11010,100,0,1,1,1,1,'(ReferenceTable)'),
(141,11000,11000,100,0,1,1,1,1,'(ReferenceTable)'),
(148,11104,11104,100,0,1,1,1,1,'(ReferenceTable)'),
(150,11005,11005,100,0,1,1,1,1,'(ReferenceTable)'),
(168,11001,11001,100,0,1,1,1,1,'(ReferenceTable)'),
(169,11001,11001,100,0,1,1,1,1,'(ReferenceTable)'),
(215,11000,11000,100,0,1,1,1,1,'(ReferenceTable)'),
(226,11003,11003,100,0,1,1,1,1,'(ReferenceTable)'),
(267,11004,11004,100,0,1,1,1,1,'(ReferenceTable)'),
(271,11005,11005,100,0,1,1,1,1,'(ReferenceTable)'),
(294,11005,11005,100,0,1,1,1,1,'(ReferenceTable)'),
(295,11005,11005,100,0,1,1,1,1,'(ReferenceTable)'),
(297,11009,11009,100,0,1,1,1,1,'(ReferenceTable)'),
(298,11005,11005,100,0,1,1,1,1,'(ReferenceTable)'),
(299,11005,11005,100,0,1,1,1,1,'(ReferenceTable)'),
(300,11007,11007,100,0,1,1,1,1,'(ReferenceTable)'),
(300,16970,0,20,1,1,0,1,1,'Misty Reed Mahi Mahi'),
(301,11007,11007,100,0,1,1,1,1,'(ReferenceTable)'),
(301,16969,0,20,1,1,0,1,1,'Savage Coast Blue Sailfin'),
(302,11007,11007,100,0,1,1,1,1,'(ReferenceTable)'),
(305,11003,11003,100,0,1,1,1,1,'(ReferenceTable)'),
(306,11003,11003,100,0,1,1,1,1,'(ReferenceTable)'),
(307,11009,11009,100,0,1,1,1,1,'(ReferenceTable)'),
(311,11007,11007,100,0,1,1,1,1,'(ReferenceTable)'),
(312,11007,11007,100,0,1,1,1,1,'(ReferenceTable)'),
(327,11007,11007,100,0,1,1,1,1,'(ReferenceTable)'),
(328,11007,11007,100,0,1,1,1,1,'(ReferenceTable)'),
(331,11004,11004,100,0,1,1,1,1,'(ReferenceTable)'),
(357,11008,11008,100,0,1,1,1,1,'(ReferenceTable)'),
(361,11008,11008,100,0,1,1,1,1,'(ReferenceTable)'),
(367,11000,11000,100,0,1,1,1,1,'(ReferenceTable)'),
(382,6651,0,0.1,0,1,0,1,1,'Broken Wine Bottle'),
(382,11101,11101,100,0,1,1,1,1,'(ReferenceTable)'),
(384,11002,11002,100,0,1,1,1,1,'(ReferenceTable)'),
(386,11102,11102,100,0,1,1,1,1,'(ReferenceTable)'),
(387,11102,11102,100,0,1,1,1,1,'(ReferenceTable)'),
(388,11102,11102,100,0,1,1,1,1,'(ReferenceTable)'),
(394,11019,11019,100,0,1,0,1,1,'(ReferenceTable)'),
(400,11006,11006,100,0,1,1,1,1,'(ReferenceTable)'),
(405,11006,11006,100,0,1,1,1,1,'(ReferenceTable)'),
(406,11004,11004,100,0,1,1,1,1,'(ReferenceTable)'),
(414,11005,11005,100,0,1,1,1,1,'(ReferenceTable)'),
(440,11009,11009,100,0,1,1,1,1,'(ReferenceTable)'),
(443,11103,11103,100,0,1,0,1,1,'(ReferenceTable)'),
(445,11103,11103,100,0,1,0,1,1,'(ReferenceTable)'),
(448,11103,11103,100,0,1,0,1,1,'(ReferenceTable)'),
(454,11103,11103,100,0,1,0,1,1,'(ReferenceTable)'),
(456,11103,11103,100,0,1,0,1,1,'(ReferenceTable)'),
(457,11003,11003,100,0,1,1,1,1,'(ReferenceTable)'),
(463,11101,11101,100,0,1,1,1,1,'(ReferenceTable)'),
(490,11008,11008,100,0,1,1,1,1,'(ReferenceTable)'),
(493,11008,11008,100,0,1,1,1,1,'(ReferenceTable)'),
(495,11018,11018,100,0,1,1,1,1,'(ReferenceTable)'),
(513,11007,11007,100,0,1,1,1,1,'(ReferenceTable)'),
(516,11007,11007,100,0,1,1,1,1,'(ReferenceTable)'),
(517,11007,11007,100,0,1,1,1,1,'(ReferenceTable)'),
(518,11007,11007,100,0,1,1,1,1,'(ReferenceTable)'),
(537,11106,11106,100,0,1,1,1,1,'(ReferenceTable)'),
(598,11007,11007,100,0,1,1,1,1,'(ReferenceTable)'),
(598,16968,0,20,1,1,0,1,1,'Sar\'theris Striker'),
(618,11010,11010,100,0,1,1,1,1,'(ReferenceTable)'),
(636,11101,11101,100,0,1,1,1,1,'(ReferenceTable)'),
(702,11001,11001,100,0,1,1,1,1,'(ReferenceTable)'),
(718,11102,11102,100,0,1,1,1,1,'(ReferenceTable)'),
(719,11099,11099,100,0,1,1,1,1,'(ReferenceTable)'),
(796,11006,11006,100,0,1,1,1,1,'(ReferenceTable)'),
(814,11000,11000,100,0,1,1,1,1,'(ReferenceTable)'),
(815,11002,11002,100,0,1,1,1,1,'(ReferenceTable)'),
(1039,11005,11005,100,0,1,1,1,1,'(ReferenceTable)'),
(1108,11009,11009,100,0,1,1,1,1,'(ReferenceTable)'),
(1112,11010,11010,100,0,1,1,1,1,'(ReferenceTable)'),
(1156,11002,11002,100,0,1,1,1,1,'(ReferenceTable)'),
(1222,11105,11105,100,0,1,1,1,1,'(ReferenceTable)'),
(1226,11009,11009,100,0,1,1,1,1,'(ReferenceTable)'),
(1227,11105,11105,100,0,1,1,1,1,'(ReferenceTable)'),
(1228,11009,11009,100,0,1,1,1,1,'(ReferenceTable)'),
(1229,11009,11009,100,0,1,1,1,1,'(ReferenceTable)'),
(1230,11009,11009,100,0,1,1,1,1,'(ReferenceTable)'),
(1231,11009,11009,100,0,1,1,1,1,'(ReferenceTable)'),
(1256,11009,11009,100,0,1,1,1,1,'(ReferenceTable)'),
(1377,11010,11010,100,0,1,1,1,1,'(ReferenceTable)'),
(1417,11008,11008,100,0,1,1,1,1,'(ReferenceTable)'),
(1497,11100,11100,100,0,1,1,1,1,'(ReferenceTable)'),
(1519,11002,11002,100,0,1,1,1,1,'(ReferenceTable)'),
(1519,34864,0,20,1,1,0,1,1,'Baby Crocolisk'),
(1537,11002,11002,100,0,1,1,1,1,'(ReferenceTable)'),
(1537,34484,0,0.1,0,1,0,1,1,'Old Ironjaw'),
(1577,11007,11007,100,0,1,1,1,1,'(ReferenceTable)'),
(1578,11007,11007,100,0,1,1,1,1,'(ReferenceTable)'),
(1578,16969,0,20,1,1,0,1,1,'Savage Coast Blue Sailfin'),
(1581,11002,11002,100,0,1,1,1,1,'(ReferenceTable)'),
(1637,11002,11002,100,0,1,1,1,1,'(ReferenceTable)'),
(1637,34486,0,0.1,0,1,0,1,1,'Old Crafty'),
(1637,34864,0,20,1,1,0,1,1,'Baby Crocolisk'),
(1638,11002,11002,100,0,1,1,1,1,'(ReferenceTable)'),
(1657,11002,11002,100,0,1,1,1,1,'(ReferenceTable)'),
(1701,11002,11002,100,0,1,1,1,1,'(ReferenceTable)'),
(1739,11007,11007,100,0,1,1,1,1,'(ReferenceTable)'),
(1797,11007,11007,100,0,1,1,1,1,'(ReferenceTable)'),
(1977,11010,11010,100,0,1,1,1,1,'(ReferenceTable)'),
(2017,11010,11010,100,0,1,1,1,1,'(ReferenceTable)'),
(2057,11010,11010,100,0,1,1,1,1,'(ReferenceTable)'),
(2077,11103,11103,100,0,1,0,1,1,'(ReferenceTable)'),
(2079,11007,11007,100,0,1,1,1,1,'(ReferenceTable)'),
(2100,11008,11008,100,0,1,1,1,1,'(ReferenceTable)'),
(2104,11005,11005,100,0,1,1,1,1,'(ReferenceTable)'),
(2322,11001,11001,100,0,1,1,1,1,'(ReferenceTable)'),
(2324,11007,11007,100,0,1,1,1,1,'(ReferenceTable)'),
(2325,11005,11005,100,0,1,1,1,1,'(ReferenceTable)'),
(2339,11007,11007,100,0,1,1,1,1,'(ReferenceTable)'),
(2365,11005,11005,100,0,1,1,1,1,'(ReferenceTable)'),
(2397,11005,11005,100,0,1,1,1,1,'(ReferenceTable)'),
(2398,11003,11003,100,0,1,1,1,1,'(ReferenceTable)'),
(2399,11001,11001,100,0,1,1,1,1,'(ReferenceTable)'),
(2402,11005,11005,100,0,1,1,1,1,'(ReferenceTable)'),
(2403,11007,11007,100,0,1,1,1,1,'(ReferenceTable)'),
(2405,11007,11007,100,0,1,1,1,1,'(ReferenceTable)'),
(2406,11007,11007,100,0,1,1,1,1,'(ReferenceTable)'),
(2408,11007,11007,100,0,1,1,1,1,'(ReferenceTable)'),
(2521,11008,11008,100,0,1,1,1,1,'(ReferenceTable)'),
(2521,16967,0,20,1,1,0,1,1,'Feralas Ahi'),
(2817,11021,11021,100,0,1,0,1,1,'(ReferenceTable)'),
(2979,11000,11000,100,0,1,1,1,1,'(ReferenceTable)'),
(3140,11105,11105,100,0,1,1,1,1,'(ReferenceTable)'),
(3317,11009,11009,100,0,1,1,1,1,'(ReferenceTable)'),
(3357,11007,11007,100,0,1,1,1,1,'(ReferenceTable)'),
(3430,11001,11001,100,0,1,1,1,1,'(ReferenceTable)'),
(3433,11003,11003,100,0,1,1,1,1,'(ReferenceTable)'),
(3470,11000,11000,100,0,1,1,1,1,'(ReferenceTable)'),
(3473,11000,11000,100,0,1,1,1,1,'(ReferenceTable)'),
(3475,11000,11000,100,0,1,1,1,1,'(ReferenceTable)'),
(3479,6307,0,0.4,0,1,0,1,1,'Message in a Bottle'),
(3479,6352,0,0.4,0,1,0,1,1,'Waterlogged Crate'),
(3479,6354,0,0.4,0,1,0,1,1,'Small Locked Chest'),
(3479,6358,0,25,0,1,0,1,1,'Oily Blackmouth'),
(3479,6359,0,15,0,1,0,1,1,'Firefin Snapper'),
(3479,6360,0,0.5,0,1,0,1,1,'Steelscale Crushfish'),
(3479,6361,0,58.8,0,1,0,1,1,'Raw Rainbow Fin Albacore'),
(3482,11003,11003,100,0,1,1,1,1,'(ReferenceTable)'),
(3483,11011,11011,100,0,1,1,1,1,'(ReferenceTable)'),
(3483,34867,0,20,1,1,0,1,1,'Monstrous Felblood Snapper'),
(3489,11002,11002,100,0,1,1,1,1,'(ReferenceTable)'),
(3496,11002,11002,100,0,1,1,1,1,'(ReferenceTable)'),
(3506,11002,11002,100,0,1,1,1,1,'(ReferenceTable)'),
(3507,11002,11002,100,0,1,1,1,1,'(ReferenceTable)'),
(3508,11002,11002,100,0,1,1,1,1,'(ReferenceTable)'),
(3515,11002,11002,100,0,1,1,1,1,'(ReferenceTable)'),
(3518,11014,11014,100,0,1,1,1,1,'(ReferenceTable)'),
(3519,11013,11013,100,0,1,1,1,1,'(ReferenceTable)'),
(3519,34865,0,20,1,1,0,1,1,'Blackfin Darter'),
(3520,11015,11015,100,0,1,1,1,1,'(ReferenceTable)'),
(3520,34867,0,20,1,1,0,1,1,'Monstrous Felblood Snapper'),
(3521,11012,11012,100,0,1,0,1,1,'(ReferenceTable)'),
(3523,11014,11014,100,0,1,1,1,1,'(ReferenceTable)'),
(3524,11001,11001,100,0,1,1,1,1,'(ReferenceTable)'),
(3525,11003,11003,100,0,1,1,1,1,'(ReferenceTable)'),
(3526,11000,11000,100,0,1,1,1,1,'(ReferenceTable)'),
(3527,11000,11000,100,0,1,1,1,1,'(ReferenceTable)'),
(3528,11000,11000,100,0,1,1,1,1,'(ReferenceTable)'),
(3537,11018,11018,100,0,1,1,1,1,'(ReferenceTable)'),
(3595,11101,11101,100,0,1,1,1,1,'(ReferenceTable)'),
(3607,11012,11012,100,0,1,0,1,1,'(ReferenceTable)'),
(3614,11014,11014,100,0,1,1,1,1,'(ReferenceTable)'),
(3614,34868,0,33,1,1,0,1,1,'World\'s Largest Mudfish'),
(3621,11014,11014,100,0,1,1,1,1,'(ReferenceTable)'),
(3621,34868,0,33,1,1,0,1,1,'World\'s Largest Mudfish'),
(3625,11011,11011,100,0,1,1,1,1,'(ReferenceTable)'),
(3684,11013,11013,100,0,1,1,1,1,'(ReferenceTable)'),
(3690,11013,11013,100,0,1,1,1,1,'(ReferenceTable)'),
(3691,11013,11013,100,0,1,1,1,1,'(ReferenceTable)'),
(3711,11022,11022,100,0,1,0,1,1,'(ReferenceTable)'),
(3716,11012,11012,100,0,1,0,1,1,'(ReferenceTable)'),
(3805,11017,11017,100,0,1,1,1,1,'(ReferenceTable)'),
(3859,11013,11013,100,0,1,1,1,1,'(ReferenceTable)'),
(3979,11023,11023,100,0,1,1,1,1,'(ReferenceTable)'),
(3980,11019,11019,100,0,1,0,1,1,'(ReferenceTable)'),
(3982,11019,11019,100,0,1,0,1,1,'(ReferenceTable)'),
(3994,11019,11019,100,0,1,0,1,1,'(ReferenceTable)'),
(3999,11019,11019,100,0,1,0,1,1,'(ReferenceTable)'),
(4001,11019,11019,100,0,1,0,1,1,'(ReferenceTable)'),
(4002,11019,11019,100,0,1,0,1,1,'(ReferenceTable)'),
(4039,11020,11020,100,0,1,0,1,1,'(ReferenceTable)'),
(4043,11020,11020,100,0,1,0,1,1,'(ReferenceTable)'),
(4047,11007,11007,100,0,1,1,1,1,'(ReferenceTable)'),
(4055,11019,11019,100,0,1,0,1,1,'(ReferenceTable)'),
(4058,11019,11019,100,0,1,0,1,1,'(ReferenceTable)'),
(4059,11019,11019,100,0,1,0,1,1,'(ReferenceTable)'),
(4071,11019,11019,100,0,1,0,1,1,'(ReferenceTable)'),
(4080,11016,11016,100,0,1,1,1,1,'(ReferenceTable)'),
(4109,11020,11020,100,0,1,0,1,1,'(ReferenceTable)'),
(4134,11020,11020,100,0,1,0,1,1,'(ReferenceTable)'),
(4152,11018,11018,100,0,1,1,1,1,'(ReferenceTable)'),
(4157,11018,11018,100,0,1,1,1,1,'(ReferenceTable)'),
(4181,11018,11018,100,0,1,1,1,1,'(ReferenceTable)'),
(4185,11018,11018,100,0,1,1,1,1,'(ReferenceTable)'),
(4197,1,11107,100,0,1,0,1,1,'(ReferenceTable)'),
(4197,45904,0,50,1,1,0,1,1,'Terrorfish'),
(4212,11018,11018,100,0,1,1,1,1,'(ReferenceTable)'),
(4224,11018,11018,100,0,1,1,1,1,'(ReferenceTable)'),
(4225,11018,11018,100,0,1,1,1,1,'(ReferenceTable)'),
(4241,11018,11018,100,0,1,1,1,1,'(ReferenceTable)'),
(4242,11018,11018,100,0,1,1,1,1,'(ReferenceTable)'),
(4244,11018,11018,100,0,1,1,1,1,'(ReferenceTable)'),
(4263,11019,11019,100,0,1,0,1,1,'(ReferenceTable)'),
(4290,45902,0,20,1,1,0,1,1,'Phantom Ghostfish'),
(4478,11018,11018,100,0,1,1,1,1,'(ReferenceTable)'),
(4479,11019,11019,100,0,1,0,1,1,'(ReferenceTable)'),
(4560,11026,11026,100,0,1,0,1,1,'(ReferenceTable)'),
(4567,11024,11024,100,0,1,1,1,1,'(ReferenceTable)'),
(4568,11025,11025,100,0,1,1,1,1,'(ReferenceTable)'),
(4813,3671,0,4.5,0,1,1,1,1,'Lifeless Skull'),
(4813,4875,0,5,0,1,1,1,1,'Slimy Bone'),
(4813,25447,0,4.5,0,1,1,1,1,'Broken Skull'),
(4813,36794,0,5.4,0,1,1,1,1,'Scoured Fishbones'),
(4813,37705,0,1,0,1,1,1,1,'Crystallized Water'),
(4813,41808,0,58,0,1,1,1,1,'Bonescale Snapper'),
(4813,43572,0,20.5,0,1,1,1,1,'Magic Eater'),
(4813,44475,0,1.1,0,1,1,1,1,'Reinforced Crate');
/*!40000 ALTER TABLE `fishing_loot_template` ENABLE KEYS */;
UNLOCK TABLES;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2025-07-19 12:08:56
