#include "MemUtils.h"
#include <Psapi.h>
#include <Libraries.h>

void MemoryUtils::init() {
	MH_Initialize();
	isInitialized = true;
}

void MemoryUtils::restore() {
	MH_DisableHook(MH_ALL_HOOKS);
	MH_RemoveHook(MH_ALL_HOOKS);
	MH_Uninitialize();
}