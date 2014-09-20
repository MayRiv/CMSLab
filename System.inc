<?php
	require("Page.inc");
class System 
{
	private static $_instance;
	public static  function getInstance()
	{
		if (System::$_instance == null) System::$_instance = new System();
		return System::$_instance;
	}

	private function __construct()
	{
		# code...
	}
	
	public function showPage($id)
	{
		
		echo "<html>
				<head>
					<link rel=\"stylesheet\" type=\"text/css\" href=\"css/feed.css\"/>
					<meta http-equiv = \"content-language\" content = \"ru\" />
				</head>
				<body>";

		
		$p = new Page($id);
		while($p->instanceOf != null)
		{
			$p = new Page($p->instanceOf);
		}
		$this->showHeader();
		echo "<div id='menu'>";
		$this->showMenu($this->getParents($id));
		echo "</div>";
		$p->publish();
		$this->showFooter();

		echo "	</body>
			  </html>";
	}
	public function showHeader()
	{
		getView("header.inc",null);
	}
	public function showFooter()
	{
		getView("Footer.inc",null);
	}

	private function showMenu($parentPages, $parent = null, $level = 1)
	{	
		$margin = 10;
		$pages = $this->getChildPages($parentPages, $parent);

		for ($i=0; $i < count($pages); $i++) { 
			if ($pages[$i]["InstanceOf"] != null)
				$page = new Page($pages[$i]["InstanceOf"]);
			else 
				$page = new Page($pages[$i]["Id"]);
		
			$title = $page->title;
			$id = $page->id;

			echo "<div style=\"margin:" . $level * $margin . "px \"><a href=\"index.php?pageId=" .$id
			."\">" . $title . "</a></div>";
			if (in_array($page, $parentPages))
				$this->showMenu($parentPages,$pages[$i], $level + 1);

		}
	}
	private function getParents($id)
	{
		$parentPages = array();

	  	$page = new Page($id);
	  	array_push($parentPages, $page);
	  	while($page->parentId != null)
	  	{	
	   		$page = new Page ($page->parentId)   	;	
	   		array_push($parentPages, $page);
	  	}
	  	return $parentPages;
	}
	private function getChildPages($parentPages, $parent = null)
	{
		$sortField = $parent["sortField"];
		$query = "Select * from( select * from  news where";
		$params = array();
		
		if ($parent == null)
		{
			$query = $query . " ISNULL(ParentId)";
			array_push($params, null);
		}
		else
		{
			$query = $query . " ParentId = ? order by " . $sortField;
			array_push($params, $parent["Id"]);			 
		}

		$query = $query . ") as t ";
		
		
		/*
		if (isset($_GET['f']) )
		{
			$filters = explode('-', $_GET['f']);
			$filtersOb = array();
			
			$queryFilters = "select * from filtervalues where filtervalueid = ?";
			
			for($i=1; $i < count($filters); $i++){
				$queryFilters = $queryFilters . " or filtervalueid = ? ";
				
			}
			$queryFilters = $queryFilters . " order by filterid";

			$array = SQL($queryFilters, $filters)->getAll();
			//var_dump($array);
			//echo $queryFilters;
			$i = 0;
			while( $i < count($array)) { 
				$query = $query . " inner JOIN (
								   SELECT *
								   FROM news
								   INNER JOIN filtervaluesnews ON ( id = newsid )
								   INNER JOIN filtervalues T
								   USING ( filtervalueid )
							       WHERE filtervalueid = " . intval($array[$i]["FilterValueId"]);
				$j = 0;
			    while($i + $j < count($array) - 1 && $array[$i + $j]["FilterId"] == $array[$i + 1 + $j]["FilterId"])
				{
					$query = $query . " or filtervalueid = " . intval( $array[$i + 1 + $j]["FilterValueId"]);
					$j++;					
				}
				$i += $j;
				$query = $query . ") AS t" . $i. "
									USING ( id ) ";
				$i++;
				
			}
		}

		*/
		$pages = SQL($query,$params)->getAll();
		//var_dump($pages);
		return $pages;
	}
}

?>

