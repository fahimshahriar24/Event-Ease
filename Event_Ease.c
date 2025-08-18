/*
 * Event-Ease: Console-based Event Management System
 * 
 * Features:
 * - User registration and authentication with unique ticket codes
 * - Event viewing and seat booking
 * - Admin panel for event and user management
 * - Persistent data storage in text files
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <time.h>  
#include <ctype.h>


#define BOOKINGS_FILE "bookings.txt"
#define USER_INFO_FILE "user_info.txt"

char loggedInUserName[100] = "";  // Stores currently logged-in user's name

/*
 * ========================= FUNCTION DECLARATIONS =========================
 */

// Core: authentication and user management
void landingPage();
void newUserRegistration();
void existingUserLogin();
void adminLogin();
int generateUniqueTicketCode();
int isTicketCodeExists(int ticketCode);
int isNameExists(const char *name);
int equalsIgnoreCase(const char *a, const char *b);
void saveUserInfo(int ticketCode, const char *name);
int validateUserLogin(const char *name, int ticketCode);

// Core: main navigation dashboards
void userDashboard();
void adminDashboard();

// Core: event management
void addEvent();
void adminViewAllEvents();
void viewAllUsers();
void viewEventDetailsOnly();
char* getEventNameByID(int eventID);

// Core: booking system
void bookSeat();
void cancelBooking();
void saveBooking(int eventID, const char *name);
void removeBooking(int eventID, const char *name);
void viewAllBookings();
void adminViewAllBookings();

// UI & design helpers (kept at bottom of file)
void clear();
void welcomePage();
void dashboardDesign();
void adminDashboardDesign();
void printCentered(const char *str);
int getConsoleWidth();
int calculateCenterPosition(int contentWidth);
void printUnified(const char *str);
void inputUnified(const char *prompt, char *buffer, int size);
void inputUnifiedBlock(const char *prompt, char *buffer, int size);
void printUnifiedBlockLeft(const char *str);
void resetUnifiedBlock();
void boxBordered(const char *text, int innerWidth);
void printMenuItemsWithBoxes(const char *title, const char **items, int count);
int visualLen(const char *s);
void printNotice(const char *msg, char type);
void inputPasswordUnified(char *buffer, int size);

/*
 * ========================= UNIFIED POSITIONING SYSTEM =========================
 * Ensures consistent alignment across all UI elements
 */

static int unified_blockMaxLen = 0;
static int unified_blockStartPos = -1;
static int unified_blockFirstCall = 1;

/*
 * ========================= AUTHENTICATION & LANDING PAGE =========================
 */

// Main entry point showing login, registration, and admin options
void landingPage()
{
    int choice;
    static int splashShown = 0;
    
    while (1)
    {
        clear();
        if (!splashShown)
        {
            welcomePage();
            Sleep(1500);
            clear();
            splashShown = 1;
        }

        // Header and individual boxed options
        const char *menuItems[] = {
            "1. New User Registration",
            "2. Existing User Login",
            "3. Admin Login",
            "0. Exit"
        };
        printMenuItemsWithBoxes("Welcome to Event-Ease!", menuItems, 4);
        
        char buf[16];
        inputUnified("Select an option: ", buf, sizeof(buf));
        if (sscanf(buf, "%d", &choice) != 1)
        {
            printNotice("Invalid input. Please enter a number.", 'W');
            printNotice("Press any key to continue...", 'I');
            getch();
            continue;
        }

        switch (choice)
        {
        case 1:
            clear();
            newUserRegistration();
            break;
        case 2:
            clear();
            existingUserLogin();
            break;
        case 3:
            clear();
            adminLogin();
            break;
        case 0:
            clear();
            printNotice("Thank you for using Event-Ease!", 'I');
            printNotice("Goodbye!", 'I');
            exit(0);
        default:
            printNotice("Invalid choice. Please select again.", 'W');
            printNotice("Press any key to continue...", 'I');
            getch();
        }
    }
}

// Handles new user account creation with unique ticket code generation
void newUserRegistration()
{
    char name[100];
    int ticketCode;
    
    resetUnifiedBlock();
    printUnifiedBlockLeft("=== New User Registration ===");
    printUnifiedBlockLeft("");
    printUnifiedBlockLeft("Enter your name: ");
    
    resetUnifiedBlock();
    unified_blockFirstCall = 0;
    printUnifiedBlockLeft("=== New User Registration ===");
    printUnifiedBlockLeft("");
    
    while (1)
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(hConsole, &csbi);
        
        // Position cursor at the block's starting position
        COORD pos = csbi.dwCursorPosition;
        pos.X = unified_blockStartPos;
        SetConsoleCursorPosition(hConsole, pos);
        
        printf("Enter your name: ");
        fflush(stdout);
        
        // Move cursor right after prompt
        pos.X += strlen("Enter your name: ");
        SetConsoleCursorPosition(hConsole, pos);
        
        fgets(name, sizeof(name), stdin);
        size_t len = strlen(name);
        if (len > 0 && name[len - 1] == '\n')
            name[len - 1] = '\0';
        
        // Validate name (check if not empty and not just spaces)
        int valid = 0;
        for (int i = 0; name[i] != '\0'; i++)
        {
            if (name[i] != ' ' && name[i] != '\t' && name[i] != '\n')
            {
                valid = 1;
                break;
            }
        }
        
        if (!valid || strlen(name) == 0)
        {
            // Use unified block for error messages
            resetUnifiedBlock();
            printUnifiedBlockLeft("Name cannot be empty. Please enter a valid name.");
            
            resetUnifiedBlock();
            unified_blockFirstCall = 0;
            printUnifiedBlockLeft("Name cannot be empty. Please enter a valid name.");
            
            printNotice("Press any key to try again...", 'I');
            getch();
            clear(); // Clear screen before asking for new name
            
            // Redisplay the registration header
            resetUnifiedBlock();
            printUnifiedBlockLeft("=== New User Registration ===");
            printUnifiedBlockLeft("");
            printUnifiedBlockLeft("Enter your name: ");
            
            // Calculate the unified block position first
            resetUnifiedBlock();
            unified_blockFirstCall = 0;
            printUnifiedBlockLeft("=== New User Registration ===");
            printUnifiedBlockLeft("");
            
            continue;
        }
        
        // Check if name already exists
        if (isNameExists(name))
        {
            // Use unified block for error messages
            resetUnifiedBlock();
            printUnifiedBlockLeft("This name is already registered!");
            printUnifiedBlockLeft("Please choose a different name.");
            
            resetUnifiedBlock();
            unified_blockFirstCall = 0;
            printUnifiedBlockLeft("This name is already registered!");
            printUnifiedBlockLeft("Please choose a different name.");
            
            printNotice("Press any key to try again...", 'I');
            getch();
            clear(); // Clear screen before asking for new name
            
            // Redisplay the registration header
            resetUnifiedBlock();
            printUnifiedBlockLeft("=== New User Registration ===");
            printUnifiedBlockLeft("");
            printUnifiedBlockLeft("Enter your name: ");
            
            // Calculate the unified block position first
            resetUnifiedBlock();
            unified_blockFirstCall = 0;
            printUnifiedBlockLeft("=== New User Registration ===");
            printUnifiedBlockLeft("");
            
            continue;
        }
        
        // Name is valid and unique
        break;
    }
    
    // Generate unique ticket code
    ticketCode = generateUniqueTicketCode();
    
    if (ticketCode == -1)
    {
        printNotice("Error: Unable to generate unique ticket code.", 'E');
        printNotice("Please try again later.", 'I');
        printNotice("Press any key to continue...", 'I');
        getch();
        return;
    }
    
    saveUserInfo(ticketCode, name);
    strcpy(loggedInUserName, name);
    
    // Display registration success using unified block system (two-pass for alignment)
    resetUnifiedBlock();
    char ticketMsg[100];
    printUnifiedBlockLeft("========================");
    printUnifiedBlockLeft("");
    snprintf(ticketMsg, sizeof(ticketMsg), "Your ticket code is: %04d", ticketCode);
    printUnifiedBlockLeft(ticketMsg);
    printUnifiedBlockLeft("Please remember your ticket code for future logins.");
    printUnifiedBlockLeft("");
    
    unified_blockFirstCall = 0; // second pass: actually print
    printNotice("Registration Successful!", 'S');
    printUnifiedBlockLeft("========================");
    printUnifiedBlockLeft("");
    printUnifiedBlockLeft(ticketMsg);
    printUnifiedBlockLeft("Please remember your ticket code for future logins.");
    printUnifiedBlockLeft("");
    printNotice("Press any key to continue to your dashboard...", 'I');
    
    getch();
    
    clear();
    userDashboard();
}

