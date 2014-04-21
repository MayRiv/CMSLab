<?php

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
					<link rel=\"stylesheet\" type=\"text/css\" href=\"css\feed.css\"/>
				</head>
				<body>";
		$this->showHeader();
		$this->showMenu($this->getParents($id));
		$page = SQL("select * from news where id=?",array($id))->next();
		$this->showContent($page);
		$this->showFooter();

		echo "	</body>
			  </html>";
		//$page = new NewsPage($result->getAll()[0]);

	}
	public function showHeader()
	{
		getView("header.inc",null);

	}
	public function showFooter()
	{
		getView("Footer.inc",null);
	}
	public function showContent($content)
	{
		getView("Content.inc",$content);	
	}

	private function showMenu($parentPages, $parent = null, $level = 1)
	{
		
		$margin = 10;

		if ($parent == null) 
			$pages = SQL("Select * from news where ISNULL(parentId)",null)->getAll();
		else 
			$pages = SQL("Select * from news where parentId = ? order by ?",array($parent["id"], $parent["sortField"]))->getAll();
		
	
		for ($i=0; $i < count($pages); $i++) { 
			echo "<div style=\"margin:" . $level * $margin . "px \"><a href=\"index.php?pageId=" . $pages[$i]["id"]
			."\">" . $pages[$i]["title"] . "</a></div>";
			if (in_array($pages[$i], $parentPages))
				$this->showMenu($parentPages,$pages[$i], $level + 1);
		}
	}
	private function getParents($id)
	{
		$parentPages = array();
		$page = SQL("select * from news where id=?",array($id))->next();
		array_push($parentPages, $page);
		while(true)
	  	{	
	   		$page = SQL('select * from news where id = ?',array($page['parentId']))->next();   		
	   		array_push($parentPages, $page);
	   		if ($page['parentId'] == null) break;
	  	}
	  	return $parentPages;
	}

}

?>