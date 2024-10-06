#pragma once

#include <cstdint>
#include <cstring>
#include <immintrin.h>
#include <xutility>
#include <Psapi.h>
#include <string>
#include <vector>
#include <ranges>
#include <optional>
#include <algorithm>
#include <future>

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

	static uintptr_t findSig(const length start, const length end, const signature pattern) {
		if (start >= end || pattern.empty()) return 0;

		auto* _start = (byte*)start;
		auto* _end = (byte*)end - pattern.size() + 1;
		std::atomic<bool> found(false);
		std::promise<uintptr_t> promise;
		auto future = promise.get_future();

		size_t thread_count = std::thread::hardware_concurrency();
		size_t chunk_size = (_end - _start) / thread_count;

		std::vector<std::future<void>> futures;
		for (size_t i = 0; i < thread_count; ++i) {
			auto* chunk_start = _start + i * chunk_size;
			auto* chunk_end = (i == thread_count - 1) ? _end : chunk_start + chunk_size;

			futures.push_back(std::async(std::launch::async, [&, chunk_start, chunk_end]() {
				if (found) return;

				auto address = std::search(chunk_start, chunk_end, pattern.begin(), pattern.end(),
					[](const byte& a, const test& b) 
					{ return b.iswild || a == b._byte; }
				);

				if (address != chunk_end && !found.exchange(true))
					promise.set_value((uintptr_t)address);
			}));
		}

		future.wait();
		return found ? future.get() : 0;
	}

	template <typename Return, typename Type>
	static Return& at(Type* type, size_t offset) {
		union {
			size_t offset;
			Type* type;
			Return* ret;
		} u;
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