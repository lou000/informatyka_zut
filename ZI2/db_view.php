<?php

function printSelect($q){
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
}


try {
    $conn = new PDO("mysql:host=localhost;dbname=lab7", "root", "Sdwkw1kp");
    $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
    echo "Connection successful<br>";
} catch(PDOException $e) {
    echo "Connection failed: " . $e->getMessage();
}
$conn->exec("DROP VIEW IF EXISTS view1, view2, view3;");
$q = $conn->exec(
" 
CREATE VIEW view1
AS 
SELECT 
	customerNumber, 
	orderNumber,
	SUM(quantityOrdered) numberOfItemsOrdered,
	paymentDate,
	amount
	status
 FROM
	customers
 INNER JOIN
	payments USING (customerNumber)
INNER JOIN
	orders USING (customerNumber)
INNER JOIN
	orderdetails USING (orderNumber)
GROUP BY customerNumber;");

if($q === FALSE) {
    print "Failed to set view1: " . $conn->errorMsg();
}else{
    print "View1 created successfully<br>";
}

$q = $conn->exec(
    " 
CREATE VIEW view2
AS 
 SELECT 
	employeeNumber,
	customerNumber,
    contactFirstName,
    contactLastName,
    concat_ws('', addressLine1, addressLine2) adress,
	amount,
    orderDate,
    status
FROM
	employees
INNER JOIN
	customers ON employeeNumber = salesRepEmployeeNumber
INNER JOIN
	payments USING (customerNumber)
INNER JOIN
	orders USING (customerNumber)
ORDER BY employeeNumber DESC, orderDate DESC");

if($q === FALSE) {
    print "Failed to set view2: " . $conn->errorMsg();
}else{
    print "View2 created successfully<br>";
}

$q = $conn->exec(
    " 
CREATE VIEW view3
AS 
 SELECT 
	customerNumber,
    employees.*
FROM
	customers
INNER JOIN
	employees ON employeeNumber = salesRepEmployeeNumber");

if($q === FALSE) {
    print "Failed to set view3: " . $conn->errorMsg();
}else{
    print "View3 created successfully<br>";
}

$q = $conn->query("SELECT * FROM view3;");
printSelect($q);



