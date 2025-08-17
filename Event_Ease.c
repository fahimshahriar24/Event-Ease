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


#define BOOKINGS_FILE "bookings.txt"
#define USER_INFO_FILE "user_info.txt"

char loggedInUserName[100] = "";  // Stores currently logged-in user's name

/*
 * ========================= FUNCTION DECLARATIONS =========================
 */

// User Interface
void clear();
void welcomePage();
void dashboardDesign();
void printCentered(const char *str);
void inputCentered(const char *prompt, char *buffer, int size);

// Unified positioning system for consistent UI alignment
int getConsoleWidth();
int calculateCenterPosition(int contentWidth);
void printUnified(const char *str);
void inputUnified(const char *prompt, char *buffer, int size);
void inputUnifiedBlock(const char *prompt, char *buffer, int size);
void printUnifiedBlockLeft(const char *str);
void resetUnifiedBlock();

// Authentication and user management
void landingPage();
void newUserRegistration();
void existingUserLogin();
void adminLogin();
void inputPasswordHidden(const char *prompt, char *buffer, int size);
void inputPasswordUnified(char *buffer, int size);
int generateUniqueTicketCode();
int isTicketCodeExists(int ticketCode);
int isNameExists(const char *name);
void saveUserInfo(int ticketCode, const char *name);
int validateUserLogin(const char *name, int ticketCode);

// Main navigation dashboards
void userDashboard();
void adminDashboard();

// Event management
void viewEvents();
void addEvent();
void adminViewAllEvents();
void viewAllUsers();

// Booking system
void bookSeat();
void bookSeatDirectly(int eventID);
void cancelBooking();
void saveBooking(int eventID, const char *name);
void removeBooking(int eventID, const char *name);
void viewAllBookings();
void adminViewAllBookings();
void viewEventDetails();
char* getEventNameByID(int eventID);

/*
 * ========================= USER INTERFACE =========================
 */

void clear()
{
    system("cls");
}

void printCentered(const char *str)
{
    int width = getConsoleWidth();
    int len = (int)strlen(str);
    int pad = (width - len) / 2;
    if (pad < 0) pad = 0;
    for (int i = 0; i < pad; i++)
        putchar(' ');
    printf("%s\n", str);
}

void inputCentered(const char *prompt, char *buffer, int size)
{
    int width = getConsoleWidth();
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    int promptLen = (int)strlen(prompt);
    int pad = (width - promptLen - size) / 2;
    if (pad < 0) pad = 0;
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

void inputPasswordHidden(const char *prompt, char *buffer, int size)
{
    int width = getConsoleWidth();
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    int promptLen = (int)strlen(prompt);
    int pad = (width - promptLen) / 2;
    if (pad < 0) pad = 0;
    
    // Position and display prompt
    COORD pos = csbi.dwCursorPosition;
    pos.X = pad;
    SetConsoleCursorPosition(hConsole, pos);
    printf("%s", prompt);
    fflush(stdout);
    
    // Read password character by character
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
            printf("*"); // Display asterisk
            fflush(stdout);
        }
    }
    
    buffer[i] = '\0'; // Null terminate
    printf("\n"); // Move to next line
}

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

    for (int i = 0; i < 35; i++) {
        for (const char *p = art[i]; *p; p++) {
            putchar(*p); putchar(*p);
            fflush(stdout); Sleep(0);
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
        " | |  | | / /\\ \\   \\___ \\ |  __  ||  _ < | |  | | / /\\ \\  |  _  / | |  | |",
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

/*
 * ========================= UNIFIED POSITIONING SYSTEM =========================
 * Ensures consistent alignment across all UI elements
 */

static int unified_blockMaxLen = 0;
static int unified_blockStartPos = -1;
static int unified_blockFirstCall = 1;

int getConsoleWidth()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (GetConsoleScreenBufferInfo(hConsole, &csbi))
        return csbi.srWindow.Right - csbi.srWindow.Left + 1;
    return 80;
}

int calculateCenterPosition(int contentWidth)
{
    int consoleWidth = getConsoleWidth();
    int centerPos = (consoleWidth - contentWidth) / 2;
    return (centerPos < 0) ? 0 : centerPos;
}

void printUnified(const char *str)
{
    int len = (int)strlen(str);
    int pad = calculateCenterPosition(len);
    
    for (int i = 0; i < pad; i++)
        putchar(' ');
    printf("%s\n", str);
}

void inputUnified(const char *prompt, char *buffer, int size)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    
    int promptLen = (int)strlen(prompt);
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

void resetUnifiedBlock()
{
    unified_blockMaxLen = 0;
    unified_blockStartPos = -1;
    unified_blockFirstCall = 1;
}

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
            printf("*"); // Display asterisk
            fflush(stdout);
        }
    }
    
    buffer[i] = '\0'; // Null terminate
    printf("\n"); // Move to next line
}

/*
 * ========================= AUTHENTICATION & LANDING PAGE =========================
 */

void landingPage()
{
    int choice;
    
    while (1)
    {
        clear();
        welcomePage();
        
        resetUnifiedBlock();
        printUnifiedBlockLeft("Welcome to Event-Ease!");
        printUnifiedBlockLeft("=====================");
        printUnifiedBlockLeft("");
        printUnifiedBlockLeft("1. New User Registration");
        printUnifiedBlockLeft("2. Existing User Login");
        printUnifiedBlockLeft("3. Admin Login");
        printUnifiedBlockLeft("0. Exit");
        
        resetUnifiedBlock();
        unified_blockFirstCall = 0;
        
        printUnifiedBlockLeft("Welcome to Event-Ease!");
        printUnifiedBlockLeft("=====================");
        printUnifiedBlockLeft("");
        printUnifiedBlockLeft("1. New User Registration");
        printUnifiedBlockLeft("2. Existing User Login");
        printUnifiedBlockLeft("3. Admin Login");
        printUnifiedBlockLeft("0. Exit");
        
        char buf[16];
        inputUnifiedBlock("Select an option: ", buf, sizeof(buf));
        if (sscanf(buf, "%d", &choice) != 1)
        {
            resetUnifiedBlock();
            printUnifiedBlockLeft("Invalid input. Please enter a number.");
            printUnifiedBlockLeft("Press any key to continue...");
            
            resetUnifiedBlock();
            unified_blockFirstCall = 0;
            printUnifiedBlockLeft("Invalid input. Please enter a number.");
            printUnifiedBlockLeft("Press any key to continue...");
            
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
            printUnified("Thank you for using Event-Ease!");
            printUnified("Goodbye!");
            exit(0);
        default:
            resetUnifiedBlock();
            printUnifiedBlockLeft("Invalid choice. Please select again.");
            printUnifiedBlockLeft("Press any key to continue...");
            
            resetUnifiedBlock();
            unified_blockFirstCall = 0;
            printUnifiedBlockLeft("Invalid choice. Please select again.");
            printUnifiedBlockLeft("Press any key to continue...");
            
            getch();
        }
    }
}

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
            
            printUnified("Press any key to try again...");
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
            
            printUnified("Press any key to try again...");
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
        // Use unified block for error messages
        resetUnifiedBlock();
        printUnifiedBlockLeft("Error: Unable to generate unique ticket code.");
        printUnifiedBlockLeft("Please try again later.");
        printUnifiedBlockLeft("Press any key to continue...");
        
        resetUnifiedBlock();
        unified_blockFirstCall = 0;
        printUnifiedBlockLeft("Error: Unable to generate unique ticket code.");
        printUnifiedBlockLeft("Please try again later.");
        printUnifiedBlockLeft("Press any key to continue...");
        
        getch();
        return;
    }
    
    saveUserInfo(ticketCode, name);
    strcpy(loggedInUserName, name);
    
    // Display registration success using unified block system
    resetUnifiedBlock();
    printUnifiedBlockLeft("Registration Successful!");
    printUnifiedBlockLeft("========================");
    printUnifiedBlockLeft("");
    char ticketMsg[100];
    snprintf(ticketMsg, sizeof(ticketMsg), "Your ticket code is: %04d", ticketCode);
    printUnifiedBlockLeft(ticketMsg);
    printUnifiedBlockLeft("Please remember your ticket code for future logins.");
    printUnifiedBlockLeft("");
    printUnifiedBlockLeft("Press any key to continue to your dashboard...");
    
    // Second pass to actually print with alignment
    resetUnifiedBlock();
    unified_blockFirstCall = 0;
    printUnifiedBlockLeft("Registration Successful!");
    printUnifiedBlockLeft("========================");
    printUnifiedBlockLeft("");
    printUnifiedBlockLeft(ticketMsg);
    printUnifiedBlockLeft("Please remember your ticket code for future logins.");
    printUnifiedBlockLeft("");
    printUnifiedBlockLeft("Press any key to continue to your dashboard...");
    
    getch();
    
    clear();
    userDashboard();
}

