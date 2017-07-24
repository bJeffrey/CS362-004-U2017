#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

/********************************************
Relevant ascii values
[ = 91
( = 40
{ = 123
  = 32
a = 97
x = 120
} = 125
) = 41
] = 93
********************************************/
char inputChar()
{
      // random() is part of posix and not available on windows
      unsigned int min = 32;
      unsigned int max = 125;
      unsigned int asciiValue;
      char asciiValueToChar;
      unsigned int randNum;
      unsigned int range = 1 + max - min;
      unsigned int buckets = RAND_MAX / range;
      unsigned int limit = buckets * range;

      do{
          randNum = random();
      //     randNum = rand();
      }while(randNum >= limit);

      asciiValue = min + (randNum / buckets);
      asciiValueToChar = asciiValue;
      return asciiValueToChar;
}


char *inputString()
{
    char* str = malloc(5);
    memset(str, '\0', sizeof(char) * 5);

    // random() is part of posix and not available on windows
    unsigned int min = 0;
    unsigned int max = 10;
    unsigned int i;
    unsigned int randNum;
    unsigned int range = 1 + max - min;
    unsigned int buckets = RAND_MAX / range;
    unsigned int limit = buckets * range;
    int counter = 0;
    char strChoices[] = "iarexspzktl";

    while(counter < 5){

          do{
                randNum = random();
                //     randNum = rand();
          }while(randNum >= limit);

          i = min + (randNum / buckets);
          str[counter] = strChoices[i];
          counter++;
   }
   /*
   str[0] = 'r';
   str[1] = 'e';
   str[2] = 's';
   str[3] = 'e';
   str[4] = 't';
   */

    return str;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
        tcCount++;
        c = inputChar();
        s = inputString();
        printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

        if (c == '[' && state == 0)
            state = 1;
        if (c == '(' && state == 1)
            state = 2;
        if (c == '{' && state == 2)
            state = 3;
        if (c == ' '&& state == 3)
            state = 4;
        if (c == 'a' && state == 4)
            state = 5;
        if (c == 'x' && state == 5)
            state = 6;
        if (c == '}' && state == 6)
            state = 7;
        if (c == ')' && state == 7)
            state = 8;
        if (c == ']' && state == 8)
            state = 9;

    if (s[0] == 'r' && s[1] == 'e' && s[2] == 's' && s[3] == 'e' && s[4] == 't' && s[5] == '\0' && state == 9)
    {
          printf("error ");
          free(s);
          exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
