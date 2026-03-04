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
	<script src="jquery-3.6.0.min.js"></script>
	<script>
    $(document).ready(function(){
        $('.ticket').on( 'keyup blur change','.item',function(){
            var item = $(".item").val();//+$(this).val();
            var commoditySet = $(".commoditySet").val();   //+$(this).val();
            var cost = $(".cost").val();
            var temp = item*commoditySet*cost;
            $(this).closest('.ticket').find('#totalExpenses').text(temp);
        });
        $('.ticket').on( 'click','.item',function(){
            var item = $(".item").val();//+$(this).val();
            var commoditySet = $(".commoditySet").val();   //+$(this).val();
            var cost = $(".cost").val();
            var temp = item*commoditySet*cost;
            $(this).closest('.ticket').find('#totalExpenses').text(temp);
        });
        $('.ticket').on( 'keyup blur change','.commoditySet',function(){
            var item = $(".item").val();//+$(this).val();
            var commoditySet = $(".commoditySet").val();   //+$(this).val();
            var cost = $(".cost").val();
            var temp = item*commoditySet*cost;
            $(this).closest('.ticket').find('#totalExpenses').text(temp);
        });
        $('.ticket').on( 'click','.commoditySet',function(){
            var item = $(".item").val();//+$(this).val();
            var commoditySet = $(".commoditySet").val();   //+$(this).val();
            var cost = $(".cost").val();
            var temp = item*commoditySet*cost;
            $(this).closest('.ticket').find('#totalExpenses').text(temp);
        });
        $('.ticket').on( 'keyup blur change','.cost',function(){
            var item = $(".item").val();//+$(this).val();
            var commoditySet = $(".commoditySet").val();   //+$(this).val();
            var cost = $(".cost").val();
            var temp = item*commoditySet*cost;
            $(this).closest('.ticket').find('#totalExpenses').text(temp);
        });
        $('.ticket').on( 'click','.cost',function(){
            var item = $(".item").val();//+$(this).val();
            var commoditySet = $(".commoditySet").val();   //+$(this).val();
            var cost = $(".cost").val();
            var temp = item*commoditySet*cost;
            $(this).closest('.ticket').find('#totalExpenses').text(temp);
        });
    });     
    </script>
	<title>新增訂單</title>
