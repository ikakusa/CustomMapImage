#pragma once
#include "../HookManager.h"

namespace MapItemHook {
	class save : public Hook {
	private:
		static inline std::unique_ptr<FuncHook> funcPtr;
	public:
		save() : Hook("MapItemSavedData::save") {};
		static __int64 handle(MapItemSavedData* a1, __int64* a2);
		bool Initialize() override { //1.26.60
			uintptr_t address = SigScan("55 41 56 56 57 53 48 81 EC B0 00 00 00 48 8D AC 24 80 00 00 00 48 C7 45 28 FE FF FF FF 48 89 D6 48 89 CF 48 8D 1D");
			return CreateHook(funcPtr, address, handle);
		}
	};
	class onSave : public Hook { //ituka tukau
	private:
		static inline std::unique_ptr<FuncHook> funcPtr;
	public:
		onSave() : Hook("MapDataManager::onSaveLevelData") {};
		static __int64 handle(MapDataManager* a1, LevelStorage* a2);
		bool Initialize() override { //1.26.60
			uintptr_t address = SigScan("41 56 56 57 53 48 83 EC 28 48 8B 59 78");
			return CreateHook(funcPtr, address, handle);
		}
	};
}

namespace MinecraftHook {
	class update : public Hook {
	private:
		static inline std::unique_ptr<FuncHook> funcPtr;
	public:
		update() : Hook("Minecraft::update") {};
		static void handle(Minecraft* a1);
		bool Initialize() override { //1.26.60
			uintptr_t address = SigScan("55 41 57 41 56 41 55 41 54 56 57 53 48 81 EC 38 01 00 00 48 8D AC 24 80 00 00 00 0F 29 BD A0 00 00 00 66");
			return CreateHook(funcPtr, address, handle);
		}
	};
}

namespace LocalPlayerHook {
	class normalTick : public Hook {
	private:
		static inline std::unique_ptr<FuncHook> funcPtr;
	public:
		normalTick() : Hook("LocalPlayer::normalTick") {};
		static __int64 handle(LocalPlayer* _this);
		bool Initialize() override { //1.26.60
			uintptr_t address = SigScan("55 41 57 41 56 41 55 41 54 56 57 53 48 81 EC E8 02 00 00 48 8D AC 24 80 00 00 00 44 0F 29 85 50 02 00 00 66");
			return CreateHook(funcPtr, address, handle);
		}
	};
}

namespace ClientInstanceHook {
	class update : public Hook {
	private:
		static inline std::unique_ptr<FuncHook> funcPtr;
	public:
		update() : Hook("ClientInstance::update") {};
		static __int64 handle(ClientInstance* _this, bool a, bool b);
		bool Initialize() override { //1.26.60
			uintptr_t address = SigScan("55 41 57 41 56 41 55 41 54 56 57 53 48 81 EC 08 05 00 00 48 8D AC 24 80 00 00 00 0F 29 B5 70 04 00 00 48 C7 85 68 04 00 00 FE FF FF FF 45");
			return CreateHook(funcPtr, address, handle);
		}
	};
}
namespace LoopbackPacketSenderHook {
	class sendToServer : public Hook {
	private:
		static inline std::unique_ptr<FuncHook> funcPtr;
	public:
		sendToServer() : Hook("LoopbackPacketSender::sendToServer") {};
		static __int64 handle(LoopbackPacketSender* _this, Packet* packet);
		bool Initialize() override { //1.26.60
			uintptr_t address = SigScan("41 57 41 56 41 54 56 57 55 53 48 81 EC 90 01");
			return CreateHook(funcPtr, address, handle);
		}
	};
}