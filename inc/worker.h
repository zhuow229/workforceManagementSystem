#pragma once
#include<iostream>
#include<string>
using namespace std;

class Worker
{
public:
    //显示个人信息
    virtual void showInfo() = 0;
    //获取岗位名称
    virtual string getDept() = 0;

    int _Id;        //职工ID
    string _Name;   //职工姓名
    int _DeptId;    //职工所在岗位编号
};