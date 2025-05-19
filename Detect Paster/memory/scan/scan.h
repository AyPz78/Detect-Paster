#pragma once
#include "../../includes.h"
class scan
{
	public:

		inline BYTE getByte(const char* pattern);
		inline PVOID  FindPatternInRange(uintptr_t start, uintptr_t end, const char* pattern);
	
};
inline scan* scan_instance;

