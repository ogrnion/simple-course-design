#include "admin.h"
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QIODevice>
#include <QDebug>
#pragma execution_character_set("utf-8")
Admin::Admin(): User("Administrator", "Administrator", "男", "0000"){};

Subject* Admin::addSubject(QString tempNumber, QString tempName, QString tempTeaNumber)
{
    Subject *p = new Subject(tempNumber, tempName, tempTeaNumber, 50);
    return p;
}

void Admin::releaseSubject(Subject * subject)
{
    subject->reload();
    //发布给老师
    QString pathTea = QString("./teacher/").append(subject->tea+".txt");
    QFile fileTeaRead(pathTea);
    fileTeaRead.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream txt(&fileTeaRead);
    QStringList teaList = txt.readAll().split('\n');
    int index = 0;
    for(; teaList[index]!="";index++)
    {
        if(teaList[index][0] != 'A')
            continue;
        else
        {
            QStringList tempList = teaList[index].split(' ');
            if(tempList[0] == subject->number)
            {
                if(subject->mark[0] == -1)
                    teaList[index] = subject->number + ' ' +subject->name + ' ' + "Not Given";
                else
                    teaList[index] = subject->number + ' ' +subject->name + ' ' + "Given";
                break;
            }
        }
    }
    if(teaList[index] == "")
    {
        if(subject->mark[0] == -1)
            teaList[index] = subject->number + ' ' +subject->name + ' ' + "Not Given";
        else
            teaList[index] = subject->number + ' ' +subject->name + ' ' + "Given";
        teaList.append("");
    }
    fileTeaRead.close();
    QFile fileTeaWrite(pathTea);
    fileTeaWrite.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream TXT(&fileTeaWrite);
    for(int i = 0; teaList[i] != ""; i++)
        TXT<<teaList[i]<<'\n';
    fileTeaWrite.close();

    //发布给学生
    QString pathLookFor = "./teacher/TeacherInfo.txt";
    QString teacherName;
    QFile fileLookFor(pathLookFor);
    fileLookFor.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream lookFor(&fileLookFor);
    QStringList temp;
    do
    {
        temp = lookFor.readLine().split(' ');
    }while(temp[0] != subject->tea && temp[0] != "");
    if(temp[0] == subject->tea)
        teacherName = temp[1];
    else
        qDebug()<<"error,no one";
    fileLookFor.close();

    QString pathStu;
    for(int i = 0; subject->stu[i] != " "; i++)
    {
        pathStu = QString("./student/").append(subject->stu[i] + ".txt");
        QFile fileStuRead(pathStu);
        fileStuRead.open(QIODevice::ReadOnly|QIODevice::Text);
        QTextStream txt(&fileStuRead);
        QStringList stuList = txt.readAll().split('\n');
        int index = 0;
        for(; stuList[index]!="";index++)
        {
            if(stuList[index][0] != 'A')
                continue;
            else
            {
                QStringList tempList = stuList[index].split(' ');
                if(tempList[0] == subject->number)
                {
                    stuList[index] = subject->number + ' ' +subject->name + ' ' + subject->tea + ' ' + teacherName + ' ' + QString("%1").arg(subject->mark[i]);
                    break;
                }
            }
        }

        if(stuList[index] == "")
        {
            stuList[index] = subject->number + ' ' +subject->name + ' ' + subject->tea + ' ' + teacherName + ' ' + QString("%1").arg(subject->mark[i]);
            stuList.append("");
        }
        fileStuRead.close();
        QFile fileStuWrite(pathStu);
        fileStuWrite.open(QIODevice::WriteOnly|QIODevice::Text);
        QTextStream TXT(&fileStuWrite);
        for(int i = 0; stuList[i] != ""; i++)
            TXT<<stuList[i]<<'\n';
        fileStuWrite.close();
    }
}

void Admin::releaseMark(Subject *subject)
{
    QString pathLookFor = "./teacher/TeacherInfo.txt";
    QString teacherName;
    QFile fileLookFor(pathLookFor);
    fileLookFor.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream lookFor(&fileLookFor);
    QStringList temp;
    do
    {
        temp = lookFor.readLine().split(' ');
    }while(temp[0] != subject->tea && temp[0] != "");
    if(temp[0] == subject->tea)
        teacherName = temp[1];
    else
        qDebug()<<"error,no one";
    fileLookFor.close();
    for(int i = 0; i < subject->studentsize; i++)
    {
        QString studentPath;
        studentPath = "./student/" + subject->stu[i] + ".txt";
        QFile studentFileRead(studentPath);
        studentFileRead.open(QIODevice::ReadOnly|QIODevice::Text);
        QTextStream studentRead(&studentFileRead);
        QStringList list = studentRead.readAll().split('\n');
        int index = 1;
        while(1)
        {
            if(list[index] == "")
                break;
            QStringList list2 = list[index].split(' ');
            if(list2[0] == subject->number)
            {
                list[index] = subject->number + ' ' + subject->name + ' ' + teacherName + ' ' + QString("%1").arg(subject->mark[i]);
                break;
            }
            index++;
        }
        studentFileRead.close();
        QFile studentFileWrite(studentPath);
        studentFileWrite.open(QIODevice::WriteOnly|QIODevice::Text);
        QTextStream studentWrite(&studentFileWrite);
        for(int i = 0; list[i] != ""; i++)
        {
            studentWrite<<list[i]<<'\n';
        }
        studentFileWrite.close();
    }
}
