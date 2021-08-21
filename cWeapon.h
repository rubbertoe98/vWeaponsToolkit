#pragma once
#include <wx/string.h>

class cWeapon
{
public:
	cWeapon();

	void setWeaponTemplate(wxString weaponTemplate);
	void setWeaponName(wxString weaponName);
	void setWeaponId(wxString weaponId);
	void setWeaponModel(wxString weaponModel);

	wxString getWeaponTemplate();
	wxString getWeaponName();
	wxString getWeaponId();
	wxString getWeaponModel();

	void exportWeapon();

private:
	wxString weaponTemplate;
	wxString weaponName;
	wxString weaponId;
	wxString weaponModel;

	char* weaponAssets[50] = {};
};

