#include <list>

class MapItemSavedData;
class CompoundTag;
class LevelStorage {
private:
	char pad_[0x8];
};
class MapDataManager {
public:
	BUILD_ACCESS(LevelStorage*, levelStorage, 0x10);
};
class Level {
public:
	MapItemSavedData* getMapSavedData(CompoundTag* tag) { //1.26.60
		return CallVFunc<268, MapItemSavedData*, CompoundTag*>(this, tag);
	}
	MapDataManager* getMapDataManager() { //1.26.60
		return CallVFunc<400, MapDataManager*>(this);
	}
	LevelStorage* getLevelStorage() { //1.26.60
		return CallVFunc<170, LevelStorage*>(this);
	}
	bool hasLevelStorage() { //1.26.60
		return CallVFunc<169, bool>(this);
	}
};