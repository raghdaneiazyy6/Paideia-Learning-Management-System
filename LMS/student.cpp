//
// Created by 10 on 12/12/2022.
//

#include "Student.h"
#include "Course.h"
#include "Person.h"

Student::Student(QString &firstName, QString &lastName, QString &mobile, QString &email, QString &grade, int &age,const int &id): Person(firstName, lastName, mobile, email, age) {
    setGrade(grade);
    this->id=id;

}


bool Student::setGrade(QString &grade) {
    this->grade=grade;
    return true;
}


bool Student::addCourse(Course* course, double mark) {

    for (int i = 0; i < courses.size(); ++i) {
        if (*courses[i].first == *course)
            return false;
    }
    if(mark < 0 || mark > 100)
        return false;

    pair<Course*, double> CourseData(course,mark);

    courses.push_back(CourseData);

    return true;

}

QString Student::getGrade() const {
    return this->grade;
}

bool Student::operator==(const Student & c1) {
    return (c1.getFirstName() == getFirstName() && c1.getLastName() == getLastName());
}

vector<pair<Course *, double>> Student::getMarksForEveryCourse() {
    return this->courses;
}

int Student::getId()const{
    return id;
}

double Student::getGradesForCertainCourse(QString name){
    for (int i = 0; i < courses.size(); ++i) {
        if(name==courses[i].first->getName()){
            return courses[i].second;
        }
    }
    return -1;
}
