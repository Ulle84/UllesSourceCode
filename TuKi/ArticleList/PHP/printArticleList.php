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

$pdf = new FPDF();
// Column headings
$header = array('Nr.', 'Artikelbeschreibung', 'Gr.', 'Bemerkung', 'Preis');
$w = array(12, 73, 15, 73, 15);

$pdf->SetFont('Arial', '', 12);
$pdf->AddPage();

$pdf->SetFillColor(255, 255, 255);
$pdf->SetTextColor(0);
$pdf->SetDrawColor(0, 0, 0);
$pdf->SetLineWidth(.3);
// Data
$rowCount = 0;
for ($i = $minArticleNumber; $i <= $maxArticleNumber; $i++) {
    if ($rowCount % 43 == 0 && $i < $maxArticleNumber) {
        // Header
        $pdf->SetFont('', 'B');
        for ($j = 0; $j < count($header); $j++) {
            $pdf->Cell($w[$j], 7, $header[$j], 1, 0, 'C', true);
        }
        $pdf->SetFont('');
        $pdf->Ln();
    }
    $pdf->Cell($w[0], 6, $i, 1, 0, 'L', false);
    $pdf->Cell($w[1], 6, $articleDescription[$i], 1, 0, 'L', false);
    $pdf->Cell($w[2], 6, $size[$i], 1, 0, 'L', false);
    $pdf->Cell($w[3], 6, $notes[$i], 1, 0, 'L', false);
    $pdf->Cell($w[4], 6, $price[$i], 1, 0, 'R', false);
    $pdf->Ln();
    $rowCount++;
}

$pdf->Output();

?>
