<?php

        $command = $_REQUEST["command"];
        $meta = $_REQUEST["meta"];


        system('python Spotify/' . "'$command'" . '.py', $retval);

	echo "";

?>

