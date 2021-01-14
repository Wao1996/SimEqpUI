#ifndef LOADEXCELDATA_H
#define LOADEXCELDATA_H
#pragma execution_character_set("utf-8")
#include <QtCore>
#include <iostream>
#include <QAxObject>
#include <QDir>
#include <QObject>
#include <QMetaType>
#include <QVector>
#include <QVariant>

class LoadExcelData;

class LoadExcelData :public QObject
{
	Q_OBJECT
public:
	explicit LoadExcelData();
	virtual ~LoadExcelData();

	/*******************����ת��*******************/
		/*��QVariantתΪQList<QList<QVariant>>,���ڿ��ٶ���*/
	static void castVariant2ListListVariant(const QVariant &var, QList<QList<QVariant> > &x_y);

	/*��QVariantתΪQVector<double>,���ڿ��ٶ���*/
	static void castVariant2VectorAndVector(const QVariant &var, QVector<double> &x, QVector<double> &y);

	/*��QList<QList<QVariant>>תΪQVariant,���ڿ���д��*/
	static void castListListVariant2Variant(const QList<QList<QVariant> > &x_y, QVariant &res);

	/*��QList<QList<QVariant>>תΪQVariant�Լ�QVector<double>,���ڿ���д��*/
	static void castListListVariant2VectorAndVector(const QList<QList<QVariant> > &x_y, QVector<double> &x, QVector<double> &y);

	/*������ת��Ϊexcel����ĸ�к�*/
	static void convert2ColName(int data, QString &res);

	/*����ת��Ϊ26��ĸ*/
	static QString to26AlphabetString(int data);
	/**********************************************/

		/*��ȡ*/
	void readExcelFast(QString fileName, QList<QList<QVariant> > &x_y);//���ٶ�ȡ����

	/*д��*/
	void writeExcelFast(const QList<QList<QVariant> > &x_y, QString fileName);//����д��
	void setExcelCell(QAxObject *worksheet, int row, int column, QString text);//����Ԫд��
signals:
	void writeExcelisEmpty();
private:
	QAxObject * excel;
	QAxObject * workbooks;
	QAxObject * workbook;
	QAxObject * worksheets;
	QAxObject * worksheet;
	QAxObject * usedrange_Read;//��ȡ���ݾ�������
	QAxObject * usedrange_Write;//д�����ݾ�������
	QAxObject * rows;//����
	QAxObject * columns;//����
	int WorkSheetCount;//Excel�ļ��б�ĸ���
	int RowsCount;//������
	int ColumnsCount;//������
	int StartRow;//���ݵ���ʼ��
	int StartColumn;//���ݵ���ʼ��
	QVariant var;
};

#endif // LOADDATA_H
