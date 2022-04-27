#include "welcomescene.h"
#include "ui_welcomescene.h"
#include <QString>
#include <QLineEdit>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QMessageBox>
#include <QIODevice>
#include "student.h"
#include "teacher.h"
#pragma execution_character_set("utf-8")

WelcomeScene::WelcomeScene(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WelcomeScene)
{
    ui->setupUi(this);

    {
        ui->stackedWidget->setCurrentIndex(0);
        ui->page1_modify->hide();
        ui->page1_cancel->hide();
        connect(ui->page0_login, &QPushButton::clicked, [=](){
            tempNumber = ui->page0_number->text();
            tempPassword = ui->page0_password->text();
            to_logIn(tempNumber, tempPassword);
        });
        connect(ui->page0_register, &QPushButton::clicked, [=](){
            ui->page0_number->setText(NULL);
            ui->page0_password->setText(NULL);
            ui->stackedWidget->setCurrentIndex(1);
        });
        connect(ui->page1_register, &QPushButton::clicked, [=](){
            tempName = ui->page1_name->text();
            tempSex = ui->page1_sex->currentText();
            tempNumber = ui->page1_number->text();
            tempPassword = ui->page1_password1->text();
            if(ui->page1_password1->text() != ui->page1_password2->text())
                QMessageBox::critical(this, "错误", "两次输入的密码不一致", "确定");
            else
                to_register(tempNumber, tempName, tempSex, tempPassword);
        });
        connect(ui->page1_login, &QPushButton::clicked, [=](){
            ui->page1_name->setText(NULL);
            ui->page1_sex->setCurrentIndex(0);
            ui->page1_password1->setText(NULL);
            ui->page1_password2->setText(NULL);
            ui->stackedWidget->setCurrentIndex(0);
        });
        connect(ui->page3_modify, &QPushButton::clicked, [=](){
            ui->page1_number->setText(Tea->number);
            ui->page1_number->setEnabled(false);
            ui->page1_name->setText(Tea->name);
            if(Tea->sex == "男")
                ui->page1_sex->setCurrentIndex(0);
            else
                ui->page1_sex->setCurrentIndex(1);
            ui->page1_password1->setText(NULL);
            ui->page1_password2->setText(NULL);
            ui->page1_register->hide();
            ui->page1_login->hide();
            ui->page1_modify->show();
            ui->page1_cancel->show();
            ui->stackedWidget->setCurrentIndex(1);
        });
        connect(ui->page4_modify, &QPushButton::clicked, [=](){
            ui->page1_number->setText(Stu->number);
            ui->page1_number->setEnabled(false);
            ui->page1_name->setText(Stu->name);
            if(Stu->sex == "男")
                ui->page1_sex->setCurrentIndex(0);
            else
                ui->page1_sex->setCurrentIndex(1);
            ui->page1_password1->setText(NULL);
            ui->page1_password2->setText(NULL);
            ui->page1_register->hide();
            ui->page1_login->hide();
            ui->page1_modify->show();
            ui->page1_cancel->show();
            ui->stackedWidget->setCurrentIndex(1);
        });
        connect(ui->page1_modify, &QPushButton::clicked, [=](){
            if(ui->page1_password1->text() != ui->page1_password2->text())
                QMessageBox::critical(this, "错误", "两次输入的密码不一致", "确定");
            else
            {
                QMessageBox::information(this, "提示", "修改成功");
                if(tempNumber[0] == '9')
                    Stu->modifyInfo(ui->page1_name->text(), ui->page1_sex->currentText(), ui->page1_password1->text());
                else
                    Tea->modifyInfo(ui->page1_name->text(), ui->page1_sex->currentText(), ui->page1_password1->text());
            }
        });
        connect(ui->page1_cancel, &QPushButton::clicked, [=](){
            if(tempNumber[0] == '9')
                ui->stackedWidget->setCurrentIndex(4);
            else
                ui->stackedWidget->setCurrentIndex(3);
            ui->page1_number->setEnabled(true);
            ui->page1_number->setText(NULL);
            ui->page1_name->setText(NULL);
            ui->page1_sex->setCurrentIndex(0);
            ui->page1_password1->setText(NULL);
            ui->page1_password2->setText(NULL);
        });
    }
}


