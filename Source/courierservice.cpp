#include <bits/stdc++.h>
#include <fstream>
#include <string>
#include <conio.h>

using namespace std;

void courierdetails()
{
    ofstream file("compdatabase.txt", ios::app);

    string compname;
    cout << "Enter the company name - ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, compname);

    string location;
    cout << "Enter the company location: ";
    getline(cin, location);

    int number;
    cout << "Enter the contact number: ";
    cin >> number;

    float packagingprice;
    cout << "Enter the charge - ";
    cin >> packagingprice;

    float discount;
    cout << "Enter discount rates: ";
    cin >> discount;

    file << compname << " , " << number << " , " << location << "," << packagingprice << "," << discount << "\n";
    file.close();
    cout << "Press any key to exit!!!";
    _getch();
    cout << "\033[2J\033[H";
}

void serviceoffering()
{
    float packagingprice;
    cout << "Enter the charge - ";
    cin >> packagingprice;

    float discount;
    cout << "Enter discount rates: ";
    cin >> discount;
}

void updateStatus()
{
    ifstream file("database.txt");
    ofstream tempFile("temp.txt"); // Temporary file to store updated records

    if (file.is_open() && tempFile.is_open())
    {
        string line;
        string order_id_to_update;
        string new_status;

        cout << "Enter Order ID of the record to update: ";
        cin >> order_id_to_update;
        cout << "Enter new status: ";
        cin >> new_status;

        bool found = false;

        while (getline(file, line))
        {
            // Extract Order ID from the line
            size_t pos = line.find(',');
            string current_order_id = line.substr(0, pos); // Extract from the start until the first comma

            if (current_order_id == order_id_to_update)
            {
                found = true;

                // Find the position of the last comma (before the status)
                size_t last_comma_pos = line.rfind(',');

                // Replace the status by creating a new line with the updated status
                string updated_line = line.substr(0, last_comma_pos + 1) + new_status;

                // Write the updated line to the temp file
                tempFile << updated_line << endl;
            }
            else
            {
                // Write the unchanged line to the temp file
                tempFile << line << endl;
            }
        }

        file.close();
        tempFile.close();

        // Remove the old file and rename the temp file to the original file name
        remove("database.txt");
        rename("temp.txt", "database.txt");

        if (found)
        {
            cout << "Status updated successfully!" << endl;
        }
        else
        {
            cout << "Record with Order ID " << order_id_to_update << " not found." << endl;
        }
    }
    else
    {
        cout << "Unable to open file." << endl;
    }
    cout << "Press any key to exit!!!";
    _getch();
    cout << "\033[2J\033[H";
}