</head>
<body>
	<header id = 'nav'></header>
	<form method="post" action="addOrder.php" >
		<div id = "information" class="inform" class="ticket">
			<div>日期:<input type="date"  name="orderDate0"         id="orderDate"></div>
			<div>訂單編號:<input type="text"  name="purchaseOrderCode0" id="purchaseOrderCode"></div>
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

	<form method="post" action="addOrder.php" >
		<div id = "information"  class = "inform" class="ticket"  style="border-bottom-left-radius:0px;border-bottom-right-radius:0px;">
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
			<div>訂單編號:<input type="text"  name="purchaseOrderCode" id="purchaseOrderCode" value = <?php echo $b ?> readonly required></div>
			<div>廠商: <select type="text" name="supplierName" id="supplierName" >
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
			<div style = "width: 200px;">製單人員: <select type="text" name="staffName" id="staffName" >
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
				<tr><td>商品名稱:</td><td>件數</td><td>單價</td><td></td></tr>
				<tr><!-- ==================================================第一筆商品明細====================================================== -->
				<td><div><select type="text" name="commodityName" id="commodityName">
					<?php 
					echo "<option value>請選擇</option>";
					$sql = "SELECT * FROM commodity WHERE supplierId = $c"; //從company某個table選擇所有資料
					$result = mysqli_query($link,$sql);
					$i=0;
					while($row = mysqli_fetch_assoc($result)){
						$i++;
						$commodityId=$row['commodityId'];
						$commoditySet=$row['commoditySet'];
						echo "<option value=$commodityId>";
						echo $row['commodityName']; //商品名稱
						echo "</option>";
					}
					?>
				</select></div></td>
				<td><div><input type="number" class="item" name="item" value="0"/></div></td>
				<td><div><input type="number" class="cost" name="cost" value="0"/></div></td>
				<td><div><input type="hidden" class="commoditySet" name="commoditySet" value="0"/></div></td>
				<!--<td><div><span name="totalExpenses" id ="totalExpenses" value="0">0</span></div></td>-->
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
						$commoditySet=$row['commoditySet'];
						echo "<option value=$commodityId>";
						echo $row['commodityName']; //商品名稱
						echo "</option>";
					}
					?>
				</select></div></td>
				<td><div><input type="number" class="item" name="item2" value="0"/></div></td>
				<td><div><input type="number" class="cost" name="cost2" value="0"/></div></td>
				<td><div><input type="hidden" class="commoditySet" name="commoditySet2" value="0"/></div></td>
				<!--<td><div><span name="totalExpenses" id ="totalExpenses" value="0">0</span></div></td>-->
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
						$commoditySet=$row['commoditySet'];
						echo "<option value=$commodityId>";
						echo $row['commodityName']; //商品名稱
						echo "</option>";
					}
					?>
				</select></div></td>
				<td><div><input type="number" class="item" name="item3" value="0"/></div></td>
				<td><div><input type="number" class="cost" name="cost3" value="0"/></div></td>
				<td><div><input type="hidden" class="commoditySet" name="commoditySet3" value="0"/></div></td>
				<!--<td><div><span name="totalExpenses" id ="totalExpenses" value="0">0</span></div></td>-->
				</tr><tr><!-- ==================================================第四筆商品明細====================================================== -->
				<td><div><select type="text" name="commodityName4" id="commodityName">
					<?php 
					echo "<option value>請選擇</option>";
					$sql = "SELECT * FROM commodity WHERE supplierId = $c"; //從company某個table選擇所有資料
					$result = mysqli_query($link,$sql);
					$i=0;
					while($row = mysqli_fetch_assoc($result)){
						$i++;
						$commodityId=$row['commodityId'];
						$commoditySet=$row['commoditySet'];
						echo "<option value=$commodityId>";
						echo $row['commodityName']; //商品名稱
						echo "</option>";
					}
					?>
				</select></div></td>
				<td><div><input type="number" class="item" name="item4" value="0"/></div></td>
				<td><div><input type="number" class="cost" name="cost4" value="0"/></div></td>
				<td><div><input type="hidden" class="commoditySet" name="commoditySet4" value="0"/></div></td>
				<!--<td><div><span name="totalExpenses" id ="totalExpenses" value="0">0</span></div></td>-->
				</tr><tr><!-- ==================================================第五筆商品明細====================================================== -->
				<td><div><select type="text" name="commodityName5" id="commodityName">
					<?php 
					echo "<option value>請選擇</option>";
					$sql = "SELECT * FROM commodity WHERE supplierId = $c"; //從company某個table選擇所有資料
					$result = mysqli_query($link,$sql);
					$i=0;
					while($row = mysqli_fetch_assoc($result)){
						$i++;
						$commodityId=$row['commodityId'];
						$commoditySet=$row['commoditySet'];
						echo "<option value=$commodityId>";
						echo $row['commodityName']; //商品名稱
						echo "</option>";
					}
					?>
				</select></div></td>
				<td><div><input type="number" class="item" name="item5" value="0"/></div></td>
				<td><div><input type="number" class="cost" name="cost5" value="0"/></div></td>
				<td><div><input type="hidden" class="commoditySet" name="commoditySet5" value="0"/></div></td>
				<!--<td><div><span name="totalExpenses" id ="totalExpenses" value="0">0</span></div></td>-->
				</tr>
			</table>
		<?php 
			}
		}
		?>
		</div>
	<input id = "changeAuthorityButton" type="submit" name="submitButton1" style = "float: right;margin-right: 200px;margin-top: 20px;"value="新增訂單"/>
	</form>

	<?php 
		if(isset($_POST["submitButton1"]))
		{
			if
			(
				isset($_POST["orderDate"]) && isset($_POST["purchaseOrderCode"]) && isset($_POST["supplierName"]) && isset($_POST["staffName"]) && 
				(
					isset($_POST["commodityName"]) && isset($_POST["commoditySet"]) && isset($_POST["item"]) && isset($_POST["cost"]) ||
					isset($_POST["commodityName2"]) && isset($_POST["commoditySet2"]) && isset($_POST["item2"]) && isset($_POST["cost2"]) ||
					isset($_POST["commodityName3"]) && isset($_POST["commoditySet3"]) && isset($_POST["item3"]) && isset($_POST["cost3"]) ||
					isset($_POST["commodityName4"]) && isset($_POST["commoditySet4"]) && isset($_POST["item4"]) && isset($_POST["cost4"]) ||
					isset($_POST["commodityName5"]) && isset($_POST["commoditySet5"]) && isset($_POST["item5"]) && isset($_POST["cost5"]) 
				)
			)
			{
				$orderDate = $_POST["orderDate"];
				$purchaseOrderCode = $_POST["purchaseOrderCode"];
				$supplierName = $_POST["supplierName"];
				$staffName = $_POST["staffName"];

				$commodityName = $_POST["commodityName"];
				if($commodityName != ""){
				$sql11 = "SELECT * FROM commodity WHERE commodityId = '$commodityName'";
				$result11 = mysqli_query($link,$sql11);
				$data11 = mysqli_fetch_assoc($result11);
				$commoditySet = $data11["commoditySet"];
				$item = $_POST["item"];
				$cost = $_POST["cost"];
				$totalExpenses = $commoditySet * $item * $cost;
				$totalQuantity = $commoditySet * $item;}

				$commodityName2 = $_POST["commodityName2"];
				if($commodityName2 != ""){
				$sql22 = "SELECT * FROM commodity WHERE commodityId = '$commodityName2'";
				$result2 = mysqli_query($link,$sql22);
				$data2 = mysqli_fetch_assoc($result2);
				$commoditySet2 = $data2["commoditySet"];
				$item2 = $_POST["item2"];
				$cost2 = $_POST["cost2"];
				$totalExpenses2 = $commoditySet2 * $item2 * $cost2;
				$totalQuantity2 = $commoditySet2 * $item2;}

				$commodityName3 = $_POST["commodityName3"];
				if($commodityName3 != ""){
				$sql33 = "SELECT * FROM commodity WHERE commodityId = '$commodityName3'";
				$result3 = mysqli_query($link,$sql33);
				$data3 = mysqli_fetch_assoc($result3);
				$commoditySet3 = $data3["commoditySet"];
				$item3 = $_POST["item3"];
				$cost3 = $_POST["cost3"];
				$totalExpenses3 = $commoditySet3 * $item3 * $cost3;
				$totalQuantity3 = $commoditySet3 * $item3;}

				$commodityName4 = $_POST["commodityName4"];
				if($commodityName4 != ""){
				$sql44 = "SELECT * FROM commodity WHERE commodityId = '$commodityName4'";
				$result4 = mysqli_query($link,$sql44);
				$data4 = mysqli_fetch_assoc($result4);
				$commoditySet4 = $data4["commoditySet"];
				$item4 = $_POST["item4"];
				$cost4 = $_POST["cost4"];
				$totalExpenses4 = $commoditySet4 * $item4 * $cost4;
				$totalQuantity4 = $commoditySet4 * $item4;}

				$commodityName5 = $_POST["commodityName5"];
				if($commodityName5 != ""){
				$sql55 = "SELECT * FROM commodity WHERE commodityId = '$commodityName5'";
				$result5 = mysqli_query($link,$sql55);
				$data5 = mysqli_fetch_assoc($result5);
				$commoditySet5 = $data5["commoditySet"];
				$item5 = $_POST["item5"];
				$cost5 = $_POST["cost5"];
				$totalExpenses5 = $commoditySet5 * $item5 * $cost5;
				$totalQuantity5 = $commoditySet5 * $item5;}
				
				if //廠商
				(
					($orderDate != "" && $purchaseOrderCode != "" && $supplierName != "" && $staffName != "") &&
					(
						($commodityName != "" && $item != "" && $cost != "" && $totalQuantity != "" && $totalExpenses != "") ||
						($commodityName2 != "" && $item2 != "" && $cost2 != "" && $totalQuantity2 != "" && $totalExpenses2 != "") ||
						($commodityName3 != "" && $item3 != "" && $cost3 != "" && $totalQuantity3 != "" && $totalExpenses3 != "") ||
						($commodityName4 != "" && $item4 != "" && $cost4 != "" && $totalQuantity4 != "" && $totalExpenses4 != "") ||
						($commodityName5 != "" && $item5 != "" && $cost5 != "" && $totalQuantity5 != "" && $totalExpenses5 != "")
					)
				) 
				{
					$sql = "INSERT INTO `purchaseorder`(`orderDate`,`purchaseOrderId`,`supplierId`,`operator`) 
					VALUES('$orderDate','$purchaseOrderCode','$supplierName','$staffName')";
					
					if ( mysqli_query($link, $sql) ) { // 執行SQL指令
						echo "<font color=red>新增廠商資料成功!";
						echo "</font><br/>";
					}
					else
					{
						echo "<font color=red>新增廠商資料失敗!";
						echo "</font><br/>";
					}
				}
				else
				{
					echo "<font color=red>未輸入訂單產品資料!";
					echo "</font><br/>";
				}
				if //1
				(
					($orderDate != "" && $purchaseOrderCode != "" && $supplierName != "" && $staffName != "") &&
					($commodityName != "" && $item != "" && $cost != "" && $totalQuantity != "" && $totalExpenses != "")
				) 
				{
					//$sql11 = "INSERT INTO `purchaseorder`(`orderDate`,`purchaseOrderId`,`supplierId`,`operator`) VALUES('$orderDate','$purchaseOrderCode','$supplierName','$staffName')";
					$sql1 = "INSERT INTO `commoditydetails`(`purchaseOrderId`,`commodityId`,`item`,`cost`,`totalQuantity`,`totalExpenses`) VALUES('$purchaseOrderCode','$commodityName','$item','$cost','$totalQuantity','$totalExpenses')";
					if (mysqli_query($link, $sql1)) { // 執行SQL指令
						echo "<font color=red>新增第一筆訂單商品資料成功!";
						echo "</font><br/>";
					}
					else
					{
						echo "<font color=red>新增第一筆訂單商品資料失敗!";
						echo "</font><br/>";
					}
				}
				if //2
				(
					($orderDate != "" && $purchaseOrderCode != "" && $supplierName != "" && $staffName != "") &&
					($commodityName2 != "" && $item2 != "" && $cost2 != "" && $totalQuantity2 != "" && $totalExpenses2 != "")
				) 
				{
					//$sql22 = "INSERT INTO `purchaseorder`(`orderDate`,`purchaseOrderId`,`supplierId`,`operator`) VALUES('$orderDate','$purchaseOrderCode','$supplierName','$staffName')";
					$sql2 = "INSERT INTO `commoditydetails`(`purchaseOrderId`,`commodityId`,`item`,`cost`,`totalQuantity`,`totalExpenses`) VALUES('$purchaseOrderCode','$commodityName2','$item2','$cost2','$totalQuantity2','$totalExpenses2')";
					if (mysqli_query($link, $sql2)) { // 執行SQL指令
						echo "<font color=red>新增第二筆訂單商品資料成功!";
						echo "</font><br/>";
					}
					else
					{
						echo "<font color=red>新增第二筆訂單商品資料失敗!";
						echo "</font><br/>";
					}
				}
				if //3
				(
					($orderDate != "" && $purchaseOrderCode != "" && $supplierName != "" && $staffName != "") &&
					($commodityName3 != "" && $item3 != "" && $cost3 != "" && $totalQuantity3 != "" && $totalExpenses3 != "")
				) 
				{
					//$sql22 = "INSERT INTO `purchaseorder`(`orderDate`,`purchaseOrderId`,`supplierId`,`operator`) VALUES('$orderDate','$purchaseOrderCode','$supplierName','$staffName')";
					$sql3 = "INSERT INTO `commoditydetails`(`purchaseOrderId`,`commodityId`,`item`,`cost`,`totalQuantity`,`totalExpenses`) VALUES('$purchaseOrderCode','$commodityName3','$item3','$cost3','$totalQuantity3','$totalExpenses3')";
					if (mysqli_query($link, $sql3)) { // 執行SQL指令
						echo "<font color=red>新增第三筆訂單商品資料成功!";
						echo "</font><br/>";
					}
					else
					{
						echo "<font color=red>新增第三筆訂單商品資料失敗!";
						echo "</font><br/>";
					}
				}
				if //4
				(
					($orderDate != "" && $purchaseOrderCode != "" && $supplierName != "" && $staffName != "") &&
					($commodityName4 != "" && $item4 != "" && $cost4 != "" && $totalQuantity4 != "" && $totalExpenses4 != "")
				) 
				{
					//$sql22 = "INSERT INTO `purchaseorder`(`orderDate`,`purchaseOrderId`,`supplierId`,`operator`) VALUES('$orderDate','$purchaseOrderCode','$supplierName','$staffName')";
					$sql4 = "INSERT INTO `commoditydetails`(`purchaseOrderId`,`commodityId`,`item`,`cost`,`totalQuantity`,`totalExpenses`) VALUES('$purchaseOrderCode','$commodityName4','$item4','$cost4','$totalQuantity4','$totalExpenses4')";
					if (mysqli_query($link, $sql4)) { // 執行SQL指令
						echo "<font color=red>新增第四筆訂單商品資料成功!";
						echo "</font><br/>";
					}
					else
					{
						echo "<font color=red>新增第四筆訂單商品資料失敗!";
						echo "</font><br/>";
					}
				}
				if //5
				(
					($orderDate != "" && $purchaseOrderCode != "" && $supplierName != "" && $staffName != "") &&
					($commodityName5 != "" && $item5 != "" && $cost5 != "" && $totalQuantity5 != "" && $totalExpenses5 != "")
				) 
				{
					//$sql22 = "INSERT INTO `purchaseorder`(`orderDate`,`purchaseOrderId`,`supplierId`,`operator`) VALUES('$orderDate','$purchaseOrderCode','$supplierName','$staffName')";
					$sql5 = "INSERT INTO `commoditydetails`(`purchaseOrderId`,`commodityId`,`item`,`cost`,`totalQuantity`,`totalExpenses`) VALUES('$purchaseOrderCode','$commodityName5','$item5','$cost5','$totalQuantity5','$totalExpenses5')";
					if (mysqli_query($link, $sql5)) { // 執行SQL指令
						echo "<font color=red>新增第五筆訂單商品資料成功!";
						echo "</font><br/>";
					}
					else
					{
						echo "<font color=red>新增第五筆訂單商品資料失敗!";
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