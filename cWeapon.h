#pragma once
#include <wx/string.h>
#include <vector>
#include <string>
#include "cWeaponComponent.h"

class cWeapon
{
public:
	cWeapon();

	void setWeaponTemplate(std::string weaponTemplate);
	void setWeaponName(std::string weaponName);
	void setWeaponId(std::string weaponId);
	void setWeaponModel(std::string weaponModel);
	void addWeaponAsset(std::string weaponAsset);
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
		"COMPONENT_AT_AR_AFGRIP",
		"COMPONENT_AT_PI_FLSH",
		"COMPONENT_AT_AR_FLSH",
		"COMPONENT_AT_PI_SUPP",
		//TODO finish.
	};

	std::vector<cWeaponComponent*> components[100] = {};

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

	std::vector<std::string> weaponAssets[50] = {};
};

