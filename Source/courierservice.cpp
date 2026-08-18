#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include "common.h"

using namespace std;

void courierdetails()
{
    string compname;
    cout << "Enter the company name - ";
    getline(cin, compname);

    string location;
    cout << "Enter the company location: ";
    getline(cin, location);

    string number;
    cout << "Enter the contact number: ";
    getline(cin, number);

    float packagingprice;
    cout << "Enter the charge - ";
    cin >> packagingprice;

    float discount;
    cout << "Enter discount rates: ";
    cin >> discount;

    CourierCompany company;
    company.companyName = compname;
    company.contactNumber = number;
    company.location = location;
    company.packagingPrice = packagingprice;
    company.discount = discount;

    if (saveCourierCompany(company))
    {
        cout << "Courier details saved successfully.\n";
    }
    else
    {
        cout << "Unable to save courier details.\n";
    }

    pauseForUser();
    clearScreen();
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
    vector<Order> orders = loadOrders();
    int orderId = readInt("Enter Order ID to update: ");

    string newStatus;
    cout << "Enter new status (PickedUp/InTransit/Delivered): ";
    getline(cin, newStatus);

    bool found = false;
    for (size_t i = 0; i < orders.size(); i++)
    {
        if (orders[i].orderId == orderId)
        {
            orders[i].status = newStatus;
            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "Record with Order ID " << orderId << " not found.\n";
    }
    else if (!saveOrders(orders))
    {
        cout << "Unable to update database.\n";
    }
    else
    {
        cout << "Status updated successfully.\n";
    }

    pauseForUser();
    clearScreen();
}