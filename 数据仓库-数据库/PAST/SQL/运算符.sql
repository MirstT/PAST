SELECT 3+4 AS �ӵĽ��
GO
SELECT 5/2 AS ���Ľ��
GO
SELECT 5.0/2 AS ���Ľ��
GO

SELECT 5%2 AS ģ
GO

DECLARE @age int
SET @age=18
SELECT @age
GO

DECLARE @x int,@y int
SET @x=8
SET @y=10
IF @x>=@y
	SELECT '@x��ֵ���ڵ���@y��ֵ'
ELSE
	SELECT'@y��ֵ=��'
GO


IF(3>5 OR 6>3 AND NOT 6>4)
	SELECT 'TRUE(��)'
ELSE
	SELECT'FALSE(��)'
GO

DECLARE @color varchar(4)
SET @color ='��ɫ'
SELECT '����ϲ������ɫ'+@color
GO




