#pragma once
class ItemStack;
class Level;
class PlayerInventory;
class GameMode;
class Actor {
public:
    BUILD_ACCESS(Level*, level, 0x200); //1.26.60
};

class Player : public Actor {
public:
	BUILD_ACCESS(PlayerInventory*, supplies, 0x5E0); //1.26.60
	BUILD_ACCESS(GameMode*, gameMode, 0xAC8); //1.26.60
public:
	ItemStack* getSelectedItem() { //1.26.60
		auto supplies = this->supplies;
		int selected = supplies->selectedSlot;
		if (supplies->selectedContainerID) {
			return nullptr;
		}
		return supplies->inventory->getItem(selected);
	}
};

class LocalPlayer : public Player {

};