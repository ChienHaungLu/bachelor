<!-- 程式範例：company_open.inc -->
<?php
// 建立MySQL的資料庫連接
$link = mysqli_connect("localhost", "S10859045", "S10859045") 
        or die("無法開啟MySQL資料庫連接!<br/>");
mysqli_select_db($link, "company");  

//送出UTF8編碼的MySQL指令
mysqli_query($link, 'SET NAMES utf8'); 
?>