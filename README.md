# Delivery Agent System

A C++ console application that simulates a basic delivery management workflow for three roles:
- **Customer**: place, track, cancel, reschedule, and view past orders
- **Courier Service**: register courier details and update delivery status
- **Admin**: generate delivery reports from stored order records

The project stores data in simple text files and provides a menu-driven terminal interface.

## Project Structure

- `/home/runner/work/Delivery-Agent-Sysytem/Delivery-Agent-Sysytem/Source/main.cpp` - entry point and role-based menus
- `/home/runner/work/Delivery-Agent-Sysytem/Delivery-Agent-Sysytem/Source/customer.cpp` - customer operations
- `/home/runner/work/Delivery-Agent-Sysytem/Delivery-Agent-Sysytem/Source/courierservice.cpp` - courier service operations
- `/home/runner/work/Delivery-Agent-Sysytem/Delivery-Agent-Sysytem/Source/admin.cpp` - admin reporting
- `/home/runner/work/Delivery-Agent-Sysytem/Delivery-Agent-Sysytem/Makefile` - build instructions

## Features

### Customer
- Book a delivery (name and shipping address)
- View order status by order ID
- Cancel an order by order ID
- View past records by customer name
- Reschedule an order

### Courier Service
- Add courier company details and pricing information
- Update order status by order ID

### Admin
- Generate a tabular report of all delivery records

## Data Files

The application creates/updates these files in the repository root while running:
- `database.txt` - customer order records
- `order_id.txt` - latest generated order ID
- `compdatabase.txt` - courier service/company entries
- `temp.txt` - temporary file used during update/delete operations

## Requirements

- C++ compiler with C++11 support (`g++` recommended)
- `make`
- Console environment that supports `conio.h` (`_getch`) used by this codebase

## Build and Run

From the repository root:

```bash
cd /home/runner/work/Delivery-Agent-Sysytem/Delivery-Agent-Sysytem
make
./devilery_agent_system
```

> Note: The executable name is currently `devilery_agent_system` (matching the existing Makefile target).

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

- Data is stored in plain text files (no database).
- No authentication/authorization between user roles.
- Input validation is minimal.
- The codebase uses platform-specific headers (`conio.h`), which may require a compatible compiler/environment.

## Clean Build Artifacts

```bash
make clean
```

## Future Improvements

- Replace text-file storage with a proper database
- Add stronger validation and error handling
- Add role authentication
- Add unit/integration tests
- Make the build fully cross-platform
