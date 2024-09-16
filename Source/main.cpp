#include <bits/stdc++.h>
#include <conio.h>
#include "customer.h"
#include "admin.h"
#include "courierservice.h"

using namespace std;

int main()
{
    while (1)
    {
    start:
        cout << "1. Login as a Customer\n";
        cout << "2. Login as a Admin\n";
        cout << "3. Login as a Courier Service\n";
        cout << "4. EXIT\n";

        int choice;
        cout << "Enter the choice: ";
        cin >> choice;

        cout << "\033[2J\033[H";

        switch (choice)
        {
        case 1:
            while (1)
            {

                cout << ("1. Book Delivery\n");
                cout << ("2. View Status\n");
                cout << ("3. Cancel Order\n");
                cout << ("4. View Past Records\n");
                cout << ("5. Reschedule Order\n");
                cout << ("6. EXIT\n");

                int custchoice;
                cout << "Enter the choice: ";
                cin >> custchoice;

                cout << "\033[2J\033[H";
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
                    goto start;
                default:
                    cout << "Enter the valid choice!!!\n";
                }
            }
            break;
        case 2:
            while (1)
            {
                cout << "1. Generate Report\n";
                cout << "2. EXIT!!!\n";
                cout << "Enter the choice: ";
                int adminchoice;
                cin >> adminchoice;

                cout << "\033[2J\033[H";
                switch (adminchoice)
                {
                case 1:
                    generateReport();
                    break;
                case 2:
                    goto start;
                default:
                    cout << "Enter the valid choice!!!\n";
                }
            }
            break;
        case 3:
            while (1)
            {
                cout << "1. Enter details and service offerings\n";
                cout << "2. Update status\n";
                cout << "3. EXIT!!!\n";
                cout << "Enter the choice: ";
                int CSchoice;
                cin >> CSchoice;

                cout << "\033[2J\033[H";
                switch (CSchoice)
                {
                case 1:
                    courierdetails();
                    break;
                case 2:
                    updateStatus();
                    break;
                case 3:
                    goto start;
                default:
                    cout << "Enter the valid choice!!!";
                }
            }
            break;
        case 4:
            goto end;
        default:
            cout << "Enter the valid choice!!!\n";
        }
    }
end:
    cout << "Program Exitted Successfully!!!";
    return 0;
}