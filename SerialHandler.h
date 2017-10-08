#ifndef __SERIALHANDLER_H_INCLUDED__
#define __SERIALHANDLER_H_INCLUDED__

#include <iostream>   /* Standard input/output definitions */
#include <string>
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <cerrno>   /* Error number definitions */
#include <termios.h>
#include <unistd.h>

class SerialHandler
{
  public:
  SerialHandler(std::string portPath, unsigned int baudRate);
  bool active(void);
  char getChar(void);
  void closeSerial(void);
  private:
  int initSerial(void);
  int fport;
  unsigned int baudR;
  std::string portP;
  char data;
};

#endif
