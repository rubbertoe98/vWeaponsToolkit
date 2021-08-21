#include "cWeapon.h"

cWeapon::cWeapon()
{
	weaponTemplate = wxString("WEAPON_ASSAULTRIFLE");
	weaponName = "";
	weaponId = "";
	weaponModel = "";
	validWeaponModelFound = false;
}

void cWeapon::setWeaponTemplate(wxString wT)
{
	weaponTemplate = wT;
}

void cWeapon::setWeaponName(wxString wN)
{
	weaponName = wN;
}

void cWeapon::setWeaponId(wxString wI)
{
	weaponId = wI;
}

void cWeapon::setWeaponModel(wxString wM)
{
	weaponModel = wM;
}

void cWeapon::addWeaponAsset(std::string weaponAsset)
{
	weaponAssets->push_back(weaponAsset);
}

void cWeapon::setValidWeaponModelFound(bool found)
{
	validWeaponModelFound = found;
}

void cWeapon::setAudioItem(wxString weaponAudio)
{
	audioItem = weaponAudio;
}

void cWeapon::setWeaponDamage(float damage)
{
	weaponDamage = damage;
}

void cWeapon::setWeaponRange(float range)
{
	weaponRange = range;
}

void cWeapon::setAmmoType(wxString type)
{
	ammoType = type;
}

void cWeapon::setWeaponLOD(float lod)
{
	weaponLOD = lod;
}

void cWeapon::setWeaponReloadSpeedMultiplier(float multiplier)
{
	weaponReloadSpeedMultiplier = multiplier;
}

void cWeapon::setWeaponFireRateMultiplier(float multiplier)
{
	weaponFireRateMultiplier = multiplier;
}

void cWeapon::setWeaponDamageType(wxString type)
{
	damageType = type;
}

bool cWeapon::getValidWeaponModelFound()
{
	return validWeaponModelFound;
}

wxString cWeapon::getWeaponTemplate()
{
	return weaponTemplate;
}

wxString cWeapon::getWeaponName()
{
	return weaponName;
}

wxString cWeapon::getWeaponId()
{
	return weaponId;
}

wxString cWeapon::getWeaponModel()
{
	return weaponModel;
}

wxString cWeapon::getAudioItem()
{
	return audioItem;
}

float cWeapon::getWeaponDamage()
{
	return weaponDamage;
}

float cWeapon::getWeaponRange()
{
	return weaponRange;
}

wxString cWeapon::getAmmoType()
{
	return ammoType;
}

float cWeapon::getWeaponLOD()
{
	return weaponLOD;
}

float cWeapon::getWeaponReloadSpeedMultiplier()
{
	return weaponReloadSpeedMultiplier;
}

float cWeapon::getWeaponFireRateMultiplier()
{
	return weaponFireRateMultiplier;
}

wxString cWeapon::getWeaponDamageType()
{
	return damageType;
}

void cWeapon::exportWeapon()
{
	//TODO
}
