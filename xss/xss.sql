USE xss; 

CREATE TABLE user (
  username VARCHAR(30) PRIMARY KEY,
  password VARCHAR(30) NOT NULL,
  name VARCHAR(50) NOT NULL
);
