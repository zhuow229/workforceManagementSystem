#include "workerManager.h"
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

workerManager::workerManager()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);
    if(!ifs.is_open()){
        cout << "文件不存在！" << endl;//测试代码
        this->_empNum = 0;
        this->_empArray = NULL;
        this->_fileIsEmpty = true;
        ifs.close();
        return;
    }

    char ch;
    ifs >> ch;
    if(ifs.eof()){
        cout << "文件为空！" << endl;//测试代码
        this->_empNum = 0;
        this->_empArray = NULL;
        this->_fileIsEmpty = true;
        ifs.close();
        return;
    }

    this->_fileIsEmpty = false;
    int num = this->getEmpNum();
    cout << "职工总人数为：" << num << endl;//测试代码
    this->_empNum = num;

    this->_empArray = new Worker *[this->_empNum];
    init_Emp();
}

workerManager::~workerManager()
{
    if(this->_empArray != NULL){
        delete[] this->_empArray;
    }
}

void workerManager::showMenu()
{
    cout << "***************************************" << endl;
    cout << "*********欢迎使用职工管理系统！********" << endl;
    cout << "************0. 退出管理系统************" << endl;
    cout << "************1. 增加职工信息************" << endl;
    cout << "************2. 显示职工信息************" << endl;
    cout << "************3. 删除离职职工************" << endl;
    cout << "************4. 修改职工信息************" << endl;
    cout << "************5. 查找职工信息************" << endl;
    cout << "************6. 按照编号排序************" << endl;
    cout << "************7. 清空所有文档************" << endl;
    cout << "***************************************" << endl;
    cout << endl;
    cout << "请输入您的选择：" << endl;
}

void workerManager::exitSystem()
{
    cout << "欢迎下次使用！" << endl;
    system("pause");
    exit(0);
}

void workerManager::addEmp()
{
    cout << "请输入增加职工的数量：" << endl;
    int addNum = 0;
    cin >> addNum;

    if(addNum > 0){
        int newSize = this->_empNum + addNum;
        Worker **newSpace = new Worker* [newSize];
        //将原职工数组的内容存放到新空间中
        if(this->_empArray != NULL){
            for(int i = 0; i < this->_empNum; i++){
                newSpace[i] = this->_empArray[i];
            }
        }

        //输入增加职工的数据
        for(int i = 0; i < addNum; i++){
            int id;
            string name;
            int deptSelect;

            cout << "请输入第 " << i + 1 << " 个新职工的编号：" << endl;
            cin >> id;
            cout << "请输入第 " << i + 1 << " 个新职工的姓名：" << endl;
            cin >> name;
            cout << "请选择该职工的岗位：" << endl;
            cout << "1、员工" << endl;
            cout << "2、经理" << endl;
            cout << "3、老板" << endl;
            cin >> deptSelect;

            Worker *worker = NULL;
            switch(deptSelect){
            case 1:
                worker = new Employee(id, name, 1);
                break;
            case 2:
                worker = new Manager(id, name, 2);
                break;
            case 3:
                worker = new Boss(id, name, 3);
                break;
            default:
                break;
            }

            newSpace[this->_empNum + i] = worker;
        }
        //释放原有空间
        delete[] this->_empArray;
        //更新新空间的指向
        this->_empArray = newSpace;
        //更新文件中职工个数
        this->_empNum = newSize;
        //更新职工文件不为空的标记
        this->_fileIsEmpty = false;

        cout << "成功添加 " << addNum << " 名新职工！" << endl;
        //保存到文件中
        this->save();
    }
    else{
        cout << "输入有误" << endl;
    }

    system("pause");
    system("cls");
}

void workerManager::save()
{
    ofstream ofs;
    ofs.open(FILENAME, ios::out);
    for(int i = 0; i < this->_empNum; i++){
        ofs << this->_empArray[i]->_Id << " "
            << this->_empArray[i]->_Name << " "
            << this->_empArray[i]->_DeptId << endl;
    }

    ofs.close();
}

int workerManager::getEmpNum()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);

    int id;
    string name;
    int dId;

    int num = 0;

    while(ifs >> id && ifs >> name && ifs >> dId){
        num++;
    }
    ifs.close();

    return num;
}

void workerManager::init_Emp()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);
    int id;
    string name;
    int dId;
    int index = 0;
    while(ifs >> id && ifs >> name && ifs >> dId){
        Worker *worker = NULL;
        if(dId == 1){
            worker = new Employee(id, name, dId);
        }
        else if(dId == 2){
            worker = new Manager(id, name, dId);
        }
        else if(dId == 3){
            worker = new Boss(id, name, dId);
        }

        this->_empArray[index] = worker;
        index++;
    }
}

void workerManager::showEmp()
{
    if(this->_fileIsEmpty){
        cout << "文件不存在或记录为空！" << endl;
    }
    else{
        for(int i = 0; i < this->_empNum; i++){
            this->_empArray[i]->showInfo();
        }
    }

    system("pause");
    system("cls");
}

int workerManager::isExist(int id)
{
    int index = -1;
    for(int i = 0; i < this->_empNum; i++){
        if(this->_empArray[i]->_Id == id){
            index = i;
            break;
        }
    }
    return index;
}

