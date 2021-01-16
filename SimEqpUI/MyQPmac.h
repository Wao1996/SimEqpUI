#pragma once
#pragma execution_character_set("utf-8")
#include "PmacDeviceLib.h"
#include <QObject>
#include <QtCore>
#include <iostream>
#include <QMessageBox>
#include "SimEqpGlobal.h"
#include <QElapsedTimer>
class MyQPmac:public QObject
{
	Q_OBJECT

public:
	MyQPmac();
	~MyQPmac();

	bool creatPmacSelect();
	bool initPmac();
	void enabelMotorServo();
	void enablePLC(int n);
	bool downloadFile(QString strFile);
	void openForceLoop();//��������Ȼ��ſ��������Լ���plc0�ŷ��㷨

	double getMotorDisp();
	double getMotorVel();
	double getMotorForce();
	bool getLimState();
	bool getForceHomeState();

	void setJogVel(double vel);
	void jogDisp(double disp);


	void startWinds();//��ʼ�˶�������
	void stopWinds();//��;ֹֹͣͣ������

	

private:
	PCOMMSERVERLib::PmacDevice *Pmac0;
	int pDeviceNumber;
	bool pbSuccess_select;
	bool pbSuccess_open;
	bool pbSucess_download;
	QString pAnswer;
	bool bAddLF;
	int pstatus;
};

