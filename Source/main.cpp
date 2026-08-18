#include <iostream>
#include "customer.h"
#include "admin.h"
#include "courierservice.h"
#include "common.h"

using namespace std;

int main()
{
    bool running = true;
    while (running)
    {
        cout << "1. Login as a Customer\n";
        cout << "2. Login as a Admin\n";
        cout << "3. Login as a Courier Service\n";
        cout << "4. EXIT\n";

        int choice = readInt("Enter the choice: ");

        clearScreen();

        switch (choice)
        {
        case 1:
        {
            bool inCustomerMenu = true;
            while (inCustomerMenu)
            {
                cout << "1. Book Delivery\n";
                cout << "2. View Status\n";
                cout << "3. Cancel Order\n";
                cout << "4. View Past Records\n";
                cout << "5. Reschedule Order\n";
                cout << "6. EXIT\n";

                int custchoice = readInt("Enter the choice: ");
                clearScreen();

                switch (custchoice)
                {
                case 1:
                    bookdelivery();
                    break;
                case 2:
                    viewStatus();
                    break;
                case 3:
                    cancel();
                    break;
                case 4:
                    viewrecords();
                    break;
                case 5:
                    reschedule();
                    break;
                case 6:
                    inCustomerMenu = false;
                    break;
                default:
                    cout << "Enter the valid choice!!!\n";
                }
            }
            break;
        }
        case 2:
        {
            bool inAdminMenu = true;
            while (inAdminMenu)
            {
                cout << "1. Generate Report\n";
                cout << "2. EXIT!!!\n";
                int adminchoice = readInt("Enter the choice: ");
                clearScreen();

                switch (adminchoice)
                {
                case 1:
                    generateReport();
                    break;
                case 2:
                    inAdminMenu = false;
                    break;
                default:
                    cout << "Enter the valid choice!!!\n";
                }
            }
            break;
        }
        case 3:
        {
            bool inCourierMenu = true;
            while (inCourierMenu)
            {
                cout << "1. Enter details and service offerings\n";
                cout << "2. Update status\n";
                cout << "3. EXIT!!!\n";
                int CSchoice = readInt("Enter the choice: ");
                clearScreen();

                switch (CSchoice)
                {
                case 1:
                    courierdetails();
                    break;
                case 2:
                    updateStatus();
                    break;
                case 3:
                    inCourierMenu = false;
                    break;
                default:
                    cout << "Enter the valid choice!!!\n";
                }
            }
            break;
        }
        case 4:
            running = false;
            break;
        default:
            cout << "Enter the valid choice!!!\n";
        }
    }

    cout << "Program exited successfully!!!";
    return 0;
}