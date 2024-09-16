#include <iostream>
#include <fstream>
#include <iomanip>
#include <conio.h>

using namespace std;

void generateReport()
{
    ifstream file("database.txt");

    if (!file.is_open())
    {
        cout << "Error opening file!" << endl;
        return;
    }

    string line;
    int recordCount = 0;
    cout << "Generating report...\n";
    cout << "-------------------------------------------------------------------------\n";
    cout << left << setw(10) << "Name" << setw(15) << "Order ID" << setw(25) << "Address" << setw(15) << "Status" << endl;
    cout << "------------------------------------------------------------------------\n";

    while (getline(file, line))
    {
        size_t first_comma = line.find(',');
        size_t second_comma = line.find(',', first_comma + 1);
        size_t third_comma = line.find(',', second_comma + 1);
        size_t fourth_comma = line.find(',', third_comma + 1);

        string name = line.substr(0, first_comma);
        string order_id = line.substr(first_comma + 1, second_comma - first_comma - 1);
        string address = line.substr(second_comma + 1, third_comma - second_comma - 1);
        string status = line.substr(third_comma + 1, fourth_comma - third_comma - 1);

        cout << left << setw(10) << name << setw(15) << order_id << setw(25) << address << setw(15) << status << endl;
        recordCount++;
    }

    if (recordCount == 0)
    {
        cout << "No records found in the database." << endl;
    }
    else
    {
        cout << "------------------------------------------------------------------------\n";
        cout << "Total records: " << recordCount << endl;
    }

    file.close();
    cout << "Press any key to exit!!!";
    _getch();
    cout << "\033[2J\033[H";
}