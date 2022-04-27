#include "student.h"
#include <QFile>
#include <QTextStream>
#include <QIODevice>
#include <QDebug>

Student::Student(QString tempNumber, QString tempName, QString tempSex, QString tempPassword): User(tempNumber, tempName, tempSex, tempPassword)
{
    QString filePath = "./student/";
    QFile file(filePath.append(tempNumber+".txt"));
    if(! file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        qDebug()<<"warning";
    }
    QTextStream txtWrite(&file);
    txtWrite<<tempNumber<<' '<<tempName<<' '<<tempSex<<' '<<tempPassword<<' ';
    file.close();
}

void Student::modifyInfo(QString tempName, QString tempSex, QString tempPassword)
{
    User::modifyInfo(tempName, tempSex, tempPassword);
    QString filePath = "./student/";
    QFile file(filePath.append(number+".txt"));
    file.open(QIODevice::ReadOnly|QIODevice::WriteOnly|QIODevice::Text);
    QTextStream txtModify(&file);
    QString firstLine = txtModify.readLine();
    QStringList list = firstLine.split(" ");
    qDebug()<<list;
///////

    /////
    file.close();
}
