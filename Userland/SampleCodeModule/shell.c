#include <shell.h>
#include <processExec.h>
#include <stdio.h>
#include <exitProcess.h>
#include <prodcons.h>

static char choice[BUFFER_SIZE];

#define STEP 10

#define CMD_SIZE 14

static int isRunning = 1;
static instruction commands[] = {
		{"help\n", help},
		{"changeTextColor\n", changeTextColor},
		{"changeBackGroundColor\n", changeBackGroundColor},
		{"info\n", info},
		{"clear\n", clearWorkSpace},
		{"displayTimeDigital\n", startDigitalTime},
		{"displayTimeConsole\n", displayTime},
		{"blobWars\n", iniciarBlobWars},
		{"exceptionZero\n", zeroDiv},
		{"exit\n", exitProcess},
		{"exceptionOpCode\n", opCode},
		{"messageTest\n", messageTest},
		{"printPids\n", printPids},
		{"prodcons\n", prodcons}
	};

#define DEFAULT 0
#define RED 1
#define ORANGE 2
#define YELLOW 3
#define GREEN 4
#define BLUE 5

void shell()
{
	printf("Shell initialized\n");
	char string[MAX_WORD_LENGTH] = {0};
	char lastString[MAX_WORD_LENGTH] = {0};
	int counter = 0;
	char ch;

	printf("$> ");

	while (isRunning)
	{
		ch = getchar();

		if (counter < MAX_WORD_LENGTH || ch == '\n' || ch == '\b')
		{

			putchar(ch);

			string[counter] = ch;
			(ch != 0) ? counter++ : counter;

			if (ch == '\n')
			{
				callFunction(string);
				for(int aux=0; aux<counter; aux++){
					string[aux] = 0;
				}
				counter = 0;
			}

			if (ch == '\b')
			{
				(counter != 0) ? string[counter--] = 0 : counter;
				(counter != 0) ? string[counter--] = 0 : counter;
			}
			if (ch == 14)
			{
				while (counter)
				{
					putchar('\b');
					(counter != 0) ? string[counter--] = 0 : counter;
					(counter != 0) ? string[counter] = 0 : counter;
				}
			}
		}
	}
}

int callFunction(char *buffer)
{
	if (buffer == NULL)
	{
		return 1;
	}

	int words;
	char **argv;

	int foreground = 1;
	if (*buffer == '&')
	{
		buffer++;
		foreground = 0;
	}

	parseParams(buffer, &words, &argv);
	int i, valid = 0;
	for (i = 0; i < CMD_SIZE && valid == 0; i++)
	{
		if (strcmp(argv[0], commands[i].name) == 0)
		{
			execProcess(commands[i].function, words, argv, commands[i].name, foreground);
			valid = 1;
		}
	}

	if (valid == 0){
		printf("Wrong input\n$>");
		return 0;
	}

	return 1;
}

void parseParams(char *command, int *argc, char ***argv)
{
	char buffer[BUFFERSIZE];
	int count = 0, size = 0, i = 0, j = 0;
	do
	{
		if (command[i] != ' ' && command[i] != 0)
		{
			buffer[j] = command[i];
			j++;
		}
		else if (j != 0)
		{
			if (size - count == 0)
			{
				size += STEP;
				(*argv) = (char **)malloc(sizeof(void *) * size);
			}
			(*argv)[count] = (char *)malloc(sizeof(char) * (j + 1));
			for (int k = 0; k < j; k++)
			{
				(*argv)[count][k] = buffer[k];
			}
			(*argv)[count][j] = 0; //Null terminated
			count++;
			j = 0;
		}
	} while (command[i++] != 0);

	(*argc) = count;
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
