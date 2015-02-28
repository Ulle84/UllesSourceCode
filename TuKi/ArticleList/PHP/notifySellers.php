<?php

require_once '../ExternalResources/PHPMailer/PHPMailerAutoload.php';
require_once 'UniqueIdList.php';

$hostname = $_SERVER['HTTP_HOST'];
$path = dirname($_SERVER['PHP_SELF']);

$fileName = "../Data/mailAddresses.txt";

$mailAddresses = array();

if (file_exists($fileName)) {
    $file = fopen($fileName, "r");

    while (!feof($file)) {
        $line = rtrim(fgets($file));
        $exploded = explode(' ', $line);
        $mailAddresses[$exploded[0]] = $exploded[1];
    }

    fclose($file);
}

$uniqueIdList = new UniqueIdList();
$uniqueIdList->readFromFile("../Data/uniqueIds.txt");

foreach ($mailAddresses as $sellerNumber => $mailAddress) {
    $id = $uniqueIdList->getId($sellerNumber);
    $url = 'http://tv-hechtsheim.de/tv_tuki/PHP/articleListView.php?seller=' . $sellerNumber . '&id=' . $id . '&mode=edit';
    $link = '<a href="' . $url . '">Liste für Verkäufer ' . $sellerNumber . '</a>';

    $body = 'Liebe(r) Verkäufer(in),<br /><br />';
    $body .= 'unter dem nachfolgenden Link steht ab sofort Ihre persönliche Online-Artikelliste bereit. <br/>';
    $body .= $link;
    $body .= '<br/><br/>Bitte tragen Sie dort alle Ihre zu verkaufenden Artikel mit Preisen bis zum 05.03.2015  ein.<br /><br />';
    $body .= 'Ihr TuKi-Team';

    $altBody = 'Liebe(r) Verkäufer(in),\n\n';
    $altBody .= 'unter dem nachfolgenden Link steht ab sofort Ihre persönliche Online-Artikelliste bereit.\n';
    $altBody .= $url;
    $altBody .= '\n\nBitte tragen Sie dort alle Ihre zu verkaufenden Artikel mit Preisen bis zum 05.03.2015  ein.\n\n';
    $altBody .= 'Ihr TuKi-Team';

    $mail = new PHPMailer;

    $mail->CharSet = "iso-8859-1"; //'iso-8859-1';   UTF-8
    $mail->isSMTP(); // Set mailer to use SMTP
    $mail->Host = 'smtp.1und1.de'; // Specify main and backup server
    $mail->SMTPAuth = true; // Enable SMTP authentication
    $mail->Username = 'tuki@tv-hechtsheim.de'; // SMTP username
    $mail->Password = 'tuki1882'; // SMTP password
    $mail->SMTPSecure = 'ssl'; // Enable encryption, 'ssl' also accepted
    $mail->Port = "465";

    $mail->From = 'tuki@tv-hechtsheim.de';

    $mail->FromName = 'TuKi-Basar Team';

    $mail->addAddress($mailAddress);

    // also notify developer and team
    $mail->addBCC('u.belitz@gmx.de', 'Ulrich Belitz');
    $mail->addCC('tuki@tv-hechtsheim.de');

    //$mail->addAddress('ellen@example.com');               // Name is optional
    //$mail->addReplyTo('info@example.com', 'Information');
    //$mail->addCC('cc@example.com');
    //$mail->addBCC('bcc@example.com');

    $mail->WordWrap = 50; // Set word wrap to 50 characters


    //$mail->addAttachment('/var/tmp/file.tar.gz');         // Add attachments
    //$mail->addAttachment('/tmp/image.jpg', 'new.jpg');    // Optional name
    $mail->isHTML(true); // Set email format to HTML

    $mail->Subject = utf8_decode('Ihre TuKi-Basar Artikelliste');
    $mail->Body = utf8_decode($body);
    $mail->AltBody = utf8_decode($altBody);


    //$mail->SMTPDebug = 1;

    if (!$mail->send()) {
        echo 'Nachricht an ' . $sellerNumber . ' konnte nicht gesendet werden. ';
        echo 'Fehlermeldung: ' . $mail->ErrorInfo . '<br />';
    }

    echo 'Nachricht an ' . $sellerNumber . ' wurde gesendet.<br/>';
}

?>