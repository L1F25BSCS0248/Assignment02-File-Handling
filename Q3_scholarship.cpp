/*
 * Name       : Muhammad Abuzar
 * Reg No     : L1F25BSCS0248
 * Assignment : 02 - File Handling
 * Question   : Q3 - Scholarship List
 */

// Allow strcpy when compiling with Visual Studio, as permitted by the assignment.
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int main() {
    char path[100];
    cout << "Enter the file name: ";
    cin.getline(path, 100);

    ifstream inFile(path);
    if (!inFile.is_open()) {
        cout << "Could not open " << path << "!" << endl;
        return 1;
    }

    // Start a fresh scholarship file for every successfully opened class file.
    ofstream scholarship("scholarship.txt");
    int n;
    if (!(inFile >> n)) {
        inFile.close();
        scholarship.close();
        cout << "No students found!" << endl;
        return 0;
    }
    if (n > 30) {
        inFile.close();
        scholarship.close();
        cout << "Too many students!" << endl;
        return 0;
    }
    inFile.ignore(100, '\n');

    char name[30], topName[30] = "";
    double cgpa, total = 0, highest = -1;
    int count = 0, eligible = 0;
    for (int i = 0; i < n; i++) {
        if (!inFile.getline(name, 30, ',')) break;
        if (!(inFile >> cgpa)) break;
        inFile.ignore(100, '\n');
        cout << "[" << name << "] CGPA: " << cgpa << endl;
        total += cgpa;
        count++;
        if (cgpa >= 3.50) {
            scholarship << name << "," << cgpa << endl;
            eligible++;
        }
        if (cgpa > highest) {
            highest = cgpa;
            strcpy(topName, name);
        }
    }
    inFile.close();
    scholarship.close();

    if (count < n) cout << "Warning: only " << count << " of " << n << " records found." << endl;
    if (count == 0) {
        cout << "No students found!" << endl;
        return 0;
    }
    cout << "Students: " << count << endl;
    cout << "Average CGPA: " << total / count << endl;
    cout << "Eligible for scholarship: " << eligible << endl;
    cout << "Top student: " << topName << " (" << highest << ")" << endl;
    return 0;
}
