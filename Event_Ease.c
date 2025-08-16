#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#define BOOKINGS_FILE "bookings.txt"
#define USER_INFO_FILE "user_info.txt"

/* ===================== Function Declarations ===================== */
// UI and Display Functions
void clear();
void welcomePage();
void dashboardDesign();
void printCentered(const char *str);
void inputCentered(const char *prompt, char *buffer, int size);

// New unified positioning system
int getConsoleWidth();
int calculateCenterPosition(int contentWidth);
void printUnified(const char *str);
void inputUnified(const char *prompt, char *buffer, int size);
void inputUnifiedBlock(const char *prompt, char *buffer, int size);
void printUnifiedBlock(const char *str);
void resetUnifiedBlock();

// Landing Page and Authentication Functions
void landingPage();
void newUserRegistration();
void existingUserLogin();
void adminLogin();
int generateUniqueTicketCode();
int isTicketCodeExists(int ticketCode);
int isNameExists(const char *name);
void saveUserInfo(int ticketCode, const char *name);
int validateUserLogin(const char *name, int ticketCode);

// Core Navigation Functions
void userDashboard();
void adminDashboard();

// Event Management Functions
void viewEvents();
void addEvent();
void adminViewAllEvents();
void viewAllUsers();

// Booking Management Functions
void bookSeat();
void cancelBooking();
void saveBooking(int eventID, const char *name);
void removeBooking(int eventID, const char *name);
void viewAllBookings();

/* ===================== Main Function ===================== */
int main()
{
    system("chcp 65001");
    
    // Remove any existing conflicting files
    remove("bookings.txt");
    
    // Initialize random seed for ticket code generation
    srand((unsigned int)time(NULL));
    
    landingPage();
    return 0;
}

/* ===================== UI Functions ===================== */
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
    // Move cursor right after prompt
    pos.X += promptLen;
    SetConsoleCursorPosition(hConsole, pos);
    fgets(buffer, size, stdin);
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n')
        buffer[len - 1] = '\0';
}

