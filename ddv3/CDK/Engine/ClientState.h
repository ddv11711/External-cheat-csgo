#pragma once
#include <Windows.h>
#include "Memory.h"
#include "lib/Modules.h"
#include "lib/Offsets.h"
#include "State.h"

class ClientState {
      public:
	  DWORD base = 0;
	  ClientState() {}
	  DWORD GetBase() {
		    if (engineDll.base <= 0) return 0;
		    auto base = memory.Read<DWORD>(engineDll.base + hazedumper::signatures::dwClientState);
			if (base <= 0) return 0;
			return base;
	  }
	  EState State() {
		     if (this->base <= 0) return EState::Invalid;
		     auto state = memory.Read<EState>(this->base + hazedumper::signatures::dwClientState_State);
		     if (state <= EState::Invalid || state >= EState::InvalidLast) return EState::Invalid;
		     return state;
	  }
	  DWORD GetLocalPayerIndex() {
		    if (engineDll.base <= 0) return 0;
		    auto localIndex = memory.Read<int>(engineDll.base + hazedumper::signatures::dwClientState_GetLocalPlayer);
		    if (localIndex <= 0) return 0;
		    return localIndex;
 	  }
	  Vec3 GetLocalPayerViewAngles() {
		  if (this->base <= 0)return { 0,0,0 };
		  return memory.Read<Vec3>(this->base + hazedumper::signatures::dwClientState_ViewAngles);
	  }
};