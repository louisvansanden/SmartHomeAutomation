<?php

	require_once("config.php");

	$main_array = [];

	$sql = "SELECT * FROM devices";
    	$result = $conn->query($sql);

    	if ($result->num_rows > 0) {
    	while($row = $result->fetch_assoc()) {

		$info = [
			
			"id" => $row['id'],
			"type" => $row['type'],
			"state" => $row['state'],
			"topic" => $row['topic'],
			"prefix" => $row['prefix'],
			"name" => $row['name'],

		];        				

		array_push($main_array, $info);
        
    	}

	$mObj->devices = $main_array;

	echo json_encode($mObj);

    	} else {

    	echo "";

    	}
    	$conn->close(); 


?>