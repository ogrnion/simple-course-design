#include "teacher.h"
#include "ui_welcomescene.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QIODevice>
#include <QDebug>
#pragma execution_character_set("utf-8")
Teacher::Teacher(QString tempNumber, QString tempName, QString tempSex, QString tempPassword): User(tempNumber, tempName, tempSex, tempPassword)
{
    QString filePath = "./teacher/";
    QFile file(filePath.append(tempNumber+".txt"));
    if(! file.open(QIODevice::ReadWrite|QIODevice::Text))
    {
        qDebug()<<"warning";
    }
    QTextStream txtWrite(&file);
    txtWrite<<tempNumber<<' '<<tempName<<' '<<tempSex<<' '<<tempPassword<<'\n';
    file.close();
}

void Teacher::checkSubject()
{
    QString filePath = "./teacher/";
    QFile file(filePath.append(number+".txt"));
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream subjectRead(&file);
    subjectRead.readLine();
    QStringList tempList;
    do
    {
        tempList = subjectRead.readLine().split(' ');
        if(tempList[0] == "")
            break;
        qDebug()<<"课序号"<<tempList[0]<<"课程名"<<tempList[1];
        qDebug()<<"学生名单：";
        QString subjectPath = "./subject/"+tempList[0]+".txt";
        QFile subjectFile(subjectPath);
        subjectFile.open(QIODevice::ReadOnly|QIODevice::Text);
        QTextStream Read(&subjectFile);
        Read.readLine();
        QStringList temp;
        while(1)
        {
            temp = Read.readLine().split(' ');
            if(temp[0] == "")
                break;
            qDebug()<<temp[0];
        }
        subjectFile.close();
    }while(1);
    file.close();
}

void Teacher::giveMark(Subject *subject)
{
    subject->reload();
    //记得修改
    subject->mark[0] = 100;
    subject->mark[1] = 96;

    QString teacherPath;
    teacherPath = "./teacher/" + number + ".txt";
    QFile teacherFileRead(teacherPath);
    teacherFileRead.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream teacherRead(&teacherFileRead);
    QString allData = teacherRead.readAll();
    QStringList list = allData.split('\n');
    int index = 1;
    QStringList tempList;
    while(list[index] != "")
    {
        tempList = list[index].split(' ');
        if(tempList[0] == subject->number)
        {
            list[index] = subject->number + ' ' + subject->name + ' ' + "Given";
            break;
        }
    }
    teacherFileRead.close();
    QFile teacherFileWrite(teacherPath);
    teacherFileWrite.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream teacherWrite(&teacherFileWrite);
    for(int i = 0; list[i] != ""; i++)
    {
        teacherWrite<<list[i]<<'\n';
    }
    teacherFileWrite.close();
    subject->record();
//    QString subjectPath;
//    subjectPath = "./subject/" + subject->number + ".txt";
//    QFile subjectFileWrite(subjectPath);
//    subjectFileWrite.open(QIODevice::WriteOnly|QIODevice::Text);
//    QTextStream subjectWrite(&subjectFileWrite);
//    subjectWrite<<subject->number<<' '<<subject->name<<' '<<subject->tea<<'\n';
//    subject->addMark(subject->stu, subject->mark);
//    subjectFileWrite.close();
}

void Teacher::modifyInfo(QString tempName, QString tempSex, QString tempPassword)
{
    User::modifyInfo(tempName, tempSex, tempPassword);
    QString filePath = "./teacher/";
    filePath = filePath.append(number+".txt");
    QFile fileRead(filePath);
    fileRead.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream txtRead(&fileRead);
    QString allData = txtRead.readAll();
    QStringList list = allData.split('\n');
    list[0] = number + ' ' + tempName + ' ' + tempSex + ' ' + tempPassword;
    fileRead.close();
    QFile fileWrite(filePath);
    fileWrite.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream txtWrite(&fileWrite);
    for(int i = 0; list[i] != ""; i++)
    {
        txtWrite<<list[i]<<'\n';
    }
    fileWrite.close();
}