WelcomeScene::~WelcomeScene()
{
    delete ui;
}

void WelcomeScene::to_register(QString tempNumber, QString tempName, QString tempSex, QString tempPassword)
{
    if(tempNumber[0]!='1' && tempNumber[0]!='9')
        QMessageBox::critical(this, "错误", "学号（工号）格式错误", "确定");
    else
    {
        QString path;
        if(ifExist(tempNumber, path))
        {
            QMessageBox::critical(this, "错误", "该用户已存在", "确定");
        }
        else
        {
            QMessageBox::information(this, "提示", "注册成功，已自动登录");
            QFile file(path);
            file.open(QIODevice::Append);
            QTextStream txtWrite(&file);
            txtWrite<<tempNumber<<' ';
            if(tempNumber[0] == '9')
            {
                Stu = new Student(tempNumber, tempName, tempSex, tempPassword);
                ui->stackedWidget->setCurrentIndex(4);
            }
            else if(tempNumber[0] == '1')
            {
                Tea = new Teacher(tempNumber, tempName, tempSex, tempPassword);
                ui->stackedWidget->setCurrentIndex(3);
            }
            else;
            file.close();
        }
    }
}

void WelcomeScene::to_logIn(QString tempNumber, QString tempPassword)
{
    if(tempNumber[0]!='1' && tempNumber[0]!='9')
        QMessageBox::critical(this, "错误", "学号（工号）格式错误", "确定");
    else
    {
        QString path;
        if(!ifExist(tempNumber, path))
        {
            QMessageBox::critical(this, "错误", "该用户不存在", "确定");
        }else
        {
            if(tempNumber[0] == '9')
                path = "./student/";
            else
                path = "./teacher/";
            QFile file(path.append(tempNumber+".txt"));
            file.open(QIODevice::ReadOnly|QIODevice::Text);
            QTextStream txtRead(&file);
            QString tempA, tempB, tempC, tempD;
            txtRead>>tempA>>tempB>>tempC>>tempD;
            if(tempD == tempPassword)
            {
                tempName = tempB;
                tempSex = tempC;
                if(tempA[0] == '9')
                    Stu = new Student(tempNumber, tempName, tempSex, tempPassword);
                else
                    Tea = new Teacher(tempNumber, tempName, tempSex, tempPassword);
                QMessageBox::information(this, "提示", "登陆成功");
                if(tempNumber[0] == '1')
                    ui->stackedWidget->setCurrentIndex(3);
                else
                    ui->stackedWidget->setCurrentIndex(4);
            }
            else
                QMessageBox::critical(this, "密码错误", "若忘记密码，请联系管理员", "确定");
            file.close();
        }
    }
}

void WelcomeScene::to_modifyInfo(QString tempName, QString tempSex, QString tempPassword)
{
    Stu->modifyInfo(tempName, tempSex, tempPassword);
}

bool WelcomeScene::ifExist(QString tempNumber, QString &filePath)
{
    if(tempNumber[0] == '9')
    {
        filePath = "./student/StudentInfo.txt";
    }
    else
    {
        filePath = "./teacher/TeacherInfo.txt";
    }
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly|QIODevice::WriteOnly|QIODevice::Text))
    {
        QMessageBox::critical(this, "错误", "文件打开失败", "确定");
        return false;
    }
    QTextStream lookFor(&file);
    QString temp;
    do
    {
        lookFor>>temp;
    }while(tempNumber != temp && temp != "");
    if(tempNumber == temp)
    {
        file.close();
        return true;
    }
    else
    {
        file.close();
        return false;
    }
}

