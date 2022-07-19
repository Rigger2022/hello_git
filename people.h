#pragma once
#include<iostream>
#include<fstream>
#pragma warning (disable:4996)
using namespace std;
class Date {
private:
    int y, m, d;
public:
    Date() {};
    Date(int yy, int mm, int dd) :d(dd), m(mm), y(yy) {};
    Date(char* s) { 
        y = m = d = 0;
        y = (s[0] - 48) * 1000 + (s[1] - 48) * 100 + (s[2] - 48) * 10 + s[3]; 
        int j = 5;
        while (s[j] != '/') m = m * 10 + (s[j] - 48), j++;
        j++;
        while (s[j] != '/') d = d * 10 + (s[j] - 48), j++;
    }
    friend ostream& operator <<(ostream& output, Date& D) {
        output << D.y << '/' << D.m << '/' << D.d << '/';
        return output;
    }
    friend istream& operator >>(istream& input, Date& D) {
        cout << "请分别输入年月日：";
        cin >> D.y >> D.m >> D.d;
        return input;
    }
};

class People {
private:
    char name[11];
    char number[15];
    char sex[3];
    Date birthday;
    char id[25];
    const char* p_TYPE = "People";
public:
    friend istream& operator >>(istream& input, People& p) {
        cout << "输入姓名"; cin >> p.name;
        cout << "输入编号"; cin >> p.number;
        cout << "输入性别"; cin >> p.sex;
        cout << "输入生日"; cin >> p.birthday;
        cout << "输入身份证号"; cin >> p.id;
        return input;
    }
    friend ostream& operator <<(ostream& output, People& p) {
        output << p.name << ',';
        output << p.number << ',';
        output << p.sex << ',';
        output << p.birthday << ',';
        output << p.id << ',';
        return output;
    }
    People() {
        strcpy(name, "udf");
        strcpy(number, "udf");
        strcpy(sex, "u");
        birthday = Date{ 2000,1,1 };
        strcpy(id, "udf");
    }
    People(const char* n, const char* no, const char* s, Date d, const char* i) {
        strcpy(name, n);
        strcpy(number, no);
        strcpy(sex, s);
        birthday = d;
        strcpy(id, i);
    }
    People(People& p) {
        strcpy(name, p.name);
        strcpy(number, p.number);
        strcpy(sex, p.sex);
        birthday = p.birthday;
        strcpy(id, p.id);
    }
    ~People() {}
    virtual void enter() {
        cin >> *this;
        return;
    }
    virtual void print(ostream& output) {
        output << p_TYPE << ',';
        show(output);
        output << endl;
    }
    inline void show(ostream& output) {
        output << *this;
    }
    char* getName() { return name; }
    char* getNo() { return number; }
    char* getSex() { return sex; }
    Date getBirthday() { return birthday; }
    char* getID() { return id; }

    void updateName(const char* s) { strcpy(name, s); }
    void updateNo(const char* s) { strcpy(number, s); }
    void updateSex(const char* s) { strcpy(sex, s); }
    void updateBirthday(Date d) { birthday = d; }
    void updateID(const char* s) { strcpy(id, s); }

};

class Student : virtual public People {
private:
    char classNo[7];
    const char* p_TYPE = "Student";
public:
    Student() :People(), classNo("0") {}
    Student(People& p, const char* no) :People(p) {
        strcpy(classNo, no);
    }
    Student(const char* n, const char* no, const char* s, Date d, const char* i, const char* c_no)
        :People(n, no, s, d, i) {
        strcpy(classNo, c_no);
    }
    Student(Student& s) { *this = s; }
    void enter() {
        People::enter();
        //cout << "===========添加学生信息============" << endl;
        cout << "请输入班号: ";
        cin >> classNo;
        //cout << "=================================" << endl;
    }
    void show(ostream& output) {
        output << classNo << ',';
    }
    void print(ostream& output) {
        output << p_TYPE << ',';
        People::show(output);
        show(output);
        output << endl;
    }
    void updateClassNo(const char* s) { strcpy(classNo, s); }
    ~Student() { }
};

