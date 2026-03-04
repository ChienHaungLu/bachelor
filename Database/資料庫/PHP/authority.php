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
	<link rel="stylesheet" href="../CSS/authority.css">
	<link rel="stylesheet" href="../CSS/common.css">
	<title>管控權限</title>
</head>
<body>
	<header id = 'nav'>
    </header>
	<div id = "divAddNewStaff">
		<button id = "addNewStaff"><a href="addStaff.php" id = "addNewStaffA">新增人事資料</a></button>
	</div>
	<div id = "staffDiv">
		<div id="current" class = "staff">
			<div class = "staffTitle">在職</div>
			<div class = "staffList" id = "currentStaffList"></div>
		</div>
		<?php
		$records_per_page = 10;  // 每一頁顯示的記錄筆數
		if (isset($_GET["Pages"])) $pages = $_GET["Pages"];
		else                       $pages = 1;
		// 設定SQL查詢字串
		$sql = "SELECT staffId,staffName,positionName,account,password FROM staff INNER JOIN position ON staff.positionId = position.positionId Where positionStatus=1";

		// 執行SQL查詢
		$result = mysqli_query($link, $sql);
		$total_fields=mysqli_num_fields($result); // 取得欄位數
		$total_records=mysqli_num_rows($result);  // 取得記錄數
		$total_pages = ceil($total_records/$records_per_page); // 計算總頁數
		$offset = ($pages - 1)*$records_per_page; // 計算這一頁第1筆記錄的位置
		mysqli_data_seek($result, $offset); // 移到此記錄
		echo "在職人數: $total_records 人<br/>";
		echo "<table border=1><tr><td align='center' valign='middle'>員工ID</td>";
		echo "<td align='center' valign='middle'>姓名</td><td align='center' valign='middle' style='width:050px'>職位</td>";
		echo "<td align='center' valign='middle'>帳號</td><td align='center' valign='middle'>密碼</td></tr>";
		$j = 1;
		while ($rows = mysqli_fetch_array($result, MYSQLI_NUM) and $j <= $records_per_page) {
 			echo "<tr>";
 			for ( $i = 0; $i<= $total_fields-1; $i++ ){
				echo "<td align='center' valign='middle'>".$rows[$i]."</td>"; 
			}
			echo "<td style='width:035px' ><a href='staff.php?action=edit&id=";
			 	echo $rows[0]."&positionStatus=1&positionName=";echo $rows[2]."'><b>編輯</b></td>";
				echo "</tr>";   
	 		echo "</tr>";
 			$j++;
			
		}
		?>
		
		<td  colspan="6" align='right'>
	<?php
		if ( $pages > 1 )  // 顯示上一頁
   			echo "<a href='authority.php?Pages=".($pages-1).
        		"'>上一頁</a>| ";
		for ( $i = 1; $i <= $total_pages; $i++ )
   			if ($i != $pages)
     			echo "<a href=\"authority.php?Pages=".$i."\">".
          			$i."</a> ";
   			else
     			echo $i." ";
		if ( $pages < $total_pages )  // 顯示下一頁
   			echo "|<a href='authority.php?Pages=".($pages+1).
        		"'>下一頁</a> ";
		mysqli_free_result($result);  // 釋放佔用的記憶體
		
		?>
		
		</td>
			

		<?php echo "</table><br>" ?>

		<div id ="quit" class = "staff">
			<div class = "staffTitle">已離職</div>
			<div class = "staffList" id = "quitStaffList"></div>
			<div></div>
		</div>
			
		<?php
		$records_per_page = 10;  // 每一頁顯示的記錄筆數
		if (isset($_GET["Pages"])) $pages = $_GET["Pages"];
		else                       $pages = 1;
		// 設定SQL查詢字串
		$sql = "SELECT staffId,staffName,positionName,account,password FROM staff INNER JOIN position ON staff.positionId = position.positionId Where positionStatus=0";

		// 執行SQL查詢
		$result = mysqli_query($link, $sql);
		$total_fields=mysqli_num_fields($result); // 取得欄位數
		$total_records=mysqli_num_rows($result);  // 取得記錄數
		$total_pages = ceil($total_records/$records_per_page);
		echo "已離職人數: $total_records 人<br/>";
		echo "<table border=1><tr><td align='center' valign='middle'>員工ID</td>";
		echo "<td align='center' valign='middle'>姓名</td><td align='center' valign='middle' style='width:050px'>職位</td>";
		echo "<td align='center' valign='middle'>帳號</td><td align='center' valign='middle'>密碼</td></tr>";
		$j = 1;
		while ($rows = mysqli_fetch_array($result, MYSQLI_NUM)
	 			and $j <= $records_per_page) {
 			echo "<tr>";
 			for ( $i = 0; $i<= $total_fields-1; $i++ )
				echo "<td align='center' valign='middle'>".$rows[$i]."</td>";
 			echo "<td style='width:035px'><a href='staff.php?action=edit&id=";
				echo $rows[0]."&positionStatus=0&positionName=";echo $rows[2]."'><b>編輯</b></td>";
				echo "</tr>";   
	 		echo "</tr>";
 			$j++;
		}
	?>	
		<td  colspan="6" align='right'>
	<?php
		if ( $pages > 1 )  // 顯示上一頁
   			echo "<a href='authority.php?Pages=".($pages-1).
        		"'>上一頁</a>| ";
		for ( $i = 1; $i <= $total_pages; $i++ )
   			if ($i != $pages)
     			echo "<a href=\"authority.php?Pages=".$i."\">".
          			$i."</a> ";
   			else
     			echo $i." ";
		if ( $pages < $total_pages )  // 顯示下一頁
   			echo "|<a href='authority.php?Pages=".($pages+1).
        		"'>下一頁</a> ";
		mysqli_free_result($result);  // 釋放佔用的記憶體
		?>
	</div>
	<?php echo "</table><br>"; ?>
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