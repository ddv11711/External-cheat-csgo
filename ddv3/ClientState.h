#pragma once
#include <Windows.h>
#include "Memory.h"
#include "Modules.h"
#include "Offsets.h"
#include "State.h"

class ClientState {
      public:
	  ClientState() {}
	  DWORD GetBase() {
		    return memory.Read<DWORD>(engineDll.base + hazedumper::signatures::dwClientState);
	  }
	  EState State() {
		     auto state = memory.Read<int>(this->GetBase() + hazedumper::signatures::dwClientState_State);
		     if (state <= (int)EState::Invalid || state >= (int)EState::InvalidLast) return EState::Invalid;
		     return (EState)state;
	  }
	  int GetLocalPayerIndex() {
		  return memory.Read<int>(engineDll.base + hazedumper::signatures::dwClientState_GetLocalPlayer);
 	  }
	  Vec3 GetLocalPayerViewAngles() {
		  return memory.Read<Vec3>(this->GetBase() + hazedumper::signatures::dwClientState_ViewAngles);
	  }
};