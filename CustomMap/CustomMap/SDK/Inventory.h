#pragma once
class ItemStack;
class Inventory {
public:
	ItemStack* getItem(int slot) { //1.21.132
		return CallVFunc<7, ItemStack*, int>(this, slot);
	}
};
class PlayerInventory {
public:
	BUILD_ACCESS(int, selectedSlot, 0x10); //1.21.132
	BUILD_ACCESS(char, selectedContainerID, 0xB0); //1.21.132
	BUILD_ACCESS(Inventory*, inventory, 0xB8); //1.21.132
};