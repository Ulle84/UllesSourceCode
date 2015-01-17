<?php

require_once 'UniqueIdList.php';
require_once 'ArticleList.php';
require_once 'Settings.php';

if (isset($_GET['seller'])) {
    $sellerNumber = $_GET['seller'];
} else {
    echo "Keine Verkäufernummer angegeben!";
    exit;
}

if (isset($_GET['id'])) {
    $id = $_GET['id'];
} else {
    echo "Keine ID angegeben!";
    exit;
}

if (isset($_GET['mode'])) {
    $mode = $_GET['mode'];
} else {
    $mode = 'view';
}

$uniqueIdList = new UniqueIdList();
$uniqueIdList->readFromFile("../Data/uniqueIds.txt");
if (!$uniqueIdList->checkId($sellerNumber, $id)) {
    echo "Kein Zugang!";
    exit;
}

$settings = new Settings();
$articleList = new ArticleList($sellerNumber, $id, $settings->minArticleNumber, $settings->maxArticleNumber);

if ($mode == 'edit') {
    $articleList->writeHtml();
}
else {
    $articleList->writePdf();
}

?>