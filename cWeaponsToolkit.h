#pragma once

#include "wx/wx.h"
#include <wx/aui/aui.h>
#include <wx/filepicker.h>
#include <wx/richtext/richtextprint.h>
#include <wx/listctrl.h>
#include "cWeapon.h"

class cWeaponsToolkit : public wxFrame
{
public:
	cWeaponsToolkit();

private:
	wxAuiNotebook* menuTabs;
	wxPanel* createWeaponPanel;
	wxPanel* configTab;
	wxPanel* componentsTab;
	wxPanel* exportTab;
	wxPanel* debugLogTab;
	wxListCtrl* filesFoundListCtrl;
	wxDirPickerCtrl* importerDirectoryPicker;
	wxComboBox* audioItemComboBox;
	wxTextCtrl* weaponNameTextCtrl;
	wxTextCtrl* weaponIdTextCtrl;
	wxTextCtrl* weaponModelTextCtrl;
	wxComboBox* damageTypesComboxBox;
	wxTextCtrl* weaponDamageTextCtrl;
	wxTextCtrl* weaponRangeTextCtrl;
	wxTextCtrl* weaponLODTextCtrl;
	wxTextCtrl* weaponReloadModifierTextCtrl;
	wxTextCtrl* weaponFireRateModifierTextCtrl;
	wxComboBox* ammoTypesComboBox;
	wxListCtrl* weaponComponentsListCtrl;
	wxComboBox* weaponComponentsComboBox;

	int windowWidth = 800;
	int windowHeight = 500;
	int selectedComponent;

	int getWeaponCount();
	int getAudioItemsCount();
	int getAmmoTypesCount();
	int getDamageTypesCount();
	int getWeaponComponentCount();
	void onImportDirectoryChanged(wxCommandEvent& evt);
	void onWeaponTemplateChanged(wxCommandEvent& evt);
	void onWeaponNameChanged(wxCommandEvent& evt);
	void onWeaponIdChanged(wxCommandEvent& evt);
	void onWeaponModelChanged(wxCommandEvent& evt);
	void onCreateWeaponNextButtonChanged(wxCommandEvent& evt);
	void searchForWeaponAssets(const std::wstring& directory);
	void validateWeaponAssets();
	wxString removeWeaponFileExtension(wxString s);
	void onAddComponent(wxCommandEvent& evt);
	void onRemoveComponent(wxCommandEvent& evt);
	void onSelectComponent(wxCommandEvent& evt);

	cWeapon* generatedWeapon = new cWeapon();
};

