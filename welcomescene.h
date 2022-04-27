#ifndef WELCOMESCENE_H
#define WELCOMESCENE_H

#include <QWidget>
#include <QString>
#include <admin.h>
#include <subject.h>
#include "student.h"
#include "teacher.h"
#include "ui_welcomescene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class WelcomeScene; }
QT_END_NAMESPACE

class WelcomeScene : public QWidget
{
    Q_OBJECT

public:

    QString tempNumber, tempPassword, tempName, tempSex,numedit;
    void to_register(QString tempNumber, QString tempName, QString tempSex, QString tempPassword);
    void to_logIn(QString tempNumber, QString tempPassword);
    void to_modifyInfo(QString tempName, QString tempSex, QString tempPassword);
    bool ifExist(QString tempPassword, QString &filePath);
    Admin *Ad;
    Student *Stu;
    Teacher *Tea;
    Subject *Sub;
    WelcomeScene(QWidget *parent = nullptr);
    ~WelcomeScene();

    void to_display(QString tempNumber);
    void searchinf();

private slots:
    //void on_searchButton_clicked();

private:
    Ui::WelcomeScene *ui;
};
#endif // WELCOMESCENE_H
