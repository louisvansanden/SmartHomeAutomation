<?php

	$topic = $_REQUEST["topic"];
	$message = $_REQUEST["message"];


	system('mosquitto_pub -t ' . $topic . ' -m ' . "'$message'");

?>
