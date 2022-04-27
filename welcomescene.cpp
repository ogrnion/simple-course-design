#include "welcomescene.h"
#include "ui_welcomescene.h"
#include <QString>
#include <QLineEdit>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QIODevice>
#pragma execution_character_set("utf-8")

WelcomeScene::WelcomeScene(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WelcomeScene)
{
    ui->setupUi(this);

    {
        Ad = new Admin();
        ui->stackedWidget->setCurrentIndex(0);
        ui->page1_modify->hide();
        ui->page1_cancel->hide();
///
        ui->subjectName->hide();
        ui->subjectNumber->hide();
        ui->subjectTeaNumber->hide();
        //ui->label_subName->hide();
        ui->page2_StuNumberChoose->hide();
        ui->page2_StuNumberConfirm->hide();
        //ui->pushButton_chooseSub->hide();
        //ui->page2_SubNumberChoose->hide();
        ui->page7_classtea->hide();
        ui->page7_showteaname->hide();
        ///

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
//新建课程
        connect(ui->page2_subject, &QPushButton::clicked, [=](){
            ui->stackedWidget->setCurrentIndex(8);
            ui->subjectName->show();
            ui->subjectNumber->show();
            ui->subjectTeaNumber->show();
            ui->subjectConfirm->show();
            ui->subjectSelectStu->setEnabled(false);
            ui->subjectRelease->setEnabled(false);
            //ui->label_subNum->show();
            //ui->label_teaNum->show();
            //ui->label_subName->show();
        });
        connect(ui->subjectConfirm, &QPushButton::clicked, [=](){
            QString subjectName = ui->subjectName->text();
            QString subjectNumber = ui->subjectNumber->text();
            QString subjectTeaNumber = ui->subjectTeaNumber->text();
            Sub = Ad->addSubject(subjectNumber, subjectName, subjectTeaNumber);
            ui->subjectConfirm->setEnabled(false);
            ui->subjectSelectStu->setEnabled(true);
        });
        connect(ui->subjectSelectStu, &QPushButton::clicked, [=](){
            ui->page2_StuNumberChoose->show();
            ui->page2_StuNumberConfirm->show();
            ui->subjectName->setEnabled(false);
            ui->subjectNumber->setEnabled(false);
            ui->subjectTeaNumber->setEnabled(false);

            ui->subjectSelectStu->setEnabled(false);
            QFile stuInfo("./student/StudentInfo.txt");
            if(!stuInfo.open(QIODevice::ReadOnly|QIODevice::Text))
                qDebug()<<"warning";
            QTextStream stuRead(&stuInfo);
            QStringList tempListStu;
            do{
                tempListStu = stuRead.readLine().split(' ');
                if(tempListStu[0] == "")
                    break;
                qDebug()<<tempListStu;
                ui->page2_StuNumberChoose->addItem(tempListStu[0]);
            }while(1);
            stuInfo.close();

            connect(ui->page2_StuNumberConfirm,&QPushButton::clicked, [=](){
                QString stuChosen=ui->page2_StuNumberChoose->currentText();
                qDebug()<<stuChosen;
                Sub->addStudent(stuChosen);
                ui->subjectRelease->setEnabled(true);
            });
            Sub->record();
        });

        connect(ui->page2_mark, &QPushButton::clicked, [=](){
            //通过列表选课程发布分数
            ui->stackedWidget->setCurrentIndex(9);
            //ui->page2_SubNumberChoose->show();
            //ui->pushButton_chooseSub->show();
            QFile classInfo("./subject/SubjectInfo.txt");
            if(!classInfo.open(QIODevice::ReadOnly|QIODevice::Text))
                qDebug()<<"warning";
            QTextStream subRead(&classInfo);
            QStringList tempListSub;
            do
            {
                tempListSub = subRead.readLine().split(' ');
                if(tempListSub[0] == "")
                    break;
                ui->page9_SubNumberChoose->addItems(tempListSub);
            }while(1);
            classInfo.close();
        });
        connect(ui->pushButton_chooseSub,&QPushButton::clicked, [=](){
            QString subChosen=ui->page9_SubNumberChoose->currentText();

            Sub = new Subject(subChosen);
            //ui->pushButton_chooseSubFinish->show();
            Ad->releaseMark(Sub);
        });

        connect(ui->subjectRelease, &QPushButton::clicked, [=](){
            Ad->releaseSubject(Sub);
            ui->subjectName->setText("");
            ui->subjectNumber->setText("");
            //ui->subjectTeaNumber->setText("");
            ui->page2_StuNumberChoose->setCurrentIndex(0);
            ui->subjectRelease->setEnabled(true);
            ui->subjectName->setEnabled(true);
            ui->subjectNumber->setEnabled(true);
            ui->subjectTeaNumber->setEnabled(true);

            ui->page2_StuNumberChoose->hide();
            ui->page2_StuNumberConfirm->hide();
        });

        connect(ui->page2_manage, &QPushButton::clicked, [=](){
            ui->stackedWidget->setCurrentIndex(6);
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

        connect(ui->page3_table, &QPushButton::clicked, [=](){
            Tea->checkSubject();
            ui->stackedWidget->setCurrentIndex(5);
            tempNumber=Tea->number;
            to_display(tempNumber);
        });
        connect(ui->page4_table, &QPushButton::clicked, [=](){
            Stu->checkSubject();
            ui->stackedWidget->setCurrentIndex(5);
            tempNumber=Stu->number;
            to_display(tempNumber);
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

        connect(ui->page5_back, &QPushButton::clicked, [=](){
            if(tempNumber[0] == '9')
                ui->stackedWidget->setCurrentIndex(4);
            else// if(tempNumber[0] == '1')
                ui->stackedWidget->setCurrentIndex(3);
        });
        connect(ui->searchButton , &QPushButton::clicked, [=](){
            QString numedit = ui->numberEdit->text();
            QString Path;
            if(numedit[0] == '9')
            {
                Path = "./student/"+numedit+".txt";
                QFile file(Path);
                file.open(QIODevice::ReadOnly|QIODevice::Text);
                QTextStream subjectRead(&file);
                //subjectRead.readLine();
                QStringList tempList;
                tempList = subjectRead.readLine().split(' ');
                if(tempList[0] != "")
                {
                    ui->showname->setText(tempList[1]);
                    ui->showpassward->setText(tempList[3]);
                }
            }
            else if(numedit[0] == '1')
            {
                Path = "./teacher/" +numedit+ ".txt";
                QFile file(Path);
                if (file.exists())
                {
                    file.open(QIODevice::ReadOnly|QIODevice::Text);
                    QTextStream subjectRead(&file);
                    QStringList tempList;
                    tempList = subjectRead.readLine().split(' ');
                    if(tempList[0] != " ")
                    {
                        ui->showname->setText(tempList[1]);qDebug()<<tempList[1];
                        ui->showpassward->setText(tempList[3]);
                    }
                }else
                    QMessageBox::information(this, "提示", "该用户不存在");
            }else
                QMessageBox::information(this, "提示", "该用户不存在");
            connect(ui->page6_delButton, &QPushButton::clicked, [=](){
                switch( QMessageBox::information( this, tr("删除文件"),
                                  tr("确定删除该用户吗？"), tr("是"), tr("否"), 0, 1 ) )
                {case 0:{
                    QFile::remove(Path);
                    QMessageBox::warning(this,"删除文件","删除成功！");
                    break;}
                 case 1:
                    break;
                }
                ui->showname->clear();
                ui->showpassward->clear();
            });
        });

        connect(ui->page2_lookinf, &QPushButton::clicked, [=](){
            ui->stackedWidget->setCurrentIndex(7);
            ui->page7_showname->setText("NULL");
            ui->page7_shownumber->setText("NULL");
            ui->page7_showteaname->setText("NULL");
            ui->page7_infEdit->clear();
        });
        connect(ui->page3_lookinf, &QPushButton::clicked, [=](){
            ui->stackedWidget->setCurrentIndex(7);
            ui->page7_showname->setText("NULL");
            ui->page7_shownumber->setText("NULL");
            ui->page7_showteaname->setText("NULL");
            ui->page7_infEdit->clear();
        });
        connect(ui->page4_lookinf, &QPushButton::clicked, [=](){
            ui->stackedWidget->setCurrentIndex(7);
            ui->page7_showname->setText("NULL");
            ui->page7_shownumber->setText("NULL");
            ui->page7_showteaname->setText("NULL");
            ui->page7_infEdit->clear();
        });
        connect(ui->page7_searchButton, &QPushButton::clicked, [=](){
            searchinf();
            //QString gender = ui->comboBox->currentIndex()==0 ? "男" : "女";
            //ui->stackedWidget->setCurrentIndex(7);
        });

        connect(ui->page2_back0, &QPushButton::clicked, [=](){
            ui->stackedWidget->setCurrentIndex(0);
            ui->page0_number->clear();
            ui->page0_password->clear();
        });
        connect(ui->page3_back0, &QPushButton::clicked, [=](){
            ui->stackedWidget->setCurrentIndex(0);
            ui->page0_number->clear();
            ui->page0_password->clear();
        });
        connect(ui->page4_back0, &QPushButton::clicked, [=](){
            ui->stackedWidget->setCurrentIndex(0);
            ui->page0_number->clear();
            ui->page0_password->clear();
        });
        connect(ui->page7_back, &QPushButton::clicked, [=](){
            if(tempNumber[0] == '9')
                ui->stackedWidget->setCurrentIndex(4);
            else if(tempNumber[0] == '1')
                ui->stackedWidget->setCurrentIndex(3);
            else
                ui->stackedWidget->setCurrentIndex(2);
        });
        connect(ui->page6_back, &QPushButton::clicked, [=](){
            ui->numberEdit->clear();
            ui->showname->clear();
            ui->showpassward->clear();
            ui->stackedWidget->setCurrentIndex(2);
        });
        connect(ui->page8_back, &QPushButton::clicked, [=](){
            ui->numberEdit->clear();
            ui->stackedWidget->setCurrentIndex(2);
        });
        connect(ui->page9_back, &QPushButton::clicked, [=](){
            //ui->numberEdit->clear();
            ui->stackedWidget->setCurrentIndex(2);
        });
    }
    QStringList headers;
    headers<<"课程"<<"学生名单"<<"成绩";
    ui->treeWidget->setHeaderLabels(headers);
}


WelcomeScene::~WelcomeScene()
{
    delete ui;
}

void WelcomeScene::searchinf()
{
    int infbox = ui->searchcomboBox->currentIndex();
    QString inf;
    inf=ui->page7_infEdit->text();
    QString Path;
    if(infbox==0)
    {
        if(inf[0] == '1')
        {
            qDebug()<<inf;
            ui->page7_numberlabel->setText("工号");
            Path = "./teacher/" +inf+ ".txt";
            QFile file(Path);
            file.open(QIODevice::ReadOnly|QIODevice::Text);
            qDebug()<<tempNumber;
            QTextStream Read(&file);
            QStringList tempList;
            tempList = Read.readLine().split(' ');
            qDebug()<<tempList;
            ui->page7_showname->setText(tempList[1]);
            ui->page7_shownumber->setText(tempList[0]);
        }
        else if(inf[0] == '9')
        {
            qDebug()<<inf;
            ui->page7_numberlabel->setText("学号");
            Path = "./student/" +inf+ ".txt";
            QFile file(Path);
            file.open(QIODevice::ReadOnly|QIODevice::Text);
            QTextStream Read(&file);
            QStringList tempList;
            tempList = Read.readLine().split(' ');
            qDebug()<<tempList;
            ui->page7_showname->setText(tempList[1]);
            ui->page7_shownumber->setText(tempList[0]);
        }
        else
            QMessageBox::critical(this, "错误", "学号（工号）格式错误", "确定");
    }
    if(infbox==1)
    {
        QFile files("./student/Studentinfo.txt");
        files.open(QIODevice::ReadOnly|QIODevice::Text);
        QTextStream Reads(&files);
        QStringList tempLists;
        QString tps=0;
        do{
            tempLists = Reads.readLine().split(' ');
            if(tempLists[0] == "")
                break;
            qDebug()<<tempLists[1];
            if(tempLists[1] ==inf)
            {
                tps=1;
                ui->page7_numberlabel->setText("学号");
                ui->page7_showname->setText(tempLists[1]);
                ui->page7_shownumber->setText(tempLists[0]);
            }
        }while(1);
        //files.close();
        QFile filet("./teacher/Teacherinfo.txt");
        filet.open(QIODevice::ReadOnly|QIODevice::Text);
        QTextStream Readt(&filet);
        QStringList tempListt;
        QString tpt=0;
        do{
            tempListt = Readt.readLine().split(' ');
            if(tempListt[0] == "")
                break;
            qDebug()<<tempListt[1];
            if(tempListt[1] ==inf)
            {
                tpt=1;
                ui->page7_numberlabel->setText("工号");
                ui->page7_showname->setText(tempListt[1]);
                ui->page7_shownumber->setText(tempListt[0]);
            }
        }while(1);
        if (tps !=1 && tpt !=1)
            QMessageBox::critical(this, "错误", "请检查输入的姓名", "确定");
    }
    else if(infbox==2)
    {
        ui->page7_numberlabel->setText("课序号");
        ui->page7_classtea->show();
        ui->page7_showteaname->show();
        QFile file("./subject/subjectinfo.txt");
        file.open(QIODevice::ReadOnly|QIODevice::Text);
        QTextStream Read(&file);
        QStringList tempList;
        QString tp=0;
        do{
            tempList = Read.readLine().split(' ');
            if(tempList[0] == "")
                break;
            qDebug()<<tempList[1];
            if(tempList[1] ==inf)
            {
                tp=1;
                ui->page7_showname->setText(tempList[1]);
                ui->page7_shownumber->setText(tempList[0]);
                QString teaPath = "./teacher/"+tempList[2]+".txt";
                QFile teaFile(teaPath);
                teaFile.open(QIODevice::ReadOnly|QIODevice::Text);
                QTextStream Read(&teaFile);
                QStringList temp;
                temp = Read.readLine().split(' ');
                qDebug()<<temp;
                ui->page7_showteaname->setText(temp[1]);
            }
        }while(1);
        if (tp !=1)
            QMessageBox::critical(this, "错误", "请检查课程名", "确定");
    }
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
            txtWrite<<tempNumber<<' '<<tempName<<'\n';
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
            file.close();
        }
    }
}

void WelcomeScene::to_logIn(QString tempNumber, QString tempPassword)
{
    if(tempNumber == "A"&&tempPassword == "0000")
    {
        ui->stackedWidget->setCurrentIndex(2);
    }else if(tempNumber[0]!='1' && tempNumber[0]!='9')
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
    else if(tempNumber[0] == '1')
    {
        filePath = "./teacher/TeacherInfo.txt";
    }
    else
    {
        filePath = "./subject/SubjectInfo.txt";
    };
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
        QString tempString = lookFor.readLine();
        QStringList list = tempString.split(' ');
        temp = list[0];
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

void WelcomeScene::to_display(QString tempNumber)
{
    ui->treeWidget->clear();
    if(tempNumber[0] =='1')
    {
        QString Path;
        Path = "./teacher/" + tempNumber + ".txt";
        QFile file(Path);
        file.open(QIODevice::ReadOnly|QIODevice::Text);
        qDebug()<<tempNumber;
        QTextStream subjectRead(&file);
        subjectRead.readLine();
        QStringList tempList;
        do{
            tempList = subjectRead.readLine().split(' ');
            if(tempList[0] == "")
                break;
            QTreeWidgetItem *topItem2 = new QTreeWidgetItem(ui->treeWidget);
            qDebug()<<tempList[1];
            topItem2->setText(0,tempList[1]);//显示一级为课程名
            topItem2->setCheckState(0,Qt::Checked);
            ui->treeWidget->addTopLevelItem(topItem2);
            qDebug()<<"学生名单：";
            QString subjectPath = "./subject/"+tempList[0]+".txt";
            QFile subjectFile(subjectPath);
            subjectFile.open(QIODevice::ReadOnly|QIODevice::Text);
            QTextStream Read(&subjectFile);
            Read.readLine();
            QStringList temp;
            while(1)
            {
                temp = Read.readLine().split(' ');
                if(temp[0] == "")
                       break;
                qDebug()<<temp[0]<<temp[1];
                QTreeWidgetItem *item21 = new QTreeWidgetItem(topItem2);
                item21->setText(1,temp[0]);//显示二级为学生名
                item21->setText(2,temp[1]);//显示三级为成绩
            }
            subjectFile.close();
        }while(1);
        file.close();
    }
    else {
        QStringList headers;
        headers<<"课程"<<"老师"<<"成绩";
        ui->treeWidget->setHeaderLabels(headers);
        QString Path;
        Path = "./student/" + tempNumber + ".txt";
        QFile file(Path);
        file.open(QIODevice::ReadOnly|QIODevice::Text);
        qDebug()<<tempNumber;
        QTextStream subjectRead(&file);
        subjectRead.readLine();
        QStringList tempList;
        do{
            tempList = subjectRead.readLine().split(' ');
            if(tempList[0] == "")
                break;
            QTreeWidgetItem *topItem2 = new QTreeWidgetItem(ui->treeWidget);
            qDebug()<<tempList[1];
            topItem2->setText(0,tempList[1]);//显示一级为课程名
            topItem2->setCheckState(0,Qt::Checked);
            topItem2->setText(1,tempList[2]);//显示二级为成绩
            if(tempList[3] != "-1")
            {
                topItem2->setText(2,tempList[3]);//显示三级为成绩
            }else{topItem2->setText(2,"无成绩");
            }
        }while(1);
    }
}
