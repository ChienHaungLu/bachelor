nav();
function nav()
{
  sign = localStorage.getItem('sign');
  const head= document.getElementById('nav');
  head.innerHTML = ' ';
 
  head.innerHTML = ''+'<h2 id="name"class="ml1">' + '<span class="text-Wrapper">' + 
  '<a href="../PHP/purchase.php" ><span id="position">人事</span></a>'+'</span>' + '</h2>' + 
  '<nav>' + '<ul>' + '<li>'+'<a href="../PHP/authority.php">管控權限</a></li>'+'<li>'+'<a href="../HTML/signin.html">登出</a></li>'+ '</ul>' + '</nav>';
}

