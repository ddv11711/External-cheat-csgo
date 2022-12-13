#pragma once
#include <iostream>
class Memory {
      public:
	  HANDLE	process=0;
	  HWND		processHandle=0;
	  DWORD		processId=0;

	  struct Module {
		     DWORD base=0;
		     DWORD size=0;
	  };

	  struct HandleData {
		     DWORD processId=0;
	 	     HWND handle=0;
	  };
	  ~Memory() { CloseHandle(process); }
	inline DWORD FindProcess (const char* name) {
		   PROCESSENTRY32 entry;
		   entry.dwSize = sizeof(entry);
		   auto handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
		   do {
			  if (strcmp(_bstr_t(entry.szExeFile), name)) continue;
			  CloseHandle(handle);
			  return entry.th32ProcessID;
		   }
		   while (Process32Next(handle, &entry));
		   return 0;
	}

	inline void Attach (const DWORD id, const DWORD access) {
		   this->processId = id;
		   this->process = OpenProcess (access, false, id);
		   HandleData data = { id, nullptr };
		   EnumWindows ([](HWND handle, LPARAM lparam) {
			           auto& nextData = *reinterpret_cast<HandleData*>(lparam);
			           DWORD processId = 0;
			           GetWindowThreadProcessId(handle, &processId);
			           if (nextData.processId != processId) return 1;
			           nextData.handle = handle;
			           return 0;
		   }, reinterpret_cast<LPARAM>(&data));
		   this->processHandle = data.handle;
	}

	inline Module GetModule (const char* moduleName) {
		   MODULEENTRY32 entry;
		   entry.dwSize = sizeof (entry);
		   auto module = CreateToolhelp32Snapshot (TH32CS_SNAPMODULE, this->processId);
		   do {
			  if (strcmp(_bstr_t(entry.szModule), moduleName)) continue;
			  CloseHandle (module);
			
			  return Module{
				     reinterpret_cast<DWORD>(entry.hModule),
				     entry.modBaseSize
			  };
		   } while (Module32Next(module, &entry));
		   return Module{ 0, 0 };
	}

	template<class T>
	T Read (DWORD address) {
		   if (address < 0) address = 0;
		   T value;
		   ReadProcessMemory (process, LPVOID(address), &value, sizeof(T), NULL);
		   return value;
	}

	template<int size>
	std::string ReadString (DWORD address) {
		 if (address < 0) address = 0;
		 char value[size];
		 ReadProcessMemory(process, LPVOID(address), value, sizeof(char[size]), NULL);
		 return std::string (value);
	}

	template<class T>
	bool Write(DWORD address, const T& value, SIZE_T size = sizeof(T)) {
		 if (address <= 0 ) return false;
		 return WriteProcessMemory (process, LPVOID(address), &value, size, NULL);
	}

};

extern Memory memory;