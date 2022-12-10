USE injection; 

CREATE TABLE users (
  userID INT PRIMARY KEY,
  username VARCHAR(30) NOT NULL,
  password VARCHAR(30) NOT NULL
);

INSERT INTO injection.users (userID, username, password) VALUES (1, 'Bob', 'password');
INSERT INTO injection.users (userID, username, password) VALUES (2, 'Alice', 'test');
INSERT INTO injection.users (userID, username, password) VALUES (3, 'Eve', 'sneaky');
INSERT INTO injection.users (userID, username, password) VALUES (4, 'Steve', 'banana');




