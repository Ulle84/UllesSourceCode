<?php


class UniqueIdList
{
    private $uniqueIds = array();

    public function createNewList($startNumber, $endNumber)
    {
        do {
            $this->uniqueIds = array();
            for ($i = $startNumber; $i <= $endNumber; $i++) {
                $id = md5(uniqid());
                $this->uniqueIds[$i] = $id;
            }
        } while (count($this->uniqueIds) !== count(array_unique($this->uniqueIds)));

        $this->writeFile("../Data/uniqueIds_classTest.txt");

    }

    public function printList()
    {
        echo '<div class="code">';

        foreach ($this->uniqueIds as $sellerNumber => $id)
        {
            echo $id . " = " . $sellerNumber . '<br />';
        }

        echo '</div>';
    }

    public function readFile($fileName)
    {
        if (file_exists($fileName)) {
            $lines = file($fileName);

            foreach ($lines as $line) {
                $data = explode(' = ', trim($line));
                $this->uniqueIds[$data[1]] = $data[0];
            }
        }
    }

    private function writeFile($fileName)
    {
        $fh = fopen($fileName, "w");
        /*for ($i = $this->startNumber; $i <= $this->endNumber; $i++) {
            fwrite($fh, $this->uniqueIds[$i] . " = " . $i . "\n");
        }*/
        foreach ($this->uniqueIds as $sellerNumber => $id)
        {
            fwrite($fh, $id . " = " . $sellerNumber . "\n");
        }
        fclose($fh);
    }
}