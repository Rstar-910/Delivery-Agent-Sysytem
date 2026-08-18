#include <iostream>
#include <map>
#include <iomanip>
#include <vector>

#include "common.h"

using namespace std;

void generateReport()
{
    vector<Order> orders = loadOrders();
    map<string, int> statusCount;

    cout << "Generating report...\n";
    cout << "------------------------------------------------------------------------------------------------\n";
    cout << left << setw(10) << "Order ID"
         << setw(18) << "Customer"
         << setw(30) << "Address"
         << setw(16) << "Status"
         << setw(14) << "Scheduled" << "\n";
    cout << "------------------------------------------------------------------------------------------------\n";

    for (size_t i = 0; i < orders.size(); i++)
    {
        cout << left << setw(10) << orders[i].orderId
             << setw(18) << orders[i].customerName
             << setw(30) << orders[i].address
             << setw(16) << orders[i].status
             << setw(14) << orders[i].scheduledDate << "\n";
        statusCount[orders[i].status]++;
    }

    if (orders.empty())
    {
        cout << "No records found in the database.\n";
    }
    else
    {
        cout << "------------------------------------------------------------------------------------------------\n";
        cout << "Total records: " << orders.size() << "\n";
        cout << "Status Summary:\n";

        for (map<string, int>::const_iterator it = statusCount.begin(); it != statusCount.end(); ++it)
        {
            cout << "- " << it->first << ": " << it->second << "\n";
        }
    }

    pauseForUser();
    clearScreen();
}