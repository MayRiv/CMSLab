<html>
<head>
	<link rel="stylesheet" type="text/css" href="feed.css"/>
</head>
<body>

	<div id="header">hello</div>
	<div id="feed">
	<?php
	echo "<h1>".$obj->getTitle()."</h1>
			<p>".$obj->getBody()."</p>";
	?>
	</div>
	<div id="footer">
		Good bye
	</div>
</body>
</html>