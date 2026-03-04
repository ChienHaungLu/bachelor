-- phpMyAdmin SQL Dump
-- version 5.1.1
-- https://www.phpmyadmin.net/
--
-- 主機： 127.0.0.1
-- 產生時間： 2021-12-29 16:51:45
-- 伺服器版本： 10.4.21-MariaDB
-- PHP 版本： 8.0.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- 資料庫: `company`
--

-- --------------------------------------------------------

--
-- 資料表結構 `commodity`
--

CREATE TABLE `commodity` (
  `commodityId` int(11) NOT NULL,
  `commodityName` varchar(50) DEFAULT NULL,
  `supplierId` int(11) DEFAULT NULL,
  `commoditySet` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- 傾印資料表的資料 `commodity`
--

INSERT INTO `commodity` (`commodityId`, `commodityName`, `supplierId`, `commoditySet`) VALUES
(8000, '大號杯(36入)', 7000, 36),
(8001, '長方盤(24入)', 7000, 24),
(8002, '直口碗(72入)', 7000, 72),
(8003, '企口碗(72入)', 7001, 72),
(8004, '長方盤(48入)', 7001, 48),
(8005, '飯盤(48入)', 7001, 48),
(8006, '四角湯盤(48入)', 7002, 48),
(8007, '連把碗(48入)', 7002, 48),
(8008, '和尚碗(48入)', 7003, 48),
(8009, '反口碗(72入)', 7003, 72);

-- --------------------------------------------------------

--
-- 資料表結構 `commoditydetails`
--

CREATE TABLE `commoditydetails` (
  `commodityDetailsId` int(11) NOT NULL,
  `purchaseOrderId` int(11) DEFAULT NULL,
  `commodityId` int(11) DEFAULT NULL,
  `item` int(11) DEFAULT NULL,
  `cost` decimal(10,2) DEFAULT NULL,
  `totalQuantity` int(11) DEFAULT NULL,
  `totalExpenses` decimal(20,2) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- 傾印資料表的資料 `commoditydetails`
--

INSERT INTO `commoditydetails` (`commodityDetailsId`, `purchaseOrderId`, `commodityId`, `item`, `cost`, `totalQuantity`, `totalExpenses`) VALUES
(9000, 1000, 8000, 1, '13.00', 36, '468.00'),
(9001, 1001, 8001, 2, '18.00', 48, '864.00'),
(9002, 1002, 8002, 3, '30.00', 216, '6480.00'),
(9003, 1003, 8003, 1, '14.00', 72, '1008.00'),
(9004, 1004, 8004, 1, '19.00', 48, '912.00'),
(9005, 1005, 8005, 3, '12.00', 144, '1728.00'),
(9006, 1006, 8006, 4, '16.00', 192, '3072.00'),
(9007, 1007, 8007, 2, '25.00', 96, '2400.00'),
(9008, 1008, 8008, 1, '18.00', 48, '864.00'),
(9009, 1009, 8009, 1, '11.00', 72, '792.00');

-- --------------------------------------------------------

--
-- 資料表結構 `position`
--

CREATE TABLE `position` (
  `positionId` int(11) NOT NULL,
  `positionName` varchar(10) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- 傾印資料表的資料 `position`
--

INSERT INTO `position` (`positionId`, `positionName`) VALUES
(5000, '總經理'),
(5001, '銷售'),
(5002, '會計'),
(5003, '倉管');

-- --------------------------------------------------------

--
-- 資料表結構 `purchaseorder`
--

CREATE TABLE `purchaseorder` (
  `purchaseOrderId` int(11) NOT NULL,
  `orderDate` date DEFAULT NULL,
  `supplierId` int(11) DEFAULT NULL,
  `operator` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- 傾印資料表的資料 `purchaseorder`
--

INSERT INTO `purchaseorder` (`purchaseOrderId`, `orderDate`, `supplierId`, `operator`) VALUES
(1000, '2021-11-03', 7000, 4000),
(1001, '2021-10-12', 7000, 4001),
(1002, '2020-12-31', 7000, 4002),
(1003, '2021-11-23', 7001, 4003),
(1004, '2021-09-15', 7001, 4004),
(1005, '2021-08-31', 7001, 4005),
(1006, '2021-09-11', 7002, 4006),
(1007, '2021-11-14', 7002, 4007),
(1008, '2021-05-19', 7003, 4008),
(1009, '2021-07-16', 7003, 4009);

-- --------------------------------------------------------

--
-- 資料表結構 `staff`
--

CREATE TABLE `staff` (
  `staffId` int(11) NOT NULL,
  `staffName` varchar(50) DEFAULT NULL,
  `positionId` int(11) DEFAULT NULL,
  `account` varchar(20) DEFAULT NULL,
  `password` varchar(20) DEFAULT NULL,
  `positionStatus` bit(1) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- 傾印資料表的資料 `staff`
--

INSERT INTO `staff` (`staffId`, `staffName`, `positionId`, `account`, `password`, `positionStatus`) VALUES
(4000, '陳勳森', 5000, 'abcd4000', 'abcd4000', b'1'),
(4001, '謝裕民', 5001, 'abcd4001', 'abcd4001', b'1'),
(4002, '翁崇銘', 5002, 'abcd4002', 'abcd4002', b'1'),
(4003, '郭淑玲', 5003, 'abcd4003', 'abcd4003', b'1'),
(4004, '廖述宏', 5003, 'abcd4004', 'abcd4004', b'1'),
(4005, '黃清吉', 5003, 'abcd4005', 'abcd4005', b'1'),
(4006, '林慶文', 5003, 'abcd4006', 'abcd4006', b'1'),
(4007, '陳幼獅', 5001, 'abcd4007', 'abcd4007', b'0'),
(4008, '張國萬', 5002, 'abcd4008', 'abcd4008', b'0'),
(4009, '劉瑞復', 5003, 'abcd4009', 'abcd4009', b'0'),
(4011, '陳世棟', 5001, 'abcd4010', 'abcd4010', b'1'),
(4012, '林金源', 5003, 'abcd4011', 'abcd4011', b'1'),
(4020, '楊喜棠', 5003, 'abcd4012', 'abcd4012', b'1'),
(4021, '李青潭', 5002, 'abcd4013', 'abcd4013', b'1'),
(4023, '李進興', 5003, 'abcd4014', 'abcd4014', b'1'),
(4025, '蘇益慶', 5002, 'abcd4015', 'abcd4015', b'1'),
(4026, '張子信', 5001, 'abcd4016', 'abcd4016', b'1'),
(4027, '黃俊勝', 5000, 'abcd4017', 'abcd4017', b'0'),
(4028, '徐旭明', 5001, 'abcd4018', 'abcd4018', b'1'),
(4029, '林勝豐', 5002, 'abcd4019', 'abcd4019', b'1'),
(4030, '鄭榮勳', 5003, 'abcd4020', 'abcd4020', b'1');

-- --------------------------------------------------------

--
-- 資料表結構 `stock`
--

CREATE TABLE `stock` (
  `stockId` int(11) NOT NULL,
  `commodityId` int(11) DEFAULT NULL,
  `stockQuantity` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- 傾印資料表的資料 `stock`
--

INSERT INTO `stock` (`stockId`, `commodityId`, `stockQuantity`) VALUES
(6000, 8000, 524),
(6001, 8001, 763),
(6002, 8002, 1340),
(6003, 8003, 878),
(6004, 8004, 664),
(6005, 8005, 431),
(6006, 8006, 547),
(6007, 8007, 2731),
(6008, 8008, 446),
(6009, 8009, 643);

-- --------------------------------------------------------

--
-- 資料表結構 `supplier`
--

CREATE TABLE `supplier` (
  `supplierId` int(11) NOT NULL,
  `phoneNumber` varchar(20) DEFAULT NULL,
  `address` varchar(50) DEFAULT NULL,
  `supplierName` varchar(20) DEFAULT NULL,
  `leaderName` varchar(50) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- 傾印資料表的資料 `supplier`
--

INSERT INTO `supplier` (`supplierId`, `phoneNumber`, `address`, `supplierName`, `leaderName`) VALUES
(7000, '06-6548854', '台南市中西區樹林街二段33號', '惠亞瓷器股份有限公司', '高文彬'),
(7001, '06-7899552', '台南市東區大學路1號', '現代瓷器股份有限公司', '秦嘉鴻'),
(7002, '02-9985554', '新北市樹林鎮東興街1號', '新寶瓷器股份有限公司', '林棟材'),
(7003, '02-8499256', '新北市新店市寶橋路229號', '原帥瓷器股份有限公司', '李春淵');

-- --------------------------------------------------------

--
-- 資料表結構 `verificationsheet`
--

CREATE TABLE `verificationsheet` (
  `verificationSheetId` int(11) NOT NULL,
  `orderDate` date DEFAULT NULL,
  `suppilerId` int(11) DEFAULT NULL,
  `staffId` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- 傾印資料表的資料 `verificationsheet`
--

INSERT INTO `verificationsheet` (`verificationSheetId`, `orderDate`, `suppilerId`, `staffId`) VALUES
(3000, NULL, NULL, 4000),
(3001, NULL, NULL, 4001),
(3002, NULL, NULL, 4002),
(3003, NULL, NULL, 4003),
(3004, NULL, NULL, 4004),
(3005, NULL, NULL, 4005),
(3006, NULL, NULL, 4006),
(3007, NULL, NULL, 4007),
(3008, NULL, NULL, 4008),
(3009, NULL, NULL, 4009);

-- --------------------------------------------------------

--
-- 資料表結構 `verificationsheetdetails`
--

CREATE TABLE `verificationsheetdetails` (
  `verificationSheetDetailsId` int(11) NOT NULL,
  `verificationSheetId` int(11) DEFAULT NULL,
  `commodityId` int(11) DEFAULT NULL,
  `verificationSheetQuantity` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- 傾印資料表的資料 `verificationsheetdetails`
--

INSERT INTO `verificationsheetdetails` (`verificationSheetDetailsId`, `verificationSheetId`, `commodityId`, `verificationSheetQuantity`) VALUES
(2000, 3000, 8000, 11),
(2001, 3001, 8001, 15),
(2002, 3002, 8002, 6),
(2003, 3003, 8003, 8),
(2004, 3004, 8004, 7),
(2005, 3005, 8005, 7),
(2006, 3006, 8006, 5),
(2007, 3007, 8007, 9),
(2008, 3008, 8008, 1),
(2009, 3009, 8009, 0);

--
-- 已傾印資料表的索引
--

--
-- 資料表索引 `commodity`
--
ALTER TABLE `commodity`
  ADD PRIMARY KEY (`commodityId`),
  ADD KEY `fk_commodity_supplier_1` (`supplierId`);

--
-- 資料表索引 `commoditydetails`
--
ALTER TABLE `commoditydetails`
  ADD PRIMARY KEY (`commodityDetailsId`);

--
-- 資料表索引 `position`
--
ALTER TABLE `position`
  ADD PRIMARY KEY (`positionId`);

--
-- 資料表索引 `purchaseorder`
--
ALTER TABLE `purchaseorder`
  ADD PRIMARY KEY (`purchaseOrderId`),
  ADD KEY `fk_purchaseOrder_staff_1` (`operator`),
  ADD KEY `fk_purchaseOrder_supplier_1` (`supplierId`);

--
-- 資料表索引 `staff`
--
ALTER TABLE `staff`
  ADD PRIMARY KEY (`staffId`),
  ADD KEY `fk_staff_position_1` (`positionId`);

--
-- 資料表索引 `stock`
--
ALTER TABLE `stock`
  ADD PRIMARY KEY (`stockId`);

--
-- 資料表索引 `supplier`
--
ALTER TABLE `supplier`
  ADD PRIMARY KEY (`supplierId`);

--
-- 資料表索引 `verificationsheet`
--
ALTER TABLE `verificationsheet`
  ADD PRIMARY KEY (`verificationSheetId`);

--
-- 資料表索引 `verificationsheetdetails`
--
ALTER TABLE `verificationsheetdetails`
  ADD PRIMARY KEY (`verificationSheetDetailsId`);

--
-- 在傾印的資料表使用自動遞增(AUTO_INCREMENT)
--

--
-- 使用資料表自動遞增(AUTO_INCREMENT) `commodity`
--
ALTER TABLE `commodity`
  MODIFY `commodityId` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=8010;

--
-- 使用資料表自動遞增(AUTO_INCREMENT) `commoditydetails`
--
ALTER TABLE `commoditydetails`
  MODIFY `commodityDetailsId` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=9010;

--
-- 使用資料表自動遞增(AUTO_INCREMENT) `position`
--
ALTER TABLE `position`
  MODIFY `positionId` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=5011;

--
-- 使用資料表自動遞增(AUTO_INCREMENT) `staff`
--
ALTER TABLE `staff`
  MODIFY `staffId` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4031;

--
-- 使用資料表自動遞增(AUTO_INCREMENT) `stock`
--
ALTER TABLE `stock`
  MODIFY `stockId` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=6010;

--
-- 使用資料表自動遞增(AUTO_INCREMENT) `supplier`
--
ALTER TABLE `supplier`
  MODIFY `supplierId` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=7011;

--
-- 使用資料表自動遞增(AUTO_INCREMENT) `verificationsheet`
--
ALTER TABLE `verificationsheet`
  MODIFY `verificationSheetId` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3010;

--
-- 使用資料表自動遞增(AUTO_INCREMENT) `verificationsheetdetails`
--
ALTER TABLE `verificationsheetdetails`
  MODIFY `verificationSheetDetailsId` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2010;

--
-- 已傾印資料表的限制式
--

--
-- 資料表的限制式 `commodity`
--
ALTER TABLE `commodity`
  ADD CONSTRAINT `fk_commodity_supplier_1` FOREIGN KEY (`supplierId`) REFERENCES `supplier` (`supplierId`);

--
-- 資料表的限制式 `commoditydetails`
--
ALTER TABLE `commoditydetails`
  ADD CONSTRAINT `fk_commodityDetails_commodity_1` FOREIGN KEY (`commodityId`) REFERENCES `commodity` (`commodityId`),
  ADD CONSTRAINT `fk_commodityDetails_purchaseOrder_1` FOREIGN KEY (`purchaseOrderId`) REFERENCES `purchaseorder` (`purchaseOrderId`);

--
-- 資料表的限制式 `purchaseorder`
--
ALTER TABLE `purchaseorder`
  ADD CONSTRAINT `fk_purchaseOrder_staff_1` FOREIGN KEY (`operator`) REFERENCES `staff` (`staffId`),
  ADD CONSTRAINT `fk_purchaseOrder_supplier_1` FOREIGN KEY (`supplierId`) REFERENCES `supplier` (`supplierId`);

--
-- 資料表的限制式 `staff`
--
ALTER TABLE `staff`
  ADD CONSTRAINT `fk_staff_position_1` FOREIGN KEY (`positionId`) REFERENCES `position` (`positionId`);

--
-- 資料表的限制式 `stock`
--
ALTER TABLE `stock`
  ADD CONSTRAINT `fk_stock_commodity_1` FOREIGN KEY (`commodityId`) REFERENCES `commodity` (`commodityId`);

--
-- 資料表的限制式 `verificationsheetdetails`
--
ALTER TABLE `verificationsheetdetails`
  ADD CONSTRAINT `fk_verificationSheetDetails_commodity_1` FOREIGN KEY (`commodityId`) REFERENCES `commodity` (`commodityId`),
  ADD CONSTRAINT `fk_verificationSheetDetails_verificationSheet_1` FOREIGN KEY (`verificationSheetId`) REFERENCES `verificationsheet` (`verificationSheetId`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
