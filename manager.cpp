#include "manager.h"

Manager::Manager(int id, string name, int dId)
{
    this->_Id = id;
    this->_Name = name;
    this->_DeptId = dId;
}

void Manager::showInfo()
{
    cout << "职工编号：" << this->_Id
         << "\t职工姓名：" << this->_Name
         << "\t职工岗位：" << this->getDept()
         << "\t岗位职责：完成老板交给的任务，并下发任务给员工 " << endl;
}

string Manager::getDept()
{
    return string("经理");   
}