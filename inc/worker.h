#pragma once
#include<iostream>
#include<string>
using namespace std;

class Worker
{
public:
    //��ʾ������Ϣ
    virtual void showInfo() = 0;
    //��ȡ��λ����
    virtual string getDept() = 0;

    int _Id;        //ְ��ID
    string _Name;   //ְ������
    int _DeptId;    //ְ�����ڸ�λ���
};