// Manages existing user login with name and ticket code validation
void existingUserLogin()
{
    char name[100];
    int ticketCode;
    
    // Use unified block for consistent alignment
    resetUnifiedBlock();
    printUnifiedBlockLeft("=== User Login ===");
    printUnifiedBlockLeft("");
    printUnifiedBlockLeft("Enter your name: ");
    printUnifiedBlockLeft("Enter your 4-digit ticket code: ");
    
    // Calculate the unified block position first
    resetUnifiedBlock();
    unified_blockFirstCall = 0;
    printUnifiedBlockLeft("=== User Login ===");
    printUnifiedBlockLeft("");
    
    // Get user credentials with manual positioning
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    
    // Get name
    COORD pos = csbi.dwCursorPosition;
    pos.X = unified_blockStartPos;
    SetConsoleCursorPosition(hConsole, pos);
    printf("Enter your name: ");
    fflush(stdout);
    pos.X += strlen("Enter your name: ");
    SetConsoleCursorPosition(hConsole, pos);
    fgets(name, sizeof(name), stdin);
    size_t len = strlen(name);
    if (len > 0 && name[len - 1] == '\n')
        name[len - 1] = '\0';
    
    // Get ticket code
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    pos = csbi.dwCursorPosition;
    pos.X = unified_blockStartPos;
    SetConsoleCursorPosition(hConsole, pos);
    printf("Enter your 4-digit ticket code: ");
    fflush(stdout);
    pos.X += strlen("Enter your 4-digit ticket code: ");
    SetConsoleCursorPosition(hConsole, pos);
    char ticketBuf[16];
    fgets(ticketBuf, sizeof(ticketBuf), stdin);
    len = strlen(ticketBuf);
    if (len > 0 && ticketBuf[len - 1] == '\n')
        ticketBuf[len - 1] = '\0';
    
    if (sscanf(ticketBuf, "%d", &ticketCode) != 1)
    {
        printNotice("Invalid ticket code format. Please enter a 4-digit number.", 'W');
        printNotice("Press any key to continue...", 'I');
        getch();
        return;
    }
    
    // Validate ticket code range
    if (ticketCode < 0 || ticketCode > 9999)
    {
        printNotice("Invalid ticket code. Must be between 0000-9999.", 'W');
        printNotice("Press any key to continue...", 'I');
        getch();
        return;
    }
    
    if (validateUserLogin(name, ticketCode))
    {
        strcpy(loggedInUserName, name);
        printNotice("Login successful!", 'S');
        printNotice("Welcome back!", 'I');
        printNotice("Press any key to continue to your dashboard...", 'I');
        getch();
        clear();
        userDashboard();
    }
    else
    {
        printNotice("Invalid credentials. Name or ticket code does not match.", 'E');
        printNotice("Please check your information and try again.", 'I');
        printNotice("Press any key to continue...", 'I');
        getch();
    }
}

// Handles admin authentication with secure credentials
void adminLogin()
{
    char username[50], password[50];
    
    // Use unified block for consistent alignment
    resetUnifiedBlock();
    printUnifiedBlockLeft("=== Admin Login ===");
    printUnifiedBlockLeft("");
    printUnifiedBlockLeft("Username: ");
    printUnifiedBlockLeft("Password: ");
    
    // Calculate the unified block position first
    resetUnifiedBlock();
    unified_blockFirstCall = 0;
    printUnifiedBlockLeft("=== Admin Login ===");
    printUnifiedBlockLeft("");
    
    // Get admin credentials with manual positioning
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    
    // Get username
    COORD pos = csbi.dwCursorPosition;
    pos.X = unified_blockStartPos;
    SetConsoleCursorPosition(hConsole, pos);
    printf("Username: ");
    fflush(stdout);
    pos.X += strlen("Username: ");
    SetConsoleCursorPosition(hConsole, pos);
    fgets(username, sizeof(username), stdin);
    size_t len = strlen(username);
    if (len > 0 && username[len - 1] == '\n')
        username[len - 1] = '\0';
    
    // Get password (hidden input)
    inputPasswordUnified(password, sizeof(password));
    
    if (strcmp(username, "admin") == 0 && strcmp(password, "fahim1234") == 0)
    {
        printf("\n");
        printNotice("Admin login successful!", 'S');
        printNotice("Access granted to admin panel.", 'I');
        printNotice("Press any key to continue...", 'I');
        getch();
        clear();
        adminDashboard();
    }
    else
    {
        printf("\n");
        printNotice("Invalid admin credentials.", 'E');
        printNotice("Access denied.", 'E');
        printNotice("Press any key to continue...", 'I');
        getch();
    }
}

// Generates a unique 4-digit ticket code for new users
int generateUniqueTicketCode()
{
    int maxAttempts = 1000;
    int attempts = 0;
    
    while (attempts < maxAttempts)
    {
        int ticketCode = rand() % 10000; // Generate 0-9999
        
        if (!isTicketCodeExists(ticketCode))
        {
            return ticketCode;
        }
        
        attempts++;
    }
    
    return -1; // Failed to generate unique code
}

// Checks if a ticket code already exists in the system
int isTicketCodeExists(int ticketCode)
{
    FILE *file = fopen(USER_INFO_FILE, "r");
    if (file == NULL)
    {
        return 0; // File doesn't exist, so code doesn't exist
    }
    
    char line[200];
    int existingTicket;
    char existingName[100];
    
    while (fgets(line, sizeof(line), file))
    {
        if (sscanf(line, "%d,%99[^\n]", &existingTicket, existingName) == 2)
        {
            if (existingTicket == ticketCode)
            {
                fclose(file);
                return 1; // Code exists
            }
        }
    }
    
    fclose(file);
    return 0; // Code doesn't exist
}

// Checks if a username already exists in the system
int isNameExists(const char *name)
{
    FILE *file = fopen(USER_INFO_FILE, "r");
    if (file == NULL)
    {
        return 0; // File doesn't exist, so name doesn't exist
    }
    
    char line[200];
    int existingTicket;
    char existingName[100];
    
    while (fgets(line, sizeof(line), file))
    {
        if (sscanf(line, "%d,%99[^\n]", &existingTicket, existingName) == 2)
        {
            if (equalsIgnoreCase(existingName, name))
            {
                fclose(file);
                return 1; // Name exists
            }
        }
    }
    
    fclose(file);
    return 0; // Name doesn't exist
}

// Case-insensitive string equality without platform-specific functions
int equalsIgnoreCase(const char *a, const char *b)
{
    unsigned char ca, cb;
    while (*a && *b)
    {
        ca = (unsigned char)*a;
        cb = (unsigned char)*b;
        if (tolower(ca) != tolower(cb)) return 0;
        a++; b++;
    }
    return *a == '\0' && *b == '\0';
}

/**
 * Save user information (ticket code and name) to user_info.txt
 * Format: ticket,name
 */
void saveUserInfo(int ticketCode, const char *name)
{
    FILE *file = fopen(USER_INFO_FILE, "a");
    if (file == NULL)
    {
        resetUnifiedBlock();
    printNotice("Error: Unable to save user information.", 'E');
        return;
    }
    
    fprintf(file, "%04d,%s\n", ticketCode, name);
    fclose(file);
}

/**
 * Validate user login credentials against stored data
 * Returns 1 if valid, 0 if invalid
 */
int validateUserLogin(const char *name, int ticketCode)
{
    FILE *file = fopen(USER_INFO_FILE, "r");
    if (file == NULL)
    {
        return 0; // No user file exists
    }
    
    char line[200];
    int storedTicket;
    char storedName[100];
    
    while (fgets(line, sizeof(line), file))
    {
        if (sscanf(line, "%d,%99[^\n]", &storedTicket, storedName) == 2)
        {
            if (storedTicket == ticketCode && strcmp(storedName, name) == 0)
            {
                fclose(file);
                return 1; // Match found
            }
        }
    }
    
    fclose(file);
    return 0; // No match found
}

/*
 * ========================= NAVIGATION DASHBOARDS =========================
 */

