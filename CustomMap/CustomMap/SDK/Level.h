#pragma once
#include "../../Libraries/Libs/MemUtils.h"

class ItemStack;
class CompoundTag;

class LevelStorageManager {
};
class MapItemSaveData {
	void setToLocked() {
		if (!*((uintptr_t*)this + 123))
		{
			*(uintptr_t*)((char*)this + 121) = 257;
			*((uintptr_t*)this + 123) = 1;
		}
	}

	void setPixel(uint32_t color, uint32_t x, uint32_t y) {
		using save = void(*)(MapItemSaveData*, uint32_t, uint32_t, uint32_t);
		static save func = reinterpret_cast<save>(SigScan("66 C7 41 ?? ?? ?? 44 8B"));
		return func(this, color, x, y);
	}

	void save(LevelStorageManager* levelStorage) {
		using save = void(*)(MapItemSaveData*, LevelStorageManager*);
		static save func = reinterpret_cast<save>(SigScan("48 89 5C 24 ?? 48 89 74 24 ?? 55 57 41 56 48 8D 6C 24 B9 48 81 EC ?? ?? ?? ?? 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 45 ?? 48 8B F2 48 8B F9 0F 57 C0 0F 11 45 F7"));
		return func(this, levelStorage);
	}
};


class Level {
public:
	MapItemSaveData* getMapSavedData(CompoundTag* compoundTag) {
		using getDamageVal = MapItemSaveData*(*)(Level*, CompoundTag*);
		static getDamageVal func = reinterpret_cast<getDamageVal>(SigScan("48 89 5C 24 10 57 48 83 EC 20 48 8B 01 48 8B F9 48 8D"));
		return func(this, compoundTag);
	};
	LevelStorageManager* getLevelStorage() {
		return Memory::at<LevelStorageManager*>(this + 0xF0, 0x8);
	};
};