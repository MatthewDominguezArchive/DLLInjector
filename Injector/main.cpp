#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>

HANDLE GetProcessHandle(const char* processName) {
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);
	if (hSnapshot == INVALID_HANDLE_VALUE) return 0;

	PROCESSENTRY32 process;
	process.dwSize = sizeof(PROCESSENTRY32);
	if (!Process32First(hSnapshot, &process)) {
		return 0;
	}

	while (Process32Next(hSnapshot, &process)) {
		if (!_stricmp(process.szExeFile, processName)) {
			HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, process.th32ProcessID);
			CloseHandle(hSnapshot);
			return hProcess;
		}
	}

	CloseHandle(hSnapshot);
	return 0;
}

int main(int argc, char* argv[]) {
	if (argc != 3) {
		std::cerr << "Usage: " << argv[0] << " <yourdll.dll> <target.exe>\n";
		return 1;
	}

	char* dllName = argv[1];
	  
	HANDLE hProcess = GetProcessHandle(argv[2]);
	if (!hProcess) return 1;

	HMODULE kernel32 = GetModuleHandleA("kernel32.dll");
	if (!kernel32) return 1;

	LPVOID allocMem = VirtualAllocEx(hProcess, NULL, strlen(dllName) + 1, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (!allocMem) return 1;

	WriteProcessMemory(hProcess, allocMem, dllName, strlen(dllName) + 1, NULL);

	HANDLE thread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)(LPVOID)GetProcAddress(kernel32, "LoadLibraryA"), allocMem, 0, NULL);
	if (!thread) return 1;

	WaitForSingleObject(thread, INFINITE);

	VirtualFreeEx(hProcess, allocMem, 0, MEM_RELEASE);
	CloseHandle(thread);
	CloseHandle(hProcess);
}