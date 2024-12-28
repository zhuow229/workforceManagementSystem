#include<iostream>
#include "workerManager.h"
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

using namespace std;

// void test(){
//     Worker *worker = NULL;
//     worker = new Employee(1, "张三", 1);
//     worker->showInfo();
//     delete worker;

//     worker = new Manager(2, "李四", 2);
//     worker->showInfo();
//     delete worker;

//     worker = new Boss(3, "王五", 3);
//     worker->showInfo();
//     delete worker;
// }




int main(){
    workerManager wm;
    int choice = 0;
    while(true){
        wm.showMenu();
        cin >> choice;

        switch(choice){
        case 0:
            wm.exitSystem();
            break;
        case 1:
            wm.addEmp();
            break;
        case 2:
            wm.showEmp();
            break;
        case 3:
            wm.deleteEmp();
            break;
        case 4:
            wm.modEmp();
            break;
        case 5:
            wm.findEmp();
            break;
        case 6:
            wm.sortEmp();
            break;
        case 7:
            wm.cleanFile();
            break;
        default:
            system("cls");
            break;
        }
    }

    //test();
    

    system("pause");
    return 0;
}