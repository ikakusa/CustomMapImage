#include "ActorHook.h"
#include "../../Logger/Logger.h"

void ActorHook::baseTick::handle(Actor* a1, __int64 entityCtx) {
	static auto oFunc = funcPtr->GetFastcall<void, Actor*, __int64>();

	if (a1) {
		gameData.setLevel(a1->getLevel());
		if (gameData.getLevel()) {
			gameData.getLevel()->getLevelStorage();
		}
	}

	return oFunc(a1, entityCtx);
}