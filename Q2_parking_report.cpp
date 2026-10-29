/*
 * Name       : Muhammad Abuzar
 * Reg No     : L1F25BSCS0248
 * Assignment : 02 - File Handling
 * Question   : Q2 - Parking Report
 */

// Allow strcpy when compiling with Visual Studio, as permitted by the assignment.
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int main() {
    ifstream inFile("parking.txt");
    if (!inFile) {
        cout << "parking.txt not found!" << endl;
        return 1;
    }

    int d, m, y;
    char slash;
    inFile >> d >> slash >> m >> slash >> y;
    inFile.ignore(100, '\n');
    inFile.ignore(100, '\n');

    cout << "Parking report for " << d << "/" << m << "/" << y << endl;
    ofstream receipts("receipts.txt");
    receipts << "Receipts for " << d << "/" << m << "/" << y << endl;

    char plate[15], type, inTime[6], outTime[6];
    char longestPlate[15] = "";
    int vehicles = 0, cars = 0, bikes = 0, total = 0;
    int longestMinutes = -1;

    while (vehicles < 30 && inFile >> plate >> type >> inTime >> outTime) {
        int inHour = (inTime[0] - '0') * 10 + inTime[1] - '0';
        int inMinute = (inTime[3] - '0') * 10 + inTime[4] - '0';
        int outHour = (outTime[0] - '0') * 10 + outTime[1] - '0';
        int outMinute = (outTime[3] - '0') * 10 + outTime[4] - '0';
        int minutes = (outHour * 60 + outMinute) - (inHour * 60 + inMinute);
        int hoursCharged = (minutes + 59) / 60;
        if (hoursCharged == 0) hoursCharged = 1;
        int rate = (type == 'C') ? 100 : 40;
        int fee = hoursCharged * rate;

        cout << plate << " " << ((type == 'C') ? "Car" : "Bike") << " "
             << minutes / 60 << " h " << minutes % 60 << " min Fee: " << fee << endl;
        receipts << plate << " " << fee << endl;
        if (type == 'C') cars++;
        else bikes++;
        vehicles++;
        total += fee;
        if (minutes > longestMinutes) {
            longestMinutes = minutes;
            strcpy(longestPlate, plate);
        }
    }
    inFile.close();
    receipts.close();

    if (vehicles == 0) {
        cout << "No vehicles found!" << endl;
        return 0;
    }
    cout << "Vehicles: " << vehicles << endl;
    cout << "Cars: " << cars << " Bikes: " << bikes << endl;
    cout << "Total collected: " << total << endl;
    cout << "Longest stay: " << longestPlate << " (" << longestMinutes / 60
         << " h " << longestMinutes % 60 << " min)" << endl;
    return 0;
}
