//
// Created by 10 on 12/12/2022.
//

#include "Course.h"
#include "Student.h"
Course::Course(QString &name, QString &code, QString &lectureHall, QString &day, int &hour) {
    setName(name);
    setCode(code);
    setTime(day,hour);
    setLectureHall(lectureHall);
}

QString Course::getName() const {
    return name;
}

QString Course::getCode() const {
    return code;
}

QString Course::getLectureHall() const {
    return lectureHall;
}

pair<QString,int> Course::getTime() const {
    return {day,hour};
}

bool Course::setName(QString &name) {
   this->name=name;
    return true;

}

bool Course::setCode(QString &code) {
    this->code=code;
    return true;
}

bool Course::setLectureHall(QString &lectureHall) {
    this->lectureHall = lectureHall;
    return true;
}

bool Course::setTime(QString &d, int &h) {
   day=d;
   hour=h;
   return true;
}

bool Course::operator==(const Course & c1) {
    return (c1.getName()==name&&c1.getCode()==code);
}

bool Course::addProfessor(Professor *p) {
    for (int i = 0; i < prof.size(); ++i) {
        if (*prof[i] == *p) {
            return false;
        }
    }
    prof.push_back(p);
    return true;
}

bool Course::addStudent(Student *s) {
    for (int i = 0; i < stud.size(); ++i) {
        if(*stud[i]==*s){
            return false;
        }
    }
    stud.push_back(s);
    return true;
}

QString Course::getLectureDay() const {
    return day;
}

int Course::getLectureTime() const {
    return hour;
}

vector<Student *> Course::getEnrolledStudentsInCourses() {
    return this->stud;
}

vector<Professor*>Course::getProfessors(){
    return this->prof;
}
