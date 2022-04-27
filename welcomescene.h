#ifndef WELCOMESCENE_H
#define WELCOMESCENE_H

#include <QWidget>
#include <QString>
#include "student.h"
#include "teacher.h"

QT_BEGIN_NAMESPACE
namespace Ui { class WelcomeScene; }
QT_END_NAMESPACE

class WelcomeScene : public QWidget
{
    Q_OBJECT

public:

    QString tempNumber, tempPassword, tempName, tempSex;
    void to_register(QString tempNumber, QString tempName, QString tempSex, QString tempPassword);
    void to_logIn(QString tempNumber, QString tempPassword);
    void to_modifyInfo(QString tempName, QString tempSex, QString tempPassword);
    bool ifExist(QString tempPassword, QString &filePath);
    Student *Stu;
    Teacher *Tea;
    WelcomeScene(QWidget *parent = nullptr);
    ~WelcomeScene();



private:
    Ui::WelcomeScene *ui;
};
#endif // WELCOMESCENE_H
