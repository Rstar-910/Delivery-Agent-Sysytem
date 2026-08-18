#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include "common.h"

using namespace std;

void cancel()
{
    vector<Order> orders = loadOrders();
    int orderId = readInt("Enter Order ID to cancel: ");
    bool found = false;

    for (size_t i = 0; i < orders.size(); i++)
    {
        if (orders[i].orderId == orderId)
        {
            found = true;
            if (orders[i].status == "Delivered")
            {
                cout << "Delivered orders cannot be cancelled.\n";
            }
            else
            {
                orders[i].status = "Cancelled";
                cout << "Order cancelled successfully!\n";
            }
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

    pauseForUser();
    clearScreen();
}

void viewStatus()
{
    vector<Order> orders = loadOrders();
    int orderId = readInt("Enter Order ID to view status: ");
    bool found = false;

    for (size_t i = 0; i < orders.size(); i++)
    {
        if (orders[i].orderId == orderId)
        {
            cout << "Order ID: " << orders[i].orderId << "\n";
            cout << "Customer: " << orders[i].customerName << "\n";
            cout << "Address: " << orders[i].address << "\n";
            cout << "Scheduled Date: " << orders[i].scheduledDate << "\n";
            cout << "Status: " << orders[i].status << "\n";
            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "Record with Order ID " << orderId << " not found.\n";
    }

    pauseForUser();
    clearScreen();
}

void viewrecords()
{
    vector<Order> orders = loadOrders();
    string name;
    cout << "Enter your name to view records: ";
    getline(cin, name);
    bool found = false;

    for (size_t i = 0; i < orders.size(); i++)
    {
        if (name == orders[i].customerName)
        {
            cout << "Order ID: " << orders[i].orderId
                 << " | Address: " << orders[i].address
                 << " | Date: " << orders[i].scheduledDate
                 << " | Status: " << orders[i].status << "\n";
            found = true;
        }
    }

    if (!found)
    {
        cout << "No records found.\n";
    }

    pauseForUser();
    clearScreen();
}

void reschedule()
{
    vector<Order> orders = loadOrders();
    int orderId = readInt("Enter Order ID to reschedule: ");
    string newDate;
    cout << "Enter new date (DD-MM-YYYY): ";
    getline(cin, newDate);

    bool found = false;
    for (size_t i = 0; i < orders.size(); i++)
    {
        if (orders[i].orderId == orderId)
        {
            found = true;
            if (orders[i].status == "Cancelled" || orders[i].status == "Delivered")
            {
                cout << "This order cannot be rescheduled in its current state.\n";
            }
            else
            {
                orders[i].scheduledDate = newDate;
                orders[i].status = "Rescheduled";
                cout << "Order rescheduled successfully.\n";
            }
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

    pauseForUser();
    clearScreen();
}

// void printbill(string name, string address, int order_id, float price)
// {
//     ifstream file("database.txt");
//     string name;
// }

void bookdelivery()
{
    vector<Order> orders = loadOrders();
    Order order;

    cout << "***** Enter Shipping Details *****\n";
    order.orderId = getNextOrderId();

    cout << "Enter Name: ";
    getline(cin, order.customerName);

    cout << "Enter Address: ";
    getline(cin, order.address);

    cout << "Enter delivery date (DD-MM-YYYY): ";
    getline(cin, order.scheduledDate);

    order.status = "Booked";
    orders.push_back(order);

    if (saveOrders(orders))
    {
        updateOrderId(order.orderId);
        cout << "Order placed successfully! Your Order ID is " << order.orderId << ".\n";
    }
    else
    {
        cout << "Unable to save order. Please try again.\n";
    }

    pauseForUser();
    clearScreen();
}