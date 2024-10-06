#include "HookManager.h"
void HookManager::initHooks() {
	auto start = std::chrono::steady_clock::now();
	hooks.push_back(new ConnectionRequest::create);

	for (auto hook : hooks) {
		hook->Initialize();
		MH_EnableHook(MH_ALL_HOOKS);
	}
	auto end = std::chrono::steady_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	writelog("%ld", duration.count());
}