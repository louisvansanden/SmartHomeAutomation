<?php

	require_once("config.php");

	$id = $_REQUEST["id"];

	
	$sql = "SELECT name FROM devices where id='" . $id . "'";
    $result = $conn->query($sql);

    if ($result->num_rows > 0) {
    while($row = $result->fetch_assoc()) {
        echo $row["name"];
    }
    } else {
    echo "0 results";
    }
    $conn->close(); 


?>