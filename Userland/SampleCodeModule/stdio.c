#include <stdio.h>

static unsigned int charR = 255;
static unsigned int charG = 255;
static unsigned int charB = 255;
static char buffer[BUFFER_SIZE];

int abs(int a)
{
    if (a < 0)
    {
        return -a;
    }
    return a;
}

void beepSound()
{
    systemCall(3, 0, 0, 0, 0, 0);
}

void putPixel(unsigned int x, unsigned int y, unsigned char red, unsigned char green, unsigned char blue)
{
    systemCall(7, (uint64_t)x, (uint64_t)y, (uint64_t)red, (uint64_t)green, (uint64_t)blue);
}

void setPixel(unsigned int x, unsigned int y)
{
    systemCall(8, (uint64_t)x, (uint64_t)y, 0, 0, 0);
}

void printPixelBackGroundColor(unsigned int x, unsigned int y)
{
    systemCall(9, (uint64_t)x, (uint64_t)y, 0, 0, 0);
}

void clearWorkSpace()
{
    systemCall(5, 0, 0, 0, 0, 0);
}

void setBackGroundColor(unsigned int red, unsigned int green, unsigned int blue)
{
    systemCall(6, (uint64_t)red, (uint64_t)green, (uint64_t)blue, 0, 0);
}

void setCharColor(unsigned int red, unsigned int green, unsigned int blue)
{
    charR = red;
    charG = green;
    charB = blue;
}

int getchar()
{
    return systemCall(1, 0, 0, 0, 0, 0);
}

void putchar(unsigned char c)
{
    if (c != 0)
        systemCall(2, (uint64_t)c, (uint64_t)charR, (uint64_t)charG, (uint64_t)charB, 0);
}

void *malloc(long unsigned int size)
{
    if (size == 0)
    {
        return NULL;
    }
    return (void *)systemCall(4, (uint64_t)size, 0, 0, 0, 0);
}

void free(void *pointer)
{
    return;
}

int printf(const char *str, ...)
{
    va_list arguments;
    va_start(arguments, str);
    char num[INT_BUFFER_SIZE];
    int strIndex = 0;
    while (str[strIndex] != '\0')
    {
        if (str[strIndex] != '%')
        {
            putchar(str[strIndex]);
        }
        else
        {
            switch (str[++strIndex])
            {
            case 'd':
            case 'i':
                inToString(va_arg(arguments, int), num);
                int index = 0;
                while (num[index] != 0)
                    putchar(num[index++]);
                break;
            case 'c':
                putchar((char)(va_arg(arguments, int)));
                break;
            case 's':
                printf(va_arg(arguments, char *));
                break;
            default:
                putchar('%');
                putchar(str[strIndex]);
                break;
            }
        }
        strIndex++;
    }
    va_end(arguments);
    return strIndex;
}

int sscanf(const char *str, const char *format, ...)
{
    va_list args;
    va_start(args, format);

    int strIndex = 0;
    int formatIndex = 0;

    int result = 0;
    int flag = 0;
    int auxIndex;

    char *auxChar;
    int *auxNum;

    while (format[formatIndex] != '\0' && str[strIndex] != '\0' && !flag)
    {
        if (format[formatIndex] != '%')
        {
            if (format[formatIndex] != str[strIndex])
            {
                flag = 1;
            }
            else
            {
                formatIndex++;
                strIndex++;
            }
        }
        else
        {
            formatIndex++;
            switch (format[formatIndex])
            {
            default:
                if (str[strIndex] != '%')
                {
                    flag = 1;
                }
                else
                {
                    strIndex++;
                }
                break;
            case 'd':
            case 'i':
                auxNum = va_arg(args, int *);
                auxIndex = strIndex;
                strIndex += stringToInt(str + strIndex, auxNum);
                if (strIndex > auxIndex)
                {
                    result++;
                }
                else
                {
                    flag = 1;
                }
                formatIndex++;
                break;
            case 'c':
                auxChar = va_arg(args, char *);
                if (isAlpha(str[strIndex]))
                {
                    *auxChar = str[strIndex++];
                    result++;
                }
                else
                {
                    *auxChar = '\0';
                    flag = 1;
                }
                formatIndex++;
                break;
            case 's': //String hasta espacio
                auxChar = va_arg(args, char *);
                auxIndex = strIndex;
                while (!isSpace(str[strIndex]) && str[strIndex] != '\0')
                {
                    *auxChar = str[strIndex];
                    auxChar++;
                    strIndex++;
                }
                if (strIndex > auxIndex)
                {
                    auxChar[auxIndex] = '\0';
                    result++;
                }
                else
                {
                    auxChar[auxIndex] = '\0';
                    flag = 1;
                }
                formatIndex++;
                break;
            case 'n': //String hasta el enter
                auxChar = va_arg(args, char *);
                auxIndex = strIndex;
                while (str[strIndex] != '\0')
                {
                    *auxChar = str[strIndex];
                    auxChar++;
                    strIndex++;
                }
                if (strIndex > auxIndex)
                {
                    auxChar[auxIndex] = '\0';
                    result++;
                }
                else
                {
                    auxChar[auxIndex] = '\0';
                    flag = 1;
                }
                formatIndex++;
                break;
            }
        }
    }

    if (flag || (format[formatIndex] == '\0' && str[strIndex] != '\0'))
    {
        return 0;
    }

    va_end(args);
    return result;
}

