/* Connect to Web socket */
var Socket;
function connect() {
  Socket = new WebSocket('ws://172.16.0.23:81/');
}

/* Open */
function openNav() {
  document.getElementById("mobNav").style.height = "100%";
}

/* Close */
function closeNav() {
  document.getElementById("mobNav").style.height = "0%";
}

/* Free Text */
function freeText() {
  
  var freeText = document.getElementById("freeTextValue").value;
  
  if (!freeText) {
    alert ("Please enter something in the box");
  } else {
    document.getElementById("word").innerHTML = freeText;
    Socket.send( "!" + freeText );
  }
}
/* Predefined Words */
var word = "";
function predefined (word) {
  // alert ("The word is: " + word);
  Socket.send( "*" + word );
}

/* LED Slider */
function setDelay () {
  var delay = document.getElementById("myDelay").value;
  Socket.send( "#" + delay );
}
function displayDelay() {
  var delay = document.getElementById("myDelay").value;
  document.getElementById("delay").innerHTML = delay;
}


