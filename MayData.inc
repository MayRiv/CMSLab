<?php
class MayData
{
	private $STH;
	public $array;
	public function __construct($STH)
	{
		$this->STH = $STH;
		$this->array = $STH->fetchAll();
		
	}
	public function write()
	{
		foreach($this->array as $row)
		{
			foreach($row as $cell)
				echo $cell.'|';
			echo "<br>";
		}
	
	}
	
}

?>