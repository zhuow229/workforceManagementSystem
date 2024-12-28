#pragma once
#include<iostream>
using namespace std;
#include "worker.h"
#include<fstream>

#define FILENAME "workerFile.txt"

class workerManager
{
public:
    //构造函数
    workerManager();

    //显示菜单
    void showMenu();

    //退出系统
    void exitSystem();

    //析构函数
    ~workerManager();

    //添加新职工
    void addEmp();

    //将职工信息保存到文件中
    void save();

    //统计人数
    int getEmpNum();

    //初始化职工数组
    void init_Emp();

    //显示职工
    void showEmp();

    //删除职工
    void deleteEmp();

    //根据职工编号判断职工是否存在
    int isExist(int id);

    //修改职工信息
    void modEmp();

    //查找职工
    void findEmp();

    //排序
    void sortEmp();

    //清空文件
    void cleanFile();



    //记录文件中的人数
    int _empNum;

    //职工数组的指针
    Worker **_empArray;

    bool _fileIsEmpty;
};