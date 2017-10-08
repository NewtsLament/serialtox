#include "SerialHandler.h"

SerialHandler::SerialHandler(std::string portPath, unsigned int baudRate)
{
  baudR = baudRate;
  portP = portPath;

  fport = initSerial(); // initSerial shall throw exception if something goofs up.
  data = '\0';
}

int SerialHandler::initSerial()
{
	int tempf;
	int tempMode;
	mode_t mode = O_NOCTTY;
	tempf = open(portP.c_str(), mode);
	if (tempf == -1)
	{
		throw std::ios_base::failure("Error opening serial port.");
	}
	tempMode = fcntl(tempf,F_GETFL);
	tempMode &= O_RDONLY | O_NDELAY;
	fcntl(tempf,tempMode);

	speed_t speed;

	switch(baudR) {
	    case 0		:	speed = B0;
	    				break;
	    case 50 	: 	speed = B50;
	    				break;
	    case 75 	: 	speed = B75;
						break;
	    case 110	: 	speed = B110;
						break;
	    case 134	:	speed = B134;
						break;
	    case 150	:	speed = B150;
						break;
	    case 200	:	speed = B200;
						break;
	    case 300	:	speed = B300;
						break;
	    case 600	:	speed = B600;
						break;
	    case 1200	:	speed = B1200;
						break;
	    case 1800	:	speed = B1800;
						break;
	    case 2400	:	speed = B2400;
						break;
	    case 4800	:	speed = B4800;
						break;
	    case 9600	:	speed = B9600;
						break;
	    case 19200	:	speed = B19200;
						break;
	    case 38400	:	speed = B38400;
						break;
	    case 57600	:	speed = B57600;
						break;
	    case 115200	:	speed = B115200;
	    				break;
	    case 230400	:	speed = B230400;
						break;
	    default		:	speed = B9600;
						break;
	}

	struct termios options;
	if (tcgetattr(tempf, &options) != 0)
	{
		perror("Error getting terminal attributes");
	}

	cfsetispeed(&options, speed);
	cfsetospeed(&options, speed);

	/* Setting other Port Stuff */
	options.c_cflag     &=  ~PARENB;            // Make 8n1
	options.c_cflag     &=  ~CSTOPB;
	options.c_cflag     &=  ~CSIZE;
	options.c_cflag     |=  CS8;

	options.c_cflag     &=  ~CRTSCTS;           // no flow control
	options.c_cc[VMIN]   =  1;                  // read doesn't block
	options.c_cc[VTIME]  =  5;                  // 0.5 seconds read timeout
	options.c_cflag     |=  CREAD | CLOCAL;     // turn on READ & ignore ctrl lines

	if (tcsetattr(tempf, TCSANOW, &options) != 0)
	{
		perror("Error while setting attributes");
	}

	return tempf;
}

void SerialHandler::closeSerial()
{
	close(fport);
}

bool SerialHandler::active()
{
	int temp = read(fport,&data,1);
	if (temp > 0)
	{
		return true;
	} else
	{
		if (temp == -1)
		{
			perror("Error");
		}
		return false;
	}
}

char SerialHandler::getChar()
{
	return data;
}
