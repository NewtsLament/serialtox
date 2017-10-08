/*
 *
 *  Created on: 7 Oct 2017
 *      Author: kelvin
 */

#include "SerialHandler.h"

int main(int, char*[])
{
	SerialHandler ser = SerialHandler("/dev/ttyUSB0",57600);
	while (1)
	{
		if (ser.active())
		{
			std::cout << ser.getChar() << std::flush; // Print char, flush stream.
		}
	}
	return 0;
}
