<?php
	require("DBManager.inc");
	require("NewsPage.inc");
	require("viewer.inc");
	if (!is_null($_GET["id"]))
		$id = intval($_GET["id"]);
	$host = "localhost";
	$dbName = "MayNews";
	$user = "root";
	$password = "";
	DBManager::getInstance()->connect($host, $dbName, $user, $password);
	$result = SQL("select * from news where id=?",array($id));
	$page = new NewsPage($result->getAll()[0]);
	getView("page.inc",$page);
?>