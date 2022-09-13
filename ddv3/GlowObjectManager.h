#pragma once
#include <Windows.h>
#include "Memory.h"
#include "Modules.h"
#include "Offsets.h"
#include "GlowObjectDefinition.h"
#include <vector>

class GlowObjectManager {
      public:
	  GlowObjectManager() {}
	  struct GlowObject {
		     int index;
		     GlowObjectDefinition definition;
	  };
	  DWORD GetBase() {
		    return memory.Read<DWORD>(clientDll.base + hazedumper::signatures::dwGlowObjectManager);
	  }
	  int Size() {
		  return memory.Read<DWORD>(clientDll.base + hazedumper::signatures::dwGlowObjectManager+ 0x4);
	  }
	  std::vector<GlowObject> Attay(int size){
	       std::vector<GlowObject> glowObjectArray;
		   for (int glowIndex = 0; glowIndex < size; glowIndex++) {
			   auto glowObjectDefinition = memory.Read<GlowObjectDefinition>(this->GetBase() + glowIndex * sizeof(GlowObjectDefinition));
			   if (glowObjectDefinition.baseEntity == 0) continue;
			   glowObjectArray.push_back ({ glowIndex,glowObjectDefinition });
		   }
		  return glowObjectArray;
	  }
	  DWORD GetGlowObjectBaseId(int glowIndex) {
		    return this->GetBase() + glowIndex * sizeof(GlowObjectDefinition);
	  }
	DWORD GetGlowObjectBase(GlowObject glowObject) {
		  return this->GetGlowObjectBaseId(glowObject.index);
	}
};