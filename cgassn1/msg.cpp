#include "msg.h"
#include "util.h"

Message::Message(bool is_win_) {
	is_win = is_win;

	bl[0] = new BmpLoader("win.bmp");
	bl[1] = new BmpLoader("lose.bmp");
}

void
Message::display() {
	glEnable(GL_TEXTURE_2D);
	int idx = 0;
	if (!is_win)
		idx = 1;

	LoadTexture(idx);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0, 0.0); // Need to check
	glVertex2f(150, 350);
	glTexCoord2f(0.0, 1.0);
	glVertex2f(150, 450);

	glTexCoord2f(1.0, 1.0);
	glVertex2f(650, 450);


	glTexCoord2f(1.0, 0.0);
	glVertex2f(650, 350);
	glEnd();
}

void
Message::LoadTexture(unsigned int idx) {

	BmpLoader * tmp = bl[idx];

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, tmp->iWidth, tmp->iHeight, GL_RGB, GL_UNSIGNED_BYTE, tmp->textureData);
}

Message::~Message() {
	for (int i = 0; i < 2; i++)
		delete bl[i];
}