int readLine(char buffer[BUFFER_SIZE])
{
    int bufferIndex = 0;
    int c;

    while ((c = getchar()) != '\n')
    {
        if (c == '\b')
        {
            if (bufferIndex > 0)
            {
                bufferIndex--;
                putchar('\b');
            }
        }
        else if (c != EOF && c > 31)
        {
            if (bufferIndex <= BUFFER_SIZE)
            {
                buffer[bufferIndex++] = c;
            }
            putchar(c);
        }
    }
    putchar('\n');
    buffer[bufferIndex++] = '\0';
    return bufferIndex;
}

int scanf(const char *format, ...)
{
    va_list args;
    va_start(args, format);

    readLine(buffer);
    int bufferIndex = 0;
    int formatIndex = 0;

    int result = 0;
    int flag = 0;
    int auxIndex;

    char *auxChar;
    int *auxNum;

    while (format[formatIndex] != '\0' && buffer[bufferIndex] != '\0' && !flag)
    {
        if (format[formatIndex] != '%')
        {
            if (format[formatIndex] != buffer[bufferIndex])
            {
                flag = 1;
            }
            else
            {
                formatIndex++;
                bufferIndex++;
            }
        }
        else
        {
            formatIndex++;
            switch (format[formatIndex])
            {
            default:
                if (buffer[bufferIndex] != '%')
                {
                    flag = 1;
                }
                else
                {
                    bufferIndex++;
                }
                break;
            case 'd':
            case 'i':
                auxNum = va_arg(args, int *);
                auxIndex = bufferIndex;
                bufferIndex += stringToInt(buffer + bufferIndex, auxNum);
                if (bufferIndex > auxIndex)
                {
                    result++;
                }
                else
                {
                    flag = 1;
                }
                formatIndex++;
                break;
            case 'c':
                auxChar = va_arg(args, char *);
                if (isAlpha(buffer[bufferIndex]))
                {
                    *auxChar = buffer[bufferIndex++];
                    result++;
                }
                else
                {
                    *auxChar = '\0';
                    flag = 1;
                }
                formatIndex++;
                break;
            case 's': //String hasta espacio
                auxChar = va_arg(args, char *);
                auxIndex = bufferIndex;
                while (!isSpace(buffer[bufferIndex]) && buffer[bufferIndex] != '\0')
                {
                    *auxChar = buffer[bufferIndex];
                    auxChar++;
                    bufferIndex++;
                }
                if (bufferIndex > auxIndex)
                {
                    auxChar[auxIndex] = '\0';
                    result++;
                }
                else
                {
                    auxChar[auxIndex] = '\0';
                    flag = 1;
                }
                formatIndex++;
                break;
            case 'n': //String hasta el enter
                auxChar = va_arg(args, char *);
                auxIndex = bufferIndex;
                while (buffer[bufferIndex] != '\0')
                {
                    *auxChar = buffer[bufferIndex];
                    auxChar++;
                    bufferIndex++;
                }
                if (bufferIndex > auxIndex)
                {
                    auxChar[auxIndex] = '\0';
                    result++;
                }
                else
                {
                    auxChar[auxIndex] = '\0';
                    flag = 1;
                }
                formatIndex++;
                break;
            }
        }
    }

    if (flag || (format[formatIndex] == '\0' && buffer[bufferIndex] != '\0'))
    {
        return 0;
    }

    va_end(args);
    return result;
}