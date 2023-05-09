#include "nvse/PluginAPI.h"

NVSEInterface* g_nvseInterface{};


void SafeWrite8(UInt32 addr, UInt32 data)
{
	UInt32	oldProtect;

	VirtualProtect((void*)addr, 4, PAGE_EXECUTE_READWRITE, &oldProtect);
	*((UInt8*)addr) = data;
	VirtualProtect((void*)addr, 4, oldProtect, &oldProtect);
}

void SafeWriteBuf(UInt32 addr, const char* data, UInt32 len)
{
	UInt32	oldProtect;

	VirtualProtect((void*)addr, len, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((void*)addr, data, len);
	VirtualProtect((void*)addr, len, oldProtect, &oldProtect);
}

bool NVSEPlugin_Query(const NVSEInterface* nvse, PluginInfo* info)
{
	info->infoVersion = PluginInfo::kInfoVersion;
	info->name = "HighResWaterFog";
	info->version = 11	;

	return true;
}

bool NVSEPlugin_Load(NVSEInterface* nvse)
{
	if (!nvse->isEditor) {

		SafeWriteBuf(0xB6C661, "\x8B\x0D\x30\x94\x1F\x01", 6);// width
		SafeWriteBuf(0xB6C667, "\x8B\x15\x34\x94\x1F\x01", 6);// height
	}

	return true;
}
