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
	<title>進貨資料</title>
</head>
<body>
	<header id = 'nav'></header>
	<?php
		$id = $_GET["id"];  // 取得URL參數的編號  進貨單編號
	?>
	<div>
		<div id = "buttonDiv">
			<button id = "addButton"style = "margin-left: 1300px;" onclick="window.location.href='purchase.php'">返回進貨單</button>
		</div>
			
			<table width='900' border='2' align='center' style = "margin-top: 50px;">
			<td style='width:70px;' align='center' valign='middle'>進貨單編號</td><td style='width:85px;' align='center' valign='middle'>商品名稱</td>
			<td style='width:060px;' align='center' valign='middle'>入數</td><td style='width:060px;' align='center' valign='middle'>件數</td>
	  		 <td style='width:060px;' align='center' valign='middle'>單價</td><td style='width:060px;' align='center' valign='middle'>小計</td>
			
			 

		 <?php
			$sql = "SELECT purchaseorder.`purchaseorderId`, commodity.`commodityName`,commodity.`commoditySet`, commodityDetails.`item`,commodityDetails.`cost`,(commodity.`commoditySet` * commodityDetails.`item` * commodityDetails.`cost`),commoditydetails.`commodityId`
					FROM purchaseorder 
					JOIN commoditydetails  ON  purchaseorder.purchaseOrderId = commoditydetails.purchaseOrderId 
					JOIN supplier ON purchaseOrder.supplierId = supplier.supplierId  
					JOIN staff ON purchaseOrder.operator = staff.staffId 
					JOIN commodity ON commodityDetails.commodityId = commodity.commodityId  
					WHERE purchaseOrder.purchaseOrderId = $id";


			$records_per_page = 5;  // 每一頁顯示的記錄筆數
			if (isset($_GET["Pages"])) $pages = $_GET["Pages"];
			else                       $pages = 1;

			$result = mysqli_query($link, $sql);
			$total_fields=mysqli_num_fields($result); // 取得欄位數
			$total_records=mysqli_num_rows($result);  // 取得記錄數
			$total_pages = ceil($total_records/$records_per_page);
			$offset = ($pages - 1)*$records_per_page;
			mysqli_data_seek($result, $offset); // 移到此記錄
		
			while($data= mysqli_fetch_assoc($result))
			{
				$commodityid = $data["commodityId"];
				$commodityname = $data["commodityName"];
				$commodityset = $data["commoditySet"];
				$item = $data["item"];
				$cost = $data["cost"];
				$totalexpenses = $commodityset*$item*$cost;
					echo "<tr>" ?>	<td align='center' valign='middle'><?php echo $id ?></td> 
									<td align='center' valign='middle'><?php echo $commodityname ?></td> 
									<td align='center' valign='middle'><?php echo $commodityset ?></td> 
									<td align='center' valign='middle'><?php echo $item ?></td>
									<td align='center' valign='middle'><?php echo $cost ?></td> 
									<td align='center' valign='middle'><?php echo $totalexpenses ?></td> 
				<?php 	
						echo "<td style='width:015px' ><a href='modifyOrder.php?action=del&id=";
							echo $id."&productid=";echo $commodityid."'><b>刪除</b></td>";
						echo "<td style='width:015px' ><a href='modifyOrder.php?action=edit&id=";
							echo $id."&productid=";echo $commodityid."'><b>編輯</b></td>";
					echo "</tr>";   
		   }
		?>

		<td  colspan="8" align='right'> 
	<?php	   
			if ( $pages > 1 )  // 顯示上一頁
   				echo "<a href='commodityDetails.php?Pages=".($pages-1)."'>上一頁</a>| ";
			for ( $i = 1; $i <= $total_pages; $i++ )
   				if ($i != $pages)
     				echo "<a href=\"commodityDetails.php?Pages=".$i."\">".$i."</a> ";
   				else
     				echo $i." ";
			if ( $pages < $total_pages )  // 顯示下一頁
   				echo "|<a href='commodityDetails.php?Pages=".($pages+1)."'>下一頁</a> ";
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