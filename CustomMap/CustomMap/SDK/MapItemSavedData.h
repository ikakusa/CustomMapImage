#pragma once
#include "../../Libraries/Libs/MemUtils.h"
#undef min
#undef max
#include "../Logger/Logger.h"
struct PixelUpdate {
	int color;        // 0
	int packedPos;    // 4
};
struct SimplePixel {
	int color;
	int x;
	int y;
};
class LevelStorage;
class MapItemSavedData {
public:
	BUILD_ACCESS(__int64, mapId, 0x8); //1.26.60
public:
	void applyPixels(
		const std::vector<SimplePixel>& pixelsIn
	) {
		auto map = this;

		int* pixels = *(int**)((char*)map + 48); //1.26.60 mPixels
		for (auto& p : pixelsIn) {
			int index = p.x + (p.y << 7);

			if (pixels[index] == p.color)
				continue;

			pixels[index] = p.color;

			*(uint16_t*)((char*)map + 121) = 257; //mDirtyForSave 1.26.60
			*(uint16_t*)((char*)map + 122) = 257; //mDirtyForSave 1.26.60

			auto* taBegin = *(__int64**)((char*)map + 0x60);
			auto* taEnd = *(__int64**)((char*)map + 0x68);

			for (auto* it = taBegin; it != taEnd; it += 2) {
				if (!*it) continue;
				char* actor = (char*)*it;

				if (*(bool*)(actor + 32)) {
					*(int*)(actor + 36) = std::min(*(int*)(actor + 36), p.x);
					*(int*)(actor + 40) = std::min(*(int*)(actor + 40), p.y);
					*(int*)(actor + 44) = std::max(*(int*)(actor + 44), p.x);
					*(int*)(actor + 48) = std::max(*(int*)(actor + 48), p.y);
				}
				else {
					*(bool*)(actor + 32) = true;
					*(int*)(actor + 36) = p.x;
					*(int*)(actor + 40) = p.y;
					*(int*)(actor + 44) = p.x;
					*(int*)(actor + 48) = p.y;
				}
			}
		}
	}
	void setToLocked() {
		auto base = reinterpret_cast<uint8_t*>(this);
		if (!*(bool*)(base + 123)) //mLocked 1.26.60
		{
			*(bool*)(base + 121) = true; //mDirtyForSave 1.26.60
			*(bool*)(base + 123) = true; //mLocked 1.26.60
		}
	}

	void save(LevelStorage* ls) {
		using func_t = void(__fastcall*)(MapItemSavedData*, LevelStorage*); //1.26.60
		func_t func = reinterpret_cast<func_t>(SigScan("55 41 56 56 57 53 48 81 ec ? ? ? ? 48 8d ac 24 ? ? ? ? 48 c7 45 ? ? ? ? ? 48 89 d6 48 89 cf 48 8d 1d ? ? ? ? 48 89 5d ? 0f 57 c0 0f 11 45 ? 48 8b 0d ? ? ? ? 48 8b 01 48 8b 40 ? ba ? ? ? ? ff 15 ? ? ? ? 48 85 c0 0f 84 ? ? ? ? 48 89 00 48 89 40 ? 48 89 40 ? 66 c7 40 ? ? ? 48 89 45 ? 48 8d 55"));
		func(this, ls);
	}
};