// CodeAlpha C++ Internship - Task 1: CGPA Calculator
// Author: Himanshu Srivastava
// Supports multiple semesters, letter grades (10-point scale) or numeric grade points.

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <limits>
#include <algorithm>

using namespace std;

struct Course {
    string name;
    double gradePoint;
    double credits;
};

struct Semester {
    vector<Course> courses;
    double totalCredits = 0;
    double totalPoints = 0;

    double gpa() const { return totalCredits > 0 ? totalPoints / totalCredits : 0.0; }
};

const map<string, double> GRADE_MAP = {
    {"O", 10}, {"A+", 9}, {"A", 8}, {"B+", 7}, {"B", 6}, {"C", 5}, {"P", 4}, {"F", 0}};

string toUpper(string s) {
    transform(s.begin(), s.end(), s.begin(), ::toupper);
    return s;
}

// Reads a grade as a letter (O, A+, A, B+, B, C, P, F) or a number between 0 and 10.
double readGrade(const string& prompt) {
    while (true) {
        cout << prompt;
        string input;
        cin >> input;
        string up = toUpper(input);

        auto it = GRADE_MAP.find(up);
        if (it != GRADE_MAP.end()) return it->second;

    

        try {
            size_t pos = 0;
            double v = stod(input, &pos);
            if (pos == input.size() && v >= 0 && v <= 10) return v;
        } catch (...) {
        }
        cout << "  Invalid grade. Use O, A+, A, B+, B, C, P, F or a number from 0 to 10.\n";
    }
}

double readPositive(const string& prompt, double maxValue) {
    while (true) {
        cout << prompt;
        double v;
        if (cin >> v && v > 0 && v <= maxValue) return v;
        cout << "  Invalid input. Enter a value greater than 0 and up to " << maxValue << ".\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int readInt(const string& prompt, int lo, int hi) {
    while (true) {
        cout << prompt;
        int v;
        if (cin >> v && v >= lo && v <= hi) return v;
        cout << "  Invalid input. Enter a number between " << lo << " and " << hi << ".\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

Semester inputSemester(int semNo) {
    Semester sem;
    cout << "\n--- Semester " << semNo << " ---\n";
    int n = readInt("Number of courses: ", 1, 20);

    for (int i = 1; i <= n; i++) {
        Course c;
        cout << "\nCourse " << i << "\n";
        cout << "  Course name: ";
        cin >> ws;
        getline(cin, c.name);
        c.gradePoint = readGrade("  Grade (O/A+/A/B+/B/C/P/F or 0-10): ");
        c.credits = readPositive("  Credit hours: ", 10);

        sem.totalCredits += c.credits;
        sem.totalPoints += c.gradePoint * c.credits;
        sem.courses.push_back(c);
    }
    return sem;
}

void printSemester(const Semester& sem, int semNo) {
    cout << "\n==================== Semester " << semNo << " Report ====================\n";
    cout << left << setw(25) << "Course" << right << setw(8) << "Grade" << setw(10) << "Credits"
         << setw(14) << "Grade Points" << "\n";
    cout << string(57, '-') << "\n";
    for (const auto& c : sem.courses) {
        cout << left << setw(25) << c.name.substr(0, 24) << right << fixed << setprecision(1)
             << setw(8) << c.gradePoint << setw(10) << c.credits << setw(14)
             << c.gradePoint * c.credits << "\n";
    }
    cout << string(57, '-') << "\n";
    cout << "Total Credits : " << sem.totalCredits << "\n";
    cout << "Total Points  : " << sem.totalPoints << "\n";
    cout << "Semester GPA  : " << setprecision(2) << sem.gpa() << "\n";
}

int main() {
    cout << "=====================================\n";
    cout << "        CGPA CALCULATOR (C++)\n";
    cout << "=====================================\n";

    int semCount = readInt("How many semesters do you want to enter? ", 1, 12);

    vector<Semester> semesters;
    double allCredits = 0, allPoints = 0;

    for (int s = 1; s <= semCount; s++) {
        Semester sem = inputSemester(s);
        allCredits += sem.totalCredits;
        allPoints += sem.totalPoints;
        semesters.push_back(sem);
    }

    for (int s = 0; s < (int)semesters.size(); s++) printSemester(semesters[s], s + 1);

    double cgpa = allCredits > 0 ? allPoints / allCredits : 0.0;
    cout << "\n=====================================\n";
    cout << "Total Credits (all semesters): " << fixed << setprecision(1) << allCredits << "\n";
    cout << "Overall CGPA                 : " << setprecision(2) << cgpa << "\n";
    cout << "Approx. Percentage (CGPA x 9.5): " << setprecision(2) << cgpa * 9.5 << "%\n";
    cout << "=====================================\n";
    return 0;
}
