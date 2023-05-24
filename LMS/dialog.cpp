#include "dialog.h"
#include "./ui_dialog.h"
#include<QString>
#include<QMessageBox>
#include"course.h"
#include<QDebug>
#include<iostream>
#include<string>
int id=1;
int index=0;
int lol=0;
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{

    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    ui->comboBox_input_hour->setEnabled(false);
    usernamePassword.push_back(std::make_pair("admin","admin"));


    QTableWidget *table=ui->tableWidget_Showall_Stud;
    table->setColumnCount(7);
    table->setHorizontalHeaderLabels({"firstname","lastname","Email","Mobile","Grade","Age","ID"});
    QTableWidget *studtable=ui->tableWidget_stud1;
    studtable->setColumnCount(2);
    studtable->setHorizontalHeaderLabels({"Course","Grade"});
    QTableWidget*coursestable=ui->tableWidget_courses;
    coursestable->setColumnCount(3);
    coursestable->setHorizontalHeaderLabels({"Students","Grades","Students ID"});
    QTableWidget*professortable=ui->tableWidget_displayprofessor;
    professortable->setColumnCount(1);
    QTableWidget*courseprof=ui->tableWidget_courseProf;
    courseprof->setColumnCount(1);
    courseprof->setHorizontalHeaderLabels({"Professor Name"});
    professortable->setHorizontalHeaderLabels({"Courses"});
    QComboBox*box=ui->comboBox_input_day;



    QString sun="sunday";
    QString mon="monday";
    QString tues="tuesday";
    QString wed="wednesday";
    QString thur="thursday";
    QString fri="friday";
    QString satur="saturday";
    //box->addItem(sun);
    //box->addItem(mon);
    //box->addItem(tues);
    //box->addItem(wed);
    //box->addItem(thur);
    //box->addItem(fri);
    //box->addItem(satur);

    QComboBox*lechall=ui->comboBox_input_lecturehall;
    QString first="3201";
    QString second="3101";
    QString third="3001";
    lechall->addItem(first);
    lechall->addItem(second);
    lechall->addItem(third);

    timeSlots.resize(3);
    for (int i = 0; i < 3; ++i) {
    for(int j = 8;j < 18;j+=2){
           timeSlots[i]["sunday"].insert(j);
           timeSlots[i]["monday"].insert(j);
           timeSlots[i]["tuesday"].insert(j);
           timeSlots[i]["wednesday"].insert(j);
           timeSlots[i]["thursday"].insert(j);

       }
    }


    for(auto& i:timeSlots[0]){
        QString day = QString::fromStdString(i.first);
        box->addItem(day);
    }

    QComboBox*courseHour=ui->comboBox_input_hour;
    //to add courses to combox in choose course to be added to student

    QString timeinterval1="8 AM - 10 AM";
    QString timeinterval2="10 AM - 12 AM";
    QString timeinterval3="12 AM - 2 PM";
    QString timeinterval4="2 PM - 4 PM";
    QString timeinterval5="4 PM - 6 PM";
   // courseHour->addItem(timeinterval1);
   // courseHour->addItem(timeinterval2);
   // courseHour->addItem(timeinterval3);
   // courseHour->addItem(timeinterval4);
   // courseHour->addItem(timeinterval5);

    QString hardCodedCoursename1="Data Structures";//3201,tuesday//timeinterval2
    QString hardcodedcoursename2="Physiology&Anatomy";//3101,monday//timeinterval1
    QString hardcodedcoursename3="Electronics";//3001,thursday//timeinterval3
    QString hardcodedCoursecode1="CMP2241";
    QString hardcodedcoursecode2="SBE2120";
    QString hardcodedcoursecode3="ELC2241";
    timeSlots[0]["tuesday"].erase(10);
    timeSlots[1]["monday"].erase(8);
    timeSlots[2]["thursday"].erase(12);


   // for(auto i:timeSlots[0]["sunday"]){
     //   int hr = i;
     //   QString timeInterval = QString::number((hr%12)+(12*(hr%12==0)));
     //   if(hr >= 12)
     //       timeInterval+=" PM - ";
    //    else
    //        timeInterval+=" AM - ";

    //    timeInterval+=QString::number((hr%12)+2);
    //    if(hr+2 >= 12)
     //       timeInterval+=" PM";
     //   else
      //      timeInterval+=" AM";
        //courseHour->addItem(timeInterval);
    // }

    int hour1=10;
    int hour2=8;
    int hour3=12;

    QComboBox*chooseCourse=ui->comboBox_choosecourse_addstud;
    chooseCourse->addItem(hardCodedCoursename1);
    chooseCourse->addItem(hardcodedcoursename2);
    chooseCourse->addItem(hardcodedcoursename3);

    QComboBox*course=ui->comboBox_searchcourse;
    course->addItem(hardCodedCoursename1);
    course->addItem(hardcodedcoursename2);
    course->addItem(hardcodedcoursename3);

    Course newcourse1(hardCodedCoursename1,hardcodedCoursecode1,first,tues,hour1);
    registeredCourses.push_back(newcourse1);
    Course newcourse2(hardcodedcoursename2,hardcodedcoursecode2,second,mon,hour2);
    registeredCourses.push_back(newcourse2);
    Course newcourse3(hardcodedcoursename3,hardcodedcoursecode3,third,thur,hour3);
    registeredCourses.push_back(newcourse3);

    QComboBox*chooseCourseToProfessor=ui->comboBox_choose_course_addprof;
    chooseCourseToProfessor->addItem(hardCodedCoursename1);
    chooseCourseToProfessor->addItem(hardcodedcoursename2);
    chooseCourseToProfessor->addItem(hardcodedcoursename3);

    QRegularExpression rx("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b",QRegularExpression::CaseInsensitiveOption);
    ui->lineEdit_input_emailstud->setValidator(new QRegularExpressionValidator(rx,this));

    connect(ui->lineEdit_input_emailstud,&QLineEdit::textChanged,this,&Dialog::checkInput);

    ui->lineEdit_input_email_prof->setValidator(new QRegularExpressionValidator(rx,this));

    connect(ui->lineEdit_input_email_prof,&QLineEdit::textChanged,this,&Dialog::checkInput2);

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::checkInput(){
    if(ui->lineEdit_input_emailstud->hasAcceptableInput()){
        ui->lineEdit_input_emailstud->setStyleSheet("QLineEdit {color: rgb(255, 255, 255); border-width: 2px; border-style: solid;border-color: rgb(255, 255, 255); border-radius: 20px; padding:5px;}");
    }
    else{
        ui->lineEdit_input_emailstud->setStyleSheet("QLineEdit {color: red; border-width: 2px; border-style: solid;border-color: rgb(255, 255, 255); border-radius: 20px; padding:5px;}");
    }
}

void Dialog::checkInput2(){
    if(ui->lineEdit_input_email_prof->hasAcceptableInput()){
        ui->lineEdit_input_email_prof->setStyleSheet("QLineEdit {color: rgb(255, 255, 255); border-width: 2px; border-style: solid;border-color: rgb(255, 255, 255); border-radius: 20px; padding:5px;}");
    }
    else{
         ui->lineEdit_input_email_prof->setStyleSheet("QLineEdit {color: red; border-width: 2px; border-style: solid;border-color: rgb(255, 255, 255); border-radius: 20px; padding:5px;}");
    }
}


void Dialog::on_pushButton_clicked()
{
    bool in=true;
    QString username2=ui->lineEdit_username->text();
    QString password2=ui->lineEdit_password->text();
    for(int i = 0; i < usernamePassword.size(); i++){
        if(username2==usernamePassword[i].first && password2==usernamePassword[i].second){
            ui->stackedWidget->setCurrentIndex(1);
            ui->lineEdit_username->setText("");
            ui->lineEdit_password->setText("");
            in=false;
        }
    }
    if(in){
        QMessageBox mb("Login", "Incorrect username or password.",QMessageBox::NoIcon,
                       QMessageBox::Ok | QMessageBox::Default,
                       QMessageBox::NoButton,
                       QMessageBox::NoButton);
        mb.setStyleSheet("QMessageBox {color: rgb(255, 255, 255);}");
        mb.exec();
    }
}
void Dialog::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}
void Dialog::on_pushButton_back_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}
void Dialog::on_pushButton_homepagestud_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}
void Dialog::on_pushButton_goToStudents_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}
void Dialog::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(lol);
    QTableWidget*studtable=ui->tableWidget_stud1;
    studtable->clearContents();
    studtable->setRowCount(0);
}
void Dialog::on_pushButton_5_clicked()
{

    ui->stackedWidget->setCurrentIndex(1);
    QTableWidget*studtable=ui->tableWidget_stud1;
    studtable->clearContents();
    studtable->setRowCount(0);

}
void Dialog::on_pushButton_15_clicked()
{
     ui->stackedWidget->setCurrentIndex(5);
     ui->lineEdit_input_coursename->setText("");
     ui->lineEdit_input_coursecode->setText("");
     ui->comboBox_input_lecturehall->setCurrentIndex(-1);
     ui->comboBox_input_day->setCurrentIndex(-1);
     ui->comboBox_input_hour->setCurrentIndex(-1);
     ui->comboBox_input_hour->setEnabled(false);
     ui->comboBox_input_lecturehall->setEnabled(true);
}
void Dialog::on_pushButton_16_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->lineEdit_input_coursename->setText("");
    ui->lineEdit_input_coursecode->setText("");
    ui->comboBox_input_lecturehall->setCurrentIndex(-1);
    ui->comboBox_input_day->setCurrentIndex(-1);
    ui->comboBox_input_hour->setCurrentIndex(-1);
    ui->comboBox_input_hour->setEnabled(false);
    ui->comboBox_input_lecturehall->setEnabled(true);
}
void Dialog::on_pushButton_goToCourses_clicked()
{
     ui->stackedWidget->setCurrentIndex(5);
}
void Dialog::on_pushButton_13_clicked()
{
     ui->stackedWidget->setCurrentIndex(6);
}
void Dialog::on_pushButton_17_clicked()
{
     ui->stackedWidget->setCurrentIndex(5);

     QTableWidget*coursetable=ui->tableWidget_courses;
     coursetable->clearContents();
     coursetable->setRowCount(0);
     ui->tableWidget_courseProf->clearContents();
     ui->tableWidget_courseProf->setRowCount(0);
}
void Dialog::on_pushButton_18_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    QTableWidget*coursetable=ui->tableWidget_courses;
    coursetable->clearContents();
    coursetable->setRowCount(0);
    ui->tableWidget_courseProf->clearContents();
    ui->tableWidget_courseProf->setRowCount(0);
}
void Dialog::on_pushButton_26_clicked()
{
     ui->stackedWidget->setCurrentIndex(8);
}
void Dialog::on_pushButton_25_clicked()
{
     ui->stackedWidget->setCurrentIndex(1);
}
void Dialog::on_pushButton_42_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
    QTableWidget*professortable=ui->tableWidget_displayprofessor;
    professortable->clearContents();
    professortable->setRowCount(0);
}
void Dialog::on_pushButton_43_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    QTableWidget*professortable=ui->tableWidget_displayprofessor;
    professortable->clearContents();
    professortable->setRowCount(0);
}
void Dialog::on_pushButton_9_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}
void Dialog::on_pushButton_goTOPRofessors_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
}
void Dialog::on_pushButton_7_clicked()
{
     ui->stackedWidget->setCurrentIndex(9);
}
//function to search and display the info of a professor
void Dialog::on_pushButton_8_clicked()
{
    QString first=ui->lineEdit_firstname_searchProf->text();
     QString last=ui->lineEdit_lastname_search_prof->text();
    bool status=false;
    int index;
    for (int i = 0; i < registeredProfessors.size(); ++i) {
        if(registeredProfessors[i].getFirstName()==first&&registeredProfessors[i].getLastName()==last){
            index=i;
            status=true;
            break;
        }
    }

    if(status){
        Professor newProfessor=registeredProfessors[index];
        QString firstname=newProfessor.getFirstName();
        QString lastname=newProfessor.getLastName();
        QString mobile=newProfessor.getMobile();
        int age=newProfessor.getAge();
        QString age2=QString::number(age);
        QString email=newProfessor.getEmail();
        QString title=newProfessor.getTitle();
        ui->lineEdit_output_firstname_prof->setText(firstname);
        ui->lineEdit_output_firstname_prof->setEnabled(false);
        ui->lineEdit_output_lastname_prof->setText(lastname);
        ui->lineEdit_output_lastname_prof->setEnabled(false);
        ui->lineEdit_output_title_prof->setText(title);
        ui->lineEdit_output_title_prof->setEnabled(false);
        ui->lineEdit_output_mobile_prof->setText(mobile);
        ui->lineEdit_output_mobile_prof->setEnabled(false);
        ui->lineEdit_output_email_prof->setText(email);
        ui->lineEdit_output_email_prof->setEnabled(false);
        ui->lineEdit_output_age_prof->setText(age2);
        ui->lineEdit_output_age_prof->setEnabled(false);
         QTableWidget*professortable=ui->tableWidget_displayprofessor;
         professortable->setEnabled(false);
         vector<Course*>getcourses=registeredProfessors[index].getCourses();
         for (int i = 0; i <getcourses.size() ; ++i) {

              QTableWidgetItem*coursewidget=new QTableWidgetItem(getcourses[i]->getName());
              professortable->insertRow(professortable->rowCount());
              professortable->setItem(professortable->rowCount()-1,0,coursewidget);

         }
         professortable->resizeColumnsToContents();
         professortable->resizeRowsToContents();
         ui->stackedWidget->setCurrentIndex(10);
         ui->lineEdit_firstname_searchProf->setText("");
         ui->lineEdit_lastname_search_prof->setText("");

    }
    else{
        QMessageBox mb("Warning", "Professor is not registered on the system, try adding new professor.",QMessageBox::NoIcon,
                       QMessageBox::Ok | QMessageBox::Default,
                       QMessageBox::NoButton,
                       QMessageBox::NoButton);
        mb.setStyleSheet("QMessageBox {color: rgb(255, 255, 255);}");
        mb.exec();
    }

}
void Dialog::on_pushButton_10_clicked()
{
     ui->stackedWidget->setCurrentIndex(1);
}
void Dialog::on_pushButton_12_clicked()
{
     ui->stackedWidget->setCurrentIndex(1);
}
void Dialog::on_pushButton_11_clicked()
{
     ui->stackedWidget->setCurrentIndex(11);
     index=2;
}
//Student code
bool Dialog:: verifyName(QString name){

    name.toStdString();
    if(name.size()<=1)
        return false;
    for (int i = 0; i < name.size(); ++i) {
        if(name[i].isLetter()){
            continue;
        }
        else
            return false;

    }
    return true;

}
void Dialog::on_pushButton_21_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}
void Dialog::on_pushButton_22_clicked()
{
    ui->stackedWidget->setCurrentIndex(12);
}
void Dialog::on_pushButton_SignUp_clicked()
{
    //secret code
    QString secretcode = "CU23_AdminCode";

    if (ui->lineEdit->text() == secretcode){
        //enter the pair
        QString username = ui->lineEdit_username_signUp->text();
        QString password = ui->lineEdit_password_signUp->text();
        usernamePassword.push_back( std::make_pair(username,password) );

        //go back to login screen
        ui->stackedWidget->setCurrentIndex(0);
        ui->lineEdit_username->setText("");
        ui->lineEdit_password->setText("");
    }
    else{
        QMessageBox mb("SignUp", "The secret code you entered is wrong, make sure to check with the adminstration office.",QMessageBox::NoIcon,
                       QMessageBox::Ok | QMessageBox::Default,
                       QMessageBox::NoButton,
                       QMessageBox::NoButton);
        mb.setStyleSheet("QMessageBox {color: rgb(255, 255, 255);}");
        mb.exec();
    }
}
void Dialog::on_pushButton_23_clicked()
{
    ui->stackedWidget->setCurrentIndex(index);
}
void Dialog::on_pushButton_27_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
//Add New Student Button
void Dialog::on_pushButton_addstud_clicked()
{
    QString firstname=ui->lineEdit_input_firstnamestudent->text();
    QString lastname=ui->lineEdit_input_lastnamestud->text();
    QString email=ui->lineEdit_input_emailstud->text();
    QString mobile=ui->lineEdit_input_mobilestud->text();
    QString grade=ui->comboBox_input_gradestud->currentText();
    QString age=ui->lineEdit_input_agestud->text();
    QFile file("C:/Users/user/Documents/GitHub/final-project-binaryattack/csv/Students.csv"); //hena hot path elresource file
            file.open(QIODevice::Append | QIODevice::Text);

            // Write data to file
            QTextStream stream(&file);
            QString separator(",");
            stream <<id<<','<<firstname<<','<<lastname<<','<<age<<','<<grade<<','<<mobile<<','<<email<<"\n";


            stream.flush();
            file.close();
    bool ok;
    int age1=age.toInt(&ok,10);
     if(ui->lineEdit_input_emailstud->hasAcceptableInput()&&age1>0&&age1<100&&verifyName(firstname)&&verifyName(lastname)){

     }
     else{
         QMessageBox mb("Warning", "Invalid Input.",QMessageBox::NoIcon,
                        QMessageBox::Ok | QMessageBox::Default,
                        QMessageBox::NoButton,
                        QMessageBox::NoButton);
         mb.setStyleSheet("QMessageBox {color: rgb(255, 255, 255);}");
         mb.exec();
         return;
     }
    Student newstudent(firstname,lastname,mobile,email,grade,age1,id);
    int iD=id;
    QString ID=QString::number(iD);
    id++;
    ui->lineEdit_input_firstnamestudent->setText("");
    ui->lineEdit_input_lastnamestud->setText("");
    ui->lineEdit_input_mobilestud->setText("");
    ui->lineEdit_input_agestud->setText("");
    ui->lineEdit_input_emailstud->setText("");
    ui->comboBox_input_gradestud->setCurrentIndex(-1);


    for(int i=0;i<registeredStudents.size();i++){
     if(newstudent.getFirstName()==registeredStudents[i].getFirstName()&&newstudent.getLastName()==registeredStudents[i].getLastName()){
         QMessageBox mb("Info", "Student is already Registered on the system.",QMessageBox::NoIcon,
                        QMessageBox::Ok | QMessageBox::Default,
                        QMessageBox::NoButton,
                        QMessageBox::NoButton);
         mb.setStyleSheet("QMessageBox {color: rgb(255, 255, 255);}");
         mb.exec();
         return;
     }
    }
    registeredStudents.push_back(newstudent);
    QTableWidget*table=ui->tableWidget_Showall_Stud;

    table->insertRow(table->rowCount());
    QTableWidgetItem*firstnamewidget=new QTableWidgetItem(firstname);
    QTableWidgetItem*lastnamewidget=new QTableWidgetItem(lastname);
    QTableWidgetItem*emailwidget=new QTableWidgetItem(email);
    QTableWidgetItem*agewidget=new QTableWidgetItem(age);
    QTableWidgetItem*mobilewidget=new QTableWidgetItem(mobile);
    QTableWidgetItem*gradewidget=new QTableWidgetItem(grade);
    QTableWidgetItem*idwidget=new QTableWidgetItem(ID);
   // table->setEnabled(false);
    table->setItem(table->rowCount()-1,0,firstnamewidget);
    table->setItem(table->rowCount()-1,1,lastnamewidget);
    table->setItem(table->rowCount()-1,2,emailwidget);
    table->setItem(table->rowCount()-1,3,mobilewidget);
    table->setItem(table->rowCount()-1,4,gradewidget);
    table->setItem(table->rowCount()-1,5,agewidget);
    table->setItem(table->rowCount()-1,6,idwidget);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);


    table->resizeColumnsToContents();
    table->resizeRowsToContents();

    QMessageBox mb("Info", "Student Added.",QMessageBox::NoIcon,
                   QMessageBox::Ok | QMessageBox::Default,
                   QMessageBox::NoButton,
                   QMessageBox::NoButton);
    mb.setStyleSheet("QMessageBox {color: rgb(255, 255, 255);}");
    mb.exec();


}
void Dialog::on_pushButton_3_clicked()
{
    lol=2;
    QString ID=ui->lineEdit_search_stud_ID->text();
    int id=ID.toInt();
    bool found=false;
    int index;

    for (int i = 0; i < registeredStudents.size(); ++i) {
        if(registeredStudents[i].getId()==id){
            index=i;
            found=true;
            break;
        }
    }

    if(found){
        Student newstudent=registeredStudents[index];
        QString firstname=newstudent.getFirstName();
        QString lastname=newstudent.getLastName();
        QString mobile=newstudent.getMobile();
        int age=newstudent.getAge();
        QString age1=QString::number(age);
        QString email=newstudent.getEmail();
        QString grade=newstudent.getGrade();
        ui->lineEdit_output_firstname_stud->setText(firstname);
        ui->lineEdit_output_firstname_stud->setEnabled(false);
        ui->lineEdit_output_lastname_stud->setText(lastname);
        ui->lineEdit_output_lastname_stud->setEnabled(false);
        ui->lineEdit_output_grade_stud->setText(grade);
        ui->lineEdit_output_grade_stud->setEnabled(false);
        ui->lineEdit_output_mobile_stud->setText(mobile);
        ui->lineEdit_output_mobile_stud->setEnabled(false);
        ui->lineEdit_output_email_stud->setText(email);
        ui->lineEdit_output_email_stud->setEnabled(false);
        ui->lineEdit_output_age_stud->setText(age1);
        ui->lineEdit_output_age_stud->setEnabled(false);
        QTableWidget*studtable=ui->tableWidget_stud1;
        studtable->setEnabled(false);
        vector<pair<Course*,double>>coursess=registeredStudents[index].getMarksForEveryCourse();

        for (int i = 0; i < coursess.size(); ++i) {
            QString grade=QString::number(coursess[i].second);
            QTableWidgetItem*coursenamewidget=new QTableWidgetItem(coursess[i].first->getName());
            QTableWidgetItem*coursegradewidget=new QTableWidgetItem(grade);
            studtable->insertRow(studtable->rowCount());
            studtable->setItem(studtable->rowCount()-1,0,coursenamewidget);
            studtable->setItem(studtable->rowCount()-1,1,coursegradewidget);


        }
        studtable->resizeColumnsToContents();
        studtable->resizeRowsToContents();
        ui->stackedWidget->setCurrentIndex(4);
    }
    else{
        QMessageBox mb("Warning", "Student is not registered on the system.",QMessageBox::NoIcon,
                       QMessageBox::Ok | QMessageBox::Default,
                       QMessageBox::NoButton,
                       QMessageBox::NoButton);
        mb.setStyleSheet("QMessageBox {color: rgb(255, 255, 255);}");
        mb.exec();
    }
    ui->lineEdit_search_stud_ID->setText("");
}
void Dialog::on_pushButton_6_clicked()
{
    QString coursename=ui->lineEdit_input_coursename->text();
    QString coursecode=ui->lineEdit_input_coursecode->text();
    QString courselecturhall=ui->comboBox_input_lecturehall->currentText();
    QString courseday=ui->comboBox_input_day->currentText();
    QString  Interval=ui->comboBox_input_hour->currentText();

    QFile file("D:/Project Data/learning_managment_system/csv/Courses.csv"); //hena hot path elresource file
            file.open(QIODevice::Append | QIODevice::Text);

            // Write data to file
            QTextStream stream(&file);
            QString separator(",");
            stream <<coursename<<','<<coursecode<<','<<courselecturhall<<','<<courseday<<','<<Interval<<"\n";


            stream.flush();
            file.close();
    if(!coursename.isEmpty()&&!coursecode.isEmpty()&&!courselecturhall.isEmpty()&&!courseday.isEmpty()&&!Interval.isEmpty()){

        }
        else{
        QMessageBox mb("Warning", "Invalid Input.",QMessageBox::NoIcon,
                       QMessageBox::Ok | QMessageBox::Default,
                       QMessageBox::NoButton,
                       QMessageBox::NoButton);
        mb.setStyleSheet("QMessageBox {color: rgb(255, 255, 255);}");
        mb.exec();;
            return;
        }
    Interval.toStdString();

    int startHour;
    int lecturHallIndex = ui->comboBox_input_lecturehall->currentIndex();
    QString temp;

    for (int var = 0; var <Interval.size(); ++var) {
        if(Interval[var].isLetter()){
            startHour = temp.toInt();
            break;
        }
        temp += Interval[var];
    }

    Course newcourse(coursename,coursecode,courselecturhall,courseday,startHour);
    ui->lineEdit_input_coursename->setText("");
    ui->lineEdit_input_coursecode->setText("");
    ui->comboBox_input_lecturehall->setCurrentIndex(-1);
    ui->comboBox_input_day->setCurrentIndex(-1);
    ui->comboBox_input_hour->setCurrentIndex(-1);
    ui->comboBox_input_hour->setEnabled(false);
    ui->comboBox_input_lecturehall->setEnabled(true);

    for (int i = 0; i < registeredCourses.size(); ++i) {
        if(newcourse.getName()==registeredCourses[i].getName()){
            QMessageBox mb("Warning", "Course is Already Added in the system.",QMessageBox::NoIcon,
                           QMessageBox::Ok | QMessageBox::Default,
                           QMessageBox::NoButton,
                           QMessageBox::NoButton);
            mb.setStyleSheet("QMessageBox {color: rgb(255, 255, 255);}");
            mb.exec();
            return;
        }
    }
    registeredCourses.push_back(newcourse);
    QMessageBox mb("Info", "Course is Added.",QMessageBox::NoIcon,
                   QMessageBox::Ok | QMessageBox::Default,
                   QMessageBox::NoButton,
                   QMessageBox::NoButton);
    mb.setStyleSheet("QMessageBox {color: rgb(255, 255, 255);}");
    mb.exec();
    QComboBox*addToStud=ui->comboBox_choosecourse_addstud;
    QComboBox*addToProf=ui->comboBox_choose_course_addprof;
    QComboBox*addToSearch=ui->comboBox_searchcourse;
    addToStud->addItem(newcourse.getName());
    addToProf->addItem(newcourse.getName());
    addToSearch->addItem(newcourse.getName());
    timeSlots[lecturHallIndex][courseday.toStdString()].erase( startHour + (12*(startHour < 8) ) );
}

