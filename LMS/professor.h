//
// Created by 10 on 12/12/2022.
//

#ifndef LEARNING_MANAGEMENT_SYSTEM_PROFESSOR_H
#define LEARNING_MANAGEMENT_SYSTEM_PROFESSOR_H
#include <iostream>
#include <vector>
#include"Student.h"
#include "Person.h"
#include<QString>
using namespace std;
class Professor: public Person{
private:
    QString Title;
    vector<Course*> courses;
public:
    Professor(QString &, QString &, QString &, QString &, int &,QString&);

    void setTitle(const QString &title);

    QString getTitle() const;

    void DisplayInfo();

    bool addCourse(Course*);

    bool operator==(const Professor&);

    vector<Course*>getCourses()const;


};


#endif //LEARNING_MANAGEMENT_SYSTEM_PROFESSOR_H
