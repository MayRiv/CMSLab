<?php
echo '<div id="content" class="Box" >';
	echo '<h1>'.$obj['title'].'</h1>';
	if (isset($obj))
	{
		for ($i=0; $i < count($obj) - 1; $i++) { 
			echo '<div class="news"><a href="?pageId='. $obj[$i]['id'] .'">'.$obj[$i]['title'].'</a></div>';
			
		}
	}
echo '</div>';
?>