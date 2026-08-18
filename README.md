# Delivery Agent System

A C++ console application that simulates a delivery management workflow for three roles:
- **Customer**: place, track, cancel, reschedule, and view past orders
- **Courier Service**: register courier details and update delivery status
- **Admin**: generate delivery reports from stored order records

The project uses a normalized **SQLite-backed** storage layer and a menu-driven terminal interface.

## Resume Highlights

- Designed and implemented a **role-based logistics workflow** (Customer, Courier, Admin) using modular C++ components.
- Built a reusable **order data model** and SQLite persistence utilities for consistent storage, retrieval, and updates.
- Added **input validation and state-aware business rules** (cancel, reschedule, status update) to improve reliability.
- Implemented **admin analytics reporting** with status-wise summaries for operational visibility.
- Improved **cross-platform compatibility** by removing non-portable dependencies and standardizing build steps.

## Project Structure

- `Source/main.cpp` - entry point and role-based menus
- `Source/customer.cpp` - customer workflows
- `Source/courierservice.cpp` - courier service workflows
- `Source/admin.cpp` - admin reporting and status summary
- `Source/common.cpp` - shared order persistence, input handling, and console utilities
- `Makefile` - build instructions

## Features

### Customer
- Book a delivery (name and shipping address)
- View full order details by order ID
- Cancel an order by order ID (status-based cancellation)
- View past records by customer name
- Reschedule an order with updated delivery date

### Courier Service
- Add courier company details and pricing information
- Update order status by order ID

### Admin
- Generate a tabular report of all delivery records
- View aggregate status summary (e.g., Booked, InTransit, Delivered)

## Data Storage

The application creates/updates this database file in the repository root while running:
- `delivery_agent.db` - SQLite database containing:
   - `orders(order_id, customer_name, address, status, scheduled_date, created_at)`
   - `courier_companies(id, company_name, contact_number, location, packaging_price, discount, created_at)`

## Requirements

- C++ compiler with C++11 support (`g++` recommended)
- `make`
- SQLite3 development library (`sqlite3` / `libsqlite3`)

## Build and Run

From the repository root:

```bash
cd /path/to/Delivery-Agent-Sysytem
make
./delivery_agent_system
```

## Usage Flow

1. Start the program.
2. Choose one role:
   - `1` Customer
   - `2` Admin
   - `3` Courier Service
   - `4` Exit
3. Follow the menu options shown for the selected role.
4. Use generated **Order ID** values to track, update, or cancel orders.

## Known Limitations

- No authentication or authorization between roles.
- Single-process local execution only (no API/network layer).

## Clean Build Artifacts

```bash
make clean
```

## Future Improvements

- Add stronger validation and error handling
- Add role authentication
- Add unit/integration tests
- Make the build fully cross-platform
