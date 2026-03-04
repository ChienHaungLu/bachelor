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
    <title>管理瑕疵</title>
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
				$verificationSheetQuantity = $_POST["verificationSheetQuantity"];

				$sql3 = "UPDATE verificationSheetdetails
						SET verificationsheetdetails.commodityId = '$commodityName', verificationSheetdetails.verificationSheetQuantity = '$verificationSheetQuantity'
						WHERE verificationSheetdetails.verificationSheetId = $id AND verificationSheetdetails.commodityId = $productid";
				mysqli_query($link, $sql3);  // 執行SQL指令
				header("Location: flawsDetails.php?id=$id"); // 轉址
			break;
			
			case "del":
				$sql = "DELETE FROM verificationSheetdetails  
						WHERE verificationSheetdetails.verificationSheetId = $id AND verificationSheetdetails.commodityId = $productid";
				mysqli_query($link, $sql); 
				header("Location: flaws.php"); // 轉址
			break;

			case "Del":
				$sql1 = "DELETE FROM verificationsheetdetails  WHERE verificationsheetdetails.verificationSheetId = $id";
				mysqli_query($link, $sql1); 
				$sql2 = "DELETE FROM verificationsheet WHERE verificationsheet.verificationSheetId = $id";
				mysqli_query($link, $sql2); 
	
				header("Location: flaws.php"); // 轉址
			break;

			case "edit":   // 編輯操作
				$sql = "SELECT * FROM verificationsheet 
						JOIN verificationSheetdetails  ON  verificationsheet.verificationSheetId = verificationSheetdetails.verificationSheetId 
						JOIN supplier ON verificationsheet.suppilerId = supplier.supplierId  
						JOIN staff ON verificationsheet.staffId = staff.staffId 
						JOIN commodity ON verificationSheetdetails.commodityId = commodity.commodityId  
						WHERE verificationsheet.verificationSheetId = $id AND verificationSheetdetails.commodityId = $productid";
				
				$result = mysqli_query($link, $sql); // 執行SQL指令
				$row = mysqli_fetch_assoc($result); // 取回記錄
				$orderDate = $row["orderDate"];
				$verificationSheetId = $row["verificationSheetId"];
				$commodityName = $row["commodityName"];
				$verificationSheetQuantity = $row["verificationSheetQuantity"];
    		// 顯示編輯表單
    ?>

	<form action="modifyflaws.php?action=update&id=<?php echo $id ?>" method="post">
		<div id = "introduction" class="ticket">
			<div class="everyIntroduction">報銷單編號 <input type="text"  name="verificationSheetId" id="verificationSheetId" value="<?php echo $verificationSheetId ?> " readonly></div>
			<div class="everyIntroduction">商品名稱:<select type="text" name="commodityName" id="commodityName">
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
			<div class="everyIntroduction">入數:<input type="number" class="verificationSheetQuantity" name="verificationSheetQuantity" value="<?php echo $verificationSheetQuantity ?>" required/></div>
		</div>
		<input id = "changeAuthorityButton" type="submit" style = "margin-left: 500px;margin-top: 50px;"value="修改訂單" >
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