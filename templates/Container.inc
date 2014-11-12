<?php
echo '<div id="contentainer" class="lifted">';

	for ($i=0; $i < count($obj); $i++) { 
		echo '<div class="news"><a href="?pageId='. $obj[$i]['id'] .'">'.$obj[$i]['title'].'</a></div>';
		
	}
	
echo '</div>';
?>