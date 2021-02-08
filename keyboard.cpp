#include <signal.h>
#include <stdio.h>
#include <stropts.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <sys/types.h>
#include <termios.h>

namespace io {

static struct termios myold, mynew;

/* Initialize new terminal i/o settings */
void initTermios(int echo) {
  tcgetattr(0, &myold);     /* grab old terminal i/o settings */
  mynew = myold;            /* make new settings same as old settings */
  mynew.c_lflag &= ~ICANON; /* disable buffered i/o */
  mynew.c_lflag &= echo ? ECHO : ~ECHO; /* set echo mode */
  tcsetattr(0, TCSANOW, &mynew); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void) { tcsetattr(0, TCSANOW, &myold); }

int _kbhit() {
  static const int STDIN = 0;
  static bool initialized = false;

  if (!initialized) {
    // Use termios to turn off line buffering
    termios term;
    tcgetattr(STDIN, &term);
    term.c_lflag &= ~ICANON;
    tcsetattr(STDIN, TCSANOW, &term);
    setbuf(stdin, NULL);
    initialized = true;
  }

  int bytesWaiting;
  ioctl(STDIN, FIONREAD, &bytesWaiting);
  return bytesWaiting;
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo) {
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}

/* Read 1 character without echo */
char getch(void) { return getch_(0); }

/* Read 1 character with echo */
char getche(void) { return getch_(1); }

char readKeyboard() {
  if (_kbhit()) {
    char c = getche();
    return c;
  }
  return '\0';
}
}
