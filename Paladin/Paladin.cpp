#include "pch.h"
#pragma warning(disable : 4996)

#define ReplacePVM(a, b) helperFunctions.ReplaceFile("system\\" a ".PVM", "system\\" b ".PVM");

HelperFunctions HelperFunctionsGlobal;

wchar_t* ConvertCharToWChar(const char* value)
{
	const size_t cSize = strlen(value) + 1;
	wchar_t* wcharVariable = new wchar_t[cSize];
	mbstowcs(wcharVariable, value, cSize);
	return wcharVariable;
}

void ReplaceCharacter(const char* iniFile, const char* modDirectory, const HelperFunctions& helper)
{
	std::string iniFilePathString = modDirectory + (std::string)"\\" + iniFile + ".ini";

	const char* iniFilePathChar = iniFilePathString.c_str();
	wchar_t* iniFileFullPath = ConvertCharToWChar(iniFilePathChar);
	wchar_t* modPath = ConvertCharToWChar(modDirectory);

	helper.LoadDLLData(iniFileFullPath, modPath);
	delete[] iniFileFullPath;
	delete[] modPath;
}

extern "C"
{
	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{
		ReplaceCharacter("PaladinAmy", path, helperFunctions);
		std::string fullPath = path + (std::string)"\\welds.ini";
		helperFunctions.RegisterCharacterWelds(Characters_Amy, fullPath.c_str());
		WriteData<1>((int*)0x4867C0, 0xC3);
		ReplacePVM("amy", "PAmy");
	}

	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer };
}