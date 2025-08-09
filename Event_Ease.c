#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

#define BOOKINGS_FILE "bookings.txt"

void welcomePage();
void loginPage();
void dashboard();
void viewEvents();
void bookSeat();
void cancelBooking();
void adminDashboard();
void saveBooking(int eventID, const char *name);
void removeBooking(int eventID, const char *name);
void viewAllBookings();
void adminViewAllEvents();
void dashboardDesign();

void addEvent();

int main()
{
    loginPage();
    return 0;
}

void welcomePage()
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO ci;
    GetConsoleScreenBufferInfo(h, &ci);

    SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

    const char *art[] = {
                                                                                                                                        @@@                     
                                                                                                                              @@@@@@@@@                  
                                                                                                                           +@@@@@@ @@@@:                 
                                                                                                                         @@@@@@      -@@                 
                                                                                                                      @@@@@@@@        @@                 
                                                                                                                   :@@@@@@   @       %@@.                
                                                                                                                 @@@@@@      @+      @@:                 
                                                                                                              @@@@@@.                @@                  
                                                                                                           .@@@@@@                   @@@-.               
                                                                                                         @@@@@@               @@      @@@@               
                                                                                                      %@@@@@*                  @       @@@*              
                                                                                                    @@@@@@                     @-        @@              
                                                                                                 @@@@@@                        @@        @@              
                                                                                              =@@@@@#                           #       @@@              
                                                                                             #@@@@                                      @@               
                                                                                              @@                                 @      @@               
                                                                                             @@@                                 @      @@@@@            
                                                                                            @@@                                  @@      @@@@            
                                                                                            #@@                                   @        @@@           
                                                                                             @@                                   @         @@           
                                                                                             @@@@@                                         @@@           
                @@@@@@@@%: @@@@        @@@@    -@@@@@@@@+    @@@%       @@@   @@@@@@@@@@@@@@  @@@@                                         @@            
              +@@@@@@@@@@@ @@@@.       @@@@   @@@@@@@@@@@   @@@@@@      @@@   @@@@@@@@@@@@@@    @@@                                @@     %@@            
              @@@@@@@@@@@@  @@@@       @@@@  @@@@@@@@@@@@   @@@@@@      @@@   @@@@@@@@@@@@@@    @@@                                +@   @@@@@            
              @@@@*=======  @@@@      @@@@   @@@@@=======   @@@@@@@     @@@   @@@@@@@@@@@@@@   @@@                                  @@@@@@@              
              @@@@          @@@@      @@@@   @@@@           @@@@@@@     @@@        @@@@        @@.                                *@@@@@@                
              @@@@           @@@:     @@@@   @@@@           @@@@@@@@    @@@        @@@@        =@@                              @@@@@@                   
              @@@@           @@@@     @@@-   @@@@           @@@@ @@@    @@@        @@@@         @@@@                         @@@@@@.                     
              @@@@.......    @@@@    @@@@    @@@@.......    @@@@ @@@#   @@@        @@@@         @@@@@                      @@@@@@                        
              @@@@@@@@@@@    #@@@    @@@@    @@@@@@@@@@@    @@@@  @@@   @@@        @@@@            @@                      @@@                           
              @@@@@@@@@@@     @@@.   @@@@    @@@@@@@@@@@    @@@@  @@@*  @@@        @@@@                                               .-                 
              @@@@            @@@@   @@@     @@@@           @@@@   @@@  @@@        @@@@         @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                
              @@@@            @@@@  @@@@     @@@@           @@@@   @@@+ @@@        @@@@        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                
              @@@@             @@@  @@@@     @@@@           @@@@    @@@ @@@        @@@@        @@-                              @      @@@@              
              @@@@             @@@: @@@:     @@@@           @@@@    @@@ @@@        @@@@      @@@@                               @       *@@              
              @@@@             @@@@ @@@      @@@@           @@@@    .@@@@@@        @@@@      @@%                                @        @@              
              @@@@@@@@@@@@     +@@@@@@@      @@@@@@@@@@@@   @@@@     @@@@@@        @@@@      @@.                                         @@              
              @@@@@@@@@@@@      @@@@@@@      +@@@@@@@@@@@   @@@@     .@@@@@        @@@@      @@@                                       :@@@              
               @@@@@@@@@@@      @@@@@@        @@@@@@@@@@@   @@@@      @@@@@        @@@@      @@@@                               @-     @@@               
                                                                                               @@@                              @#     @@                
                                                                                                @@                              @@     @@#               
                                             @@@@@@@     :@@@@      -@@@@@@@    @@@@@@@@       @@@                              @@     *@@@              
                                           =@@@@@@@@     @@@@@     @@@@@@@@@   @@@@@@@@@     @@@@                               @        @@              
                                           @@@@@@@@@     @@@@@@    @@@@@@@@@   @@@@@@@@@     @@@                                         @@              
                                           @@@          @@@ @@@    @@@         @@@           @@@                                         @@              
                                           @@@          @@@ @@@    @@@         @@@           %@@                                @@      @@@              
                                           @@@          @@@  @@:   @@@@@       @@@            @@@                               @@     @@@               
                                           @@@@@@@@@   =@@   @@@    @@@@@@#    @@@@@@@@        @@@                              @@     @@                
                                           @@@@@@@@@   @@@   @@@     @@@@@@@   @@@@@@@@         @@                              @@     @@@               
                                           @@@         @@@@@@@@@        @@@@+  @@@             @@@                                      @@@.             
                                           @@@         @@@@@@@@@@         @@@  @@@            @@@                                        @@-             
                                           @@@        @@@     @@@         @@@  @@@            @@                                         @@*             
                                           @@@@:::::  @@@     @@@  *=-..:@@@@  @@@::::::      @@                                @@       @@%             
                                           @@@@@@@@@  @@@      @@@ @@@@@@@@@   @@@@@@@@@      @@                                @@      @@@#             
                                            @@@@@@@@ @@@       @@@ @@@@@@@@.    @@@@@@@@      @@@+                              @@   ..@@@               
                                                                                               *@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                
                                                                                                @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                
                                                                                                 .                                                       
                                                                                                                                                         
                                                                                                                                                         
                                                                                                                                                         
                                                                                                                                                         

    int lines = sizeof(art) / sizeof(art[0]);
    for (int i = 0; i < lines; i++)
    {
        puts(art[i]);
        Sleep(60);
    }

    SetConsoleTextAttribute(h, ci.wAttributes);
}

