#include "cWeapon.h"

cWeapon::cWeapon()
{
	weaponTemplate = wxString("WEAPON_ASSAULTRIFLE");
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

void cWeapon::exportWeapon()
{
	//TODO
}
