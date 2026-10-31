#include "HookManager.h"
#include <MinHook/MinHook.h>
#include "../Logger/Logger.h"
void HookManager::initHooks() {
	auto& hooks = getInstance().hooks;

	hooks.push_back(std::make_unique<MapItemHook::save>());
	hooks.push_back(std::make_unique<LocalPlayerHook::normalTick>());
	hooks.push_back(std::make_unique<ClientInstanceHook::update>());
	hooks.push_back(std::make_unique<LoopbackPacketSenderHook::sendToServer>());
	hooks.push_back(std::make_unique<MinecraftHook::update>());

	for (auto& hook : hooks) {
		hook->Initialize();
		MH_EnableHook(MH_ALL_HOOKS);
	}
}

void HookManager::DeleteHooks() {
	getInstance().hooks.clear(); //自動的にFuncHookクラスがデストラクタでMH_DisableHookを呼ぶ
}