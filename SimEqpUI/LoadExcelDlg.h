#ifndef LOADEXCELDLG_H
#define LOADEXCELDLG_H
#pragma execution_character_set("utf-8")
#include <qdialog.h>
#include "ui_LoadExcelDlg.h"
//������ʾ������
class LoadExcelDlg :
	public QDialog
{
	Q_OBJECT
public:
	LoadExcelDlg(QWidget* parent = Q_NULLPTR);
	~LoadExcelDlg();
private:
	Ui::LoadExcelDlg ui;
};

#endif // LOADEXCELDLG_H
