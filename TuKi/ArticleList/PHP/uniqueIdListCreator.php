<!DOCTYPE html>
<meta charset="utf-8">
<html>
<head>
    <title>Unique ID Creator</title>
    <link rel="stylesheet" type="text/css" href="../CSS/global.css" media="all"/>
</head>
<body>
<div class="code">
    <?php

    $startNumberOfUniqueIds = 0;
    $endNumberOfUniqueIds = 999;

    $uniqueIds = array();

    do {
        $uniqueIds = array();
        for ($i = $startNumberOfUniqueIds; $i <= $endNumberOfUniqueIds; $i++) {
            $id = md5(uniqid());
            echo $id . " = " . $i . '<br />';
            $uniqueIds[$i] = $id;
        }
    } while (count($uniqueIds) !== count(array_unique($uniqueIds)));

    $fileName = "../Data/uniqueIds.txt";
    $fh = fopen($fileName, "w");
    for ($i = $startNumberOfUniqueIds; $i <= $endNumberOfUniqueIds; $i++) {
        fwrite($fh, $uniqueIds[$i] . " = " . $i . "\n");
    }
    fclose($fh);



    ?>
</div>
</body>
</html>
