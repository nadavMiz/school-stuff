CREATE DATABASE SmartBuilding;

use SmartBuilding;

CREATE TABLE Info (
				    section_name VARCHAR(256),
                    ip VARCHAR(256),
					msg_port INT,
					registration_port INT
				  );

CREATE TABLE Agents (
					id INT PRIMARY KEY AUTO_INCREMENT,
                    config VARCHAR(256),
                    location_id INT,
                    type_id INT,
                    log_id INT
                    );
                    
CREATE TABLE AgentType	(
						id INT PRIMARY KEY AUTO_INCREMENT,
                        agent_type VARCHAR(32),
                        description VARCHAR(256),
                        log_name VARCHAR(256),
                        so_name VARCHAR(256)
                        );
                        
CREATE TABLE Loger	(
					id INT PRIMARY KEY AUTO_INCREMENT,
					time_t TIMESTAMP,
                    status_t VARCHAR(32),
                    message VARCHAR(256),
                    agent_id INT,
                    category VARCHAR(32)
                    );

CREATE TABLE Location	(
						id INT PRIMARY KEY AUTO_INCREMENT,
                        building VARCHAR(256),
                        floor INT,
                        room VARCHAR(32)
                        );
                        
CREATE TABLE AgentEvents	(
							id INT PRIMARY KEY AUTO_INCREMENT,
							time_t TIMESTAMP,
                            agent_id INT,
                            details VARCHAR(256),
                            event_type VARCHAR(32)
                            );
                            
ALTER TABLE Agents
ADD FOREIGN KEY (type_id) REFERENCES AgentType(id),
ADD FOREIGN KEY (location_id) REFERENCES Location(id);

ALTER TABLE AgentEvents
ADD FOREIGN KEY (agent_id) REFERENCES Agents(id);

INSERT INTO AgentType(agent_type, description, log_name, so_name) VALUES
("TmpSensor", "tmp sensor", "tmpSensor.log", "nadavSensors.so"),
("fireSensor", "fire sensor", "fireSensor.log", "nadavElectric.so"),
("HVAC", "air conditioner", "hvac.log", "nadavElectric.so"),
("sprinkler", "sprinkler", "sprinkler.log", "nadavElectric.so"),
("interhubSprinkler", "interhubSprinkler", "interhubSprinkler.log", "nadavElectric.so"),
("bad_device", "tmp sensor", NULL, "badDeviceCorp.so");

INSERT INTO Location(building, floor, room) VALUES
("nadav corp. HQ", 1, "room-1-a");

INSERT INTO Agents(config, location_id, type_id) VALUES
("lower: -5 upper: 50 period: 1", 1, 1),
("low: 15 high: 30", 1, 3),
("low: 15 high: 30", 1, 3),
("low: 15 high: 30", 1, 4),
("low: 15 high: 30", 1, 3),
("low: 15 high: 30", 1, 3),
("low: 15 high: 30", 1, 4),
("low: 15 high: 30", 1, 5),
("low: 15 high: 30", 1, 4);

INSERT INTO Info(section_name, ip, msg_port, registration_port) VALUES
("mainHub", "127.0.0.1", 2004, 2003);

SELECT * FROM SmartBuilding.AgentType;
