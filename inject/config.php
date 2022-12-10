<?php

$host = "localhost";
$username = "root";
$password = "password";
$dbname = "injection";
$dsn = "mysql:host=$host;dbname=$dbname";
$options = array( 
		PDO::ATTR_ERRMODE => PDO::ERRMODE_EXCEPTION 
	);
