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
    <link rel="stylesheet" href="../CSS/addStaff.css">
    <title>新增人事資料</title>
</head>
<body>
  <?php
    // 取得欄位資料
    if ( isset($_POST["StaffName"]) && isset($_POST["positionName"]) && isset($_POST["StaffAccount"]) && isset($_POST["StaffPassword"]) ) {
      $staffName = $_POST["StaffName"];
      $positionName = $_POST["positionName"];
      $account = $_POST["StaffAccount"];
      $password = $_POST["StaffPassword"];
      $positionStatus = '1';

      $sql = "SELECT * FROM `staff` WHERE account = '".$account."'";
      $result = mysqli_query($link, $sql);
		  $data = mysqli_fetch_assoc($result);
      if ( $data >= 1 ) {
        echo "<script>alert('這個帳號已經存在了！請使用其他帳號註冊');history.go(-1);</script>";
        die;
      }
      elseif ($staffName != "" && $positionName != "" && $account != "" && $password != "") {
        $sql = "INSERT INTO `staff` (`staffName`,`positionId`,`account`,`password`,`positionStatus`) VALUES('$staffName','$positionName','$account','$password','$positionStatus')";
        if ( mysqli_query($link, $sql)) { // 執行SQL指令
          echo "<font color=red>新增聯絡資料成功!";
          echo "</font><br/>";
        }
        else{
          echo "<font color=red>新增聯絡資料失敗!";
          echo "</font><br/>";
        }
      }
    }
  ?>
    <header id = 'nav'></header>
    <form action="addStaff.php" method="post">
      <div id = "introduction">
        <div class="everyIntroduction">名稱:<input type ="text" name="StaffName"     id = "staffName"     ></div>
        <div class="everyIntroduction">職位:　<select type ="text" name="positionName" id = "positionName" >
          <?php 
	    		$sql = "SELECT * FROM position"; //從company某個table選擇所有資料
	    		$result = mysqli_query($link,$sql);
	    		$i=0;
	    		while($row = mysqli_fetch_assoc($result)){
	    			$i++;
            $positionId=$row['positionId'];
	  	  		echo "<option value=$positionId>";
	  	  		echo $row['positionName']; 
	  	  		echo "</option>";
  		  		}
	    		?>
        </select></div>
        <div class="everyIntroduction">帳號:<input type ="text" name="StaffAccount"  id = "staffAccount"  ></div>
        <div class="everyIntroduction">密碼:<input type ="text" name="StaffPassword" id = "staffPassword" ></div>

      </div>
      <input id = "changeAuthorityButton" type="submit" style = "margin-left: 500px;margin-top: 50px;"value="新增資料"/><a href="authority.php"></a>
    </form>
    <!--<button id = "changeAuthorityButton"><a href="authority.php">新增資料</a></button>-->
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