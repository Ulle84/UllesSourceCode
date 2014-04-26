<!DOCTYPE html>
<meta charset="utf-8">
<html>
<head>
    <title>TuKi Artikelliste</title>

    <link rel="stylesheet" type="text/css" href="../CSS/global.css" media="all"/>
    <script language="JavaScript" src="../JavaScript/articleList.js"></script>
</head>
<body>

<table>
    <h1>Artikelliste für Verkäufer Nr. 100</h1>
    <tr>
        <th>Artikelnummer</th>
        <th>Artikelbeschreibung</th>
        <th>Größe</th>
        <th>Bemerkungen</th>
        <th>Preis</th>
    </tr>

    <?php

    $minArticleNumber = 100;
    $maxArticleNumber = 199;


    $fileName = "../Data/articleList.txt";
    $articleDescription = array();
    $size = array();
    $notes = array();
    $price = array();
    if (file_exists($fileName)) {

        $file = fopen($fileName, "r");

        for ($i = $minArticleNumber; $i <= $maxArticleNumber; $i++) {
            $articleDescription[$i] = rtrim(fgets($file));
            $size[$i] = rtrim(fgets($file));
            $notes[$i] = rtrim(fgets($file));
            $price[$i] = rtrim(fgets($file));
        }
        fclose($file);
    }
    else
    {
        for ($i = $minArticleNumber; $i <= $maxArticleNumber; $i++) {
            $articleDescription[$i] = "";
            $size[$i] = "";
            $notes[$i] = "";
            $price[$i] = "";
        }
    }


    for ($i = $minArticleNumber; $i <= $maxArticleNumber; $i++) {
        echo '<tr class="data">';

        echo '<td>' . $i . '</td>';
        echo '<td><input value="' . $articleDescription[$i] . '" type="text" size="30" maxlength="200" /></td>';
        echo '<td><input value="' . $size[$i] . '" type="text" size="4" maxlength="4" /></td>';
        echo '<td><input value="' . $notes[$i] . '" type="text" size="30" maxlength="200" /></td>';
        echo '<td><input value="' . $price[$i] . '" type="text" size="6" maxlength="6" /></td>';

        echo '</tr>';
    }

    echo '</table>';

    ?>

    <!--<div class="button" onclick="save()">Speichern</div>-->
    <br />
    <input type="button" value="Tabelle speichern" onclick="save()" /> <br />

    Antwort vom Server: <span id="httpResponse"></span>
</body>
</html>

