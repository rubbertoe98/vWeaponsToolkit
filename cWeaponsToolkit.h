#pragma once

#include "wx/wx.h"
#include <wx/aui/aui.h>
#include <wx/filepicker.h>
#include <Windows.h>
#include <string>
#include <vector> 
#include <locale>
#include <codecvt>
#include <wx/richtext/richtextprint.h>
#include "cWeapon.h"
#include <wx/msgdlg.h>

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
	wxListBox* filesFoundListbox;
	wxDirPickerCtrl* importerDirectoryPicker;

	int windowWidth = 800;
	int windowHeight = 500;

	const char* nativeWeapons[100] = {
		"WEAPON_ASSAULTRIFLE",
		"WEAPON_CARBINE"
	};

	int getWeaponCount();
	void onImportDirectoryChanged(wxCommandEvent& evt);
	void onWeaponTemplateChanged(wxCommandEvent& evt);
	void onWeaponNameChanged(wxCommandEvent& evt);
	void onWeaponIdChanged(wxCommandEvent& evt);
	void onWeaponModelChanged(wxCommandEvent& evt);
	void onCreateWeaponNextButtonChanged(wxCommandEvent& evt);
	void searchForWeaponAssets(const std::wstring& directory);
	void validateWeaponAssets();

	cWeapon* generatedWeapon = new cWeapon();
};

