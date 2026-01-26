#include "HookManager.h"
#include <MinHook/MinHook.h>
#include "../Logger/Logger.h"
void HookManager::initHooks() {
	hooks.push_back(new MapItemHook::save());
	hooks.push_back(new LocalPlayerHook::normalTick());
	hooks.push_back(new ClientInstanceHook::update());
	hooks.push_back(new LoopbackPacketSenderHook::sendToServer());
	for (auto hook : hooks) {
		hook->Initialize();
		MH_EnableHook(MH_ALL_HOOKS);
	}
}