/**
 * Existing user login - validates credentials against stored data
 */
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
        // Use unified block for error messages
        resetUnifiedBlock();
        printUnifiedBlockLeft("Invalid ticket code format. Please enter a 4-digit number.");
        printUnifiedBlockLeft("Press any key to continue...");
        
        resetUnifiedBlock();
        unified_blockFirstCall = 0;
        printUnifiedBlockLeft("Invalid ticket code format. Please enter a 4-digit number.");
        printUnifiedBlockLeft("Press any key to continue...");
        
        getch();
        return;
    }
    
    // Validate ticket code range
    if (ticketCode < 0 || ticketCode > 9999)
    {
        // Use unified block for error messages
        resetUnifiedBlock();
        printUnifiedBlockLeft("Invalid ticket code. Must be between 0000-9999.");
        printUnifiedBlockLeft("Press any key to continue...");
        
        resetUnifiedBlock();
        unified_blockFirstCall = 0;
        printUnifiedBlockLeft("Invalid ticket code. Must be between 0000-9999.");
        printUnifiedBlockLeft("Press any key to continue...");
        
        getch();
        return;
    }
    
    if (validateUserLogin(name, ticketCode))
    {
        strcpy(loggedInUserName, name);
        
        resetUnifiedBlock();
        printUnifiedBlockLeft("Login successful!");
        printUnifiedBlockLeft("Welcome back!");
        printUnifiedBlockLeft("Press any key to continue to your dashboard...");
        
        resetUnifiedBlock();
        unified_blockFirstCall = 0;
        printUnifiedBlockLeft("Login successful!");
        printUnifiedBlockLeft("Welcome back!");
        printUnifiedBlockLeft("Press any key to continue to your dashboard...");
        
        getch();
        
        clear();
        userDashboard();
        // After logout, user returns here and function ends normally
        // This should return control to landingPage() main menu
    }
    else
    {
        // Use unified block for error messages
        resetUnifiedBlock();
        printUnifiedBlockLeft("Invalid credentials. Name or ticket code does not match.");
        printUnifiedBlockLeft("Please check your information and try again.");
        printUnifiedBlockLeft("Press any key to continue...");
        
        resetUnifiedBlock();
        unified_blockFirstCall = 0;
        printUnifiedBlockLeft("Invalid credentials. Name or ticket code does not match.");
        printUnifiedBlockLeft("Please check your information and try again.");
        printUnifiedBlockLeft("Press any key to continue...");
        
        getch();
    }
}

/**
 * Admin login - hardcoded credentials for admin access
 */
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
    
    if (strcmp(username, "admin") == 0 && strcmp(password, "password") == 0)
    {
        resetUnifiedBlock();
        printUnifiedBlockLeft("Admin login successful!");
        printUnifiedBlockLeft("Access granted to admin panel.");
        printUnifiedBlockLeft("Press any key to continue...");
        
        resetUnifiedBlock();
        unified_blockFirstCall = 0;
        printUnifiedBlockLeft("Admin login successful!");
        printUnifiedBlockLeft("Access granted to admin panel.");
        printUnifiedBlockLeft("Press any key to continue...");
        
        getch();
        
        clear();
        adminDashboard();
    }
    else
    {
        // Use unified block for error messages
        resetUnifiedBlock();
        printUnifiedBlockLeft("Invalid admin credentials.");
        printUnifiedBlockLeft("Access denied.");
        printUnifiedBlockLeft("Press any key to continue...");
        
        resetUnifiedBlock();
        unified_blockFirstCall = 0;
        printUnifiedBlockLeft("Invalid admin credentials.");
        printUnifiedBlockLeft("Access denied.");
        printUnifiedBlockLeft("Press any key to continue...");
        
        getch();
    }
}

/**
 * Generate a unique 4-digit ticket code (0000-9999)
 * Returns -1 if unable to generate unique code after max attempts
 */
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

/**
 * Check if a ticket code already exists in the user_info.txt file
 * Returns 1 if exists, 0 if not exists
 */
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

/**
 * Check if a name already exists in the user_info.txt file
 * Returns 1 if name exists, 0 if it doesn't exist
 */
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
            if (_stricmp(existingName, name) == 0)
            {
                fclose(file);
                return 1; // Name exists
            }
        }
    }
    
    fclose(file);
    return 0; // Name doesn't exist
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
        printUnifiedBlockLeft("Error: Unable to save user information.");
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
        
        resetUnifiedBlock();
        printUnifiedBlockLeft("1. View Event Details");
        printUnifiedBlockLeft("2. Book Seat");
        printUnifiedBlockLeft("3. Cancel Booking");
        printUnifiedBlockLeft("4. View All Bookings");
        printUnifiedBlockLeft("5. Logout");
        printUnifiedBlockLeft("0. Exit");
        
        // Second pass - actually print the menu
        unified_blockFirstCall = 0;
        printUnifiedBlockLeft("1. View Event Details");
        printUnifiedBlockLeft("2. Book Seat");
        printUnifiedBlockLeft("3. Cancel Booking");
        printUnifiedBlockLeft("4. View All Bookings");
        printUnifiedBlockLeft("5. Logout");
        printUnifiedBlockLeft("0. Exit");
        
        // Get input using unified block positioning
        char buf[16];
        inputUnifiedBlock("Select an option: ", buf, sizeof(buf));
            
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
            viewEventDetails();
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
            resetUnifiedBlock();
            printUnifiedBlockLeft("Successfully logged out!");
            printUnifiedBlockLeft("Returning to main menu...");
            unified_blockFirstCall = 0;
            printUnifiedBlockLeft("Successfully logged out!");
            printUnifiedBlockLeft("Returning to main menu...");
            Sleep(1500); // Show message for 1.5 seconds instead of waiting for key press
            clear(); // Clear screen before returning to main menu
            return;
        case 0:
            clear();
            resetUnifiedBlock();
            printUnifiedBlockLeft("Thank you for using Event-Ease!");
            printUnifiedBlockLeft("Press any key to exit...");
            getch();
            exit(0);
        default:
            clear();
            resetUnifiedBlock();
            printUnifiedBlockLeft("Invalid choice. Please select again.");
            printUnifiedBlockLeft("Press any key to continue...");
            getch();
        }
    }
}

