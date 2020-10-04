<?php

	require_once("config.php");

    $id = $_REQUEST["id"];
    $io = $_REQUEST["io"];
    $timer = $_REQUEST["timer"];
    $xxxx = $_REQUEST["xxxx"];
    $xooo = $_REQUEST["xooo"];
    $oxoo = $_REQUEST["oxoo"];
    $ooxo = $_REQUEST["ooxo"];
    $ooox = $_REQUEST["ooox"];

	$sql = "SELECT * FROM devices where id='" . $id . "'";
    $result = $conn->query($sql);

    if ($result->num_rows > 0) {
    while($row = $result->fetch_assoc()) {

        

        if ($row["state"] == "0") {
            $toggledState = "1";
            $response = "on";
        } elseif ($row["state"] == "1") {
            $toggledState = "0";
            $response = "off";
        }

        if ($timer == "1") {
            $toggledState = "1";
            $response = "on";
            if ($xxxx == "") {
                $mqtt_message = $row["prefix"] . "T" . $xooo . $oxoo . $ooxo . $ooox;
            } else {
                $mqtt_message = $row["prefix"] . "T" . $xxxx;
            }
            
        } else {
            if ($io == "1") {
                $toggledState = "1";
                $response = "on";
            } elseif ($io == "0") {
                $toggledState = "0";
                $response = "off";
            }
            $mqtt_message = $row["prefix"] . $toggledState;
        }

        $mqtt_topic = $row["topic"];
        system('mosquitto_pub -t ' . $mqtt_topic . ' -m ' . "'$mqtt_message'");

        $sql = "UPDATE devices SET state='" . $toggledState ."' WHERE id='" . $id . "'";

        if ($conn->query($sql) === TRUE) {
        echo $response;

        } else {
        echo "Error updating record: " . $conn->error;
        }

    }
    } else {
    echo "ID not found";
    }
    $conn->close(); 

    


?>