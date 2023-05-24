#ifndef DIALOG_H
#define DIALOG_H

#include <vector>
#include <QDialog>
#include<map>
#include"course.h"
#include<set>
#include<QRegularExpression>
#include<QRegularExpressionValidator>
#include<unordered_map>

#include<QFile> //-R
#include<QTextStream> //-R
#include<QDebug> //-R
#include<QStringList>//-R
#include<QDebug>//-R
#include<QFile>//-R
#include<QFileDialog>//-R

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_back_clicked();

    void on_pushButton_homepagestud_clicked();

    void on_pushButton_goToStudents_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_goToCourses_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_26_clicked();

    void on_pushButton_25_clicked();

    void on_pushButton_42_clicked();

    void on_pushButton_43_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_goTOPRofessors_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_SignUp_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_27_clicked();

    bool verifyName(QString);

    void checkInput();

    void checkInput2();

    void on_pushButton_addstud_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_14_clicked();

    void on_comboBox_input_hour_activated(int index);

    void on_comboBox_input_day_activated(int index);

    void on_pushButton_19_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_addstud_4_clicked();

    void on_tableWidget_Showall_Stud_cellDoubleClicked(int row, int column);

    void on_tableWidget_courses_cellDoubleClicked(int row, int column);

    void on_comboBox_input_day_currentIndexChanged(int index);

    void on_comboBox_input_lecturehall_currentIndexChanged(int index);
    void on_pushButton_28_clicked();

    void on_pushButton_29_clicked();

    void on_pushButton_30_clicked();

    void on_pushButton_31_clicked();

    void on_pushButton_32_clicked();

    void on_pushButton_33_clicked();

    void on_infoButton_clicked();

    void on_comboBox_choosecourse_addstud_currentIndexChanged(int index);

    void on_comboBox_choose_course_addprof_currentIndexChanged(int index);

private:
    Ui::Dialog *ui;
    QVector< QPair <QString,QString> > usernamePassword;

    vector<unordered_map<string,set<int>>>timeSlots;
    vector<Course>registeredCourses;
    vector<Student>registeredStudents;
    vector<Professor>registeredProfessors;
    void generateHours();
};
#endif // DIALOG_H
