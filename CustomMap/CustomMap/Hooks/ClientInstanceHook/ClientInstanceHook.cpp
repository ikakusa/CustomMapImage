#include "ClientInstanceHook.h"

void ClientInstanceHook::Update::handle(ClientInstance* clientinstance, bool a2) {
	static auto oFunc = funcPtr->GetFastcall<void, ClientInstance*, bool>();

	if (clientinstance) {
		gameData.setClientInstance(clientinstance);
		gameData.setLocalPlayer(clientinstance->getLocalPlayer());
	}

	return oFunc(clientinstance, a2);
}