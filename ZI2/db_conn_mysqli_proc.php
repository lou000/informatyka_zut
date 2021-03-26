<?php

$conn = mysqli_connect('localhost', 'root', 'Sdwkw1kp', 'world');
$q = mysqli_query($conn, "SELECT * FROM CITY LIMIT 20");

if (mysqli_connect_errno()) {
    echo("Connection failed: " . mysqli_connect_error());
    exit();
}
else
    echo "Connection successful";

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