void adminDashboard()
{
    int choice;
    while (1)
    {
        dashboardDesign();
        
        resetUnifiedBlock();
        printUnifiedBlockLeft("1. View all bookings");
        printUnifiedBlockLeft("2. Add Event");
        printUnifiedBlockLeft("3. View All Events");
        printUnifiedBlockLeft("4. View All Users");
        printUnifiedBlockLeft("5. Logout");
        printUnifiedBlockLeft("0. Exit");
        
        // Second pass - actually print the menu
        unified_blockFirstCall = 0;
        printUnifiedBlockLeft("1. View all bookings");
        printUnifiedBlockLeft("2. Add Event");
        printUnifiedBlockLeft("3. View All Events");
        printUnifiedBlockLeft("4. View All Users");
        printUnifiedBlockLeft("5. Logout");
        printUnifiedBlockLeft("0. Exit");
        
        // Get input using unified block positioning
        char buf[16];
        inputUnifiedBlock("Select an option: ", buf, sizeof(buf));
            
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
            resetUnifiedBlock();
            printUnifiedBlockLeft("Logging out of admin panel...");
            unified_blockFirstCall = 0;
            printUnifiedBlockLeft("Logging out of admin panel...");
            Sleep(1500); // Show message for 1.5 seconds instead of waiting for key press
            return; // Return to landing page
        case 0:
            clear();
            resetUnifiedBlock();
            printUnifiedBlockLeft("Thank you for using Event-Ease!");
            printUnifiedBlockLeft("Press any key to exit...");
            getch();
            exit(0);
        default:
            clear();
            resetUnifiedBlock();
            printUnifiedBlockLeft("Invalid choice. Please select again.");
            printUnifiedBlockLeft("Press any key to continue...");
            getch();
        }
    }
}
/*
 * ========================= EVENT MANAGEMENT =========================
 */
void viewEvents()
{
    FILE *file = fopen("events.txt", "r");
    if (file == NULL)
    {
        resetUnifiedBlock();
        printUnifiedBlockLeft("No events found.");
        return;
    }

    char line[300], name[100], venue[100], date[20], time[20];
    int seatCapacity;
    int eventCount = 0;
    char events[50][300]; // Store up to 50 events

    resetUnifiedBlock();
    printUnifiedBlockLeft("=== Available Events ===");
    printUnifiedBlockLeft("");
    
    // First pass - collect all event strings
    while (fgets(line, sizeof(line), file))
    {
        if (sscanf(line, "%99[^|]|%99[^|]|%19[^|]|%19[^|]|%d", name, venue, date, time, &seatCapacity) == 5)
        {
            eventCount++;
            snprintf(events[eventCount - 1], sizeof(events[eventCount - 1]), "%s|%s|%s|%s|%d", name, venue, date, time, seatCapacity);
            char buf[200];
            snprintf(buf, sizeof(buf), "%d. %s", eventCount, name);
            printUnifiedBlockLeft(buf);
        }
    }
    fclose(file);
    
    char returnBuf[100];
    snprintf(returnBuf, sizeof(returnBuf), "%d. Return to main menu", eventCount + 1);
    printUnifiedBlockLeft(returnBuf);

    if (eventCount == 0)
        return;

    int choice;
    char selectPrompt[100];
    snprintf(selectPrompt, sizeof(selectPrompt), "Select an event to view details or %d to return: ", eventCount + 1);
    char buf_input[16];
    inputUnifiedBlock(selectPrompt, buf_input, sizeof(buf_input));
    if (sscanf(buf_input, "%d", &choice) != 1)
    {
        resetUnifiedBlock();
        printUnifiedBlockLeft("Invalid input.");
        return;
    }
    if (choice < 1 || choice > eventCount + 1)
    {
        resetUnifiedBlock();
        printUnifiedBlockLeft("Invalid choice.");
        return;
    }
    if (choice == eventCount + 1)
    {
        clear(); // Clear screen before returning to dashboard
        return;
    }

    // Show details for selected event
    clear();
    sscanf(events[choice - 1], "%99[^|]|%99[^|]|%19[^|]|%19[^|]|%d", name, venue, date, time, &seatCapacity);
    
    resetUnifiedBlock();
    printUnifiedBlockLeft("=== Event Details ===");
    printUnifiedBlockLeft("");
    
    char detail_buf[200];
    snprintf(detail_buf, sizeof(detail_buf), "Name: %s", name);
    printUnifiedBlockLeft(detail_buf);
    snprintf(detail_buf, sizeof(detail_buf), "Venue: %s", venue);
    printUnifiedBlockLeft(detail_buf);
    snprintf(detail_buf, sizeof(detail_buf), "Date (DD-MM-YYYY): %s", date);
    printUnifiedBlockLeft(detail_buf);
    snprintf(detail_buf, sizeof(detail_buf), "Time: %s", time);
    printUnifiedBlockLeft(detail_buf);
    snprintf(detail_buf, sizeof(detail_buf), "Seat Capacity: %d", seatCapacity);
    printUnifiedBlockLeft(detail_buf);

    // Add prompt to continue
    char continueBuf[10];
    inputUnifiedBlock("Press Enter to continue...", continueBuf, sizeof(continueBuf));
    clear(); // Clear screen after viewing event details
}

/**
 * View event details with booking options
 * Shows events list, then detailed view with booking options
 */