void Dialog::on_pushButton_14_clicked()
{
    QString coursename=ui->comboBox_searchcourse->currentText();
    bool found=false;
    int index;
    for (int i = 0; i < registeredCourses.size(); ++i) {
        if(coursename==registeredCourses[i].getName()){
            index=i;
            found=true;
            break;
        }
    }
    if(found){
        Course newcourse=registeredCourses[index];
        QString coursename=newcourse.getName();
        QString coursecode=newcourse.getCode();
        QString courseLecturehall=newcourse.getLectureHall();
        QString courseday=newcourse.getLectureDay();
        int coursehour1=newcourse.getLectureTime();
        QString coursehour=QString::number(coursehour1);
        ui->lineEdit_output_lecturehall->setText(courseLecturehall);
        ui->lineEdit_output_coursename->setText(coursename);
        ui->lineEdit_output_course_code->setText(coursecode);
        ui->lineEdit_output_day->setText(courseday);
        if(coursehour1==8){
            ui->lineEdit_output_hour->setText(coursehour+" AM - 10 AM");
        }
        else if(coursehour1==10){
            ui->lineEdit_output_hour->setText(coursehour+" AM - 12 PM");
        }
        else if(coursehour1==12){
            ui->lineEdit_output_hour->setText(coursehour+" PM - 2 PM");
        }
        else if(coursehour1==2){
            ui->lineEdit_output_hour->setText(coursehour+" PM - 4 PM");
        }
        else{
            ui->lineEdit_output_hour->setText(coursehour+" PM - 6 PM");
        }
        ui->lineEdit_output_lecturehall->setEnabled(false);
        ui->lineEdit_output_coursename->setEnabled(false);
        ui->lineEdit_output_day->setEnabled(false);
        ui->lineEdit_output_hour->setEnabled(false);
        ui->lineEdit_output_course_code->setEnabled(false);
        // ui->tableWidget_courses->setEnabled(false);

        QTableWidget*coursetable=ui->tableWidget_courses;
        coursetable->clearContents();
        coursetable->setRowCount(0);
        ui->tableWidget_courseProf->clearContents();
        ui->tableWidget_courseProf->setRowCount(0);

        QTableWidget*tablecourses=ui->tableWidget_courses;
        tablecourses->setEditTriggers(QAbstractItemView::NoEditTriggers);

       vector<Student*>enrolledStudnets=registeredCourses[index].getEnrolledStudentsInCourses();

       for (int i = 0; i < enrolledStudnets.size(); ++i) {
           tablecourses->insertRow(tablecourses->rowCount());

           double studentgrades=enrolledStudnets[i]->getGradesForCertainCourse(coursename);
           QString grade=QString::number(studentgrades);
           QTableWidgetItem*fullnamewidget=new QTableWidgetItem(enrolledStudnets[i]->getFirstName() + enrolledStudnets[i]->getLastName());
           QTableWidgetItem*gradewidget=new QTableWidgetItem(grade);
           int IDval=enrolledStudnets[i]->getId();
           QString printId=QString::number(IDval);
           QTableWidgetItem*idwidget=new QTableWidgetItem(printId);
           tablecourses->setItem(tablecourses->rowCount()-1,0,fullnamewidget);
           tablecourses->setItem(tablecourses->rowCount()-1,1,gradewidget);
           qDebug()<<enrolledStudnets[i]->getId();
           tablecourses->setItem(tablecourses->rowCount()-1,2,idwidget);


           }

       QTableWidget*tableprof=ui->tableWidget_courseProf;
       tableprof->setEditTriggers(QAbstractItemView::NoEditTriggers);

        vector<Professor*> profName=registeredCourses[index].getProfessors();
           for (int i = 0; i < profName.size(); ++i) {
                   QTableWidgetItem*profnamewidget=new QTableWidgetItem(profName[i]->getFirstName()+profName[i]->getLastName());
                        tableprof->insertRow(tableprof->rowCount());
                      tableprof->setItem(tableprof->rowCount()-1,0,profnamewidget);
           }
       //for (int i = 0; i < profName.size(); ++i) {
           //QTableWidgetItem*profnamewidget=new QTableWidgetItem(profName[i]->getFirstName()+profName[i]->getLastName());
           //if(profName.size()>tablecourses->rowCount())
          // tablecourses->insertRow(tablecourses->rowCount());
        //   tablecourses->setItem(tablecourses->rowCount(),2,profnamewidget);

      // }
           tableprof->resizeColumnsToContents();
           tableprof->resizeRowsToContents();
       tablecourses->resizeColumnsToContents();
       tablecourses->resizeRowsToContents();
       ui->stackedWidget->setCurrentIndex(7);

       ui->comboBox_searchcourse->setCurrentIndex(-1);
    }
    else{
        QMessageBox mb("Warning", "Please select a course First.",QMessageBox::NoIcon,
                       QMessageBox::Ok | QMessageBox::Default,
                       QMessageBox::NoButton,
                       QMessageBox::NoButton);
        mb.setStyleSheet("QMessageBox {color: rgb(255, 255, 255);}");
        mb.exec();
    }
}
void Dialog::on_pushButton_19_clicked()
{
    QString firstname=ui->lineEdit_firstname_addcourse_stud->text();
    QString lastname=ui->lineEdit_lastname_addcourse_stud->text();
    QString chosencourse=ui->comboBox_choosecourse_addstud->currentText();
    QString marksScored=ui->lineEdit_scoredmarks_addstud->text();
    bool ok;
    double marks=marksScored.toDouble(&ok);
    if(verifyName(firstname)&&verifyName(lastname)&&marks>=0&&marks<=100){


    }
    else{
        QMessageBox mb("Warning", "Invalid Input.",QMessageBox::NoIcon,
                       QMessageBox::Ok | QMessageBox::Default,
                       QMessageBox::NoButton,
                       QMessageBox::NoButton);
        mb.setStyleSheet("QMessageBox {color: rgb(255, 255, 255);}");
        mb.exec();
        return;
    }
    bool found=false;
    int index;
    int courseindex;
    for (int i = 0; i < registeredStudents.size(); ++i) {
        if(registeredStudents[i].getFirstName()==firstname&&registeredStudents[i].getLastName()==lastname){
            index=i;
            found=true;
            break;
        }
    }
    if(!found){
        QMessageBox mb("Warning", "This Student is not Registered on the system.",QMessageBox::NoIcon,
                       QMessageBox::Ok | QMessageBox::Default,
                       QMessageBox::NoButton,
                       QMessageBox::NoButton);
        mb.setStyleSheet("QMessageBox {color: rgb(255, 255, 255);}");
        mb.exec();
        return;
    }
    else
    {
        bool f=false;
        Student&student=registeredStudents[index];
        for (int i = 0; i < registeredCourses.size(); ++i) {
            if(chosencourse==registeredCourses[i].getName()){
                courseindex=i;
                f=true;
                break;
            }
        }
        if(!f){
            QMessageBox mb("Warning", "Please select a course",QMessageBox::NoIcon,
                           QMessageBox::Ok | QMessageBox::Default,
                           QMessageBox::NoButton,
                           QMessageBox::NoButton);
            mb.setStyleSheet("QMessageBox {color: rgb(255, 255, 255);}");
            mb.exec();
            return;
        }
        if(student.addCourse(&registeredCourses[courseindex],marks)){
            QMessageBox mb("Info", "Course Added Successfully.",QMessageBox::NoIcon,
                           QMessageBox::Ok | QMessageBox::Default,
                           QMessageBox::NoButton,
                           QMessageBox::NoButton);
            mb.setStyleSheet("QMessageBox {color: rgb(255, 255, 255);}");
            mb.exec();
            ui->lineEdit_firstname_addcourse_stud->setText("");
            ui->lineEdit_lastname_addcourse_stud->setText("");
            ui->comboBox_choosecourse_addstud->setCurrentIndex(-1);
            ui->lineEdit_scoredmarks_addstud->setText("");
           // qDebug()<<10;
            registeredCourses[courseindex].addStudent(&student);
        }
        else{
            QMessageBox mb("Warning", "Already registered in this course.",QMessageBox::NoIcon,
                           QMessageBox::Ok | QMessageBox::Default,
                           QMessageBox::NoButton,
                           QMessageBox::NoButton);
            mb.setStyleSheet("QMessageBox {color: rgb(255, 255, 255);}");
            mb.exec();
        }

    }

}
void Dialog::on_pushButton_20_clicked()
{
    QString firstname=ui->lineEdit_addcourse_firstname_addprof->text();
    QString lastname=ui->lineEdit_addcourse_lastname_addprof->text();
    QString chosencourse=ui->comboBox_choose_course_addprof->currentText();
    if(verifyName(firstname)&&verifyName(lastname)){

    }
    else{
        QMessageBox mb("Warning", "Invalid Input",QMessageBox::NoIcon,
                       QMessageBox::Ok | QMessageBox::Default,
                       QMessageBox::NoButton,
                       QMessageBox::NoButton);
        mb.setStyleSheet("QMessageBox {color: rgb(255, 255, 255);}");
        mb.exec();
        return;
    }

    bool found=false;
    int index;
    int courseindex;
    for (int i = 0; i < registeredProfessors.size(); ++i) {
        if(registeredProfessors[i].getFirstName()==firstname&&registeredProfessors[i].getLastName()==lastname){
            index=i;
            found=true;
            break;
        }
    }
    if(!found){
        QMessageBox mb("Warning", "This Professor is not added to the system, try adding new professor.",QMessageBox::NoIcon,
                       QMessageBox::Ok | QMessageBox::Default,
                       QMessageBox::NoButton,
                       QMessageBox::NoButton);
        mb.setStyleSheet("QMessageBox {color: rgb(255, 255, 255);}");
        mb.exec();
        return;
    }
    else{
        bool f=false;
        Professor &professor(registeredProfessors[index]);
        for (int i = 0; i < registeredCourses.size(); ++i) {
            if(chosencourse==registeredCourses[i].getName()){
                courseindex=i;
                f=true;
                break;
            }
        }
        if(!f){
            QMessageBox mb("Warning", "Please select a course",QMessageBox::NoIcon,
                           QMessageBox::Ok | QMessageBox::Default,
                           QMessageBox::NoButton,
                           QMessageBox::NoButton);
            mb.setStyleSheet("QMessageBox {color: rgb(255, 255, 255);}");
            mb.exec();
            return;
        }
        if(professor.addCourse(&registeredCourses[courseindex])){
            QMessageBox mb("Info", "Course Added Successfully.",QMessageBox::NoIcon,
                           QMessageBox::Ok | QMessageBox::Default,
                           QMessageBox::NoButton,
                           QMessageBox::NoButton);
            mb.setStyleSheet("QMessageBox {color: rgb(255, 255, 255);}");
            mb.exec();
            ui->lineEdit_addcourse_firstname_addprof->setText("");
            ui->lineEdit_addcourse_lastname_addprof->setText("");
            ui->comboBox_choose_course_addprof->setCurrentIndex(-1);
            registeredCourses[courseindex].addProfessor(&professor);
        }
        else{
            QMessageBox mb("Warning", "Already Teaching this course.",QMessageBox::NoIcon,
                           QMessageBox::Ok | QMessageBox::Default,
                           QMessageBox::NoButton,
                           QMessageBox::NoButton);
            mb.setStyleSheet("QMessageBox {color: rgb(255, 255, 255);}");
            mb.exec();
        }

    }
}
void Dialog::on_pushButton_addstud_4_clicked()
{
    QString firstname=ui->lineEdit_input_firstname_prof->text();
    QString lastname=ui->lineEdit_input_lastname_prof ->text();
    QString email=ui->lineEdit_input_email_prof->text();
    QString mobile=ui->lineEdit_input_mobile_prof->text();
    QString titleofprof=ui->comboBox_input_title_prof->currentText();
    QString ageofprof=ui->lineEdit_input_age_prof->text();
    QFile file("D:/Project Data/learning_managment_system/csv/Prof.csv"); //hena hot path elresource file
            file.open(QIODevice::Append | QIODevice::Text);

            // Write data to file
            QTextStream stream(&file);
            QString separator(",");
            stream <<id<<','<<firstname<<','<<lastname<<','<<ageofprof<<','<<titleofprof<<','<<mobile<<','<<email<<"\n";


            stream.flush();
            file.close();
    bool ok;
    int age2=ageofprof.toInt(&ok,10);
    if(ui->lineEdit_input_email_prof->hasAcceptableInput()&&age2>0&&age2<100&&verifyName(firstname)&&verifyName(lastname)){

    }
    else{
        QMessageBox mb("Warning", "Invalid Input.",QMessageBox::NoIcon,
                       QMessageBox::Ok | QMessageBox::Default,
                       QMessageBox::NoButton,
                       QMessageBox::NoButton);
        mb.setStyleSheet("QMessageBox {color: rgb(255, 255, 255);}");
        mb.exec();
        return;
    }
    Professor newProfessor(firstname,lastname,email,mobile,age2,titleofprof);
    ui->lineEdit_input_firstname_prof->setText("");
    ui->lineEdit_input_lastname_prof->setText("");
    ui->lineEdit_input_mobile_prof->setText("");
    ui->lineEdit_input_age_prof->setText("");
    ui->lineEdit_input_email_prof->setText("");
    ui->comboBox_input_title_prof->setCurrentIndex(-1);

    for(int i=0;i<registeredProfessors.size();i++){
        if(newProfessor.getFirstName()==registeredProfessors[i].getFirstName()&&newProfessor.getLastName()==registeredProfessors[i].getLastName()){
            QMessageBox mb("Warning", "Professor has already been Registered.",QMessageBox::NoIcon,
                           QMessageBox::Ok | QMessageBox::Default,
                           QMessageBox::NoButton,
                           QMessageBox::NoButton);
            mb.setStyleSheet("QMessageBox {color: rgb(255, 255, 255);}");
            mb.exec();
                   return;
            }
    }
              registeredProfessors.push_back(newProfessor);
              QMessageBox mb("Info", "Professor added successfully.",QMessageBox::NoIcon,
                             QMessageBox::Ok | QMessageBox::Default,
                             QMessageBox::NoButton,
                             QMessageBox::NoButton);
              mb.setStyleSheet("QMessageBox {color: rgb(255, 255, 255);}");
              mb.exec();



}
void Dialog::on_tableWidget_Showall_Stud_cellDoubleClicked(int row, int column)
{
    if(column!=6){
        return;
    }
        QTableWidget*table=ui->tableWidget_Showall_Stud;
         QString getid=table->item(row,column)->text();
         ui->lineEdit_search_stud_ID->setText(getid);
         //searching the student by id
         on_pushButton_3_clicked();
}
void Dialog::on_tableWidget_courses_cellDoubleClicked(int row, int column)
{

    QTableWidget*table=ui->tableWidget_courses;

    if(registeredStudents.empty())
        return;

    if(column!=2)
        return;

    QString getid=table->item(row,column)->text();
    ui->lineEdit_search_stud_ID->setText(getid);
    on_pushButton_3_clicked();
    lol=7;
}
void Dialog::on_comboBox_input_day_currentIndexChanged(int index)
{
    ui->comboBox_input_hour->setEnabled(false);
    ui->comboBox_input_hour->setCurrentIndex(-1);

    ui->comboBox_input_hour->setEnabled(false);
    QString lectureHall=ui->comboBox_input_lecturehall->currentText();
    QString day=ui->comboBox_input_day->currentText();

    if(!lectureHall.isEmpty()  && !day.isEmpty() ){
        ui->comboBox_input_hour->setEnabled(true);
        generateHours();
    }
}
void Dialog::on_comboBox_input_lecturehall_currentIndexChanged(int index)
{
    ui->comboBox_input_hour->setEnabled(false);
    ui->comboBox_input_hour->setCurrentIndex(-1);

    QString lectureHall=ui->comboBox_input_lecturehall->currentText();
    QString day=ui->comboBox_input_day->currentText();
    if(!lectureHall.isEmpty()  && !day.isEmpty() ){
        ui->comboBox_input_hour->setEnabled(true);
        generateHours();
    }
}

