#ifndef SUBJECT_H
#define SUBJECT_H
#include <QString>

class Subject
{
public:
    QString number;
    QString name;
    QString tea;
    QString classTime;
    int studentsize;
    QString stu[50];
    QString stuName;
    int mark[50];

    Subject(QString, QString, QString, int);
    Subject(QString);
    ~Subject();
    void setTea(QString);
    void addStudent(QString menu);//[],int
    void addMark(QString[], int[]);
    void record();
    void reload();
};

#endif // SUBJECT_H
