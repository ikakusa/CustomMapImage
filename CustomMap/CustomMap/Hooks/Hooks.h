#pragma once
#include <vector>
#include <string>
#include <memory>
#include "../dllmain.h"

#include "../SDK/SDK.h"

#include <MemUtils.h>

class FuncHook;
class Hook {
public:
	std::string name = "";
	Hook(const char* a) {
		name = a;
	};
	virtual bool Initialize() = 0;
};