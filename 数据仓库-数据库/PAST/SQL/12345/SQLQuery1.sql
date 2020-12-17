USE E_Market
GO

INSERT INTO Commoditysort VALUES('手机数码')

SELECT * FROM CommoditySort





INSERT UserInfo VALUES('yoyo','iloveyou','王浩',1,'wanghao@163.com','上海嘉定','010-8238823')

SELECT * FROM UserInfo





INSERT INTO	CommodityInfo(SortId,CommodityName,InOrice,OutPrice,Amount)
VALUES(1,'索尼Z3',3300,4299,100)

SELECT * FROM CommodityInfo

INSERT INTO OrderInfo(UserId,CommodityId,Amount,PayMoney,PayWay,OrderTime,SendGoods,Confirm)
VALUES('yoyo',1,2,8589,DEFAULT,'2014-3-26',1,1)

SELECT * FROM OrederInfo

------------------------------------------------------
SELECT * FROM UserInfo

IF EXISTS (SELECT * FROM sysobjects WHERE name='UserAddress')
DROP TABLE UserAddress
GO

CREATE TABLE UserAddress
(
	UId varchar(20) PRIMARY KEY(UId) NOT NULL,
	Uname varchar(50) NOT NULL,
	UAddress varchar (200),
	UPhone varchar(20) NOT NULL
)
GO

SELECT * FROM UserAddress



INSERT INTO UserAddress(UId,Uname,UAddress,UAddress)
SELECT UserId,UserNme,UserAddress,Phone
FROM UserInfo
GO


SELECT UserId,UserName,UserAddress,Phone,IDENTITY(INT,1,1) AS ID
INTO AddressList
FROM UserInfo
GO


SELECT * FROM UserInfo

UPDATE UserInfo SET Gender=1


UPDATE UserIfo SET UserName='张三' WHERE UserId='yoyo'

UPDATE UserInfo SET UserName='李四',UserAddress='北京市昌平区'
WHERE UserId='daxia'


SELECT * FROM CommodityInfo
UPDATE CommodityInfo SET Amount=10 
WHERE SortId =1 AND CommodityId=3



UPDATE CommodityInfo SET InPrice=900
WHERE CommodityId =4

SELECT * FROM OrderInfo

DELETE FROM OrderInfo WHERE UserId='yoyo'

DELETE UserInfo WHERE UserId ='yoyo'

SELECT * FROM UserInfo
SELECT * FROM OrderInfo

TRUNCATE TABLE OrderInfo




