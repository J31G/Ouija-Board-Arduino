// VARS
var word = "", x = "", y = "";

/* Connect to Web socket */
var Socket;
function connect() {
  Socket = new WebSocket('ws://172.16.0.23:81/');
}

/* Nav: Open */
function openNav() {
  document.getElementById("mobNav").style.height = "100%";
}

/* NAV: Close */
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
    // Socket.send( "!" + freeText );
    sendLetter (freeText);
  }
}
/* Send letter */
function sendLetter (word) {

  // Send whole word
  Socket.send( "*" + word );

  // Split word into letters
  var letters = word.split("");

  // For each letter, do the following:
  for ( i = 0; i < letters.length; i++ ) {

    // Make sure the letters are lower case
    var letter = letters[i].toLowerCase();

    // Set X & Y to how many steps they'll need
    switch ( letter ) {
      case "a" :
          x = 1;
          y = 1;
        break;
      case "b" :
          x = 1;
          y = 1;
        break;
      case "c" :
          x = 1;
          y = 1;
        break;
      case "d" :
          x = 1;
          y = 1;
        break;
      case "e" :
          x = 1;
          y = 1;
        break;
      case "f" :
          x = 1;
          y = 1;
        break;
      case "g" :
          x = 1;
          y = 1;
        break;
      case "h" :
          x = 1;
          y = 1;
        break;
      case "i" :
          x = 1;
          y = 1;
        break;
      case "j" :
          x = 1;
          y = 1;
        break;
      case "k" :
          x = 1;
          y = 1;
        break;
      case "l" :
          x = 1;
          y = 1;
        break;
      case "m" :
          x = 1;
          y = 1;
        break;
      case "n" :
          x = 1;
          y = 1;
        break;
      case "o" :
          x = 1;
          y = 1;
        break;
      case "p" :
          x = 1;
          y = 1;
        break;
      case "q" :
          x = 1;
          y = 1;
        break;
      case "r" :
          x = 1;
          y = 1;
        break;
      case "s" :
          x = 1;
          y = 1;
        break;
      case "t" :
          x = 1;
          y = 1;
        break;
      case "u" :
          x = 1;
          y = 1;
        break;
      case "v":
          x = 1;
          y = 1;
        break;
      case "w" :
          x = 1;
          y = 1;
        break;
      case "x" :
          x = 1;
          y = 1;
        break;
      case "y" :
          x = 1;
          y = 1;
        break;
      case "z" :
          x = 1;
          y = 1;
        break;
      case " " :
        x = 100;
        y = 100;
    }

    // Debug
    // console.log ( "Letter = " + letters[i] + "; X = " + x + "; Y = " + y);

    // Send to board
    Socket.send( "+" + "X" + x );
    Socket.send( "+" + "Y" + y );
  }

}

/* Motor On / Off */
var motorSet = "";
function setMotor (motorSet) {
  Socket.send( "/" + motorSet );
}

/* Motor CW / ACW */
var motorDir = "";
function setDir (motorDir) {
  Socket.send( "/" + motorDir );
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


