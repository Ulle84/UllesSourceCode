function save() {
    var httpResponse = document.getElementById("httpResponse");
    httpResponse.textContent = "";

    document.getElementById("httpResponse").innerHTML = "";

    var content = "";

    var data = window.document.getElementsByClassName("data");

    for (var i = 0; i < data.length; i++) {
        var dataContent = data[i].getElementsByTagName("td");
        content += dataContent[1].firstChild.value;
        content += "\n";
        content += dataContent[2].firstChild.value;
        content += "\n";
        content += dataContent[3].firstChild.value;
        content += "\n";
        content += dataContent[4].firstChild.value;
        content += "\n";
    }

    var xmlhttp = new XMLHttpRequest();

    xmlhttp.onreadystatechange = function () {
        if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
            httpResponse.textContent = xmlhttp.responseText;
        }
    }

    xmlhttp.open("POST", "../PHP/articleListSaver.php", true);
    xmlhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
    xmlhttp.send("content=" + content);
}