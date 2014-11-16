<div id="footer" class="Box">
	<?php 
		echo '<div> You visited: <br/>';
		if(isset($obj))
		{
				foreach ($obj as $key => $value) {
					echo '<a href="/CMSLab/index.php?pageId='.$key.'">'.$value.'</a><br/>';
				}
		}
	?>
		<p>Made by Igor Maydanovskiy in 2014</p>
</div>