<?php

$conn = new mysqli('localhost', 'root', 'Sdwkw1kp', 'world');
$q = mysqli_query($conn, "SELECT * FROM CITY LIMIT 20");

if ($conn->connect_error)
    die("Connection failed: " . $conn->connect_error);
else
    echo "Connection successful\n\n";

$first_row = true;
echo("<table>");
while ($row = mysqli_fetch_assoc($q)) {
    if ($first_row) {
        $first_row = false;
        echo '<tr>';
        foreach($row as $key => $field) {
            echo '<th>' . htmlspecialchars($key) . '</th>';
        }
        echo '</tr>';
    }
    echo '<tr>';
    foreach($row as $key => $field) {
        echo '<td>' . htmlspecialchars($field) . '</td>';
    }
    echo '</tr>';
}
echo("</table>");
$conn->close();

?>