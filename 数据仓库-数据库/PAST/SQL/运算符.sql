SELECT 3+4 AS 加的结果
GO
SELECT 5/2 AS 除的结果
GO
SELECT 5.0/2 AS 除的结果
GO

SELECT 5%2 AS 模
GO

DECLARE @age int
SET @age=18
SELECT @age
GO

DECLARE @x int,@y int
SET @x=8
SET @y=10
IF @x>=@y
	SELECT '@x的值大于等于@y的值'
ELSE
	SELECT'@y的值=大'
GO


IF(3>5 OR 6>3 AND NOT 6>4)
	SELECT 'TRUE(真)'
ELSE
	SELECT'FALSE(假)'
GO

DECLARE @color varchar(4)
SET @color ='白色'
SELECT '我最喜欢的颜色'+@color
GO




