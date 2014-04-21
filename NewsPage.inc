<?php
	class NewsPage
	{
		private $body;
		private $title;
		public function __construct($obj)
		{
			$this->body = $obj["body"];
			$this->title = $obj["title"];
		}
		public function getBody()
		{
			return $this->body;
		}
		public function getTitle()
		{
			return $this->title;
		}
	}	


?>