#include "boss.h"

Boss::Boss(int id, string name, int dId)
{
    this->_Id = id;
    this->_Name = name;
    this->_DeptId = dId;
}

void Boss::showInfo()
{
    cout << "职工编号：" << this->_Id
         << "\t职工姓名：" << this->_Name
         << "\t职工岗位：" << this->getDept()
         << "\t岗位职责：管理公司所有事务" << endl;   
}

string Boss::getDept()
{
    return string("老板");
}