void viewEventDetails()
{
    FILE *file = fopen("events.txt", "r");
    if (file == NULL)
    {
        resetUnifiedBlock();
        printUnifiedBlockLeft("No events found.");
        printUnifiedBlockLeft("Press any key to continue...");
        getch();
        return;
    }

    char line[300], name[100], venue[100], date[20], time[20];
    int seatCapacity;
    int eventCount = 0;
    char events[50][300]; // Store up to 50 events

    // Use unified block system for consistency
    resetUnifiedBlock();
    printUnifiedBlockLeft("=== Available Events ===");
    printUnifiedBlockLeft("");
    
    // First pass - collect all events and measure them
    while (fgets(line, sizeof(line), file))
    {
        if (sscanf(line, "%99[^|]|%99[^|]|%19[^|]|%19[^|]|%d", name, venue, date, time, &seatCapacity) == 5)
        {
            eventCount++;
            snprintf(events[eventCount - 1], sizeof(events[eventCount - 1]), "%s|%s|%s|%s|%d", name, venue, date, time, seatCapacity);
            char buf[200];
            snprintf(buf, sizeof(buf), "%d. %s", eventCount, name);
            printUnifiedBlockLeft(buf);
        }
    }
    fclose(file);
    
    if (eventCount == 0)
    {
        resetUnifiedBlock();
        printUnifiedBlockLeft("No events available.");
        printUnifiedBlockLeft("Press any key to continue...");
        getch();
        return;
    }
    
    char returnBuf[100];
    snprintf(returnBuf, sizeof(returnBuf), "%d. Return to main menu", eventCount + 1);
    printUnifiedBlockLeft(returnBuf);
    
    // Now display with unified alignment
    resetUnifiedBlock();
    unified_blockFirstCall = 0;
    printUnifiedBlockLeft("=== Available Events ===");
    printUnifiedBlockLeft("");
    for (int i = 0; i < eventCount; i++) {
        char name[100], venue[100], date[20], time[20];
        int seatCapacity;
        if (sscanf(events[i], "%99[^|]|%99[^|]|%19[^|]|%19[^|]|%d", name, venue, date, time, &seatCapacity) == 5) {
            char buf[200];
            snprintf(buf, sizeof(buf), "%d. %s", i + 1, name);
            printUnifiedBlockLeft(buf);
        }
    }
    
    // Print the return option
    char returnBuf2[100];
    snprintf(returnBuf2, sizeof(returnBuf2), "%d. Return to main menu", eventCount + 1);
    printUnifiedBlockLeft(returnBuf2);

    // Get user's event selection
    int choice;
    char selectPrompt[100];
    snprintf(selectPrompt, sizeof(selectPrompt), "Enter event ID to view details: ");
    char buf_input[16];
    inputUnifiedBlock(selectPrompt, buf_input, sizeof(buf_input));
    if (sscanf(buf_input, "%d", &choice) != 1)
    {
        resetUnifiedBlock();
        printUnifiedBlockLeft("Invalid input.");
        printUnifiedBlockLeft("Press any key to continue...");
        getch();
        return;
    }
    if (choice < 1 || choice > eventCount + 1)
    {
        resetUnifiedBlock();
        printUnifiedBlockLeft("Invalid choice.");
        printUnifiedBlockLeft("Press any key to continue...");
        getch();
        return;
    }
    if (choice == eventCount + 1)
    {
        clear(); // Clear screen before returning to dashboard
        return;
    }

    // Show details for selected event
    clear();
    sscanf(events[choice - 1], "%99[^|]|%99[^|]|%19[^|]|%19[^|]|%d", name, venue, date, time, &seatCapacity);
    
    resetUnifiedBlock();
    printUnifiedBlockLeft("=== Event Details ===");
    printUnifiedBlockLeft("");
    
    char detail_buf[200];
    snprintf(detail_buf, sizeof(detail_buf), "Name: %s", name);
    printUnifiedBlockLeft(detail_buf);
    snprintf(detail_buf, sizeof(detail_buf), "Venue: %s", venue);
    printUnifiedBlockLeft(detail_buf);
    snprintf(detail_buf, sizeof(detail_buf), "Date (DD-MM-YYYY): %s", date);
    printUnifiedBlockLeft(detail_buf);
    snprintf(detail_buf, sizeof(detail_buf), "Time: %s", time);
    printUnifiedBlockLeft(detail_buf);
    snprintf(detail_buf, sizeof(detail_buf), "Seat Capacity: %d", seatCapacity);
    printUnifiedBlockLeft(detail_buf);
    printUnifiedBlockLeft("");
    
    // Show booking options
    printUnifiedBlockLeft("[B] Book this event");
    printUnifiedBlockLeft("[R] Return to list");
    printUnifiedBlockLeft("[M] Main menu");
    printUnifiedBlockLeft("");

    // Get user's action choice
    char action;
    char actionPrompt[50] = "Choose an option (B/R/M): ";
    char actionBuf[16];
    inputUnifiedBlock(actionPrompt, actionBuf, sizeof(actionBuf));
    
    if (strlen(actionBuf) > 0)
    {
        action = (actionBuf[0] >= 'a' && actionBuf[0] <= 'z') ? 
                 actionBuf[0] - 'a' + 'A' : actionBuf[0];
    }
    else
    {
        action = 'M'; // Default to main menu if no input
    }

    switch (action)
    {
    case 'B':
        // Book this event directly
        clear();
        bookSeatDirectly(choice);
        break;
    case 'R':
        // Return to event list
        clear();
        viewEventDetails(); // Recursive call to show list again
        break;
    case 'M':
    default:
        // Return to main menu
        clear();
        break;
    }
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
        printUnifiedBlockLeft("Invalid input for seat capacity.");
        printUnifiedBlockLeft("Press any key to continue...");
        getch();
        return;
    }

    FILE *file = fopen("events.txt", "a");
    if (file == NULL)
    {
        resetUnifiedBlock();
        printUnifiedBlockLeft("Error opening events file!");
        printUnifiedBlockLeft("Press any key to continue...");
        getch();
        return;
    }
    fprintf(file, "%s|%s|%s|%s|%d\n", name, venue, date, time, seatCapacity);
    fclose(file);
    
    resetUnifiedBlock();
    printUnifiedBlockLeft("Event added successfully!");
    printUnifiedBlockLeft("Press any key to continue...");
    getch();
    clear(); // Clear screen after adding event
}

