<?php
    session_start();
    if(isset($_POST["btn_login"]))
    {
        require_once("company_open.inc");
        $account=$_POST["account"];
        $password=$_POST["password"];
        $sql = "SELECT * FROM `staff` WHERE account = '".$account."'";
        $result = mysqli_query($link, $sql);
		$data = mysqli_fetch_assoc($result);
        if($data["positionStatus"] == 1){
            $url1="../html/signInError.html";
            $url2="../html/signInBlank.html";
            $sql = "SELECT * FROM `staff` WHERE account = '";
            $sql.= $account."' AND password='".$password."'";
            $result = mysqli_query($link, $sql);//執行sql
            $total_records = mysqli_num_rows($result);//返回一個數值
            if($total_records>0){//0 false 1 true
                $_SESSION["account"] = $account;
                header("Location:../PHP/purchase.php");
                exit;
            }
            else if($account!=""&&$password!=""){                    
                echo "<script>window.location.href='$url1'</script>";
            }
            else{//如果使用者名稱或密碼有空
                echo "<script>window.location.href='$url2'</script>";                   
            }
        }
        else{
            echo "<script>alert('非本公司員工禁止使用本系統')</script>";
            echo "<script>window.location.href='../html/signIn.html'</script>";
        }
        require_once("company_close.inc");
    }
?>