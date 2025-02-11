#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <iomanip>

using namespace std;

// Define the student struct
struct student {
    string name;
    int id;
    char gender;
    float gpa;
};

// Define the course struct
struct course {
    string name;
    int id;
    vector<string> lecture_list;
    vector<student*> student_list;
};

// Function to find a student by ID
student* findstudent(vector<student>& allstudents, int key) {
    for (unsigned int i = 0; i < allstudents.size(); i++) {
        if (allstudents[i].id == key) return &allstudents[i];
    }
    return nullptr; // Return nullptr if student not found
}

// Function to print the report
void printreport(vector<course>& allcourses) {
    for (unsigned int i = 0; i < allcourses.size(); i++) {
        cout << "-----------------------------------------------------------------------------\n";
        cout << left << setw(20);
        cout << "Course:" << allcourses[i].name << " (" << allcourses[i].id << ")\n\n";
        cout << left << setw(20);
        cout << "Lecturers:";
        for (unsigned int j = 0; j < allcourses[i].lecture_list.size(); j++) {
            if (j != 0) cout << ", ";
            cout << allcourses[i].lecture_list[j];
        }
        cout << "\n\n";
        cout << left << setw(20);
        cout << "Students:";
        for (unsigned int j = 0; j < allcourses[i].student_list.size(); j++) {
            if (j != 0) cout << left << setw(20) << " ";
            cout << left << setw(20) << allcourses[i].student_list[j]->name;
            cout << left << setw(10) << allcourses[i].student_list[j]->id;
            cout << left << setw(3) << allcourses[i].student_list[j]->gender;
            cout << left << setw(5) << setprecision(2) << fixed << allcourses[i].student_list[j]->gpa << "\n";
        }
    }
    cout << "-----------------------------------------------------------------------------\n";
}

int main() {
    ifstream student_file("students.txt");
    ifstream course_file("courses.txt");
    vector<student> allstudents;
    vector<course> allcourses;

    string textline;

    // Read student data from students.txt
    while (getline(student_file, textline)) {
        student s;
        char name[100];
        sscanf(textline.c_str(), "%[^,],%d,%c,%f", name, &s.id, &s.gender, &s.gpa);
        s.name = name;
        allstudents.push_back(s);
    }

    int state = 1;
    course* current_course = nullptr;

    // Read course data from courses.txt
    while (getline(course_file, textline)) {
        if (state == 1) {
            course c;
            int loc = textline.find_first_of('(');
            c.name = textline.substr(0, loc - 1);
            c.id = atoi(textline.substr(loc + 1, 5).c_str());
            getline(course_file, textline);
            allcourses.push_back(c);
            current_course = &allcourses.back(); // Point to the recently added course
            state = 2;
        } else if (state == 2) {
            if (textline == "> Students") {
                state = 3;
            } else {
                // Append to lecture_list
                current_course->lecture_list.push_back(textline);
            }
        } else {
            if (textline == "---------------------------------------") {
                state = 1;
            } else {
                // Find student and append to student_list
                student* p = findstudent(allstudents, atoi(textline.c_str()));
                if (p) {
                    current_course->student_list.push_back(p);
                }
            }
        }
    }

    // Print the report
    printreport(allcourses);

    return 0;
}