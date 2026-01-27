class MapItemSavedData;
class CompoundTag;
class LevelStorage {

};
class Level {
public:
	MapItemSavedData* getMapSavedData(CompoundTag* tag) {
		return CallVFunc<261, MapItemSavedData*, CompoundTag*>(this, tag);
	}
};