void welcomePage()
{
    // Compact ASCII art organized in logical sections
    const char *art[] = {
        // Top decoration (14 lines)
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
        // EVENT text (10 lines)
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
        // EASE text (11 lines)
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

    // Set light green color
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

    // Optimized rendering loop
    for (int i = 0; i < 35; i++) {
        for (const char *p = art[i]; *p; p++) {
            putchar(*p); putchar(*p); // stretch horizontally
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

    // Cyan = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY
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

/* ===================== Unified Positioning System ===================== */

// Global variables for unified positioning
static int unified_blockMaxLen = 0;
static int unified_blockStartPos = -1;
static int unified_blockFirstCall = 1;

/**
 * Get current console width
 */
int getConsoleWidth()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (GetConsoleScreenBufferInfo(hConsole, &csbi))
        return csbi.srWindow.Right - csbi.srWindow.Left + 1;
    return 80; // default width
}

/**
 * Calculate center position for given content width
 */
int calculateCenterPosition(int contentWidth)
{
    int consoleWidth = getConsoleWidth();
    int centerPos = (consoleWidth - contentWidth) / 2;
    return (centerPos < 0) ? 0 : centerPos;
}

/**
 * Print text centered on console
 */
void printUnified(const char *str)
{
    int len = (int)strlen(str);
    int pad = calculateCenterPosition(len);
    
    for (int i = 0; i < pad; i++)
        putchar(' ');
    printf("%s\n", str);
}

/**
 * Input with unified positioning (matches printUnified alignment)
 */
void inputUnified(const char *prompt, char *buffer, int size)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    
    int promptLen = (int)strlen(prompt);
    int totalLen = promptLen + size;
    int pad = calculateCenterPosition(totalLen);
    
    // Position cursor at calculated center position
    COORD pos = csbi.dwCursorPosition;
    pos.X = pad;
    SetConsoleCursorPosition(hConsole, pos);
    
    printf("%s", prompt);
    fflush(stdout);
    
    // Move cursor right after prompt
    pos.X += promptLen;
    SetConsoleCursorPosition(hConsole, pos);
    
    fgets(buffer, size, stdin);
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n')
        buffer[len - 1] = '\0';
}

/**
 * Input function that aligns with unified block positioning
 */
void inputUnifiedBlock(const char *prompt, char *buffer, int size)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    
    // Use the same positioning as unified block
    int promptLen = (int)strlen(prompt);
    int pad = unified_blockStartPos; // Use the same position as the block
    
    if (pad == -1) {
        // If block position not set, calculate manually
        pad = calculateCenterPosition(promptLen + size);
    }
    
    // Position cursor at the block's starting position
    COORD pos = csbi.dwCursorPosition;
    pos.X = pad;
    SetConsoleCursorPosition(hConsole, pos);
    
    printf("%s", prompt);
    fflush(stdout);
    
    // Move cursor right after prompt
    pos.X += promptLen;
    SetConsoleCursorPosition(hConsole, pos);
    
    fgets(buffer, size, stdin);
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n')
        buffer[len - 1] = '\0';
}

/**
 * Reset unified block formatting
 */
void resetUnifiedBlock()
{
    unified_blockMaxLen = 0;
    unified_blockStartPos = -1;
    unified_blockFirstCall = 1;
}

/**
 * Print text in a unified left-aligned block (centered as a group)
 */
void printUnifiedBlock(const char *str)
{
    int currentLen = (int)strlen(str);
    
    // First call after reset - measure all strings
    if (unified_blockFirstCall) {
        // Track all strings to find the maximum length
        if (currentLen > unified_blockMaxLen) {
            unified_blockMaxLen = currentLen;
        }
        return; // Don't print during measuring phase
    }
    
    // Calculate the starting position (centered block) - only once
    if (unified_blockStartPos == -1) {
        unified_blockStartPos = calculateCenterPosition(unified_blockMaxLen);
    }
    
    // Print spaces to the starting position
    for (int i = 0; i < unified_blockStartPos; i++) {
        putchar(' ');
    }
    
    // Print the string
    printf("%s\n", str);
}

/* ===================== Landing Page and Authentication Functions ===================== */

/**
 * Main landing page - displays welcome screen and user options
 */
void landingPage()
{
    int choice;
    
    while (1)
    {
        clear();
        welcomePage();
        
        // Use unified block for ALL elements to ensure perfect alignment
        resetUnifiedBlock();
        printUnifiedBlock("Welcome to Event-Ease!");
        printUnifiedBlock("=====================");
        printUnifiedBlock("");
        printUnifiedBlock("1. New User Registration");
        printUnifiedBlock("2. Existing User Login");
        printUnifiedBlock("3. Admin Login");
        printUnifiedBlock("0. Exit");
        
        // Second pass to actually print with alignment
        resetUnifiedBlock();
        unified_blockFirstCall = 0;
        
        printUnifiedBlock("Welcome to Event-Ease!");
        printUnifiedBlock("=====================");
        printUnifiedBlock("");
        printUnifiedBlock("1. New User Registration");
        printUnifiedBlock("2. Existing User Login");
        printUnifiedBlock("3. Admin Login");
        printUnifiedBlock("0. Exit");
        
        char buf[16];
        inputUnifiedBlock("Select an option: ", buf, sizeof(buf));
        if (sscanf(buf, "%d", &choice) != 1)
        {
            resetUnifiedBlock();
            printUnifiedBlock("Invalid input. Please enter a number.");
            printUnifiedBlock("Press any key to continue...");
            
            resetUnifiedBlock();
            unified_blockFirstCall = 0;
            printUnifiedBlock("Invalid input. Please enter a number.");
            printUnifiedBlock("Press any key to continue...");
            
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
            printUnifiedBlock("Invalid choice. Please select again.");
            printUnifiedBlock("Press any key to continue...");
            
            resetUnifiedBlock();
            unified_blockFirstCall = 0;
            printUnifiedBlock("Invalid choice. Please select again.");
            printUnifiedBlock("Press any key to continue...");
            
            getch();
        }
    }
}

/**
 * New user registration - generates unique ticket code and saves user info
 */
void newUserRegistration()
{
    char name[100];
    int ticketCode;
    
    // Use unified block for header to ensure alignment with content
    resetUnifiedBlock();
    printUnifiedBlock("=== New User Registration ===");
    printUnifiedBlock("");
    printUnifiedBlock("Enter your name: ");
    
    // Calculate the unified block position first
    resetUnifiedBlock();
    unified_blockFirstCall = 0;
    printUnifiedBlock("=== New User Registration ===");
    printUnifiedBlock("");
    
    // Get user name with validation
    while (1)
    {
        // Position the input at the same location as the block
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
            printUnifiedBlock("Name cannot be empty. Please enter a valid name.");
            
            resetUnifiedBlock();
            unified_blockFirstCall = 0;
            printUnifiedBlock("Name cannot be empty. Please enter a valid name.");
            
            printUnified("Press any key to try again...");
            getch();
            clear(); // Clear screen before asking for new name
            
            // Redisplay the registration header
            resetUnifiedBlock();
            printUnifiedBlock("=== New User Registration ===");
            printUnifiedBlock("");
            printUnifiedBlock("Enter your name: ");
            
            // Calculate the unified block position first
            resetUnifiedBlock();
            unified_blockFirstCall = 0;
            printUnifiedBlock("=== New User Registration ===");
            printUnifiedBlock("");
            
            continue;
        }
        
        // Check if name already exists
        if (isNameExists(name))
        {
            // Use unified block for error messages
            resetUnifiedBlock();
            printUnifiedBlock("This name is already registered!");
            printUnifiedBlock("Please choose a different name.");
            
            resetUnifiedBlock();
            unified_blockFirstCall = 0;
            printUnifiedBlock("This name is already registered!");
            printUnifiedBlock("Please choose a different name.");
            
            printUnified("Press any key to try again...");
            getch();
            clear(); // Clear screen before asking for new name
            
            // Redisplay the registration header
            resetUnifiedBlock();
            printUnifiedBlock("=== New User Registration ===");
            printUnifiedBlock("");
            printUnifiedBlock("Enter your name: ");
            
            // Calculate the unified block position first
            resetUnifiedBlock();
            unified_blockFirstCall = 0;
            printUnifiedBlock("=== New User Registration ===");
            printUnifiedBlock("");
            
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
        printUnifiedBlock("Error: Unable to generate unique ticket code.");
        printUnifiedBlock("Please try again later.");
        printUnifiedBlock("Press any key to continue...");
        
        resetUnifiedBlock();
        unified_blockFirstCall = 0;
        printUnifiedBlock("Error: Unable to generate unique ticket code.");
        printUnifiedBlock("Please try again later.");
        printUnifiedBlock("Press any key to continue...");
        
        getch();
        return;
    }
    
    // Save user information
    saveUserInfo(ticketCode, name);
    
    // Display registration success using unified block system
    resetUnifiedBlock();
    printUnifiedBlock("Registration Successful!");
    printUnifiedBlock("========================");
    printUnifiedBlock("");
    char ticketMsg[100];
    snprintf(ticketMsg, sizeof(ticketMsg), "Your ticket code is: %04d", ticketCode);
    printUnifiedBlock(ticketMsg);
    printUnifiedBlock("Please remember your ticket code for future logins.");
    printUnifiedBlock("");
    printUnifiedBlock("Press any key to continue to your dashboard...");
    
    // Second pass to actually print with alignment
    resetUnifiedBlock();
    unified_blockFirstCall = 0;
    printUnifiedBlock("Registration Successful!");
    printUnifiedBlock("========================");
    printUnifiedBlock("");
    printUnifiedBlock(ticketMsg);
    printUnifiedBlock("Please remember your ticket code for future logins.");
    printUnifiedBlock("");
    printUnifiedBlock("Press any key to continue to your dashboard...");
    
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
    printUnifiedBlock("=== User Login ===");
    printUnifiedBlock("");
    printUnifiedBlock("Enter your name: ");
    printUnifiedBlock("Enter your 4-digit ticket code: ");
    
    // Calculate the unified block position first
    resetUnifiedBlock();
    unified_blockFirstCall = 0;
    printUnifiedBlock("=== User Login ===");
    printUnifiedBlock("");
    
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
        printUnifiedBlock("Invalid ticket code format. Please enter a 4-digit number.");
        printUnifiedBlock("Press any key to continue...");
        
        resetUnifiedBlock();
        unified_blockFirstCall = 0;
        printUnifiedBlock("Invalid ticket code format. Please enter a 4-digit number.");
        printUnifiedBlock("Press any key to continue...");
        
        getch();
        return;
    }
    
    // Validate ticket code range
    if (ticketCode < 0 || ticketCode > 9999)
    {
        // Use unified block for error messages
        resetUnifiedBlock();
        printUnifiedBlock("Invalid ticket code. Must be between 0000-9999.");
        printUnifiedBlock("Press any key to continue...");
        
        resetUnifiedBlock();
        unified_blockFirstCall = 0;
        printUnifiedBlock("Invalid ticket code. Must be between 0000-9999.");
        printUnifiedBlock("Press any key to continue...");
        
        getch();
        return;
    }
    
    // Validate user login
    if (validateUserLogin(name, ticketCode))
    {
        // Use unified block for success messages
        resetUnifiedBlock();
        printUnifiedBlock("Login successful!");
        printUnifiedBlock("Welcome back!");
        printUnifiedBlock("Press any key to continue to your dashboard...");
        
        resetUnifiedBlock();
        unified_blockFirstCall = 0;
        printUnifiedBlock("Login successful!");
        printUnifiedBlock("Welcome back!");
        printUnifiedBlock("Press any key to continue to your dashboard...");
        
        getch();
        
        clear();
        userDashboard();
    }
    else
    {
        // Use unified block for error messages
        resetUnifiedBlock();
        printUnifiedBlock("Invalid credentials. Name or ticket code does not match.");
        printUnifiedBlock("Please check your information and try again.");
        printUnifiedBlock("Press any key to continue...");
        
        resetUnifiedBlock();
        unified_blockFirstCall = 0;
        printUnifiedBlock("Invalid credentials. Name or ticket code does not match.");
        printUnifiedBlock("Please check your information and try again.");
        printUnifiedBlock("Press any key to continue...");
        
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
    printUnifiedBlock("=== Admin Login ===");
    printUnifiedBlock("");
    printUnifiedBlock("Username: ");
    printUnifiedBlock("Password: ");
    
    // Calculate the unified block position first
    resetUnifiedBlock();
    unified_blockFirstCall = 0;
    printUnifiedBlock("=== Admin Login ===");
    printUnifiedBlock("");
    
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
    
    // Get password
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    pos = csbi.dwCursorPosition;
    pos.X = unified_blockStartPos;
    SetConsoleCursorPosition(hConsole, pos);
    printf("Password: ");
    fflush(stdout);
    pos.X += strlen("Password: ");
    SetConsoleCursorPosition(hConsole, pos);
    fgets(password, sizeof(password), stdin);
    len = strlen(password);
    if (len > 0 && password[len - 1] == '\n')
        password[len - 1] = '\0';
    
    // Check hardcoded admin credentials
    if (strcmp(username, "admin") == 0 && strcmp(password, "password") == 0)
    {
        // Use unified block for success messages
        resetUnifiedBlock();
        printUnifiedBlock("Admin login successful!");
        printUnifiedBlock("Access granted to admin panel.");
        printUnifiedBlock("Press any key to continue...");
        
        resetUnifiedBlock();
        unified_blockFirstCall = 0;
        printUnifiedBlock("Admin login successful!");
        printUnifiedBlock("Access granted to admin panel.");
        printUnifiedBlock("Press any key to continue...");
        
        getch();
        
        clear();
        adminDashboard();
    }
    else
    {
        // Use unified block for error messages
        resetUnifiedBlock();
        printUnifiedBlock("Invalid admin credentials.");
        printUnifiedBlock("Access denied.");
        printUnifiedBlock("Press any key to continue...");
        
        resetUnifiedBlock();
        unified_blockFirstCall = 0;
        printUnifiedBlock("Invalid admin credentials.");
        printUnifiedBlock("Access denied.");
        printUnifiedBlock("Press any key to continue...");
        
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
            // Case-insensitive comparison for names
            if (strcasecmp(existingName, name) == 0)
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
        printCentered("Error: Unable to save user information.");
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

/* ===================== Core Navigation Functions ===================== */

/**
 * User dashboard - main menu for registered users
 */
void userDashboard()
{
    int choice;

    while (1)
    {
        dashboardDesign();
        
        // Use unified block for menu items - first pass to collect strings
        resetUnifiedBlock();
        printUnifiedBlock("1. View Events");
        printUnifiedBlock("2. Book Seat");
        printUnifiedBlock("3. Cancel Booking");
        printUnifiedBlock("4. View All Bookings");
        printUnifiedBlock("5. Logout");
        printUnifiedBlock("0. Exit");
        
        // Second pass to actually print with alignment
        resetUnifiedBlock();
        unified_blockFirstCall = 0;     // Turn off first_call flag to trigger printing
        
        // Print the same strings again, now they'll be properly aligned
        printUnifiedBlock("1. View Events");
        printUnifiedBlock("2. Book Seat");
        printUnifiedBlock("3. Cancel Booking");
        printUnifiedBlock("4. View All Bookings");
        printUnifiedBlock("5. Logout");
        printUnifiedBlock("0. Exit");
        
        char buf[16];
        inputCentered("Select an option: ", buf, sizeof(buf));
        if (sscanf(buf, "%d", &choice) != 1)
        {
            printCentered("Invalid input. Please enter a number.");
            printCentered("Press any key to continue...");
            getch();
            continue;
        }

        switch (choice)
        {
        case 1:
            clear();
            viewEvents();
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
            printCentered("Logging out...");
            return; // Return to landing page
        case 0:
            clear();
            printCentered("Thank you for using Event-Ease!");
            exit(0);
        default:
            clear();
            printCentered("Invalid choice. Please select again.");
            printCentered("Press any key to continue...");
            getch();
        }
    }
}

/**
 * Admin dashboard - main menu for administrators
 */
void adminDashboard()
{
    int choice;
    while (1)
    {
        dashboardDesign();
        
        // Use unified block for menu items - first pass to collect strings
        resetUnifiedBlock();
        printUnifiedBlock("1. View all bookings");
        printUnifiedBlock("2. Add Event");
        printUnifiedBlock("3. View All Events");
        printUnifiedBlock("4. View All Users");
        printUnifiedBlock("5. Logout");
        printUnifiedBlock("0. Exit");
        
        // Second pass to actually print with alignment
        resetUnifiedBlock();
        unified_blockFirstCall = 0;     // Turn off first_call flag to trigger printing
        
        // Print the same strings again, now they'll be properly aligned
        printUnifiedBlock("1. View all bookings");
        printUnifiedBlock("2. Add Event");
        printUnifiedBlock("3. View All Events");
        printUnifiedBlock("4. View All Users");
        printUnifiedBlock("5. Logout");
        printUnifiedBlock("0. Exit");
        
        char buf[16];
        inputCentered("Select an option: ", buf, sizeof(buf));
        if (sscanf(buf, "%d", &choice) != 1)
        {
            printCentered("Invalid input. Please enter a number.");
            printCentered("Press any key to continue...");
            getch();
            continue;
        }

        switch (choice)
        {
        case 1:
            clear();
            viewAllBookings();
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
            printCentered("Logging out of admin panel...");
            return; // Return to landing page
        case 0:
            clear();
            printCentered("Thank you for using Event-Ease!");
            exit(0);
        default:
            clear();
            printCentered("Invalid choice. Please select again.");
            printCentered("Press any key to continue...");
            getch();
        }
    }
}
/* ===================== Event Management Functions ===================== */
void viewEvents()
{
    FILE *file = fopen("events.txt", "r");
    if (file == NULL)
    {
        printCentered("No events found.");
        return;
    }

    char line[300], name[100], venue[100], date[20], time[20];
    int seatCapacity;
    int eventCount = 0;
    char events[50][300]; // Store up to 50 events

    printCentered("-- Available Events --");
    
    // First pass - collect all event strings
    resetUnifiedBlock();
    while (fgets(line, sizeof(line), file))
    {
        if (sscanf(line, "%99[^|]|%99[^|]|%19[^|]|%19[^|]|%d", name, venue, date, time, &seatCapacity) == 5)
        {
            eventCount++;
            snprintf(events[eventCount - 1], sizeof(events[eventCount - 1]), "%s|%s|%s|%s|%d", name, venue, date, time, seatCapacity);
            char buf[200];
            snprintf(buf, sizeof(buf), "%d. %s", eventCount, name);
            printUnifiedBlock(buf);
        }
    }
    fclose(file);
    char buf[100];
    snprintf(buf, sizeof(buf), "%d. Return to main menu", eventCount + 1);
    printUnifiedBlock(buf);
    
    // Second pass - actually print with proper alignment
    resetUnifiedBlock();
    unified_blockFirstCall = 0;  // Turn off first_call flag to trigger printing
    
    // Print the event list again with proper alignment
    for (int i = 0; i < eventCount; i++) {
        char name[100], venue[100], date[20], time[20];
        int seatCapacity;
        if (sscanf(events[i], "%99[^|]|%99[^|]|%19[^|]|%19[^|]|%d", name, venue, date, time, &seatCapacity) == 5) {
            char buf[200];
            snprintf(buf, sizeof(buf), "%d. %s", i + 1, name);
            printUnifiedBlock(buf);
        }
    }
    
    // Print the return option
    snprintf(buf, sizeof(buf), "%d. Return to main menu", eventCount + 1);
    printUnifiedBlock(buf);

    if (eventCount == 0)
        return;

    int choice;
    char selectPrompt[100];
    snprintf(selectPrompt, sizeof(selectPrompt), "Select an event to view details or %d to return: ", eventCount + 1);
    char buf_input[16];
    inputCentered(selectPrompt, buf_input, sizeof(buf_input));
    if (sscanf(buf_input, "%d", &choice) != 1)
    {
        printCentered("Invalid input.");
        return;
    }
    if (choice < 1 || choice > eventCount + 1)
    {
        printCentered("Invalid choice.");
        return;
    }
    if (choice == eventCount + 1)
    {
        clear(); // Clear screen before returning to dashboard
        return;
    }

    // Show details for selected event
    sscanf(events[choice - 1], "%99[^|]|%99[^|]|%19[^|]|%19[^|]|%d", name, venue, date, time, &seatCapacity);
    printCentered("\n--- Event Details ---");
    
    char detail_buf[200];
    snprintf(detail_buf, sizeof(detail_buf), "Name: %s", name);
    printCentered(detail_buf);
    snprintf(detail_buf, sizeof(detail_buf), "Venue: %s", venue);
    printCentered(detail_buf);
    snprintf(detail_buf, sizeof(detail_buf), "Date (DD-MM-YYYY): %s", date);
    printCentered(detail_buf);
    snprintf(detail_buf, sizeof(detail_buf), "Time: %s", time);
    printCentered(detail_buf);
    snprintf(detail_buf, sizeof(detail_buf), "Seat Capacity: %d", seatCapacity);
    printCentered(detail_buf);

    // Add prompt to continue
    char continueBuf[10];
    inputCentered("Press Enter to continue...", continueBuf, sizeof(continueBuf));
    clear(); // Clear screen after viewing event details
}

void addEvent()
{
    char name[100], venue[100], date[20], time[20];
    int seatCapacity;

    printCentered("-- Add New Event --");
    resetUnifiedBlock(); // Reset the block formatting for prompts
    inputCentered("Event Name: ", name, 40);
    inputCentered("Venue: ", venue, 40);
    inputCentered("Date (DD-MM-YYYY): ", date, sizeof(date));
    inputCentered("Time (HH:MM): ", time, sizeof(time));

    char buf[16];
    inputCentered("Seat Capacity: ", buf, sizeof(buf));
    if (sscanf(buf, "%d", &seatCapacity) != 1)
    {
        printCentered("Invalid input for seat capacity.");
        return;
    }

    FILE *file = fopen("events.txt", "a");
    if (file == NULL)
    {
        printCentered("Error opening events file!");
        return;
    }
    fprintf(file, "%s|%s|%s|%s|%d\n", name, venue, date, time, seatCapacity);
    fclose(file);
    printCentered("Event added successfully!");

    // Add prompt to continue
    char continueBuf[10];
    inputCentered("Press Enter to continue...", continueBuf, sizeof(continueBuf));
    clear(); // Clear screen after adding event
}

void adminViewAllEvents()
{
    FILE *file = fopen("events.txt", "r");
    if (file == NULL)
    {
        printCentered("No events found.");
        return;
    }

    char line[300], name[100], venue[100], date[20], time[20];
    int seatCapacity, newSeatCapacity;
    int eventCount = 0;
    char events[50][300]; // Store up to 50 events

    printCentered("-- All Events --");
    
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
            printUnifiedBlock(eventBuf);
        }
    }
    fclose(file);
    char returnBuf[100];
    snprintf(returnBuf, sizeof(returnBuf), "%d. Return to admin menu", eventCount + 1);
    printUnifiedBlock(returnBuf);
    
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
                printUnifiedBlock(eventBuf);
            }
        }
        fclose(file);
        snprintf(returnBuf, sizeof(returnBuf), "%d. Return to admin menu", eventCount + 1);
        printUnifiedBlock(returnBuf);
    }

    if (eventCount == 0)
        return;

    int choice;
    char selectPrompt[100];
    snprintf(selectPrompt, sizeof(selectPrompt), "Select an event to view/edit/delete or %d to return: ", eventCount + 1);
    char buf[16];
    inputCentered(selectPrompt, buf, sizeof(buf));
    if (sscanf(buf, "%d", &choice) != 1)
    {
        printCentered("Invalid input.");
        return;
    }
    if (choice < 1 || choice > eventCount + 1)
    {
        printCentered("Invalid choice.");
        return;
    }
    if (choice == eventCount + 1)
    {
        clear(); // Clear screen before returning to admin dashboard
        return;
    }

    // Show details for selected event
    sscanf(events[choice - 1], "%99[^|]|%99[^|]|%19[^|]|%19[^|]|%d", name, venue, date, time, &seatCapacity);
    printCentered("--- Event Details ---");
    
    char buf_output[200];
    snprintf(buf_output, sizeof(buf_output), "Name: %s", name);
    printCentered(buf_output);
    snprintf(buf_output, sizeof(buf_output), "Venue: %s", venue);
    printCentered(buf_output);
    snprintf(buf_output, sizeof(buf_output), "Date (DD-MM-YYYY): %s", date);
    printCentered(buf_output);
    snprintf(buf_output, sizeof(buf_output), "Time: %s", time);
    printCentered(buf_output);
    snprintf(buf_output, sizeof(buf_output), "Seat Capacity: %d", seatCapacity);
    printCentered(buf_output);

    printCentered(""); // Add a blank line
    printCentered("1. Edit Event");
    printCentered("2. Delete Event");
    printCentered("3. Return");
    int action;
    char buf2[16];
    inputCentered("Select an option: ", buf2, sizeof(buf2));
    if (sscanf(buf2, "%d", &action) != 1)
    {
        printCentered("Invalid input.");
        return;
    }

    if (action == 1)
    {
        // Edit event
        char newName[100], newVenue[100], newDate[20], newTime[20];
        while (getchar() != '\n')
            ; // clear input buffer
        char promptName[150];
        snprintf(promptName, sizeof(promptName), "Enter new event name (or press Enter to keep '%s'): ", name);
        inputCentered(promptName, newName, sizeof(newName));
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
        inputCentered(promptVenue, newVenue, sizeof(newVenue));
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
        inputCentered(promptDate, newDate, sizeof(newDate));
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
        inputCentered(promptTime, newTime, sizeof(newTime));
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
        inputCentered(promptSeat, buf3, sizeof(buf3));
        if (sscanf(buf3, "%d", &newSeatCapacity) != 1 || newSeatCapacity <= 0)
            newSeatCapacity = seatCapacity;

        // Update event in array
        snprintf(events[choice - 1], sizeof(events[choice - 1]), "%s|%s|%s|%s|%d\n", newName, newVenue, newDate, newTime, newSeatCapacity);
        printCentered("Event updated successfully!");

        // Add prompt to continue
        char continueBuf[10];
        inputCentered("Press Enter to continue...", continueBuf, sizeof(continueBuf));
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
        printCentered("Event deleted successfully!");
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
        printCentered("Error updating events file!");
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
        printCentered("No users found.");
        printCentered("Press any key to continue...");
        getch();
        return;
    }

    printCentered("--- All Registered Users ---");
    printCentered("Ticket Code | Name");
    printCentered("---------------------------");

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
    
    // Now display with proper vertical alignment
    resetUnifiedBlock();
    for (int i = 0; i < userCount; i++)
    {
        // For the first pass, just collect string lengths
        if (sscanf(users[i], "%d,%99[^\n]", &ticketCode, name) == 2)
        {
            char buf[200];
            snprintf(buf, sizeof(buf), "    %04d    | %s", ticketCode, name);
            printUnifiedBlock(buf);
        }
    }
    
    // Second pass: Actually print with alignment
    resetUnifiedBlock();
    unified_blockFirstCall = 0; // Switch to printing mode
    
    for (int i = 0; i < userCount; i++)
    {
        if (sscanf(users[i], "%d,%99[^\n]", &ticketCode, name) == 2)
        {
            char buf[200];
            snprintf(buf, sizeof(buf), "    %04d    | %s", ticketCode, name);
            printUnifiedBlock(buf);
        }
    }
    
    printCentered("---------------------------");
    char totalMsg[50];
    snprintf(totalMsg, sizeof(totalMsg), "Total registered users: %d", userCount);
    printCentered(totalMsg);

    // Add prompt to continue
    char continueBuf[10];
    inputCentered("Press Enter to continue...", continueBuf, sizeof(continueBuf));
    clear(); // Clear screen after viewing users
}

