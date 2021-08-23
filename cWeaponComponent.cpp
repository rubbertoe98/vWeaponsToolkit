#include "cWeaponComponent.h"

cWeaponComponent::cWeaponComponent()
{

}

void cWeaponComponent::setComponentName(std::string _componentName)
{
	componentName = _componentName;
}

void cWeaponComponent::setModelName(std::string _modelName)
{
	modelName = _modelName;
}

void cWeaponComponent::setClipSize(int _clipSize)
{
	clipSize = _clipSize;
}

void cWeaponComponent::setAmmoInfo(std::string _ammoInfo)
{
	ammoInfo = _ammoInfo;
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

std::string cWeaponComponent::getAmmoInfo()
{
	return ammoInfo;
}
