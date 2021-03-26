<?php

try {
    $conn = new PDO("mysql:host=localhost;dbname=world", "root", "Sdwkw1kp");
    $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
    echo "Connection successful\n\n";

    $qStr = "INSERT INTO test (string, number) 
         VALUES (:String, :Number);";


    $array = [
        "testTransactions",
        "testTransactions",
        "testTransactions",
        "testTransactions",
        "testTransactions",
        "testTransactions"
    ];

    $num =0;
    $str ='';
    $q = $conn->prepare($qStr);
    $q->bindParam(':String', $str);
    $q->bindParam(':Number', $num);

    try {
        $conn->beginTransaction();
        foreach ($array as $el) {
            $str = $el;
            $num = rand(0, 2000);
            $q->execute();
            echo "Row   " . $str . " " . $num . "  added.\n";
        }
    } catch (PDOException $e) {
            if ($conn->inTransaction())
                $conn->rollBack();
    }
    $conn->commit();


} catch(PDOException $e) {
    echo "Connection failed: " . $e->getMessage();
}
