<?php

require '../ExternalResources/FreePDF_v1_7/fpdf.php';

$minArticleNumber = 100;
$maxArticleNumber = 199;


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
}

$pdf = new FPDF();
// Column headings
$header = array('Nr.', 'Preis', 'Gr.', 'Artikelbeschreibung');
$w = array(12, 15, 15, 146);

$pdf->SetFont('Arial', '', 12);
$pdf->AddPage();

$pdf->SetFillColor(255, 255, 255);
$pdf->SetTextColor(0);
$pdf->SetDrawColor(0, 0, 0);
$pdf->SetLineWidth(.3);
// Data
$rowCount = 0;
for ($i = $minArticleNumber; $i <= $maxArticleNumber; $i++) {
    if ($rowCount % 41 == 0 && $i < $maxArticleNumber) {
        // Header
        $pdf->Cell(200, 10, utf8_decode('Verkäufer Nummer: ') . $sellerNumber . ' - ' . $firstName . ' ' . $lastName . ' - ' . $phone);
        $pdf->Ln();
        $pdf->SetFont('', 'B');
        for ($j = 0; $j < count($header); $j++) {
            $pdf->Cell($w[$j], 7, utf8_decode($header[$j]), 1, 0, 'C', true);
        }
        $pdf->SetFont('');
        $pdf->Ln();
    }
    $pdf->Cell($w[0], 6, utf8_decode($i), 1, 0, 'L', false);
    $pdf->Cell($w[1], 6, utf8_decode($price[$i]), 1, 0, 'R', false);
    $pdf->Cell($w[2], 6, utf8_decode($size[$i]), 1, 0, 'L', false);
    $pdf->Cell($w[3], 6, utf8_decode($articleDescription[$i]), 1, 0, 'L', false);

    $pdf->Ln();
    $rowCount++;
}

$pdf->Output();

?>
