#pragma once

class Memory {
      public:
	  HANDLE	process;
	  HWND		processHandle;
	  DWORD		processId;

	  struct Module {
		     DWORD base;
		     DWORD size;
	  };

	  struct HandleData {
		     DWORD processId;
	 	    HWND handle;
	  };
	  ~Memory() { Exit(); }
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
		   } 
		   while (Module32Next(module, &entry));
		   return Module{ 0, 0 };
	}

	template<class T>
	T Read (const DWORD address) {
		   T value;
		   ReadProcessMemory (process, LPVOID(address), &value, sizeof(T), NULL);
		   return value;
	}

	template<int size>
	std::string ReadString (const DWORD address) {
		 char value[size];
		 ReadProcessMemory(process, LPVOID(address), value, sizeof(char[size]), NULL);
		 return std::string (value);
	}

	template<class T>
	bool Write(const DWORD address, const T& value, SIZE_T size = sizeof(T)) {
		 return WriteProcessMemory (process, LPVOID(address), &value, size, NULL);
	}

	void Exit() {
		 CloseHandle(process);
	}
};

extern Memory memory;