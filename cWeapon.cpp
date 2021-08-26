#include "cWeapon.h"

cWeapon::cWeapon()
{
	weaponTemplate = std::string("WEAPON_ASSAULTRIFLE");
	weaponName = "AK-47";
	weaponId = "WEAPON_AK47";
	weaponModel = "w_ar_assaultrifle";
	validWeaponModelFound = false;
	weaponLOD = 500;
}

void cWeapon::setWeaponTemplate(std::string _weaponTemplate)
{
	weaponTemplate = _weaponTemplate;
}

void cWeapon::setWeaponName(std::string _weaponName)
{
	weaponName = _weaponName;
}

void cWeapon::setWeaponId(std::string _weaponId)
{
	weaponId = _weaponId;
}

void cWeapon::setWeaponModel(std::string _weaponModel)
{
	weaponModel = _weaponModel;
}

void cWeapon::addWeaponAsset(cWeaponAsset* weaponAsset)
{
	weaponAssets.push_back(weaponAsset);
}

void cWeapon::setValidWeaponModelFound(bool found)
{
	validWeaponModelFound = found;
}

void cWeapon::setAudioItem(std::string _audioItem)
{
	audioItem = _audioItem;
}

void cWeapon::setWeaponDamage(float _weaponDamage)
{
	weaponDamage = _weaponDamage;
}

void cWeapon::setWeaponRange(float _weaponRange)
{
	weaponRange = _weaponRange;
}

void cWeapon::setAmmoType(std::string _ammoType)
{
	ammoType = _ammoType;
}

void cWeapon::setWeaponLOD(int _weaponLOD)
{
	weaponLOD = _weaponLOD;
}

void cWeapon::setWeaponReloadSpeedMultiplier(float _weaponReloadSpeedMultiplier)
{
	weaponReloadSpeedMultiplier = _weaponReloadSpeedMultiplier;
}

void cWeapon::setWeaponFireRateMultiplier(float _weaponFireRateMultiplier)
{
	weaponFireRateMultiplier = _weaponFireRateMultiplier;
}

void cWeapon::setWeaponDamageType(std::string _damageType)
{
	damageType = _damageType;
}

void cWeapon::setWeaponAudioItem(std::string _audioItem)
{
	audioItem = _audioItem;
}

bool cWeapon::getValidWeaponModelFound()
{
	return validWeaponModelFound;
}

std::string cWeapon::getWeaponTemplate()
{
	return weaponTemplate;
}

std::string cWeapon::getWeaponName()
{
	return weaponName;
}

std::string cWeapon::getWeaponId()
{
	return weaponId;
}

std::string cWeapon::getWeaponModel()
{
	return weaponModel;
}

std::string cWeapon::getAudioItem()
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

std::string cWeapon::getAmmoType()
{
	return ammoType;
}

int cWeapon::getWeaponLOD()
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

std::string cWeapon::getWeaponDamageType()
{
	return damageType;
}

std::string cWeapon::getWeaponAudioItem()
{
	return audioItem;
}

void cWeapon::exportWeapon()
{
	//TODO
}
