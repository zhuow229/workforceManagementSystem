#include "manager.h"

Manager::Manager(int id, string name, int dId)
{
    this->_Id = id;
    this->_Name = name;
    this->_DeptId = dId;
}

void Manager::showInfo()
{
    cout << "ְ����ţ�" << this->_Id
         << "\tְ��������" << this->_Name
         << "\tְ����λ��" << this->getDept()
         << "\t��λְ������ϰ彻�������񣬲��·������Ա�� " << endl;
}

string Manager::getDept()
{
    return string("����");   
}