#include "Actor.h"

Level* Actor::getLevel() {
	return Memory::at<Level*>(this, 0x230);
}