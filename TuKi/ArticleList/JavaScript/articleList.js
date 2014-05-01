function save(sellerNumber) {
    var httpResponse = document.getElementById("httpResponse");
    httpResponse.textContent = "";

    document.getElementById("httpResponse").innerHTML = "";

    var content = "";

    var data = window.document.getElementsByClassName("data");

    for (var i = 0; i < data.length; i++) {
        var dataContent = data[i].getElementsByTagName("td");

        for (var j = 1; j < dataContent.length; j++) {
            content += dataContent[j].firstChild.value;
            content += "\n";
        }
    }

    var xmlhttp = new XMLHttpRequest();

    xmlhttp.onreadystatechange = function () {
        if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
            httpResponse.textContent = xmlhttp.responseText;
        }
    }

    xmlhttp.open("POST", "../PHP/articleListSaver.php", true);
    xmlhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
    xmlhttp.send("sellerNumber=" + sellerNumber + "&content=" + content);
}

function print(id) {
    if (confirm("Haben Sie die Artikelliste gespeichert?")) {
        //window.location.href = "../PHP/printArticleList.php";
        window.open("../PHP/printArticleList.php?id=" + id);
    }
}

function checkContent(element) {
    // string.replace(new RegExp("\"", 'g'), "&quot;");
    if (element.value.contains("&")) {
        alert("Das Zeichen '&' ist ein unerlaubtes Sonderzeichen und wurde entfernt!");
        element.value = element.value.replace(new RegExp("&", 'g'), "");
    }
}

function checkPrice(element) {
    if (element.value == "") {
        return;
    }

    var number = parseFloat(element.value.replace(",", "."));
    if (isNaN(number)) {
        element.value = ""; // first delete, otherwise the following message is doubled (due to the onblur-event, which occurs because of the alert)
        alert("Der eingegebene Preis ist ungültig und wurde gelöscht!")
    }
    else {
        if (number < 0) {
            element.value = "";
            alert("Negative Preise sind unsinnig!\nDer eingegebene Preis wurde gelöscht");
            return;
        }

        if (number > 999.99) {
            element.value = ""; // set, so onblur-function does return immediatly
            alert("Preise größer als 999,99 € sind nicht erlaubt!\nDer eingegebene Preis wurde auf das Maximum erniedrigt");
            number = 999.99;
        }

        element.value = number.toFixed(2);
        element.value = element.value.replace(".", ",");
    }

}

function checkSize(element) {
    if (element.value == "") {
        return;
    }

    var number = parseInt(element.value);
    if (isNaN(number)) {
        element.value = ""; // first delete, otherwise the following message is doubled (due to the onblur-event, which occurs because of the alert)
        alert("Die eingegebene Größe ist ungültig und wurde gelöscht!")
    }
    else {
        if (number < 50) {
            element.value = "";
            alert("Die eingegebene Größe ist zu klein und wurde gelöscht");
            return;
        }

        if (number > 188) {
            element.value = "";
            alert("Die eingegebene Größe ist zu groß und wurde gelöscht");
            return;
        }

        if ((number - 50) % 6 != 0) {
            element.value = "";
            alert("Die eingegebene Größe ist zu falsch und wurde gelöscht");
            return;
        }

        element.value = number;
    }

}