void dashboardDesign()
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO ci;
    GetConsoleScreenBufferInfo(h, &ci);

    // Cyan = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY
    SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

    const char *art[] = {
        "                                                                             ",
        "    ██████╗  █████╗ ███████╗██╗  ██╗██████╗  ██████╗  █████╗ ██████╗ ██████╗ ",
        "    ██╔══██╗██╔══██╗██╔════╝██║  ██║██╔══██╗██╔═══██╗██╔══██╗██╔══██╗██╔══██╗",
        "    ██║  ██║███████║███████╗███████║██████╔╝██║   ██║███████║██████╔╝██║  ██║",
        "    ██║  ██║██╔══██║╚════██║██╔══██║██╔══██╗██║   ██║██╔══██║██╔══██╗██║  ██║",
        "    ██████╔╝██║  ██║███████║██║  ██║██████╔╝╚██████╔╝██║  ██║██║  ██║██████╔╝",
        "    ╚═════╝ ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚═════╝  ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚═════╝ "};

    int lines = sizeof(art) / sizeof(art[0]);
    for (int i = 0; i < lines; i++)
    {
        puts(art[i]);
        Sleep(60);
    }

    SetConsoleTextAttribute(h, ci.wAttributes);
}

void getPassword(char *password, int maxLength)
{
    int i = 0;
    char ch;
    while ((ch = getch()) != '\r' && i < maxLength - 1)
    {
        if (ch == '\b' && i > 0)
        {
            i--;
            printf("\b \b");
        }
        else if (ch != '\b')
        {
            password[i++] = ch;
            printf("*");
        }
    }
    password[i] = '\0';
    printf("\n");
}

void loginPage() // Function used for login
{

#define USERNAME "user"
#define PASSWORD "weakpassword"
#define aUSERNAME "admin"
#define aPASSWORD "strongpassword"
    char user[50], pass[50];
    while (1)
    {
        welcomePage();
        printf("Enter your User name and password to login...\n");
        printf("Username: ");
        scanf("%49s", user);
        printf("Password: ");
        getPassword(pass, sizeof(pass));

        if (strcmp(user, USERNAME) == 0 && strcmp(pass, PASSWORD) == 0)
        {
            printf("Login Success\n");
            dashboard();
            break;
        }
        else if (strcmp(user, aUSERNAME) == 0 && strcmp(pass, aPASSWORD) == 0)
        {
            printf("\nAdmin Access granted\n");
            adminDashboard();
            break;
        }
        else
        {
            printf("Invalid Credentials.\nTry again\n");
        }
    }
}

