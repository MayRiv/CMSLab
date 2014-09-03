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
		$this->showContent($p);
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
	public function showContent($page)
	{
	
		$content = array('title' =>$page->title,'body'=>$page->body );
		getView("Content.inc",$content);	
	}

	private function showMenu($parentPages, $parent = null, $level = 1)
	{	
		$margin = 10;
		$sortField = $parent["sortField"];
		if ($parent == null) 
			$pages = SQL("Select * from news where ISNULL(ParentId)",null)->getAll();
		else 
			$pages = SQL("Select * from news where ParentId = ? order by ".$sortField,array($parent["Id"]))->getAll();
		
		
		for ($i=0; $i < count($pages); $i++) { 
			if ($pages[$i]["InstanceOf"] != null)
				$page = new Page($pages[$i]["InstanceOf"]);
			else 
				$page = new Page($pages[$i]["Id"]);
			
			$title = $page->title;
			$id = $page->id;

			echo "<div style=\"margin:" . $level * $margin . "px \"><a href=\"index.php?pageId=" .$id
			."\">" . $title . "</a></div>";
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
	   		$page = SQL('select * from news where id = ?',array($page['ParentId']))->next();   		
	   		array_push($parentPages, $page);
	   		if ($page['ParentId'] == null) break;
	  	}
	  	return $parentPages;
	}

}

?>