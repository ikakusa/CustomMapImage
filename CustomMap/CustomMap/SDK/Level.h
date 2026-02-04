#include <list>

class MapItemSavedData;
class CompoundTag;
class LevelStorage {

};
class MapDataManager {
public:
};
class Level {
public:
	MapItemSavedData* getMapSavedData(CompoundTag* tag) {
		return CallVFunc<261, MapItemSavedData*, CompoundTag*>(this, tag);
	}
	MapDataManager* getMapDataManager() {
		return CallVFunc<390, MapDataManager*>(this);
	}
};