#include "LoadExcelDlg.h"

LoadExcelDlg::LoadExcelDlg(QWidget* parent /*= Q_NULLPTR*/)
	:QDialog(parent)
{
	ui.setupUi(this);
	ui.ExcelProgBar->setMinimum(0);  // ��Сֵ
	ui.ExcelProgBar->setMaximum(0);  // ���ֵ
}

LoadExcelDlg::~LoadExcelDlg()
{
}