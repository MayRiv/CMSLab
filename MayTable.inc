<?php
require("MayField.inc");
require_once("DBManager.inc");

class Table
{
	private $name;
	private $caption;
	private $primaryKey;
	private $currentAction;   //browse  edit  insert

	private $fields;
	private $currentRowVal;
	private $scriptName;

	private $eventHandlers;

	private $isExec = false;
	private $isHTMLEditorNeed;

	private $header;
	private $footer;
	private $css;
	public function __construct($name, $caption, $primaryKey, $scriptName)
	{
		$this->name = $name;
		$this->caption = $caption;
		$this->primaryKey = $primaryKey;
		$this->scriptName = $scriptName;
		$this->fields = array();


		$this->currentAction = "browse";

		if(isset($_GET['action']))
		{
			$this->currentAction = $_GET['action'];
		}

		if($this->currentAction == 'edit')
		{
			DBManager::getInstance()->connect("localhost", "maynews", "root", "");
			$this->currentRowVal = SQL("select * from ".$this->name." where ".$this->primaryKey." = ?",array($_GET['id']))->next();
		}
		
		if($this->currentAction == 'browse' && !empty($_POST))
		{
			$this->isExec = true;
		}
	}
	public function addField($name, $type, $caption, $formPrefix, 
		$cssClass, $defaultValue = "", $isVisibleBr = true, $isVisible = true, $isAutoInc = false)
	{
		$value = $this->currentRowVal[$name];
		if($this->isExec)
		{
			 $value = (isset($_POST[$formPrefix.$name]))? $_POST[$formPrefix.$name] : $defaultValue;
		}
		if($type == 'html')
		{
			$this->isHTMLEditorNeed = true;
		}

		$this->fields[] = new Field($name, $type, $caption, $formPrefix, 
			$cssClass, $defaultValue, $isVisibleBr, $isVisible, $value, $isAutoInc);
	}
	public function mainProcess()
	{
		if($this->isExec)
		{
			$params = array();
			$isUpdate = isset($_POST['old_'.$this->primaryKey]);
			foreach ($this->fields as $f) {
				if(!$isUpdate ||($isUpdate && $f->isVisible()))
				{
					$params[] = $f->getSQLValue();
				}
			}


			if($isUpdate)
			{
				
				//$params[] = $_POST['old_'.$this->primaryKey];
				array_push($params, $_POST['old_'.$this->primaryKey]);
				
				try
				{
					DBManager::getInstance()->connect("localhost", "maynews", "root", "");
					SQL($this->generateSQL('update'), $params);
				}
				catch(PDOException $e)
				{
					echo 'Update error';
				}
			}
			else
			{
				//$this->createEvent('beforeInsert');
				try
				{
					DBManager::getInstance()->connect("localhost", "maynews", "root", "");
					SQL($this->generateSQL('insert'), $params);
				}
				catch(PDOException $e) 
				{
					echo 'Insert error';
				}		
			}
		}

		/*if (isset($this->header)) 
		{
			include($this->header);	
		}
		if($this->isHTMLEditorNeed == true)
		{
			echo '<script src="ckeditor/ckeditor.js" ></script>';
		}
		*/
		switch($this->currentAction)
		{
			case 'browse':
				$this->browse();
				break;
			case 'edit':
				$this->edit();
				break;
			case 'insert':
				$this->insert();
				break;
			case 'delete':
				{
					//$this->createEvent('beforeDelete');
					DBManager::getInstance()->connect("localhost", "maynews", "root", "");

					SQL($this->generateSQL('delete'), array($_GET['id']));

					
					$this->browse();
					break;
				}
			default:
				echo 'such mod not found';
		}
	}
	private function browse()
	{
		DBManager::getInstance()->connect("localhost", "maynews", "root", "");
		$rows = SQL("select * from ".$this->name)->getAll();

		echo "<a class='addlink' href = '".$this->scriptName."?action=insert'><img src='Pictures/add.png'> <span>Add new record</span></a>";
		echo "<table class = 'browsetable'>";
		echo "<tr id='tablecaption'> <td colspan = '100'>".$this->caption."</td> </tr>";
		echo "<tr id='tableheader'>";
		echo "<td>Edit.</td>";
		echo "<td>Delete.</td>";
		foreach ($this->fields as $f) {			
			if($f->isVisibleBrowse() == 'true')
			{
				echo "<td>";
				echo $f->getCaption();
				echo "</td>";
			}
		}
		echo "</tr>";
		foreach ($rows as $row) 
		{
			echo "<tr>";
			echo "<td class = 'changelink'>";
			echo "<a href = '".$this->scriptName."?action=edit&id=".$row[$this->primaryKey]."'><img src='Pictures/edit.png'></a>";
			echo "</td>";
			echo "<td class = 'deletelink'>";
			$t = "onclick=\"return confirm('Are you sure?')\"";
			echo "<a href = '".$this->scriptName."?action=delete&id=".$row[$this->primaryKey]."'".$t." ><img src='Pictures/delete.png'></a>";
			echo "</td>";
			foreach ($this->fields as $f) 
			{
				if($f->isVisibleBrowse() == 'true')
				{
					echo "<td>";
					echo Field::prepareValue($row[$f->getName()]);
					echo "</td>";
				}
			}
			echo "</tr>";
		}
		echo "</table>";
	}
	private function edit()
	{
		echo "<div id = 'edittable'>";
		$this->createForm();
		echo "</div>";
	}

	private function insert()
	{
		echo "<div id = 'edittable'>";
		$this->createForm();
		echo "</div>";
	}

	private function createForm()
	{
		echo "<form action='".$this->scriptName."' method='post'>";
		echo "<table>";
		foreach ($this->fields as $f) {
			if (!$f->isAutoInc() && $f->isVisible())
			{
				if($f->getName() == $this->primaryKey)
				{
					echo "<tr id='txt-primary'>";
				}
				else
				{
					echo "<tr>";
				}
				
				if($f->getType() == 'html')
				{
					echo "<td colspan='2'><p>".$f->getCaption()."</p>".$f->createControl()."</td>";
				}
				else
				{
					echo "<td>".$f->getCaption()."</td>";
					echo "<td>".$f->createControl()."</td>";
				}
			

			echo "</tr>";
			}	
		}
		if($this->currentAction == 'edit')
		{
			$pkValue = "";
			foreach ($this->fields as $f) 
			{
				if($f->getName() == $this->primaryKey)
				{
					$pkValue = $f->getHTMLValue();
				}
			}
			echo "<tr> <td> <input type='hidden' name='old_".$this->primaryKey."' value='".$pkValue."'> </td> </tr>";
		}
		echo "<tr> <td colspan = '2'> <input type='submit' class = 'input-submit'> </td></tr>";
		echo "</table>";
		echo "</form>";
	}
	private function generateSQL($type)
	{
		$query = "";

		switch($type)
		{
			case 'insert':
			{
				$query = "INSERT INTO ".$this->name." VALUES( ";
				foreach ($this->fields as $f) {
					$query .= '?,';
				}
				$query = substr($query, 0, -1);
				$query .= " )";
				return $query;
			}
			case 'update':
			{
				$query .= "UPDATE ".$this->name." SET ";
			    foreach ($this->fields as $f) 
			    {
					if($f->isVisible())
					{
						$query .= $f->getName().' = ?,';
					}
				}
				$query = substr($query, 0, -1);
				$query .= " where ".$this->primaryKey." = ?";

				return $query;
			}
			case 'delete':
			{
			    return "DELETE FROM ".$this->name." WHERE ".$this->primaryKey." = ?";
			}
		}
	}
}

?>