#pragma once
#include <MemUtils.h>

class Actor;
class ClientInstance {
public:
	Actor* getLocalPlayer() {
		return CallVFunc<29, Actor*>(this);
	}
};