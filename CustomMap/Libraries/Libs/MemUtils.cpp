#include "MemUtils.h"
#include <Psapi.h>

void MemoryUtils::init() {
	MH_Initialize();
    Memory::setProcess("Minecraft.windows.exe");
	isInitialized = true;
}

void MemoryUtils::restore() {
	MH_DisableHook(MH_ALL_HOOKS);
	MH_RemoveHook(MH_ALL_HOOKS);
	MH_Uninitialize();
}
uintptr_t MemoryUtils::findSig(std::string_view signature) {
    const auto parsed = Memory::parseSig(signature);
    auto base = Memory::getBase();
    auto length = Memory::getSize();
    auto end = base + length;

    auto result = Memory::findSig(base, end, parsed);
    return result;
}