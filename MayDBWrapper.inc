<?php
require("MayData.inc");
class MayDBWrapper
{

	private $DBH;
	function __construct($host,$dbName,$user,$password)
	{
		$this->DBH = new PDO("mysql:host=$host;dbname=$dbName",$user,$password);
		$this->DBH->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_WARNING);
	}
	public function sql($query, $param)
	{
		//echo $query;
		$STH = $this->DBH->prepare($query);
		$STH->execute($param);
		return new MayData($STH);
	}
	public function dsql($query,$param)
	{
		
		$array = explode('?',$query);
		$result ="";
		for( $i = 0; $i < count($array) - 1;$i++)
		{
			$result.=$array[$i].$this->DBH->quote($param[$i]);
		}
		$result.=$array[count($array) - 1];
		echo $result;
	}

}
?>