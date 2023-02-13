-- MySQL dump 10.13  Distrib 8.0.32, for Linux (x86_64)
--
-- Host: localhost    Database: Juno
-- ------------------------------------------------------
-- Server version	8.0.32-0ubuntu0.20.04.2

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `account_userdevice`
--

DROP TABLE IF EXISTS `account_userdevice`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `account_userdevice` (
  `id` bigint NOT NULL AUTO_INCREMENT,
  `keyname` varchar(200) NOT NULL,
  `ssh_prefix` varchar(64) NOT NULL,
  `ssh_pubkey` varchar(600) NOT NULL,
  `ssh_suffix` varchar(256) NOT NULL,
  `last_seen` datetime(6) DEFAULT NULL,
  `user_id_id` int NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `ssh_pubkey` (`ssh_pubkey`),
  KEY `account_userdevice_user_id_id_20c88a08_fk_auth_user_id` (`user_id_id`),
  CONSTRAINT `account_userdevice_user_id_id_20c88a08_fk_auth_user_id` FOREIGN KEY (`user_id_id`) REFERENCES `auth_user` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `account_userdevice`
--

LOCK TABLES `account_userdevice` WRITE;
/*!40000 ALTER TABLE `account_userdevice` DISABLE KEYS */;
INSERT INTO `account_userdevice` VALUES (1,'hybrids-key','ssh-rsa','AAAAB3NzaC1yc2EAAAADAQABAAABgQDV6pvDAafe6Emu305YWzxuEWgWq6ypPpMftmHVtu5al9+VzLSFFph2J5hqUL06M8W7+5b1a+UXxdns7hUIHYEh2WPxJkPf4xPXyEG3bXeoTXyt4YZ3i+PagmvcYLg4pwUJl2y5A1/ipamdZTqoPNtycIDt62+pPEjBUL7QnE3YPIP6Fzh76SQcPHS46t7MDzSahBkAvaTMErCfYfyFgIrWgcWbVY+pM+JPyfNpAQs/XkYxXtctzieasPqkOlLc/Y2XKeB6SiXZiiOuu8zHTNfuAd1OO1yZ0Bp0+Bph/ZlsLmrPVsEzgw0yzOn+Mz9zMng1flQHQqxA2kLzI8lk8/HbIf9byKzIJebRdsOBJEnY+/xyEO8wxx5bgs3MshtDe9lNyKraaEgS/+c87Q4p1v6tUZdXSRPTSjyeczYxRVAMFU0NVo+WZvnG0KIHx5wMUX46tBiQFlW+gdhs1EC1wdkcC8K9zxZuK9685duhRbZp0DMgWsSC6wJi8mAUhYAT8Es=','hybrid-swansea@junotest','2023-02-13 18:12:11.000000',2),(2,'lemon8s-key','ssh-rsa','AAAAB3NzaC1yc2EAAAADAQABAAABgQC1fKpZZPujnSYHQS+tDIOtjcXjzD9TgzPBkLE3KrXcEi/3XejarmzFSspiD3X+tbWoL+HL6GlYGMwsi+V4gGglHfsJjfY/VdKKIDmzBWOxuR4AJsOlSDBsBAgYY4XlChk9qFS7QeECYPTV+pSKzA12AP3hC34ueC/ZF/pkKI7V9poqVVku8TbOvbAD1Un91gUtfSRAMSTap4TA7xdXs/6wCzSrl3ttdZ+agiHMouRihFWBppxW1Rl1BKVuQOn8kxsdjNNFr78loT4bX5vxYdgQk2YrQ9m1eenTD+GdP2/GjulQmdJNpzabDDA48MtTH9UOdK5V+M4DBcvEPkKh/68dN4TdtoAHCGszg9R+C+eZdgkpaeGErFNpeI4mMvYaPJNHo0ogz0VzDW1XithvjmADAcrOqLHV90BJVeJeNU4YiUoQ0JIkVGsQwCABJ386kfrCIHSRLR0op3nvur3/u3m1v7dclxUJXKfGsJVd0ZOv77Vw9a8Q5Z94jwXXPwKzZ/0=','lemon8@junotest','2023-02-13 18:12:43.000000',3),(3,'bukems-key','ssh-rsa','AAAAB3NzaC1yc2EAAAADAQABAAABgQC6ZO16nNJyD6c19cRoMohkLAXbFCI2zQhzTkG4sOrd5rIWLnadECiB92HGu7OrmAT5IvY286gF84fURvTA7p+6iGceDWzjZVtA+CYoKlr3J+G7P+sNbahX9vfL/pGcC9IdSAzsZrrCr2adJLjJAJlEtYyfURF4W3GjE4Yal5iMcBzmK8Ki5T/1bosRtZ9jpk0r8vhGrb+isxyssyUxEXL0HSJR+Z3Qe13xUNdFWUOk9vZ1EUpcq3Kpb0uJCnaskgb6pDkOyWAzyZlQ3+R2qL9S8hYyzGCxql9qHHaPQ+S6Y++Dh5KsZMXCRtOcqN7iDpZNwK4EtVFc9qMpkg8BGnu7gEE1A7X9tmmYljYPm+YUEbECAE/KwxVYo3h4X0vs37jnnVjGxgYCCFJrGAyVlYLzUYq30uTLVhEJd50zhQNvQcVsLrhHtKaOvebQXUO8Wm9FtDuuwdKFPWythkEs7hDVNuVV6Ct2sYO6NDvhgskOxH/Yz3z7GKMqn/MoAIymd6E=','ltj-bukem@junotest','2023-02-13 18:13:24.000000',4);
/*!40000 ALTER TABLE `account_userdevice` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `account_userscore`
--

DROP TABLE IF EXISTS `account_userscore`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `account_userscore` (
  `id` bigint NOT NULL AUTO_INCREMENT,
  `score` bigint unsigned NOT NULL,
  `user_id_id` int NOT NULL,
  PRIMARY KEY (`id`),
  KEY `account_userscore_user_id_id_c006535e_fk_auth_user_id` (`user_id_id`),
  CONSTRAINT `account_userscore_user_id_id_c006535e_fk_auth_user_id` FOREIGN KEY (`user_id_id`) REFERENCES `auth_user` (`id`),
  CONSTRAINT `account_userscore_chk_1` CHECK ((`score` >= 0))
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `account_userscore`
--

LOCK TABLES `account_userscore` WRITE;
/*!40000 ALTER TABLE `account_userscore` DISABLE KEYS */;
/*!40000 ALTER TABLE `account_userscore` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `auth_group`
--

DROP TABLE IF EXISTS `auth_group`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `auth_group` (
  `id` int NOT NULL AUTO_INCREMENT,
  `name` varchar(150) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `name` (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `auth_group`
--

LOCK TABLES `auth_group` WRITE;
/*!40000 ALTER TABLE `auth_group` DISABLE KEYS */;
/*!40000 ALTER TABLE `auth_group` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `auth_group_permissions`
--

DROP TABLE IF EXISTS `auth_group_permissions`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `auth_group_permissions` (
  `id` bigint NOT NULL AUTO_INCREMENT,
  `group_id` int NOT NULL,
  `permission_id` int NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `auth_group_permissions_group_id_permission_id_0cd325b0_uniq` (`group_id`,`permission_id`),
  KEY `auth_group_permissio_permission_id_84c5c92e_fk_auth_perm` (`permission_id`),
  CONSTRAINT `auth_group_permissio_permission_id_84c5c92e_fk_auth_perm` FOREIGN KEY (`permission_id`) REFERENCES `auth_permission` (`id`),
  CONSTRAINT `auth_group_permissions_group_id_b120cbf9_fk_auth_group_id` FOREIGN KEY (`group_id`) REFERENCES `auth_group` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `auth_group_permissions`
--

LOCK TABLES `auth_group_permissions` WRITE;
/*!40000 ALTER TABLE `auth_group_permissions` DISABLE KEYS */;
/*!40000 ALTER TABLE `auth_group_permissions` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `auth_permission`
--

DROP TABLE IF EXISTS `auth_permission`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `auth_permission` (
  `id` int NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL,
  `content_type_id` int NOT NULL,
  `codename` varchar(100) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `auth_permission_content_type_id_codename_01ab375a_uniq` (`content_type_id`,`codename`),
  CONSTRAINT `auth_permission_content_type_id_2f476e4b_fk_django_co` FOREIGN KEY (`content_type_id`) REFERENCES `django_content_type` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=57 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `auth_permission`
--

LOCK TABLES `auth_permission` WRITE;
/*!40000 ALTER TABLE `auth_permission` DISABLE KEYS */;
INSERT INTO `auth_permission` VALUES (1,'Can add log entry',1,'add_logentry'),(2,'Can change log entry',1,'change_logentry'),(3,'Can delete log entry',1,'delete_logentry'),(4,'Can view log entry',1,'view_logentry'),(5,'Can add permission',2,'add_permission'),(6,'Can change permission',2,'change_permission'),(7,'Can delete permission',2,'delete_permission'),(8,'Can view permission',2,'view_permission'),(9,'Can add group',3,'add_group'),(10,'Can change group',3,'change_group'),(11,'Can delete group',3,'delete_group'),(12,'Can view group',3,'view_group'),(13,'Can add user',4,'add_user'),(14,'Can change user',4,'change_user'),(15,'Can delete user',4,'delete_user'),(16,'Can view user',4,'view_user'),(17,'Can add content type',5,'add_contenttype'),(18,'Can change content type',5,'change_contenttype'),(19,'Can delete content type',5,'delete_contenttype'),(20,'Can view content type',5,'view_contenttype'),(21,'Can add session',6,'add_session'),(22,'Can change session',6,'change_session'),(23,'Can delete session',6,'delete_session'),(24,'Can view session',6,'view_session'),(25,'Can add user score',7,'add_userscore'),(26,'Can change user score',7,'change_userscore'),(27,'Can delete user score',7,'delete_userscore'),(28,'Can view user score',7,'view_userscore'),(29,'Can add user device',8,'add_userdevice'),(30,'Can change user device',8,'change_userdevice'),(31,'Can delete user device',8,'delete_userdevice'),(32,'Can view user device',8,'view_userdevice'),(33,'Can add game',9,'add_game'),(34,'Can change game',9,'change_game'),(35,'Can delete game',9,'delete_game'),(36,'Can view game',9,'view_game'),(37,'Can add team ref',10,'add_teamref'),(38,'Can change team ref',10,'change_teamref'),(39,'Can delete team ref',10,'delete_teamref'),(40,'Can view team ref',10,'view_teamref'),(41,'Can add game service',11,'add_gameservice'),(42,'Can change game service',11,'change_gameservice'),(43,'Can delete game service',11,'delete_gameservice'),(44,'Can view game service',11,'view_gameservice'),(45,'Can add game scoring',12,'add_gamescoring'),(46,'Can change game scoring',12,'change_gamescoring'),(47,'Can delete game scoring',12,'delete_gamescoring'),(48,'Can view game scoring',12,'view_gamescoring'),(49,'Can add game score',13,'add_gamescore'),(50,'Can change game score',13,'change_gamescore'),(51,'Can delete game score',13,'delete_gamescore'),(52,'Can view game score',13,'view_gamescore'),(53,'Can add game player',14,'add_gameplayer'),(54,'Can change game player',14,'change_gameplayer'),(55,'Can delete game player',14,'delete_gameplayer'),(56,'Can view game player',14,'view_gameplayer');
/*!40000 ALTER TABLE `auth_permission` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `auth_user`
--

DROP TABLE IF EXISTS `auth_user`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `auth_user` (
  `id` int NOT NULL AUTO_INCREMENT,
  `password` varchar(128) NOT NULL,
  `last_login` datetime(6) DEFAULT NULL,
  `is_superuser` tinyint(1) NOT NULL,
  `username` varchar(150) NOT NULL,
  `first_name` varchar(150) NOT NULL,
  `last_name` varchar(150) NOT NULL,
  `email` varchar(254) NOT NULL,
  `is_staff` tinyint(1) NOT NULL,
  `is_active` tinyint(1) NOT NULL,
  `date_joined` datetime(6) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `username` (`username`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `auth_user`
--

LOCK TABLES `auth_user` WRITE;
/*!40000 ALTER TABLE `auth_user` DISABLE KEYS */;
INSERT INTO `auth_user` VALUES (1,'argon2$argon2id$v=19$m=102400,t=2,p=8$ZTU3aUxtOXhRa1RTUnpkQ0pnamw1aQ$+C2Vn97/W3MpLJbBuROojC584icHajQCVLiKiWu0ptQ','2023-02-13 18:08:33.376664',1,'admin','','','',1,1,'2023-02-13 18:08:05.525080'),(2,'argon2$argon2id$v=19$m=102400,t=2,p=8$dXB5OTRPdDB2ZHhHanUwYXBzQWFJQg$SvxpGyzeDMN8yPV4e26lYSvfj2a+becTZIxRMVpiHrk',NULL,0,'hybrid-swansea','','','',0,1,'2023-02-13 18:09:24.468490'),(3,'argon2$argon2id$v=19$m=102400,t=2,p=8$c0sxRnRhc0lRNEVrOEdyUzZPMHhLZg$kbXU45GAVMNknEjHAwHs1Cm+YMNy6/584PzAzw8IUz4',NULL,0,'lemon8','','','',0,1,'2023-02-13 18:09:37.457841'),(4,'argon2$argon2id$v=19$m=102400,t=2,p=8$S2tQdk1hcXJ5Q1kwSk80Y0l0bjhCaw$ZTrFHSfzkZvg2CjSieWX0fSEFF3NTGisLv+/JIQNDlM',NULL,0,'ltj-bukem','','','',0,1,'2023-02-13 18:10:12.637418');
/*!40000 ALTER TABLE `auth_user` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `auth_user_groups`
--

DROP TABLE IF EXISTS `auth_user_groups`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `auth_user_groups` (
  `id` bigint NOT NULL AUTO_INCREMENT,
  `user_id` int NOT NULL,
  `group_id` int NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `auth_user_groups_user_id_group_id_94350c0c_uniq` (`user_id`,`group_id`),
  KEY `auth_user_groups_group_id_97559544_fk_auth_group_id` (`group_id`),
  CONSTRAINT `auth_user_groups_group_id_97559544_fk_auth_group_id` FOREIGN KEY (`group_id`) REFERENCES `auth_group` (`id`),
  CONSTRAINT `auth_user_groups_user_id_6a12ed8b_fk_auth_user_id` FOREIGN KEY (`user_id`) REFERENCES `auth_user` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `auth_user_groups`
--

LOCK TABLES `auth_user_groups` WRITE;
/*!40000 ALTER TABLE `auth_user_groups` DISABLE KEYS */;
/*!40000 ALTER TABLE `auth_user_groups` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `auth_user_user_permissions`
--

DROP TABLE IF EXISTS `auth_user_user_permissions`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `auth_user_user_permissions` (
  `id` bigint NOT NULL AUTO_INCREMENT,
  `user_id` int NOT NULL,
  `permission_id` int NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `auth_user_user_permissions_user_id_permission_id_14a6b632_uniq` (`user_id`,`permission_id`),
  KEY `auth_user_user_permi_permission_id_1fbb5f2c_fk_auth_perm` (`permission_id`),
  CONSTRAINT `auth_user_user_permi_permission_id_1fbb5f2c_fk_auth_perm` FOREIGN KEY (`permission_id`) REFERENCES `auth_permission` (`id`),
  CONSTRAINT `auth_user_user_permissions_user_id_a95ead1b_fk_auth_user_id` FOREIGN KEY (`user_id`) REFERENCES `auth_user` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `auth_user_user_permissions`
--

LOCK TABLES `auth_user_user_permissions` WRITE;
/*!40000 ALTER TABLE `auth_user_user_permissions` DISABLE KEYS */;
/*!40000 ALTER TABLE `auth_user_user_permissions` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `django_admin_log`
--

DROP TABLE IF EXISTS `django_admin_log`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `django_admin_log` (
  `id` int NOT NULL AUTO_INCREMENT,
  `action_time` datetime(6) NOT NULL,
  `object_id` longtext,
  `object_repr` varchar(200) NOT NULL,
  `action_flag` smallint unsigned NOT NULL,
  `change_message` longtext NOT NULL,
  `content_type_id` int DEFAULT NULL,
  `user_id` int NOT NULL,
  PRIMARY KEY (`id`),
  KEY `django_admin_log_content_type_id_c4bce8eb_fk_django_co` (`content_type_id`),
  KEY `django_admin_log_user_id_c564eba6_fk_auth_user_id` (`user_id`),
  CONSTRAINT `django_admin_log_content_type_id_c4bce8eb_fk_django_co` FOREIGN KEY (`content_type_id`) REFERENCES `django_content_type` (`id`),
  CONSTRAINT `django_admin_log_user_id_c564eba6_fk_auth_user_id` FOREIGN KEY (`user_id`) REFERENCES `auth_user` (`id`),
  CONSTRAINT `django_admin_log_chk_1` CHECK ((`action_flag` >= 0))
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `django_admin_log`
--

LOCK TABLES `django_admin_log` WRITE;
/*!40000 ALTER TABLE `django_admin_log` DISABLE KEYS */;
INSERT INTO `django_admin_log` VALUES (1,'2023-02-13 18:09:24.728565','2','hybrid-swansea',1,'[{\"added\": {}}]',4,1),(2,'2023-02-13 18:09:37.745539','3','lemon8',1,'[{\"added\": {}}]',4,1),(3,'2023-02-13 18:10:12.866463','4','ltj-bukem',1,'[{\"added\": {}}]',4,1),(4,'2023-02-13 18:12:13.269554','1','hybrids-key',1,'[{\"added\": {}}]',8,1),(5,'2023-02-13 18:12:45.367231','2','lemon8s-key',1,'[{\"added\": {}}]',8,1),(6,'2023-02-13 18:13:27.586964','3','bukems-key',1,'[{\"added\": {}}]',8,1);
/*!40000 ALTER TABLE `django_admin_log` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `django_content_type`
--

DROP TABLE IF EXISTS `django_content_type`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `django_content_type` (
  `id` int NOT NULL AUTO_INCREMENT,
  `app_label` varchar(100) NOT NULL,
  `model` varchar(100) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `django_content_type_app_label_model_76bd3d3b_uniq` (`app_label`,`model`)
) ENGINE=InnoDB AUTO_INCREMENT=15 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `django_content_type`
--

LOCK TABLES `django_content_type` WRITE;
/*!40000 ALTER TABLE `django_content_type` DISABLE KEYS */;
INSERT INTO `django_content_type` VALUES (8,'account','userdevice'),(7,'account','userscore'),(1,'admin','logentry'),(3,'auth','group'),(2,'auth','permission'),(4,'auth','user'),(5,'contenttypes','contenttype'),(9,'games','game'),(14,'games','gameplayer'),(13,'games','gamescore'),(12,'games','gamescoring'),(11,'games','gameservice'),(10,'games','teamref'),(6,'sessions','session');
/*!40000 ALTER TABLE `django_content_type` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `django_migrations`
--

DROP TABLE IF EXISTS `django_migrations`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `django_migrations` (
  `id` bigint NOT NULL AUTO_INCREMENT,
  `app` varchar(255) NOT NULL,
  `name` varchar(255) NOT NULL,
  `applied` datetime(6) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=23 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `django_migrations`
--

LOCK TABLES `django_migrations` WRITE;
/*!40000 ALTER TABLE `django_migrations` DISABLE KEYS */;
INSERT INTO `django_migrations` VALUES (1,'contenttypes','0001_initial','2023-02-13 04:59:11.198064'),(2,'auth','0001_initial','2023-02-13 04:59:58.401875'),(3,'account','0001_initial','2023-02-13 05:00:19.184420'),(4,'admin','0001_initial','2023-02-13 05:00:32.279213'),(5,'admin','0002_logentry_remove_auto_add','2023-02-13 05:00:32.452145'),(6,'admin','0003_logentry_add_action_flag_choices','2023-02-13 05:00:32.659355'),(7,'contenttypes','0002_remove_content_type_name','2023-02-13 05:00:38.401876'),(8,'auth','0002_alter_permission_name_max_length','2023-02-13 05:00:45.324927'),(9,'auth','0003_alter_user_email_max_length','2023-02-13 05:00:46.168711'),(10,'auth','0004_alter_user_username_opts','2023-02-13 05:00:46.599255'),(11,'auth','0005_alter_user_last_login_null','2023-02-13 05:00:50.234892'),(12,'auth','0006_require_contenttypes_0002','2023-02-13 05:00:50.412402'),(13,'auth','0007_alter_validators_add_error_messages','2023-02-13 05:00:50.544807'),(14,'auth','0008_alter_user_username_max_length','2023-02-13 05:00:57.649088'),(15,'auth','0009_alter_user_last_name_max_length','2023-02-13 05:01:06.196538'),(16,'auth','0010_alter_group_name_max_length','2023-02-13 05:01:06.597937'),(17,'auth','0011_update_proxy_permissions','2023-02-13 05:01:06.762167'),(18,'auth','0012_alter_user_first_name_max_length','2023-02-13 05:01:11.712151'),(19,'games','0001_initial','2023-02-13 05:02:14.982847'),(20,'sessions','0001_initial','2023-02-13 05:02:19.423621'),(21,'account','0002_alter_userdevice_last_seen','2023-02-13 18:38:10.375625'),(22,'games','0002_alter_gameplayer_team_id_alter_gameplayer_user_id_and_more','2023-02-13 18:38:19.290959');
/*!40000 ALTER TABLE `django_migrations` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `django_session`
--

DROP TABLE IF EXISTS `django_session`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `django_session` (
  `session_key` varchar(40) NOT NULL,
  `session_data` longtext NOT NULL,
  `expire_date` datetime(6) NOT NULL,
  PRIMARY KEY (`session_key`),
  KEY `django_session_expire_date_a5c62663` (`expire_date`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `django_session`
--

LOCK TABLES `django_session` WRITE;
/*!40000 ALTER TABLE `django_session` DISABLE KEYS */;
INSERT INTO `django_session` VALUES ('m9z97arowee6js59co5tqmgnyg9wkg9q','.eJxVjEEOwiAURO_C2hAKfKAu3fcM5AMfqRpISrsy3t026UKTWc17M2_mcVuL3zotfk7sygZ2-e0CxifVA6QH1nvjsdV1mQM_FH7SzqeW6HU73b-Dgr3sa4tRjspGkqi1Axf0Hk05AiabtFEBTR5IGIkgHIAmGB0klaNAAUGxzxfmoTfR:1pRdFh:PpeW4VcE4etr9dJLeUeY0vAA62X1lqUJd1ED5zDXFfE','2023-02-27 18:08:33.506536');
/*!40000 ALTER TABLE `django_session` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `games_game`
--

DROP TABLE IF EXISTS `games_game`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `games_game` (
  `id` bigint NOT NULL AUTO_INCREMENT,
  `start_time` datetime(6) NOT NULL,
  `end_time` datetime(6) NOT NULL,
  `ready` tinyint(1) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `games_game`
--

LOCK TABLES `games_game` WRITE;
/*!40000 ALTER TABLE `games_game` DISABLE KEYS */;
/*!40000 ALTER TABLE `games_game` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `games_gameplayer`
--

DROP TABLE IF EXISTS `games_gameplayer`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `games_gameplayer` (
  `id` bigint NOT NULL AUTO_INCREMENT,
  `wg_pubkey` varchar(255) DEFAULT NULL,
  `game_id_id` bigint NOT NULL,
  `team_id_id` bigint NOT NULL,
  `user_id_id` int NOT NULL,
  PRIMARY KEY (`id`),
  KEY `games_gameplayer_game_id_id_01ffb288_fk_games_game_id` (`game_id_id`),
  KEY `games_gameplayer_team_id_id_e3a2f2a5_fk_games_teamref_id` (`team_id_id`),
  KEY `games_gameplayer_user_id_id_bd4d581e_fk_auth_user_id` (`user_id_id`),
  CONSTRAINT `games_gameplayer_game_id_id_01ffb288_fk_games_game_id` FOREIGN KEY (`game_id_id`) REFERENCES `games_game` (`id`),
  CONSTRAINT `games_gameplayer_team_id_id_e3a2f2a5_fk_games_teamref_id` FOREIGN KEY (`team_id_id`) REFERENCES `games_teamref` (`id`),
  CONSTRAINT `games_gameplayer_user_id_id_bd4d581e_fk_auth_user_id` FOREIGN KEY (`user_id_id`) REFERENCES `auth_user` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `games_gameplayer`
--

LOCK TABLES `games_gameplayer` WRITE;
/*!40000 ALTER TABLE `games_gameplayer` DISABLE KEYS */;
/*!40000 ALTER TABLE `games_gameplayer` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `games_gamescore`
--

DROP TABLE IF EXISTS `games_gamescore`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `games_gamescore` (
  `id` bigint NOT NULL AUTO_INCREMENT,
  `score` bigint unsigned NOT NULL,
  `game_id_id` bigint NOT NULL,
  `team_id_id` bigint NOT NULL,
  PRIMARY KEY (`id`),
  KEY `games_gamescore_game_id_id_731cc5cf_fk_games_game_id` (`game_id_id`),
  KEY `games_gamescore_team_id_id_2df4825b_fk_games_teamref_id` (`team_id_id`),
  CONSTRAINT `games_gamescore_game_id_id_731cc5cf_fk_games_game_id` FOREIGN KEY (`game_id_id`) REFERENCES `games_game` (`id`),
  CONSTRAINT `games_gamescore_team_id_id_2df4825b_fk_games_teamref_id` FOREIGN KEY (`team_id_id`) REFERENCES `games_teamref` (`id`),
  CONSTRAINT `games_gamescore_chk_1` CHECK ((`score` >= 0))
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `games_gamescore`
--

LOCK TABLES `games_gamescore` WRITE;
/*!40000 ALTER TABLE `games_gamescore` DISABLE KEYS */;
/*!40000 ALTER TABLE `games_gamescore` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `games_gamescoring`
--

DROP TABLE IF EXISTS `games_gamescoring`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `games_gamescoring` (
  `id` bigint NOT NULL AUTO_INCREMENT,
  `result` varchar(255) DEFAULT NULL,
  `polled` datetime(6) NOT NULL,
  `game_id_id` bigint NOT NULL,
  `service_id_id` bigint NOT NULL,
  `team_id_id` bigint NOT NULL,
  PRIMARY KEY (`id`),
  KEY `games_gamescoring_game_id_id_d68fdf7d_fk_games_game_id` (`game_id_id`),
  KEY `games_gamescoring_service_id_id_b5493757_fk_games_gameservice_id` (`service_id_id`),
  KEY `games_gamescoring_team_id_id_31da7392_fk_games_teamref_id` (`team_id_id`),
  CONSTRAINT `games_gamescoring_game_id_id_d68fdf7d_fk_games_game_id` FOREIGN KEY (`game_id_id`) REFERENCES `games_game` (`id`),
  CONSTRAINT `games_gamescoring_service_id_id_b5493757_fk_games_gameservice_id` FOREIGN KEY (`service_id_id`) REFERENCES `games_gameservice` (`id`),
  CONSTRAINT `games_gamescoring_team_id_id_31da7392_fk_games_teamref_id` FOREIGN KEY (`team_id_id`) REFERENCES `games_teamref` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `games_gamescoring`
--

LOCK TABLES `games_gamescoring` WRITE;
/*!40000 ALTER TABLE `games_gamescoring` DISABLE KEYS */;
/*!40000 ALTER TABLE `games_gamescoring` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `games_gameservice`
--

DROP TABLE IF EXISTS `games_gameservice`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `games_gameservice` (
  `id` bigint NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL,
  `type` varchar(255) DEFAULT NULL,
  `game_id_id` bigint NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `name` (`name`),
  KEY `games_gameservice_game_id_id_db349d91_fk_games_game_id` (`game_id_id`),
  CONSTRAINT `games_gameservice_game_id_id_db349d91_fk_games_game_id` FOREIGN KEY (`game_id_id`) REFERENCES `games_game` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `games_gameservice`
--

LOCK TABLES `games_gameservice` WRITE;
/*!40000 ALTER TABLE `games_gameservice` DISABLE KEYS */;
/*!40000 ALTER TABLE `games_gameservice` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `games_teamref`
--

DROP TABLE IF EXISTS `games_teamref`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `games_teamref` (
  `id` bigint NOT NULL AUTO_INCREMENT,
  `name` varchar(256) NOT NULL,
  `color` int unsigned NOT NULL,
  `flag` varchar(256) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `name` (`name`),
  UNIQUE KEY `color` (`color`),
  UNIQUE KEY `flag` (`flag`),
  CONSTRAINT `games_teamref_chk_1` CHECK ((`color` >= 0))
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `games_teamref`
--

LOCK TABLES `games_teamref` WRITE;
/*!40000 ALTER TABLE `games_teamref` DISABLE KEYS */;
/*!40000 ALTER TABLE `games_teamref` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2023-02-13 11:05:16
