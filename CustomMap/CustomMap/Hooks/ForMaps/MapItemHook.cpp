#include "MapItemHook.h"
#include "../../Logger/Logger.h"
#include <sstream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <winrt/Windows.UI.Notifications.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Data.Xml.Dom.h>
#include <winrt/Windows.UI.ViewManagement.h>
#include <winrt/Windows.ApplicationModel.Core.h>
#include <winrt/Windows.UI.Core.h>
#include <atomic>
#include <chrono>

using namespace winrt;
using namespace Windows::Data::Xml::Dom;
using namespace Windows::UI::Notifications;
#include <commdlg.h>

inline uint32_t RGBAtoABGR(
	uint8_t r,
	uint8_t g,
	uint8_t b,
	uint8_t a
) {
	return (uint32_t(a) << 24)
		| (uint32_t(b) << 16)
		| (uint32_t(g) << 8)
		| uint32_t(r);
}

static int mapSize = 128;
static std::chrono::steady_clock::time_point last = std::chrono::steady_clock::now();
static std::string filePath{};
static std::vector<SimplePixel> pixels{};

static bool setMapData = false;
static bool hasUpdate = false;

__int64 MapItemHook::save::handle(MapItemSavedData* _this, __int64* storage) {
	static auto oFunc = funcPtr->GetFastcall<__int64, MapItemSavedData*, __int64*>();
	using clock = std::chrono::steady_clock;
	static bool threadStart = false;
	if (setMapData) {
		hasUpdate = true;
		_this->applyPixels(pixels);
		_this->setToLocked();
		writelog("saved: %p, return_address: %p", _this, _ReturnAddress());
	}
	return oFunc(_this, storage);
}

__int64 MinecraftGameHook::update::handle(MinecraftGame* _this) {
	static auto oFunc = funcPtr->GetFastcall<__int64, MinecraftGame*>();
	data::setMCGame(_this);
	data::setLS(_this->getLevelStorage());
	return oFunc(_this);
}

__int64 LocalPlayerHook::normalTick::handle(LocalPlayer* _this) {
	static auto oFunc = funcPtr->GetFastcall<__int64, LocalPlayer*>();
	data::setLocalPlayer(_this);
	return oFunc(_this);
}

__int64 ClientInstanceHook::update::handle(ClientInstance* _this, bool a) {
	static auto oFunc = funcPtr->GetFastcall<__int64, ClientInstance*, bool>();
	data::setClientInstance(_this);
	data::setGuiData(_this->guiData);
	static bool hasNotice = false;
	if (!hasNotice) {
		data::toast(data::getFormatted("%sCustomMapImage has been injected!", COLOR_E));
		hasNotice = true;
	}
	for (int i = 0; i < data::toasts.size(); i++) {
		auto toast = data::toasts[i];
		try {
			if (toast.display) {
				data::getGuiData()->displayClientMessage("%s<%s%s%s> %s", COLOR_H, COLOR_E, toast.title.c_str(), COLOR_H, toast.message.c_str());
			} else
				ToastNotificationManager::CreateToastNotifier().Show(toast.toast);
		}
		catch (...) {
			writelog("<%s> %s", toast.title.c_str(), toast.message.c_str());
		}
		data::toasts.erase(data::toasts.begin() + i);
	}
	if (setMapData && hasUpdate) {
		auto now = std::chrono::steady_clock::now();
		if (now - last >= std::chrono::seconds(1)) {
			hasUpdate = false;
			last = now;
			setMapData = false;
			pixels.clear();
			mapSize = 128;
			data::toast(data::getFormatted("%sSuccessfully applied to map image!", COLOR_E));
		}
	}
	return oFunc(_this, a);
}

__int64 LoopbackPacketSenderHook::sendToServer::handle(LoopbackPacketSender* _this, Packet* packet) {
	static auto oFunc = funcPtr->GetFastcall<__int64, LoopbackPacketSender*, Packet*>();
	auto lp = data::getLocalPlayer();
	auto guidata = data::getGuiData();
	if (!guidata || !lp || !packet) return oFunc(_this, packet);
	if (packet->isTextPacket()) {
		auto pkt = reinterpret_cast<TextPacket*>(packet);

		auto& body = pkt->mBody.authorAndMessage;
		std::string cmdTxt = body.message;
		if (cmdTxt._Starts_with(".")) {
			std::vector<std::string> args{};
			std::istringstream iss(cmdTxt);
			std::string s;
			while (getline(iss, s, ' ')) {
				args.push_back(s);
			}
			auto& command = args[0];
			//.set_map 0
			//128 1
			//path 2~~
			if (strcmp(command.c_str(), ".set_map") == 0) {
				if (args.size() >= 3) {
					pixels.clear();
					auto level = lp->level;
					auto ls = data::getLS();
					auto mapDataManager = level->getMapDataManager();
					auto supplies = lp->supplies;
					auto item = lp->getSelectedItem();
					//if (!item || !level->getMapSavedData(item->tag)) {
					//	data::toast(data::getFormatted("%sHold the map!", COLOR_C));
					//	return 0;
					//}
					//if (!ls) {
					//	data::toast(data::getFormatted("%sLevelStorage is null!\ntry again", COLOR_C));
					//	return 0;
					//}
					char* end{};
					mapSize = std::strtol(args[1].c_str(), &end, 10);
					if (mapSize == 0 || args[1] == end) mapSize = 128;
					filePath = data::joinString(std::vector<std::string>(args.begin() + 2, args.end()), " ");
					int w, h, channels;
					auto image = stbi_load(filePath.c_str(), &w, &h, &channels, 4);
					if (!image) {
						data::toast(data::getFormatted("%sFile not found", COLOR_C));
						return 0;
					}
					for (int y = 0; y < mapSize; ++y) {
						for (int x = 0; x < mapSize; ++x) {
							int sx = x * w / mapSize;
							int sy = y * h / mapSize;

							unsigned char* p = &image[(sy * w + sx) * 4];
							// p[0]=R p[1]=G p[2]=B p[3]=A

							uint32_t abgr = RGBAtoABGR(p[0], p[1], p[2], p[3]);

							pixels.push_back({
								(int)abgr,
								x,
								y
							});
						}
					}

					//auto mapData = level->getMapSavedData(item->tag);
					//uintptr_t* mapList = *reinterpret_cast<uintptr_t**>((uintptr_t)mapDataManager + 0x78);

					//if (mapList != nullptr) {
					//	for (uintptr_t* i = reinterpret_cast<uintptr_t*>(*mapList);
					//		i != mapList;
					//		i = reinterpret_cast<uintptr_t*>(*i))
					//	{
					//		auto v5 = reinterpret_cast<MapItemSavedData*>(i[3]);

					//		if (v5 != nullptr) {
					//			if (v5->mapId == mapData->mapId) {
					//				writelog("%lld", v5->mapId);
					//				v5->applyPixels(pixels);
					//				v5->setToLocked();
					//				v5->save(ls);
					//			}
					//		}
					//	}
					//}
					setMapData = true;
					data::toast(data::getFormatted("%sMap data is now set to %s%s!\n%sCreate an empty map to apply image!", COLOR_E, COLOR_H, filePath.c_str(), COLOR_E));
					return 0;
				}
				else {
					data::toast(data::getFormatted("%s.set_map <size> <filePath>", COLOR_C));
					return 0;
				}
			}
			else {
				data::toast(data::getFormatted("%sCommand not found", COLOR_C));
			}
			return 0;
		}
	}
	return oFunc(_this, packet);
}