class Teacher : virtual public People {
private:
    char principalShip[11];
    char department[21];
    const char* p_TYPE = "Teacher";
public:
    Teacher() :People() {
        strcpy(principalShip, "udf");
        strcpy(department, "udf");
    }
    Teacher(People& p, const char* pship, const char* dep) :People(p) {
        strcpy(principalShip, pship);
        strcpy(department, dep);
    }
    Teacher(const char* n, const char* no, const char* s, Date d, const char* i, const char* pship, const char* dep)
        :People(n, no, s, d, i) {
        strcpy(principalShip, pship);
        strcpy(department, dep);
    }
    Teacher(Teacher& t) { *this = t; }
    void enter() {
        cout << "teacher enter start" << endl;
        People::enter();
        cout << "输入职务："; cin >> principalShip;
        cout << "输入所属部门："; cin >> department;
    }
    void show(ostream& output) {
        output << principalShip <<',';
        output << department << ',';
    }
    void print(ostream& output) {
        output << p_TYPE << ','; cout << 1;
        People::show(output);
        show(output);
        output << endl;
    }
    void updatePship(const char* s) { strcpy(principalShip, s); }
    void updateDep(const char* s) { strcpy(department, s); }
    char* getPship() { return (char*)principalShip; }

    virtual int PAY() { return 600 * strlen(getPship()); }

    ~Teacher() { }
};

class Graduate : virtual public Student {
private:
    char subject[21];
    char teacherAdvisor[21];
    const char* p_TYPE = "Graduate";
public:
    Graduate() :Student() {
        strcpy(subject, "udf");
        strcpy(teacherAdvisor, "udf");
    }
    Graduate(Student& s, const char* sub, const char* tA) :Student(s) {
        strcpy(subject, sub);
        strcpy(teacherAdvisor, tA);
    }
    Graduate(People& p, const char* c_no, const char* sub, const char* tA) :People(p) {
        updateClassNo(c_no);
        strcpy(subject, sub);
        strcpy(teacherAdvisor, tA);
    }
    Graduate(Graduate& g) { *this = g; }
    void enter() {
        Student::enter();
        cout << "输入专业："; cin >> subject;
        cout << "输入导师"; cin >> teacherAdvisor;
    }
    void show(ostream& output) {
        output << subject << ',';
        output << teacherAdvisor << ',';
    }
    void print(ostream& output) {
        output << p_TYPE << ',';
        People::show(output);
        Student::show(output);
        show(output);
        output << endl;
    }
    void updateSubject(const char* s) { strcpy(subject, s); }
    void updateTeacherAdvisor(const char* s) { strcpy(teacherAdvisor, s); }
    ~Graduate() {}
};
class TA : virtual public Teacher, virtual public Graduate {
private:
    int RA;
    const char* p_TYPE = "TA";
public:
    TA() :People(), Student(), Teacher(), Graduate(), RA(-1) {};
    TA(Graduate& g, Teacher& t, int a) :Teacher(t), Graduate(g), RA(a) {};
    TA(TA& ta) { *this = ta; }
    void enter() {
        Student::enter();
        char s[30];
        cout << "输入职务："; cin >> s; updatePship(s);
        cout << "输入所属部门："; cin >> s; updateDep(s);
        cout << "输入补助："; cin >> RA;
    }
    void print(ostream& output) {
        output << p_TYPE << ',';
        People::show(output);
        Student::show(output);
        Graduate::show(output);
        Teacher::show(output);
        output << RA << endl;
    }
};

class Prof :virtual public Teacher {
private:
    const char* p_TYPE = "Prof";
public:
    Prof() :People(), Teacher() {};
    Prof(People& p, Teacher& t) :People(p), Teacher(t) {};
    int PAY() { return 1000 * strlen(getPship()); }
};

class Female_Prof : virtual public Prof {
public:
    Female_Prof() :People(), Teacher(), Prof() {};
    Female_Prof(People& p, Teacher& t) :People(p), Teacher(t) {};
    int PAY() { return 800 * strlen(getPship()) + 3200; }
};