void adminViewAllEvents()
{
    FILE *file = fopen("events.txt", "r");
    if (file == NULL)
    {
        resetUnifiedBlock();
        printUnifiedBlockLeft("No events found.");
        return;
    }

    char line[300], name[100], venue[100], date[20], time[20];
    int seatCapacity, newSeatCapacity;
    int eventCount = 0;
    char events[50][300]; // Store up to 50 events

    resetUnifiedBlock();
    printUnifiedBlockLeft("=== All Events ===");
    printUnifiedBlockLeft("");
    
    // Use unified block for event list
    resetUnifiedBlock();
    while (fgets(line, sizeof(line), file))
    {
        if (sscanf(line, "%99[^|]|%99[^|]|%19[^|]|%19[^|]|%d", name, venue, date, time, &seatCapacity) == 5)
        {
            eventCount++;
            strncpy(events[eventCount - 1], line, sizeof(events[eventCount - 1]) - 1);
            events[eventCount - 1][sizeof(events[eventCount - 1]) - 1] = '\0';
            char eventBuf[200];
            snprintf(eventBuf, sizeof(eventBuf), "%d. %s", eventCount, name);
            printUnifiedBlockLeft(eventBuf);
        }
    }
    fclose(file);
    char returnBuf[100];
    snprintf(returnBuf, sizeof(returnBuf), "%d. Return to admin menu", eventCount + 1);
    printUnifiedBlockLeft(returnBuf);
    
    // Second pass - actually print with proper alignment
    resetUnifiedBlock();
    unified_blockFirstCall = 0;  // Turn off first_call flag to trigger printing
    
    // Re-open file and print the event list again with proper alignment
    file = fopen("events.txt", "r");
    if (file != NULL) {
        eventCount = 0;
        while (fgets(line, sizeof(line), file))
        {
            if (sscanf(line, "%99[^|]|%99[^|]|%19[^|]|%19[^|]|%d", name, venue, date, time, &seatCapacity) == 5)
            {
                eventCount++;
                char eventBuf[200];
                snprintf(eventBuf, sizeof(eventBuf), "%d. %s", eventCount, name);
                printUnifiedBlockLeft(eventBuf);
            }
        }
        fclose(file);
        snprintf(returnBuf, sizeof(returnBuf), "%d. Return to admin menu", eventCount + 1);
        printUnifiedBlockLeft(returnBuf);
    }

    if (eventCount == 0)
        return;

    int choice;
    char selectPrompt[100];
    snprintf(selectPrompt, sizeof(selectPrompt), "Select an event to view/edit/delete or %d to return: ", eventCount + 1);
    char buf[16];
    inputUnifiedBlock(selectPrompt, buf, sizeof(buf));
    if (sscanf(buf, "%d", &choice) != 1)
    {
        resetUnifiedBlock();
        printUnifiedBlockLeft("Invalid input.");
        printUnifiedBlockLeft("Press any key to continue...");
        getch();
        return;
    }
    if (choice < 1 || choice > eventCount + 1)
    {
        resetUnifiedBlock();
        printUnifiedBlockLeft("Invalid choice.");
        printUnifiedBlockLeft("Press any key to continue...");
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
    printUnifiedBlockLeft("1. Edit Event");
    printUnifiedBlockLeft("2. Delete Event");
    printUnifiedBlockLeft("3. Return");
    
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
    printUnifiedBlockLeft("1. Edit Event");
    printUnifiedBlockLeft("2. Delete Event");
    printUnifiedBlockLeft("3. Return");
    
    int action;
    char buf2[16];
    inputUnifiedBlock("Select an option: ", buf2, sizeof(buf2));
    if (sscanf(buf2, "%d", &action) != 1)
    {
        resetUnifiedBlock();
        printUnifiedBlockLeft("Invalid input.");
        return;
    }

    if (action == 1)
    {
        // Edit event
        clear();
        char newName[100], newVenue[100], newDate[20], newTime[20];
        while (getchar() != '\n')
            ; // clear input buffer
        char promptName[150];
        snprintf(promptName, sizeof(promptName), "Enter new event name (or press Enter to keep '%s'): ", name);
        inputUnifiedBlock(promptName, newName, sizeof(newName));
        if (newName[0] == '\n')
            strcpy(newName, name);
        else
        {
            size_t l = strlen(newName);
            if (l > 0 && newName[l - 1] == '\n')
                newName[l - 1] = '\0';
        }

        char promptVenue[150];
        snprintf(promptVenue, sizeof(promptVenue), "Enter new venue (or press Enter to keep '%s'): ", venue);
        inputUnifiedBlock(promptVenue, newVenue, sizeof(newVenue));
        if (newVenue[0] == '\n')
            strcpy(newVenue, venue);
        else
        {
            size_t l = strlen(newVenue);
            if (l > 0 && newVenue[l - 1] == '\n')
                newVenue[l - 1] = '\0';
        }

        char promptDate[150];
        snprintf(promptDate, sizeof(promptDate), "Enter new date (DD-MM-YYYY) (or press Enter to keep '%s'): ", date);
        inputUnifiedBlock(promptDate, newDate, sizeof(newDate));
        if (newDate[0] == '\n')
            strcpy(newDate, date);
        else
        {
            size_t l = strlen(newDate);
            if (l > 0 && newDate[l - 1] == '\n')
                newDate[l - 1] = '\0';
        }

        char promptTime[150];
        snprintf(promptTime, sizeof(promptTime), "Enter new time (or press Enter to keep '%s'): ", time);
        inputUnifiedBlock(promptTime, newTime, sizeof(newTime));
        if (newTime[0] == '\n')
            strcpy(newTime, time);
        else
        {
            size_t l = strlen(newTime);
            if (l > 0 && newTime[l - 1] == '\n')
                newTime[l - 1] = '\0';
        }

        char promptSeat[100];
        snprintf(promptSeat, sizeof(promptSeat), "Enter new seat capacity (or 0 to keep %d): ", seatCapacity);
        char buf3[16];
        inputUnifiedBlock(promptSeat, buf3, sizeof(buf3));
        if (sscanf(buf3, "%d", &newSeatCapacity) != 1 || newSeatCapacity <= 0)
            newSeatCapacity = seatCapacity;

        // Update event in array
        snprintf(events[choice - 1], sizeof(events[choice - 1]), "%s|%s|%s|%s|%d\n", newName, newVenue, newDate, newTime, newSeatCapacity);
        
        resetUnifiedBlock();
        printUnifiedBlockLeft("Event updated successfully!");
        printUnifiedBlockLeft("Press any key to continue...");
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
        printUnifiedBlockLeft("Event deleted successfully!");
        printUnifiedBlockLeft("Press any key to continue...");
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
        printUnifiedBlockLeft("Error updating events file!");
        return;
    }
    for (int i = 0; i < eventCount; i++)
    {
        fputs(events[i], file);
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
        resetUnifiedBlock();
        printUnifiedBlockLeft("No users found.");
        printUnifiedBlockLeft("Press any key to continue...");
        getch();
        return;
    }

    char line[200];
    int ticketCode;
    char name[100];
    char users[100][200]; // Array to store user information
    int userCount = 0;

    // First pass: collect all user information
    while (fgets(line, sizeof(line), file) && userCount < 100)
    {
        if (sscanf(line, "%d,%99[^\n]", &ticketCode, name) == 2)
        {
            // Store user information
            strcpy(users[userCount], line);
            userCount++;
        }
    }
    fclose(file);
    
    resetUnifiedBlock();
    printUnifiedBlockLeft("=== All Registered Users ===");
    printUnifiedBlockLeft("");
    printUnifiedBlockLeft("Ticket Code | Name");
    printUnifiedBlockLeft("---------------------------");
    
    // First pass: collect all user data for alignment calculation
    for (int i = 0; i < userCount; i++)
    {
        if (sscanf(users[i], "%d,%99[^\n]", &ticketCode, name) == 2)
        {
            char buf[200];
            snprintf(buf, sizeof(buf), "    %04d    | %s", ticketCode, name);
            printUnifiedBlockLeft(buf);
        }
    }
    
    // Second pass: Actually print with alignment
    unified_blockFirstCall = 0; // Switch to printing mode
    
    printUnifiedBlockLeft("=== All Registered Users ===");
    printUnifiedBlockLeft("");
    printUnifiedBlockLeft("Ticket Code | Name");
    printUnifiedBlockLeft("---------------------------");
    // Print user data with proper alignment
    for (int i = 0; i < userCount; i++)
    {
        if (sscanf(users[i], "%d,%99[^\n]", &ticketCode, name) == 2)
        {
            char buf[200];
            snprintf(buf, sizeof(buf), "    %04d    | %s", ticketCode, name);
            printUnifiedBlockLeft(buf);
        }
    }
    
    // Print bottom border and total count
    printUnifiedBlockLeft("---------------------------");
    printUnifiedBlockLeft("");
    
    char totalMsg[50];
    snprintf(totalMsg, sizeof(totalMsg), "Total registered users: %d", userCount);
    printUnifiedBlockLeft(totalMsg);

    // Add prompt to continue
    char continueBuf[10];
    inputUnifiedBlock("Press Enter to continue...", continueBuf, sizeof(continueBuf));
    clear(); // Clear screen after viewing users
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
        resetUnifiedBlock();
        unified_blockFirstCall = 1;
        printUnifiedBlockLeft("Error: You must be logged in to view your bookings.");
        printUnifiedBlockLeft("Press any key to continue...");
        unified_blockFirstCall = 0;
        printUnifiedBlockLeft("Error: You must be logged in to view your bookings.");
        printUnifiedBlockLeft("Press any key to continue...");
        getch();
        return;
    }

    FILE *file = fopen(BOOKINGS_FILE, "r");
    if (file == NULL)
    {
        resetUnifiedBlock();
        unified_blockFirstCall = 1;
        printUnifiedBlockLeft("No bookings found.");
        printUnifiedBlockLeft("Press any key to continue...");
        unified_blockFirstCall = 0;
        printUnifiedBlockLeft("No bookings found.");
        printUnifiedBlockLeft("Press any key to continue...");
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
        resetUnifiedBlock();
        unified_blockFirstCall = 1;
        char buf[200];
        snprintf(buf, sizeof(buf), "No bookings found for %s.", loggedInUserName);
        printUnifiedBlockLeft(buf);
        printUnifiedBlockLeft("Press any key to continue...");
        unified_blockFirstCall = 0;
        printUnifiedBlockLeft(buf);
        printUnifiedBlockLeft("Press any key to continue...");
        getch();
        return;
    }
    
    // First pass: Calculate alignment
    unified_blockFirstCall = 1;
    resetUnifiedBlock();
    char headerBuf[200];
    snprintf(headerBuf, sizeof(headerBuf), "=== Your Bookings (%s) ===", loggedInUserName);
    printUnifiedBlockLeft(headerBuf);
    printUnifiedBlockLeft("");
    printUnifiedBlockLeft("Event ID | Event Name");
    printUnifiedBlockLeft("---------------------------");
    
    for (int i = 0; i < userBookingCount; i++)
    {
        if (sscanf(userBookings[i], "%d %[^\n]", &eventID, name) == 2)
        {
            char *eventName = getEventNameByID(eventID);
            char buf[300];
            snprintf(buf, sizeof(buf), "%d | %s", eventID, eventName);
            printUnifiedBlockLeft(buf);
        }
    }
    printUnifiedBlockLeft("---------------------------");
    
    // Second pass: Actually print with alignment
    unified_blockFirstCall = 0;
    
    printUnifiedBlockLeft(headerBuf);
    printUnifiedBlockLeft("");
    printUnifiedBlockLeft("Event ID | Event Name");
    printUnifiedBlockLeft("---------------------------");
    
    for (int i = 0; i < userBookingCount; i++)
    {
        if (sscanf(userBookings[i], "%d %[^\n]", &eventID, name) == 2)
        {
            char *eventName = getEventNameByID(eventID);
            char buf[300];
            snprintf(buf, sizeof(buf), "%d | %s", eventID, eventName);
            printUnifiedBlockLeft(buf);
        }
    }
    
    printUnifiedBlockLeft("---------------------------");

    // Add prompt to continue
    char continueBuf[10];
    inputUnifiedBlock("Press Enter to continue...", continueBuf, sizeof(continueBuf));
    clear();
}

