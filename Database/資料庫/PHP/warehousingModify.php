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
	<title>庫存資料修改</title>
</head>
<body>
	<?php 
		$id = $_GET["id"];  // 取得URL參數的編號
		$action = $_GET["action"];  // 取得操作種類
	?>
	<header id = 'nav'></header>
	<?php
      
      switch ($action) {
        case "update": // 更新操作    
			$productID = $_POST["productID"];
			$productName = $_POST["productName"];
			$remainder = $_POST["remainder"];
			$sql = "UPDATE commodity LEFT JOIN stock ON  commodity.commodityId = stock.commodityId SET  commodityName = '$productName' ,stockQuantity = '$remainder' WHERE commodity.commodityId = $id";
			mysqli_query($link, $sql);  // 執行SQL指令

        	header("Location: warehousing.php"); // 轉址
		break;
        

        case "edit":   // 編輯操作
          // Please insert code here. hint:sql
		  $sql = "SELECT * FROM commodity  JOIN stock  ON  stock.commodityId = commodity.commodityId WHERE commodity.commodityId = $id";
		  $result = mysqli_query($link, $sql); // 執行SQL指令
          $row = mysqli_fetch_assoc($result); // 取回記錄
		  $productID = $row["commodityId"];
          $productName = $row["commodityName"];
          $remainder = $row["stockQuantity"];
      // 顯示編輯表單
    ?>

	<form action="warehousingModify.php?action=update&id=<?php echo $id ?>" method="post">
		<table id = "warehousingTable">
			<tr id = "title">
				<th>商品編號</th>
				<th>商品名稱</th>
				<th>剩餘數量</th>
				<tr>
					<th><input type= "text" readonly="readonly" id="productID" name="productID" size="7" value="<?php echo $productID ?>" required/></th>
					<th><input type= "text" readonly="readonly" id="productName" name="productName" size="20" value="<?php echo $productName  ?>" required/></th>
					<th><input type= "text"  id="remainder" name="remainder" size="7" value="<?php echo $remainder ?>" required/></th>
				<tr>

			
			</tr>
		</table>
		
		<input id = "modifyButton" type= "submit"  value="  確認修改  " /><a href="warehousing.php"></a>
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