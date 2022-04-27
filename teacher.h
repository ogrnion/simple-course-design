#ifndef TEACHER_H
#define TEACHER_H
#include "user.h"
#include "subject.h"

class Teacher : public User
{
public:
    Teacher(QString, QString, QString, QString);
    void modifyInfo(QString, QString, QString);
    void checkSubject();
    void giveMark(Subject *);
    void display(QString *);
};

#endif // TEACHER_H