void userDashboard()
{
    int choice;

    while (1)
    {
        dashboardDesign();
        const char *userMenu[] = {
            "1. View Event Details",
            "2. Book Seat",
            "3. Cancel Booking",
            "4. View All Bookings",
            "5. Logout",
            "0. Exit"
        };
        printMenuItemsWithBoxes("User Dashboard", userMenu, 6);
        
        // Get input using unified block positioning
    char buf[16];
    inputUnified("Select an option: ", buf, sizeof(buf));
            
        if (sscanf(buf, "%d", &choice) != 1)
        {
            resetUnifiedBlock();
            printUnifiedBlockLeft("Invalid input. Please enter a number.");
            printUnifiedBlockLeft("Press any key to continue...");
            getch();
            continue;
        }

        switch (choice)
        {
        case 1:
            clear();
            viewEventDetailsOnly();
            break;
        case 2:
            clear();
            bookSeat();
            break;
        case 3:
            clear();
            cancelBooking();
            break;
        case 4:
            clear();
            viewAllBookings();
            break;
        case 5:
            clear();
            strcpy(loggedInUserName, "");
            printNotice("Successfully logged out!", 'S');
            printNotice("Returning to main menu...", 'I');
            Sleep(1500);
            clear(); // Clear screen before returning to main menu
            return;
        case 0:
            clear();
            resetUnifiedBlock();
            printNotice("Thank you for using Event-Ease!", 'I');
            printNotice("Press any key to exit...", 'I');
            getch();
            exit(0);
        default:
            clear();
            resetUnifiedBlock();
            printNotice("Invalid choice. Please select again.", 'W');
            printNotice("Press any key to continue...", 'I');
            getch();
        }
    }
}

// Admin control panel with enhanced red ASCII art display
void adminDashboard()
{
    int choice;
    while (1)
    {
        adminDashboardDesign();
        const char *adminMenu[] = {
            "1. View all bookings",
            "2. Add Event",
            "3. View All Events",
            "4. View All Users",
            "5. Logout",
            "0. Exit"
        };
        printMenuItemsWithBoxes("Admin Panel", adminMenu, 6);
        
        // Get input using unified block positioning
    char buf[16];
    inputUnified("Select an option: ", buf, sizeof(buf));
            
        if (sscanf(buf, "%d", &choice) != 1)
        {
            resetUnifiedBlock();
            printNotice("Invalid input. Please enter a number.", 'W');
            printNotice("Press any key to continue...", 'I');
            getch();
            continue;
        }

        switch (choice)
        {
        case 1:
            clear();
            adminViewAllBookings();
            break;
        case 2:
            clear();
            addEvent();
            break;
        case 3:
            clear();
            adminViewAllEvents();
            break;
        case 4:
            clear();
            viewAllUsers();
            break;
        case 5:
            clear();
            printNotice("Logging out of admin panel", 'I');
            Sleep(1500);
            return; // Return to landing page
        case 0:
            clear();
            resetUnifiedBlock();
            printNotice("Thank you for using Event-Ease!", 'I');
            printNotice("Press any key to exit...", 'I');
            getch();
            exit(0);
        default:
            clear();
            resetUnifiedBlock();
            printNotice("Invalid choice. Please select again.", 'W');
            printNotice("Press any key to continue...", 'I');
            getch();
        }
    }
}
/*
 * ========================= EVENT MANAGEMENT =========================
 */

void viewEventDetailsOnly()
{
    FILE *file = fopen("events.txt", "r");
    if (file == NULL)
    {
    printNotice("No events found.", 'I');
    printNotice("Press any key to continue...", 'I');
    getch();
        return;
    }

    char line[300], name[100], venue[100], date[20], time[20];
    int seatCapacity;
    int eventCount = 0;
    char events[50][300]; // Store up to 50 events

    // First pass - collect all events
    while (fgets(line, sizeof(line), file))
    {
        if (sscanf(line, "%99[^|]|%99[^|]|%19[^|]|%19[^|]|%d", name, venue, date, time, &seatCapacity) == 5)
        {
            eventCount++;
            snprintf(events[eventCount - 1], sizeof(events[eventCount - 1]), "%s|%s|%s|%s|%d", name, venue, date, time, seatCapacity);
        }
    }
    fclose(file);
    
    if (eventCount == 0)
    {
    printNotice("No events available.", 'I');
    printNotice("Press any key to continue...", 'I');
        getch();
        return;
    }

    // Build boxed list
    char items[60][200];
    int itemsCount = 0;
    for (int i = 0; i < eventCount && itemsCount < 59; i++) {
        char name[100], venue[100], date[20], time[20];
        int seatCapacity;
        if (sscanf(events[i], "%99[^|]|%99[^|]|%19[^|]|%19[^|]|%d", name, venue, date, time, &seatCapacity) == 5) {
            snprintf(items[itemsCount++], sizeof(items[0]), "%d. %s", i + 1, name);
        }
    }
    snprintf(items[itemsCount++], sizeof(items[0]), "%d. Return to dashboard", eventCount + 1);
    const char *ptrs[60];
    for (int i = 0; i < itemsCount; i++) ptrs[i] = items[i];
    printMenuItemsWithBoxes("Available Events", ptrs, itemsCount);

    // Get user's event selection
    int choice;
    char selectPrompt[100];
    snprintf(selectPrompt, sizeof(selectPrompt), "Enter event ID to view details: ");
    char buf_input[16];
    inputUnified(selectPrompt, buf_input, sizeof(buf_input));
    if (sscanf(buf_input, "%d", &choice) != 1)
    {
        printNotice("Invalid input.", 'W');
        printNotice("Press any key to continue...", 'I');
        getch();
        return;
    }
    if (choice < 1 || choice > eventCount + 1)
    {
        printNotice("Invalid choice.", 'W');
        printNotice("Press any key to continue...", 'I');
        getch();
        return;
    }
    if (choice == eventCount + 1)
    {
        clear(); // Clear screen before returning to dashboard
        return;
    }

    // Show details for selected event (VIEW ONLY)
    clear();
    char eventName[100], eventVenue[100], eventDate[20], eventTime[20];
    int eventCapacity;
    sscanf(events[choice - 1], "%99[^|]|%99[^|]|%19[^|]|%19[^|]|%d", eventName, eventVenue, eventDate, eventTime, &eventCapacity);
    
    // First pass: Calculate alignment
    resetUnifiedBlock();
    printUnifiedBlockLeft("=== Event Details ===");
    printUnifiedBlockLeft("");
    
    char detail_buf[200];
    snprintf(detail_buf, sizeof(detail_buf), "Name: %s", eventName);
    printUnifiedBlockLeft(detail_buf);
    snprintf(detail_buf, sizeof(detail_buf), "Venue: %s", eventVenue);
    printUnifiedBlockLeft(detail_buf);
    snprintf(detail_buf, sizeof(detail_buf), "Date (DD-MM-YYYY): %s", eventDate);
    printUnifiedBlockLeft(detail_buf);
    snprintf(detail_buf, sizeof(detail_buf), "Time: %s", eventTime);
    printUnifiedBlockLeft(detail_buf);
    snprintf(detail_buf, sizeof(detail_buf), "Seat Capacity: %d", eventCapacity);
    printUnifiedBlockLeft(detail_buf);
    printUnifiedBlockLeft("");
    printUnifiedBlockLeft("Press Enter to return to event list...");
    
    // Second pass: Actually display
    unified_blockFirstCall = 0;
    printUnifiedBlockLeft("=== Event Details ===");
    printUnifiedBlockLeft("");
    
    snprintf(detail_buf, sizeof(detail_buf), "Name: %s", eventName);
    printUnifiedBlockLeft(detail_buf);
    snprintf(detail_buf, sizeof(detail_buf), "Venue: %s", eventVenue);
    printUnifiedBlockLeft(detail_buf);
    snprintf(detail_buf, sizeof(detail_buf), "Date (DD-MM-YYYY): %s", eventDate);
    printUnifiedBlockLeft(detail_buf);
    snprintf(detail_buf, sizeof(detail_buf), "Time: %s", eventTime);
    printUnifiedBlockLeft(detail_buf);
    snprintf(detail_buf, sizeof(detail_buf), "Seat Capacity: %d", eventCapacity);
    printUnifiedBlockLeft(detail_buf);
    printUnifiedBlockLeft("");
    
    // Simple return prompt (NO BOOKING OPTIONS)
    char continueBuf[10];
    inputUnifiedBlock("Press Enter to return to event list...", continueBuf, sizeof(continueBuf));
    
    // Return to event list to view more events
    clear();
    viewEventDetailsOnly(); // Recursive call to show list again
}

