<!DOCTYPE html>
<meta charset="utf-8">
<html>
<head>
    <title>TuKi Artikelliste</title>

    <link rel="stylesheet" type="text/css" href="../CSS/global.css" media="all"/>
    <script language="JavaScript" src="../JavaScript/articleList.js"></script>
</head>
<body>

<?php

if (isset($_GET['id'])) {
    $id = $_GET['id'];
} else {
    echo "Keine ID angebeben!";
    exit;
}


$fileName = "../Data/uniqueIds.txt";
$sellerNumber = 0;
$data = array();
if (file_exists($fileName)) {
    $lines = file($fileName);

    foreach ($lines as $line) {
        $data = explode(' = ', trim($line));
        if ($data[0] == $id) {
            $sellerNumber = $data[1];
            break;
        }
    }


} else {
    echo "Keine Liste mit IDs gefunden!";
    exit;
}

if ($sellerNumber == 0) {
    echo "ID ist ungültig!";
    exit;
}

echo '<h1>Artikelliste für Verkäufer Nr. ' . $sellerNumber . '</h1>'

?>

<table>
    <tr>
        <th>Artikelnummer</th>
        <th>Preis</th>
        <th>Größe</th>
        <th>Artikelbeschreibung</th>
    </tr>

    <?php
    $minArticleNumber = 100;
    $maxArticleNumber = 199;


    $fileName = "../Data/articleList_" . $sellerNumber . ".txt";
    $articleDescription = array();
    $size = array();
    $price = array();
    if (file_exists($fileName)) {

        $file = fopen($fileName, "r");

        for ($i = $minArticleNumber; $i <= $maxArticleNumber; $i++) {
            $price[$i] = rtrim(fgets($file));
            $size[$i] = rtrim(fgets($file));
            $articleDescription[$i] = rtrim(fgets($file));

        }
        fclose($file);
    } else {
        for ($i = $minArticleNumber; $i <= $maxArticleNumber; $i++) {
            $price[$i] = "";
            $size[$i] = "";
            $articleDescription[$i] = "";
        }
    }


    for ($i = $minArticleNumber; $i <= $maxArticleNumber; $i++) {
        echo '<tr class="data">';

        echo '<td>' . $i . '</td>';
        echo '<td><input onblur="checkPrice(this); save(' . $sellerNumber . ')" onchange="checkPrice(this); save(' . $sellerNumber . ')" class="right" value="' . htmlspecialchars($price[$i]) . '" type="text" size="6" maxlength="6" /> €</td>';
        echo '<td><input onblur="checkContent(this); save(' . $sellerNumber . ')" onchange="checkContent(this); save(' . $sellerNumber . ')" value="' . htmlspecialchars($size[$i]) . '" type="text" size="4" maxlength="4" /></td>';
        echo '<td><input onblur="checkContent(this); save(' . $sellerNumber . ')" onchange="checkContent(this); save(' . $sellerNumber . ')" value="' . htmlspecialchars($articleDescription[$i]) . '" type="text" size="60" maxlength="50" /></td>';

        echo '</tr>';
    }

    echo '</table>';


    echo '<br/>';
    //echo '<input type="button" value="Tabelle auf Server speichern" onclick="save(' . $sellerNumber . ')"/>';

    echo '<input type="button" value="Tabelle als PDF anzeigen" onclick="print(\'' . $id . '\')"/> <br/>';

    ?>


    <!--Antwort vom Server: <span id="httpResponse"></span>-->
</body>
</html>

