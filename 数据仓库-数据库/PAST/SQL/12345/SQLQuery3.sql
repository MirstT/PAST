USE E_Market
GO

SELECT * FROM UserInfo WHERE UserName LIKE '��%'


SELECT * FROM UserInfo

SELECT UserId,PayWay,PayMoney FROM OrderInfo
WHERE PayWay='��������'

SELECT UserId,PayWay,PayMoney FROM OrderInfo
WHERE PayWay<>'��������'


SELECT UserId AS �û���,PayWay AS ���ʽ,PayMoney AS ������ FROM OrderInfo
WHERE PayWay='��������'


SELECT �û���=UserId,���ʽ=PayWay,������=PayMoney FROM OrderInfo
WHERE PayWay='��������'

SELECT UserId �û���,PayWay ���ʽ,PayMoney ������ FROM OrderInfo
WHERE PayWay='��������'

SELECT * FROM UserInfo WHERE Email IS NULL


SELECT * FROM UserInfo WHERE Email IS NULL OR Emai=''
GO


--------------------------------------------
SELECT UserId �û���,PayWay ���ʽ,PayMoney ������ FROM OrderInfo
'��è' AS ������վ FROM OrderInfo



SELECT TOP 5 UserName AS �û���,UserAddress AS ��ַ  
FROM UserInfo WHERE Gender=1



SELECT TOP 20 PERCENT UserName AS �û���,UserAddress AS ��ַ  
FROM UserInfo WHERE Gender=1




SELECT * FROM UserInfo WHERE Gender=1


SELECT UserId,PayWay,PayMoney FROM OrderInfo
ORDER BY PayMoney DESC

SELECT UserId,PayWay,Amount,PayMoney FROM OrderInfo
ORDER BY Amount DESC,PayMoney ASC
