USE master
GO

IF EXISTS (SELECT * FROM sysdatabases WHERE name='Demo')
DROP DATABASE Demo

CREATE DATABASE Demo
ON PRIMARY
(
	NAME='Demo_data',
	FILENAME='C:\SQL\Demo_data.mdf',
	SIZE=3MB
)

LOG ON
(
	NAME='Demo_log',
	FILENAME='C:\SQL\Demo_log.ldf',
	SIZE=3MB
)
GO

USE Demo
GO
IF EXISTS (SELECT * FROM sysobjects WHERE name='Employee')
DROP TABLE Employee

CREATE TABLE Employee
(
	EmployeeNo int IDENTITY(1001,1) NOT NULL,
	EmployeeName varchar(20) NOT NULL,
	EmployeeId varchar(18),
	Age int NOT NULL,
	PostId int NOT NULL,
	Country nvarchar(50)
)
GO

USE Demo
GO
IF EXISTS(SELECT * FROM sysobjects WHERE name='Post')
DROP TABLE Post
CREATE TABLE Post
(
	PostId int IDENTITY(1,1) NOT NULL,
	PostName varchar(50) NOT NULL
)
GO


