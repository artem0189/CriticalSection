#include <windows.h>
#include <iostream>

#define MEMORY_NAME L"SharedMemory"

LPCRITICAL_SECTION pcSection;

int main()
{
	HANDLE shmem = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, MEMORY_NAME);
	pcSection = (LPCRITICAL_SECTION)MapViewOfFile(shmem, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(*pcSection));

	while (true) {
		if (TryEnterCriticalSection(pcSection)) {
			std::cout << "Enter critical section " << GetProcessId(GetCurrentProcess()) << std::endl;
			Sleep(1000);
			std::cout << "Leave critical section " << GetProcessId(GetCurrentProcess()) << std::endl;

			LeaveCriticalSection(pcSection);
			break;
		}
	}

	UnmapViewOfFile(pcSection);
	CloseHandle(shmem);
}