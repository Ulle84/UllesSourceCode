var sellerNumber = 0;

function init (sellerNumberValue) {
    sellerNumber = sellerNumberValue;
}

function save(checkInput, confirmation) {

    var inputChecked = true;
    if (checkInput) {
        inputChecked = checkAllInputs();
    }

    var content = "Article List\nVersion 1.0\n" + sellerNumber + "\n";

    content += window.document.getElementById("firstname").value + "\n";
    content += window.document.getElementById("lastname").value + "\n";
    content += window.document.getElementById("phone").value + "\n";

    var data = window.document.getElementsByClassName("data");

    for (var i = 0; i < data.length; i++) {
        var dataContent = data[i].getElementsByTagName("td");

        content += dataContent[0].textContent + "\n";

        for (var j = 1; j < dataContent.length; j++) {
            content += dataContent[j].firstChild.value;
            content += "\n";
        }
    }

    var xmlhttp = new XMLHttpRequest();

    if (confirmation && inputChecked) {
        var saveButton = window.document.getElementById("saveButton");
        saveButton.disabled = true;
        xmlhttp.onreadystatechange = function () {
            if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
                alert(xmlhttp.responseText);
                saveButton.disabled = false;
            }
        }
    }

    xmlhttp.open("POST", "../PHP/articleListSaver.php", true);
    xmlhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
    xmlhttp.send("sellerNumber=" + sellerNumber + "&content=" + content);
}

function showPdf(id) {
    if (checkAllInputs()) {
        window.open("../PHP/articleListView.php?seller=" + sellerNumber + "&id=" + id + "&mode=print");
    }
}

function checkAllInputs() {
    if (window.document.getElementById("firstname").value == "") {
        alert("Bitte Vornamen eingeben!");
        return false;
    }

    if (window.document.getElementById("lastname").value == "") {
        alert("Bitte Nachnamen eingeben!");
        return false;
    }

    if (window.document.getElementById("phone").value  == "") {
        alert("Bitte Telefonnummer eingeben!");
        return false;
    }

    var data = window.document.getElementsByClassName("data");

    var missingPrices = 0;
    for (var i = 0; i < data.length; i++) {
        var dataContent = data[i].getElementsByTagName("td");

        if (dataContent[1].firstChild.value == "")
        {
            if (dataContent[3].firstChild.value != "")
            {
                missingPrices++;
            }
        }
    }

    if (missingPrices > 0) {
        if (missingPrices == 1) {
            alert("Bei einem Artikel ist eine Artikelbeschreibung, aber kein Preis angegeben.\nBitte tragen Sie einen Preis ein!");
            return false;
        }
        else {
            alert("Bei " + missingPrices + " Artikeln sind Artikelbeschreibungen, aber keine Preise angegeben.\nBitte tragen Sie die Preise ein!");
            return false;
        }
    }

    return true;
}

function checkContent(element) {
    if (element.value.contains("&")) {
        element.value = element.value.replace(new RegExp("&", 'g'), "");
        alert("Das Zeichen '&' ist ein unerlaubtes Sonderzeichen und wurde entfernt!");
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
            element.value = ""; // set, so onblur-function does return immediately
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
            alert("Die eingegebene Größe ist falsch und wurde gelöscht");
            return;
        }

        element.value = number;
    }

}
