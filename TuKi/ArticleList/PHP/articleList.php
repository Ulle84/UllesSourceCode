<?php

class ArticleList {
    private $sellerNumber;
    private $data = array(); // needed?
    private $fileName;
    private $articleDescription = array();
    private $size = array();
    private $price = array();
    private $articleNumber = array();
    private $fileDescription;
    private $versionNumber;
    private $sellerNumberFile;
    private $firstName;
    private $lastName;
    private $phone;

    function __construct($sellerNumber)
    {
        $this->sellerNumber = $sellerNumber;
        $this->readFromFile();
    }

    public function writeSellerInformation() {
        echo '<table>';
        echo '<tr>';
        echo '<td>Vorname</td>';
        echo '<td><input id="firstname" onblur="save(' . $this->sellerNumber . ')" onchange="save(' . $this->sellerNumber . ')" value="' . htmlspecialchars($this->firstName) . '" type="text" size="30"/></td>';
        echo '</tr>';

        echo '<tr>';
        echo '<td>Nachname</td>';
        echo '<td><input id="lastname" onblur="save(' . $this->sellerNumber . ')" onchange="save(' . $this->sellerNumber . ')" value="' . htmlspecialchars($this->lastName) . '" type="text" size="30"/></td>';
        echo '</tr>';

        echo '<tr>';
        echo '<td>Telefonnummer (für Rückfragen)</td>';
        echo '<td><input id="phone" onblur="save(' . $this->sellerNumber . ')" onchange="save(' . $this->sellerNumber . ')" value="' . htmlspecialchars($this->phone) . '" type="text" size="30"/></td>';
        echo '</tr>';
        echo '</table>';
        echo '<br />';
    }

    private function readFromFile() {
        $this->fileName = "../Data/articleList_" . $this->sellerNumber . ".txt";

        if (file_exists($this->fileName)) {
            $file = fopen($this->fileName, "r");

            $fileDescription = rtrim(fgets($file));
            $versionNumber = rtrim(fgets($file));
            $sellerNumberFile = rtrim(fgets($file));
            $firstName = rtrim(fgets($file));
            $lastName = rtrim(fgets($file));
            $phone = rtrim(fgets($file));

            /* ToDo modify this code!
            while (!feof($file)) {
                $name = rtrim(fgets($file));
                $dates = rtrim(fgets($file));
                $notes = rtrim(fgets($file));

                if ($name != "") {
                    $this->assistanceInput[$name] = explode(";", $dates);
                    $this->assistanceNotes[$name] = $notes;
                    $this->dataExist = true;
                }
            }
            */

            //TODO do not read from min to max, read the whole file and determine the articleNumber by file content
            for ($i = $minArticleNumber; $i <= $maxArticleNumber; $i++) {
                $articleNumber[$i] = rtrim(fgets($file));
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
    }
}

?>


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
    echo "<body>";
    echo "Keine Liste mit IDs gefunden!";
    echo "</body>";
    echo "</html>";
    exit;
}

if ($sellerNumber == 0) {
    echo "<body>";
    echo "ID ist ungültig!";
    echo "</body>";
    echo "</html>";
    exit;
}

echo '<body onload="init(' . $sellerNumber . ')">';
echo '<h1>Artikelliste für Verkäufer Nr. ' . $sellerNumber . '</h1>';

$minArticleNumber = 100;
$maxArticleNumber = 199;


$fileName = "../Data/articleList_" . $sellerNumber . ".txt";
$articleDescription = array();
$size = array();
$price = array();
$articleNumber = array();
if (file_exists($fileName)) {
    $file = fopen($fileName, "r");

    $fileDescription = rtrim(fgets($file));
    $versionNumber = rtrim(fgets($file));
    $sellerNumberFile = rtrim(fgets($file));
    $firstName = rtrim(fgets($file));
    $lastName = rtrim(fgets($file));
    $phone = rtrim(fgets($file));

    //TODO do not read from min to max, read the whole file and determine the articleNumber by file content
    for ($i = $minArticleNumber; $i <= $maxArticleNumber; $i++) {
        $articleNumber[$i] = rtrim(fgets($file));
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





echo '<table>';
echo '<tr>';
echo '<th>Artikelnummer</th>';
echo '<th>Preis</th>';
echo '<th>Größe</th>';
echo '<th>Artikelbeschreibung</th>';
echo '</tr>';

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
echo '<input type="button" value="Tabelle Speichern" onclick="save(' . $sellerNumber . ', true, true)"/>';
echo '<input type="button" value="Tabelle als PDF anzeigen" onclick="print(\'' . $id . '\')"/> <br/>';

echo '</body>';

?>

</html>

