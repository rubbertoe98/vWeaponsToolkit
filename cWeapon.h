#pragma once
#include <wx/string.h>
#include <vector>
#include <string>
#include "cWeaponComponent.h"
#include "cWeaponAsset.h"

class cWeapon
{
public:
	cWeapon();

	void setWeaponTemplate(std::string weaponTemplate);
	void setWeaponName(std::string weaponName);
	void setWeaponId(std::string weaponId);
	void setWeaponModel(std::string weaponModel);
	void addWeaponAsset(cWeaponAsset* weaponAsset);
	void setValidWeaponModelFound(bool found);
	void setAudioItem(std::string weaponAudio);
	void setWeaponDamage(float weaponDamage);
	void setWeaponRange(float weaponRange);
	void setAmmoType(std::string ammoType);
	void setWeaponLOD(float weaponLOD);
	void setWeaponReloadSpeedMultiplier(float weaponReloadSpeedMultiplier);
	void setWeaponFireRateMultiplier(float weaponFireRateMultiplier);
	void setWeaponDamageType(std::string damageType);
	void setWeaponAudioItem(std::string audioItem);

	bool getValidWeaponModelFound();
	std::string getWeaponTemplate();
	std::string getWeaponName();
	std::string getWeaponId();
	std::string getWeaponModel();
	std::string getAudioItem();
	float getWeaponDamage();
	float getWeaponRange();
	std::string getAmmoType();
	float getWeaponLOD();
	float getWeaponReloadSpeedMultiplier();
	float getWeaponFireRateMultiplier();
	std::string getWeaponDamageType();
	std::string getWeaponAudioItem();
	
	void exportWeapon();

	const char* nativeWeapons[100] = {
		"WEAPON_ASSAULTRIFLE",
		"WEAPON_CARBINE"
		//TODO finish.
	};

	const char* audioItems[100] = {
		"AUDIO_ITEM_PISTOL",
		"AUDIO_ITEM_COMBATPISTOL"
		//TODO finish.
	};

	const char* ammoTypes[100] = {
		"AMMO_PISTOL",
		"AMMO_SMG"
		//TODO finish.
	};

	const char* damageTypes[100] = {
		"BULLET",
		"MELEE",
		"ELECTRIC",
		"EXPLOSIVE",
		"NONE",
		"WATER_CANNON",
		"FIRE",
		"SMOKE",
	}; 

	const char* nativeComponents[100] = {
		"COMPONENT_AT_RAILCOVER_01",
		"COMPONENT_COMBATPISTOL_CLIP_01",
		//TODO finish.
	};

	const char* nativeAmmoInfos[100] = {
		"",
		"AMMO_RIFLE_ARMORPIERCING",
		"AMMO_RIFLE_FMJ",
		"AMMO_RIFLE_INCENDIARY",
		"AMMO_RIFLE_TRACER",
		//TODO finish.
	};

	std::vector<cWeaponComponent*> components = {};
	std::vector<cWeaponAsset*> weaponAssets = {};

private:
	std::string weaponTemplate;
	std::string weaponName;
	std::string weaponId;
	std::string weaponModel;

	std::string audioItem;
	float weaponDamage;
	float weaponRange;
	std::string ammoType;
	float weaponLOD;
	float weaponReloadSpeedMultiplier;
	float weaponFireRateMultiplier;
	std::string damageType;

	bool validWeaponModelFound;
};