void workerManager::deleteEmp()
{
    if(this->_fileIsEmpty){
        cout << "文件不存在或记录为空" << endl;
    }
    else{
        //按职工编号删除
        cout << "请输入想要删除职工的编号：" << endl;
        int id = 0;
        cin >> id;
        int index = this->isExist(id);
        if(index != -1){
            for(int i = index; i < this->_empNum - 1; i++){
                this->_empArray[i] = this->_empArray[i+1];
            }
            this->_empNum--;
            this->save();
            cout << "删除成功！" << endl;
        }
        else{
            cout << "删除失败，未找到该职工！" << endl;
        }
    }

    system("pause");
    system("cls");
}

void workerManager::modEmp()
{
    if(this->_fileIsEmpty){
        cout << "文件不存在或记录为空" << endl;
    }
    else{
        cout << "请输入修改职工的编号：" << endl;
        int id;
        cin >> id;
        int index = this->isExist(id);
        if(index != -1){
            delete this->_empArray[index];

            int newId = 0;
            string newName = "";
            int deptSelect = 0;

            cout << "查到 " << id << " 号职工，请输入新的职工编号：" << endl;
            cin >> newId;
            cout << "请输入新职工的姓名：" << endl;
            cin >> newName;
            cout << "请选择新职工的岗位：" << endl;
            cout << "1、员工" << endl;
            cout << "2、经理" << endl;
            cout << "3、老板" << endl;
            cin >> deptSelect;

            Worker *worker = NULL;
            switch (deptSelect)
            {
            case 1:
                worker = new Employee(newId, newName, 1);
                break;
            case 2:
                worker = new Manager(newId, newName, 2);
                break;
            case 3:
                worker = new Boss(newId, newName, 3);
                break;
            default:
                break;
            }

            this->_empArray[index] = worker;
            this->save();
            
            cout << "修改成功！" << endl;
        }
        else{
            cout << "修改失败，查无此人" << endl;
        }
    }

    system("pause");
    system("cls");
}

void workerManager::findEmp()
{
    if(this->_fileIsEmpty){
        cout << "文件不存在或记录为空！" << endl;
    }
    else{
        cout << "请输入查找方式：" << endl;
        cout << "1、按职工编号查找" << endl;
        cout << "2、按职工姓名查找" << endl;
        
        int select = 0;
        cin >> select;

        if(select == 1){
            cout << "请输入要查找的职工编号：" << endl;
            int id;
            cin >> id;
            int index = this->isExist(id);
            if(index != -1){
                cout << "查找成功！该职工信息如下：" << endl;
                this->_empArray[index]->showInfo();
            }
            else{
                cout << "查找失败，查无此人" << endl;
            }
        }
        else if(select == 2){
            cout << "请输入要查找的职工姓名：" << endl;
            string name;
            cin >> name;

            bool flag = false;
            for(int i = 0; i < this->_empNum; i++){
                if(this->_empArray[i]->_Name == name){
                    cout << "查找成功！编号为 " << _empArray[i]->_Id 
                    <<" 的职工信息如下：" << endl;
                    this->_empArray[i]->showInfo();
                    flag = true;
                }
            }
            if(flag == false){
                cout << "查找失败，查无此人" << endl;
            }
        }
        else{
            cout << "输入选项有误" << endl;
        }
    }

    system("pause");
    system("cls");
}

void workerManager::sortEmp()
{
    if(this->_fileIsEmpty){
        cout << "文件不存在或记录为空！" << endl;
    }
    else{
        cout << "请选择排序方式：" << endl;
        cout << "1、按职工编号升序" << endl;
        cout << "2、按职工编号降序" << endl;

        int select = 0;
        cin >> select;

        if((select != 1) && (select != 2)){
            cout << "输入选项有误" << endl;
        }
        else{
            for(int i = 0; i < this->_empNum; i++){
                int minOrMax = i;
                for(int j = i + 1; j < this->_empNum; j++){
                    if(select == 1){
                        if(_empArray[minOrMax]->_Id > _empArray[j]->_Id){
                            minOrMax = j;
                        }
                    }
                    else if(select == 2){
                        if(_empArray[minOrMax]->_Id < _empArray[j]->_Id){
                            minOrMax = j;
                        }
                    }
                }
                if(i != minOrMax){
                    Worker *temp = _empArray[i];
                    _empArray[i] = _empArray[minOrMax];
                    _empArray[minOrMax] = temp;
                }
            }

            cout << "排序成功，排序后的结果为：" << endl;
            this->save();
            this->showEmp();
        }

    }
}

void workerManager::cleanFile()
{
    cout << "确认清空？" << endl;
	cout << "1、确认" << endl;
	cout << "2、返回" << endl;

    int select = 0;
    cin >> select;

    if(select == 1){
        //模式 ios::trunc 可删除文件并重新创建（如果文件存在）
        ofstream ofs(FILENAME, ios::trunc);
        ofs.close();

        if(this->_empArray != NULL){
            for(int i = 0; i < this->_empNum; i++){
                if(this->_empArray[i] != NULL){
                    delete this->_empArray[i];
                }
            }
            this->_empNum = 0;
            delete[] this->_empArray;
            this->_empArray = NULL;
            this->_fileIsEmpty = true;
        }
        cout << "清空成功！" << endl;
    }

    system("pause");
    system("cls");
}