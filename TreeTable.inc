<?php
require_once("Table.inc");

class TreeTable extends Table
{
	private $parentField;
	private $parentCaption;
	private $defaultParentId;

	public function __construct($name, $caption, $primaryKey, $scriptName, $parentField, $parentCaption, $defaultParentId)
	{
		parent::__construct($name, $caption, $primaryKey, $scriptName);
		$this->parentField = $parentField;
		$this->parentCaption = $parentCaption;
		$this->defaultParentId = $defaultParentId;
	}

	protected function browse()
	{
		$select = "select ";
        $what = "*";
		$from = " from ".$this->name;
	    
	    if($this->isHasCombo)
	    {
	    	$what = "";
	    	foreach ($this->fields as $f) {	    			    		
	    		$what .= $f->getName().", ";
	    		if($f->isLookup() != false)
	    		{
	    			$lookInf = $f->getLookupInfo();
	    			if($this->name != $lookInf['table'])
	    			{
	    				$n = $f->getName();
	    				$what .= "if (".$n." = '' || isnull(".$n."), ".$n.", ( select ".
	    				$lookInf['table'].".".$lookInf['captionfield']." from ".$lookInf['table']." where ".
	    				$lookInf['table'].".".$lookInf['field']." = ".$this->name.".".$f->getName().")) as ".$f->getName()."_combo, ";
	    			}
	    			else
	    			{
	    				$what .= $f->getName().", ";
	    			}
	    		}
	    	}
	    	$what = substr($what, 0, -2);
		}

		if(isset($this->parentField))
		{
			$from .= ' where ';		
			$temp = '';	
			if(isset($_GET['parentId']))
			{
				$temp = $_GET['parentId'];		
			}
			else
			{
				$temp = $this->defaultParentId;		
			}
			$from .= $this->parentField." = '$temp'";//' and ';
		}
		DBManager::getInstance()->connect("localhost", "maynews", "root", "");
		$rows = SQL($select.$what.$from)->getAll();

		$mId = '';
		if(isset($this->parentField) )
		{
			if(isset($_GET['parentId']))
			{
				$mId = '&parentId='.$_GET['parentId'];	
			}
			else
			{
				$mId = '&parentId='.$this->defaultParentId;
			}
		}

		echo "<a class='addlink' href = '".$this->scriptName."?action=insert".$mId."''><img src='images/add_icon.png'> <span>Додати новий запис</span></a>";
		echo "<table class = 'browsetable'>";
		echo "<tr id='tablecaption'>";
		if(isset($this->parentField) && isset($_GET['parentId']))
		{
			echo "<p><a class='backlink' href='".$this->getBrowseReference($_GET['parentId'], $this->getPrimaryKey())."'>До батьківської сторінки</a></p>";			
		}
		//<td></td> 
		echo "<td colspan = '100'>".$this->caption."</td> </tr>";
		echo "<tr id='tableheader'>";
		echo "<td>Змін.</td>";
		echo "<td>Вид.</td>";
		if(isset($this->parentField))
		{
			echo '<td>Дочірня. Ст.</td>';
		}
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
			echo "<a href = '".$this->scriptName."?action=edit&id=".$this->getPrimaryKeyValueFrom($row)."'><img src='images/edit_icon.png'></a>";
			echo "</td>";
			echo "<td class = 'deletelink'>";
			$t = "onclick=\"return confirm('Видалити запис?')\"";
			echo "<a href = '".$this->scriptName."?action=delete&id=".$this->getPrimaryKeyValueFrom($row)."'".$t." ><img src='images/delete_icon.png'></a>";
			echo "</td>";

			if(isset($this->parentField))
			{
				echo '<td>';
				echo "<a class='detaillink' href='".$this->getScriptName()."?parentId=".$this->getPrimaryKeyValueFrom($row)."'>".$this->parentCaption."</a>";
				echo '</td>';				
			}

			foreach ($this->fields as $f) 
			{
				if($f->isVisibleBrowse() == 'true')
				{
					echo "<td>";
					if($f->isLookup() && ($this->name != $f->getLookupInfo()['table']))
					{
						echo Field::prepareValue($row[$f->getName().'_combo']);
					}
					else
					{
						echo Field::prepareValue($row[$f->getName()]);			
					}
					echo "</td>";
				}
			}
			echo "</tr>";
		}
		echo "</table>";
	}

	protected function createForm()
	{
		$mId = '';
		if($this->currentAction == 'insert' && isset($_GET['mainId']))
		{
			$mId = '?mainId='.$_GET['mainId'];
		}

		echo "<form action='".$this->scriptName.$mId."' method='post'>";
		echo "<table>";
		foreach ($this->fields as $f) {
			if($f->isAutoInc() == false && $f->isVisible() == true)
			{
				if($this->compareWithPrimaryKey($f->getName()))
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
					if($this->currentAction == 'insert' && isset($_GET['parentId']) && $f->getName() == $this->parentField)
					{
						$t = (isset($_GET['parentId'])) ? $_GET['parentId'] : $this->defaultParentId;
						echo "<td>".$f->createControl($t, $this->parentField)."</td>";
					}
					else
					{
						echo "<td>".$f->createControl()."</td>";
					}
				}
				echo "</tr>";	
			}
		}
		if($this->currentAction == 'edit')
		{
			$pkValue = $this->getPrimaryKeyValueFrom();
			echo "<tr> <td> <input type='hidden' name='old_".$this->getPrimaryKey()."' value='".$pkValue."'> </td> </tr>";
		}
		echo "<tr> <td colspan = '2'> <input type='submit' class = 'input-submit'> </td></tr>";
		echo "</table>";
		echo "</form>";
	}

	public function getBrowseReference($mainId, $detailPK)
	{
		$reference = $this->scriptName;
		if(isset($this->parentField))
		{
			$query = 'select '.$this->parentField.' from '.$this->name.
					 ' where '.$this->getPrimaryKey()." = '$mainId'";

			DBManager::getInstance()->connect("localhost", "maynews", "root", "");
			$refId = SQL($query)->next();
			if(isset($refId))
			{
				$reference.='?parentId='.$refId[$this->parentField];
			}
			else
			{
				$reference .='?parentId='.$this->defaultParentId;
			}
		}
		return $reference;
	}
}

?>