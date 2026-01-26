#pragma once
class ItemStack;
class Level;
class PlayerInventory;
class GameMode;
class Actor {
public:
    BUILD_ACCESS(Level*, level, 0x1D8); //1.21.132
};

class Player : public Actor {
public:
	BUILD_ACCESS(PlayerInventory*, supplies, 0x5B8); //1.21.132
	BUILD_ACCESS(GameMode*, gameMode, 0xA78); //1.21.132
public:
	ItemStack* getSelectedItem() { //1.21.132
		auto supplies = this->supplies;
		int selected = supplies->selectedSlot;
		if (supplies->selectedContainerID) {
			return nullptr;
		}
		return supplies->inventory->getItem(selected);
	}
};

class LocalPlayer : public Player {
public:
	void displayClientMessage(const char* str, ...) {
		va_list arg;
		va_start(arg, str);
		int lengthNeeded = _vscprintf(str, arg) + 1;
		if (lengthNeeded >= 300) {
			va_end(arg);
			return;
		}
		char message[300];
		vsnprintf_s(message, sizeof(message), _TRUNCATE, str, arg);
		const std::string& msg(message);
		char bruh[28]{};
		CallVFunc<199, void, const std::string&, char*>(this, msg, bruh);
		va_end(arg);
	}
};