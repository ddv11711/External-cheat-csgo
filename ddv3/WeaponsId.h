#pragma once

enum EWeaponsId : int {
	Invalid = 0,
	DEAGLE = 1,
	DUAL = 2,
	FIVE = 3,
	CLOCK = 4,
	AK47=7,
	AUG = 8,
	AWP = 9,
	FAMAS = 10,
	G3SG1 = 11,
	GALIL=13,
	M249 = 14,
	MAC10 = 17,
	M4A1 = 16,
	P90 = 19,
	C4=49,
	SG556=39,
	MP9=34,
	MP7=33,
	UMP45=24,
	BIZON=26,
	P2000=32,
	P250=36,
	TEC9=30,
	NOVA=35,
	XM1014=25,
	MAG7=27,
	SAWED=29,
	NEGEV=28,
	ZEUSE=31,
	SCAR20 = 38,
	SSG08 = 40,
	KNIFE_CT = 42,
	FLASH = 43,
	GRENADE=44,
	SMOKE=45,
	MOLOTOV=46,
	DECOY = 47,
	INCGRENADE=48,
	KNIFE_T = 59,
	M4A1S = 60,
	USPS = 61,
	CZ75 = 63,
	REVOLVER = 64,
	InvalidLast=99
};

constexpr const int GetWeaponPaint(short weaponid) {
	switch (weaponid) {
	case EWeaponsId::AWP:return 475;
	case EWeaponsId::DEAGLE:return 962;
	default:return 0;
	}
}