void addEvent()
{
    char name[100], venue[100], date[20], time[20];
    int seatCapacity;

    // Use unified block system for consistency
    resetUnifiedBlock();
    printUnifiedBlockLeft("=== Add New Event ===");
    printUnifiedBlockLeft("");
    printUnifiedBlockLeft("Event Name: ");
    printUnifiedBlockLeft("Venue: ");
    printUnifiedBlockLeft("Date (DD-MM-YYYY): ");
    printUnifiedBlockLeft("Time (HH:MM): ");
    printUnifiedBlockLeft("Seat Capacity: ");
    
    // Now get the actual input using unified positioning
    resetUnifiedBlock();
    unified_blockFirstCall = 0;
    printUnifiedBlockLeft("=== Add New Event ===");
    printUnifiedBlockLeft("");
    
    // Get event details with unified block positioning
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    
    // Get event name
    COORD pos = csbi.dwCursorPosition;
    pos.X = unified_blockStartPos;
    SetConsoleCursorPosition(hConsole, pos);
    printf("Event Name: ");
    fflush(stdout);
    pos.X += strlen("Event Name: ");
    SetConsoleCursorPosition(hConsole, pos);
    fgets(name, sizeof(name), stdin);
    size_t len = strlen(name);
    if (len > 0 && name[len - 1] == '\n')
        name[len - 1] = '\0';
    
    // Get venue
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    pos = csbi.dwCursorPosition;
    pos.X = unified_blockStartPos;
    SetConsoleCursorPosition(hConsole, pos);
    printf("Venue: ");
    fflush(stdout);
    pos.X += strlen("Venue: ");
    SetConsoleCursorPosition(hConsole, pos);
    fgets(venue, sizeof(venue), stdin);
    len = strlen(venue);
    if (len > 0 && venue[len - 1] == '\n')
        venue[len - 1] = '\0';
    
    // Get date
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    pos = csbi.dwCursorPosition;
    pos.X = unified_blockStartPos;
    SetConsoleCursorPosition(hConsole, pos);
    printf("Date (DD-MM-YYYY): ");
    fflush(stdout);
    pos.X += strlen("Date (DD-MM-YYYY): ");
    SetConsoleCursorPosition(hConsole, pos);
    fgets(date, sizeof(date), stdin);
    len = strlen(date);
    if (len > 0 && date[len - 1] == '\n')
        date[len - 1] = '\0';
    
    // Get time
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    pos = csbi.dwCursorPosition;
    pos.X = unified_blockStartPos;
    SetConsoleCursorPosition(hConsole, pos);
    printf("Time (HH:MM): ");
    fflush(stdout);
    pos.X += strlen("Time (HH:MM): ");
    SetConsoleCursorPosition(hConsole, pos);
    fgets(time, sizeof(time), stdin);
    len = strlen(time);
    if (len > 0 && time[len - 1] == '\n')
        time[len - 1] = '\0';
    
    // Get seat capacity
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    pos = csbi.dwCursorPosition;
    pos.X = unified_blockStartPos;
    SetConsoleCursorPosition(hConsole, pos);
    printf("Seat Capacity: ");
    fflush(stdout);
    pos.X += strlen("Seat Capacity: ");
    SetConsoleCursorPosition(hConsole, pos);
    char buf[16];
    fgets(buf, sizeof(buf), stdin);
    len = strlen(buf);
    if (len > 0 && buf[len - 1] == '\n')
        buf[len - 1] = '\0';
    
    if (sscanf(buf, "%d", &seatCapacity) != 1)
    {
        resetUnifiedBlock();
    printNotice("Invalid input for seat capacity.", 'W');
    printNotice("Press any key to continue...", 'I');
        getch();
        return;
    }

    FILE *file = fopen("events.txt", "a");
    if (file == NULL)
    {
        resetUnifiedBlock();
        printNotice("Error opening events file!", 'E');
        printNotice("Press any key to continue...", 'I');
        getch();
        return;
    }
    fprintf(file, "%s|%s|%s|%s|%d\n", name, venue, date, time, seatCapacity);
    fclose(file);
    
    resetUnifiedBlock();
    printNotice("Event added successfully!", 'S');
    printNotice("Press any key to continue...", 'I');
    getch();
    clear(); // Clear screen after adding event
}

void adminViewAllEvents()
{
    FILE *file = fopen("events.txt", "r");
    if (file == NULL)
    {
        resetUnifiedBlock();
    printNotice("No events found.", 'I');
        return;
    }

    char line[300], name[100], venue[100], date[20], time[20];
    int seatCapacity, newSeatCapacity;
    int eventCount = 0;
    char events[50][300]; // Store up to 50 events

    // Build event list
    while (fgets(line, sizeof(line), file))
    {
        if (sscanf(line, "%99[^|]|%99[^|]|%19[^|]|%19[^|]|%d", name, venue, date, time, &seatCapacity) == 5)
        {
            eventCount++;
            snprintf(events[eventCount - 1], sizeof(events[eventCount - 1]), "%s|%s|%s|%s|%d", name, venue, date, time, seatCapacity);
        }
    }
    fclose(file);
    if (eventCount == 0)
    {
    printNotice("No events found.", 'I');
    printNotice("Press any key to continue...", 'I');
        getch();
        return;
    }
    // Render boxed list
    const char *ptrs[60];
    char items[60][200];
    for (int i = 0; i < eventCount; i++)
    {
        char nm[100], vn[100], dt[20], tm[20]; int cap;
        sscanf(events[i], "%99[^|]|%99[^|]|%19[^|]|%19[^|]|%d", nm, vn, dt, tm, &cap);
        snprintf(items[i], sizeof(items[0]), "%d. %s", i + 1, nm);
        ptrs[i] = items[i];
    }
    char retLine[64];
    snprintf(retLine, sizeof(retLine), "%d. Return to admin menu", eventCount + 1);
    ptrs[eventCount] = retLine;
    printMenuItemsWithBoxes("All Events", ptrs, eventCount + 1);

    if (eventCount == 0)
        return;

    int choice;
    char selectPrompt[100];
    snprintf(selectPrompt, sizeof(selectPrompt), "Select an event to view/edit/delete or %d to return: ", eventCount + 1);
    char buf[16];
    inputUnified(selectPrompt, buf, sizeof(buf));
    if (sscanf(buf, "%d", &choice) != 1)
    {
        resetUnifiedBlock();
    printNotice("Invalid input.", 'W');
    printNotice("Press any key to continue...", 'I');
        getch();
        return;
    }
    if (choice < 1 || choice > eventCount + 1)
    {
        resetUnifiedBlock();
    printNotice("Invalid choice.", 'W');
    printNotice("Press any key to continue...", 'I');
        getch();
        return;
    }
    if (choice == eventCount + 1)
    {
        clear(); // Clear screen before returning to admin dashboard
        return;
    }

    // Show details for selected event
    clear();
    sscanf(events[choice - 1], "%99[^|]|%99[^|]|%19[^|]|%19[^|]|%d", name, venue, date, time, &seatCapacity);
    
    resetUnifiedBlock();
    printUnifiedBlockLeft("=== Event Details ===");
    printUnifiedBlockLeft("");
    
    char buf_output[200];
    snprintf(buf_output, sizeof(buf_output), "Name: %s", name);
    printUnifiedBlockLeft(buf_output);
    snprintf(buf_output, sizeof(buf_output), "Venue: %s", venue);
    printUnifiedBlockLeft(buf_output);
    snprintf(buf_output, sizeof(buf_output), "Date (DD-MM-YYYY): %s", date);
    printUnifiedBlockLeft(buf_output);
    snprintf(buf_output, sizeof(buf_output), "Time: %s", time);
    printUnifiedBlockLeft(buf_output);
    snprintf(buf_output, sizeof(buf_output), "Seat Capacity: %d", seatCapacity);
    printUnifiedBlockLeft(buf_output);
    printUnifiedBlockLeft("");
    
    // Second pass - actually print
    unified_blockFirstCall = 0;
    printUnifiedBlockLeft("=== Event Details ===");
    printUnifiedBlockLeft("");
    snprintf(buf_output, sizeof(buf_output), "Name: %s", name);
    printUnifiedBlockLeft(buf_output);
    snprintf(buf_output, sizeof(buf_output), "Venue: %s", venue);
    printUnifiedBlockLeft(buf_output);
    snprintf(buf_output, sizeof(buf_output), "Date (DD-MM-YYYY): %s", date);
    printUnifiedBlockLeft(buf_output);
    snprintf(buf_output, sizeof(buf_output), "Time: %s", time);
    printUnifiedBlockLeft(buf_output);
    snprintf(buf_output, sizeof(buf_output), "Seat Capacity: %d", seatCapacity);
    printUnifiedBlockLeft(buf_output);
    printUnifiedBlockLeft("");
    {
        const char *evtMenu2[] = {
            "1. Edit Event",
            "2. Delete Event",
            "3. Return"
        };
        printMenuItemsWithBoxes("Actions", evtMenu2, 3);
    }
    
    int action;
    char buf2[16];
    inputUnified("Select an option: ", buf2, sizeof(buf2));
    if (sscanf(buf2, "%d", &action) != 1)
    {
        resetUnifiedBlock();
    printNotice("Invalid input.", 'W');
        return;
    }

    if (action == 1)
    {
        // Edit event
        clear();
        char newName[100], newVenue[100], newDate[20], newTime[20];
        char promptName[150];
        snprintf(promptName, sizeof(promptName), "Enter new event name (or press Enter to keep '%s'): ", name);
        inputUnifiedBlock(promptName, newName, sizeof(newName));
        if (strlen(newName) == 0)
            strcpy(newName, name);

        char promptVenue[150];
        snprintf(promptVenue, sizeof(promptVenue), "Enter new venue (or press Enter to keep '%s'): ", venue);
        inputUnifiedBlock(promptVenue, newVenue, sizeof(newVenue));
        if (strlen(newVenue) == 0)
            strcpy(newVenue, venue);

        char promptDate[150];
        snprintf(promptDate, sizeof(promptDate), "Enter new date (DD-MM-YYYY) (or press Enter to keep '%s'): ", date);
        inputUnifiedBlock(promptDate, newDate, sizeof(newDate));
        if (strlen(newDate) == 0)
            strcpy(newDate, date);

        char promptTime[150];
        snprintf(promptTime, sizeof(promptTime), "Enter new time (or press Enter to keep '%s'): ", time);
        inputUnifiedBlock(promptTime, newTime, sizeof(newTime));
        if (strlen(newTime) == 0)
            strcpy(newTime, time);

        char promptSeat[100];
        snprintf(promptSeat, sizeof(promptSeat), "Enter new seat capacity (or 0 to keep %d): ", seatCapacity);
        char buf3[16];
        inputUnifiedBlock(promptSeat, buf3, sizeof(buf3));
        if (sscanf(buf3, "%d", &newSeatCapacity) != 1 || newSeatCapacity <= 0)
            newSeatCapacity = seatCapacity;

        // Update event in array (without extra newline)
        snprintf(events[choice - 1], sizeof(events[choice - 1]), "%s|%s|%s|%s|%d", newName, newVenue, newDate, newTime, newSeatCapacity);
        
        resetUnifiedBlock();
    printNotice("Event updated successfully!", 'S');
    printNotice("Press any key to continue...", 'I');
        getch();
        clear(); // Clear screen after event update
    }
    else if (action == 2)
    {
        // Delete event
        for (int i = choice - 1; i < eventCount - 1; i++)
        {
            strcpy(events[i], events[i + 1]);
        }
        eventCount--;
        clear();
        resetUnifiedBlock();
    printNotice("Event deleted successfully!", 'S');
    printNotice("Press any key to continue...", 'I');
        getch();
    }
    else
    {
        clear();
        return;
    }

    // Write updated events back to file
    file = fopen("events.txt", "w");
    if (file == NULL)
    {
        resetUnifiedBlock();
        printNotice("Error updating events file!", 'E');
        return;
    }
    for (int i = 0; i < eventCount; i++)
    {
        fprintf(file, "%s\n", events[i]);
    }
    fclose(file);
}

