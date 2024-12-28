#pragma once
#include<iostream>
using namespace std;
#include "worker.h"
#include<fstream>

#define FILENAME "workerFile.txt"

class workerManager
{
public:
    //���캯��
    workerManager();

    //��ʾ�˵�
    void showMenu();

    //�˳�ϵͳ
    void exitSystem();

    //��������
    ~workerManager();

    //�����ְ��
    void addEmp();

    //��ְ����Ϣ���浽�ļ���
    void save();

    //ͳ������
    int getEmpNum();

    //��ʼ��ְ������
    void init_Emp();

    //��ʾְ��
    void showEmp();

    //ɾ��ְ��
    void deleteEmp();

    //����ְ������ж�ְ���Ƿ����
    int isExist(int id);

    //�޸�ְ����Ϣ
    void modEmp();

    //����ְ��
    void findEmp();

    //����
    void sortEmp();

    //����ļ�
    void cleanFile();



    //��¼�ļ��е�����
    int _empNum;

    //ְ�������ָ��
    Worker **_empArray;

    bool _fileIsEmpty;
};