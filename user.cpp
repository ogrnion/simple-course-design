#include "user.h"

User::User(QString tempNumber, QString tempName, QString tempSex, QString tempPassword)
{
    number = tempNumber;
    name = tempName;
    sex = tempSex;
    password = tempPassword;
}

void User::modifyInfo(QString tempName, QString tempSex, QString tempPassword)
{
    name = tempName;
    sex = tempSex;
    password = tempPassword;
}
