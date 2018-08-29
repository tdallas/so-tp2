#include <shell.h>

static char choice[BUFFER_SIZE];

#define DEFAULT 0
#define RED 1
#define ORANGE 2
#define YELLOW 3
#define GREEN 4
#define BLUE 5

void shell(int showMenu)
{
    int flag = 0;
    while (!flag)
    {
        printf("$> ");
        scanf("%n", choice);
        flag = managingCases(choice);
    }
}

int managingCases(char *option)
{
    if (strcmp(option, "help") == 0)
    {
        help();
    }
    else if (strncmp(option, "setTimeZone ", 11) == 0)
    {
        int newTimeZone;
        int correct = sscanf(option, "setTimeZone %d", &newTimeZone);
        if (correct == 1)
        {
            setTimeUTC(newTimeZone);
            printTimeUTC();
        }
        else
        {
            printf("Invalid input! For help write help.\n");
        }
    }
    else if (strncmp(option, "changeTextColor ", 15) == 0)
    {
        int correct = changeTextColor(option + 16);
        if (correct == 1)
        {
            printf("Color changed!\n");
        }
        else
        {
            printf("Invalid input! For help write help.\n");
        }
    }
    else if (strncmp(option, "changeBackGroundColor ", 21) == 0)
    {
        int correct = changeBackGroundColor(option + 22);
        if (correct == 1)
        {
            clearWorkSpace();
            printf("Color changed!\n");
        }
        else
        {
            printf("Invalid input! For help write help.\n");
        }
    }
    else if (strncmp(option, "echo ", 4) == 0)
    {
        char buffer[BUFFER_SIZE];
        int correct = sscanf(option, "echo %n", buffer);
        if (correct == 1)
        {
            printf(buffer);
            printf("\n");
        }
        else
        {
            printf("Invalid input! For help write help.\n");
        }
    }
    else if (strcmp(option, "info") == 0)
    {
        info();
    }
    else if (strcmp(option, "displayTime -digital") == 0)
    {
        startDigitalTime();
    }
    else if (strcmp(option, "displayTime -console") == 0)
    {
        displayTime();
    }
    else if (strcmp(option, "blobWars") == 0)
    {
        iniciarBlobWars();
    }
    else if (strcmp(option, "exceptionZero") == 0)
    {
        zeroDiv();
    }
    else if (strcmp(option, "exceptionOpCode") == 0)
    {
        opCode();
    }
    else if (strcmp(option, "clear") == 0)
    {
        clearWorkSpace();
    }
    else if (strcmp(option, "exit") == 0)
    {
        return 1;
    }
    else if (strcmp(option, "") != 0)
    {
        printf("Invalid input! For help write help.\n");
    }
    *option = 0;
    return 0;
}

int changeTextColor(char *color)
{
    int number = wichColor(color);
    switch (number)
    {
    case DEFAULT:
        setCharColor(255, 255, 255);
        break;
    case RED:
        setCharColor(255, 0, 0);
        break;
    case ORANGE:
        setCharColor(255, 128, 0);
        break;
    case YELLOW:
        setCharColor(255, 255, 0);
        break;
    case GREEN:
        setCharColor(0, 255, 0);
        break;
    case BLUE:
        setCharColor(0, 0, 255);
        break;
    }
    return number >= 0;
}

int changeBackGroundColor(char *color)
{
    int number = wichColor(color);
    switch (number)
    {
    case DEFAULT:
        setBackGroundColor(0, 0, 0);
        break;
    case RED:
        setBackGroundColor(255, 0, 0);
        break;
    case ORANGE:
        setBackGroundColor(255, 128, 0);
        break;
    case YELLOW:
        setBackGroundColor(255, 255, 0);
        break;
    case GREEN:
        setBackGroundColor(0, 255, 0);
        break;
    case BLUE:
        setBackGroundColor(0, 0, 255);
        break;
    }
    return number >= 0;
}

int wichColor(char *color)
{
    if (strcmp(color, "default") == 0)
    {
        return DEFAULT;
    }
    else if (strcmp(color, "red") == 0)
    {
        return RED;
    }
    else if (strcmp(color, "orange") == 0)
    {
        return ORANGE;
    }
    else if (strcmp(color, "yellow") == 0)
    {
        return YELLOW;
    }
    else if (strcmp(color, "green") == 0)
    {
        return GREEN;
    }
    else if (strcmp(color, "blue") == 0)
    {
        return BLUE;
    }
    return -1;
}