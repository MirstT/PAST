USE N
GO
IF EXISTS(SELECT *FROM sysobjects WHERE name='Test')
DROP TABLE Test
CREATE TABLE Test
(
	UName nvarchar(50) NOT NULL,
	UPwd nvarchar(50) NOT NULL,
	UAddress nvarchar(50) NOT NULL
)
GO

DECLARE @x  int,@y int

SET @x=10000
SET @y=0
WHILE(@y<@x)
	BEGIN
		INSERT INTO Test(UName,UPwd,UAddress)
		VALUES('ÕÅÈý'+CONVERT(varchar(5),@x),@y,'23333')
		SET @y=@y+1
	END

	GO


SELECT COUNT(*) FROM Test

TRUNCATE TABLE Test
