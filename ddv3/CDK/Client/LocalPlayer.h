#pragma once

#include <Windows.h>
#include "Memory.h"
#include "lib/Modules.h"
#include "lib/Offsets.h"
#include "Player.h"
#include "Team.h"

class LocalPlayer :public Player {
      public:
	  LocalPlayer () {}
	  DWORD GetBase() {
		    if (clientDll.base <= 0) return 0;
		    auto base = memory.Read<DWORD>(clientDll.base + hazedumper::signatures::dwLocalPlayer);
			if (base <= 0) return 0;
			return base;
	  }
	  bool GetFlash() {
		    if (this->base <= 0) return false;
		    auto flash = memory.Read<DWORD>(this->base + hazedumper::netvars::m_flFlashDuration);
			if (flash > 0) return true;
			return false;
	  }
	 DWORD GetCrosshairId() {
		   if (this->base <= 0) return 0;
		   DWORD CrosshairId =  memory.Read<DWORD>(this->base + hazedumper::netvars::m_iCrosshairId);
		   if (CrosshairId > 32 || CrosshairId < 1) return 0;
		   return CrosshairId;
	 }
	 DWORD GetActiveWeapon() {
		   if (this->base <= 0) return 0;
		   DWORD currentWeapon = memory.Read<DWORD>(this->base + hazedumper::netvars::m_hActiveWeapon) & 0xfff;
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
	 bool GetFlag() {
		  if (this->base <= 0) return 0;
		  auto flag = memory.Read<int>(this->base + hazedumper::netvars:: m_fFlags);
		  if (flag == 257) return true;
		  return false;
	 }
	 Vec3 GetLocalPosition() {
		  if (this->base <= 0) return {0,0,0};
		  return memory.Read<Vec3>(this->base + hazedumper::netvars::m_vecOrigin) + memory.Read<Vec3>(this->base + hazedumper::netvars::m_vecViewOffset);
	 }
	 Vec3 GetAimPunch() {
		  if (this->base <= 0) return { 0,0,0 };
		  return (memory.Read<Vec3>(this->base+ hazedumper::netvars::m_aimPunchAngle) * 2.f);
	 }
	 int GetShotsFired() {
		 if (this->base <= 0) return 0;
		 return memory.Read<int>(this->base + hazedumper::netvars::m_iShotsFired);
	 }
	 bool GetScop() {
		  if (this->base <= 0) return false;
		  return memory.Read<bool>(this->base +hazedumper::netvars::m_bIsScoped);
	 }
};