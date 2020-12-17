USE N
GO

DROP TABLE CommodityInfo
DROP TABLE CommoditySort
GO


USE N
GO

SELECT *FROM sysobjects

IF EXISTS (SELECT * FROM sysobjects WHERE name='CommodityInfo')
DROP TABLE CommdityInfo
GO

	