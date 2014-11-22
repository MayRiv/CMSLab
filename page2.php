<?php
require("Table.inc");


$table = new Table('News', 'News', 'Id', 'page2.php');

$arr1 = array('table' => 'News', 'field' => 'id','isRequired' => false);

//$arr2 = array('table' => 'entities','field' => 'entityid', 'captionfield' => 'caption','isRequired' => false);

//name type caption formPref cssClass defaultvalue isvisiblebr isvisible isAutInc 
/*
$table->addField('id',            'varchar', 'Id',               'page_', 'input-txt-primary', 'page1');
$table->addField('parentpage',    'varchar', 'Батьківська ст.',  'page_', 'input-txt', 'default');
$table->addField('aliasof',        $arr1,    'Псевдонім',        'page_', 'input-combo');
$table->addField('sortindex',     'int',     'Номер при сорт.',  'page_', 'input-txt', 0);
$table->addField('caption',       'varchar', 'Заголовок',        'page_', 'input-txt', 'Заголовок');
$table->addField('shortcaption',  'varchar', 'Корот. заголовок', 'page_', 'input-txt', 'Заг.');
$table->addField('description',   'varchar', 'Опис',             'page_', 'input-txt', '', false);
$table->addField('image',         'varchar', 'Картинка',         'page_', 'input-txt', '', false);
$table->addField('content',       'html',    'Контент',          'page_', 'input-html', '', false);
$table->addField('containertype', 'varchar', 'Тип контейнеру',   'page_', 'input-txt');
$table->addField('sorttype',      'varchar', 'Тип сортування',   'page_', 'input-txt');
$table->addField('hidemenu',      'bool',    'Чи є у меню',      'page_', 'input-chbox');
$table->addField('creationdate',  'date',    'Дата створ.',      'page_', 'input-date', '', false, false);
$table->addField('changedate',    'date',    'Дата зміни',       'page_', 'input-date', '', false, false);
$table->addField('childentity',    $arr2,     'Дочірня кат.',    'page_', 'input-combo', '', false);
$table->addField('entity',         $arr2,     'Категорія',       'page_', 'input-combo');
$table->addField('price',         'double',  'Ціна',             'page_', 'input-txt', -2);
*/	$table->addField('Id','int','Id','','','null',false,false,true);
	//$table->addField('InstanceOf','id','InstanceOf','','input-txt');
	

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