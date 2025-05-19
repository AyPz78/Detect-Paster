#include "scan.h"


inline BYTE scan::getByte(const char* pattern) {
	return static_cast<BYTE>(std::strtoul(pattern, nullptr, 16));
}

inline PVOID  scan::FindPatternInRange(uintptr_t start, uintptr_t end, const char* pattern)
{
	const char* pat = pattern;
	uintptr_t firstMatch = 0;
	for (uintptr_t pCur = start; pCur < end; pCur++)
	{
		if (!*pat) return (PVOID)firstMatch;
		if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == getByte(pat))
		{
			if (!firstMatch) firstMatch = pCur;
			if (!pat[2]) return (PVOID)firstMatch;
			if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?') pat += 3;
			else pat += 2;
		}
		else
		{
			pat = pattern;
			firstMatch = 0;
		}
	}
	return nullptr;
}