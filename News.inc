<?php
	class News
	{
		public $body;
		public $title;
		function __construct($Title, $Body ){
			$this->body = $Body;
			$this->title = $Title;
		}
	}

?>