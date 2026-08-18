#ifndef COMMON_H
#define COMMON_H

#include <string>
#include <vector>

struct Order
{
    int orderId;
    std::string customerName;
    std::string address;
    std::string status;
    std::string scheduledDate;
};

struct CourierCompany
{
    std::string companyName;
    std::string contactNumber;
    std::string location;
    double packagingPrice;
    double discount;
};

std::vector<Order> loadOrders();
bool saveOrders(const std::vector<Order> &orders);
bool saveCourierCompany(const CourierCompany &company);
int getNextOrderId();
void updateOrderId(int orderId);

void clearScreen();
void pauseForUser();
int readInt(const std::string &prompt);

#endif