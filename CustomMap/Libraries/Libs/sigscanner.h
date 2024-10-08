#pragma once
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <cstdint>
#include <cstring>
#include <immintrin.h>
#include <xutility>
#include <string>
#include <vector>
#include <ranges>
#include <optional>
#include <algorithm>
#include <future>
#include <Psapi.h>


#define INRANGE(x,a,b)		(x >= a && x <= b) 
#define getBits( x )		(INRANGE(x,'0','9') ? (x - '0') : ((x&(~0x20)) - 'A' + 0xa))
#define getByte( x )		(getBits(x[0]) << 4 | getBits(x[1]))

typedef unsigned char byte;
struct test {
	byte _byte;
	bool iswild;
	test(byte _byte, bool iswild) : _byte(_byte), iswild(iswild){};
};
typedef unsigned __int64 length;
typedef std::vector<test> signature;
typedef std::string_view view;

namespace Memory {
	static inline view process;

	static void setProcess(const view& input) {
		process = input;
	}

	static constexpr signature parseSig(const view& pattern) {
		signature sig;
		for (const auto& p : pattern | std::views::split(' ')) {
			if (p[0] == '\?') {
				sig.push_back({0x0, true});
			}
			else {
				byte b = getByte(p);
				sig.push_back({b, false});
			}
		}

		return sig;
	}

	static constexpr uintptr_t findSig(const length start, const length end, const signature pattern) {
		if (start >= end || pattern.empty()) return 0;

		const auto _start = (byte*)start;
		const auto _end = (byte*)end - pattern.size(); 
		const auto pattern_size = pattern.size();
		const auto &front = pattern.front(), &back = pattern.back();
		const auto Match_Side = [&front, &back, &pattern_size](byte* data) {
			if (front.iswild && back.iswild) return true;
			if (!front.iswild && !back.iswild) {
				return data[0] == front._byte && data[pattern_size - 1] == back._byte;
			}
			return (front.iswild || data[0] == front._byte) && (back.iswild || data[pattern_size - 1] == back._byte);
		};
		const auto Match_All = [&pattern, &pattern_size](byte* data) {
			for (size_t i = 1; i < pattern_size - 1; i++) {
				if (data[i] != pattern[i]._byte && !pattern[i].iswild) return false;
			}
			return true;
		};

		for (auto i = _start; i <= _end; i += 4) {
			if (Match_Side(i) && Match_All(i)) { 
				return start + (i - _start); 
			}
		}

		return 0;
	}

	template <typename Return, typename Type>
	static Return& at(Type* type, size_t offset) {
		union {
			size_t offset;
			Type* type;
			Return* ret;
		} u{};
		u.offset += offset;
		u.type = type;
		return *u.ret;
	};

	static length getBase() {
		return reinterpret_cast<length>(GetModuleHandleA(process.data()));
	}

	static length getSize() {
		static HMODULE base = (HMODULE)getBase();
		if (!base) return 0;

		MODULEINFO modules;
		if (!GetModuleInformation(GetCurrentProcess(), base, &modules, sizeof(MODULEINFO))) return 0;
		return modules.SizeOfImage;
	}
}