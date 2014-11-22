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
		session_start();
	
		echo "<html>
				<head>
					<link rel=\"stylesheet\" type=\"text/css\" href=\"css/feed.css\"/>
					<meta http-equiv = \"content-language\" content = \"ru\" />
					<meta charset=\"UTF-8\"/>
					<script src=\"js/script.js\".>
					</script>
				</head>
				<body>";

		
		$p = new Page($id);
		/*while($p->instanceOf != null)
		{
			$p = new Page($p->instanceOf);
		}*/
		$this->showHeader();
		echo "<div id='menu' class=\"Box\">";
		$this->showMenu($this->getParents($id));
		echo "</div>";

		if(!isset($_GET['fav']))
		{
			$p->publish();
		}
		else
		{
			$this->handleFavourites($p);			
		}

		

		$this->showFilterMenu($p->isContainer);
		$this->showFooter();

		echo "	</body>
			  </html>";
		ob_end_flush();
	}
	private function handleFavourites($p)
	{
		if($_GET['fav'] =='add')
		{
			if(!isset($_SESSION['favourites']))
			{
				$_SESSION['favourites'] = array($p->id => 'title');
			}
			if(!in_array($p->id, $_SESSION['favourites']))
			{
				
				$_SESSION['favourites'][$p->id] =  $p->title;
			}
			$p->publish();			
		}

		if ($_GET['fav'] == 'show')
		{
			$content = array();
			if(isset($_SESSION['favourites']))
			{
				foreach ($_SESSION['favourites'] as $key => $value) {
					 array_push($content, array('title' => $value, 'id' => $key));
				}
			}
			$content['title'] = 'Your favourites';
			getView("Container.inc",$content);
		}
		

	}
	public function showHeader()
	{
		getView("header.inc",null);
	}
	public function showFooter()
	{
		
		getView("Footer.inc",$_COOKIE['path']);
		
	}

	private function showMenu($parentPages, $parent = null, $level = 1)
	{	
		$margin = 10;
		$pages = $this->getChildPages($parentPages, $parent);

		for ($i=0; $i < count($pages); $i++) { 
			/*if ($pages[$i]["InstanceOf"] != null)
				$page = new Page($pages[$i]["InstanceOf"]);
			else*/ 
				$page = new Page($pages[$i]["Id"]);
		
			$title = $page->title;
			$id = $page->id;

			echo "<div style=\"margin:" . $level * $margin . "px \"><a href=\"index.php?pageId=" .$id
			."\">" . $title . "</a></div>";
			if (in_array($page, $parentPages))
				$this->showMenu($parentPages,$pages[$i], $level + 1);

		}
	}
	private function showFilterMenu($isContainer)
	{
		$hidden = '';
		if (!$isContainer)  $hidden = 'style="visibility:hidden"';
		echo "<div id='filter' class='Box'".$hidden." >";

		
		$filtervalueschecked = array();
		if (isset($_GET['f']))
			$filtervalueschecked = explode('-', $_GET['f']);;

			$filters = SQL("Select * from filters")->getAll();
			for ($i=0; $i < count($filters); $i++) { 
				echo "<div><h4>" . $filters[$i]["Caption"] . "</h4>";

				$filtervalues = SQL("Select * from filtervalues where filterId =?", array($filters[$i]['FilterId']))->getAll();
				for ($j=0; $j <  count($filtervalues); $j++) { 
					$checked = "";
					$bool = in_array($filtervalues[$j]['FilterValueId'], $filtervalueschecked);
					if ($bool)
						$checked = "checked = true";
					
					echo "<input id='".$filtervalues[$j]["FilterValueId"]."' type='checkbox' ".$checked."  onclick='NewsModule.changeFiltersList(".$filtervalues[$j]["FilterValueId"].")' >".$filtervalues[$j]['Caption'] . "</input>";
				}

				echo "</div>";
			}
			echo "<input id='filterButton' type='button' value='filter' onclick='NewsModule.filter()'/>";
		
		echo "</div>";
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
		if (strlen($sortField) == 0)
			$sortField = "title";
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

