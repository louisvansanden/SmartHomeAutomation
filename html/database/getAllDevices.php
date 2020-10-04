<?php

	require_once("config.php");

	$sql = "SELECT * FROM devices";
    $result = $conn->query($sql);

    if ($result->num_rows > 0) {
    while($row = $result->fetch_assoc()) {

        if ($row["name"] == "") {
            $name = "<b>" . $row["id"] . "</b>";
        } else {
            $name = "<b>" . $row["name"] . "</b>";
        }

        $html = "<div class=\"time-holder\"><input class=\"time-input\" placeholder=\"hh:mm\" type=\"number\" id=\"time";
        $html .= $row["id"];
        $html .= "\"><button class=\"time-button\"onclick=\"setTimer('";
        $html .= $row["id"];
        $html .= "')\">Set timer</button></div>";


        if ($row["state"] == "0") {
            $html .= "<button class=\"btn-device btn-off\" id=\"";
        } else if ($row["state"] == "1") {
            $html .= "<button class=\"btn-device btn-on\" id=\"";
        }

        $html .= $row["id"];
        $html .= "\" onclick=\"toggle(this.id)\">";
        $html .= $name;
        $html .= " <i style=\"font-size: 10px; \">(" . $row["id"] . ")</i>";
        $html .= "</button>";

        if ($row["state"] == "0") {
            $html .= "<img id=\"" . $row[id] . "logo\" class=\"logo\" src=\"../media/flash_off.png\" />";
        } else if ($row["state"] == "1") {
            $html .= "<img id=\"" . $row[id] . "logo\" class=\"logo\" src=\"../media/flash_on.png\" />";
        }

        $html .= "";

        echo $html;
    }
    } else {
    echo "0 results";
    }
    $conn->close(); 


?>