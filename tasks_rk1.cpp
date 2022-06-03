#include <iostream>
#include <QVector>
#include <QString>
#include <QTextStream>
#include <QtGlobal>
#include <stdio.h>
#include <QDebug>
#include <QFile>
#include <map>
#include <tuple>
#include <string>
#include <fstream>
#include "tasks_rk1.h"

using namespace std;

//task6

LinkedList::LinkedList()
{
    countNodes=0;
    Head=NULL;
    Tail=NULL;
}
LinkedList::~LinkedList() {}

void LinkedList::push_back(int nameNode)
{
    countNodes++;
    Node* tmp = new Node;
           tmp->nameNode = nameNode;
           tmp->next = NULL;

           if (Head == NULL)
           {
               Head = tmp;
               Tail = tmp;
               Head->prev = NULL;
               Tail->next = NULL;
           }
           else
           {
               tmp->prev = Tail;
               tmp->next = NULL;
               Tail->next = tmp;
               Tail = Tail->next;
           }
}
void LinkedList::writeToFileFromTail()
{
    ofstream myfile;
            myfile.open("example.txt");
            Node* temp = Tail;
            myfile << "\nWriting from tail" << endl;
            while (temp != NULL)
            {

                myfile << " " << temp->nameNode << " ";
                temp = temp->prev;
                if (temp == NULL)
                    break;

            }
            myfile.close();
}

void LinkedList::writeToFileFromHead()
{
    ofstream myfile;
            myfile.open("example1.txt");
            myfile << "\nWriting from head" << endl;
            Node* temp = Head;
            while (temp != NULL)
            {
                myfile << " " << temp->nameNode << " ";
                temp = temp->next;
            }
            myfile.close();
}

//task7
void LinkedList::insert(int nameNode, int pos)
{
    if(pos>countNodes)
    {
        cout<<"Position out of range\n";
        return;
    }
     //1.Выделяем узел для нового элемента
    Node* newNode = new Node();
    newNode->nameNode = nameNode;
    newNode->next = NULL;
    newNode->prev = NULL;

    //2. Проверить больше ли нуля позиция
        if (pos < 1)
            {
        cout << "\nposition should be >= 1.";
            }
    //3. Если позиция равна 1, сделать новый узел head-ом
        else if (pos == 1)
            {
               newNode->next = Head;
               Head->prev = newNode;
               Head = newNode;
               countNodes++;
            }
        else
            {
     //4. В противном случае создаем временный узел и переходим к узлу, предшествующему положению
               Node* temp = Head;
               for (int i = 1; i < pos - 1; i++)
               {
                   if (temp != NULL && temp!=Tail)
                   {
                       temp = temp->next;
                   }

               }
         if (temp == Tail)
            {
                   newNode->prev = Tail;
                   newNode->next = NULL;
                   Tail->next = newNode;
                   Tail = Tail->next;
                   countNodes++;
            }
     //5. Если предыдущий узел не нулевой, отрегулируем ссылки
         else if (temp != NULL)
            {
                   countNodes++;
                   newNode->next = temp->next;
                   newNode->prev = temp;
                   temp->next = newNode;
                   if (newNode->next != NULL)
                       newNode->next->prev = newNode;
            }
               else {
                    //6. Когда предыдущий узел нулевой
                   cout << "\nThe previous node is null.";
               }
           }


};
//task8
StudentInfo::StudentInfo(string surname,string name,char* studyTicket)
{
    info=std::make_tuple(surname,name,studyTicket);
}

/*	desription	:	добавления отметки по выбранному предмету
            input		:	subjName - название предмета, mark -- оценка
            output		:	0 - оценка добавлена, 1 - нет такого предмета
            author		:
            date		:
        */
int StudentInfo::addMark(const string& subjName, int mark)

{
    if(mark<1)
    {
        cout<<"The mark should be >=1";
        return -1;

    }
    float avg=0;
    auto subjIter = subjMark.find(subjName);
    if(subjIter==subjMark.end())
    {
        return 1;
    }
    subjMark[subjName].first.push_back(mark);
    for (std::list<int>::iterator it = subjMark[subjName].first.begin(); it != subjMark[subjName].first.end(); it++)
    {
       avg+=*it;
    }
    avg=avg/subjMark[subjName].first.size();
    subjMark[subjName].second=avg;
    return 0;
}
/*	desription	:	добавления отметки по выбранному предмету (добавление нового предмета)
    input		:	subjName - название предмета
    output		:	0 - предмет добавлен, 1 - такой предмет уже есть
    author		:
    date		:

*/

int StudentInfo::addSubj(const string& subjName)
{
    auto subjIter = subjMark.find(subjName);
    if(subjIter!=subjMark.end())
    {
        return 1;
    }
    subjMark[subjName]=std::pair<std::list<int> , float >();
    return 0;
}
/*	desription	:	добавления нового предмета
    input		:	subjName - название предмета
    output		:	среднее значение оценки
    author		:
    date		:
*/

float StudentInfo::getAverMark(const string& subjName)
{
    auto subjIter = subjMark.find(subjName);
    if(subjIter==subjMark.end())
    {
        return 0;
    }
    return subjMark[subjName].second;
}
/*	desription	:	вычисления средней оценки по предметам
    input		:	subjName - название предмета
    output		:	среднее значение оценки
    author		:
    date		:
*/

void StudentInfo::writeAllInfoToFile()
{
    ofstream myfile;
            myfile.open("studentinfo.txt");
    string name;
    string surname;
    char* studyTicket;
    std::tie(surname,name,studyTicket)=info;
    myfile<<surname<<" "<<name<<" : "<<studyTicket<<endl;



    for(auto iter =subjMark.begin(); iter != subjMark.end(); iter++)
    {
        auto subjName = (*iter).first;
        myfile<<subjName<<" : ";
        auto markListPair = (*iter).second;
          auto markList =markListPair.first;
        for (auto iterList = markList.begin(); iterList != markList.end(); iterList++)
        {
           myfile << *iterList <<",";
        }
        myfile<< "--" << markListPair.second <<endl;
    }
 myfile.close();




}
/*	desription	:	запись данных в файл формат файла
                        [Фамилия] [имя] : [номер билета]
                            [предмет 1]	:	[оценка 1], [оценка 2],... [оценка N] -- [среднее значение]
                            [предмет 2]	:	[оценка 1], [оценка 2],... [оценка N] -- [среднее значение]
    input		:	subjName - название предмета
    output		:	среднее значение оценки
    author		:
    date		:
*/

void StudentInfo::printInfoStudent()
{
    string name;
    string surname;
    char* studyTicket;
    std::tie(surname,name,studyTicket)=info;
    cout<<surname<<" "<<name<<" : "<<studyTicket<<endl;



    for(auto iter =subjMark.begin(); iter != subjMark.end(); iter++)
    {
        auto subjName = (*iter).first;
        cout<<subjName<<" : ";
        auto markListPair = (*iter).second;
          auto markList =markListPair.first;
        for (auto iterList = markList.begin(); iterList != markList.end(); iterList++)
        {
           cout << *iterList <<",";
        }
        cout<< "--" << markListPair.second <<endl;
    }
}

