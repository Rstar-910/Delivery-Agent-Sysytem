#include <bits/stdc++.h>
#include <fstream>
#include <iomanip>
#include <conio.h>

using namespace std;

int getNextOrderId()
{
    ifstream file("order_id.txt");
    int order_id = 0;

    if (file.is_open())
    {
        file >> order_id;
    }
    file.close();

    return order_id + 1;
}

void updateOrderId(int order_id)
{
    ofstream file("order_id.txt");
    file << order_id;
    file.close();
}

void shipaddress()
{
    // string Name, Address;
    // cout << "Enter Name : ";
    // cin >> Name;
    // cout << "Enter Address : ";
    // getline(cin, Address);

    ofstream file("database.txt", ios::app); // Open file in append mode

    string name, status, address;
    int order_id = getNextOrderId();

    cout << "Enter Name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    getline(cin, name);

    cout << "Enter Address: ";
    // cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, address);

    // Write the data to the file
    file << order_id << "," << name << "," << address << ",\n";
    file.close();

    updateOrderId(order_id);
    cout << "Press any key to exit!!!";
    _getch();
    cout << "\033[2J\033[H";

    return;
}

void cancel()
{
    ifstream file("database.txt");
    ofstream tempFile("temp.txt"); // Temporary file to store remaining records

    if (file.is_open() && tempFile.is_open())
    {
        string line;
        string order_id_to_delete;

        cout << "Enter Order ID of the record to delete: ";
        cin >> order_id_to_delete;

        bool found = false;

        while (getline(file, line))
        {
            // Extract Order ID from the line
            size_t pos = line.find(',');
            string current_order_id = line.substr(0, pos); // Extract from the start until the first comma

            // If the current Order ID doesn't match the one to delete, write it to the temp file
            if (current_order_id != order_id_to_delete)
            {
                tempFile << line << endl;
            }
            else
            {
                found = true;
            }
        }

        file.close();
        tempFile.close();

        // Remove the old file and rename the temp file to the original file name
        remove("database.txt");
        rename("temp.txt", "database.txt");

        if (found)
        {
            cout << "Order cancelled successfully!" << endl;
        }
        else
        {
            cout << "Record with Order ID " << order_id_to_delete << " not found." << endl;
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

void viewStatus()
{
    ifstream file("database.txt");

    string line;
    string order_id_to_view;

    cout << "Enter Order ID to view the status: ";
    cin >> order_id_to_view;

    bool found = false;

    while (getline(file, line))
    {
        // Extract Order ID from the line
        size_t pos = line.find(',');
        string current_order_id = line.substr(0, pos); // Extract Order ID

        if (current_order_id == order_id_to_view)
        {
            // Extract the status by finding the last comma
            size_t last_comma_pos = line.rfind(',');
            string status = line.substr(last_comma_pos + 1); // Extract Status

            cout << "Order ID: " << current_order_id << ", Status: " << status << endl;
            found = true;
            break; // Exit the loop since the order is found
        }
    }

    if (!found)
    {
        cout << "Record with Order ID " << order_id_to_view << " not found." << endl;
    }

    file.close();
    cout << "Press any key to exit!!!";
    _getch();
    cout << "\033[2J\033[H";
}

void viewrecords()
{
    ifstream file("database.txt");
    string line;
    string name;
    cout << "Enter your name to view you records:  ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, name);
    bool found = false;

    while (getline(file, line))
    {
        size_t first_comma = line.find(",");
        size_t second_comma = line.find(",", first_comma + 1);
        string currentname = line.substr(first_comma + 1, second_comma - first_comma - 1);

        if (name == currentname)
        {
            cout << line << endl;
            found = true;
        }
    }
    if (!found)
    {
        cout << "No records found!!\n";
    }
    file.close();
    cout << "Press any key to exit!!!";
    _getch();
    cout << "\033[2J\033[H";
}

void reschedule()
{
    int date;
    cout << "Enter the reschedule date: ";
    cin >> date;
    cout << "Order rescheduled successfully!!!\n";
    cout << "Press any key to exit!!!";
    _getch();
    cout << "\033[2J\033[H";
}

// void printbill(string name, string address, int order_id, float price)
// {
//     ifstream file("database.txt");
//     string name;
// }

void bookdelivery()
{
    cout << "*****Enter the Shipping Details*****\n";
    shipaddress();
    cout << "Order Placed Successfully!!\n";
    cout << "Press any key to exit!!!";
    _getch();
    cout << "\033[2J\033[H";
}

// int main()
// {
//     cout << "\033[2J\033[H"; // Escape sequence to clear screen
//     cout << "\033[1m*****Enter the source details*****\033[0m\n";

//     // cout << "\n\n";

//     // cout << "\033[2J\033[H";
//     // cout << "\033[1m*****Enter the destination details*****\033[0m\n";
//     // cout << "Enter Name : ";
//     // getline(cin, name);
//     // cout << "Enter Address : ";
//     // getline(cin, address);

//     // dest(name, address);

//     return 0;
// }