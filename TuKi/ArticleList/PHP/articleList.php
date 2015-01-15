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
    private $id;

    function __construct($sellerNumber, $id)
    {
        $this->sellerNumber = $sellerNumber;
        $this->id = $id;

        //TODO check ID

        $this->readFromFile();
    }

    public function writeHtml() {
        echo '<body onload="init(' . $this->sellerNumber . ')">';
        echo '<h1>Artikelliste für Verkäufer Nr. ' . $this->sellerNumber . '</h1>';

        echo '<table>';
        echo '<tr>';
        echo '<td>Vorname</td>';
        echo '<td><input id="firstname" onblur="save()" onchange="save()" value="' . htmlspecialchars($this->firstName) . '" type="text" size="30"/></td>';
        echo '</tr>';

        echo '<tr>';
        echo '<td>Nachname</td>';
        echo '<td><input id="lastname" onblur="save()" onchange="save()" value="' . htmlspecialchars($this->lastName) . '" type="text" size="30"/></td>';
        echo '</tr>';

        echo '<tr>';
        echo '<td>Telefonnummer (für Rückfragen)</td>';
        echo '<td><input id="phone" onblur="save()" onchange="save()" value="' . htmlspecialchars($this->phone) . '" type="text" size="30"/></td>';
        echo '</tr>';
        echo '</table>';
        echo '<br />';

        echo '<table>';
        echo '<tr>';
        echo '<th>Artikelnummer</th>';
        echo '<th>Preis</th>';
        echo '<th>Größe</th>';
        echo '<th>Artikelbeschreibung</th>';
        echo '</tr>';

        for ($i = $this->minArticleNumber; $i <= $this->maxArticleNumber; $i++) {
            echo '<tr class="data">';

            echo '<td>' . $i . '</td>';
            echo '<td><input onblur="checkPrice(this); save()" onchange="checkPrice(this); save()" class="right" value="' . htmlspecialchars($this->price[$i]) . '" type="text" size="6" maxlength="6" /> €</td>';
            echo '<td><input onblur="checkContent(this); save()" onchange="checkContent(this); save()" value="' . htmlspecialchars($this->size[$i]) . '" type="text" size="4" maxlength="4" /></td>';
            echo '<td><input onblur="checkContent(this); save()" onchange="checkContent(this); save()" value="' . htmlspecialchars($this->articleDescription[$i]) . '" type="text" size="60" maxlength="50" /></td>';

            echo '</tr>';
        }

        echo '</table>';
        echo '<br />';

        echo '<input type="button" value="Tabelle Speichern" onclick="save(true, true)"/>';
        echo '<input type="button" value="Tabelle als PDF anzeigen" onclick="print(\'' . $this->id . '\')"/> <br/>';

        echo '</body>';
    }

    private function readFromFile() {
        $this->fileName = "../Data/articleList_" . $this->sellerNumber . ".txt";

        if (file_exists($this->fileName)) {
            $file = fopen($this->fileName, "r");

            $this->fileDescription = rtrim(fgets($file));
            $this->versionNumber = rtrim(fgets($file));
            $this->sellerNumberFile = rtrim(fgets($file));
            $this->firstName = rtrim(fgets($file));
            $this->lastName = rtrim(fgets($file));
            $this->phone = rtrim(fgets($file));

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
                $this->articleNumber[$i] = rtrim(fgets($file));
                $this->price[$i] = rtrim(fgets($file));
                $this->size[$i] = rtrim(fgets($file));
                $this->articleDescription[$i] = rtrim(fgets($file));
            }
            fclose($file);
        } else {
            for ($i = $minArticleNumber; $i <= $maxArticleNumber; $i++) {
                $this->price[$i] = "";
                $this->size[$i] = "";
                $this->articleDescription[$i] = "";
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

echo '<body onload="init()">';
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


?>

</html>

