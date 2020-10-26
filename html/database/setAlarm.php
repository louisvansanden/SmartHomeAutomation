<?php

	require_once("config.php");

    $id = $_REQUEST["id"];
    $io = $_REQUEST["io"];
    $xooo = $_REQUEST["xooo"];
    $oxoo = $_REQUEST["oxoo"];
    $ooxo = $_REQUEST["ooxo"];
    $ooox = $_REQUEST["ooox"];

    $mqtt_topic = $id;

    if ($io == "0") {
        system('mosquitto_pub -t ' . $mqtt_topic . ' -m \"T0----\"');
    }

    elseif ($io == "1") {
        
        $mqtt_message = "T1" . $xooo . $oxoo . $ooxo . $ooox;
        system('mosquitto_pub -t ' . $mqtt_topic . ' -m ' . "$mqtt_message");

    }
    
    

?>