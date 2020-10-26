document.addEventListener("readystatechange", (event) => {
  if (event.target.readyState === "complete") {
    showDevices();
  }
});

function toggle(id) {
  var xmlhttp = new XMLHttpRequest();
  xmlhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      console.log(this.response);
      if (this.response == "off") {
        document.getElementById(id).className = "btn-device btn-off";
        document.getElementById(id + "logo").src = "../media/flash_off.png";
      } else if (this.response == "on") {
        document.getElementById(id).className = "btn-device btn-on";
        document.getElementById(id + "logo").src = "../media/flash_on.png";
      }
    }
  };
  xmlhttp.open("GET", "/database/toggleState.php?id=" + id, true);
  xmlhttp.send();
}

function spotify(command, meta) {
  var xmlhttp = new XMLHttpRequest();
  xmlhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      console.log(this.response);
    }
  };
  xmlhttp.open("GET", "spotify.php?command=" + command + "&meta=" + meta, true);
  xmlhttp.send();
}

function showDevices() {
  var xmlhttp = new XMLHttpRequest();
  xmlhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("btn-holder").innerHTML = this.response;
    }
  };
  xmlhttp.open("GET", "/database/getAllDevices.php", true);
  xmlhttp.send();
}

function renameDevice() {
  $id = document.getElementById("deviceID").value;
  $name = document.getElementById("newName").value;

  var xmlhttp = new XMLHttpRequest();
  xmlhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      // if (this.response == "") {
      //   document.getElementById("err_change_name").innerHTML =
      //     "Name of <b>" +
      //     $id +
      //     "</b> changed to <b>" +
      //     $name +
      //     "</b> succesfully!";
      // } else {
      //   document.getElementById("err_change_name").innerHTML = this.response;
      // }
    }
  };
  xmlhttp.open(
    "GET",
    "/database/renameDevice.php?id=" + $id + "&name=" + $name,
    true
  );
  xmlhttp.send();
}

function setTimer(id) {
  if (
    document.getElementById("time" + id).value != "" &&
    document.getElementById("time" + id).value != "0000"
  ) {
    var xmlhttp = new XMLHttpRequest();
    xmlhttp.onreadystatechange = function () {
      if (this.readyState == 4 && this.status == 200) {
        document.getElementById(id).className = "btn-device btn-timer";
        document.getElementById(id + "logo").src = "../media/flash_on.png";
        console.log("Timer activated!");
      }
    };
    xmlhttp.open(
      "GET",
      "/database/toggleState.php?id=" +
        id +
        "&timer=1&xxxx=" +
        document.getElementById("time" + id).value,
      true
    );
    xmlhttp.send();
  }
}
