#pragma once
#include "../HookManager.h"

namespace ClientInstanceHook {
	class Update : public Hook {
	private:
		static inline std::unique_ptr<FuncHook> funcPtr;
	public:
		Update() : Hook("ClientInstance::update") {};
		static void handle(ClientInstance* a1, bool a2);
		bool Initialize() override {
			uintptr_t address = SigScan("48 89 5C 24 ?? 48 89 74 24 ?? 55 57 41 54 41 56 41 57 48 8D AC 24 F0 FA FF FF 48 81 EC ?? ?? ?? ?? 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 85 ?? ?? ?? ?? 44");
			return CreateHook(funcPtr, address, handle);
		}
	};
}