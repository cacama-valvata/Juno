-- Initial Database

CREATE DATABASE Juno;
USE Juno;

-- Users and Auth Tables

CREATE TABLE users (
	userid INT UNSIGNED NOT NULL,
	username VARCHAR(255) NOT NULL,
	score INT UNSIGNED NOT NULL,
	PRIMARY KEY (userid)
);

CREATE TABLE devices (
	keyname VARCHAR(255) NOT NULL,
	ssh_prefix VARCHAR(63) NOT NULL,
	ssh_pubkey VARCHAR(600) NOT NULL,
	ssh_suffix VARCHAR(255) NOT NULL,
	userid INT UNSIGNED NOT NULL,
	last_seen DATETIME,
	PRIMARY KEY (ssh_pubkey),
	FOREIGN KEY (userid) REFERENCES users(userid)
);

CREATE TABLE user_auth (
	userid INT UNSIGNED NOT NULL,
	hash VARCHAR(600) NOT NULL,
	salt VARCHAR(255) NOT NULL,
	FOREIGN KEY (userid) REFERENCES users(userid)
);

-- Teams Tables (reference data, is reused each game but not edited)

CREATE TABLE teams_reference (
	teamid INT UNSIGNED NOT NULL,
	name VARCHAR(63) NOT NULL UNIQUE,
	color MEDIUMINT UNSIGNED NOT NULL UNIQUE,
	flag VARCHAR(255) NOT NULL UNIQUE,
	PRIMARY KEY (teamid)
);

-- Games Tables

CREATE TABLE games (
	gameid INT UNSIGNED NOT NULL,
	start_time DATETIME NOT NULL,
	end_time DATETIME NOT NULL,
	ready BOOL NOT NULL,
	PRIMARY KEY (gameid)
);

CREATE TABLE game_players (
	gameid INT UNSIGNED NOT NULL,
	userid INT UNSIGNED NOT NULL,
	teamid INT UNSIGNED NOT NULL,
	wg_pubkey VARCHAR(255),
	FOREIGN KEY (gameid) REFERENCES games(gameid),
	FOREIGN KEY (userid) REFERENCES users(userid),
	FOREIGN KEY (teamid) REFERENCES teams_reference(teamid)
);

CREATE TABLE games_scores (
	gameid INT UNSIGNED NOT NULL,
	userid INT UNSIGNED NOT NULL,
	score INT UNSIGNED NOT NULL,
	FOREIGN KEY (gameid) REFERENCES games(gameid),
	FOREIGN KEY (userid) REFERENCES users(userid)
);

-- Temporary Game Tables - are generated per each game and then deleted once complete
-- 	- Replace gameid with the true gameid when creating the table
--	- Use this 'create table' command as a template when writing and executing your own

-- Note on this table:
-- 	- Service type is mostly a placeholder
--	- Need some way to record/encode a payload for the scorechecker
CREATE TABLE __gameid_services (
	serviceid INT UNSIGNED NOT NULL,
	service_name VARCHAR(255) NOT NULL UNIQUE,
	service_type VARCHAR(255),
	PRIMARY KEY (serviceid)
);

-- Note:
--	- 'result' will be either a team's flag or NULL
CREATE TABLE __gameid_scoring (
	serviceid INT UNSIGNED NOT NULL,
	teamid INT UNSIGNED NOT NULL,
	result VARCHAR(255),
	polled DATETIME NOT NULL,
	FOREIGN KEY (serviceid) REFERENCES __gameid_services(serviceid),
	FOREIGN KEY (teamid) REFERENCES teams_reference(teamid)
);

