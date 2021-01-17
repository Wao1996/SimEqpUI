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
	void closeLoop();//1:�ջ������ܽ����ٶȵ㶯 2:��j+ �����˶�ʱ��ʹ�ÿ���ֹͣ�˶�

	double getMotorDisp();//��ȡ���λ��
	double getMotorVel();
	double getMotorForce();
	bool getPosLimState();//��ȡ����λ״̬
	bool getNegLimState();//��ȡ����λ״̬
	bool getForceHomeState();//��ȡ������״̬

	void setJogVel(double vel);//���õ㶯�ٶ�

	void jogDisp(double disp);//����㶯
	void jogPosContinuously();//����+�˶�

	void startWinds();//��ʼ�˶�������
	void stopWinds();//��;ֹֹͣͣ������
	void forceHome();//������

	

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

