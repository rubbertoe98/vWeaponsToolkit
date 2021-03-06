#pragma once
#include <string>

class cWeaponComponent
{
public:
	cWeaponComponent();
	void setComponentName(std::string componentName);
	void setComponentTemplate(std::string componentTemplate);
	void setModelName(std::string modelName);
	void setClipSize(int clipSize);
	void setModelLOD(int modelLOD);
	void setAmmoInfo(std::string ammoInfo);
	void setComponentEnabled(bool enabled);

	std::string getComponentTemplate();
	std::string getComponentName();
	std::string getModelName();
	int getClipSize();
	int getModelLOD();
	std::string getAmmoInfo();
	bool isComponentEnabled();

private:
	std::string componentTemplate;
	std::string componentName;
	std::string modelName;

	int clipSize;
	int modelLOD;
	std::string ammoInfo;
	bool enabled;
};

