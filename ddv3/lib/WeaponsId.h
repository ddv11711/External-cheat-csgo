#pragma once

enum EWeaponsId : int {
	Invalid = 0,
	DEAGLE = 1, //1
	DUAL = 2,   //1
	FIVE = 3,   //1
	CLOCK = 4,  //1
	AK47=7,     
	AUG = 8,    
	AWP = 9,    
	FAMAS = 10, 
	G3SG1 = 11, 
	GALIL=13,   
	M249 = 14,  
	M4A1 = 16,  
	MAC10 = 17, //2
	P90 = 19,   
	UMP45=24,   
	XM1014=25,  //2
	BIZON = 26, 
	MAG7=27,    
	NEGEV = 28, 
	SAWED=29,   
	TEC9 = 30,  //1
	ZEUSE=31,
	P2000 = 32, 
	MP7 = 33,   
	MP9 = 34,    
	NOVA = 35,  
	P250 = 36,  //1
	SCAR20 = 38,
	SG556 = 39, 
	SSG08 = 40, 
	KNIFE_CT = 42,
	FLASH = 43,
	GRENADE=44,
	SMOKE=45,
	MOLOTOV=46,
	DECOY = 47,
	INCGRENADE=48,
	C4 = 49,
	KNIFE_T = 59,
	M4A1S = 60,     
	USPS = 61,      //1
	CZ75 = 63,      //1
	REVOLVER = 64,  //1
	InvalidLast=99
};

constexpr const int GetWeaponPaint(short weaponid) {
	if (weaponid == EWeaponsId::AWP) return 475;
	else if (weaponid == EWeaponsId::DEAGLE)  return 328;
	else if (weaponid == EWeaponsId::TEC9)  return 2;
	else if (weaponid == EWeaponsId::FIVE)  return 3;
	else return 0;
}
constexpr const int GetTipeWeapon(short weaponid) {
	if ((weaponid >= EWeaponsId::DEAGLE && weaponid <= EWeaponsId::CLOCK) || weaponid == EWeaponsId::P2000 || weaponid == EWeaponsId::TEC9 || weaponid == EWeaponsId::USPS || weaponid == EWeaponsId::REVOLVER || weaponid == EWeaponsId::CZ75) return 1;
	else if (weaponid == EWeaponsId::AK47 || weaponid == EWeaponsId::AUG || weaponid == EWeaponsId::FAMAS || weaponid == EWeaponsId::M4A1 || weaponid == EWeaponsId::SG556 || weaponid == EWeaponsId::M4A1S) return 2;
	else if (weaponid == EWeaponsId::P90 || weaponid == EWeaponsId::UMP45 || weaponid == EWeaponsId::BIZON || weaponid == EWeaponsId::MP7 || weaponid == EWeaponsId::MP9) return 3;
	else if (weaponid == EWeaponsId::MAC10 || weaponid == EWeaponsId::XM1014 || weaponid == EWeaponsId::MAG7 || weaponid == EWeaponsId::SAWED || weaponid == EWeaponsId::NOVA)return 4;
	else if (weaponid == EWeaponsId::AWP || weaponid == EWeaponsId::G3SG1 || weaponid == EWeaponsId::SCAR20 || weaponid == EWeaponsId::SSG08) return 5;
	else if (weaponid == EWeaponsId::M249 || weaponid == EWeaponsId::NEGEV) return 6;
	else if (weaponid == EWeaponsId::KNIFE_T || weaponid == EWeaponsId::KNIFE_CT)return 7;
	else if (weaponid >= EWeaponsId::FLASH && weaponid <= EWeaponsId::INCGRENADE) return 8;
	else return 0;
}