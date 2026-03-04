--函式(Functions)的宣告語法：  Function 函式名稱 (輸入參數：資料型別) Return 輸出參數型別；

-- 函式(Functions)的主體內容語法如下：
-- 	Function 函式名稱 (輸入參數：資料型別) Return 輸出參數型別 IS
-- 		函式內的區域變數(Local Variable)宣告區
-- 	Begin
-- 		函式內的主體內容區
-- 		Return 輸出之參數名稱;
-- 	end 函式名稱;

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity function_call is
	port(A,B,C,D,E:in std_logic;
			Y1,Y2,Y3: out std_logic);
end function_call;

architecture behavior of function_call is

	function Fn1(F1,F2,F3,F4:std_logic) return std_logic is
		variable Temp:std_logic;
	begin
		Temp:=(F1 XOR F2) XOR (F3 XOR F4);
		return Temp;
	end function Fn1;
	
begin
	Y1<=Fn1(A,B,C,D) xor E; 
	Y2<=Fn1(A,B,C,D) xor E; 
	Y3<=Fn1(A,B,C,D) xor E; 
end behavior;