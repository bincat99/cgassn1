#ifndef MSG_H
#define MSG_H

#include "BmpLoader.h"
#include "util.h"

class Message{
private:

public:
	Message(void);
	void display(bool, position);
	~Message();
};
#endif /* msg_h */
