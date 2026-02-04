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
	void applyPixels(
		const std::vector<SimplePixel>& pixelsIn
	) {
		auto map = this;
		int* pixels = *(int**)((char*)map + 48);

		for (auto& p : pixelsIn) {
			int index = p.x + (p.y << 7);

			if (pixels[index] == p.color)
				continue;

			pixels[index] = p.color;
			*(uint16_t*)((char*)map + 121) = 257;

			auto* taBegin = *(__int64**)((char*)map + 0x38);
			auto* taEnd = *(__int64**)((char*)map + 0x40);

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
		if (*(uint8_t*)(base + 123) == 0)
		{
			*(uint16_t*)(base + 121) = 257;
			*(uint8_t*)(base + 123) = 1;
		}
	}
};