#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <clocale>

using namespace std;

class Student {
public:
    int id;
    string name;
    int age;
    double grade;
};

void addStudent(vector<Student>& students, const Student& student) {
    students.push_back(student);
}

void saveToFile(const vector<Student>& students, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& student : students) {
            file << student.id << " " << student.name << " " << student.age << " " << student.grade << "\n";
        }
        file.close();
    }
    else {
        cerr << "Невозможно открыть файл: " << filename << endl;
    }
}

void readFromFile(vector<Student>& students, const string& filename) {
    students.clear();
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            Student student;

            ss >> student.id;

            string name;
            ss >> ws;
            string token;
            string remaining;
            getline(ss, remaining);
            size_t last_space = remaining.rfind(' ');
            size_t second_last_space = remaining.rfind(' ', last_space - 1);
            name = remaining.substr(0, second_last_space);
            student.name = name;

            stringstream remaining_ss(remaining.substr(second_last_space));
            remaining_ss >> student.age >> student.grade;

            students.push_back(student);
        }
        file.close();
    }
    else {
        cerr << "Невозможно открыть файл " << filename << endl;
    }
}

void updateStudent(vector<Student>& students, int id, const Student& updatedStudent) {
    for (auto& student : students) {
        if (student.id == id) {
            student = updatedStudent;
            return;
        }
    }
    cerr << "Студент с ID " << id << " не нашлось" << endl;
}

void deleteStudent(vector<Student>& students, int id) {
    for (auto it = students.begin(); it != students.end(); ++it) {
        if (it->id == id) {
            students.erase(it);
            return;
        }
    }
    cerr << "Студент с ID " << id << " не нашлось" << endl;
}

void printStudents(const vector<Student>& students) {
    for (const auto& student : students) {
        cout << "ID: " << student.id << ", Name: " << student.name
            << ", Age: " << student.age << ", Grade: " << student.grade << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    vector<Student> students;
    const string filename = "students.txt";

    Student s1 = { 1, "маша", 18, 85.5 };
    Student s2 = { 2, "глеб", 20, 55.0 };
    addStudent(students, s1);
    addStudent(students, s2);

    saveToFile(students, filename);

    students.clear();
    readFromFile(students, filename);
    cout << "После чтения из файла:" << endl;
    printStudents(students);

    Student updatedStudent = { 1, "Камилла (обновленно)", 18, 100.0 };
    updateStudent(students, 1, updatedStudent);
    cout << "\nПосле обновления студента ID 1:" << endl;
    printStudents(students);

    deleteStudent(students, 2);
    cout << "\nПосле удаления студента ID 2:" << endl;
    printStudents(students);

    saveToFile(students, filename);

    return 0;
}