void adminViewAllBookings()
{
    FILE *file = fopen(BOOKINGS_FILE, "r");
    if (file == NULL)
    {
        resetUnifiedBlock();
        unified_blockFirstCall = 1;
        printUnifiedBlockLeft("No bookings found.");
        printUnifiedBlockLeft("Press any key to continue...");
        unified_blockFirstCall = 0;
        printUnifiedBlockLeft("No bookings found.");
        printUnifiedBlockLeft("Press any key to continue...");
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
        resetUnifiedBlock();
        unified_blockFirstCall = 1;
        printUnifiedBlockLeft("No bookings found.");
        printUnifiedBlockLeft("Press any key to continue...");
        unified_blockFirstCall = 0;
        printUnifiedBlockLeft("No bookings found.");
        printUnifiedBlockLeft("Press any key to continue...");
        getch();
        return;
    }
    
    // First pass: Calculate alignment
    unified_blockFirstCall = 1;
    resetUnifiedBlock();
    printUnifiedBlockLeft("=== All Bookings (Admin View) ===");
    printUnifiedBlockLeft("");
    printUnifiedBlockLeft("Username - Event Name");
    printUnifiedBlockLeft("---------------------------");
    
    for (int i = 0; i < totalBookingCount; i++)
    {
        if (sscanf(allBookings[i], "%d %[^\n]", &eventID, name) == 2)
        {
            char *eventName = getEventNameByID(eventID);
            char buf[300];
            snprintf(buf, sizeof(buf), "%s - %s", name, eventName);
            printUnifiedBlockLeft(buf);
        }
    }
    printUnifiedBlockLeft("---------------------------");
    
    // Second pass: Actually print with alignment
    unified_blockFirstCall = 0;
    
    printUnifiedBlockLeft("=== All Bookings (Admin View) ===");
    printUnifiedBlockLeft("");
    printUnifiedBlockLeft("Username - Event Name");
    printUnifiedBlockLeft("---------------------------");
    
    for (int i = 0; i < totalBookingCount; i++)
    {
        if (sscanf(allBookings[i], "%d %[^\n]", &eventID, name) == 2)
        {
            char *eventName = getEventNameByID(eventID);
            char buf[300];
            snprintf(buf, sizeof(buf), "%s - %s", name, eventName);
            printUnifiedBlockLeft(buf);
        }
    }
    
    printUnifiedBlockLeft("---------------------------");

    // Add prompt to continue
    char continueBuf[10];
    inputUnifiedBlock("Press Enter to continue...", continueBuf, sizeof(continueBuf));
    clear();
}

