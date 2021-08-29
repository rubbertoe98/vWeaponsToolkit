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
	void setWeaponLOD(int weaponLOD);
	void setWeaponReloadSpeedMultiplier(float weaponReloadSpeedMultiplier);
	void setWeaponFireRateMultiplier(float weaponFireRateMultiplier);
	void setWeaponDamageType(std::string damageType);
	void setWeaponAudioItem(std::string audioItem);
	void setWeaponHeadShotDamageModifierPlayer(float headShotDamageModifierPlayer);

	bool getValidWeaponModelFound();
	std::string getWeaponTemplate();
	std::string getWeaponName();
	std::string getWeaponId();
	std::string getWeaponModel();
	std::string getAudioItem();
	float getWeaponDamage();
	float getWeaponRange();
	std::string getAmmoType();
	int getWeaponLOD();
	float getWeaponReloadSpeedMultiplier();
	float getWeaponFireRateMultiplier();
	float getWeaponHeadShotDamageModifierPlayer();
	std::string getWeaponDamageType();
	std::string getWeaponAudioItem();

	const char* nativeWeapons[100] = {
		"WEAPON_KNIFE",
		"WEAPON_NIGHTSTICK",
		"WEAPON_HAMMER",
		"WEAPON_BAT",
		"WEAPON_GOLFCLUB",
		"WEAPON_CROWBAR",
		"WEAPON_PISTOL",
		"WEAPON_COMBATPISTOL",
		"WEAPON_APPISTOL",
		"WEAPON_PISTOL50",
		"WEAPON_MICROSMG",
		"WEAPON_SMG",
		"WEAPON_ASSAULTSMG",
		"WEAPON_ASSAULTRIFLE",
		"WEAPON_CARBINERIFLE",
		"WEAPON_ADVANCEDRIFLE",
		"WEAPON_MG",
		"WEAPON_COMBATMG",
	};

	const char* audioItems[100] = {
		"AUDIO_ITEM_PISTOL",
		"AUDIO_ITEM_COMBATPISTOL",
		"AUDIO_ITEM_APPISTOL",
		"AUDIO_ITEM_PISTOL50",
		"AUDIO_ITEM_MICROSMG",
		"AUDIO_ITEM_SMG",
		"AUDIO_ITEM_ASSAULTSMG",
		"AUDIO_ITEM_ASSAULTRIFLE",
		"AUDIO_ITEM_CARBINERIFLE",
		"AUDIO_ITEM_ADVANCEDRIFLE",
		"AUDIO_ITEM_MG",
		"AUDIO_ITEM_COMBATMG",
		"AUDIO_ITEM_PUMPSHOTGUN",
		"AUDIO_ITEM_SAWNOFFSHOTGUN",
		"AUDIO_ITEM_ASSAULTSHOTGUN",
		"AUDIO_ITEM_BULLPUPSHOTGUN",
		"AUDIO_ITEM_STUNGUN",
		"AUDIO_ITEM_SNIPERRIFLE",
		"AUDIO_ITEM_HEAVYSNIPER",
		"AUDIO_ITEM_REMOTESNIPER",
		"AUDIO_ITEM_GRENADELAUNCHER",
		"AUDIO_ITEM_RPG",
		"AUDIO_ITEM_MINIGUN",
		"AUDIO_ITEM_GRENADE",
		"AUDIO_ITEM_STICKYBOMB",
		"AUDIO_ITEM_SMOKEGRENADE",
		"AUDIO_ITEM_SMOKEGRENADE",
		"AUDIO_ITEM_MOLOTOV",
		"AUDIO_ITEM_SNOWBALL",
		"AUDIO_ITEM_SNSPISTOL",
		"AUDIO_ITEM_CARBINE_SPECIAL",
		"AUDIO_ITEM_MELEE_SWITCHBLADE",
		"AUDIO_ITEM_ASSAULTRIFLE_MK2",
		"AUDIO_ITEM_BULLPUP_RIFLE_MK2",
		"AUDIO_ITEM_CARBINERIFLE_MK2",
		"AUDIO_ITEM_COMBATMG_MK2",
		"AUDIO_ITEM_DOUBLEACTION_REVOLVER",
		"AUDIO_ITEM_HEAVYSNIPER_MK2",
		"AUDIO_ITEM_MARKSMAN_RIFLE_MK2",
		"AUDIO_ITEM_PISTOL_MK2",
		"AUDIO_ITEM_PUMP_SHOTGUN_MK2",
		"AUDIO_ITEM_HEAVY_REVOLVER_MK2",
		"AUDIO_ITEM_SMG_MK2",
		"AUDIO_ITEM_SNS_PISTOL_MK2",
		"AUDIO_ITEM_RAYPISTOL",
		"AUDIO_ITEM_RAYCARBINE",
		"AUDIO_ITEM_RAYMINIGUN",
		"AUDIO_ITEM_CARBINE_SPECIAL_MK2",
	};

	const char* ammoTypes[100] = {
		"AMMO_PISTOL",
		"AMMO_SMG",
		"AMMO_RIFLE",
		"AMMO_MG",
		"AMMO_SHOTGUN",
		"AMMO_STUNGUN",
		"AMMO_SNIPER",
		"AMMO_SNIPER_REMOTE",
		"AMMO_FIREEXTINGUISHER",
		"AMMO_PETROLCAN",
		"AMMO_MINIGUN",
		"AMMO_GRENADELAUNCHER",
		"AMMO_GRENADELAUNCHER_SMOKE",
		"AMMO_RPG",
		"AMMO_STINGER",
		"AMMO_GRENADE",
		"AMMO_BALL",
		"AMMO_STICKYBOMB",
		"AMMO_SMOKEGRENADE",
		"AMMO_BZGAS",
		"AMMO_FLARE",
		"AMMO_MOLOTOV",
		"AMMO_TANK",
		"AMMO_SPACE_ROCKET",
		"AMMO_PLANE_ROCKET",
		"AMMO_PLAYER_LASER",
		"AMMO_ENEMY_LASER",
		"AMMO_BIRD_CRAP",
		"AMMO_MG_ARMORPIERCING",
		"AMMO_MG_FMJ",
		"AMMO_MG_INCENDIARY",
		"AMMO_MG_TRACER",
		"AMMO_PISTOL_FMJ",
		"AMMO_PISTOL_HOLLOWPOINT",
		"AMMO_PISTOL_INCENDIARY",
		"AMMO_PISTOL_TRACER",
		"AMMO_RIFLE_ARMORPIERCING",
		"AMMO_RIFLE_FMJ",
		"AMMO_RIFLE_INCENDIARY",
		"AMMO_RIFLE_TRACER",
		"AMMO_SMG_FMJ",
		"AMMO_SMG_HOLLOWPOINT",
		"AMMO_SMG_INCENDIARY",
		"AMMO_SMG_TRACER",
		"AMMO_SNIPER_ARMORPIERCING",
		"AMMO_SNIPER_EXPLOSIVE",
		"AMMO_SNIPER_FMJ",
		"AMMO_SNIPER_INCENDIARY",
		"AMMO_SNIPER_TRACER",
		"AMMO_SHOTGUN_ARMORPIERCING",
		"AMMO_SHOTGUN_EXPLOSIVE",
		"AMMO_SHOTGUN_HOLLOWPOINT",
		"AMMO_SHOTGUN_INCENDIARY",
		"AMMO_RAYPISTOL",
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
		"COMPONENT_PISTOL_CLIP_01",
		"COMPONENT_PISTOL_CLIP_02",
		"COMPONENT_AT_PI_FLSH",
		"COMPONENT_AT_PI_SUPP",
		"COMPONENT_COMBATPISTOL_CLIP_01",
		"COMPONENT_COMBATPISTOL_CLIP_02",
		"COMPONENT_APPISTOL_CLIP_01",
		"COMPONENT_APPISTOL_CLIP_02",
		"COMPONENT_PISTOL50_CLIP_01",
		"COMPONENT_PISTOL50_CLIP_02",
		"COMPONENT_MICROSMG_CLIP_01",
		"COMPONENT_MICROSMG_CLIP_02",
		"COMPONENT_AT_SCOPE_MACRO",
		"COMPONENT_AT_AR_SUPP_02",
		"COMPONENT_SMG_CLIP_01",
		"COMPONENT_SMG_CLIP_02",
		"COMPONENT_AT_AR_FLSH",
		"COMPONENT_ASSAULTSMG_CLIP_01",
		"COMPONENT_ASSAULTSMG_CLIP_02",
		"COMPONENT_ASSAULTRIFLE_CLIP_01",
		"COMPONENT_ASSAULTRIFLE_CLIP_02",
		"COMPONENT_AT_AR_AFGRIP",
		"COMPONENT_CARBINERIFLE_CLIP_01",
		"COMPONENT_CARBINERIFLE_CLIP_02",
		"COMPONENT_AT_RAILCOVER_01",
		"COMPONENT_AT_SCOPE_MEDIUM",
		"COMPONENT_AT_AR_SUPP",
		"COMPONENT_ADVANCEDRIFLE_CLIP_01",
		"COMPONENT_ADVANCEDRIFLE_CLIP_02",
		"COMPONENT_AT_SCOPE_SMALL",
		"COMPONENT_MG_CLIP_01",
		"COMPONENT_MG_CLIP_02",
		"COMPONENT_COMBATMG_CLIP_01",
		"COMPONENT_COMBATMG_CLIP_02",
	};

	const char* nativeAmmoInfos[100] = {
		"Default Ammo",
		"AMMO_RIFLE_ARMORPIERCING",
		"AMMO_RIFLE_FMJ",
		"AMMO_RIFLE_INCENDIARY",
		"AMMO_RIFLE_TRACER",
		"AMMO_SNIPER_ARMORPIERCING",
		"AMMO_SNIPER_FMJ",
		"AMMO_SNIPER_EXPLOSIVE",
		"AMMO_SNIPER_INCENDIARY",
		"AMMO_SNIPER_TRACER",
		"AMMO_SHOTGUN_ARMORPIERCING",
		"AMMO_SHOTGUN_EXPLOSIVE",
		"AMMO_SHOTGUN_HOLLOWPOINT",
		"AMMO_SHOTGUN_INCENDIARY",
		"AMMO_PISTOL_FMJ",
		"AMMO_PISTOL_HOLLOWPOINT",
		"AMMO_PISTOL_INCENDIARY",
		"AMMO_PISTOL_TRACER",
		"AMMO_MG_ARMORPIERCING",
		"AMMO_MG_FMJ",
		"AMMO_MG_INCENDIARY",
		"AMMO_MG_TRACER",
		"AMMO_SMG_FMJ",
		"AMMO_SMG_HOLLOWPOINT",
		"AMMO_SMG_INCENDIARY",
		"AMMO_SMG_TRACER",
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
	int weaponLOD;
	float weaponReloadSpeedMultiplier;
	float weaponFireRateMultiplier;
	float headShotDamageModifierPlayer;
	std::string damageType;

	bool validWeaponModelFound;
};