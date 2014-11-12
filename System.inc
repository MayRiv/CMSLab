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
		ob_start();
		
	
		echo "<html>
				<head>
					<link rel=\"stylesheet\" type=\"text/css\" href=\"css/feed.css\"/>
					<meta http-equiv = \"content-language\" content = \"ru\" />
					<script src=\"js/script.js\".>
					</script>
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
		ob_end_flush();
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
		$query = "select * from  news where";
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


		$pages = SQL($query,$params)->getAll();
		return $pages;
	}
}

?>

