# Event-Ease

A comprehensive event management system written in C that allows users to register, login, view events, book seats, and manage bookings.

## Features

### Landing Page
- **New User Registration**: Register with automatic 4-digit ticket code generation (0000-9999)
- **Existing User Login**: Login with name and ticket code
- **Admin Login**: Special admin access with hardcoded credentials

### User Dashboard
- View available events
- Book seats for events
- Cancel existing bookings
- View all personal bookings
- Logout functionality

### Admin Dashboard
- View all bookings across the system
- Add new events
- View and manage all events (edit/delete)
- View all registered users
- Logout functionality

## Getting Started

### Prerequisites
- GCC compiler (for Windows, Linux, or Mac)
- Windows environment (uses Windows-specific console functions)

### Compilation
```bash
gcc -o Event_Ease.exe Event_Ease.c
```

### Running the Application
```bash
./Event_Ease.exe
```

## User Authentication

### New User Registration
1. Select "New User Registration" from the landing page
2. Enter your name (cannot be empty)
3. System generates a unique 4-digit ticket code
4. Save your ticket code for future logins

### User Login
1. Select "Existing User Login" from the landing page
2. Enter your registered name
3. Enter your 4-digit ticket code
4. Access granted upon successful validation

### Admin Login
- **Username**: admin
- **Password**: password

## File Structure

### Data Files
- `user_info.txt`: Stores user registration data (format: `ticket,name`)
- `events.txt`: Stores event information (format: `name|venue|date|time|capacity`)
- `bookings.txt`: Stores booking data (format: `eventID name`)

### Important Notes
- The application automatically removes `bookings.txt` on startup to prevent conflicts
- Ticket codes are unique and range from 0000-9999
- All user inputs are validated for security
- The system provides clear success/failure messages

## Code Features

### Input Validation
- Names cannot be empty or contain only spaces
- Ticket codes must be 4-digit numbers (0000-9999)
- All menu selections are validated

### Security Features
- Unique ticket code generation with duplicate checking
- Input sanitization and validation
- Clear error messages for invalid inputs

### User Experience
- Centered console output for better presentation
- Clear menu navigation
- Confirmation messages for all actions
- Option to logout and return to landing page

## Technical Details

### Functions Overview
- **Landing Page**: `landingPage()` - Main entry point
- **Registration**: `newUserRegistration()` - Handle new user signup
- **Login**: `existingUserLogin()`, `adminLogin()` - Authentication
- **Dashboards**: `userDashboard()`, `adminDashboard()` - Main menus
- **Utilities**: `generateUniqueTicketCode()`, `validateUserLogin()` - Helper functions

### Compilation Requirements
- Standard C libraries: `stdio.h`, `stdlib.h`, `string.h`, `time.h`
- Windows-specific: `windows.h`, `conio.h`

## Contributing
Feel free to fork this project and submit pull requests for improvements.

## License
This project is open source and available under the MIT License.

EventEase is a C-based console application designed to simplify event management for both users and administrators. The project aims to provide a lightweight, easy-to-use system for booking seats, managing events, and handling event data securely.

## Goals

- **User-Friendly Booking:** Allow users to view available events and book seats with minimal effort.
- **Event Management:** Enable administrators to add, edit, and delete events, as well as view all bookings and event details.
- **Data Persistence:** Store event and booking information in text files for easy access and modification.
- **Security:** Provide basic login authentication for users and admins to protect sensitive operations.
- **Console-Based UI:** Deliver a visually appealing and interactive experience using console graphics and color.

## Features

- User login and booking system
- Admin dashboard for event and booking management
- Add, edit, and delete events
- View all events and bookings
- Data stored in `events.txt` and `bookings.txt`

## Getting Started

1. Clone the repository.
2. Compile the code using GCC (MinGW recommended for Windows).
3. Run the executable and follow the on-screen instructions.

## Usage

- Users can log in, view events, and book seats.
- Admins can log in to manage events and view all bookings.

## Future Improvements

- Add support for multiple users and roles
- Enhance data validation and error handling
- Implement seat availability tracking
- Add export/import features for event data

---

Feel free to contribute or suggest improvements!
