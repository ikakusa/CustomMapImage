#pragma once
class ItemStack;
class Level;
class PlayerInventory;
class GameMode;
class Actor {
public:
    BUILD_ACCESS(Level*, level, 0x1D8); //1.21.132
	//std::string getNametag() //1.21.132
	//{
	//	std::string a;
	//	using fn = __int64(__thiscall*)(Actor*, std::string*);
	//	auto funfun = reinterpret_cast<fn>(SigScan("48 89 5C 24 08 48 89 74 24 18 48 89 7C 24 20 55 41 56 41 57 48 8D 6C 24 B9 48 81 EC E0 00 00 00 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 45 3F 48 8B F2"));
	//	funfun(this, &a);
	//	return a;
	//}
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