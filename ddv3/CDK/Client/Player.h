#pragma once

#include <Windows.h>
#include "Memory.h"
#include "lib/Modules.h"
#include "lib/Offsets.h"
#include "Entity.h"
#include "Team.h"

class Player : public Entity{
    public:
	Player() {}
	Player (Entity entity) {
		   this->base = entity.GetBase();
		   if (this->base <= 0) this->base = 0;
	}
	virtual DWORD GetBase() {
		    if (this->base <= 0) return 0;
		    return this->base;
	}
	ETeam Team() {
		  if (this->GetBase() <= 0)return ETeam::Invalid;
		  auto team = memory.Read<ETeam>(this->GetBase() + hazedumper::netvars::m_iTeamNum);
		  if (team <= ETeam::Invalid || team >= ETeam::InvalidLast) return ETeam::Invalid;
		  return team;
	}
	int Health() {
		if (this->GetBase() <= 0) return 0;
		auto heal= memory.Read<int>(this->GetBase() + hazedumper::netvars::m_iHealth);
		if (heal <= 0)return 0;
		return heal;
	}
	bool IsSpottedByMask(int playerIndex) {
		 if (this->GetBase() <= 0) return false;
		 return memory.Read<int>(this->GetBase() + hazedumper::netvars::m_bSpottedByMask)& (1 << playerIndex);
	}
	bool GetDormant() {//бесполезная функция
		 if (this->GetBase() <= 0) return false;
		 auto dormant = memory.Read<int>(this->GetBase() + hazedumper::signatures::m_bDormant);
		 if (dormant <= 0)return false;
		 return true;
	}
	DWORD GetBoneMatrix() {
		  if (this->GetBase() <= 0) return 0;
		  auto boneMatrix = memory.Read<DWORD>(this->GetBase() + hazedumper::netvars::m_dwBoneMatrix);
		  if (boneMatrix <= 0) return 0;
		  return boneMatrix;
	}
	Vec3 GetBodyPartPosition(int bon) {
		 DWORD boneMatrix = this->GetBoneMatrix();
		 if (boneMatrix <= 0) return{ 0,0,0 };
		 return {
		        memory.Read<float>(boneMatrix + 0x30 * bon + 0x0c),
			    memory.Read<float>(boneMatrix + 0x30 * bon + 0x1c),
			    memory.Read<float>(boneMatrix + 0x30 * bon + 0x2c)
		 };
	}
	bool GetLife() {
		 if (this->GetBase() <= 0)return false;
		 auto life = memory.Read<int>(this->GetBase() + hazedumper::netvars::m_lifeState);
		 if(life == 0)return true;
		 return false;
	}
	DWORD GetGlowIndex() {
		  if (this->GetBase() <= 0) return 0;
		  auto glowIndex = memory.Read<DWORD>(this->GetBase() + hazedumper::netvars::m_iGlowIndex);
		  if (glowIndex < 0) return 0;
		  return glowIndex;
	}
};