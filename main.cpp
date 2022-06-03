//Запускается в режиме отладки//
#include <QCoreApplication>
#include "tasks_rk1.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    LinkedList list1;
    list1.push_back(222);
    list1.push_back(5);
    list1.push_back(8);
    list1.push_back(10);
    list1.push_back(15);
    list1.insert(11,2);
    list1.insert(11,10);
    list1.insert(11,-1);

    list1.writeToFileFromHead();
    list1.writeToFileFromTail();

    //------------------------------------//
    StudentInfo student1("Kokotov","Mihail","L123");
    student1.addSubj("Math");
    student1.addSubj("Physics");
    student1.addMark("Math",8);
    student1.addMark("Math",10);
    student1.addMark("Math",3);
    if(student1.addMark("PE",6)==1)
    {
      cout<<"code 1\n";
    }
    float aver_mark=student1.getAverMark("Language");
    cout<<aver_mark<<"\n";
    student1.addMark("Physics",8);
    student1.addMark("Physics",10);
    student1.addMark("Physics",31);

    student1.printInfoStudent();
    student1.writeAllInfoToFile();

    return 0;
    return a.exec();
}
