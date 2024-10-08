#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "CustomMap/SDK/SDK.h"

class data {
private:
	static inline Actor* lp = nullptr;
	static inline ClientInstance*  ci = nullptr;
	static inline Level*  level = nullptr;
public:
	static Actor* getLocalPlayer() {
		return lp;
	}
	static Level* getLevel() {
		return level;
	}
	static ClientInstance* getClientInstance() {
		return ci;
	}
	static void setClientInstance(ClientInstance* clientinstance) {
		ci = clientinstance;
	}
	static void setLocalPlayer(Actor* localplayer) {
		lp = localplayer;
	}
	static void setLevel(Level* auau) {
		level = auau;
	}
};

extern data gameData;