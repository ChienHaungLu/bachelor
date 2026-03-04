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
    <link rel="stylesheet" href="../CSS/staff.css">
    <title>個人資料</title>
</head>
<!-------------------------------------------------------------------------------------------------------------------------->
<!-------------------------------------------------------------------------------------------------------------------------->
<!-------------------------------------------------------------------------------------------------------------------------->

<body>
    <?php 
      $id = $_GET["id"];  // 取得URL參數的編號
      $action = $_GET["action"];  // 取得操作種類
      $positionStatus1 = $_GET["positionStatus"]; //取得職員狀態
      $positionName1 = $_GET["positionName"];
      if ($positionStatus1==1)
      {
        $positionStatus2="在職";
      } 
      if ($positionStatus1==0)
      {
        $positionStatus2="離職";
      } 

      if($positionName1=="總經理") {$positionName2="總經理";}
      if($positionName1=="銷售") {$positionName2="銷售";}
      if($positionName1=="會計") {$positionName2="會計";}
      if($positionName1=="倉管") {$positionName2="倉管";}
    ?>


    <header id = 'nav'></header>
    <?php
      if($positionStatus1==1) //在職
      {
         
    ?>
          <?php
          
          switch ($action) {
            case "update": // 更新操作    
              $staffID = $_POST["staffID"];
              $staffName = $_POST["staffName"];
              $staffPosition = $_POST["staffPosition"];
              $staffAccount = $_POST["staffAccount"];
              $staffPassword = $_POST["staffPassword"];
              $positionStatus = $_POST["positionStatus"];

              $sql = "UPDATE staff JOIN position ON staff.positionId = position.positionId 
                      SET  staffName = '$staffName' ,positionName = '$staffPosition', positionStatus='$positionStatus'
                      ,account = '$staffAccount' , password = '$staffPassword' 
                      WHERE staffId = $id";
              mysqli_query($link, $sql);  // 執行SQL指令
            
              header("Location: authority.php"); // 轉址
              break;
            
            case "edit":   // 編輯操作
              $sql = "SELECT * FROM staff JOIN position  ON  staff.positionId = position.positionId WHERE staffId = $id";
              $result = mysqli_query($link, $sql); // 執行SQL指令
              $row = mysqli_fetch_assoc($result); // 取回記錄
              $staffID = $row["staffId"];
              $staffName = $row["staffName"];
              $staffAccount = $row["account"];
              $staffPassword = $row["password"];
          // 顯示編輯表單
        ?>

        <div id = "introduction">  <!--網頁白色個資區塊開始 -->
          
        <!--表單部分 -->
        <form action="staff.php?action=update&id=<?php echo $id ?>" method="post">  <!-- id根據權限php綁定positionId -->
        
          <div class="everyIntroduction">代碼 <input type= "text" id="staffID" name="staffID" size="30" value="<?php echo $staffID?>" disabled required/><br/></div>
          <div class="everyIntroduction">狀態 <input type= "text" size="30" value="<?php echo $positionStatus2?>" disabled required/><br/></div>
          <div class="everyIntroduction">職位 <input type= "text" size="30" value="<?php echo $positionName1?>" disabled required/><br/></div>
          <div class="everyIntroduction">名稱 <input type= "text" id="staffName" name="staffName" size="30" value="<?php echo $staffName?>" required/><br/></div>
          <div class="everyIntroduction">帳號 <input type="text" id="staffAccount" name="staffAccount" size="30" value="<?php echo $staffAccount?>" readonly required/><br/></div>
          <div class="everyIntroduction">密碼 <input type="text" id="staffPassword" name="staffPassword" size="30" value="<?php echo $staffPassword?>" required/><br/></div>
          <div class="everyIntroduction">更改職位 
            <select name="staffPosition" id="staffPosition" >
                  
                  <option value=<?php echo $positionName2 ?>>請選擇</option>
                  <option value=總經理>總經理</option>
                  <option value=銷售>銷售</option>
                  <option value=會計>會計</option>
                  <option value=倉管>倉管 </option>
              
            </select></div>

            <div class="everyIntroduction">更改狀態 
            <select name="positionStatus" id="positionStatus" >

                      <?php $a=0 ?>
                      <option value=<?php echo $positionStatus1 ?>>請選擇</option>
                      <option value=1>在職</option>
                      <option value=<?php $a?>>離職</option>
        
                  
                  
              
            </select></div>
          
          
        </div> <!--網頁白色個資區塊結束-->

        <div class="form-check">
          
          <input id = "changeAuthorityButton" type= "submit" value="  更改權限  " /><a href="authority.php"></a>
            
        </form> <!--表單結束 -->
       
        <?php  
          break;
          }  //switch部分結束
        ?>

      </div>
    <?php
      } //在職
    ?>

