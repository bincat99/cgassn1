#ifndef MSG_H
#define MSG_H

#include "BmpLoader.h"
#include "util.h"

class Message{
private:

	unsigned int textureID;
	BmpLoader* bl[3];
public:
	Message(void);
	void display(bool, position);
	void LoadTexture(unsigned int);
	~Message();
};
#endif /* msg_h */
