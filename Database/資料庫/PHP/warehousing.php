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
	<link rel="stylesheet" href="../CSS/warehousing.css">
	<title>庫存資料</title>
</head>
<body>
	<header id = 'nav'></header>
	
	<table id = "warehousingTable">
		<tr id = "title">
		<?php	
			echo "<table border=1 style = 'margin-left:100px'><tr><th>商品編號</th>";
			echo "<th style='width:110px;'>商品名稱</th><th style='width:160px;'>廠商名稱</th>";
			echo "<th>剩餘數量</th></tr>"; 
		?>
		</tr>
		<?php 
		
		
		$sql = "SELECT stock.`commodityId`,commodity.`commodityName`,supplier.`supplierName`
					, SUM(commoditydetails.`totalQuantity`) - SUM(verificationsheetdetails.`verificationSheetQuantity`) AS stockQuantity
					FROM `stock` 
					LEFT JOIN `commodity` ON stock.commodityId = commodity.commodityId 
					LEFT JOIN `supplier` ON commodity.supplierId = supplier.supplierId
					LEFT JOIN `commoditydetails` ON stock.`commodityId` = commoditydetails.`commodityId`
					LEFT JOIN `verificationsheetdetails` ON `stock`.`commodityId` = verificationsheetdetails.`commodityId`
					GROUP BY stock.`commodityId`,commodity.`commodityName`
					HAVING (stockQuantity) >0
					ORDER BY stock.`commodityId` ASC";

		$records_per_page = 5;  // 每一頁顯示的記錄筆數
		if (isset($_GET["Pages"])) $pages = $_GET["Pages"];
		else                       $pages = 1;

		$result = mysqli_query($link, $sql);
		$total_fields=mysqli_num_fields($result); // 取得欄位數
		$total_records=mysqli_num_rows($result);  // 取得記錄數
		$total_pages = ceil($total_records/$records_per_page);
		$offset = ($pages - 1)*$records_per_page;
		mysqli_data_seek($result, $offset); // 移到此記錄
		$j = 1;
		while ($rows = mysqli_fetch_array($result, MYSQLI_BOTH) and $j <= $records_per_page) {
				
			echo "<tr>";
			for ( $i = 0; $i<= $total_fields-1; $i++ ){
			   echo "<th >".$rows[$i]."</th>"; 
		   
		   }
		   //echo "<td><a href='warehousingModify.php?action=edit&id=";
		   //echo $rows[0]."'><b>修改</b></td>";
		  // echo "</tr>";   

			echo "</tr>";
			$j++;
		
		   
	   }
	?>
	<td  colspan="10" align='right'> 
	<?php
	   echo "<div id = 'page'  >";
	   if ( $pages > 1 )  // 顯示上一頁
		 	echo "<a href='warehousing.php?Pages=".($pages-1). "'>上一頁</a>| ";
  			for ( $i = 1; $i <= $total_pages; $i++ )
		 if ($i != $pages)
		   echo "<a href=\"warehousing.php?Pages=".$i."\">".$i."</a> ";
		 else
		   echo $i." ";

  		if ( $pages < $total_pages )  // 顯示下一頁
		 echo "|<a href='warehousing.php?Pages=".($pages+1).
		  "'>下一頁</a> ";
 		mysqli_free_result($result);  // 釋放佔用的記憶體
	  
	   ?>
	   </td>
	
	<?php 
		 
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