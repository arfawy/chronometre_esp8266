setInterval(function ( ) {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        document.getElementById("seconds").innerHTML = this.responseText;
      }
    };
    xhttp.open("GET", "/seconds", true);
    xhttp.send();
}, 1000 );