# Event-Ease User Manual 📚

Welcome to the complete user guide for Event-Ease! This manual will walk you through every feature and function of the application.

## Table of Contents
1. [Getting Started](#getting-started)
2. [First Time Setup](#first-time-setup)
3. [User Guide](#user-guide)
4. [Admin Guide](#admin-guide)
5. [Troubleshooting](#troubleshooting)
6. [Advanced Features](#advanced-features)
7. [Tips & Best Practices](#tips--best-practices)

---

## Getting Started

### System Requirements
- **Operating System**: Windows (7, 8, 10, 11)
- **Compiler**: GCC (MinGW recommended)
- **Memory**: 50 MB free space
- **Display**: Console/Terminal access

### Installation Process

#### Step 1: Download or Clone
```bash
# Option A: Clone from GitHub
git clone https://github.com/fahimshahriar24/Event-Ease.git

# Option B: Download ZIP and extract
```

#### Step 2: Compile the Application
```bash
# Navigate to the project folder
cd Event-Ease

# Compile with GCC
gcc Event_Ease.c -o Event_Ease.exe

# For enhanced error checking (optional)
gcc -Wall -Wextra Event_Ease.c -o Event_Ease.exe
```

#### Step 3: First Run
```bash
# Run the application
./Event_Ease.exe
```

---

## First Time Setup

### Initial Welcome Screen
When you first run Event-Ease, you'll see:
- 🎨 **Animated Logo**: Beautiful ASCII art welcome screen
- 🎯 **Main Menu**: Three primary options
- 🎨 **Professional Layout**: Centered, aligned interface

### Main Menu Options
```
Welcome to Event-Ease!
=====================

1. New User Registration
2. Existing User Login  
3. Admin Login
0. Exit
```

---

## User Guide

### 🆕 New User Registration

#### Step-by-Step Registration
1. **Select Option 1** from the main menu
2. **Enter Your Name**:
   - Cannot be empty
   - No spaces-only names
   - Names must be unique (case-insensitive)
   - Examples: "John Doe", "Alice Smith", "Bob_123"

3. **Receive Your Ticket Code**:
   - System generates a unique 4-digit code (0000-9999)
   - **IMPORTANT**: Write down your ticket code!
   - Example: `Your ticket code is: 1564`

4. **Automatic Login**: You're immediately logged in after registration

#### Registration Example
```
=== New User Registration ===

Enter your name: John Doe

Registration Successful!
========================

Your ticket code is: 1564
Please remember your ticket code for future logins.

Press any key to continue to your dashboard...
```

### 🔑 Existing User Login

#### Login Process
1. **Select Option 2** from the main menu
2. **Enter Your Name**: Exactly as registered
3. **Enter Ticket Code**: Your 4-digit code
4. **Access Granted**: Proceed to user dashboard

#### Login Example
```
=== User Login ===

Enter your name: John Doe
Enter your 4-digit ticket code: 1564

Login successful!
Welcome back!
Press any key to continue to your dashboard...
```

#### Login Troubleshooting
- ❌ **"Invalid credentials"**: Check name spelling and ticket code
- ❌ **"Invalid ticket code format"**: Must be numbers only (0000-9999)
- ❌ **Name not found**: Register as a new user first

### 🎭 User Dashboard

Once logged in, you'll see the main user menu:

```
DASHBOARD (Beautiful ASCII Art)

1. View Event Details
2. Book Seat
3. Cancel Booking  
4. View All Bookings
5. Logout
0. Exit
```

#### 📅 View Event Details

**Purpose**: Browse available events with full information

**How to Use**:
1. Select option 1
2. Choose an event from the list
3. View complete details:
   - Event name
   - Venue location
   - Date (DD-MM-YYYY format)
   - Time (HH:MM format)
   - Seat capacity

**Example Output**:
```
-- Available Events --

1. Faija's Wedding
2. Shunno Concert
3. Return to main menu

Enter event ID to view details: 1

--- Event Details ---

Name: Faija's Wedding
Venue: Chandpur
Date (DD-MM-YYYY): 17-08-2025
Time: 12:12
Seat Capacity: 500

[B] Book this event
[R] Return to list
[M] Main menu

Choose an option (B/R/M): B
```

#### 🎫 Book Seat

**Purpose**: Reserve your seat for an event

**Improved Process** (No name re-entry!):
1. Select option 2 from dashboard
2. Choose event from the list
3. **Automatic booking** using your logged-in name
4. Receive confirmation

**Example**:
```
-- Book a Seat --

-- Available Events --

1. Faija's Wedding
2. Shunno Concert
3. Return to main menu

Enter event ID to book: 1

--- Booking Confirmation ---

Seat booked successfully for John Doe
Event ID: 1
Event: Faija's Wedding

Press Enter to continue...
```

#### 🎫 Direct Booking from Event Details
You can also book directly when viewing event details:
1. View event details (option 1)
2. Press 'B' to book
3. Automatic booking with logged-in user

#### ❌ Cancel Booking

**Purpose**: Remove your existing reservations

**How to Use**:
1. Select option 3 from dashboard
2. System shows your logged-in name
3. Enter the Event ID to cancel
4. Confirmation of cancellation

**Example**:
```
-- Cancel Booking --

Canceling booking for: John Doe

Enter Event ID to cancel: 1

Booking successfully canceled.

Press Enter to continue...
```

#### 📋 View All Bookings

**Purpose**: See all your current reservations with event names (not IDs!)

**Enhanced Display**:
```
--- All Bookings ---

Event Name      | User Name
---------------------------
Faija's Wedding | John Doe
Shunno Concert  | John Doe
---------------------------
```

**Benefits**:
- ✅ See actual event names instead of confusing numbers
- ✅ Easy to understand your bookings
- ✅ Professional table format

#### 🚪 Logout

**Purpose**: Return to main menu and clear your session

**Process**:
1. Select option 5
2. Your login session is cleared
3. Return to main welcome screen
4. Must login again to access features

---

## Admin Guide

### 🔐 Admin Login

#### Access Credentials
- **Username**: `admin`
- **Password**: `password`

#### Login Process
1. Select option 3 from main menu
2. Enter admin credentials
3. Access admin control panel

### 🛠️ Admin Dashboard

```
DASHBOARD (Beautiful ASCII Art)

1. View all bookings
2. Add Event
3. View All Events  
4. View All Users
5. Logout
0. Exit
```

#### 📊 View All Bookings

**Purpose**: Monitor all bookings across the entire system

**Enhanced Features**:
- Shows event names instead of IDs
- Lists all users and their bookings
- Professional table format

**Example Output**:
```
--- All Bookings ---

Event Name      | User Name
---------------------------
Faija's Wedding | John Doe
Faija's Wedding | Alice Smith
Shunno Concert  | Bob Wilson
Shunno Concert  | John Doe
---------------------------
```

#### ➕ Add Event

**Purpose**: Create new events for users to book

**Step-by-Step Process**:
1. Select option 2
2. Fill in all event details:

```
-- Add New Event --

Event Name: Summer Music Festival
Venue: Central Park
Date (DD-MM-YYYY): 25-08-2025
Time (HH:MM): 19:00
Seat Capacity: 1000

Event added successfully!
```

**Input Guidelines**:
- **Event Name**: Descriptive, unique name
- **Venue**: Location where event takes place
- **Date**: DD-MM-YYYY format (e.g., 25-08-2025)
- **Time**: HH:MM format (e.g., 19:00)
- **Capacity**: Number of available seats

#### 🎭 View All Events

**Purpose**: Manage existing events (view, edit, delete)

**Features**:
1. **View Events List**:
```
-- All Events --

1. Faija's Wedding
2. Shunno Concert
3. Summer Music Festival
4. Return to admin menu
```

2. **Select Event** for detailed management
3. **Event Details Display**:
```
--- Event Details ---

Name: Faija's Wedding
Venue: Chandpur
Date (DD-MM-YYYY): 17-08-2025
Time: 12:12
Seat Capacity: 500

1. Edit Event
2. Delete Event
3. Return
```

#### ✏️ Edit Event

**Process**:
1. Select event to edit
2. Choose "Edit Event"
3. Update any field (or press Enter to keep current value):

```
Enter new event name (or press Enter to keep 'Faija's Wedding'): [Enter]
Enter new venue (or press Enter to keep 'Chandpur'): New Venue
Enter new date (or press Enter to keep '17-08-2025'): [Enter]
Enter new time (or press Enter to keep '12:12'): 14:00
Enter new seat capacity (or 0 to keep 500): 600

Event updated successfully!
```

#### ❌ Delete Event

**Process**:
1. Select event to delete
2. Choose "Delete Event"
3. Event is permanently removed
4. **Warning**: All bookings for this event are also lost

#### 👥 View All Users

**Purpose**: Monitor registered users and their information

**Display Format**:
```
--- All Registered Users ---

Ticket Code | Name
---------------------------
    1564    | John Doe
    2873    | Alice Smith
    9876    | Bob Wilson
    0123    | Sarah Johnson
---------------------------

Total registered users: 4
```

**Information Shown**:
- Complete list of all registered users
- Their unique ticket codes
- Total user count for analytics

---

## Troubleshooting

### Common Issues & Solutions

#### 🚫 Application Won't Start
**Problem**: Double-clicking doesn't work
**Solution**: 
```bash
# Run from command prompt/PowerShell
cd path\to\Event-Ease
Event_Ease.exe
```

#### 🚫 "GCC not found" Error
**Problem**: Compiler not installed
**Solution**:
1. Install MinGW-w64
2. Add to PATH environment variable
3. Restart terminal

#### 🚫 "File not found" Errors
**Problem**: Data files missing
**Solution**: 
- Files are created automatically on first use
- Ensure write permissions in directory

#### 🚫 Login Issues
**Problem**: Can't login with correct credentials
**Solutions**:
- Check for extra spaces in name
- Ensure ticket code is exactly 4 digits
- Verify case-sensitive name matching

#### 🚫 Booking Disappeared
**Problem**: Bookings not showing after restart
**Solution**: 
- This was fixed in recent updates
- Bookings now persist between sessions
- If issue persists, check `bookings.txt` file permissions

#### 🚫 Events Not Displaying
**Problem**: Event list appears empty
**Solutions**:
- Check if `events.txt` exists and has content
- Admin should add events first
- Verify file format: `name|venue|date|time|capacity`

#### 🚫 Alignment Issues
**Problem**: Text appears misaligned
**Solutions**:
- Use standard Windows console
- Avoid third-party terminals initially
- Check console width (recommended: 80+ characters)

### Data File Issues

#### File Formats
If you need to manually edit data files:

**user_info.txt**:
```
1564,John Doe
2873,Alice Smith
```

**events.txt**:
```
Faija's Wedding|Chandpur|17-08-2025|12:12|500
Shunno Concert|DIU Campus|18-05-2025|18:45|1000
```

**bookings.txt**:
```
1 John Doe
2 Alice Smith
1 Bob Wilson
```

#### Backup & Recovery
**Recommended Practice**:
1. Regular backup of data files
2. Copy before major changes
3. Keep sample data files for reference

---

## Advanced Features

### 🔧 Smart User Recognition

**Feature**: Once logged in, the system remembers your identity
**Benefits**:
- No need to re-enter name when booking
- Streamlined booking process
- Reduced user errors

### 🎨 Unified UI System

**Feature**: Consistent alignment across all screens
**Benefits**:
- Professional appearance
- Better readability
- Improved user experience

### 📊 Enhanced Data Display

**Feature**: Event names shown instead of IDs
**Benefits**:
- More meaningful information
- Easier to understand bookings
- Professional presentation

### 🔒 Security Features

**Input Validation**:
- Name uniqueness checking
- Ticket code format validation
- Menu option validation
- File access error handling

**Data Integrity**:
- Automatic file creation
- Error recovery mechanisms
- Data persistence guarantees

---

## Tips & Best Practices

### 🎯 For Users

#### Registration Tips
- ✅ **Choose memorable names**: Easier to remember for login
- ✅ **Write down ticket codes**: Store in secure location
- ✅ **Use unique names**: Avoid common names that might conflict

#### Booking Tips
- ✅ **Book early**: Popular events fill up quickly
- ✅ **Double-check details**: Verify event information before booking
- ✅ **Keep track**: Use "View All Bookings" to monitor your reservations

#### Navigation Tips
- ✅ **Use number keys**: Always select options using numbers
- ✅ **Read prompts carefully**: Each screen has specific instructions
- ✅ **Logout properly**: Use logout option instead of closing window

### 🛠️ For Administrators

#### Event Management
- ✅ **Clear event names**: Use descriptive, unique names
- ✅ **Correct date format**: Always use DD-MM-YYYY
- ✅ **Realistic capacity**: Set appropriate seat limits
- ✅ **Regular monitoring**: Check bookings regularly

#### User Management
- ✅ **Monitor registrations**: Keep track of user growth
- ✅ **Check booking patterns**: Identify popular events
- ✅ **Maintain data files**: Regular backups recommended

#### System Maintenance
- ✅ **Regular backups**: Copy data files frequently
- ✅ **Monitor disk space**: Ensure adequate storage
- ✅ **Update event information**: Keep details current

### 💡 Performance Tips

#### Optimal Usage
- ✅ **Close properly**: Always use exit/logout options
- ✅ **Single instance**: Run one copy at a time
- ✅ **Standard console**: Use default Windows command prompt

#### Data Management
- ✅ **File permissions**: Ensure read/write access
- ✅ **Directory structure**: Keep all files in same folder
- ✅ **Regular cleanup**: Remove old/test data periodically

---

## Support & Resources

### 📞 Getting Help

#### Documentation
- **README.md**: Project overview and quick start
- **User Manual**: This comprehensive guide
- **Code Comments**: Inline documentation in source code

#### Community Support
- **GitHub Issues**: Report bugs and request features
- **GitHub Discussions**: Ask questions and share tips
- **Pull Requests**: Contribute improvements

#### Self-Help Resources
- **Error Messages**: Read carefully for specific guidance
- **Troubleshooting Section**: Common issues and solutions
- **Log Files**: Check for error details

### 🚀 Future Updates

#### Planned Features
- Multi-language support
- Enhanced security options
- Database integration options
- Web interface version
- Mobile compatibility

#### How to Update
1. Download latest version
2. Backup current data files
3. Replace executable
4. Test with backup data

---

## Conclusion

Event-Ease is designed to make event management simple and efficient. This manual covers all features and common scenarios. For additional support, please refer to the project repository or contact the development team.

**Happy Event Managing!** 🎉

---

*Last Updated: August 17, 2025*  
*Version: 2.0*  
*Manual Version: 1.0*
