<div id="content" class='Box'>
<h1><?=$obj["title"]?></h1><?php echo '<a href="/CMSLab/?pageId='.$obj['id'].'&fav=add">Add to Favourites</a>';?>
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