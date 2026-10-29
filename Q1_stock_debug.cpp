/*
 * Name       : Muhammad Abuzar
 * Reg No     : L1F25BSCS0248
 * Assignment : 02 - File Handling
 * Question   : Q1 - Stock Report (Debugging)
 */

#include <iostream>
// FIX 1: Include fstream so ifstream and ofstream are declared.
#include <fstream>
using namespace std;

int main() {
    ifstream inFile("stock.txt");
    // FIX 2: A failed stream means the input file could not be opened.
    if (!inFile) {
        cout << "stock.txt not found!" << endl;
        return 1;
    }

    // FIX 3: Append reorder entries while preserving existing lines.
    ofstream reorder("reorder.txt", ios::app);

    char code[10];
    int qty, count = 0, low = 0;
    double price;
    // FIX 4: Keep fractional stock values by using a double total.
    double total = 0;

    // FIX 5: Skip the column heading before extracting item records.
    inFile.ignore(100, '\n');
    while (count < 50 && inFile >> code >> qty >> price) {
        count++;
        total = total + qty * price;
        if (qty < 10) {
            // FIX 6: End each reorder record with a newline.
            reorder << code << " " << qty << endl;
            low++;
        }
    }
    inFile.close();
    reorder.close();

    cout << "Items: " << count << endl;
    cout << "Total stock value: " << total << endl;
    cout << "Low stock items: " << low << endl;
    return 0;
}
