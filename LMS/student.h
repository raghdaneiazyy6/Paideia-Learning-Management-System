//
// Created by 10 on 12/12/2022.
//


#ifndef LEARNING_MANAGEMENT_SYSTEM_STUDENT_H
#define LEARNING_MANAGEMENT_SYSTEM_STUDENT_H


#include<string>
#include<vector>
#include<iostream>
#include "Person.h"
#include<QString>
class Course;
using namespace std;

class Student: public Person {
private:
     int id;
    QString grade;
   vector<pair<Course*,double>>courses;

public:
    Student(QString&, QString& , QString& , QString& , QString& , int&, const int& );

    bool setGrade(QString &);

    QString getGrade()const;

    bool addCourse(Course* , double );

    bool operator==(const Student &);

    bool setMark(double);

    vector<pair<Course*,double>>getMarksForEveryCourse();

    int getId()const;

     double getGradesForCertainCourse(QString);

};



#endif //LEARNING_MANAGEMENT_SYSTEM_STUDENT_H
