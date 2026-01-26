class MapItemSavedData;
class CompoundTag;
class LevelStorage {

};
class Level {
public:
	MapItemSavedData* getMapSavedData(CompoundTag* tag) {
		return CallVFunc<261, MapItemSavedData*, CompoundTag*>(this, tag);
	}
	//LevelStorage* getLevelStorage() {
	//	using get = __int64*(__fastcall*)(__int64*, __int64*);
	//	static get aa = reinterpret_cast<get>(SigScan("48 89 6C 24 18 57 48 83 EC 20 33 C0 48 8B FA 48 89 02 48 8B E9 48 89 42 08 48 89 42 10 48 8B 51 08"));
	//	__int64* oo{};
	//	__int64 ommc = *(uintptr_t*)this + 0x78;
	//	auto result = aa(reinterpret_cast<__int64*>(ommc), oo);
	//	return 0;
	//	//return reinterpret_cast<LevelStorage*>(aa(reinterpret_cast<__int64*>(*(uintptr_t*)this + 0x78), oo)[2]);
	//}
};