#pragma once

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include "CustomMap/SDK/SDK.h"

#include <winrt/Windows.UI.Notifications.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Data.Xml.Dom.h>
#include <winrt/Windows.UI.ViewManagement.h>
#include <winrt/Windows.ApplicationModel.Core.h>
#include <winrt/Windows.UI.Core.h>

using namespace winrt;
using namespace Windows::Data::Xml::Dom;
using namespace Windows::UI::Notifications;

class data {
private:
	static inline ClientInstance* clientInstance = nullptr;
	static inline LocalPlayer* localPlayer = nullptr;
	static inline GuiData* guiData = nullptr;
public:
	static ClientInstance* getClientInstance() {
		return clientInstance;
	}
	static LocalPlayer* getLocalPlayer() {
		return localPlayer;
	}
	static GuiData* getGuiData() {
		return guiData;
	}
public:
	static void setClientInstance(ClientInstance* ci) {
		clientInstance = ci;
	}
	static void setGuiData(GuiData* gd) {
		guiData = gd;
	}
	static void setLocalPlayer(LocalPlayer* lp) {
		localPlayer = lp;
	}
	static inline std::vector<ToastNotification> toasts;
};

extern data gameData;