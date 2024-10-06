#pragma once
#include <MemUtils.h>
#include "../Hooks.h"

namespace ConnectionRequest {
	class create : public Hook {
	private:
		static inline std::unique_ptr<FuncHook> funcPtr;
	public:
		create() : Hook("ConnectionRequest::create") {};
		static void handle(__int64* a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5, __int64 a6, __int64 a7, __int64 a8, __int64 a9, __int64 a10, std::string* deviceId, int a12, int a13, int a14, __int64 a15, char a16, char a17, __int64 a18, int a19, std::string* platformUserId, std::string* thirdPartyName, bool thirdPartyNameOnly, __int64 a23, __int64 a24, __int64 a25, char a26);
		bool Initialize() override {
			uintptr_t address = SigScan("40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 E8 FE FF FF 48 81 EC ?? ?? ?? ?? 0F 29 B4 24 ?? ?? ?? ?? 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 85 ?? ?? ?? ?? 49");
			return CreateHook(funcPtr, address, handle);
		}
	};
}