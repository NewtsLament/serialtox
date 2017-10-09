#include <unistd.h>
#include "SerialHandler.h"
#include "CharToXHandler.h"

int main(int argc, char * argv[])
{
	int c;
	extern char *optarg;
	std::string ttyPath = "";
	int ttyBaud = 0;
    while( ( c = getopt (argc, argv, "+d:b:") ) != -1 )
    {
    	switch (c)
    	{
    	case 'd' :	ttyPath = optarg;
    				break;
    	case 'b' :	ttyBaud = std::stoi(optarg);
    				break;
    	}
    }

	SerialHandler ser = SerialHandler(ttyPath,ttyBaud);
	CharToXHandler xchar = CharToXHandler();
	char temp[2];
	temp[0] = 0;
	while (1)
	{

		if (ser.active())
		{
			temp[1] = ser.getChar();
			std::cout << (unsigned short int)temp[1] << ", " << std::flush; // Print char, flush stream.
//			xchar.write(temp);
		}
	}
	ser.closeSerial();
	xchar.close();
	return 0;
}
