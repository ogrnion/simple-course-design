#ifndef TEACHER_H
#define TEACHER_H
#include "user.h"

class Teacher : public User
{
public:
    Teacher(QString, QString, QString, QString);
    void modifyInfo(QString, QString, QString);
};

#endif // TEACHER_H
