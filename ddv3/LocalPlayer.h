#pragma once

#include <Windows.h>
#include "Memory.h"
#include "Modules.h"
#include "Offsets.h"
#include "Player.h"
#include "Team.h"

class LocalPlayer :public Player {
      public:
	  LocalPlayer () {}
	  DWORD GetBase() {
		    return memory.Read<DWORD>(clientDll.base + hazedumper::signatures::dwLocalPlayer);
	  }
	  DWORD GetFlash() {
		    return memory.Read<DWORD>(this->GetBase() + hazedumper::netvars::m_flFlashDuration);
	  }
	 DWORD GetCrosshairId() {
		   DWORD CrosshairId =  memory.Read<DWORD>(this->GetBase() + hazedumper::netvars::m_iCrosshairId);
		   if (CrosshairId > 32 || CrosshairId < 1) return 0;
		   return CrosshairId;
	 }
	 DWORD GetActiveWeapon() {
		   DWORD currentWeapon = memory.Read<DWORD>(this->GetBase() + hazedumper::netvars::m_hActiveWeapon) & 0xfff;
		   if (currentWeapon <= 0) return 0;
		   currentWeapon = memory.Read<DWORD>(clientDll.base + hazedumper::signatures::dwEntityList + (currentWeapon - 1) * 0x10);
		   if (currentWeapon <= 0) return 0;
		   return currentWeapon;
	 }
	 short GetActiveWeaponID() {
		   DWORD currentWeapon = this->GetActiveWeapon();
		   if (currentWeapon <=0 ) return 0;
		   short ActiveWeaponID = memory.Read<short>(currentWeapon + hazedumper::netvars::m_iItemDefinitionIndex);
		   if(ActiveWeaponID<=0) return 0;
		   return ActiveWeaponID;
	 }
	 int GetFlag() {
		 return memory.Read<int>(this->GetBase() + hazedumper::netvars:: m_fFlags);
	 }
	 Vec3 GetLocalPosition() {
		  return memory.Read<Vec3>(this->GetBase() + hazedumper::netvars::m_vecOrigin) + memory.Read<Vec3>(this->GetBase() + hazedumper::netvars::m_vecViewOffset);
	 }
	 Vec3 GetAimPunch() {
		  return (memory.Read<Vec3>(this->GetBase() + hazedumper::netvars::m_aimPunchAngle) * 2.f);
	 }
	 int GetShotsFired() {
		 return memory.Read<int>(this->GetBase() + hazedumper::netvars::m_iShotsFired);
	 }
};