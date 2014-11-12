<?php
	require("MayTable.inc");
	$entity = new Table('News','News\'s Table','Id','newsAdmin.php');
	$entity->addField('Id','int','Id','','','null',false,false,true);
	$entity->addField('InstanceOf','int','InstanceOf','','input-txt');
	
	$entity->addField('Title','varchar','Title','','input-txt');

	$entity->addField('Body','varchar','Body','','input-txt');
	$entity->addField('ParentId','int','ParentId','','input-txt');
	
	$entity->addField('sortField','varchar','SortField','','input-txt');
	
	$entity->addField('IsContainer','int','IsContainer','','input-txt');
	$entity->mainProcess();


?>