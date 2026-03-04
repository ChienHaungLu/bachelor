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
	<link rel="stylesheet" href="../CSS/addProduct.css">
	<title>商品管理</title>
</head>
<body>
	<header id = 'nav'></header>
	<form method="post" action="addProduct.php"  >
		<div id = "information">
		<div>廠商名稱 
			<select type ="text" name="companyName" id="companyName">
			<?php 
				$sql = "SELECT * FROM supplier"; //從company某個table選擇所有資料
				$result = mysqli_query($link,$sql);
				$i=0;
				while($row = mysqli_fetch_assoc($result)){
					$i++;
					$name = $row['supplierName'];
					echo "<option value=$name>";
					echo $name; 
					echo "</option>";
					}
			?>
			</select>
		</div>
		<div>商品名稱 <input type="text" id = "productName"name = "productName"></div>
		<div>商品入數 <input type="text" id = "prouductSet" name = "prouductSet"></div>
		<div>
			<button id = "addButton" name = "addButton">加入</button>
		</div>
		</div>
	</form>
	
	<?php
	$sql = "SELECT * FROM commodity"; 
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
	echo "<table border=1 id = tab style = 'margin-left: 390px;margin-top: 100px;'><tr>";
   		echo "<td align='center' valign='middle'>商品編號</td>";
		echo "<td align='center' valign='middle'>商品名稱</td>";
		echo "<td align='center' valign='middle'>供應商編號</td>";
		echo "<td align='center' valign='middle'>商品入數</td>";
	echo "</tr>";
	$j = 1;
	while ($rows = mysqli_fetch_array($result, MYSQLI_NUM)and $j <= $records_per_page) {
   		echo "<tr>";
   		for ( $i = 0; $i<= $total_fields-1; $i++ )
      		echo "<td align='center' valign='middle'>".$rows[$i]."</td>";
   		echo "</tr>";
   		$j++;
	}
	?>
	
	 <td  colspan="4" align='right'> 
<?php
	echo "<div id = 'page'  >";
	if ( $pages > 1 )  // 顯示上一頁
   		echo "<a href='addProduct.php?Pages=".($pages-1)."' >上一頁</a> ";
	for ( $i = 1; $i <= $total_pages; $i++ )
		if ($i != $pages)
			echo "<a href=\"addProduct.php?Pages=".$i."\">".$i."</a> ";
		else
			echo $i." ";
	if ( $pages < $total_pages )  // 顯示下一頁
		echo "<a href='addProduct.php?Pages=".($pages+1)."'>下一頁</a> ";
	echo "</div>"; 
?>
	</td>
	<?php

	echo "</table><br>";
	mysqli_free_result($result);  // 釋放佔用的記憶體
	?>


	<?php
	if(isset($_POST["addButton"]))
    {
        if (isset($_POST["companyName"])&& isset($_POST["productName"]) && isset($_POST["prouductSet"])) {
			$companyName = $_POST["companyName"];
      		$productName = $_POST["productName"];
      		$prouductSet = $_POST["prouductSet"];
			$alertTimes = 0;
			if($companyName != "" &&  $productName != "" && $prouductSet != ""){	
				if(mb_strlen($productName)>50){
					echo "<script>alert('商品名稱字數不得大於50')</script>";
					$alertTimes++;
				}

				if(mb_strlen($prouductSet)>11){
					echo "<script>alert('商品一入個數不得大於11位數')</script>";
					$alertTimes++;
				}
				
				if($alertTimes == 0){
					$sql = "SELECT * FROM `supplier` WHERE supplierName = '".$companyName."'";
					echo $companyName;
					$result = mysqli_query($link, $sql);
					$data = mysqli_fetch_assoc($result);
					$ID = $data["supplierId"];
					$sql = "INSERT INTO `commodity`(`commodityName`, `supplierId`, `commoditySet`) VALUES ('$productName','$ID','$prouductSet')";
					if (mysqli_query($link, $sql)) { // 執行SQL指令
						echo "<script>alert('資料新增成功')</script>";
						echo "<script>window.location.href='addProduct.php'</script>";
					}
				}
			}
			else{
				echo "<script>alert('資料未填寫完整，無法新增')</script>";
				echo "<script>window.location.href='addProduct.php'</script>";
			}
			
		}
    }
	?>

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
</body>
</html>
<?php
	require_once("company_close.inc"); 
?>