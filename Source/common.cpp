#include "common.h"

#include <cstdlib>
#include <iostream>
#include <limits>
#include <sqlite3.h>

using namespace std;

namespace
{
const char *kDatabaseFile = "delivery_agent.db";

bool executeSql(sqlite3 *db, const char *sql)
{
    char *errorMessage = NULL;
    int rc = sqlite3_exec(db, sql, NULL, NULL, &errorMessage);
    if (rc != SQLITE_OK)
    {
        cerr << "SQLite error: " << (errorMessage ? errorMessage : "unknown") << "\n";
        if (errorMessage != NULL)
        {
            sqlite3_free(errorMessage);
        }
        return false;
    }

    return true;
}

sqlite3 *openDatabase()
{
    sqlite3 *db = NULL;
    if (sqlite3_open(kDatabaseFile, &db) != SQLITE_OK)
    {
        cerr << "Unable to open SQLite database.\n";
        if (db != NULL)
        {
            sqlite3_close(db);
        }
        return NULL;
    }

    const char *schemaSql =
        "CREATE TABLE IF NOT EXISTS orders ("
        "order_id INTEGER PRIMARY KEY,"
        "customer_name TEXT NOT NULL,"
        "address TEXT NOT NULL,"
        "status TEXT NOT NULL,"
        "scheduled_date TEXT NOT NULL,"
        "created_at DATETIME DEFAULT CURRENT_TIMESTAMP"
        ");"
        "CREATE INDEX IF NOT EXISTS idx_orders_customer ON orders(customer_name);"
        "CREATE INDEX IF NOT EXISTS idx_orders_status ON orders(status);"
        "CREATE TABLE IF NOT EXISTS courier_companies ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "company_name TEXT NOT NULL,"
        "contact_number TEXT NOT NULL,"
        "location TEXT NOT NULL,"
        "packaging_price REAL NOT NULL,"
        "discount REAL NOT NULL,"
        "created_at DATETIME DEFAULT CURRENT_TIMESTAMP"
        ");";

    if (!executeSql(db, schemaSql))
    {
        sqlite3_close(db);
        return NULL;
    }

    return db;
}
} // namespace

vector<Order> loadOrders()
{
    vector<Order> orders;
    sqlite3 *db = openDatabase();
    if (db == NULL)
    {
        return orders;
    }

    const char *query =
        "SELECT order_id, customer_name, address, status, scheduled_date "
        "FROM orders ORDER BY order_id;";
    sqlite3_stmt *stmt = NULL;

    if (sqlite3_prepare_v2(db, query, -1, &stmt, NULL) != SQLITE_OK)
    {
        cerr << "Failed to load orders from SQLite.\n";
        sqlite3_close(db);
        return orders;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        Order order;
        order.orderId = sqlite3_column_int(stmt, 0);
        order.customerName = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        order.address = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
        order.status = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
        order.scheduledDate = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4));
        orders.push_back(order);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return orders;
}

bool saveOrders(const vector<Order> &orders)
{
    sqlite3 *db = openDatabase();
    if (db == NULL)
    {
        return false;
    }

    if (!executeSql(db, "BEGIN TRANSACTION;"))
    {
        sqlite3_close(db);
        return false;
    }

    if (!executeSql(db, "DELETE FROM orders;"))
    {
        executeSql(db, "ROLLBACK;");
        sqlite3_close(db);
        return false;
    }

    const char *insertSql =
        "INSERT INTO orders(order_id, customer_name, address, status, scheduled_date) "
        "VALUES(?, ?, ?, ?, ?);";
    sqlite3_stmt *stmt = NULL;
    if (sqlite3_prepare_v2(db, insertSql, -1, &stmt, NULL) != SQLITE_OK)
    {
        executeSql(db, "ROLLBACK;");
        sqlite3_close(db);
        return false;
    }

    for (size_t i = 0; i < orders.size(); i++)
    {
        sqlite3_bind_int(stmt, 1, orders[i].orderId);
        sqlite3_bind_text(stmt, 2, orders[i].customerName.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 3, orders[i].address.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 4, orders[i].status.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 5, orders[i].scheduledDate.c_str(), -1, SQLITE_TRANSIENT);

        if (sqlite3_step(stmt) != SQLITE_DONE)
        {
            sqlite3_finalize(stmt);
            executeSql(db, "ROLLBACK;");
            sqlite3_close(db);
            return false;
        }

        sqlite3_reset(stmt);
        sqlite3_clear_bindings(stmt);
    }

    sqlite3_finalize(stmt);

    if (!executeSql(db, "COMMIT;"))
    {
        executeSql(db, "ROLLBACK;");
        sqlite3_close(db);
        return false;
    }

    sqlite3_close(db);
    return true;
}

bool saveCourierCompany(const CourierCompany &company)
{
    sqlite3 *db = openDatabase();
    if (db == NULL)
    {
        return false;
    }

    const char *insertSql =
        "INSERT INTO courier_companies(company_name, contact_number, location, packaging_price, discount) "
        "VALUES(?, ?, ?, ?, ?);";
    sqlite3_stmt *stmt = NULL;
    if (sqlite3_prepare_v2(db, insertSql, -1, &stmt, NULL) != SQLITE_OK)
    {
        sqlite3_close(db);
        return false;
    }

    sqlite3_bind_text(stmt, 1, company.companyName.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, company.contactNumber.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, company.location.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_double(stmt, 4, company.packagingPrice);
    sqlite3_bind_double(stmt, 5, company.discount);

    bool ok = sqlite3_step(stmt) == SQLITE_DONE;
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    if (!ok)
    {
        cerr << "Failed to save courier company in SQLite.\n";
    }

    return ok;
}

int getNextOrderId()
{
    sqlite3 *db = openDatabase();
    if (db == NULL)
    {
        return 1;
    }

    const char *query = "SELECT COALESCE(MAX(order_id), 0) + 1 FROM orders;";
    sqlite3_stmt *stmt = NULL;
    int nextOrderId = 1;

    if (sqlite3_prepare_v2(db, query, -1, &stmt, NULL) == SQLITE_OK)
    {
        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            nextOrderId = sqlite3_column_int(stmt, 0);
        }
    }

    if (stmt != NULL)
    {
        sqlite3_finalize(stmt);
    }

    sqlite3_close(db);
    return nextOrderId;
}

void updateOrderId(int orderId)
{
    (void)orderId;
    // Kept for compatibility with current call sites. IDs are derived from SQLite max(order_id).
}

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pauseForUser()
{
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

int readInt(const string &prompt)
{
    int value;
    while (true)
    {
        cout << prompt;
        cin >> value;

        if (!cin.fail())
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number.\n";
    }
}
