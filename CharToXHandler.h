#ifndef __CHARTOXHANDLER_H_INCLUDED__
#define __CHARTOXHANDLER_H_INCLUDED__

#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <stdexcept>
#include <string>

class CharToXHandler {
  public:
  CharToXHandler(void):CharToXHandler(NULL) {}
  CharToXHandler(char *disp);
  void write(char p[]);
  void press(char p[]);
  void release(char p[]);
  void close();

  private:
  Display *display;
  Window focus;
  Window root;

  XKeyEvent createKeyEvent(bool press, int keycode, int mod);
  void updateFocus();
  int ucharToUint(char p[2]);
};

#endif
