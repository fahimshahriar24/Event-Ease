#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    static char eventName[100];

    while (fgets(line, sizeof(line), file))
    {
        if (sscanf(line, "%99[^|]|%99[^|]|%19[^|]|%19[^|]|%d", name, venue, date, time, &seatCapacity) == 5)
        {
            if (currentEventID == eventID)
            {
                fclose(file);
                strcpy(eventName, name);
                return eventName;
            }
            currentEventID++;
        }
    }
    
    fclose(file);
    strcpy(eventName, "Unknown Event");
    return eventName;
}

int main() {
    printf("Event ID 1: %s\n", getEventNameByID(1));
    printf("Event ID 2: %s\n", getEventNameByID(2));
    printf("Event ID 3: %s\n", getEventNameByID(3));
    return 0;
}
