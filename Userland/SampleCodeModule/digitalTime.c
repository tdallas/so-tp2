#include <digitalTime.h>

#define WHITE 0
#define RED 1
#define ORANGE 2
#define YELLOW 3
#define GREEN 4
#define BLUE 5

static int actualColor = WHITE;
static unsigned char R = 255;
static unsigned char G = 255;
static unsigned char B = 255;

void startDigitalTime()
{
    int lastTime[7];
    int actualTime[7];
    char c;

    clearWorkSpace();
    printf("Press c to change color or b or ESC to go back.\n");
    
    printMark();

    getAllTimes(lastTime);
    getAllTimes(actualTime);

    printHour(actualTime);
    printMinute(actualTime);
    printSecond(actualTime);

    while ((c = getchar()) != 'b' && c != 27)
    {
        getAllTimes(actualTime);
        if (actualTime[0] > lastTime[0])
        {
            if (actualTime[0] == 59)
                lastTime[0] = -1;
            else
                lastTime[0] = actualTime[0];
            printSecond(actualTime);
            if (actualTime[1] > lastTime[1])
            {
                if (actualTime[1] == 59)
                    lastTime[1] = -1;
                else
                    lastTime[1] = actualTime[1];
                printMinute(actualTime);
                if (actualTime[2] > lastTime[2])
                {
                    if (actualTime[2] == 23)
                        lastTime[2] = -1;
                    else
                        lastTime[2] = actualTime[2];
                    lastTime[2] = actualTime[2];
                    printHour(actualTime);
                }
            }
        }
        if (c == 'c')
        {
            beepSound();
            changeColor();
            printMark();
            printHour(actualTime);
            printMinute(actualTime);
            printSecond(actualTime);
        }
    }
    clearWorkSpace();
}

void printHour(int actualTime[7])
{
    int hour = actualTime[2];
    if (hour >= 10)
    {
        int secondDigit = hour % 10;
        int firstDigit = (hour - secondDigit) / 10;
        printBigChar(firstDigit + '0', 140, 260, R, G, B);
        printBigChar(secondDigit + '0', 255, 260, R, G, B);
    }
    else
    {
        printBigChar('0', 140, 260, R, G, B);
        printBigChar((hour % 10) + '0', 255, 260, R, G, B);
    }
}

void printMinute(int actualTime[7])
{
    int minute = actualTime[1];
    if (minute >= 10)
    {
        int secondDigit = minute % 10;
        int firstDigit = (minute - secondDigit) / 10;
        printBigChar(firstDigit + '0', 404, 260, R, G, B);
        printBigChar(secondDigit + '0', 532, 260, R, G, B);
    }
    else
    {
        printBigChar('0', 404, 260, R, G, B);
        printBigChar((minute % 10) + '0', 532, 260, R, G, B);
    }
}

void printSecond(int actualTime[7])
{
    int second = actualTime[0];
    if (second >= 10)
    {
        int secondDigit = second % 10;
        int firstDigit = (second - secondDigit) / 10;
        printBigChar(firstDigit + '0', 668, 260, R, G, B);
        printBigChar(secondDigit + '0', 796, 260, R, G, B);
    }
    else
    {
        printBigChar('0', 668, 260, R, G, B);
        printBigChar((second % 10) + '0', 796, 260, R, G, B);
    }
}

void printMark()
{
    unsigned int y, x;

    for (y = 240; y <= 255; y++)
    {
        for (x = 110; x <= 920; x++)
        {
            putPixel(x, y, R, G, B);
        }
    }

    for (y = 255; y <= 512; y++)
    {
        for (x = 110; x <= 127; x++)
        {
            putPixel(x, y, R, G, B);
            putPixel(x + 793, y, R, G, B);
        }
    }

    for (y = 513; y <= 528; y++)
    {
        for (x = 110; x <= 920; x++)
        {
            putPixel(x, y, R, G, B);
        }
    }

    printCharBlock(377, 330, R, G, B);
    printCharBlock(377, 422,R, G, B);
    printCharBlock(641, 330, R, G, B);
    printCharBlock(641, 422, R, G, B);
}

void printBigChar(unsigned char c, unsigned int xPos, unsigned int yPos, unsigned char red, unsigned char green, unsigned char blue)
{
    unsigned char *charPixelMap = fontPixelMap(c);
    unsigned char charPixel;
    int y = 0;
    int x = 0;

    while (y < FONT_HEIGHT - 1)
    {
        x = 0;
        while (x < FONT_WIDTH)
        {
            charPixel = charPixelMap[y];
            charPixel >>= FONT_WIDTH - x;

            if (charPixel % 2 == 1)
            {
                printCharBlock(xPos + (x * FONT_WIDTH), yPos + (y * FONT_HEIGHT), red, green, blue);
            }
            else
            {
                printCharBlockBackGround(xPos + (x * FONT_WIDTH), yPos + (y * FONT_HEIGHT));
            }
            x++;
        }
        y++;
    }
}

void printCharBlock(unsigned int fromX, unsigned int fromY, unsigned char red, unsigned char green, unsigned char blue)
{
    int toY = fromY + FONT_HEIGHT;
    int toX = fromX + FONT_WIDTH;
    int auxX = fromX;
    while (fromY <= toY)
    {
        fromX = auxX;
        while (fromX <= toX)
        {
            putPixel(fromX, fromY, red, green, blue);
            fromX++;
        }
        fromY++;
    }
}

void printCharBlockBackGround(unsigned int fromX, unsigned int fromY)
{
    int toY = fromY + FONT_HEIGHT;
    int toX = fromX + FONT_WIDTH;
    int auxX = fromX;
    while (fromY <= toY)
    {
        fromX = auxX;
        while (fromX <= toX)
        {
            printPixelBackGroundColor(fromX, fromY);
            fromX++;
        }
        fromY++;
    }
}

void changeColor()
{
    if(actualColor == 5)
        actualColor = 0;
    else
        actualColor++;
    switch(actualColor){
        case WHITE:
            R = 255;
            G = 255;
            B = 255;
            break;
        case RED:
            R = 255;
            G = 0;
            B = 0;
            break;
        case ORANGE:
            R = 255;
            G = 128;
            B = 0;
            break;
        case YELLOW:
            R = 255;
            G = 255;
            B = 0;
            break;
        case GREEN:
            R = 0;
            G = 255;
            B = 0;
            break;
        case BLUE:
            R = 0;
            G = 0;
            B = 255;
            break;
    }
}