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
	<link rel="stylesheet" href="../CSS/modifyOrder.css">
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
            $(this).closest('.ticket').find('#total').text(temp);
        });
        $('.ticket').on( 'click','.item',function(){
            var item = $(".item").val();//+$(this).val();
            var commoditySet = $(".commoditySet").val();   //+$(this).val();
            var cost = $(".cost").val();
            var temp = item*commoditySet*cost;
            $(this).closest('.ticket').find('#total').text(temp);
        });
        $('.ticket').on( 'keyup blur change','.commoditySet',function(){
            var item = $(".item").val();//+$(this).val();
            var commoditySet = $(".commoditySet").val();   //+$(this).val();
            var cost = $(".cost").val();
            var temp = item*commoditySet*cost;
            $(this).closest('.ticket').find('#total').text(temp);
        });
        $('.ticket').on( 'click','.commoditySet',function(){
            var item = $(".item").val();//+$(this).val();
            var commoditySet = $(".commoditySet").val();   //+$(this).val();
            var cost = $(".cost").val();
            var temp = item*commoditySet*cost;
            $(this).closest('.ticket').find('#total').text(temp);
        });
        $('.ticket').on( 'keyup blur change','.cost',function(){
            var item = $(".item").val();//+$(this).val();
            var commoditySet = $(".commoditySet").val();   //+$(this).val();
            var cost = $(".cost").val();
            var temp = item*commoditySet*cost;
            $(this).closest('.ticket').find('#total').text(temp);
        });
        $('.ticket').on( 'click','.cost',function(){
            var item = $(".item").val();//+$(this).val();
            var commoditySet = $(".commoditySet").val();   //+$(this).val();
            var cost = $(".cost").val();
            var temp = item*commoditySet*cost;
            $(this).closest('.ticket').find('#total').text(temp);
        });
    });     
    </script>
	<title>修改訂單</title>
</head>
<body>
	<header id = 'nav'></header>
	<?php 
		$id = $_GET["id"];  // 取得URL參數的編號
		$productid = $_GET["productid"];
		$action = $_GET["action"];  // 取得操作種類

		switch ($action) {
			case "update": // 更新操作    
				$commodityName = $_POST["commodityName"];
				$commoditySet = $_POST["commoditySet"];
				$item = $_POST["item"];
				$cost = $_POST["cost"];
				$totalQuantity = $commoditySet * $item;
				$totalExpenses = $commoditySet * $item * $cost;

				$sql3 = "UPDATE commoditydetails 
							LEFT JOIN commodity ON commoditydetails.commodityId = commodity.commodityId
							SET commoditydetails.commodityId = '$commodityName', 
							item = '$item', 
							cost = '$cost', 
							totalQuantity = '$totalQuantity', 
							totalExpenses = '$totalExpenses'
							WHERE commoditydetails.purchaseOrderId = '$id'";

				mysqli_query($link, $sql3);  // 執行SQL指令
				header("Location: commodityDetails.php?id=$id"); // 轉址
			break;
			
			case "del":
				$sql = "DELETE FROM commoditydetails  WHERE commoditydetails.purchaseOrderId = $id AND commoditydetails.commodityId = $productid";
				mysqli_query($link, $sql); 
				header("Location: purchase.php"); // 轉址
			break;

			case "Del":
				$sql1 = "DELETE FROM commoditydetails  WHERE commoditydetails.purchaseOrderId = $id";
				mysqli_query($link, $sql1); 
				$sql2 = "DELETE FROM purchaseorder WHERE purchaseorder.purchaseOrderId = $id";
				mysqli_query($link, $sql2); 

				header("Location: purchase.php"); // 轉址
			break;

			case "edit":   // 編輯操作
				$sql = "SELECT * FROM purchaseorder JOIN commoditydetails  ON  purchaseorder.purchaseOrderId = commoditydetails.purchaseOrderId 
													JOIN supplier ON purchaseOrder.supplierId = supplier.supplierId  
													JOIN staff ON purchaseOrder.operator = staff.staffId 
													JOIN commodity ON commodityDetails.commodityId = commodity.commodityId  
													WHERE purchaseOrder.purchaseOrderId = $id AND commoditydetails.commodityId = $productid";
				
				$result = mysqli_query($link, $sql); // 執行SQL指令
				$row = mysqli_fetch_assoc($result); // 取回記錄
				$orderDate = $row["orderDate"];
				$purchaseOrderCode = $row["purchaseOrderId"];
				$supplierName = $row["supplierName"];
				$staffName = $row["staffName"];
				$commodityName = $row["commodityName"];
				$commoditySet = $row["commoditySet"];
				$item = $row["item"];
				$cost = $row["cost"];
				$totalExpenses = $row["totalExpenses"];
    		// 顯示編輯表單
			
    ?>
	<form action="modifyOrder.php?action=update&id=<?php echo $id ?>" method="post">
		<div id = "introduction" class="ticket">
			<div class="everyIntroduction">訂單編號: <input type="text"  name="purchaseOrderCode" id="purchaseOrderCode" value="<?php echo $purchaseOrderCode ?> " readonly></div>
			<div class="everyIntroduction">商品名稱: <select type="text" name="commodityName" id="commodityName">
				<?php 
				//=================================================================================
				echo "<option value>$commodityName</option>";
				$sql = "SELECT * FROM commodity"; //從company某個table選擇所有資料
				$result = mysqli_query($link,$sql);
				$i=0;
				while($row = mysqli_fetch_assoc($result)){
					$i++;
					$productname = $row['commodityName'];
					$commodityId = $row['commodityId'];
					echo "<option value=$commodityId>";
					echo $productname; //商品名稱
					echo "</option>";
				}
				//=================================================================================
				?>
			</select></div>
			<div class="everyIntroduction">入數:<input type="number" class="commoditySet" name="commoditySet" value="<?php echo $commoditySet ?>" disabled required/></div>
			<div class="everyIntroduction">件數:<input type="number" class="item" name="item" id="item" value="<?php echo $item ?>"/></div>
			<div class="everyIntroduction">單價:<input type="number" class="cost" name="cost" id="cost" value="<?php echo $cost ?>"/></div>
			<div class="everyIntroduction">小計:<span name="totalExpenses" id ="total" value="<?php echo $totalExpenses ?>" ></span></div>
		</div>
		<input id = "changeAuthorityButton" type="submit" style = "margin-left: 500px;margin-top: 50px;" value="修改訂單"/>
	</form>
	
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
break;
}  //switch部分結束
require_once("company_close.inc"); 
?>