<?php
	require "TreeTable.inc";

	$table = new TreeTable('News', 'News', 'Id', 'treepage.php', 'ParentId', 'Дочірні сторінки', 'null');
	$arr1 = array('table' => 'News', 'field' => 'id','isRequired' => false);

	$table->addField('Id','int','Id','','','null',false,false,true);
	//$table->addField('InstanceOf','id','InstanceOf','','input-txt');

	$table->addField('Title','varchar','Title','','input-txt');

	$table->addField('Body','varchar','Body','','input-txt');
	$table->addField('ParentId',$arr1,'ParentId','','input-txt');
	
	$table->addField('sortField','varchar','SortField','','input-txt');
	
	$table->addField('IsContainer','int','IsContainer','','input-txt');


	$table->addHeader('adminHeader.php');
	$table->addFooter('adminFooter.php');

	$table->mainProcess();
?>