/* ===================== Booking Management Functions ===================== */
void viewAllBookings()
{
    FILE *file = fopen(BOOKINGS_FILE, "r");
    if (file == NULL)
    {
        printCentered("No bookings found.");
        return;
    }

    printCentered("--- All Bookings ---");
    printCentered("Event ID | Name");
    printCentered("-------------------");

    char line[200];
    int eventID;
    char name[100];
    char bookings[50][200]; // Array to store bookings
    int bookingCount = 0;

    // First pass: collect all booking information
    while (fgets(line, sizeof(line), file) && bookingCount < 50)
    {
        if (sscanf(line, "%d %[^\n]", &eventID, name) == 2)
        {
            // Store booking information
            strcpy(bookings[bookingCount], line);
            bookingCount++;
        }
    }
    fclose(file);
    
    // Now display with proper vertical alignment
    resetUnifiedBlock();
    for (int i = 0; i < bookingCount; i++)
    {
        // For the first pass, just collect string lengths
        if (sscanf(bookings[i], "%d %[^\n]", &eventID, name) == 2)
        {
            char buf[200];
            snprintf(buf, sizeof(buf), "%8d | %s", eventID, name);
            printUnifiedBlock(buf);
        }
    }
    
    // Second pass: Actually print with alignment
    resetUnifiedBlock();
    unified_blockFirstCall = 0; // Switch to printing mode
    
    for (int i = 0; i < bookingCount; i++)
    {
        if (sscanf(bookings[i], "%d %[^\n]", &eventID, name) == 2)
        {
            char buf[200];
            snprintf(buf, sizeof(buf), "%8d | %s", eventID, name);
            printUnifiedBlock(buf);
        }
    }
    
    printCentered("-------------------");

    // Add prompt to continue
    char continueBuf[10];
    inputCentered("Press Enter to continue...", continueBuf, sizeof(continueBuf));
    clear(); // Clear screen after viewing bookings
}

