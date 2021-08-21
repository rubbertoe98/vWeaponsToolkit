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

class vWeaponsToolkit : public wxFrame
{
public:
	vWeaponsToolkit();

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
	void searchForWeaponAssets(const std::wstring& directory);
	void validateWeaponAssets();
};

