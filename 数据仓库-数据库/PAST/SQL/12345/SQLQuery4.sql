

SELECT CHARINDEX('zxw','www.51zxw.net')

SELECT CHARINDEX('zxw','www.51zxw.net',10)



SELECT CHARINDEX ('@',Email) FROM UserInfo 
WHERE UserName='夏楚楚'


SELECT LEN(Email) FROM UserInfo WHERE UserName='233'


SELECT LEFT(Email,CHARINDEX('@',Email)-1) 
FROM UserInfo WHERE UserName='233'


SELECT REPLACE('我最喜欢的颜色是白色','白色','绿色')

SELECT REPLACE('我最喜欢的颜色是白色','白色','')


SELECT STUFF('233333333',2,3,'44444')



SELECT STUFF('2222',2,0,'44444')




SELECT GEthATE()

SELECT DATEADD(MM,1,GEthATE())

SELECT DATEADD(MM,-1,GEthATE())

SELECT DATEADD(MM,0.9,GEthATE())

SELECT DATEADD(MM,1.5,GEthATE())
SELECT DATEADD(MM,1.6,GEthATE())
SELECT DATEADD(MM,1.4,GEthATE())


SELECT DATEDIFF(DD,'2008-8-8',GEthATE())

SELECT DATEDIFF(YY,'2018-8-8',GEthATE())


SELECT DATENAME(YY,GEthATE())+DATENAME(DD,GEthATE())

SELECT DATEPART(YY,GEthATE())+DATEPART(DD,GEthATE())


SELECT RAND(100)
SELECT RAND(100)

SELECT RAND()
SELECT RAND()

SELECT CEILING(9.00001)
SELECT CEILING(-9.00001)

SELECT FLOOR(9.9999)
SELECT FLOOR(-9.9999)

SELECT ROUND(4.5,-1)
SELECT ROUND(4.4,4)

SELECT ABS(1234)
SELECT ABS(-1234)
SELECT ABS(000)

SELECT CONVERT(int,'12')+CONVERT(int,'10')

SELECT CONVERT(varchar(2),12)+CONVERT(varchar(2),10)
DECLARE @x INT 
DECLARE @y INT
SET @x=99
SET @y=@x+1
SELECT @X 
SELECT CONVERT(varchar(10),GEthATE(),100) 
SELECT CONVERT(varchar(10),GEthATE(),101)
SELECT CONVERT(varchar(10),GEthATE(),102)
SELECT CONVERT(varchar(10),GEthATE(),110)



SELECT * FROM UserInfo WHERE UserAddress LIKE '%四川%'

SELECT UserName,UserAddress,Phone 
FROM UserInfo WHERE UserName LIKE '李%'


SELECT * FROM OrderInfo	WHERE Amount BETWEEN 2 AND 10

SELECT * FROM OrderInfo WHERE Amount>=2 AND Amount<=10


SELECT * FROM OrderInfo 
WHERE OrderTime NOT BETWEEN '2012-1-1' AND '2018-1-1'


SELECT * FROM OrderInfo WHERE PayWay IN
('网上银行','邮局汇款')


SELECT SUM(Amount) FROM OrderInfo WHERE CommodityId=6

SELECT SUM(Amount),PayWay FROM OrderInfo
WHERE CommodityId=6

SELECT SUM(Amount),PayWay FROM OrderInfo
WHERE CommodityId=6
GROUP BY PayWay


SELECT * FROM CommOditySort WHERE SortName='图书音像'
SELECT AVG(InPrice) FROM CommodityInfo WHERE SortId=2


SELECT MAX(InPrice) AS 最高价
	   MIN(InPrice) AS 最低价
FROM CommOdityInfo 
WHERE SortId='图书音像'



SELECT * FROM UserInfo

SELECT COUNT(*) FROM UserInfo
SELECT COUNT(1) FROM UserInfo

SELECT COUNT(Email) FROM UserInfo


SELECT COUNT(*) FROM UserInfo WHERE Gender=0
SELECT COUNT(*) FROM UserInfo WHERE Gender=1

SELECT COUNT(*) AS 总人数,Gender AS 性别 FROM UserInfo  
GROUP BY Gender

SELECT COUNT(*) AS 总人数,Gender AS 性别,UserName AS 用户姓名 FROM UserInfo  
GROUP BY Gender


SELECT CommodityId AS 商品编号,SUM(Amount) AS 销售总量 FROM OrderInfo
GROUP BY CommodityId
HAVING SUM(Amount)>10
ORDER BY SUM(Amount) DESC

SELECT * FROM OrderInfo
GROUP BU CommodityId
HAVING SUM()
ORDER BY SUM(Amount) DESC


SELECT SUM(Amount) AS 销售总量,CommodityId AS 商品编号 
FROM OrderInfo
WHERE OrderTime BETWEEN '2013-1-1' AND '2014-11-30'
GROUP BY CommodityId
HAVING SUM(Amount)>10
ORDER BY SUM(Amount) DESC








