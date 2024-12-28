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
        cout << "�ļ������ڣ�" << endl;//���Դ���
        this->_empNum = 0;
        this->_empArray = NULL;
        this->_fileIsEmpty = true;
        ifs.close();
        return;
    }

    char ch;
    ifs >> ch;
    if(ifs.eof()){
        cout << "�ļ�Ϊ�գ�" << endl;//���Դ���
        this->_empNum = 0;
        this->_empArray = NULL;
        this->_fileIsEmpty = true;
        ifs.close();
        return;
    }

    this->_fileIsEmpty = false;
    int num = this->getEmpNum();
    cout << "ְ��������Ϊ��" << num << endl;//���Դ���
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
    cout << "*********��ӭʹ��ְ������ϵͳ��********" << endl;
    cout << "************0. �˳�����ϵͳ************" << endl;
    cout << "************1. ����ְ����Ϣ************" << endl;
    cout << "************2. ��ʾְ����Ϣ************" << endl;
    cout << "************3. ɾ����ְְ��************" << endl;
    cout << "************4. �޸�ְ����Ϣ************" << endl;
    cout << "************5. ����ְ����Ϣ************" << endl;
    cout << "************6. ���ձ������************" << endl;
    cout << "************7. ��������ĵ�************" << endl;
    cout << "***************************************" << endl;
    cout << endl;
    cout << "����������ѡ��" << endl;
}

void workerManager::exitSystem()
{
    cout << "��ӭ�´�ʹ�ã�" << endl;
    system("pause");
    exit(0);
}

void workerManager::addEmp()
{
    cout << "����������ְ����������" << endl;
    int addNum = 0;
    cin >> addNum;

    if(addNum > 0){
        int newSize = this->_empNum + addNum;
        Worker **newSpace = new Worker* [newSize];
        //��ԭְ����������ݴ�ŵ��¿ռ���
        if(this->_empArray != NULL){
            for(int i = 0; i < this->_empNum; i++){
                newSpace[i] = this->_empArray[i];
            }
        }

        //��������ְ��������
        for(int i = 0; i < addNum; i++){
            int id;
            string name;
            int deptSelect;

            cout << "������� " << i + 1 << " ����ְ���ı�ţ�" << endl;
            cin >> id;
            cout << "������� " << i + 1 << " ����ְ����������" << endl;
            cin >> name;
            cout << "��ѡ���ְ���ĸ�λ��" << endl;
            cout << "1��Ա��" << endl;
            cout << "2������" << endl;
            cout << "3���ϰ�" << endl;
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
        //�ͷ�ԭ�пռ�
        delete[] this->_empArray;
        //�����¿ռ��ָ��
        this->_empArray = newSpace;
        //�����ļ���ְ������
        this->_empNum = newSize;
        //����ְ���ļ���Ϊ�յı��
        this->_fileIsEmpty = false;

        cout << "�ɹ���� " << addNum << " ����ְ����" << endl;
        //���浽�ļ���
        this->save();
    }
    else{
        cout << "��������" << endl;
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
        cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
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
        cout << "�ļ������ڻ��¼Ϊ��" << endl;
    }
    else{
        //��ְ�����ɾ��
        cout << "��������Ҫɾ��ְ���ı�ţ�" << endl;
        int id = 0;
        cin >> id;
        int index = this->isExist(id);
        if(index != -1){
            for(int i = index; i < this->_empNum - 1; i++){
                this->_empArray[i] = this->_empArray[i+1];
            }
            this->_empNum--;
            this->save();
            cout << "ɾ���ɹ���" << endl;
        }
        else{
            cout << "ɾ��ʧ�ܣ�δ�ҵ���ְ����" << endl;
        }
    }

    system("pause");
    system("cls");
}

void workerManager::modEmp()
{
    if(this->_fileIsEmpty){
        cout << "�ļ������ڻ��¼Ϊ��" << endl;
    }
    else{
        cout << "�������޸�ְ���ı�ţ�" << endl;
        int id;
        cin >> id;
        int index = this->isExist(id);
        if(index != -1){
            delete this->_empArray[index];

            int newId = 0;
            string newName = "";
            int deptSelect = 0;

            cout << "�鵽 " << id << " ��ְ�����������µ�ְ����ţ�" << endl;
            cin >> newId;
            cout << "��������ְ����������" << endl;
            cin >> newName;
            cout << "��ѡ����ְ���ĸ�λ��" << endl;
            cout << "1��Ա��" << endl;
            cout << "2������" << endl;
            cout << "3���ϰ�" << endl;
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
            
            cout << "�޸ĳɹ���" << endl;
        }
        else{
            cout << "�޸�ʧ�ܣ����޴���" << endl;
        }
    }

    system("pause");
    system("cls");
}

void workerManager::findEmp()
{
    if(this->_fileIsEmpty){
        cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
    }
    else{
        cout << "��������ҷ�ʽ��" << endl;
        cout << "1����ְ����Ų���" << endl;
        cout << "2����ְ����������" << endl;
        
        int select = 0;
        cin >> select;

        if(select == 1){
            cout << "������Ҫ���ҵ�ְ����ţ�" << endl;
            int id;
            cin >> id;
            int index = this->isExist(id);
            if(index != -1){
                cout << "���ҳɹ�����ְ����Ϣ���£�" << endl;
                this->_empArray[index]->showInfo();
            }
            else{
                cout << "����ʧ�ܣ����޴���" << endl;
            }
        }
        else if(select == 2){
            cout << "������Ҫ���ҵ�ְ��������" << endl;
            string name;
            cin >> name;

            bool flag = false;
            for(int i = 0; i < this->_empNum; i++){
                if(this->_empArray[i]->_Name == name){
                    cout << "���ҳɹ������Ϊ " << _empArray[i]->_Id 
                    <<" ��ְ����Ϣ���£�" << endl;
                    this->_empArray[i]->showInfo();
                    flag = true;
                }
            }
            if(flag == false){
                cout << "����ʧ�ܣ����޴���" << endl;
            }
        }
        else{
            cout << "����ѡ������" << endl;
        }
    }

    system("pause");
    system("cls");
}

void workerManager::sortEmp()
{
    if(this->_fileIsEmpty){
        cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
    }
    else{
        cout << "��ѡ������ʽ��" << endl;
        cout << "1����ְ���������" << endl;
        cout << "2����ְ����Ž���" << endl;

        int select = 0;
        cin >> select;

        if((select != 1) && (select != 2)){
            cout << "����ѡ������" << endl;
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

            cout << "����ɹ��������Ľ��Ϊ��" << endl;
            this->save();
            this->showEmp();
        }

    }
}

void workerManager::cleanFile()
{
    cout << "ȷ����գ�" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2������" << endl;

    int select = 0;
    cin >> select;

    if(select == 1){
        //ģʽ ios::trunc ��ɾ���ļ������´���������ļ����ڣ�
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
        cout << "��ճɹ���" << endl;
    }

    system("pause");
    system("cls");
}