void bookSeat()
{
    int eventID;
    
    // First pass: Calculate alignment for entire function
    unified_blockFirstCall = 1;
    resetUnifiedBlock();
    printUnifiedBlockLeft("-- Book a Seat --");
    
    // Check if user is logged in
    if (strlen(loggedInUserName) == 0)
    {
        printUnifiedBlockLeft("Error: You must be logged in to book a seat.");
        printUnifiedBlockLeft("Press any key to continue...");
        // Second pass: Display
        unified_blockFirstCall = 0;
        printUnifiedBlockLeft("-- Book a Seat --");
        printUnifiedBlockLeft("Error: You must be logged in to book a seat.");
        printUnifiedBlockLeft("Press any key to continue...");
        getch();
        return;
    }
    
    // Check if there are any events
    FILE *file = fopen("events.txt", "r");
    if (file == NULL)
    {
        printUnifiedBlockLeft("No events found.");
        printUnifiedBlockLeft("Press any key to continue...");
        // Second pass: Display
        unified_blockFirstCall = 0;
        printUnifiedBlockLeft("-- Book a Seat --");
        printUnifiedBlockLeft("No events found.");
        printUnifiedBlockLeft("Press any key to continue...");
        getch();
        return;
    }
    
    // Count and display events
    char line[300], eventName[100], venue[100], date[20], time[20];
    int seatCapacity;
    int eventCount = 0;
    char events[50][300]; // Store up to 50 events

    printUnifiedBlockLeft("-- Available Events --");
    
    // First pass - collect all event strings for alignment calculation
    while (fgets(line, sizeof(line), file))
    {
        if (sscanf(line, "%99[^|]|%99[^|]|%19[^|]|%19[^|]|%d", eventName, venue, date, time, &seatCapacity) == 5)
        {
            eventCount++;
            snprintf(events[eventCount - 1], sizeof(events[eventCount - 1]), "%s|%s|%s|%s|%d", eventName, venue, date, time, seatCapacity);
            char buf[200];
            snprintf(buf, sizeof(buf), "%d. %s", eventCount, eventName);
            printUnifiedBlockLeft(buf);
        }
    }
    fclose(file);
    
    if (eventCount == 0)
    {
        printUnifiedBlockLeft("No events found.");
        printUnifiedBlockLeft("Press any key to continue...");
        // Second pass: Display
        unified_blockFirstCall = 0;
        printUnifiedBlockLeft("-- Book a Seat --");
        printUnifiedBlockLeft("-- Available Events --");
        printUnifiedBlockLeft("No events found.");
        printUnifiedBlockLeft("Press any key to continue...");
        getch();
        return;
    }
    
    char buf[100];
    snprintf(buf, sizeof(buf), "%d. Return to main menu", eventCount + 1);
    printUnifiedBlockLeft(buf);
    
    // Second pass - actually print with proper alignment
    unified_blockFirstCall = 0;
    
    printUnifiedBlockLeft("-- Book a Seat --");
    printUnifiedBlockLeft("-- Available Events --");
    
    // Print the event list with proper alignment
    for (int i = 0; i < eventCount; i++) {
        char name[100], venue[100], date[20], time[20];
        int seatCapacity;
        if (sscanf(events[i], "%99[^|]|%99[^|]|%19[^|]|%19[^|]|%d", name, venue, date, time, &seatCapacity) == 5) {
            char buf[200];
            snprintf(buf, sizeof(buf), "%d. %s", i + 1, name);
            printUnifiedBlockLeft(buf);
        }
    }
    
    // Print the return option
    snprintf(buf, sizeof(buf), "%d. Return to main menu", eventCount + 1);
    printUnifiedBlockLeft(buf);

    // Get event ID to book
    char promptBuf[100];
    snprintf(promptBuf, sizeof(promptBuf), "Enter event ID to book: ");
    char buf2[16];
    inputUnifiedBlock(promptBuf, buf2, sizeof(buf2));
    if (sscanf(buf2, "%d", &eventID) != 1)
    {
        resetUnifiedBlock();
        unified_blockFirstCall = 1;
        printUnifiedBlockLeft("Invalid input for Event ID.");
        printUnifiedBlockLeft("Press any key to continue...");
        unified_blockFirstCall = 0;
        printUnifiedBlockLeft("Invalid input for Event ID.");
        printUnifiedBlockLeft("Press any key to continue...");
        getch();
        return;
    }

    if (eventID < 1 || eventID > eventCount + 1)
    {
        resetUnifiedBlock();
        unified_blockFirstCall = 1;
        printUnifiedBlockLeft("Invalid Event ID");
        printUnifiedBlockLeft("Press any key to continue...");
        unified_blockFirstCall = 0;
        printUnifiedBlockLeft("Invalid Event ID");
        printUnifiedBlockLeft("Press any key to continue...");
        getch();
        return;
    }
    
    if (eventID == eventCount + 1)
    {
        clear(); // Return to main menu
        return;
    }

    // Use the logged-in user's name automatically (no need to ask again)
    // Save the booking
    saveBooking(eventID, loggedInUserName);

    // Show confirmation with booking details
    clear();
    resetUnifiedBlock();
    unified_blockFirstCall = 1;
    printUnifiedBlockLeft("--- Booking Confirmation ---");
    printUnifiedBlockLeft("");
    snprintf(buf, sizeof(buf), "Seat booked successfully for %s", loggedInUserName);
    printUnifiedBlockLeft(buf);
    snprintf(buf, sizeof(buf), "Event ID: %d", eventID);
    printUnifiedBlockLeft(buf);
    
    // Show event name from the stored events
    sscanf(events[eventID - 1], "%99[^|]|%99[^|]|%19[^|]|%19[^|]|%d", eventName, venue, date, time, &seatCapacity);
    snprintf(buf, sizeof(buf), "Event: %s", eventName);
    printUnifiedBlockLeft(buf);
    printUnifiedBlockLeft("");

    // Second pass: Display confirmation
    unified_blockFirstCall = 0;
    printUnifiedBlockLeft("--- Booking Confirmation ---");
    printUnifiedBlockLeft("");
    snprintf(buf, sizeof(buf), "Seat booked successfully for %s", loggedInUserName);
    printUnifiedBlockLeft(buf);
    snprintf(buf, sizeof(buf), "Event ID: %d", eventID);
    printUnifiedBlockLeft(buf);
    snprintf(buf, sizeof(buf), "Event: %s", eventName);
    printUnifiedBlockLeft(buf);
    printUnifiedBlockLeft("");

    // Add prompt to continue
    char continueBuf[10];
    inputUnifiedBlock("Press Enter to continue...", continueBuf, sizeof(continueBuf));
    clear(); // Clear screen after booking confirmation
}

