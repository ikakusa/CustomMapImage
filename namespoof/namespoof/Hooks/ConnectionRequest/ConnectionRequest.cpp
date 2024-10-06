#include "ConnectionRequest.h"

void ConnectionRequest::create::handle(__int64* a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5, __int64 a6, __int64 a7, __int64 a8, __int64 a9, __int64 a10, std::string* deviceId, int a12, int a13, int a14, __int64 a15, char a16, char a17, __int64 a18, int a19, std::string* platformUserId, std::string* thirdPartyName, bool thirdPartyNameOnly, __int64 a23, __int64 a24, __int64 a25, char a26) {
	static auto oFunc = funcPtr->GetFastcall<void, __int64*, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, std::string*, int, int, int, __int64, char, char, __int64, int, std::string*, std::string*, bool, __int64, __int64, __int64, char>();

	*thirdPartyName = "Ellenjoe331451";
	return oFunc(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, deviceId, a12, a13, a14, a15, a16, a17, a18, a19, platformUserId, thirdPartyName, false, a23, a24, a25, a26);
}