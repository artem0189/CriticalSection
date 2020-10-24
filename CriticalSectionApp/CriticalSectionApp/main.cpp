#include <windows.h>
#include <iostream>

#define MEMORY_NAME L"SharedMemory"

CRITICAL_SECTION cSection;
std::wstring filePathFirstProcess = L"C:/Users/USER/Desktop/лб/осисп/3/CriticalSection/CriticalSectionApp/Debug/FirstProcess.exe";
std::wstring filePathSecondProcess = L"C:/Users/USER/Desktop/лб/осисп/3/CriticalSection/CriticalSectionApp/Debug/SecondProcess.exe";

STARTUPINFO infoFirstProcess, infoSecondProcess;
PROCESS_INFORMATION firstProcess, secondProcess;

int main()
{
	InitializeCriticalSection(&cSection);

	HANDLE shmem = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(cSection), MEMORY_NAME);
	LPVOID pBuffer = MapViewOfFile(shmem, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(cSection));
	CopyMemory(pBuffer, &cSection, sizeof(cSection));

	std::wstring filePath1(L"C:/Users/USER/Desktop/лб/осисп/3/CriticalSection/CriticalSectionApp/Debug/FirstProcess.exe");

	CreateProcess(NULL, &filePathFirstProcess[0], NULL, NULL, FALSE, 0, NULL, NULL, &infoFirstProcess, &firstProcess);
	CreateProcess(NULL, &filePathSecondProcess[0], NULL, NULL, FALSE, 0, NULL, NULL, &infoSecondProcess, &secondProcess);

	WaitForSingleObject(firstProcess.hProcess, INFINITE);
	WaitForSingleObject(secondProcess.hProcess, INFINITE);

	UnmapViewOfFile(pBuffer);
	CloseHandle(shmem);
	DeleteCriticalSection(&cSection);
}