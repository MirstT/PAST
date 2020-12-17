USE Demo
GO

ALTER TABLE Post
ADD CONSTRAINT PK_PostId PRIMARY KEY(PostId)
GO

--ALTER TABLE Employee
--ADD CONSTRAINT CK_EmployeeId CHECK (LEN(EmployeeId)=18)
--GO

--ALTER TABLE Employee WITH NOCHECK
--ADD CONSTRAINT CK_EmployeeId CHECK (LEN(EmployeeId)=8)
--GO

ALTER TABLE Employee
ADD CONSTRAINT PK_EmployeeNo PRIMARY KEY(EmployeeNo),
	CONSTRAINT CK_EmployeeId CHECK (LEN(EmployeeId)=18),
	CONSTRAINT UQ_EmployeeId UNIQUE(EmployeeId),
	CONSTRAINT CK_Age CHECK (Age>=18 AND Age<=55),
	CONSTRAINT FK_PostId FOREIGN KEY (PostId) REFERENCES Post (PostId),
	CONSTRAINT DF_Country DEFAULT('�й�') FOR Country
GO




