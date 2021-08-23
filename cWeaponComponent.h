#pragma once
#include <string>

class cWeaponComponent
{
public:
	cWeaponComponent();
	void setComponentName(std::string componentName);
	void setModelName(std::string modelName);
	void setClipSize(int clipSize);
	void setAmmoInfo(std::string ammoInfo);

	std::string getComponentName();
	std::string getModelName();
	int getClipSize();
	std::string getAmmoInfo();

private:
	std::string componentName;
	std::string modelName;
	
	int clipSize;
	std::string ammoInfo; //e.g "AMMO_RIFLE_FMJ" (ctrl-f <AmmoInfo> in metas)
};

