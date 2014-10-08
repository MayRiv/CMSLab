<?php
echo '<div id="contentainer">';

	for ($i=0; $i < count($obj); $i++) { 
		echo '<div class="news"><a href="?pageId='. $obj[$i]['id'] .'">'.$obj[$i]['title'].'</a>';
		//echo '<p>'.$obj[$]['Author'].'</p></div>'
	}
	
echo '</div>';
?>