#pragma once
#include <wx/string.h>
#include <vector>

class cWeapon
{
public:
	cWeapon();

	void setWeaponTemplate(wxString weaponTemplate);
	void setWeaponName(wxString weaponName);
	void setWeaponId(wxString weaponId);
	void setWeaponModel(wxString weaponModel);
	void addWeaponAsset(std::string weaponAsset);
	void setValidWeaponModelFound(bool found);
	void setAudioItem(wxString weaponAudio);
	void setWeaponDamage(float weaponDamage);
	void setWeaponRange(float weaponRange);
	void setAmmoType(wxString ammoType);
	void setWeaponLOD(float weaponLOD);
	void setWeaponReloadSpeedMultiplier(float weaponReloadSpeedMultiplier);
	void setWeaponFireRateMultiplier(float weaponFireRateMultiplier);
	void setWeaponDamageType(wxString damageType);
	void setWeaponAudioItem(wxString audioItem);

	bool getValidWeaponModelFound();
	wxString getWeaponTemplate();
	wxString getWeaponName();
	wxString getWeaponId();
	wxString getWeaponModel();
	wxString getAudioItem();
	float getWeaponDamage();
	float getWeaponRange();
	wxString getAmmoType();
	float getWeaponLOD();
	float getWeaponReloadSpeedMultiplier();
	float getWeaponFireRateMultiplier();
	wxString getWeaponDamageType();
	wxString getWeaponAudioItem();

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

private:
	wxString weaponTemplate;
	wxString weaponName;
	wxString weaponId;
	wxString weaponModel;

	wxString audioItem;
	float weaponDamage;
	float weaponRange;
	wxString ammoType;
	float weaponLOD;
	float weaponReloadSpeedMultiplier;
	float weaponFireRateMultiplier;
	wxString damageType;

	bool validWeaponModelFound;

	std::vector<std::string> weaponAssets[50] = {};
};

