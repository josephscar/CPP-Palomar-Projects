#include <iostream>
#include <vector>
using namespace std;

// Forward declarations of structs
struct Course;
struct Student;

// Struct definition for Course
struct Course {
    string name;
    vector<Student*> students; // Vector to store pointers to students enrolled in this course
};

// Struct definition for Student
struct Student {
    string name;
    vector<Course*> courses; // Vector to store pointers to courses in which this student is enrolled
};

// Function prototypes
void printStudent(Student* s);
void printCourse(Course* c);
void enroll(Student* s, Course* c);

// Function to print student information
void printStudent(Student* s){
    cout << "Student name: " << s->name << endl;
    cout << "Student courses: " << endl;
    for(int i = 0; i < s->courses.size(); i++){
        cout << s->courses[i]->name << endl;
    }
}

// Function to print course information
void printCourse(Course* c){
    cout << "Course name: " << c->name << endl;
    cout << "Course students: " << endl;
    for(int i = 0; i < c->students.size(); i++){
        cout << c->students[i]->name << endl;
    }
}

// Function to enroll student in course
void enroll(Student* s, Course* c){
    s->courses.push_back(c); // Add the course to the student's list of courses
    c->students.push_back(s); // Add the student to the course's list of students
}

int main(){
    // Create students
    Student student1 = {"Alice", {}};
    Student student2 = {"Bob", {}};
    Student student3 = {"Charlie", {}};

    // Create courses
    Course course1 = {"Math", {}};
    Course course2 = {"English", {}};

    // Enroll students in courses
    enroll(&student1, &course1);
    enroll(&student2, &course1);
    enroll(&student2, &course2);
    enroll(&student3, &course2);

    // Print student and course information
    cout << "Student information:" << endl;
    printStudent(&student1);
    printStudent(&student2);
    printStudent(&student3);

    cout << endl;

    cout << "Course information:" << endl;
    printCourse(&course1);
    printCourse(&course2);

    return 0;
}