<!-------------------------------------------------------------------------------------------------------------------------->
<!-------------------------------------------------------------------------------------------------------------------------->
<!-------------------------------------------------------------------------------------------------------------------------->

<?php
      if($positionStatus1==0)  //離職
      {
         
    ?>
          <?php
          
          switch ($action) {
            case "update": // 更新操作    
              $staffID = $_POST["staffID"];
              $staffName = $_POST["staffName"];
              $staffPosition = $_POST["staffPosition"];
              $staffAccount = $_POST["staffAccount"];
              $staffPassword = $_POST["staffPassword"];
              $positionStatus = $_POST["positionStatus"];

              $sql = "UPDATE staff JOIN position ON staff.positionId = position.positionId SET  staffName = '$staffName' ,positionName = '$staffPosition', positionStatus='$positionStatus',account = '$staffAccount' , password = '$staffPassword' WHERE staffId = $id";
              mysqli_query($link, $sql);  // 執行SQL指令
            
              header("Location: authority.php"); // 轉址
              break;

              /*------------------------------------------------------------------------------------------------------------------------------------------*/
              /*------------------------------------------------------------------------------------------------------------------------------------------*/
              /*------------------------------------------------------------------------------------------------------------------------------------------*/

            case "edit":   // 編輯操作
              $sql = "SELECT * FROM staff JOIN position  ON  staff.positionId = position.positionId WHERE staffId = $id";
            
              $result = mysqli_query($link, $sql); // 執行SQL指令
              $row = mysqli_fetch_assoc($result); // 取回記錄
              $staffID = $row["staffId"];
              $staffName = $row["staffName"];
              $staffAccount = $row["account"];
              $staffPassword = $row["password"];
          // 顯示編輯表單
        ?>
        <div id = "introduction">  <!--網頁白色個資區塊開始 -->
          
           <!--表單部分 -->
          <form action="staff.php?action=update&id=<?php echo $id ?>" method="post">  <!-- id根據權限php綁定positionId -->
          
            <div class="everyIntroduction">代碼 <input type= "text" id="staffID" name="staffID" size="30" value="<?php echo $staffID?>" disabled required/><br/></div>
            <div class="everyIntroduction">狀態 <input type= "text" size="30" value="<?php echo $positionStatus2?>" readonly  required/><br/></div>
            <div class="everyIntroduction">職位 <input type= "text" size="30" value="<?php echo $positionName1?>" readonly  required/><br/></div>
            <div class="everyIntroduction">名稱 <input type= "text" id="staffName" name="staffName" size="30" value="<?php echo $staffName?>" readonly required/><br/></div>
            <div class="everyIntroduction">帳號 <input type="text" id="staffAccount" name="staffAccount" size="30" value="<?php echo $staffAccount?>" readonly required/><br/></div>
            <div class="everyIntroduction">密碼 <input type="text" id="staffPassword" name="staffPassword" size="30" value="<?php echo $staffPassword?>" readonly required/><br/></div>
            <div class="everyIntroduction">更改職位 
              <select name="staffPosition" id="staffPosition" readonly unselectable>
                    <option value=<?php echo $positionName2 ?>></option> <!--拔掉其餘職位選項但要回傳目前的值到資料庫裡-->
              </select></div>

              <div class="everyIntroduction">更改狀態 
                <select name="positionStatus" id="positionStatus" >
                          <?php $a=0 ?>
                          <option value=<?php $a ?>>請選擇</option>
                          <option value=1>在職</option>
                          <option value=<?php $a?>>離職</option>
                </select>
              </div>
            
        </div> <!--網頁白色個資區塊結束-->
        

          <div class="form-check">
            <input id = "changeAuthorityButton" type= "submit" value="  更改權限  " /><a href="authority.php"></a>  
          
          </form> <!--表單結束 -->
       
        <?php  
          break;
          }  //switch部分結束
        ?>

      </div>
    <?php
      } //離職
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


<?php
  require_once("company_close.inc"); 
?>
</body>
</html>


