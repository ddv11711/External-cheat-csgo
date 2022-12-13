#pragma once
#include <Windows.h>
#include "ClassId.h"
#include "Memory.h"
#include "lib/Modules.h"
#include "lib/Offsets.h"

class Entity {
      public:
	  Entity() {}
	  DWORD base = 0;
	  Entity (DWORD base) {
		     this->base = base;
			 if (this->base <= 0)this->base = 0;
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
		      if (this->base <= 0) return 0;
		      return this->base;
	  }
	  EClassId ClassId() {
		       if(this->GetBase() <=0) return EClassId::Invalid;
		       EClassId classId = memory.Read<EClassId>(memory.Read<int>(memory.Read<int>(memory.Read<int>(this->GetBase() + 0x8)+0x8 )+0x1)+0x14);
		       if (classId <= EClassId::Invalid || classId >= EClassId::InvalidLast) return EClassId::Invalid;
		       return classId;
	  }
};