/**
 * Admin function to view all registered users
 */
void viewAllUsers()
{
    FILE *file = fopen(USER_INFO_FILE, "r");
    if (file == NULL)
    {
        boxBordered("No users found.", visualLen("No users found.") + 2);
        printUnified("");
    printNotice("Press any key to continue...", 'I');
        getch();
        return;
    }

    char line[200];
    int ticketCode;
    char name[100];
    // Build boxed list of users
    const char *ptrs[120];
    char items[120][300];
    int count = 0;
    while (fgets(line, sizeof(line), file) && count < 120)
    {
        if (sscanf(line, "%d,%99[^\n]", &ticketCode, name) == 2)
        {
            snprintf(items[count], sizeof(items[0]), "%04d | %s", ticketCode, name);
            ptrs[count] = items[count];
            count++;
        }
    }
    fclose(file);
    if (count == 0)
    {
        boxBordered("No users found.", visualLen("No users found.") + 2);
        printUnified("");
    printNotice("Press any key to continue...", 'I');
        getch();
        return;
    }
    printMenuItemsWithBoxes("All Registered Users", ptrs, count);

    // Centered continue prompt
    char continueBuf[10];
    inputUnified("Press Enter to continue...", continueBuf, sizeof(continueBuf));
    clear();
}

/*
 * ========================= BOOKING SYSTEM =========================
 */

/**
 * Helper function: Returns event name for given event ID
 */
char* getEventNameByID(int eventID)
{
    FILE *file = fopen("events.txt", "r");
    if (file == NULL)
    {
        static char defaultName[] = "Unknown Event";
        return defaultName;
    }

    char line[300], name[100], venue[100], date[20], time[20];
    int seatCapacity;
    int currentEventID = 1;
    static char eventName[100]; // Static to persist after function returns

    while (fgets(line, sizeof(line), file))
    {
        if (sscanf(line, "%99[^|]|%99[^|]|%19[^|]|%19[^|]|%d", name, venue, date, time, &seatCapacity) == 5)
        {
            if (currentEventID == eventID)
            {
                fclose(file);
                strcpy(eventName, name); // Copy to static variable
                return eventName;
            }
            currentEventID++;
        }
    }
    
    fclose(file);
    strcpy(eventName, "Unknown Event"); // Event ID not found
    return eventName;
}

void viewAllBookings()
{
    // Check if user is logged in
    if (strlen(loggedInUserName) == 0)
    {
    printNotice("You must be logged in to view your bookings.", 'E');
    printNotice("Press any key to continue...", 'I');
        getch();
        return;
    }

    FILE *file = fopen(BOOKINGS_FILE, "r");
    if (file == NULL)
    {
        boxBordered("No bookings found.", visualLen("No bookings found.") + 2);
        printUnified("");
    printNotice("Press any key to continue...", 'I');
        getch();
        return;
    }

    char line[200];
    int eventID;
    char name[100];
    char userBookings[50][200]; // Array to store current user's bookings
    int userBookingCount = 0;

    // First pass: collect booking information for the logged-in user only
    while (fgets(line, sizeof(line), file) && userBookingCount < 50)
    {
        if (sscanf(line, "%d %[^\n]", &eventID, name) == 2)
        {
            // Only store bookings for the current logged-in user
            if (strcmp(name, loggedInUserName) == 0)
            {
                strcpy(userBookings[userBookingCount], line);
                userBookingCount++;
            }
        }
    }
    fclose(file);
    
    if (userBookingCount == 0)
    {
    char buf[200];
    snprintf(buf, sizeof(buf), "No bookings found for %s.", loggedInUserName);
    boxBordered(buf, visualLen(buf) + 2);
    printUnified("");
    printNotice("Press any key to continue...", 'I');
    getch();
        return;
    }
    
    // Build boxed list for user bookings
    char title[256];
    snprintf(title, sizeof(title), "Your Bookings (%s)", loggedInUserName);
    const char *ptrs[60];
    char items[60][300];
    int itemsCount = 0;
    for (int i = 0; i < userBookingCount && itemsCount < 60; i++)
    {
        if (sscanf(userBookings[i], "%d %[^\n]", &eventID, name) == 2)
        {
            char *eventName = getEventNameByID(eventID);
            snprintf(items[itemsCount++], sizeof(items[0]), "%d | %s", eventID, eventName);
        }
    }
    for (int i = 0; i < itemsCount; i++) ptrs[i] = items[i];
    printMenuItemsWithBoxes(title, ptrs, itemsCount);

    // Centered continue prompt
    char continueBuf[10];
    inputUnified("Press Enter to continue...", continueBuf, sizeof(continueBuf));
    clear();
}

void adminViewAllBookings()
{
    FILE *file = fopen(BOOKINGS_FILE, "r");
    if (file == NULL)
    {
        boxBordered("No bookings found.", visualLen("No bookings found.") + 2);
        printUnified("");
    printNotice("Press any key to continue...", 'I');
        getch();
        return;
    }

    char line[200];
    int eventID;
    char name[100];
    char allBookings[100][200]; // Array to store all bookings
    int totalBookingCount = 0;

    // Collect all booking information
    while (fgets(line, sizeof(line), file) && totalBookingCount < 100)
    {
        if (sscanf(line, "%d %[^\n]", &eventID, name) == 2)
        {
            strcpy(allBookings[totalBookingCount], line);
            totalBookingCount++;
        }
    }
    fclose(file);
    
    if (totalBookingCount == 0)
    {
        boxBordered("No bookings found.", visualLen("No bookings found.") + 2);
        printUnified("");
    printNotice("Press any key to continue...", 'I');
        getch();
        return;
    }

    // Build boxed list
    const char *ptrs[120];
    char items[120][300];
    int itemsCount = 0;
    for (int i = 0; i < totalBookingCount && itemsCount < 120; i++)
    {
        if (sscanf(allBookings[i], "%d %[^\n]", &eventID, name) == 2)
        {
            char *eventName = getEventNameByID(eventID);
            snprintf(items[itemsCount++], sizeof(items[0]), "%s - %s", name, eventName);
        }
    }
    for (int i = 0; i < itemsCount; i++) ptrs[i] = items[i];
    printMenuItemsWithBoxes("All Bookings (Admin View)", ptrs, itemsCount);

    // Centered continue prompt
    char continueBuf[10];
    inputUnified("Press Enter to continue...", continueBuf, sizeof(continueBuf));
    clear();
}

