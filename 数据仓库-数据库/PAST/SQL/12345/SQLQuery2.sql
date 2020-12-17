USE master
CREATE DATABASE TesthB
ON PRIMARY
(
	NAME='TesthB_data',
	FILENAME='C:\SQL\TesthB_data.mdf',
	SIZE=3MB
)

LOG ON
(
	NAME='TesthB_log',
	FILENAME='C:\SQL\TesthB_log.ldf',
	SIZE=3MB
)

CREATE TABLE TestTable
(
	UID int,
	UName varchar (20)
)




USE master
GO

CREATE DATABASE TesthB
ON PRIMARY
(
	NAME='TesthB_data',
	FILENAME='C:\SQL\TesthB_data.mdf',
	SIZE=3MB
)

LOG ON
(
	NAME='TesthB_log',
	FILENAME='C:\SQL\TesthB_log.ldf',
	SIZE=3MB
)
GO

USE TesthB
GO

CREATE TABLE TestTable
(
	UID int,
	UName varchar (20)
)
GO