void bookSeatDirectly(int eventID)
{
    // First pass: Calculate alignment
    unified_blockFirstCall = 1;
    resetUnifiedBlock();
    
    if (strlen(loggedInUserName) == 0)
    {
        printUnifiedBlockLeft("Error: You must be logged in to book a seat.");
        printUnifiedBlockLeft("Press any key to continue...");
        // Second pass: Display
        unified_blockFirstCall = 0;
        printUnifiedBlockLeft("Error: You must be logged in to book a seat.");
        printUnifiedBlockLeft("Press any key to continue...");
        getch();
        return;
    }

    // Validate event ID exists
    FILE *file = fopen("events.txt", "r");
    if (file == NULL)
    {
        printUnifiedBlockLeft("No events found.");
        printUnifiedBlockLeft("Press any key to continue...");
        // Second pass: Display
        unified_blockFirstCall = 0;
        printUnifiedBlockLeft("No events found.");
        printUnifiedBlockLeft("Press any key to continue...");
        getch();
        return;
    }
    
    // Count total events to validate eventID
    int eventCount = 0;
    char line[300];
    while (fgets(line, sizeof(line), file))
    {
        eventCount++;
    }
    fclose(file);
    
    if (eventID < 1 || eventID > eventCount)
    {
        printUnifiedBlockLeft("Invalid Event ID");
        printUnifiedBlockLeft("Press any key to continue...");
        // Second pass: Display
        unified_blockFirstCall = 0;
        printUnifiedBlockLeft("Invalid Event ID");
        printUnifiedBlockLeft("Press any key to continue...");
        getch();
        return;
    }

    printUnifiedBlockLeft("-- Book a Seat --");
    printUnifiedBlockLeft("");
    
    // Display confirmation message showing the logged-in user
    char userMsg[200];
    snprintf(userMsg, sizeof(userMsg), "Booking seat for: %s", loggedInUserName);
    printUnifiedBlockLeft(userMsg);
    printUnifiedBlockLeft("");

    // Show confirmation
    char buf[200];
    snprintf(buf, sizeof(buf), "Seat booked successfully for %s at event ID %d.", loggedInUserName, eventID);
    printUnifiedBlockLeft("--- Booking Confirmation ---");
    printUnifiedBlockLeft(buf);
    printUnifiedBlockLeft("");

    // Second pass: Display everything
    unified_blockFirstCall = 0;
    printUnifiedBlockLeft("-- Book a Seat --");
    printUnifiedBlockLeft("");
    printUnifiedBlockLeft(userMsg);
    printUnifiedBlockLeft("");

    // Save the booking using the logged-in user's name
    saveBooking(eventID, loggedInUserName);

    printUnifiedBlockLeft("--- Booking Confirmation ---");
    printUnifiedBlockLeft(buf);
    printUnifiedBlockLeft("");

    // Add prompt to continue
    char continueBuf[10];
    inputUnifiedBlock("Press Enter to continue...", continueBuf, sizeof(continueBuf));
    clear(); // Clear screen after booking confirmation
}

void cancelBooking()
{
    int eventID;

    // Check if user is logged in
    if (strlen(loggedInUserName) == 0)
    {
        resetUnifiedBlock();
        unified_blockFirstCall = 1;
        printUnifiedBlockLeft("Error: You must be logged in to cancel a booking.");
        printUnifiedBlockLeft("Press any key to continue...");
        unified_blockFirstCall = 0;
        printUnifiedBlockLeft("Error: You must be logged in to cancel a booking.");
        printUnifiedBlockLeft("Press any key to continue...");
        getch();
        return;
    }

    // First, show user's current bookings
    FILE *file = fopen(BOOKINGS_FILE, "r");
    if (file == NULL)
    {
        resetUnifiedBlock();
        unified_blockFirstCall = 1;
        printUnifiedBlockLeft("No bookings found to cancel.");
        printUnifiedBlockLeft("Press any key to continue...");
        unified_blockFirstCall = 0;
        printUnifiedBlockLeft("No bookings found to cancel.");
        printUnifiedBlockLeft("Press any key to continue...");
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
        resetUnifiedBlock();
        unified_blockFirstCall = 1;
        char buf[200];
        snprintf(buf, sizeof(buf), "No bookings found for %s to cancel.", loggedInUserName);
        printUnifiedBlockLeft(buf);
        printUnifiedBlockLeft("Press any key to continue...");
        unified_blockFirstCall = 0;
        printUnifiedBlockLeft(buf);
        printUnifiedBlockLeft("Press any key to continue...");
        getch();
        return;
    }
    
    // First pass: Calculate alignment for displaying bookings
    unified_blockFirstCall = 1;
    resetUnifiedBlock();
    printUnifiedBlockLeft("-- Cancel Booking --");
    char headerBuf[200];
    snprintf(headerBuf, sizeof(headerBuf), "Your Current Bookings (%s):", loggedInUserName);
    printUnifiedBlockLeft(headerBuf);
    printUnifiedBlockLeft("");
    printUnifiedBlockLeft("Event ID | Event Name");
    printUnifiedBlockLeft("---------------------------");
    
    for (int i = 0; i < userBookingCount; i++)
    {
        if (sscanf(userBookings[i], "%d %[^\n]", &eventInLine, nameInLine) == 2)
        {
            char *eventName = getEventNameByID(eventInLine);
            char buf[300];
            snprintf(buf, sizeof(buf), "%d | %s", eventInLine, eventName);
            printUnifiedBlockLeft(buf);
        }
    }
    printUnifiedBlockLeft("---------------------------");
    printUnifiedBlockLeft("");
    
    // Second pass: Actually display the bookings
    unified_blockFirstCall = 0;
    printUnifiedBlockLeft("-- Cancel Booking --");
    printUnifiedBlockLeft(headerBuf);
    printUnifiedBlockLeft("");
    printUnifiedBlockLeft("Event ID | Event Name");
    printUnifiedBlockLeft("---------------------------");
    
    for (int i = 0; i < userBookingCount; i++)
    {
        if (sscanf(userBookings[i], "%d %[^\n]", &eventInLine, nameInLine) == 2)
        {
            char *eventName = getEventNameByID(eventInLine);
            char buf[300];
            snprintf(buf, sizeof(buf), "%d | %s", eventInLine, eventName);
            printUnifiedBlockLeft(buf);
        }
    }
    printUnifiedBlockLeft("---------------------------");
    printUnifiedBlockLeft("");

    // Now ask for the event ID to cancel
    char buf[16];
    inputUnifiedBlock("Enter Event ID to cancel: ", buf, sizeof(buf));
    if (sscanf(buf, "%d", &eventID) != 1)
    {
        resetUnifiedBlock();
        unified_blockFirstCall = 1;
        printUnifiedBlockLeft("Invalid input for Event ID.");
        printUnifiedBlockLeft("Press any key to continue...");
        unified_blockFirstCall = 0;
        printUnifiedBlockLeft("Invalid input for Event ID.");
        printUnifiedBlockLeft("Press any key to continue...");
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
        resetUnifiedBlock();
        unified_blockFirstCall = 1;
        printUnifiedBlockLeft("Error opening file, Name of event ID not Found!");
        unified_blockFirstCall = 0;
        printUnifiedBlockLeft("Error opening file, Name of event ID not Found!");
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
        resetUnifiedBlock();
        unified_blockFirstCall = 1;
        printUnifiedBlockLeft("Error opening file!");
        unified_blockFirstCall = 0;
        printUnifiedBlockLeft("Error opening file!");
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
        resetUnifiedBlock();
        unified_blockFirstCall = 1;
        printUnifiedBlockLeft("Booking successfully canceled.");
        unified_blockFirstCall = 0;
        printUnifiedBlockLeft("Booking successfully canceled.");
    }
    else
    {
        remove("temp.txt");
        char buf[200];
        snprintf(buf, sizeof(buf), "No booking found for %s at event ID %d.", name, eventID);
        resetUnifiedBlock();
        unified_blockFirstCall = 1;
        printUnifiedBlockLeft(buf);
        unified_blockFirstCall = 0;
        printUnifiedBlockLeft(buf);
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
