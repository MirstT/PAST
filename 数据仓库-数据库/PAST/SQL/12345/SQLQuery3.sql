USE E_Market
GO

SELECT * FROM UserInfo WHERE UserName LIKE '李%'


SELECT * FROM UserInfo

SELECT UserId,PayWay,PayMoney FROM OrderInfo
WHERE PayWay='网上银行'

SELECT UserId,PayWay,PayMoney FROM OrderInfo
WHERE PayWay<>'网上银行'


SELECT UserId AS 用户名,PayWay AS 付款方式,PayMoney AS 付款金额 FROM OrderInfo
WHERE PayWay='网上银行'


SELECT 用户名=UserId,付款方式=PayWay,付款金额=PayMoney FROM OrderInfo
WHERE PayWay='网上银行'

SELECT UserId 用户名,PayWay 付款方式,PayMoney 付款金额 FROM OrderInfo
WHERE PayWay='网上银行'

SELECT * FROM UserInfo WHERE Email IS NULL


SELECT * FROM UserInfo WHERE Email IS NULL OR Emai=''
GO


--------------------------------------------
SELECT UserId 用户号,PayWay 付款方式,PayMoney 付款金额 FROM OrderInfo
'天猫' AS 购物网站 FROM OrderInfo



SELECT TOP 5 UserName AS 用户名,UserAddress AS 地址  
FROM UserInfo WHERE Gender=1



SELECT TOP 20 PERCENT UserName AS 用户名,UserAddress AS 地址  
FROM UserInfo WHERE Gender=1




SELECT * FROM UserInfo WHERE Gender=1


SELECT UserId,PayWay,PayMoney FROM OrderInfo
ORDER BY PayMoney DESC

SELECT UserId,PayWay,Amount,PayMoney FROM OrderInfo
ORDER BY Amount DESC,PayMoney ASC
