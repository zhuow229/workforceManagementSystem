#include "employee.h"

Employee::Employee(int id, string name, int dId)
{
    this->_Id = id;
    this->_Name = name;
    this->_DeptId = dId;
}

void Employee::showInfo()
{
    cout << "ְ����ţ�" << this->_Id
         << "\tְ��������" << this->_Name
         << "\tְ����λ��" << this->getDept()
         << "\t��λְ����ɾ�����������" << endl;
}

string Employee::getDept()
{
    return string("Ա��");
}