#pragma once

#include <Windows.h>
#include "Memory.h"
#include "Modules.h"
#include "Offsets.h"
#include "Entity.h"
#include "Team.h"

class Player : public Entity{
    public:
	Player() {}
	Player(Entity entity) {
		   this->base = entity.GetBase();
	}
	virtual DWORD GetBase() {
		    return this->base;
	}
	ETeam Team() {
		  auto team = memory.Read<int>(this->GetBase() + hazedumper::netvars::m_iTeamNum);
		  if (team <= (int)ETeam::Invalid || team >= (int)ETeam::InvalidLast) return ETeam::Invalid;
		  return (ETeam)team;
	}
	int Health() {
		return memory.Read<int>(this->GetBase() + hazedumper::netvars::m_iHealth);
	}
	bool IsSpottedByMask(int playerIndex) {
		 return memory.Read<int>(this->GetBase() + hazedumper::netvars::m_bSpottedByMask)& (1 << playerIndex);
	}
	bool GetDormant() {
		 return memory.Read<int>(this->GetBase() + hazedumper::signatures::m_bDormant);
	}
	DWORD GetBoneMatrix() {
		  return memory.Read<DWORD>(this->GetBase() + hazedumper::netvars::m_dwBoneMatrix);
	}
	Vec3 GetBodyPartPosition() {
		DWORD boneMatrix = this->GetBoneMatrix();
		return {
		       memory.Read<float>(boneMatrix + 0x30 * 6 + 0x0c),
			   memory.Read<float>(boneMatrix + 0x30 * 6 + 0x1c),
			   memory.Read<float>(boneMatrix + 0x30 * 6 + 0x2c)
		};
	}
};