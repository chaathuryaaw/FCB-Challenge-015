
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Student {
    int id;
    int bio_marks[3];
    int math_marks[3];
    double total_marks;
    int school_rank;
    int class_rank;
};

void read_marks(const string& file_name, vector<Student>& students) {
    ifstream file(file_name);
    if (!file.is_open()) {
        cerr << "Error opening file: " << file_name << endl;
        exit(1);
    }
    int id;
    int marks[6];
    while (file >> id) {
        Student student;
        student.id = id;
        for (int i = 0; i < 6; i++) {
            file >> marks[i];
        }
        for (int i = 0; i < 3; i++) {
            student.bio_marks[i] = marks[i];
            student.math_marks[i] = marks[i + 3];
        }
        students.push_back(student);
    }
    file.close();
}

void calculate_total_marks(vector<Student>& students) {
    for (Student& student : students) {
        student.total_marks = 0;
        for (int i = 0; i < 3; i++) {
            student.total_marks += student.bio_marks[i];
            student.total_marks += student.math_marks[i];
        }
    }
}

void calculate_ranks(vector<Student>& students) {
    sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.total_marks > b.total_marks;
    });
    for (int i = 0; i < students.size(); i++) {
        students[i].school_rank = i + 1;
    }
    for (int i = 0; i < students.size(); i++) {
        int class_rank = 1;
        for (int j = i - 1; j >= 0; j--) {
            if (students[i].total_marks != students[j].total_marks) {
                break;
            }
            class_rank++;
        }
        students[i].class_rank = class_rank;
    }
}

void print_ranks(const vector<Student>& students) {
    cout << "ID\tTotal Marks\tSchool Rank\tClass Rank" << endl;
    for (const Student& student : students) {
        cout << student.id << "\t" << student.total_marks << "\t" << student.school_rank << "\t" << student.class_rank << endl;
    }
}

void write_ranks(const string& file_name, const vector<Student>& students) {
    ofstream file(file_name);
    if (!file.is_open()) {
        cerr << "Error opening file: " << file_name << endl;
        exit(1);
    }
    file << "ID\tTotal Marks\tSchool Rank\tClass Rank" << endl;
    for (const Student& student : students) {
        file << student.id << "\t" << student.total_marks << "\t" << student.school_rank << "\t" << student.class_rank << endl;
    }
    file.close();
}

int main() {
    vector<Student> students;
    read_marks("marks.txt", students);
    calculate_total_marks(students);
    calculate_ranks(students);
    print_ranks(students);
    write_ranks("ranks.txt", students);
    return 0;
}