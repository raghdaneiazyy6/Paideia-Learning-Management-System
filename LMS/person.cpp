//
// Created by Mourad on 12/19/2022.
//

#include "Person.h"
#include<QString>
Person::Person(QString &firstName, QString &lastName, QString &mobile, QString &email, int &age) {
    setFirstName(firstName);
    setLastName(lastName);
    setMobile(mobile);
    setAge(age);
    setEmail(email);
}

QString Person::getEmail() const {
    return email;
}

int Person::getAge() const {
    return age;
}

QString Person::getFirstName() const {
    return firstName;
}


QString Person::getLastName() const {
    return lastName;
}

QString Person::getMobile() const {
    return mobile;
}

bool Person::setEmail(QString &email) {
    this->email=email;
    return true;
}

bool Person::setAge(int &age) {
    if(age>0&&age<120) {
        this->age = age;
        return true;
    }
    else
        return false;

}

bool  Person::setFirstName(QString &firstname) {
    this->firstName=firstname;
    return true;
}

bool  Person::setLastName(QString &lastname) {
   this->lastName=lastname;
    return true;
}
bool Person::setMobile(QString &mobile) {
   this->mobile=mobile;
    return true;
}
