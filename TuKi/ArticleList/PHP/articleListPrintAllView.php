<?php

require '../ExternalResources/FreePDF_v1_7/fpdf.php';

$minSellerNumber = 100;
$maxSellerNumber = 199;

$minArticleNumber = 100;
$maxArticleNumber = 199;


$pdf = new FPDF();
// Column headings
$header = array('Nr.', 'Artikelbeschreibung', 'Gr.', 'Bemerkung', 'Preis');
$w = array(12, 73, 15, 73, 15);

$pdf->SetFont('Arial', '', 12);
$pdf->SetFillColor(255, 255, 255);
$pdf->SetTextColor(0);
$pdf->SetDrawColor(0, 0, 0);
$pdf->SetLineWidth(.3);


for ($sellerNumber = $minSellerNumber; $sellerNumber <= $maxSellerNumber; $sellerNumber++) {
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
    } else {
        continue;
    }

    $pdf->AddPage();

// Data
    $rowCount = 0;
    for ($i = $minArticleNumber; $i <= $maxArticleNumber; $i++) {
        if ($rowCount % 41 == 0 && $i < $maxArticleNumber) {
            // Header
            $pdf->SetFont('', 'B');
            //$pdf->Cell(200, 7, $header[$j], 1, 0, 'C', true);
            $pdf->Cell(200, 10, 'Verkaeufer Nummer: ' . $sellerNumber);
            $pdf->Ln();
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
}

$pdf->Output();

?>
