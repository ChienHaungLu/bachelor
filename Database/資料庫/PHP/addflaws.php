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
	<link rel="stylesheet" href="../CSS/addOrder.css">
	<link rel="stylesheet" href="../CSS/addStaff.css">
	<title>新增瑕疵單</title>
</head>
<body>
<header id = 'nav'></header>
	<form method="post" action="addflaws.php" >
		<div id = "information" class="ticket">
			<div>日期:<input type="date"  name="orderDate0"         id="orderDate"></div>
			<div>報銷單編號:<input type="text"  name="purchaseOrderCode0" id="purchaseOrderCode" style="width: 150px;"></div>
			<div>廠商: <select type="text" name="supplierName0"      id="supplierName">
				<?php 
				echo "<option value>請選擇</option>";
				$sql = "SELECT * FROM supplier";
				$result = mysqli_query($link,$sql);
				$i=0;
				while($row = mysqli_fetch_assoc($result)){
					$i++;
					$supplierId=$row['supplierId'];
					$supplierName=$row['supplierName'];
					echo "<option value=$supplierId>";
					echo $row['supplierName']; 
					echo "</option>";
					}
				?>
			</select></div>
			<div style = "width: 200px;">製單人員: <select type="text" name="staffName0" id="staffName">
				<?php 
				echo "<option value>請選擇</option>";
				$sql = "SELECT * FROM staff";
				$result = mysqli_query($link,$sql);
				$i=0;
				while($row = mysqli_fetch_assoc($result)){
					$i++;
					$staffId=$row['staffId'];
					$staffName=$row['staffName'];
					echo "<option value=$staffId>";
					echo $row['staffName']; 
					echo "</option>";
					} 
				?>
			</select></div>
		<input id = "changeAuthorityButton" type="submit" name="submitButton" value="新增"/>
		</div>
	</form>

	<form method="post" action="addflaws.php" >
		<div id = "information" class="ticket" style="border-bottom-left-radius:0px;border-bottom-right-radius:0px;">

	<?php 
		if(isset ($_POST["submitButton"]))
		{
			$a = $_POST["orderDate0"]; 
			$b = $_POST["purchaseOrderCode0"];
			$c = $_POST["supplierName0"];
			$d = $_POST["staffName0"];

			if($a=="" AND  $b=="" AND $c=="" AND $d=="")
			{
				echo "<script>alert('請確認資料已選擇後再次搜尋')</script>";
				echo "<script>window.location.href='addOrder.php'</script>";
			}
			else 
			{
	?>
			<div>日期:<input type="date"  name="orderDate" id="orderDate" value = <?php echo $a ?> readonly required></div>
			<div>報銷單編號:<input type="text"  name="verificationSheetId" id="verificationSheetId"style="width: 150px;" value = <?php echo $b ?> readonly required></div>
			<div>廠商: <select type="text" name="supplierName"      id="supplierName">
				<?php 
				$sql = "SELECT supplierName FROM supplier WHERE supplierId=$c";
				$result = mysqli_query($link,$sql);
				while($row = mysqli_fetch_assoc($result)){
				$supplierName=$row['supplierName'];
				$supplierId=$row['supplierId'];
				echo "<option value=$c>$supplierName</option>";
				}
				?>
			</select></div>
			<div style = "width: 200px;">製單人員: <select type="text" name="staffName" id="staffName">
				<?php 
				$sql = "SELECT staffName FROM staff WHERE staffId=$d";
				$result = mysqli_query($link,$sql);
				while($row = mysqli_fetch_assoc($result)){
				$staffName=$row['staffName'];
				$staffId=$row['staffId'];
				echo "<option value=$d>$staffName</option>";
				}
				?> 
			</select></div>
		</div>

		<div id = "information" class="ticket" style="margin-top:0px;border-top-left-radius:0px;border-top-right-radius:0px;">
			<table>
				<tr><td>商品名稱:</td><td>報銷數量</td></tr>
				<tr><!-- ==================================================第一筆商品明細====================================================== -->
				<td><div><select type="text" name="commodityName1" id="commodityName">
					<?php 
					echo "<option value>請選擇</option>";
					$sql = "SELECT * FROM commodity WHERE supplierId = $c"; //從company某個table選擇所有資料
					$result = mysqli_query($link,$sql);
					$i=0;
					while($row = mysqli_fetch_assoc($result)){
						$i++;
						$commodityId=$row['commodityId'];
						echo "<option value=$commodityId>";
						echo $row['commodityName']; //商品名稱
						echo "</option>";
					}
					?>
				</select></div></td>
				<td><div><input type="number" name="verificationSheetQuantity1" value="0"/></div></td>
				</tr>
				<tr><!-- ==================================================第二筆商品明細====================================================== -->
				<td><div><select type="text" name="commodityName2" id="commodityName">
					<?php 
					echo "<option value>請選擇</option>";
					$sql = "SELECT * FROM commodity WHERE supplierId = $c"; //從company某個table選擇所有資料
					$result = mysqli_query($link,$sql);
					$i=0;
					while($row = mysqli_fetch_assoc($result)){
						$i++;
						$commodityId=$row['commodityId'];
						echo "<option value=$commodityId>";
						echo $row['commodityName']; //商品名稱
						echo "</option>";
					}
					?>
				</select></div></td>
				<td><div><input type="number" name="verificationSheetQuantity2" value="0"/></div></td>
				</tr>
				<tr><!-- ==================================================第三筆商品明細====================================================== -->
				<td><div><select type="text" name="commodityName3" id="commodityName">
					<?php 
					echo "<option value>請選擇</option>";
					$sql = "SELECT * FROM commodity WHERE supplierId = $c"; //從company某個table選擇所有資料
					$result = mysqli_query($link,$sql);
					$i=0;
					while($row = mysqli_fetch_assoc($result)){
						$i++;
						$commodityId=$row['commodityId'];
						echo "<option value=$commodityId>";
						echo $row['commodityName']; //商品名稱
						echo "</option>";
					}
					?>
				</select></div></td>
				<td><div><input type="number" name="verificationSheetQuantity3" value="0"/></div></td>
				</tr>
				<tr><!-- ==================================================第四筆商品明細====================================================== -->
				<td><div><select type="text" name="commodityName4" id="commodityName">
					<?php 
					echo "<option value>請選擇</option>";
					$sql = "SELECT * FROM commodity WHERE supplierId = $c"; //從company某個table選擇所有資料
					$result = mysqli_query($link,$sql);
					$i=0;
					while($row = mysqli_fetch_assoc($result)){
						$i++;
						$commodityId=$row['commodityId'];
						echo "<option value=$commodityId>";
						echo $row['commodityName']; //商品名稱
						echo "</option>";
					}
					?>
				</select></div></td>
				<td><div><input type="number" name="verificationSheetQuantity4" value="0"/></div></td>
				</tr>
				<tr><!-- ==================================================第五筆商品明細====================================================== -->
				<td><div><select type="text" name="commodityName5" id="commodityName">
					<?php 
					echo "<option value>請選擇</option>";
					$sql = "SELECT * FROM commodity WHERE supplierId = $c"; //從company某個table選擇所有資料
					$result = mysqli_query($link,$sql);
					$i=0;
					while($row = mysqli_fetch_assoc($result)){
						$i++;
						$commodityId=$row['commodityId'];
						echo "<option value=$commodityId>";
						echo $row['commodityName']; //商品名稱
						echo "</option>";
					}
					?>
				</select></div></td>
				<td><div><input type="number" name="verificationSheetQuantity5" value="0"/></div></td>
				</tr>

			</table>
	<?php 
			}
		}
	?>
		</div>
	<input id = "changeAuthorityButton" type="submit" name="submitButton1" style = "float: right;margin-right: 200px;margin-top: 20px;" value="新增報銷單"/>
	</form>

	<?php
		if(isset($_POST["submitButton1"]))
		{
			if 
			(
				(isset($_POST["orderDate"]) && isset($_POST["verificationSheetId"]) && isset($_POST["supplierName"]) && isset($_POST["staffName"])) &&
				(
					(isset($_POST["commodityName1"]) && isset($_POST["verificationSheetQuantity1"])) ||
					(isset($_POST["commodityName2"]) && isset($_POST["verificationSheetQuantity2"])) ||
					(isset($_POST["commodityName3"]) && isset($_POST["verificationSheetQuantity3"])) ||
					(isset($_POST["commodityName4"]) && isset($_POST["verificationSheetQuantity4"])) ||
					(isset($_POST["commodityName5"]) && isset($_POST["verificationSheetQuantity5"])) 
				)

			) 
			{
				$orderDate = $_POST["orderDate"];
				$verificationSheetId = $_POST["verificationSheetId"];
				$supplierName = $_POST["supplierName"];
				$staffName = $_POST["staffName"];


				$commodityName1 = $_POST["commodityName1"];
				$verificationSheetQuantity1 = $_POST["verificationSheetQuantity1"];

				$commodityName2 = $_POST["commodityName2"];
				$verificationSheetQuantity2 = $_POST["verificationSheetQuantity2"];

				$commodityName3 = $_POST["commodityName3"];
				$verificationSheetQuantity3 = $_POST["verificationSheetQuantity3"];

				$commodityName4 = $_POST["commodityName4"];
				$verificationSheetQuantity4 = $_POST["verificationSheetQuantity4"];

				$commodityName5 = $_POST["commodityName5"];
				$verificationSheetQuantity5 = $_POST["verificationSheetQuantity5"];

				// 檢查是否有輸入欄位資料
				if //廠商
				(
					($orderDate != "" && $verificationSheetId != "" && $supplierName != "" && $staffName != "") &&
					(
						($commodityName1 != "" && $verificationSheetQuantity1 != "") ||
						($commodityName2 != "" && $verificationSheetQuantity2 != "") ||
						($commodityName3 != "" && $verificationSheetQuantity3 != "") ||
						($commodityName4 != "" && $verificationSheetQuantity4 != "") ||
						($commodityName5 != "" && $verificationSheetQuantity5 != "") 
					)
				) 
				{
					$sql = "INSERT INTO `verificationsheet`(`orderDate`,`verificationSheetId`,`suppilerId`,`staffId`) 
							VALUES('$orderDate','$verificationSheetId','$supplierName','$staffName')";
							
					if ( mysqli_query($link, $sql) ) // 執行SQL指令
					{
						echo "<font color=red>新增報銷單廠商資料成功!";
						echo "</font><br/>";
					}
					else
					{
						echo "<font color=red>新增報銷單廠商資料失敗!";
						echo "</font><br/>";
					}
				}
				else
				{
					echo "<font color=red>未輸入報銷產品資料!";
					echo "</font><br/>";
				}
				if //1
				(
					($orderDate != "" && $verificationSheetId != "" && $supplierName != "" && $staffName != "") &&
					($commodityName1 != "" && $verificationSheetQuantity1 != "")
				) 
				{
					//$sql1 = "INSERT INTO `verificationsheet`(`orderDate`,`verificationSheetId`,`suppilerId`,`staffId`) VALUES('$orderDate','$verificationSheetId','$supplierName','$staffName')";
					$sql_1 = "INSERT INTO `verificationsheetdetails`(`verificationSheetId`,`commodityId`,`verificationSheetQuantity`) VALUES('$verificationSheetId','$commodityName1','$verificationSheetQuantity1')";
					if ( mysqli_query($link, $sql_1) ) // 執行SQL指令
					{
						echo "<font color=red>新增第一筆報銷商品資料成功!";
						echo "</font><br/>";
					}
					else
					{
						echo "<font color=red>新增第一筆報銷商品資料失敗!";
						echo "</font><br/>";
					}
				}
				if //2
				(
					($orderDate != "" && $verificationSheetId != "" && $supplierName != "" && $staffName != "") &&
					($commodityName2 != "" && $verificationSheetQuantity2 != "")
				) 
				{
					//$sql2 = "INSERT INTO `verificationsheet`(`orderDate`,`verificationSheetId`,`suppilerId`,`staffId`) VALUES('$orderDate','$verificationSheetId','$supplierName','$staffName')";
					$sql_2 = "INSERT INTO `verificationsheetdetails`(`verificationSheetId`,`commodityId`,`verificationSheetQuantity`) VALUES('$verificationSheetId','$commodityName2','$verificationSheetQuantity2')";
					if ( mysqli_query($link, $sql_2) ) // 執行SQL指令
					{
						echo "<font color=red>新增第二筆報銷商品資料成功!";
						echo "</font><br/>";
					}
					else
					{
						echo "<font color=red>新增第二筆報銷商品資料失敗!";
						echo "</font><br/>";
					}
				}
				if //3
				(
					($orderDate != "" && $verificationSheetId != "" && $supplierName != "" && $staffName != "") &&
					($commodityName3 != "" && $verificationSheetQuantity3 != "")
				) 
				{
					//$sql3 = "INSERT INTO `verificationsheet`(`orderDate`,`verificationSheetId`,`suppilerId`,`staffId`) VALUES('$orderDate','$verificationSheetId','$supplierName','$staffName')";
					$sql_3 = "INSERT INTO `verificationsheetdetails`(`verificationSheetId`,`commodityId`,`verificationSheetQuantity`) VALUES('$verificationSheetId','$commodityName3','$verificationSheetQuantity3')";
					if ( mysqli_query($link, $sql_3) ) // 執行SQL指令
					{
						echo "<font color=red>新增第三筆報銷商品資料成功!";
						echo "</font><br/>";
					}
					else
					{
						echo "<font color=red>新增第三筆報銷商品資料失敗!";
						echo "</font><br/>";
					}
				}
				if //4
				(
					($orderDate != "" && $verificationSheetId != "" && $supplierName != "" && $staffName != "") &&
					($commodityName4 != "" && $verificationSheetQuantity4 != "")
				) 
				{
					//$sql4 = "INSERT INTO `verificationsheet`(`orderDate`,`verificationSheetId`,`suppilerId`,`staffId`) VALUES('$orderDate','$verificationSheetId','$supplierName','$staffName')";
					$sql_4 = "INSERT INTO `verificationsheetdetails`(`verificationSheetId`,`commodityId`,`verificationSheetQuantity`) VALUES('$verificationSheetId','$commodityName4','$verificationSheetQuantity4')";
					if ( mysqli_query($link, $sql_4) ) // 執行SQL指令
					{
						echo "<font color=red>新增第四筆報銷商品資料成功!";
						echo "</font><br/>";
					}
					else
					{
						echo "<font color=red>新增第四筆報銷商品資料失敗!";
						echo "</font><br/>";
					}
				}
				if //5
				(
					($orderDate != "" && $verificationSheetId != "" && $supplierName != "" && $staffName != "") &&
					($commodityName5 != "" && $verificationSheetQuantity5 != "")
				) 
				{
					//$sql5 = "INSERT INTO `verificationsheet`(`orderDate`,`verificationSheetId`,`suppilerId`,`staffId`) VALUES('$orderDate','$verificationSheetId','$supplierName','$staffName')";
					$sql_5 = "INSERT INTO `verificationsheetdetails`(`verificationSheetId`,`commodityId`,`verificationSheetQuantity`) VALUES('$verificationSheetId','$commodityName5','$verificationSheetQuantity5')";
					if ( mysqli_query($link, $sql_5) ) // 執行SQL指令
					{
						echo "<font color=red>新增第五筆報銷商品資料成功!";
						echo "</font><br/>";
					}
					else
					{
						echo "<font color=red>新增第五筆報銷商品資料失敗!";
						echo "</font><br/>";
					}
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