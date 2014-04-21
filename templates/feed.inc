<html>
<head>
	<link rel="stylesheet" type="text/css" href="css\feed.css"/>
</head>
<body>

	<div id="header"><img src="Pictures\header.jpg"/></div>

	<div id="feed">
	<?php
	foreach($obj as $value)
	{
	echo"	<div class=\"news_container\">
			<div class=\"news\"><p>".$value["title"]."</p></div>
			<a href=\"getNews.php?id=".$value["id"]."\">More</a>
		</div>";
	};
	?>
	</div>
	<div id="footer">
		Made by Igor Maydanovskiy
	</div>
</body>
</html>