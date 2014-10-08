<div id="content">
<h1><?=$obj["title"]?></h1>
<p><?=$obj["body"]?></p>
<table>
	<?php
		for ($i=0; $i < count($obj['table']); $i++) { 
			echo '<tr>';
			echo '<td>'.$obj['table'][$i]['Caption'].'</td>';
			echo '<td>'.$obj['table'][$i]['Value'].'</td>';
			echo '</tr>';
		}
	?>
</table>
</div>