#ifndef EXCELEXPORT_H
#define EXCELEXPORT_H
#include <QAxObject>
#include <QDir>
#include <QFile>

class ExcelExport
{
public:
	ExcelExport();
	~ExcelExport();

	void	newExcel(const QString& fileName);
	void	setCellValue(int row, int column, const QString& value);
	void	setCellValue(int row, int column, const int& value);
	void	saveExcel(const QString& fileName);

	QAxObject*	 m_Application;
	QAxObject*	 m_WorkBooks;
	QAxObject*	 m_WorkBook;
	QAxObject*	 m_Sheets;
	QAxObject*	 m_Sheet;

};

#endif