void adminDashboard()
{
    int choice;
    while (1)
    {
        dashboardDesign();
        printf("1. View all bookings\n");
        printf("2. Add Event\n");
        printf("3. View All Events\n");
        printf("0. Exit\n");
        printf("Select an option: ");
        if (scanf("%d", &choice) != 1)
        {
            while (getchar() != '\n')
                ; // clear invalid input
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        switch (choice)
        {
        case 1:
            viewAllBookings();
            break;
        case 2:
            addEvent();
            break;
        case 3:
            adminViewAllEvents();
            break;
        case 0:
            printf("Logging out of admin panel...\n");
            return;
        default:
            printf("Invalid choice. Please select again.\n");
        }
    }
}
// Admin function to view, edit, or delete events
void adminViewAllEvents()
{
    FILE *file = fopen("events.txt", "r");
    if (file == NULL)
    {
        printf("\nNo events found.\n");
        return;
    }

    char line[300], name[100], venue[100], date[20], time[20];
    int seatCapacity, newSeatCapacity;
    int eventCount = 0;
    char events[50][300]; // Store up to 50 events

    printf("\n-- All Events --\n");
    while (fgets(line, sizeof(line), file))
    {
        if (sscanf(line, "%99[^|]|%99[^|]|%19[^|]|%19[^|]|%d", name, venue, date, time, &seatCapacity) == 5)
        {
            eventCount++;
            strncpy(events[eventCount - 1], line, sizeof(events[eventCount - 1]) - 1);
            events[eventCount - 1][sizeof(events[eventCount - 1]) - 1] = '\0';
            printf("%d. %s\n", eventCount, name);
        }
    }
    fclose(file);
    printf("%d. Return to admin menu\n", eventCount + 1);

    if (eventCount == 0)
        return;

    int choice;
    printf("Select an event to view/edit/delete or %d to return: ", eventCount + 1);
    if (scanf("%d", &choice) != 1)
    {
        while (getchar() != '\n')
            ;
        printf("Invalid input.\n");
        return;
    }
    if (choice < 1 || choice > eventCount + 1)
    {
        printf("Invalid choice.\n");
        return;
    }
    if (choice == eventCount + 1)
        return;

    // Show details for selected event
    sscanf(events[choice - 1], "%99[^|]|%99[^|]|%19[^|]|%19[^|]|%d", name, venue, date, time, &seatCapacity);
    printf("\n--- Event Details ---\n");
    printf("Name: %s\n", name);
    printf("Venue: %s\n", venue);
    printf("Date (DD-MM-YYYY): %s\n", date);
    printf("Time: %s\n", time);
    printf("Seat Capacity: %d\n", seatCapacity);

    printf("\n1. Edit Event\n2. Delete Event\n3. Return\nSelect an option: ");
    int action;
    if (scanf("%d", &action) != 1)
    {
        while (getchar() != '\n')
            ;
        printf("Invalid input.\n");
        return;
    }

    if (action == 1)
    {
        // Edit event
        char newName[100], newVenue[100], newDate[20], newTime[20];
        while (getchar() != '\n')
            ; // clear input buffer
        printf("Enter new event name (or press Enter to keep '%s'): ", name);
        fgets(newName, sizeof(newName), stdin);
        if (newName[0] == '\n')
            strcpy(newName, name);
        else
        {
            size_t l = strlen(newName);
            if (l > 0 && newName[l - 1] == '\n')
                newName[l - 1] = '\0';
        }

        printf("Enter new venue (or press Enter to keep '%s'): ", venue);
        fgets(newVenue, sizeof(newVenue), stdin);
        if (newVenue[0] == '\n')
            strcpy(newVenue, venue);
        else
        {
            size_t l = strlen(newVenue);
            if (l > 0 && newVenue[l - 1] == '\n')
                newVenue[l - 1] = '\0';
        }

        printf("Enter new date (DD-MM-YYYY) (or press Enter to keep '%s'): ", date);
        fgets(newDate, sizeof(newDate), stdin);
        if (newDate[0] == '\n')
            strcpy(newDate, date);
        else
        {
            size_t l = strlen(newDate);
            if (l > 0 && newDate[l - 1] == '\n')
                newDate[l - 1] = '\0';
        }

        printf("Enter new time (or press Enter to keep '%s'): ", time);
        fgets(newTime, sizeof(newTime), stdin);
        if (newTime[0] == '\n')
            strcpy(newTime, time);
        else
        {
            size_t l = strlen(newTime);
            if (l > 0 && newTime[l - 1] == '\n')
                newTime[l - 1] = '\0';
        }

        printf("Enter new seat capacity (or 0 to keep %d): ", seatCapacity);
        if (scanf("%d", &newSeatCapacity) != 1 || newSeatCapacity <= 0)
            newSeatCapacity = seatCapacity;

        // Update event in array
        snprintf(events[choice - 1], sizeof(events[choice - 1]), "%s|%s|%s|%s|%d\n", newName, newVenue, newDate, newTime, newSeatCapacity);
        printf("Event updated successfully!\n");
    }
    else if (action == 2)
    {
        // Delete event
        for (int i = choice - 1; i < eventCount - 1; i++)
        {
            strcpy(events[i], events[i + 1]);
        }
        eventCount--;
        printf("Event deleted successfully!\n");
    }
    else
    {
        return;
    }

    // Write updated events back to file
    file = fopen("events.txt", "w");
    if (file == NULL)
    {
        printf("Error updating events file!\n");
        return;
    }
    for (int i = 0; i < eventCount; i++)
    {
        fputs(events[i], file);
    }
    fclose(file);
}

void viewAllBookings()
{
    FILE *file = fopen(BOOKINGS_FILE, "r");
    if (file == NULL)
    {
        printf("No bookings found.\n");
        return;
    }

    printf("\n--- All Bookings ---\n");
    printf("Event ID | Name\n");
    printf("-------------------\n");

    char line[200];
    int eventID;
    char name[100];

    while (fgets(line, sizeof(line), file))
    {
        if (sscanf(line, "%d %[^\n]", &eventID, name) == 2)
        {
            printf("%8d | %s\n", eventID, name);
        }
    }
    printf("-------------------\n");
    fclose(file);
}

// Dashboard for user
void dashboard()
{
    int choice;

    while (1)
    {
        dashboardDesign();
        printf("1. View Events\n");
        printf("2. Book Seat\n");
        printf("3. Cancel Booking\n");
        printf("4. View All Bookings\n");
        printf("0. Exit\n");
        printf("Select an option: ");

        if (scanf("%d", &choice) != 1)
        {
            while (getchar() != '\n')
                ;
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        switch (choice)
        {
        case 1:
            viewEvents();
            break;
        case 2:
            bookSeat();
            break;
        case 3:
            cancelBooking();
            break;
        case 4:
            viewAllBookings();
            break;
        case 0:
            printf("Thank you for using EventEase!\n");
            exit(0);
        default:
            printf("Invalid choice. Please select again.\n");
        }
    }
}
// Function to add event information and save to events.txt
void addEvent()
{
    char name[100], venue[100], date[20], time[20];
    int seatCapacity;

    printf("\n-- Add New Event --\n");
    printf("Event Name: ");
    while (getchar() != '\n')
        ; // clear input buffer
    fgets(name, sizeof(name), stdin);
    size_t len = strlen(name);
    if (len > 0 && name[len - 1] == '\n')
        name[len - 1] = '\0';

    printf("Venue: ");
    fgets(venue, sizeof(venue), stdin);
    len = strlen(venue);
    if (len > 0 && venue[len - 1] == '\n')
        venue[len - 1] = '\0';

    printf("Date (DD-MM-YYYY): ");
    fgets(date, sizeof(date), stdin);
    len = strlen(date);
    if (len > 0 && date[len - 1] == '\n')
        date[len - 1] = '\0';

    printf("Time (HH:MM): ");
    fgets(time, sizeof(time), stdin);
    len = strlen(time);
    if (len > 0 && time[len - 1] == '\n')
        time[len - 1] = '\0';

    printf("Seat Capacity: ");
    if (scanf("%d", &seatCapacity) != 1)
    {
        printf("Invalid input for seat capacity.\n");
        return;
    }

    FILE *file = fopen("events.txt", "a");
    if (file == NULL)
    {
        printf("Error opening events file!\n");
        return;
    }
    fprintf(file, "%s|%s|%s|%s|%d\n", name, venue, date, time, seatCapacity);
    fclose(file);
    printf("Event added successfully!\n");
}

void viewEvents()
{
    FILE *file = fopen("events.txt", "r");
    if (file == NULL)
    {
        printf("\nNo events found.\n");
        return;
    }

    char line[300], name[100], venue[100], date[20], time[20];
    int seatCapacity;
    int eventCount = 0;
    char events[50][300]; // Store up to 50 events

    printf("\n-- Available Events --\n");
    while (fgets(line, sizeof(line), file))
    {
        if (sscanf(line, "%99[^|]|%99[^|]|%19[^|]|%19[^|]|%d", name, venue, date, time, &seatCapacity) == 5)
        {
            eventCount++;
            snprintf(events[eventCount - 1], sizeof(events[eventCount - 1]), "%s|%s|%s|%s|%d", name, venue, date, time, seatCapacity);
            printf("%d. %s\n", eventCount, name);
        }
    }
    fclose(file);
    printf("%d. Return to main menu\n", eventCount + 1);

    if (eventCount == 0)
        return;

    int choice;
    printf("Select an event to view details or %d to return: ", eventCount + 1);
    if (scanf("%d", &choice) != 1)
    {
        while (getchar() != '\n')
            ;
        printf("Invalid input.\n");
        return;
    }
    if (choice < 1 || choice > eventCount + 1)
    {
        printf("Invalid choice.\n");
        return;
    }
    if (choice == eventCount + 1)
        return;

    // Show details for selected event
    sscanf(events[choice - 1], "%99[^|]|%99[^|]|%19[^|]|%19[^|]|%d", name, venue, date, time, &seatCapacity);
    printf("\n--- Event Details ---\n");
    printf("Name: %s\n", name);
    printf("Venue: %s\n", venue);
    printf("Date (DD-MM-YYYY): %s\n", date);
    printf("Time: %s\n", time);
    printf("Seat Capacity: %d\n", seatCapacity);
}

void bookSeat()
{
    char name[100];
    int eventID;

    printf("\n-- Book a Seat --\n");
    // Check if there are any events
    FILE *file = fopen("events.txt", "r");
    if (file == NULL)
    {
        printf("No events found.\n");
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
        printf("No events found.\n");
        return;
    }

    viewEvents();
    printf("Enter Event ID to book (1-%d): ", eventCount);
    if (scanf("%d", &eventID) != 1)
    {
        while (getchar() != '\n')
            ;
        printf("Invalid input for Event ID.\n");
        return;
    }

    if (eventID < 1 || eventID > eventCount)
    {
        printf("Invalid Event ID\n");
        return;
    }

    printf("Enter your name: ");
    while (getchar() != '\n')
        ;
    fgets(name, sizeof(name), stdin);

    size_t len = strlen(name);
    if (len > 0 && name[len - 1] == '\n')
        name[len - 1] = '\0';

    saveBooking(eventID, name);

    printf("Seat booked successfully for %s at event ID %d.\n", name, eventID);
}

void cancelBooking()
{
    char name[100];
    int eventID;

    printf("\n-- Cancel Booking --\n");
    printf("Enter your name: ");
    while (getchar() != '\n')
        ; // clear newline character
    fgets(name, sizeof(name), stdin);

    // Remove trailing newline from fgets
    size_t len = strlen(name);
    if (len > 0 && name[len - 1] == '\n')
        name[len - 1] = '\0';

    printf("Enter Event ID to cancel: ");
    if (scanf("%d", &eventID) != 1)
    {
        while (getchar() != '\n')
            ;
        printf("Invalid input for Event ID.\n");
        return;
    }

    removeBooking(eventID, name);
}

void saveBooking(int eventID, const char *name)
{
    FILE *file = fopen(BOOKINGS_FILE, "a");
    if (file == NULL)
    {
        printf("Error opening file,Name of event ID not Found!\n");
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
        printf("Error opening file!\n");
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
        printf("Booking successfully canceled.\n");
    }
    else
    {
        remove("temp.txt");
        printf("No booking found for %s at event ID %d.\n", name, eventID);
    }
}

