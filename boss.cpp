#include "boss.h"

Boss::Boss(int id, string name, int dId)
{
    this->_Id = id;
    this->_Name = name;
    this->_DeptId = dId;
}

void Boss::showInfo()
{
    cout << "ְ����ţ�" << this->_Id
         << "\tְ��������" << this->_Name
         << "\tְ����λ��" << this->getDept()
         << "\t��λְ�𣺹���˾��������" << endl;   
}

string Boss::getDept()
{
    return string("�ϰ�");
}