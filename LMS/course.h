//
// Created by 10 on 12/12/2022.
//

#ifndef LEARNING_MANAGEMENT_SYSTEM_COURSE_H
#define LEARNING_MANAGEMENT_SYSTEM_COURSE_H
#include"Professor.h"
#include "Student.h"
#include<QString>
using namespace std;
class Course {
private:
    QString name;
    QString code;
    QString lectureHall;
    QString day;
    int hour;
    vector<Student*>stud;
    vector<Professor*>prof;

public:
    Course(QString &, QString &, QString &, QString &, int &);

    bool setName(QString &);

    bool setCode(QString &);

    bool setLectureHall(QString &);

    bool setTime(QString &,int&);

    QString getName()const;

    QString getCode()const;

    QString getLectureHall()const;

    bool operator==(const Course &);

    pair<QString,int>getTime()const;

    bool addStudent(Student* s);

    bool addProfessor(Professor* p);

    QString getLectureDay()const;

    int getLectureTime()const;

    vector<Student*> getEnrolledStudentsInCourses();

    vector<Professor*>getProfessors();



};


#endif //LEARNING_MANAGEMENT_SYSTEM_COURSE_H
