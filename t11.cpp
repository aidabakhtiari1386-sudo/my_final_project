#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

struct Course {
    string name;
    float grade;
    int unit;
};

struct Student {
    string name;
    int id;
    vector<Course> courses;
    float gpa = 0.0f;
    string status;
};

vector<Student> students;

float calculateGPA(const Student& s) {
    if (s.courses.empty()) return 0.0f;

    float sum = 0.0f;
    int totalUnits = 0;

    for (const auto& course : s.courses) {
        sum += course.grade * course.unit;
        totalUnits += course.unit;
    }

    return (totalUnits > 0) ? sum / totalUnits : 0.0f;
}

string calculateStatus(float gpa) {
    if (gpa >= 14.0f)
        return "Passed";
    else if (gpa >= 10.0f)
        return "Conditional";
    else
        return "Failed";
}

void addStudent() {
    Student newStudent;

    cout << "Enter student name: ";
    cin.ignore();
    getline(cin, newStudent.name);

    cout << "Enter student ID: ";
    cin >> newStudent.id;

    int courseCount;
    do {
        cout << "Enter number of courses (1-20 recommended): ";
        cin >> courseCount;
    } while (courseCount < 1);

    newStudent.courses.reserve(courseCount);

    for (int i = 0; i < courseCount; ++i) {
        Course c;

        cout << "\nCourse " << (i + 1) << " name: ";
        cin.ignore();
        getline(cin, c.name);

        do {
            cout << "Course grade (0-20): ";
            cin >> c.grade;
        } while (c.grade < 0 || c.grade > 20);

        do {
            cout << "Course unit (>=1): ";
            cin >> c.unit;
        } while (c.unit < 1);

        newStudent.courses.push_back(c);
    }

    newStudent.gpa = calculateGPA(newStudent);
    newStudent.status = calculateStatus(newStudent.gpa);

    students.push_back(newStudent);
    cout << "\nStudent added successfully!\n";
}

void classStatistics() {
    if (students.empty()) {
        cout << "No students available.\n";
        return;
    }

    float sum = 0.0f;
    size_t maxIndex = 0;
    size_t minIndex = 0;

    for (size_t i = 0; i < students.size(); ++i) {
        sum += students[i].gpa;

        if (students[i].gpa > students[maxIndex].gpa)
            maxIndex = i;

        if (students[i].gpa < students[minIndex].gpa)
            minIndex = i;
    }

    float average = sum / students.size();

    cout << "\n===== CLASS STATISTICS =====\n";
    cout << "Total Students     : " << students.size() << endl;
    cout << "Class Average GPA  : " << fixed << setprecision(2) << average << endl;

    cout << "\nHighest GPA:\n";
    cout << "  Name: " << students[maxIndex].name << endl;
    cout << "  GPA : " << fixed << setprecision(2) << students[maxIndex].gpa << endl;

    cout << "\nLowest GPA:\n";
    cout << "  Name: " << students[minIndex].name << endl;
    cout << "  GPA : " << fixed << setprecision(2) << students[minIndex].gpa << endl;
}

void showAllStudents() {
    if (students.empty()) {
        cout << "No students available.\n";
        return;
    }

    cout << "\n===== ALL STUDENTS REPORT =====\n";
    cout << "Total students: " << students.size() << "\n\n";

    for (size_t i = 0; i < students.size(); ++i) {
        const auto& s = students[i];

        cout << "Student #" << (i + 1) << endl;
        cout << "  Name       : " << s.name << endl;
        cout << "  ID         : " << s.id << endl;
        cout << "  Courses (" << s.courses.size() << "):\n";

        for (size_t j = 0; j < s.courses.size(); ++j) {
            const auto& c = s.courses[j];
            cout << "    " << (j + 1) << ". " << left << setw(20) << c.name
                 << " | Grade: " << c.grade
                 << " | Unit: " << c.unit << endl;
        }

        cout << "  GPA        : " << fixed << setprecision(2) << s.gpa << endl;
        cout << "  Status     : " << s.status << endl; 
        if(s.gpa>=18.0f){
            cout<<"note:excellent student."<<endl;
        }
        cout << "----------------------------------------\n";
    }
}

int main() {
    int choice;

    do {
        cout << "\n==============================\n";
        cout << "   ADVANCED STUDENT GRADING SYSTEM   \n";
        cout << "==============================\n";
        cout << "1. Add New Student\n";
        cout << "2. Show Class Statistics\n";
        cout << "3. Show All Students Report\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                classStatistics();
                break;
            case 3:
                showAllStudents();
                break;
            case 0:
                cout << "Goodbye!\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}