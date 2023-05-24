//
// Created by 10 on 12/12/2022.
//

#include "Professor.h"
#include "Course.h"
#include <iostream>
using namespace std;

Professor::Professor(QString &firstname, QString & lastname, QString &mobile, QString &email, int &age, QString &title): Person(firstname,lastname,mobile,email,age) {
    setTitle(title);
}

QString Professor::getTitle() const {
    return Title;
}


bool Professor::addCourse(Course* course) {
    for (int i = 0; i < courses.size(); ++i) {
        if(*course == *courses[i]){
            return false;
        }
    }
    courses.push_back(course);
    return true;
}

void Professor::setTitle(const QString &title) {
    this->Title = title ;
}
bool Professor::operator==(const Professor & c1) {
    return (c1.getFirstName()==getFirstName()&&c1.getLastName()==getLastName());
}

vector<Course *> Professor::getCourses() const {
    return this->courses;
}


