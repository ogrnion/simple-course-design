#ifndef STUDENT_H
#define STUDENT_H
#include "user.h"

class Student : public User
{
public:
    Student(QString, QString, QString, QString);
    void modifyInfo(QString, QString, QString);
};

#endif // STUDENT_H
