<?php
require_once("company_open.inc"); 
session_start();
?>
<!DOCTYPE html>
<html lang="en">
<head>
	<meta charset="UTF-8">
	<meta http-equiv="X-UA-Compatible" content="IE=edge">
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<link rel="stylesheet" href="../CSS/common.css">
	<link rel="stylesheet" href="../CSS/addCompany.css">
	<title>廠商管理</title>
</head>
<body>
	<header id = 'nav'></header>
	<form method="post" action="addCompany.php" >
	<div id = "information">
		<div>名稱 <input type="text" id = "companyName" name = "companyName"></div>
		<div>負責人 <input type="text" id = "bossName" name = "bossName" style = "width: 150px;"></div>
		<div>地址 <input type="text" id = "address" name = "address"></div>
		<div>電話 <input type="text" id = "phone" name = "phone"></div>
		<div>
			<button id = "addButton" name = "addButton">加入</button>
		</div>
	</div>
	</form>
	<?php
	$sql = "SELECT * FROM supplier"; 
	$records_per_page = 8;  // 每一頁顯示的記錄筆數
	// 取得URL參數的頁數
	if (isset($_GET["Pages"]))
		$pages = $_GET["Pages"];
	else                       
		$pages = 1;
	// 執行SQL查詢
	$result = mysqli_query($link, $sql);
	$total_fields=mysqli_num_fields($result); // 取得欄位數
	$total_records=mysqli_num_rows($result);  // 取得記錄數
	// 計算總頁數
	$total_pages = ceil($total_records/$records_per_page);
	// 計算這一頁第1筆記錄的位置
	$offset = ($pages - 1)*$records_per_page;
	mysqli_data_seek($result, $offset); // 移到此記錄
	echo "<br><table border=1 id = tab><tr>";
		
   		echo "<td style='width:70px 'align='center' valign='middle'>公司編號</td>";
		echo "<td style='width:80px' align='center' valign='middle'>電話號碼</td>";
		echo "<td align='center' valign='middle'>地址</td>";
		echo "<td align='center' valign='middle'>公司名稱</td>";
		echo "<td align='center' valign='middle'>負責人名稱</td>";
	echo "</tr>";
	$j = 1;
	while ($rows = mysqli_fetch_array($result, MYSQLI_NUM)and $j <= $records_per_page) {
   		echo "<tr>";
   		for ( $i = 0; $i<= $total_fields-1; $i++ )
      		echo "<td align='center' valign='middle'>".$rows[$i]."</td>";
   		echo "</tr>";
   		$j++;
	}
	echo "</table><br>";
	echo "<div id = page>";
	if ( $pages > 1 )  // 顯示上一頁
   		echo "<a href='addCompany.php?Pages=".($pages-1)."'>上一頁</a> ";
	for ( $i = 1; $i <= $total_pages; $i++ )
		if ($i != $pages)
			echo "<a href=\"addCompany.php?Pages=".$i."\">".$i."</a> ";
		else
			echo $i." ";
	if ( $pages < $total_pages )  // 顯示下一頁
		echo "<a href='addCompany.php?Pages=".($pages+1)."'>下一頁</a> ";
	echo "</div>";
	mysqli_free_result($result);  // 釋放佔用的記憶體
	?>
	<?php
	if(isset($_POST["addButton"]))
    {
        if ( isset($_POST["companyName"]) && isset($_POST["bossName"]) && isset($_POST["address"]) && isset($_POST["phone"]) ) {
			$companyName = $_POST["companyName"];
      		$bossName = $_POST["bossName"];
      		$address = $_POST["address"];
      		$phone = $_POST["phone"];
			$alertTimes = 0;
			if($companyName != "" &&  $bossName != "" && $address != "" && $phone != ""){
				if(mb_strlen($companyName)>20){
					echo "<script>alert('公司名稱字數不得大於20')</script>";
					$alertTimes++;
				}
					
				if(mb_strlen($bossName)>50){
					echo "<script>alert('公司負責人字數不得大於50')</script>";
					$alertTimes++;
				}

				if(mb_strlen($address)>50){
					echo "<script>alert('地址字數不得大於50')</script>";
					$alertTimes++;
				}

				if(mb_strlen($phone)>20){
					echo "<script>alert('電話號碼長度不得大於20')</script>";
					$alertTimes++;
				}
				
				if($alertTimes == 0){
					$sql = "INSERT INTO `supplier`(`phoneNumber`, `address`, `supplierName`, `leaderName`) VALUES ('$phone','$address','$companyName','$bossName')";
					if (mysqli_query($link, $sql)) { // 執行SQL指令
						echo "<script>alert('資料新增成功')</script>";
						echo "<script>window.location.href='addCompany.php'</script>";
					}
				}
				
			}
			else{
				echo "<script>alert('資料未填寫完整，無法新增')</script>";
				echo "<script>window.location.href='addCompany.php'</script>";
			}
			
		}
    }
	?>
</body>
<?php
	if(isset($_SESSION["account"])){
		$sql = "SELECT * FROM `staff` WHERE account = '".$_SESSION["account"]."'";
		$result = mysqli_query($link, $sql);
		$data = mysqli_fetch_assoc($result);
		if($data["staffId"] == 4000)
			echo "<script src='../JS/navbar.js'></script>";
		else if($data["staffId"] == 4001)
			echo "<script src='../JS/navbarPersonnel.js'></script>";
		else if($data["staffId"] == 4002)
			echo "<script src='../JS/navbarTreasure.js'></script>";
		else if($data["staffId"] == 4003)
			echo "<script src='../JS/navbarWarehouseStaff.js'></script>";
		}
	?>
</html>
<?php
require_once("company_close.inc"); 
?>