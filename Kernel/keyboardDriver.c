#include <keyboardDriver.h>

#define IS_ALPHA(C) (C >= 'a' && C <= 'z')

static const char keyMap[128] =
    {
        0, 27, '1', '2', '3', '4', '5', '6', '7', '8',                   /* 9 */
        '9', '0', '-', '=', '\b', '\t', 'q', 'w', 'e', 'r',              /* 19 */
        't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0,                 /* 29   - Control */
        'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',                /* 39 */
        '\'', '`', 0, /*Left Shift*/ '\\', 'z', 'x', 'c', 'v', 'b', 'n', /* 49 */
        'm', ',', '.', '/', 0, /*Right Shift*/ '*',                      /*55*/
        0,                                                               /* Alt -56*/
        ' ',                                                             /* Space bar -57*/
        0,                                                               /* Caps lock -58*/
        /*- F1 key ... > */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                /* < ... F10 */
        0,                                                               /* Num lock -68*/
        0,                                                               /* Scroll Lock -69*/
        0,                                                               /* Home key -70*/
        17,                                                              /* Up Arrow -71*/
        0,                                                               /* Page Up -72*/
        '-',                                                             /* Minus -73*/
        18,                                                              /* Left Arrow */
        0,
        20,  /* Right Arrow */
        '+', /* Plus -78*/
        0,   /* 79 - End key*/
        19,  /* Down Arrow */
        0,   /* Page Down */
        0,   /* Insert Key */
        0,   /* Delete Key */
        0, 0, 0,
        0, /* F11 Key */
        0, /* F12 Key */
        0, /* All other keys are undefined */
};

static const char shiftKeyMap[128] =
    {
        0, 27, '!', '@', '#', '$', '%', '^', '&', '*',                  /* 9 */
        '(', ')', '_', '+', '\b', '\t', 'Q', 'W', 'E', 'R',             /* 19 */
        'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n', 0,                /* 29   - Control */
        'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':',               /* 39 */
        '\"', '~', 0, /*Left Shift*/ '|', 'Z', 'X', 'C', 'V', 'B', 'N', /* 49 */
        'M', '<', '>', '?', 0, /*Right Shift*/ '*',                     /*55*/
        0,                                                              /* Alt -56*/
        ' ',                                                            /* Space bar -57*/
        0,                                                              /* Caps lock -58*/
        /*- F1 key ... > */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,               /* < ... F10 */
        0,                                                              /* Num lock -68*/
        0,                                                              /* Scroll Lock -69*/
        0,                                                              /* Home key -70*/
        17,                                                             /* Up Arrow -71*/
        0,                                                              /* Page Up -72*/
        '-',                                                            /* Minus -73*/
        18,                                                             /* Left Arrow */
        0,
        20,  /* Right Arrow */
        '+', /* Plus -78*/
        0,   /* 79 - End key*/
        19,  /* Down Arrow */
        0,   /* Page Down */
        0,   /* Insert Key */
        0,   /* Delete Key */
        0, 0, 0,
        0, /* F11 Key */
        0, /* F12 Key */
        0, /* All other keys are undefined */
};

static int buffer[BUFFER_SIZE] = {0};
static int readIndex = 0;
static int writeIndex = 0;
static int elements = 0;

static int shiftKey = 0;
static int capsKey = 0;

void keyboard_handler()
{
  unsigned char keyCode;
  keyCode = getKeyCode();

  if (keyCode & 0x80) //Si acaba de soltar la tecla
  {
    if (keyCode == 182 || keyCode == 170) //Ambos shift
    {
      shiftKey = 0;
    }
  }
  else
  {
    if (keyCode == 58)
    {
      capsKey = !capsKey;
    }
    else if (keyCode == 54 || keyCode == 42) //Ambos shift
    {
      shiftKey = 1;
    }
    char c = keyMap[keyCode];
    if (c != 0)
    {
      if (shiftKey)
      {
        if (!IS_ALPHA(c) || !capsKey)
        {
          c = shiftKeyMap[keyCode];
        }
      }
      else
      {
        if (IS_ALPHA(c) && capsKey)
        {
          c = shiftKeyMap[keyCode];
        }
      }
      buffer[writeIndex] = c;
      writeIndex = (writeIndex + 1) % BUFFER_SIZE;
      if (elements < BUFFER_SIZE)
      {
        elements++;
      }
      else
      {
        readIndex = (readIndex + 1) % BUFFER_SIZE;
      }
    }
  }
}

int getChar()
{
  if (elements == 0)
  {
    return EOF;
  }
  int c;
  c = buffer[readIndex];
  readIndex = (readIndex + 1) % BUFFER_SIZE;
  elements--;
  return c;
}