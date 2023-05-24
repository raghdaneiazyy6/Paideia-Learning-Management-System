//
// Created by Mourad on 12/19/2022.
//

#ifndef LEARNING_MANAGEMENT_SYSTEM_PERSON_H
#define LEARNING_MANAGEMENT_SYSTEM_PERSON_H
#include<iostream>
#include<QString>
using namespace std;

class Person {
private:
    QString firstName;
    QString lastName;
    QString mobile;
    QString email;
    int age;
public:

    Person(QString &firstName, QString &lastName, QString &mobile, QString &email, int &age);

    bool setFirstName(QString & );

    bool setLastName(QString &);

    bool setMobile(QString & );

    bool setEmail(QString & );

    bool setAge(int & );

    QString getFirstName()const;

    QString getLastName()const;

    QString getMobile()const;

    QString getEmail()const;

    int getAge()const;

};


#endif //LEARNING_MANAGEMENT_SYSTEM_PERSON_H
