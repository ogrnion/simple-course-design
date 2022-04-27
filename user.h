#ifndef USER_H
#define USER_H
#include <QString>

class User
{


public:
    QString number;
    QString name;
    QString sex;
    QString password;

    User(QString, QString, QString, QString);
    void modifyInfo(QString, QString, QString);

};

#endif // USER_H
