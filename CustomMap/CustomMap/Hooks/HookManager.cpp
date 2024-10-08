#include "HookManager.h"
#include <MinHook/MinHook.h>
void HookManager::initHooks() {
	hooks.push_back(new ClientInstanceHook::Update());
	hooks.push_back(new ActorHook::baseTick());
	for (auto hook : hooks) {
		hook->Initialize();
		MH_EnableHook(MH_ALL_HOOKS);
	}
}