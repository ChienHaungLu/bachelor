nav();
function nav()
{
  sign = localStorage.getItem('sign');
  const head= document.getElementById('nav');
  head.innerHTML = ' ';
 
  head.innerHTML = ''+'<h2 id="name"class="ml1">' + '<span class="text-Wrapper">' + 
  '<a href="../PHP/purchase.php" ><span id="position">總經理</span></a>'+'</span>' + '</h2>' + 
  '<nav>' + '<ul>' + '<li><a href="../PHP/purchase.php">進貨資料</a></li><li>'+
  '<a href="../PHP/warehousing.php">庫存資料</a></li><li>'+'<a href="../PHP/authority.php">管控權限</a></li><li>'+
  '<a href="../PHP/addCompany.php">廠商管理</a></li><li>'+'<a href="../PHP/addProduct.php">商品管理</a></li><li>'+
  '<a href="../PHP/flaws.php">瑕疵分析</a></li><li>'+'<a href="../HTML/signIn.html">登出</a></li>'+ '</ul>' + '</nav>';
}

