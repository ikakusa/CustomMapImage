#include "ItemStack.h"

CompoundTag* ItemStack::getUserData() {
	return Memory::at<CompoundTag*>(this, 0x10);
};