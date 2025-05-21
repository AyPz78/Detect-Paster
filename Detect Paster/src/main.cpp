#include "../includes.h"


void init()
{
    //here we will just detect a simple jmp by minhook 
	uintptr_t base = (uintptr_t)GetModuleHandleA(0);
    PVOID OnlineTelemetry = scan_instance->FindPatternInRange(
        base + 0x2000000,
        base + 0xFFFFFFFFF,
        "8B CF E8 ? ? ? ? E8 ? ? ? ? 80 3D ? ? ? ? ? 75 1E E8 ? ? ? ? 84 C0 74 15 E8 ? ? ? ? 84 C0 74 0C E8 ? ? ? ? C6 05"
    );

    uintptr_t FinalAddress = reinterpret_cast<uintptr_t>(OnlineTelemetry) - 0x39;//this function is called most of the time Packets or something like that they use this to execute what they want

    BYTE firstByte = *(BYTE*)FinalAddress;// idk why they dont do that for this function 
    
 
    if (firstByte == 0xE9 || (firstByte == 0xFF && *(BYTE*)(FinalAddress + 1) == 0x25)) 
    { 
        MessageBoxA(0, "Hook detected: JMP instruction found", "init", MB_ICONWARNING);
    }

   
}


BOOL APIENTRY DllMain(HMODULE hModule, DWORD AttachReason, LPVOID lpReserved)
{
    UNREFERENCED_PARAMETER(lpReserved);
    if (AttachReason != DLL_PROCESS_ATTACH)
        return FALSE;

    init();

    return TRUE;
}