//utility code
void Dialog::generateHours(){

    QString lectureHall=ui->comboBox_input_lecturehall->currentText();
    QString day = ui->comboBox_input_day->currentText();
    QComboBox*courseHour=ui->comboBox_input_hour;
    courseHour->clear();

    int lectureIndex ;

    if(lectureHall == "3201" ){
        lectureIndex  = 0 ;
    }
    else if (lectureHall == "3101"){
        lectureIndex  = 1 ;
    }
    else{
        lectureIndex = 2;
    }

    for(auto i:timeSlots[lectureIndex][day.toStdString()]){
        int hr = i;
        QString timeInterval = QString::number((hr%12)+(12*(hr%12==0)));
        if(hr >= 12)
            timeInterval+=" PM - ";
        else
            timeInterval+=" AM - ";

        timeInterval+=QString::number((hr%12)+2);
        if(hr+2 >= 12)
            timeInterval+=" PM";
        else
            timeInterval+=" AM";
        courseHour->addItem(timeInterval);
    }
    int numberofElemnts = ui->comboBox_input_hour->count();
        if(!numberofElemnts){
            courseHour->setPlaceholderText("No available halls");
            courseHour->setEnabled(false);
        }
}

void Dialog::on_pushButton_28_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

//table Students
void Dialog::on_pushButton_29_clicked()
{
    QString filePath=QFileDialog::getOpenFileName(this,"Import CSV FILES : Importing", QDir::rootPath(),"CSV Files (*.csv)");
        qDebug()<<filePath<<" is the path of the file imported";
        QFile myFile(filePath);
        if(!myFile.open(QFile::Text | QFile::ReadOnly))
            return;
        QTextStream inFile(&myFile);
        int rCnt=0;
        QString readedLine=inFile.readLine();
        QStringList listValue=readedLine.split(',');
        ui->tableWidget_Showall_Stud->setColumnCount(listValue.size());
        ui->tableWidget_Showall_Stud->setHorizontalHeaderLabels(listValue);

        while(!inFile.atEnd())
        {
            QString readedLine=inFile.readLine();
            QStringList listValue=readedLine.split(',');
            rCnt+=1;
            ui->tableWidget_Showall_Stud->setRowCount(rCnt);

            for(int k=0;k<listValue.size();k++)
                ui->tableWidget_Showall_Stud->setItem(rCnt-1,k,new QTableWidgetItem(listValue[k]));
        }
        myFile.flush();
        myFile.close();
}

