/* Open */
function openNav() {
  document.getElementById("mobNav").style.height = "100%";
}

/* Close */
function closeNav() {
  document.getElementById("mobNav").style.height = "0%";
}

/* Free Text */
form = document.getElementById("word");

function freeText(form) {
  
  var freeText = form.FreeText.value;
  
  if (!freeText) {
    alert ("Please enter something in the box");
  } else {
    document.getElementById("word").innerHTML = freeText;
    alert ("Word to send: " + freeText);
  }
}