void bookSeat()
{
    int eventID;

    resetUnifiedBlock();

    if (strlen(loggedInUserName) == 0)
    {
        printNotice("You must be logged in to book a seat.", 'E');
        printNotice("Press any key to continue...", 'I');
        getch();
        return;
    }

    FILE *file = fopen("events.txt", "r");
    if (file == NULL)
    {
        printNotice("No events found.", 'I');
        printNotice("Press any key to continue...", 'I');
        getch();
        return;
    }

    char line[300], eventName[100], venue[100], date[20], time[20];
    int seatCapacity;
    int eventCount = 0;
    char events[50][300];

    while (fgets(line, sizeof(line), file))
    {
        if (sscanf(line, "%99[^|]|%99[^|]|%19[^|]|%19[^|]|%d", eventName, venue, date, time, &seatCapacity) == 5)
        {
            if (eventCount < 50)
            {
                snprintf(events[eventCount], sizeof(events[eventCount]), "%s|%s|%s|%s|%d", eventName, venue, date, time, seatCapacity);
                eventCount++;
            }
        }
    }
    fclose(file);

    if (eventCount == 0)
    {
        printNotice("No events found.", 'I');
        printNotice("Press any key to continue...", 'I');
        getch();
        return;
    }

    const char *ptrs[60];
    char items[60][200];
    for (int i = 0; i < eventCount; i++)
    {
        char nm[100], vn[100], dt[20], tm[20]; int cap;
        sscanf(events[i], "%99[^|]|%99[^|]|%19[^|]|%19[^|]|%d", nm, vn, dt, tm, &cap);
        snprintf(items[i], sizeof(items[0]), "%d. %s", i + 1, nm);
        ptrs[i] = items[i];
    }
    char retLine[64];
    snprintf(retLine, sizeof(retLine), "%d. Return to main menu", eventCount + 1);
    ptrs[eventCount] = retLine;
    printMenuItemsWithBoxes("Book a Seat", ptrs, eventCount + 1);

    char promptBuf[100];
    snprintf(promptBuf, sizeof(promptBuf), "Enter event ID to book: ");
    char buf2[16];
    inputUnified(promptBuf, buf2, sizeof(buf2));
    if (sscanf(buf2, "%d", &eventID) != 1)
    {
        printNotice("Invalid input for Event ID.", 'W');
        printNotice("Press any key to continue...", 'I');
        getch();
        return;
    }

    if (eventID < 1 || eventID > eventCount + 1)
    {
        printNotice("Invalid Event ID.", 'W');
        printNotice("Press any key to continue...", 'I');
        getch();
        return;
    }

    if (eventID == eventCount + 1)
    {
        clear();
        return;
    }

    saveBooking(eventID, loggedInUserName);

    clear();
    sscanf(events[eventID - 1], "%99[^|]|%99[^|]|%19[^|]|%19[^|]|%d", eventName, venue, date, time, &seatCapacity);
    char msg[256];
    printNotice("Booking Confirmation", 'S');
    snprintf(msg, sizeof(msg), "Seat booked successfully for %s", loggedInUserName);
    printNotice(msg, 'S');
    snprintf(msg, sizeof(msg), "Event ID: %d", eventID);
    printNotice(msg, 'I');
    snprintf(msg, sizeof(msg), "Event: %s", eventName);
    printNotice(msg, 'I');

    char continueBuf[10];
    inputUnified("Press Enter to continue...", continueBuf, sizeof(continueBuf));
    clear();
}


void cancelBooking()
{
    int eventID;

    // Check if user is logged in
    if (strlen(loggedInUserName) == 0)
    {
    printNotice("You must be logged in to cancel a booking.", 'E');
    printNotice("Press any key to continue...", 'I');
        getch();
        return;
    }

    // First, show user's current bookings
    FILE *file = fopen(BOOKINGS_FILE, "r");
    if (file == NULL)
    {
    printNotice("No bookings found to cancel.", 'I');
    printNotice("Press any key to continue...", 'I');
        getch();
        return;
    }

    char line[200];
    int eventInLine;
    char nameInLine[100];
    char userBookings[50][200]; // Array to store current user's bookings
    int userBookingCount = 0;

    // Collect booking information for the logged-in user only
    while (fgets(line, sizeof(line), file) && userBookingCount < 50)
    {
        if (sscanf(line, "%d %[^\n]", &eventInLine, nameInLine) == 2)
        {
            // Only store bookings for the current logged-in user
            if (strcmp(nameInLine, loggedInUserName) == 0)
            {
                strcpy(userBookings[userBookingCount], line);
                userBookingCount++;
            }
        }
    }
    fclose(file);
    
    if (userBookingCount == 0)
    {
        char buf[200];
        snprintf(buf, sizeof(buf), "No bookings found for %s to cancel.", loggedInUserName);
        printNotice(buf, 'I');
        printNotice("Press any key to continue...", 'I');
        getch();
        return;
    }
    
    // Build boxed list of user's bookings
    const char *ptrs[60];
    char items[60][300];
    int count = 0;
    for (int i = 0; i < userBookingCount && count < 60; i++)
    {
        if (sscanf(userBookings[i], "%d %[^\n]", &eventInLine, nameInLine) == 2)
        {
            char *eventName = getEventNameByID(eventInLine);
            snprintf(items[count], sizeof(items[0]), "%d | %s", eventInLine, eventName);
            ptrs[count] = items[count];
            count++;
        }
    }
    {
        char title[256];
        snprintf(title, sizeof(title), "Your Current Bookings (%s)", loggedInUserName);
        printMenuItemsWithBoxes(title, ptrs, count);
    }

    // Now ask for the event ID to cancel
    char buf[16];
    inputUnified("Enter Event ID to cancel: ", buf, sizeof(buf));
    if (sscanf(buf, "%d", &eventID) != 1)
    {
        printNotice("Invalid input for Event ID.", 'W');
        printNotice("Press any key to continue...", 'I');
        getch();
        return;
    }

    // Use the logged-in user's name for cancellation
    removeBooking(eventID, loggedInUserName);

    // Add prompt to continue
    char continueBuf[10];
    inputUnifiedBlock("Press Enter to continue...", continueBuf, sizeof(continueBuf));
    clear(); // Clear screen after cancellation process
}

void saveBooking(int eventID, const char *name)
{
    FILE *file = fopen(BOOKINGS_FILE, "a");
    if (file == NULL)
    {
        printNotice("Error opening file, Name of event ID not Found!", 'E');
        return;
    }

    fprintf(file, "%d %s\n", eventID, name);
    fclose(file);
}

void removeBooking(int eventID, const char *name)
{
    FILE *file = fopen(BOOKINGS_FILE, "r");
    FILE *tempFile = fopen("temp.txt", "w");

    if (file == NULL || tempFile == NULL)
    {
        printNotice("Error opening file!", 'E');
        if (file)
            fclose(file);
        if (tempFile)
            fclose(tempFile);
        return;
    }

    char line[200];
    int eventInLine;
    char nameInLine[100];
    int found = 0;

    while (fgets(line, sizeof(line), file))
    {
        if (sscanf(line, "%d %[^\n]", &eventInLine, nameInLine) == 2)
        {
            if (eventInLine == eventID && strcmp(nameInLine, name) == 0)
            {
                found = 1;
                continue;
            }
        }
        fputs(line, tempFile);
    }

    fclose(file);
    fclose(tempFile);

    if (found)
    {
        remove(BOOKINGS_FILE);
        rename("temp.txt", BOOKINGS_FILE);
        printNotice("Booking successfully canceled.", 'S');
    }
    else
    {
        remove("temp.txt");
        char buf[200];
        snprintf(buf, sizeof(buf), "No booking found for %s at event ID %d.", name, eventID);
        printNotice(buf, 'I');
    }
}

/*
 * ========================= MAIN FUNCTION =========================
 */
int main()
{
    system("chcp 65001");
    srand((unsigned int)time(NULL));  // Initialize random seed for ticket generation
    landingPage();
    return 0;
}

