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

struct ToastData {
public:
	std::string title;
	std::string message;
	ToastNotification toast;
	bool display;
	ToastData(std::string a, std::string title, ToastNotification notif, bool display) : message(a), title(title), toast(notif), display(display) {};
};

#define COLOR_H "ﾂｧh"
#define COLOR_E "ﾂｧe"
#define COLOR_C "ﾂｧc"
#define COLOR_4 "ﾂｧ4"

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
	static inline std::vector<ToastData> toasts;
	static inline std::string getFormatted(const char* str, ...) {
		va_list arg;
		va_start(arg, str);
		int lengthNeeded = _vscprintf(str, arg) + 1;
		if (lengthNeeded >= 1000) {
			va_end(arg);
			return "";
		}
		char message[1000];
		vsnprintf_s(message, sizeof(message), _TRUNCATE, str, arg);
		const std::string& msg(message);
		va_end(arg);
		return msg;
	}
	static inline std::wstring strToWstr(const std::string& str)
	{

		std::wstring ret;
		//一度目の呼び出しは文字列数を知るため
		auto result = MultiByteToWideChar(CP_UTF8,
			0,
			str.c_str(),//入力文字列
			str.length(),
			nullptr,
			0);
		ret.resize(result);//確保する
		//二度目の呼び出しは変換
		result = MultiByteToWideChar(CP_UTF8,
			0,
			str.c_str(),//入力文字列
			str.length(),
			ret.data(),
			ret.size());
		return ret;
	}

	static __forceinline std::string joinString(const std::vector<std::string>& vec, const std::string& delimiter) {
		std::ostringstream os;
		for (size_t i = 0; i < vec.size(); ++i) {
			os << vec[i];
			if (i < vec.size() - 1) {
				os << delimiter;
			}
		}
		return os.str();
	}
	static __forceinline void toast(std::string str, bool displayMessage = true, std::string title = "CustomMapImage") {
		try {
			XmlDocument toastXml = ToastNotificationManager::GetTemplateContent(ToastTemplateType::ToastText02);
			XmlNodeList textElements = toastXml.GetElementsByTagName(xorstr_(L"text"));
			textElements.Item(0).InnerText(strToWstr(title));
			textElements.Item(1).InnerText(strToWstr(str));
			ToastNotification toast(toastXml);
			data::toasts.push_back(ToastData(str, title, toast, displayMessage));
		}
		catch (...) {
			writelog("%s", str.c_str());
		}
	}
};

extern data gameData;