//table Prof
void Dialog::on_pushButton_30_clicked()
{
    QString filePath=QFileDialog::getOpenFileName(this,"Import CSV FILES : Importing", QDir::rootPath(),"CSV Files (*.csv)");
        qDebug()<<filePath<<" is the path of the file imported";
        QFile myFile(filePath);
        if(!myFile.open(QFile::Text | QFile::ReadOnly))
            return;
        QTextStream inFile(&myFile);
        int rCnt=0;
        QString readedLine=inFile.readLine();
        QStringList listValue=readedLine.split(',');
        ui->tableWidget->setColumnCount(listValue.size());
        ui->tableWidget->setHorizontalHeaderLabels(listValue);

        while(!inFile.atEnd())
        {
            QString readedLine=inFile.readLine();
            QStringList listValue=readedLine.split(',');
            rCnt+=1;
            ui->tableWidget->setRowCount(rCnt);

            for(int k=0;k<listValue.size();k++)
                ui->tableWidget->setItem(rCnt-1,k,new QTableWidgetItem(listValue[k]));
        }
        myFile.flush();
        myFile.close();
}

//table Courses
void Dialog::on_pushButton_31_clicked()
{
    QString filePath=QFileDialog::getOpenFileName(this,"Import CSV FILES : Importing", QDir::rootPath(),"CSV Files (*.csv)");
        qDebug()<<filePath<<" is the path of the file imported";
        QFile myFile(filePath);
        if(!myFile.open(QFile::Text | QFile::ReadOnly))
            return;
        QTextStream inFile(&myFile);
        int rCnt=0;
        QString readedLine=inFile.readLine();
        QStringList listValue=readedLine.split(',');
        ui->tableWidget_2->setColumnCount(listValue.size());
        ui->tableWidget_2->setHorizontalHeaderLabels(listValue);

        while(!inFile.atEnd())
        {
            QString readedLine=inFile.readLine();
            QStringList listValue=readedLine.split(',');
            rCnt+=1;
            ui->tableWidget_2->setRowCount(rCnt);

            for(int k=0;k<listValue.size();k++)
                ui->tableWidget_2->setItem(rCnt-1,k,new QTableWidgetItem(listValue[k]));
        }
        myFile.flush();
        myFile.close();
}


void Dialog::on_pushButton_32_clicked()
{
    ui->stackedWidget->setCurrentIndex(11);
    index=8;
}


void Dialog::on_pushButton_33_clicked()
{
    ui->stackedWidget->setCurrentIndex(11);
    index=5;
}


void Dialog::on_infoButton_clicked()
{
    QMessageBox mb("About Us", "Paideia is an Educational Management Tool made to make your life easier.",QMessageBox::NoIcon,
                   QMessageBox::Ok | QMessageBox::Default,
                   QMessageBox::NoButton,
                   QMessageBox::NoButton);
    mb.setStyleSheet("QMessageBox {color: rgb(255, 255, 255);}");
    mb.exec();
}