/*
 * ========================= UI & DESIGN HELPERS (definitions) =========================
 *  Placed at the bottom per requested organization. No logic changes.
 */

// Clears the console screen for a fresh display
void clear()
{
    system("cls");
}

// Prints text centered on the console for professional appearance
void printCentered(const char *str)
{
    int width = getConsoleWidth();
    int len = visualLen(str);
    int pad = (width - len) / 2;
    if (pad < 0) pad = 0;
    for (int i = 0; i < pad; i++)
        putchar(' ');
    printf("%s\n", str);
}

// (inputCentered removed as unused)

// (inputPasswordHidden removed as unused)

// Displays the beautiful ASCII art welcome screen with application branding
void welcomePage()
{
    const char *art[] = {
        "","","                                                                       @@@     ",
        "                                                                     @@@ @@    ",
        "                                                                  @@@@    @@   ",
        "                                                               @@@@  @    @@   ",
        "                                                             @@@          @    ",
        "                                                          @@@-        @   @@@  ",
        "                                                       %@@@           .     @  ",
        "                                                     @@@               @    @  ",
        "                                                    @#                     @@  ",
        "                                                   @@                   #   @@ ",
        "                                                   @@                   @    @@",
        "                                                    @@                       @@",
        "        @@@@@@ @@     @@  @@@@@@ #@@    @@ @@@@@@@@  *@                  @   @ ",
        "        @@@@@@ *@@   @@@ @@@@@@@ @@@@   @@ @@@@@@@@  @@                  @.@@@ ",
        "        @@      @@   @@  @@      @@ @   @@    @@     @                  @@@    ",
        "        @@      @@   @@  @@      @@@@@  @@    @@     @@@             @@@@      ",
        "        @@@@@@  @@   @@  @@@@@@  @@@@@  @@    @@       @            @@         ",
        "        @@@@@@   @@ @@   @@@@@@  @@@ @@ @@    @@     .+#@@@@@@@@@@@@@@@@@@@@   ",
        "        @@       @@ @@   @@      @@@ @@ @@    @@     @@@@@@@@@@*-.     @   @@  ",
        "        @@       @@ @@   @@      @@@  @@@@    @@    @@                 @    @  ",
        "        @@@@@@   .@@@@   @@@@@@@ @@@  @@@@    @@    @                       @  ",
        "        @@@@@@    @@@     @@@@@@ @@@   @@@    @@    @@                 @   @:  ",
        "                                                     @                 @   @   ",
        "                        @@@@@   @@+   @@@@  @@@@@   @@                 @    @  ",
        "                        @@     @@@@  @@     @@      @                       @  ",
        "                        @@     @@ @  @@     @       @@                 @   @@  ",
        "                        @@@@@  @  @   @@@.  @@@@     @                 @   @   ",
        "                        @@    .@@@@@   :@@  @        @                 @   @@  ",
        "                        @@    @@@@@@     @@ @       @@                      @+ ",
        "                        @@@@@ @@   @ @@@@@@ @@@@@   @                  @    @@ ",
        "                         @@@@ @    @@*@@@@   @@@@   @@               =%@@@@@=  ",
        "                                                     @@@@@@@@@@@@@@@@@@@@@@@   ",
        ""
    };

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    WORD originalAttrs = csbi.wAttributes;

    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

    int lines = (int)(sizeof(art) / sizeof(art[0]));
    int width = getConsoleWidth();
    for (int i = 0; i < lines; i++) {
        const char *line = art[i];
        int vlen = visualLen(line);
        int doubled = vlen * 2;
        if (doubled > 0 && doubled <= width) {
            // Print with simple "bold" effect by doubling characters if it fits the screen
            for (const char *p = line; *p; p++) {
                putchar(*p); putchar(*p);
            }
        } else {
            // Fallback: print once to avoid wrapping/"destroyed" art
            fputs(line, stdout);
        }
        putchar('\n');
    }

    SetConsoleTextAttribute(hConsole, originalAttrs);
}

void dashboardDesign()
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO ci;
    GetConsoleScreenBufferInfo(h, &ci);

    SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

    const char *art[] = {
        "  _____             _____  _    _  ____    ____            _____   _____  ",
        " |  __ \\    /\\     / ____|| |  | ||  _ \\  / __ \\    /\\    |  __ \\ |  __ \\ ",
        " | |  | |  /  \\   | (___  | |__| || |_) || |  | |  /  \\   | |__) || |  | |",
        " | |  | | / /\\ \\   \\\\___ \\ |  __  ||  _ < | |  | | / /\\ \\  |  _  / | |  | |",
        " | |__| |/ ____ \\  ____) || |  | || |_) || |__| |/ ____ \\ | | \\ \\ | |__| |",
        " |_____//_/    \\_\\|_____/ |_|  |_||____/  \\____//_/    \\_\\|_|  \\_\\|_____/ ",
        "                                                                          "};

    int lines = sizeof(art) / sizeof(art[0]);
    for (int i = 0; i < lines; i++)
    {
        printCentered(art[i]);
        Sleep(60);
    }

    SetConsoleTextAttribute(h, ci.wAttributes);
}

// Admin dashboard design with red color
void adminDashboardDesign()
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO ci;
    GetConsoleScreenBufferInfo(h, &ci);

    SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);

    const char *ascii_art5 =
        "           _____  __  __ _____ _   _ \n"
        "     /\\   |  __ \\|  \\/  |_   _| \\ | |\n"
        "    /  \\  | |  | | \\  / | | | |  \\| |\n"
        "   / /\\ \\ | |  | | |\\/| | | | | . ` |\n"
        "  / ____ \\| |__| | |  | |_| |_| |\\  |\n"
        " /_/    \\_\\|_____/|_|  |_|_____|_| \\_|\n"
        "                                     \n"
        "                                     \n";

    // Split the art by lines and print each one centered
    char line[100];
    const char *ptr = ascii_art5;
    while (*ptr)
    {
        int i = 0;
        while (*ptr && *ptr != '\n' && i < 99)
        {
            line[i++] = *ptr++;
        }
        line[i] = '\0';
        if (*ptr == '\n') ptr++; // Skip the newline
        
        printCentered(line);
        Sleep(80);
    }

    SetConsoleTextAttribute(h, ci.wAttributes);
}

/*
 * ========================= UNIFIED POSITIONING (functions) =========================
 */

// Gets the width of the console window for proper alignment
int getConsoleWidth()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (GetConsoleScreenBufferInfo(hConsole, &csbi))
        return csbi.srWindow.Right - csbi.srWindow.Left + 1;
    return 80;
}

// Calculates the center position for given content width
int calculateCenterPosition(int contentWidth)
{
    int consoleWidth = getConsoleWidth();
    int centerPos = (consoleWidth - contentWidth) / 2;
    return (centerPos < 0) ? 0 : centerPos;
}

// Prints text using the unified positioning system for consistency
void printUnified(const char *str)
{
    int len = visualLen(str);
    int pad = calculateCenterPosition(len);

    for (int i = 0; i < pad; i++)
        putchar(' ');
    printf("%s\n", str);
}

// Compact, centered notice box (double-line border) for one-off messages.
// type: 'I' info, 'S' success, 'W' warning, 'E' error
void printNotice(const char *msg, char type)
{
    // Choose icon per type
    const char *icon = "";
    WORD colorAttrs = 0;
    switch (type)
    {
    case 'S': icon = "\xE2\x9C\x94"; colorAttrs = FOREGROUND_GREEN | FOREGROUND_INTENSITY; break;      // ✓
    case 'W': icon = "\xE2\x9A\xA0"; colorAttrs = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY; break; // ⚠
    case 'E': icon = "\xE2\x9C\x96"; colorAttrs = FOREGROUND_RED | FOREGROUND_INTENSITY; break;          // ✖
    default:  icon = "\xE2\x84\xB9"; colorAttrs = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY; break; // ℹ
    }

    char content[1024];
    if (msg && msg[0]) snprintf(content, sizeof(content), "%s %s", icon, msg);
    else snprintf(content, sizeof(content), "%s", icon);

    int inner = visualLen(content) + 2; // one space padding on each side
    if (inner < 4) inner = 4;

    // Build double-line box: ╔ ═ ╗ / ║ content ║ / ╚ ═ ╝
    char top[1100], mid[1100], bot[1100];
    int n = inner; if (n > 1000) n = 1000;
    int k = 0;
    // top
    top[k++] = '\xE2'; top[k++] = '\x95'; top[k++] = '\x94'; // ╔
    for (int i = 0; i < n; i++) { top[k++] = '\xE2'; top[k++] = '\x95'; top[k++] = '\x90'; } // ═
    top[k++] = '\xE2'; top[k++] = '\x95'; top[k++] = '\x97'; // ╗
    top[k] = '\0';
    // bottom
    k = 0;
    bot[k++] = '\xE2'; bot[k++] = '\x95'; bot[k++] = '\x9A'; // ╚
    for (int i = 0; i < n; i++) { bot[k++] = '\xE2'; bot[k++] = '\x95'; bot[k++] = '\x90'; } // ═
    bot[k++] = '\xE2'; bot[k++] = '\x95'; bot[k++] = '\x9D'; // ╝
    bot[k] = '\0';
    // middle
    int contentWidth = inner - 2; if (contentWidth < 0) contentWidth = 0;
    snprintf(mid, sizeof(mid), "\xE2\x95\x91 %-*s \xE2\x95\x91", contentWidth, content); // ║ content ║

    // Colorize output
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO ci;
    GetConsoleScreenBufferInfo(h, &ci);
    SetConsoleTextAttribute(h, colorAttrs);

    printUnified(top);
    printUnified(mid);
    printUnified(bot);
    printUnified("");

    // restore
    SetConsoleTextAttribute(h, ci.wAttributes);
}

