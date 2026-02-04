#pragma once
#include "../HookManager.h"

namespace MapItemHook {
	class save : public Hook {
	private:
		static inline std::unique_ptr<FuncHook> funcPtr;
	public:
		save() : Hook("MapItemSavedData::save") {};
		static __int64 handle(MapItemSavedData* a1, __int64* a2);
		bool Initialize() override {
			uintptr_t address = SigScan("48 89 5C 24 18 55 56 57 41 56 41 57 48 8D 6C 24 C9 48 81 EC C0 00 00 00 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 45 27 48 8B FA 48 8B F1 0F");
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
		bool Initialize() override {
			uintptr_t address = SigScan("48 8B C4 48 89 58 10 48 89 70 18 48 89 78 20 55 41 54 41 55 41 56 41 57 48 8D A8 E8 FD FF FF 48 81 EC F0 02 00 00 0F 29 70 C8 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 85 D0 01 00 00 48 8B D9");
			return CreateHook(funcPtr, address, handle);
		}
	};
}

namespace MinecraftGameHook {
	class update : public Hook {
	private:
		static inline std::unique_ptr<FuncHook> funcPtr;
	public:
		update() : Hook("MinecraftGame::update") {};
		static __int64 handle(MinecraftGame* _this);
		bool Initialize() override {
			uintptr_t address = SigScan("48 8B C4 48 89 58 10 48 89 70 18 48 89 78 20 55 41 54 41 55 41 56 41 57 48 8D A8 08 FF FF FF 48 81 EC D0 01 00 00 0F 29 70 C8 0F 29 78 B8 48 8B 05");
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
		static __int64 handle(ClientInstance* _this, bool a);
		bool Initialize() override {
			uintptr_t address = SigScan("48 89 5C 24 10 48 89 74 24 18 48 89 7C 24 20 55 41 54 41 55 41 56 41 57 48 8D AC 24 F0 FB FF FF 48 81 EC 10 05 00 00 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 85 00 04 00 00 44");
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
		bool Initialize() override {
			uintptr_t address = SigScan("48 89 5C 24 18 57 48 81 EC 60 02 00 00 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 84 24 50 02 00 00 0F");
			return CreateHook(funcPtr, address, handle);
		}
	};
}