#include "ExcelExport.h"

ExcelExport::ExcelExport()
{
}

void ExcelExport::newExcel(const QString& fileName)
{
	m_Application = new QAxObject();
	m_Application->setControl("Excel.Application");
	m_Application->dynamicCall("SetVisible(bool)", false);
	m_Application->setProperty("DisplayAlerts", false);
	m_WorkBooks = m_Application->querySubObject("WorkBooks");
	QFile file(fileName);
	if (file.exists())
	{
		m_WorkBook = m_WorkBooks->querySubObject(
			"Open(const QString &", fileName);
	}
	else {
		m_WorkBooks->dynamicCall("Add");
		m_WorkBook =
			m_Application->querySubObject("ActiveWorkBook");
	}
	//默认有一个worksheet
	m_Sheets = m_WorkBook->querySubObject("WorkSheets");
	m_Sheet = m_Sheets->querySubObject("Item(int)", 1);
}

void ExcelExport::setCellValue(int row, int column
	, const QString& value)
{
	QAxObject* pRange = m_Sheet->querySubObject("Cells(int,int)"
		, row, column);
	pRange->setProperty("Value", value);
	pRange->setProperty("HorizontalAlignment", -4108);
	pRange->setProperty("VerticalAlignment", -4108);
}

void ExcelExport::setCellValue(int row, int column
	, const int& value)
{
	QAxObject* pRange = m_Sheet->querySubObject("Cells(int,int)"
		, row, column);
	pRange->setProperty("Value", value);
	pRange->setProperty("HorizontalAlignment", -4108);
	pRange->setProperty("VerticalAlignment", -4108);
}

void ExcelExport::saveExcel(const QString& fileName)
{
	m_WorkBook->dynamicCall("SaveAs(const QString &)",
		QDir::toNativeSeparators(fileName));

	m_Application->dynamicCall("Quit(void)"); 
	delete m_Application;
}

ExcelExport::~ExcelExport()
{
}
