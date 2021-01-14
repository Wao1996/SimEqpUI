#ifndef CURVEPLOT_H
#define CURVEPLOT_H
#include "qcustomplot.h"
#include <QAxObject>
#pragma execution_character_set("utf-8")
class CurvePlot :public QObject
{
	Q_OBJECT
public:
	explicit CurvePlot(QCustomPlot * Plot);
	virtual ~CurvePlot();


	void setxAxisName(QString name);
	void setyAxisName(QString name);
	void setxAxisRange(double lower, double upper);
	void setyAxisRange(double lower, double upper);
	void setGraphName(QString name0, QString name1);
	void setSelectLegend(bool enabled);
	void setLegendFont(QFont font);

	/*************��������*************/
	int curIndex;//��ǰ���ߺ� = 0, = 1, = -1ʱδѡ������
	//0������(Ŀ������)
	QVector<double> x0;//�洢x���������
	QVector<double> y0;//�洢y���������
	QList<QList<QVariant>> x_y0;
	//1������(�ɼ�����)
	QVector<double> x1;//�洢x���������
	QVector<double> y1;//�洢y���������
	QList<QList<QVariant>> x_y1;

public slots:
	void on_act_tracerToggled(bool arg1);
	void myMouseMoveEvent(QMouseEvent* event);//����¼�
	void rescaleAxes();//�Զ�����
	void clearCurve();//�������
	void clearAllCurves();//�����������
private:
	/*��ͼ����*/
	QCustomPlot * myPlot = nullptr;

	/*����*/
	QVector<QPen> pen;
	/*************�α�*************/
	bool tracerEnable;//�α�ʹ��
	QCPItemTracer *tracer0 = nullptr; // 0�������α�
	QCPItemTracer *tracer1 = nullptr; // 1�������α�
	QCPItemText *tracer0Label = nullptr; // 0������X�α��ǩ
	QCPItemText *tracer1Label = nullptr;;// 1������Y���α��ǩ
	void setVisibleTracer(bool trueorfalse);//�α�ɼ�/���ɼ� true/false

	/*********����X�᷶Χ**********/
	QCPRange QrangeX0;//0������X�᷶Χ
	double  QrangeX0_lower;
	double  QrangeX0_upper;
	QCPRange QrangeX1;//1������X�᷶Χ
	double  QrangeX1_lower;
	double  QrangeX1_upper;
	bool foundRange;
};

#endif
