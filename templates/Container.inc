<?php
echo '<div id="contentainer">';

	for ($i=0; $i < count($obj); $i++) { 
		echo '<div><a href="?pageId='. $obj[$i]['id'] .'">'.$obj[$i]['title'].'</a></div>';
	}
	
echo '</div>';
?>