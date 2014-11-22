<?php
	require("Table.inc");


	$table = new Table('News', 'News', 'Id', 'page.php');

	$arr1 = array('table' => 'News', 'field' => 'id','isRequired' => false);

	$table->addField('Id','int','Id','','','null',false,false,true);
	
	$table->addField('Title','varchar','Title','','input-txt');

	$table->addField('Body','varchar','Body','','input-txt');
	$table->addField('ParentId',$arr1,'ParentId','','input-txt');
	
	$table->addField('sortField','varchar','SortField','','input-txt');
	
	$table->addField('IsContainer','int','IsContainer','','input-txt');
function beforeUpdateListener($params)
{
	//echo 'listenerBeforeWorks ';
}

function afterUpdateListener($params)
{
	//echo 'listenerAfterWorks ';
}

$table->addEventListener('beforeUpdate', 'beforeUpdateListener');
$table->addEventListener('afterUpdate', 'afterUpdateListener');
$table->addEventListener('beforeInsert', 'beforeUpdateListener');
$table->addEventListener('afterInsert', 'afterUpdateListener');
$table->addEventListener('beforeDelete', 'beforeUpdateListener');
$table->addEventListener('afterDelete', 'afterUpdateListener');

$table->addHeader('adminHeader.php');
$table->addFooter('adminFooter.php');

$table->mainProcess();

?>