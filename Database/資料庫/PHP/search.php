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
	<link rel="stylesheet" href="../CSS/search.css">
	<title>搜尋</title>
</head>
<body>

	<header id = 'nav'></header>
	<form action="search.php" method="post">
	<div id = "searchBlock">

		<div>
			<div class = "choose">日期時間 <input type="date" name="date" id="date"/></div>
			<div class = "choose">商品名稱 <select name="productName" id="productName" >
			<?php 
					echo "<option value>請選擇</option>"; 
					$sql = "SELECT * FROM commodity"; //從company某個table選擇所有資料
					$result = mysqli_query($link,$sql);
					$i=0;
					while($row = mysqli_fetch_assoc($result)){
						$i++;
						$productName=$row['commodityName'];
						echo "<option value=$productName>";
						echo $productName; 
						echo "</option>";
					}
				?>
			</select></div>

			<div class = "choose">廠商名稱 <select name="companyName" id="companyName">
				<?php 
					echo "<option value>請選擇</option>"; 
					$sql = "SELECT * FROM supplier"; //從company某個table選擇所有資料
					$result = mysqli_query($link,$sql);
					$i=0;
					while($row = mysqli_fetch_assoc($result)){
						$i++;
						$companyName = $row['supplierName'];
						echo "<option value=$companyName>";
						echo $companyName; 
						echo "</option>";
					}
				?>
			</select></div>
			
			<div class = "choose">製單人員名稱 <select name="staffName" id="staffName">
				<?php
					echo "<option value>請選擇</option>";  
					$sql = "SELECT * FROM staff"; //從company某個table選擇所有資料
					$result = mysqli_query($link,$sql);
					$i=0;
					while($row = mysqli_fetch_assoc($result)){
						$i++;
						$staffName = $row['staffName'];
						echo "<option value=$staffName>";
						echo $staffName; 
						echo "</option>";
					}
				?>
			</select></div>	

		</div>

		<div>
			<input id = searchButton type="submit" name="cleanButton" value="清除表格"><input id = searchButton type="submit" name="submitButton" value="搜尋">
		</div>

	</div>
		
	</form>

	<?php 
		if (isset($_POST["Search"])) // 建立SQL字串
		{
			if ( isset($_SESSION["SQL"]))
			 {
				 $sql1 = $_SESSION["SQL"];
				 
			}

	   } ?>

	<table width='1300' border='2' align='center' style = "margin-top: 50px;">
	   <td style='width:125px;' align='center' valign='middle'>日期時間</td><td style='width:125px;' align='center' valign='middle'>進貨單編號</td>
	   <td style='width:150px;' align='center' valign='middle'>商品編號</td><td style='width:150px;' align='center' valign='middle'>商品名稱</td>
	   <td style='width:175px;' align='center' valign='middle'>廠商名稱</td><td style='width:150px;' align='center' valign='middle'>製單人員</td>
	   <td style='width:075px;' align='center' valign='middle'>入數</td><td style='width:075px;' align='center' valign='middle'>件數</td>
	   <td style='width:085px;' align='center' valign='middle'>單價</td><td style='width:085px;' align='center' valign='middle'>小計</td>

		<?php
			if(isset ($_POST["submitButton"]))
			{
				$_date = $_POST["date"];	
				$_companyName = $_POST["companyName"];
				$_productName = $_POST["productName"];
				$_staffName = $_POST["staffName"];

				if($_date=="" AND  $_productName=="" AND $_staffName=="" AND $_companyName=="")
				{
					echo "<script>alert('請確認資料已選擇後再次搜尋')</script>";
					echo "<script>window.location.href='search.php'</script>";
				}
				else 
				{
					$sql1 = "SELECT DISTINCT * FROM `purchaseorder` 
								inner join  `commoditydetails` ON purchaseorder.purchaseOrderId = commoditydetails.purchaseOrderId 
								inner join  `commodity` ON commoditydetails.commodityId=commodity.commodityId 
								inner join 	`supplier` ON purchaseorder.supplierId = supplier.supplierId 
								inner join 	`staff` ON purchaseorder.operator = staff.staffId 
								WHERE orderDate = '".$_date."' OR commodityName ='".$_productName."' OR supplierName = '".$_companyName."' OR staffName ='".$_staffName."'" ;
					
					$result1 = mysqli_query($link,$sql1);
					while($data1= mysqli_fetch_assoc($result1))
					{ 	?>		
						<?php 		
							$date=$data1["orderDate"];
							$purchaseorderID = $data1["purchaseOrderId"];
							$supplierName = $data1["supplierName"];
							$operator = $data1["staffName"];	
							$item = $data1["item"];
							$cost = $data1["cost"];
							$productname = $data1["commodityName"];
							$commoditySet = $data1["commoditySet"];
							$_productID = $data1["commodityId"];
							$totalexpenses = $item*$commoditySet*$cost ;
							
						?>
							<tr>
								<td align='center' valign='middle'><?php echo $date ?></td>
								<td align='center' valign='middle'><?php echo $purchaseorderID ?></td>
								<td align='center' valign='middle'><?php echo $_productID ?></td>
								<td align='center' valign='middle'><?php echo $productname ?></td>
								<td align='center' valign='middle'><?php echo $supplierName ?></td>
								<td align='center' valign='middle'><?php echo $operator?> </td>
								<td align='center' valign='middle'><?php echo $commoditySet?></td>
								<td align='center' valign='middle'><?php echo $item ?></td>
								<td align='center' valign='middle'><?php echo $cost?> </td>
								<td align='center' valign='middle'><?php echo $totalexpenses ?></td>
							</tr> 

						<?php	
					}
				}	
			}
						?>
	</table>
			
	<?php
		if(isset($_SESSION["account"]))
		{
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