#include "msg.h"
#include "util.h"
#include <string>
#include <iostream>

Message::Message() {

}

void
Message::display(bool is_win, position pos) {

	char buf[100] = { 0 };
	std::string win = "YOU WIN!! :)";
	std::string lose = "YOU LOSE T_T";
	std::string msg = "Restart : Press <R> button // Quit : Press <Q> button";
	if(is_win)
		sprintf_s(buf, win.c_str());
	else
		sprintf_s(buf, lose.c_str());
		
	renderbitmap(650, 900, GLUT_BITMAP_HELVETICA_18, buf);
	sprintf_s(buf, msg.c_str());
	renderbitmap(400, 800, GLUT_BITMAP_HELVETICA_18, buf);
}


Message::~Message() {
}
