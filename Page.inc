<?php 
class Page
{
	public $id;
	public $body;
	public $title;
	public $instanceOf;
	public $sortField;
	public $parentId;
	public $isContainer;
	public $author;
	public function __construct($id)
	{
		$page = SQL('Select * from news where id = ?', array($id))->getAll()[0];
		$this->id = $id;
		$this->body =$page['Body'];
		$this->title = $page['Title'];
		$this->instanceOf = $page['InstanceOf'];
		$this->parentId = $page['ParentId'];
		$this->sortField = $page['sortField'];
		$this->isContainer = $page['IsContainer'];
	}
	public function publish()
	{

		if (!$this->isContainer)
		{
			$content = array('title' =>$this->title,'body'=>$this->body );
			getView("Content.inc",$content);
		}
		else
		{
			$children = $this->getChildren();
			$content = array();
			for ($i=0; $i < count($children); $i++) { 
				array_push($content, array('title' => $children[$i]->title, 'id' => $children[$i]->id));
			}
			$this->publishFilterMenu();
			getView("Container.inc",$content);
		}
	}
	public function getChildren()
	{
		
		$query = "Select * from(select * from news where parentId =  ?) as m0";

		$params = array();
		
		array_push($params, $this->id);
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
			$query = $query . " group by id";
			$children = SQL($query,$params)->getAll();
			$pages = array();
			for ($i=0; $i < count($children); $i++) { 
				array_push($pages, new Page($children[$i]["Id"]));
			}
			return $pages;
			return $children;
	}

	public function publishFilterMenu()
	{
		echo "<div id='filter'>";
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
		echo "<input id='filterButton' type='button' value='filter' onclick='NewsModule.filter()'/></div>";
	}
}

?>