#pragma once
#include <Windows.h>
#include "ClassId.h"
#include "Memory.h"
#include "Modules.h"
#include "Offsets.h"

class Entity {
      public:
	  Entity() {}
	  DWORD base = 0;
	  Entity (DWORD base) {
		     this->base = base;
	  }
	  void operator=(Entity entity) {
		   this->base = entity.base;
	  }
	  bool operator==(Entity& entity) {
		   return this->GetBase() == entity.GetBase();
	  }
	  bool operator!=(Entity& entity) {
		   return this->GetBase() != entity.GetBase();
	  }
	  virtual DWORD GetBase() {
		      return this->base;
	  }
	  EClassId ClassId() {
		       auto classId = memory.Read<int>(memory.Read<int>(memory.Read<int>(memory.Read<int>(this->GetBase() + 0x8)+0x8 )+0x1)+0x14);
		       if (classId <= (int)EClassId::Invalid || classId >= (int)EClassId::InvalidLast) return EClassId::Invalid;
		       return(EClassId)classId;
	  }
};