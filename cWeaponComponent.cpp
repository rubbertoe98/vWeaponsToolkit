#include "cWeaponComponent.h"

cWeaponComponent::cWeaponComponent()
{
	componentTemplate = "";
	componentName = "";
	modelName = "";
	clipSize = 0;
	ammoInfo = "";
	modelLOD = 300.0;
}

void cWeaponComponent::setComponentName(std::string _componentName)
{
	componentName = _componentName;
}

void cWeaponComponent::setComponentTemplate(std::string _componentTemplate)
{
	componentTemplate = _componentTemplate;
}

void cWeaponComponent::setModelName(std::string _modelName)
{
	modelName = _modelName;
}

void cWeaponComponent::setClipSize(int _clipSize)
{
	clipSize = _clipSize;
}

void cWeaponComponent::setModelLOD(int _modelLOD)
{
	modelLOD = _modelLOD;
}

void cWeaponComponent::setAmmoInfo(std::string _ammoInfo)
{
	ammoInfo = _ammoInfo;
}

std::string cWeaponComponent::getComponentTemplate()
{
	return componentTemplate;
}

std::string cWeaponComponent::getComponentName()
{
	return componentName;
}

std::string cWeaponComponent::getModelName()
{
	return modelName;
}

int cWeaponComponent::getClipSize()
{
	return clipSize;
}

int cWeaponComponent::getModelLOD()
{
	return modelLOD;
}

std::string cWeaponComponent::getAmmoInfo()
{
	return ammoInfo;
}
