#ifndef SUBJECT_H
#define SUBJECT_H
#include <QString>

struct stulist{
    QString stunumber;
    QString stumark;
    struct stulistx* next;
};

class Subject
{
public:
    QString number;
    int studentsize;
    struct stulist;

    Subject(QString);
    void addStudent(QString stunumber);
};

#endif // SUBJECT_H
