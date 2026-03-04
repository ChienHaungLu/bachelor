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
	<link rel="stylesheet" href="../CSS/purchase.css">
	<link rel="stylesheet" href="../CSS/addOrder.css">
	<link rel="stylesheet" href="../CSS/addStaff.css">
    <title>報銷單資料</title>
</head>
<body>
    <header id = 'nav'></header>
	<div id = "buttonDiv" style = "margin-left:1300px"><button id = "addButton" onclick="window.location.href='addflaws.php'">新增報銷單</button></div>
	<div id = "information">
			<table width='900' border='2' align='center'>
			<td style='width:40px;' align='center' valign='middle'>日期</td>
			<td style='width:40px;' align='center' valign='middle'>報銷單編號</td>
			<td style='width:70px;' align='center' valign='middle'>廠商名稱</td>
			<td style='width:40px;' align='center' valign='middle'>製單人員</td>

		 <?php
			$sql = "SELECT  `orderDate`,`verificationSheetId`,`supplierName`,`staffName`
					FROM `verificationSheet`
					INNER JOIN `supplier` ON `verificationSheet`.suppilerId = supplier.supplierId
					INNER JOIN `staff` ON `verificationSheet`.staffId = `staff`.staffId
					GROUP BY verificationSheet.`verificationSheetId`
					ORDER BY verificationSheet.`verificationSheetId`";

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
				   echo "<td align='center' valign='middle'>".$rows[$i]."</td>"; 
				}
				echo "<td style='width:005px' ><a href='modifyflaws.php?action=Del&id=";
					echo $rows[1]."'><b align='center'>刪除</b></td>";
				echo "<td style='width:005px' ><a href='flawsDetails.php?action=edit&id=";
			 		echo $rows[1]."'><b align='center'>明細</b></td>";
					echo "</tr>";   
				echo "</tr>";
				$j++;
			   
		   }
		?>
		<td  colspan="6" align='right'> 
		<?php	   
			if ( $pages > 1 )  // 顯示上一頁
				echo "<a href='flaws.php?Pages=".($pages-1)."'>上一頁</a>| ";
			for ( $i = 1; $i <= $total_pages; $i++ )
				if ($i != $pages)
					echo "<a href=\"flaws.php?Pages=".$i."\">".$i."</a> ";
				else
					echo $i." ";
			if ( $pages < $total_pages )  // 顯示下一頁
				echo "|<a href='flaws.php?Pages=".($pages+1)."'>下一頁</a> ";
			mysqli_free_result($result);  // 釋放佔用的記憶體
				
		?>	
		</td>
		
		<?php echo "</table><br>" ?>

	</div>

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