void bookSeat()
{
    char name[100];
    int eventID;

    printCentered("-- Book a Seat --");
    // Check if there are any events
    FILE *file = fopen("events.txt", "r");
    if (file == NULL)
    {
        printCentered("No events found.");
        return;
    }
    int eventCount = 0;
    char line[300];
    while (fgets(line, sizeof(line), file))
    {
        eventCount++;
    }
    fclose(file);
    if (eventCount == 0)
    {
        printCentered("No events found.");
        return;
    }

    viewEvents();
    char buf[100];
    snprintf(buf, sizeof(buf), "Enter Event ID to book (1-%d): ", eventCount);
    char buf2[16];
    inputCentered(buf, buf2, sizeof(buf2));
    if (sscanf(buf2, "%d", &eventID) != 1)
    {
        printCentered("Invalid input for Event ID.");
        return;
    }

    if (eventID < 1 || eventID > eventCount)
    {
        printCentered("Invalid Event ID");
        return;
    }

    while (getchar() != '\n')
        ;
    inputCentered("Enter your name: ", name, sizeof(name));

    saveBooking(eventID, name);

    snprintf(buf, sizeof(buf), "Seat booked successfully for %s at event ID %d.", name, eventID);
    printCentered(buf);

    // Add prompt to continue
    char continueBuf[10];
    inputCentered("Press Enter to continue...", continueBuf, sizeof(continueBuf));
    clear(); // Clear screen after booking confirmation
}

void cancelBooking()
{
    char name[100];
    int eventID;

    printCentered("-- Cancel Booking --");
    while (getchar() != '\n')
        ;
    inputCentered("Enter your name: ", name, sizeof(name));

    char buf[16];
    inputCentered("Enter Event ID to cancel: ", buf, sizeof(buf));
    if (sscanf(buf, "%d", &eventID) != 1)
    {
        printCentered("Invalid input for Event ID.");
        return;
    }

    removeBooking(eventID, name);

    // Add prompt to continue
    char continueBuf[10];
    inputCentered("Press Enter to continue...", continueBuf, sizeof(continueBuf));
    clear(); // Clear screen after cancellation process
}

void saveBooking(int eventID, const char *name)
{
    FILE *file = fopen(BOOKINGS_FILE, "a");
    if (file == NULL)
    {
        printCentered("Error opening file, Name of event ID not Found!");
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
        printCentered("Error opening file!");
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
        printCentered("Booking successfully canceled.");
    }
    else
    {
        remove("temp.txt");
        char buf[200];
        snprintf(buf, sizeof(buf), "No booking found for %s at event ID %d.", name, eventID);
        printCentered(buf);
    }
}
