#ifndef MSG_H
#define MSG_H

#include "BmpLoader.h"

class Message{
private:
	bool is_win;

	unsigned int textureID;
	BmpLoader* bl[2];
public:
	Message(bool);
	void display(void);
	void LoadTexture(unsigned int);
	~Message();
};
#endif /* msg_h */