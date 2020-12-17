USE E_Market
GO

SELECT OrderInfo.OrderId,UserInfo.UserName,OrderInfo.Amount,OrderInfo.CommodityId
FROM OrderInfo,UserInfo
WHERE OrderInfo.UserId=UserInfo.UserId


SELECT COUNT(*) FROM UserInfo
SELECT COUNT(*) FROM OrderInfo


--三表连接

SELECT O.OrderId,U.UserName,O.Amount,C.CommodityName
FROM OrderInfo AS 0,UserInfo AS U, CommodityInfo AS C
WHERE O.UserId=U.UserId AND C.CommodityId=O.CommodityId



SELECT OrderId,UserName,O.Amount,CommodityName 
FROM UserInfo AS U
INNER JOIN OrderInfo AS O ON U.UserId=0.UserId
INNER JOIN CommodityInfo AS C ON O.CommodityId=C.CommodityId
WHERE U.UserName='赵可以'





SELECT SortName AS 商品类别,Amount AS 库存量,CommodityName AS 商品名称
FROM CommoditySort
LEFT JOIN CommodityInfo
ON CommoditySort.SortId=CommodityInfo.SortId


SELECT CommodityName AS 商品名称, OrderId AS 订单号
FROM OrderInfo 
RIGHT JOIN CommodityInfo
ON OrderInfo.CommodityId=CommodityInfo.CommodityId


SELECT S.SortName AS 类别名称,Amount AS 库存量
FROM CommoditySort AS S
LEFT JOIN CommodityInfo AS C
ON S.SortId=C.SortId

SELECT S.SortName AS 类别名称,Amount AS 库存量
FROM CommodityInfo AS C
RIGHT JOIN CommoditySort AS S
ON S.SortId=C.SortId


SELECT UserId AS 用户编号,UserName AS 用户姓名, UserAddress AS 地址 
FROM UserInfo 

UNION

SELECT PayWay AS 付款方式, UserId AS 下单用户号,CONVERT(varchar(10),OrderTime) AS 下单时间
FROM OrderInfo

UNION ALL

SELECT UserId AS 用户编号,UserName AS 用户姓名, UserAddress AS 地址 
FROM UserInfo 
ORDER BY UserId DESC

-------------------------------------

SELECT UserId AS 用户编号,UserName AS 用户姓名, UserAddress AS 地址 
FROM UserInfo 

UNION

SELECT PayWay AS 付款方式, UserId AS 下单用户号,CONVERT(varchar(10),OrderTime) AS 下单时间
FROM OrderInfo




SELECT UserInfo.UserId AS 用户编号,UserName AS 用户姓名, UserAddress AS 地址 ,
       PayWay AS 付款方式,CONVERT(varchar(10),OrderTime) AS 下单时间
FROM UserInfo,OrderInfo

WHERE UserInfo.UserId=OrderInfo.UserId


SELECT * FROM CommoditySort WHERE SortName='手机数码'

SELECT * FROM CommodityInfo WHERE SortId= 
(
SELECT SortId FROM CommoditySort WHERE SortName='手机数码'
)





SELECT * FROM CommodityInfo AS C
INNER JOIN OrderInfo AS O ON C.CommodityId=O.CommodityId
INNER JOIN UserInfo AS U ON O.UserId=U.UserId
WHERE C.CommodityName='苹果Iphone6'



SELECT CommodityId FROM CommoddityInfo 
WHERE CommodityName='苹果Iphone6'



SELECT UserId FROM OrderInfo WHERE CommodityId=
(
SELECT CommodityId FROM CommoddityInfo 
WHERE CommodityName='苹果Iphone6'
)


SELECT UserName AS 用户名,UserAddress AS 用户地址 FROM UserInfo WHERE UserId=
(
	SELECT UserId FROM OrderInfo WHERE CommodityId=
	(
		SELECT CommodityId FROM CommoddityInfo 
		WHERE CommodityName='苹果Iphone6'
	)
)





--IN NOT IN

SELECT CommodityId FROM CommodityInfo WHERE CommodityName='宝马小帅哥'

SELECT UserId FROM OrderInfo WHERE CommodityId=
(
	SELECT CommodityId FROM CommodityInfo WHERE CommodityName='宝马小帅哥'
)



SELECT * FROM UserInfo WHERE UserId IN
(
	SELECT UserId FROM OrderInfo WHERE CommodityId=
	(
		SELECT CommodityId FROM CommodityInfo WHERE CommodityName='宝马小帅哥'
	)
)


SELECT * FROM UserInfo WHERE UserId NOT IN
(
	SELECT DISTINCT UserId FROM OrderInfo
)



--WRONG	
SELECT * FROM UserInfo AS U
INNERE JOIN OrderInfo AS O
ON U.UserId <>O.UserId




-------------------------------
SELECT SortId FROM CommoditySort WHERE SortName='手机数码'





SELECT CommodityId FROM CommodityInfo WHERE SortId=
(
	SELECT SortId FROM CommoditySort WHERE SortName='手机数码'
)









IF EXISTS(SELECT * FROM OrderInfo WHERE CommodityId IN
(
	SELECT CommodityId FROM CommodityInfo WHERE SortId=
	(
		SELECT SortId FROM CommoditySort WHERE SortName='手机数码'
	)	
)AND Amount>3
)
	BEGIN

		UPDATE OrderInfo SET PayMoney=PayMoney*0.8
		WHERE CommodityId IN 
		(
			SELECT CommodityId FROM OrderInfo WHERE CommodityId IN
			(
				SELECT CommodityId FROM CommodityInfo WHERE SortId=
				(
					SELECT SortId FROM CommoditySort WHERE SortName='手机数码'
				)	
			)AND Amount>3

		)
	END
	--通常会使用 NOT EXISTS 对子查询的结果进行取反
	























