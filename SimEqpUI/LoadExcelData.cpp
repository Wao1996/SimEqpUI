#include "LoadExcelData.h"
LoadExcelData::LoadExcelData()
{
	excel = new QAxObject("Excel.Application");//����Excel����
	excel->setProperty("Visible", false); //����ʾExcel���棬���Ϊtrue�ῴ��������Excel����
	workbooks = excel->querySubObject("WorkBooks");
}
LoadExcelData::~LoadExcelData()
{
	delete excel;
	excel = nullptr;
}

void LoadExcelData::castVariant2ListListVariant(const QVariant & var, QList<QList<QVariant>>& x_y)
{
	QVariantList varRows;
	varRows = var.toList();
	if (varRows.isEmpty()) {
		return;
	}
	const int rowCount = varRows.size();
	QVariantList rowData;
	for (int i = 0; i < rowCount; ++i) {
		rowData = varRows[i].toList();
		x_y.push_back(rowData);
	}
}

void LoadExcelData::castVariant2VectorAndVector(const QVariant & var, QVector<double>& x, QVector<double>& y)
{
	QVariantList varRows;
	varRows = var.toList();
	if (varRows.isEmpty()) {
		return;
	}
	const int rowCount = varRows.size();
	QVariantList rowData;
	for (int i = 0; i < rowCount; ++i) {
		rowData = varRows[i].toList();
		x.push_back(rowData.value(0).toDouble());
		y.push_back(rowData.value(1).toDouble());
	}
}

void LoadExcelData::castListListVariant2Variant(const QList<QList<QVariant>>& x_y, QVariant & res)
{
	QVariantList vars;
	const int rowCount = x_y.size();
	for (int i = 0; i < rowCount; ++i) {
		vars.append(QVariant(x_y[i]));
	}
	res = QVariant(vars);
}

void LoadExcelData::castListListVariant2VectorAndVector(const QList<QList<QVariant>>& x_y, QVector<double> &x, QVector<double> &y)
{
	QVariant tempData;
	castListListVariant2Variant(x_y, tempData);
	castVariant2VectorAndVector(tempData, x, y);
}
/****************************************************************
** Function name ��convert2ColName
** Description   : ������ת��Ϊexcel����ĸ�к�,��1->A 26->Z 27 AA
** Parameter     ��data>0
** Return        ��
*****************************************************************/
void LoadExcelData::convert2ColName(int data, QString & res)
{
	Q_ASSERT(data > 0 && data < 65535);
	int tempData = data / 26;
	if (tempData > 0) {
		int mode = data % 26;
		convert2ColName(mode, res);
		convert2ColName(tempData, res);
	}
	else {
		res = (to26AlphabetString(data) + res);
	}
}

QString LoadExcelData::to26AlphabetString(int data)
{
	QChar ch = data + 0x40;//A��Ӧ0x41
	return QString(ch);
}

void LoadExcelData::readExcelFast(QString fileName, QList<QList<QVariant>>& x_y)
{
	workbooks->querySubObject("Open(QString&)", fileName);//���ļ�·�����Ѵ��ڵĹ�����
	workbook = excel->querySubObject("ActiveWorkBook");// ��ȡ�������
	worksheets = workbook->querySubObject("WorkSheets");// ��ȡ�򿪵�excel�ļ������еĹ���sheet
	WorkSheetCount = worksheets->property("Count").toInt();//Excel�ļ��б�ĸ���:
	worksheet = worksheets->querySubObject("Item(int)", 1);//��ȡ��һ����������������1
	usedrange_Read = worksheet->querySubObject("UsedRange");//��ȡ��sheet�����ݷ�Χ���������Ϊ�����ݵľ�������)
	//��ȡ����
	rows = usedrange_Read->querySubObject("Rows");
	RowsCount = rows->property("Count").toInt();
	//��ȡ����
	columns = usedrange_Read->querySubObject("Columns");
	ColumnsCount = columns->property("Count").toInt();
	//���ݵ���ʼ��
	StartRow = rows->property("Row").toInt();
	//���ݵ���ʼ��
	StartColumn = columns->property("Column").toInt();

	if (worksheet != NULL && !worksheet->isNull())
	{
		if (NULL == usedrange_Read || usedrange_Read->isNull())
		{
			return;
		}
		var = usedrange_Read->dynamicCall("Value");
		castVariant2ListListVariant(var, x_y); // �˺�����varת������Ҫ�ĸ�ʽ
	}
	//Ҫ�ǵ�close����Ȼϵͳ����������n��EXCEL.EXE����
	workbook->dynamicCall("Close(bool)", false);  //�ر��ļ�
	excel->dynamicCall("Quit()");
}

void LoadExcelData::writeExcelFast(const QList<QList<QVariant>>& x_y, QString fileName)
{
	if (x_y.isEmpty())
	{
		//�����Ϊ������
		emit writeExcelisEmpty();
	}
	else
	{
		workbooks->dynamicCall("Add");//�½�һ�������� �¹�������Ϊ�������
		workbook = excel->querySubObject("ActiveWorkBook");// ��ȡ�������
		worksheet = workbook->querySubObject("Sheets(int)", 1); //��ȡ��һ����������������1

		int row = x_y.size();//����
		int col = x_y.at(0).size();//����
		/*������ת����EXCEL���е���ĸ��ʽ*/
		QString rangStr;
		convert2ColName(col, rangStr);
		rangStr += QString::number(row);
		rangStr = "A1:" + rangStr;
		usedrange_Write = worksheet->querySubObject("Range(const QString&)", rangStr);

		QVariant var;
		castListListVariant2Variant(x_y, var);
		usedrange_Write->setProperty("Value", var);

		workbook->dynamicCall("SaveCopyAs(QString)", QDir::toNativeSeparators(fileName));
		workbook->dynamicCall("Close(bool)", false);  //�ر��ļ�
		excel->dynamicCall("Quit()");//�ر�excel
	}
}

void LoadExcelData::setExcelCell(QAxObject * worksheet, int row, int column, QString text)
{
	QAxObject *cell = worksheet->querySubObject("Cells(int,int)", row, column);
	cell->setProperty("Value", text);
}