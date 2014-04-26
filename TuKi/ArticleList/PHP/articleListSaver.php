<?php

$content = $_POST['content'];

$fileName = "../Data/articleList.txt";
$fh = fopen($fileName, "w");
fwrite($fh, $content);
fclose($fh);

echo "Artikelliste wurde gespeichert!";

?>