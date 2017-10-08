/*
 * CharToXHandler.cpp
 *
 *  Created on: 8 Oct 2017
 *      Author: kelvin
 */

#include "CharToXHandler.h"

CharToXHandler::CharToXHandler(char * disp)
{
	display = XOpenDisplay(disp);
	if(display == NULL)
	{
		throw std::runtime_error("Failed to open display: " + std::string(1, *disp));
	}

	root = XDefaultRootWindow(display);
	updateFocus();
}

void CharToXHandler::updateFocus()
{
	int revert;
	XGetInputFocus(display, &focus, &revert);
}

void CharToXHandler::close()
{
	XCloseDisplay(display);
}

XKeyEvent CharToXHandler::createKeyEvent(bool press, int keycode, int mod)
{
	XKeyEvent event;

	event.display     = display;
	event.window      = focus;
	event.root        = root;
	event.subwindow   = None;
	event.time        = CurrentTime;
	event.x           = 1;
	event.y           = 1;
	event.x_root      = 1;
	event.y_root      = 1;
	event.same_screen = True;
	event.keycode     = XKeysymToKeycode(display, keycode);
	event.state       = mod;

	if(press)
	  event.type = KeyPress;
	else
	  event.type = KeyRelease;

	return event;
}

void CharToXHandler::write(char p[2])
{
	updateFocus();
	int temp = ucharToUint(p);
	XKeyEvent event1 = createKeyEvent(true, temp, 0);
	XKeyEvent event2 = createKeyEvent(false, temp, 0);
	XSendEvent(event1.display, InputFocus, True, KeyPressMask, (XEvent*)&event1);
	XSendEvent(event2.display, InputFocus, True, KeyPressMask, (XEvent*)&event2);
}

void CharToXHandler::press(char p[2])
{
	updateFocus();
	XKeyEvent event1 = createKeyEvent(true, ucharToUint(p), 0);
	XSendEvent(event1.display, InputFocus, True, KeyPressMask, (XEvent*)&event1);
}

void CharToXHandler::release(char p[2])
{
	updateFocus();
	XKeyEvent event1 = createKeyEvent(false, ucharToUint(p), 0);
	XSendEvent(event1.display, InputFocus, True, KeyPressMask, (XEvent*)&event1);
}

int CharToXHandler::ucharToUint(char p[2])
{
	// Maybe put some checking here?
	// Most unicode should work properly with X keysyms.
	int temp = 0;
	temp = p[1];
	temp += p[0] * 0x0100;
	return temp;
}
