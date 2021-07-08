#ifndef MYCONIO_H_INCLUDED
#define MYCONIO_H_INCLUDED
#include <termios.h>
#include <stdio.h>
#include <unistd.h>
//#include <string.h>
//#include <stdlib.h>
#define RED   "\x1B[31m"
#define GREEN   "\x1B[32m"
#define YELLOW   "\x1B[33m"
#define BLUE   "\x1B[34m"
#define MAGENTA   "\x1B[35m"
#define CYAN   "\x1B[36m"
#define WHITE   "\x1B[37m"
#define RESET "\x1B[0m"
#define BLACK "\x1b[30m"
//gotoxy() function definition
void gotoxy(int x,int y)
{
    printf("%c[%d;%df",0x1B,y,x);
}
void clrscr(void)
{
    system("clear");
}
static struct termios old, new;

/* Initialize new terminal i/o settings */
void initTermios(int echo)
{
  tcgetattr(0, &old); //grab old terminal i/o settings
  new = old; //make new settings same as old settings
  new.c_lflag &= ~ICANON; //disable buffered i/o
  new.c_lflag &= echo ? ECHO : ~ECHO; //set echo mode
  tcsetattr(0, TCSANOW, &new); //apply terminal io settings
}

/* Restore old terminal i/o settings */
void resetTermios(void)
{
  tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo)
{
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}

/*
Read 1 character without echo
getch() function definition.
*/
char getch(void)
{
  return getch_(0);
}

/*
Read 1 character with echo
getche() function definition.
*/
char getche(void)
{
  return getch_(1);
}
void clean_stdin()
{
        int stdin_copy = dup(STDIN_FILENO);
        /* remove garbage from stdin */
       /* tcdrain(stdin_copy);*/
        tcflush(stdin_copy, TCIFLUSH);
        close(stdin_copy);
}





#endif // MYCONIO_H_INCLUDED
