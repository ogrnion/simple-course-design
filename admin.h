#ifndef ADMIN_H
#define ADMIN_H
#include "user.h"
#include "subject.h"

class Admin : public User
{
public:
    Admin();
    Subject* addSubject(QString tempName, QString tempNumber, QString tempTeaNumber);
    void releaseSubject(Subject *);
    void releaseMark(Subject *);
    void sendMark(QString filename,Subject *);
};

#endif // ADMIN_H
