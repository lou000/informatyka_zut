<?php

$conn = new PDO("mysql:host=localhost;dbname=world", "root", "Sdwkw1kp");
$q = $conn->query("SELECT * FROM CITY LIMIT 20");

try {
    $conn = new PDO("mysql:host=localhost;dbname=world", "root", "Sdwkw1kp");
    $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
    echo "Connection successful\n\n";
} catch(PDOException $e) {
    echo "Connection failed: " . $e->getMessage();
}

$first_row = true;
echo("<table>");
$table = $q->fetchAll(PDO::FETCH_ASSOC);
foreach ($table as $row) {
    if ($first_row) {
        $first_row = false;
        echo '<tr>';
            foreach ($row as $key => $field)
                echo '<th>' . htmlspecialchars($key) . '</th>';
        echo '</tr>';
    }
    echo '<tr>';
        foreach ($row as $key => $field)
        echo '<td>' . htmlspecialchars($field) . '</td>';
    echo '</tr>';
}
echo("</table>");


