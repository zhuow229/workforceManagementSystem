#include "employee.h"

Employee::Employee(int id, string name, int dId)
{
    this->_Id = id;
    this->_Name = name;
    this->_DeptId = dId;
}

void Employee::showInfo()
{
    cout << "职工编号：" << this->_Id
         << "\t职工姓名：" << this->_Name
         << "\t职工岗位：" << this->getDept()
         << "\t岗位职责：完成经理交给的任务" << endl;
}

string Employee::getDept()
{
    return string("员工");
}