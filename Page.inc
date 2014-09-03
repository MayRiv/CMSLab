<?php 
class Page
{
	public $id;
	public $body;
	public $title;
	public $instanceOf;
	public $sortField;
	public function __construct($id)
	{
		$page = SQL('Select * from news where id = ?', array($id))->getAll()[0];
		$this->id = $id;
		$this->body =$page['Body'];
		$this->title = $page['Title'];
		$this->instanceOf = $page['InstanceOf'];
		$this->parentId = $page['ParentId'];
		$this->sortField = $page['sortField'];
	}
	
}

?>