// Draw a single centered box around a text. innerWidth controls the text area width (excluding borders)
void boxBordered(const char *text, int innerWidth)
{
    int textVis = visualLen(text);
    if (innerWidth < textVis) innerWidth = textVis;
    // Build Unicode borders ┌ ─ ┐ and └ ─ ┘, with │ sides
    char top[1024], bottom[1024], middle[1024];
    int count = innerWidth;
    if (count > 1000) count = 1000;
    int idx = 0;
    // Top: ┌──…──┐
    top[idx++] = '\xE2'; top[idx++] = '\x94'; top[idx++] = '\x8C'; // ┌
    for (int i = 0; i < count; i++) { top[idx++] = '\xE2'; top[idx++] = '\x94'; top[idx++] = '\x80'; }
    top[idx++] = '\xE2'; top[idx++] = '\x94'; top[idx++] = '\x90'; // ┐
    top[idx] = '\0';
    // Bottom: └──…──┘
    idx = 0;
    bottom[idx++] = '\xE2'; bottom[idx++] = '\x94'; bottom[idx++] = '\x94'; // └
    for (int i = 0; i < count; i++) { bottom[idx++] = '\xE2'; bottom[idx++] = '\x94'; bottom[idx++] = '\x80'; }
    bottom[idx++] = '\xE2'; bottom[idx++] = '\x94'; bottom[idx++] = '\x98'; // ┘
    bottom[idx] = '\0';

    // Middle line: │ text │ (with one leading/trailing space inside)
    // Apply cyan color to generic boxes
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO ci;
    GetConsoleScreenBufferInfo(h, &ci);
    SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

    printUnified(top);
    // The formatted width should match the visual inner width minus 2 (for spaces)
    int contentWidth = innerWidth - 2; if (contentWidth < 0) contentWidth = 0;
    snprintf(middle, sizeof(middle), "\xE2\x94\x82 %-*s \xE2\x94\x82", contentWidth, text); // │ text │
    printUnified(middle);
    printUnified(bottom);

    // Restore original console attributes and add a blank line for spacing
    SetConsoleTextAttribute(h, ci.wAttributes);
    printUnified("");
}

// Utility to render a title then each item as an individual equal-width box
void printMenuItemsWithBoxes(const char *title, const char **items, int count)
{
    // Determine the maximum width among items
    int maxItemLen = 0;
    for (int i = 0; i < count; i++)
    {
        int l = visualLen(items[i]);
        if (l > maxItemLen) maxItemLen = l;
    }
    // Aim for consistent padding: we reserve 2 spaces inside (one on each side in format)
    int innerWidth = maxItemLen + 2;

    if (title && strlen(title) > 0)
    {
        printUnified(title);
        // Use a Unicode light horizontal line underline matching the box width
        int underlineLen = visualLen(title);
        if (underlineLen < innerWidth) underlineLen = innerWidth;
        char u[1024];
        int n = underlineLen; if (n > 1000) n = 1000;
        int k = 0; for (int i = 0; i < n; i++) { u[k++] = '\xE2'; u[k++] = '\x94'; u[k++] = '\x80'; }
        u[k] = '\0';
        printUnified(u);
        printUnified("");
    }

    for (int i = 0; i < count; i++)
    {
        boxBordered(items[i], innerWidth);
    }
}

// Gets input using unified positioning for consistent UI
void inputUnified(const char *prompt, char *buffer, int size)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    
    int promptLen = visualLen(prompt);
    int totalLen = promptLen + size;
    int pad = calculateCenterPosition(totalLen);
    
    COORD pos = csbi.dwCursorPosition;
    pos.X = pad;
    SetConsoleCursorPosition(hConsole, pos);
    
    printf("%s", prompt);
    fflush(stdout);
    
    pos.X += promptLen;
    SetConsoleCursorPosition(hConsole, pos);
    
    fgets(buffer, size, stdin);
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n')
        buffer[len - 1] = '\0';
}

// Approximate visible length for UTF-8 strings; counts ASCII as 1, treats UTF-8 multi-byte sequences as width 1
int visualLen(const char *s)
{
    int count = 0;
    const unsigned char *p = (const unsigned char *)s;
    while (*p)
    {
        if (*p < 0x80)
        {
            // ASCII
            count++; p++;
        }
        else if ((*p & 0xE0) == 0xC0)
        {
            // 2-byte UTF-8
            count++; p += 2;
        }
        else if ((*p & 0xF0) == 0xE0)
        {
            // 3-byte UTF-8
            count++; p += 3;
        }
        else if ((*p & 0xF8) == 0xF0)
        {
            // 4-byte UTF-8
            count++; p += 4;
        }
        else
        {
            // Fallback: count and advance by 1
            count++; p++;
        }
    }
    return count;
}

// Input function for block-aligned interface elements
void inputUnifiedBlock(const char *prompt, char *buffer, int size)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    
    int promptLen = (int)strlen(prompt);
    int pad = unified_blockStartPos;
    
    if (pad == -1) {
        pad = calculateCenterPosition(promptLen + size);
    }
    
    COORD pos = csbi.dwCursorPosition;
    pos.X = pad;
    SetConsoleCursorPosition(hConsole, pos);
    
    printf("%s", prompt);
    fflush(stdout);
    
    pos.X += promptLen;
    SetConsoleCursorPosition(hConsole, pos);
    
    fgets(buffer, size, stdin);
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n')
        buffer[len - 1] = '\0';
}

// Resets the unified block positioning system for new screens
void resetUnifiedBlock()
{
    unified_blockMaxLen = 0;
    unified_blockStartPos = -1;
    unified_blockFirstCall = 1;
}

// Prints text left-aligned within unified blocks for consistent layout
void printUnifiedBlockLeft(const char *str)
{
    int currentLen = (int)strlen(str);
    
    if (unified_blockFirstCall) {
        if (currentLen > unified_blockMaxLen) {
            unified_blockMaxLen = currentLen;
        }
        return;
    }
    
    if (unified_blockStartPos == -1) {
        unified_blockStartPos = calculateCenterPosition(unified_blockMaxLen);
    }
    
    for (int i = 0; i < unified_blockStartPos; i++) {
        putchar(' ');
    }
    
    printf("%s\n", str);
}

// Password input using unified positioning with delayed character masking
void inputPasswordUnified(char *buffer, int size)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    
    // Position cursor at unified block position
    COORD pos = csbi.dwCursorPosition;
    pos.X = unified_blockStartPos;
    SetConsoleCursorPosition(hConsole, pos);
    printf("Password: ");
    fflush(stdout);
    
    // Read password character by character with hidden input
    int i = 0;
    char ch;
    buffer[0] = '\0'; // Initialize buffer
    
    while (i < size - 1) // Leave space for null terminator
    {
        ch = getch(); // Get character without echo
        
        if (ch == '\r' || ch == '\n') // Enter key
        {
            break;
        }
        else if (ch == '\b' && i > 0) // Backspace
        {
            i--;
            printf("\b \b"); // Erase last asterisk
            fflush(stdout);
        }
        else if (ch != '\b') // Regular character
        {
            buffer[i] = ch;
            i++;
            printf("%c", ch); // Display actual character first
            fflush(stdout);
            Sleep(75); // Short preview for 75 ms
            printf("\b*"); // Replace with asterisk
            fflush(stdout);
        }
    }
    
    buffer[i] = '\0'; // Null terminate
    printf("\n"); // Move to next line
}
