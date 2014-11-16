<?php

	require("viewer.inc");
	require("DBManager.inc");
	require("System.inc");
	$host = "localhost";
	$dbName = "MayNews";
	$user = "root";
	$password = "";
	DBManager::getInstance()->connect($host, $dbName, $user, $password);

	if (!isset($_GET["pageId"]))
		System::getInstance()->showPage(1);
	else
		System::getInstance()->showPage(intval($_GET["pageId"]));

?>