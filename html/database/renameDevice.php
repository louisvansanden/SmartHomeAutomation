<?php

    require_once("config.php");

    $id = $_REQUEST["id"];
    $name = $_REQUEST["name"];

    $sql = "SELECT name FROM devices where id='" . $id . "'";
    $result = $conn->query($sql);

    if ($result->num_rows > 0) {
    while($row = $result->fetch_assoc()) {
    
        $sql = "UPDATE devices SET name='" . $name ."' WHERE id='" . $id . "'";

        if ($conn->query($sql) === TRUE) {
            echo "";
        } else {
            echo "Error updating record: " . $conn->error;
        }

    }
    } else {
    echo "ID not found";
    }

	

    $conn->close(); 

?>