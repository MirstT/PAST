USE E_Market
GO

SELECT OrderInfo.OrderId,UserInfo.UserName,OrderInfo.Amount,OrderInfo.CommodityId
FROM OrderInfo,UserInfo
WHERE OrderInfo.UserId=UserInfo.UserId


SELECT COUNT(*) FROM UserInfo
SELECT COUNT(*) FROM OrderInfo


--��������

SELECT O.OrderId,U.UserName,O.Amount,C.CommodityName
FROM OrderInfo AS 0,UserInfo AS U, CommodityInfo AS C
WHERE O.UserId=U.UserId AND C.CommodityId=O.CommodityId



SELECT OrderId,UserName,O.Amount,CommodityName 
FROM UserInfo AS U
INNER JOIN OrderInfo AS O ON U.UserId=0.UserId
INNER JOIN CommodityInfo AS C ON O.CommodityId=C.CommodityId
WHERE U.UserName='�Կ���'





SELECT SortName AS ��Ʒ���,Amount AS �����,CommodityName AS ��Ʒ����
FROM CommoditySort
LEFT JOIN CommodityInfo
ON CommoditySort.SortId=CommodityInfo.SortId


SELECT CommodityName AS ��Ʒ����, OrderId AS ������
FROM OrderInfo 
RIGHT JOIN CommodityInfo
ON OrderInfo.CommodityId=CommodityInfo.CommodityId


SELECT S.SortName AS �������,Amount AS �����
FROM CommoditySort AS S
LEFT JOIN CommodityInfo AS C
ON S.SortId=C.SortId

SELECT S.SortName AS �������,Amount AS �����
FROM CommodityInfo AS C
RIGHT JOIN CommoditySort AS S
ON S.SortId=C.SortId


SELECT UserId AS �û����,UserName AS �û�����, UserAddress AS ��ַ 
FROM UserInfo 

UNION

SELECT PayWay AS ���ʽ, UserId AS �µ��û���,CONVERT(varchar(10),OrderTime) AS �µ�ʱ��
FROM OrderInfo

UNION ALL

SELECT UserId AS �û����,UserName AS �û�����, UserAddress AS ��ַ 
FROM UserInfo 
ORDER BY UserId DESC

-------------------------------------

SELECT UserId AS �û����,UserName AS �û�����, UserAddress AS ��ַ 
FROM UserInfo 

UNION

SELECT PayWay AS ���ʽ, UserId AS �µ��û���,CONVERT(varchar(10),OrderTime) AS �µ�ʱ��
FROM OrderInfo




SELECT UserInfo.UserId AS �û����,UserName AS �û�����, UserAddress AS ��ַ ,
       PayWay AS ���ʽ,CONVERT(varchar(10),OrderTime) AS �µ�ʱ��
FROM UserInfo,OrderInfo

WHERE UserInfo.UserId=OrderInfo.UserId


SELECT * FROM CommoditySort WHERE SortName='�ֻ�����'

SELECT * FROM CommodityInfo WHERE SortId= 
(
SELECT SortId FROM CommoditySort WHERE SortName='�ֻ�����'
)





SELECT * FROM CommodityInfo AS C
INNER JOIN OrderInfo AS O ON C.CommodityId=O.CommodityId
INNER JOIN UserInfo AS U ON O.UserId=U.UserId
WHERE C.CommodityName='ƻ��Iphone6'



SELECT CommodityId FROM CommoddityInfo 
WHERE CommodityName='ƻ��Iphone6'



SELECT UserId FROM OrderInfo WHERE CommodityId=
(
SELECT CommodityId FROM CommoddityInfo 
WHERE CommodityName='ƻ��Iphone6'
)


SELECT UserName AS �û���,UserAddress AS �û���ַ FROM UserInfo WHERE UserId=
(
	SELECT UserId FROM OrderInfo WHERE CommodityId=
	(
		SELECT CommodityId FROM CommoddityInfo 
		WHERE CommodityName='ƻ��Iphone6'
	)
)





--IN NOT IN

SELECT CommodityId FROM CommodityInfo WHERE CommodityName='����С˧��'

SELECT UserId FROM OrderInfo WHERE CommodityId=
(
	SELECT CommodityId FROM CommodityInfo WHERE CommodityName='����С˧��'
)



SELECT * FROM UserInfo WHERE UserId IN
(
	SELECT UserId FROM OrderInfo WHERE CommodityId=
	(
		SELECT CommodityId FROM CommodityInfo WHERE CommodityName='����С˧��'
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
SELECT SortId FROM CommoditySort WHERE SortName='�ֻ�����'





SELECT CommodityId FROM CommodityInfo WHERE SortId=
(
	SELECT SortId FROM CommoditySort WHERE SortName='�ֻ�����'
)









IF EXISTS(SELECT * FROM OrderInfo WHERE CommodityId IN
(
	SELECT CommodityId FROM CommodityInfo WHERE SortId=
	(
		SELECT SortId FROM CommoditySort WHERE SortName='�ֻ�����'
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
					SELECT SortId FROM CommoditySort WHERE SortName='�ֻ�����'
				)	
			)AND Amount>3

		)
	END
	--ͨ����ʹ�� NOT EXISTS ���Ӳ�ѯ�Ľ������ȡ��
	























