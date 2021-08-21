#include "cWeaponsToolkit.h"

int cWeaponsToolkit::getWeaponCount() {
	int count = 0;

	for (const char* i : nativeWeapons) {
		if (i)
			count += 1;
	}
	return count;
}

void cWeaponsToolkit::onImportDirectoryChanged(wxCommandEvent& evt) {
	const std::string tmpDir = importerDirectoryPicker->GetPath().ToStdString();

	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	std::wstring wide = converter.from_bytes(tmpDir);

	searchForWeaponAssets(wide);
	validateWeaponAssets();
}

void cWeaponsToolkit::onWeaponTemplateChanged(wxCommandEvent& evt)
{
	generatedWeapon->setWeaponTemplate(evt.GetString());
}

void cWeaponsToolkit::onWeaponNameChanged(wxCommandEvent& evt)
{
	generatedWeapon->setWeaponName(evt.GetString());
}

void cWeaponsToolkit::onWeaponIdChanged(wxCommandEvent& evt)
{
	generatedWeapon->setWeaponId(evt.GetString());
}

void cWeaponsToolkit::onWeaponModelChanged(wxCommandEvent& evt)
{
	generatedWeapon->setWeaponModel(evt.GetString());
	validateWeaponAssets();
}

void cWeaponsToolkit::onCreateWeaponNextButtonChanged(wxCommandEvent& evt)
{
	if (!generatedWeapon->getValidWeaponModelFound()) {
		wxMessageBox(wxT("No valid weapon model found."), wxT("vWeaponToolkit"), wxICON_ERROR);
	}
	else {
		menuTabs->SetSelection(1);
	}
}

void cWeaponsToolkit::validateWeaponAssets()
{
	for (int i = 0; i < filesFoundListCtrl->GetItemCount(); i++) {
		filesFoundListCtrl->SetItemTextColour(i, wxColour(*wxBLACK));
	}

	for (int i = 0; i < filesFoundListCtrl->GetItemCount(); i++) {
		wxString s = filesFoundListCtrl->GetItemText(i);
		if (s == generatedWeapon->getWeaponModel() + ".ydr") {
			//Found ydr model, now look for _hi ydr & textures.
			filesFoundListCtrl->SetItemTextColour(i, wxColour(70,200,0));
			generatedWeapon->setValidWeaponModelFound(true);

			for (int i = 0; i < filesFoundListCtrl->GetItemCount(); i++) {
				wxString s = filesFoundListCtrl->GetItemText(i);
				if (s == generatedWeapon->getWeaponModel() + "_hi.ydr") {
					filesFoundListCtrl->SetItemTextColour(i, wxColour(70, 200, 0));
					generatedWeapon->addWeaponAsset(std::string(generatedWeapon->getWeaponModel() + "_hi.ydr"));
				}
				else if (s == generatedWeapon->getWeaponModel() + ".ytd") {
					filesFoundListCtrl->SetItemTextColour(i, wxColour(70, 200, 0));
					generatedWeapon->addWeaponAsset(std::string(generatedWeapon->getWeaponModel() + ".ytd"));
				}
				else if (s == generatedWeapon->getWeaponModel() + "+hi.ytd") {
					filesFoundListCtrl->SetItemTextColour(i, wxColour(70, 200, 0));
					generatedWeapon->addWeaponAsset(std::string(generatedWeapon->getWeaponModel() + "+hi.ytd"));
				}
				//Addon Mods/Components
				else if (s.find("_mag1") != std::string::npos) {
					filesFoundListCtrl->SetItemTextColour(i, wxColour(0, 70, 200));
					generatedWeapon->addWeaponAsset(std::string(s));
				}
				else if (s.find("_mag2") != std::string::npos) {
					filesFoundListCtrl->SetItemTextColour(i, wxColour(0, 70, 200));
					generatedWeapon->addWeaponAsset(std::string(s));
				}
				else if (s.find("_afgrip") != std::string::npos) {
					filesFoundListCtrl->SetItemTextColour(i, wxColour(0, 70, 200));
					generatedWeapon->addWeaponAsset(std::string(s));
				}
				else if (s.find("_supp") != std::string::npos) {
					filesFoundListCtrl->SetItemTextColour(i, wxColour(0, 70, 200));
					generatedWeapon->addWeaponAsset(std::string(s));
				}
				else if (s.find("_medium") != std::string::npos) {
					filesFoundListCtrl->SetItemTextColour(i, wxColour(0, 70, 200));
					generatedWeapon->addWeaponAsset(std::string(s));
				}
				else if(s != generatedWeapon->getWeaponModel() + ".ydr")
				{
					filesFoundListCtrl->SetItemTextColour(i, wxColour(200, 40, 0));
				}
			}
		}
	}
}

wxString cWeaponsToolkit::removeWeaponFileExtension(wxString s)
{
	std::string ext_ydr = ".ydr";

	size_t pos_ydr = s.find(ext_ydr);
	if (pos_ydr != std::string::npos)
	{
		// If found then erase it from string
		s.erase(pos_ydr, ext_ydr.length());
	}

	std::string ext_ytd = ".ytd";

	size_t pos_ytd = s.find(ext_ytd);
	if (pos_ytd != std::string::npos)
	{
		// If found then erase it from string
		s.erase(pos_ytd, ext_ytd.length());
	}
	return s;
}

void cWeaponsToolkit::searchForWeaponAssets(const std::wstring& directory)
{
	std::wstring fullDir = directory + L"\\*";
	WIN32_FIND_DATAW file;
	HANDLE search_handle = FindFirstFileW(fullDir.c_str(), &file);
	if (search_handle != INVALID_HANDLE_VALUE)
	{
		std::vector<std::wstring> directories;
		int filesFound = 0;
		filesFoundListCtrl->DeleteAllItems();
		do
		{
			if (file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if ((!lstrcmpW(file.cFileName, L".")) || (!lstrcmpW(file.cFileName, L"..")))
					continue;
			}

			fullDir = directory + L"\\" + std::wstring(file.cFileName);

			if (std::wstring(file.cFileName).find(L'.ytd') != std::string::npos || std::wstring(file.cFileName).find(L'.ydr') != std::string::npos) {
				filesFoundListCtrl->InsertItem(0, file.cFileName);
				filesFound += 1;
			}

			if (file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				directories.push_back(fullDir);
		} while (FindNextFileW(search_handle, &file));
		FindClose(search_handle);

		if (filesFound == 0) {			
			int index = filesFoundListCtrl->InsertItem(0, "No files found.");
			filesFoundListCtrl->SetItemTextColour(index, wxColour(200, 40, 0));
		}
	}
}

cWeaponsToolkit::cWeaponsToolkit() : wxFrame(nullptr, wxID_ANY, "vWeaponsToolkit", wxPoint((wxSystemSettings::GetMetric(wxSYS_SCREEN_X) / 2) - (800/2), (wxSystemSettings::GetMetric(wxSYS_SCREEN_Y) / 2) - (500 /2)), wxSize(windowWidth, windowHeight))
{
	// Initialize wxWidgets Menu.

	// MenuBar
	wxMenuBar* menuBar = new wxMenuBar;
	
	wxMenu* fileMenu = new wxMenu;
	fileMenu->Append(wxID_ANY, wxT("&New Add-on Weapon"));
	fileMenu->Append(wxID_EXIT);
	fileMenu->AppendSeparator();
	fileMenu->Append(wxID_ANY, wxT("&Made by Robbster"));

	wxMenu* emptyMenu = new wxMenu;

	menuBar->Append(fileMenu, "&File");;
	SetMenuBar(menuBar);

	// Top-level panel to hold all the contents of the frame
	wxPanel* panel = new wxPanel(this, wxID_ANY);	

	// Tabs
	menuTabs = new wxAuiNotebook(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_NB_TOP);
	createWeaponPanel = new wxPanel(menuTabs, wxID_ANY);
	menuTabs->AddPage(createWeaponPanel, L"Create Add-on Weapon");

	configTab = new wxPanel(menuTabs, wxID_ANY);
	menuTabs->AddPage(configTab, L"Configuration");

	componentsTab = new wxPanel(menuTabs, wxID_ANY);
	menuTabs->AddPage(componentsTab, L"Components");

	exportTab = new wxPanel(menuTabs, wxID_ANY);
	menuTabs->AddPage(exportTab, L"Export");

	debugLogTab = new wxPanel(menuTabs, wxID_ANY);
	menuTabs->AddPage(debugLogTab, L"Debug Log");

	// Menu Sizers
	wxBoxSizer* panelSizer = new wxBoxSizer(wxHORIZONTAL);
	panelSizer->Add(menuTabs, 1, wxEXPAND);
	panel->SetSizer(panelSizer);

	wxBoxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL);
	topSizer->Add(panel, 1, wxEXPAND);
	SetSizerAndFit(topSizer);
	SetMinSize(wxSize(windowWidth, windowHeight));
	SetMaxSize(wxSize(windowWidth, windowHeight));


	//TAB 1 - Create Add-on Weapon
	filesFoundListCtrl = new wxListCtrl(createWeaponPanel, wxID_ANY, wxPoint(20, 40), wxSize(200, 320), wxLC_REPORT, wxDefaultValidator);
	wxListItem col0;
	col0.SetId(0);
	col0.SetText(_("Files Found"));
	col0.SetWidth(200);
	filesFoundListCtrl->InsertColumn(0, col0);

	importerDirectoryPicker = new wxDirPickerCtrl(createWeaponPanel, wxID_ANY, "Import Folder", "", wxPoint(20, 370), wxSize(625, 25));
	wxButton* nextButton = new wxButton(createWeaponPanel, wxID_ANY, "Next", wxPoint(675, 370));

	wxStaticText* weaponTemplateStaticText = new wxStaticText(createWeaponPanel, wxID_ANY, "Select Weapon Template", wxPoint(250, 40));
	wxComboBox* weaponTemplate = new wxComboBox(createWeaponPanel, wxID_ANY, "WEAPON_ASSAULTRIFLE", wxPoint(250, 60), wxSize(175, 25));
	weaponTemplate->Append(wxArrayString(cWeaponsToolkit::getWeaponCount(),nativeWeapons));

	wxStaticText* weaponNameStaticText = new wxStaticText(createWeaponPanel, wxID_ANY, "Weapon Name:", wxPoint(250, 100));
	wxTextCtrl* weaponName = new wxTextCtrl(createWeaponPanel, wxID_ANY, "AK-47", wxPoint(250,120), wxSize(175, 25));

	wxStaticText* weaponIdStaticText = new wxStaticText(createWeaponPanel, wxID_ANY, "Weapon ID:", wxPoint(250, 160));
	wxTextCtrl* weaponId = new wxTextCtrl(createWeaponPanel, wxID_ANY, "WEAPON_AK47", wxPoint(250,180), wxSize(175, 25));

	wxStaticText* weaponModelStaticText = new wxStaticText(createWeaponPanel, wxID_ANY, "Weapon Model:", wxPoint(250, 220));
	wxTextCtrl* weaponModel = new wxTextCtrl(createWeaponPanel, wxID_ANY, "w_ar_assaultrifle", wxPoint(250,240), wxSize(175, 25));

	//Event Handlers
	importerDirectoryPicker->Bind(wxEVT_COMMAND_DIRPICKER_CHANGED, &cWeaponsToolkit::onImportDirectoryChanged, this);
	weaponTemplate->Bind(wxEVT_COMBOBOX, &cWeaponsToolkit::onWeaponTemplateChanged, this);
	nextButton->Bind(wxEVT_BUTTON, &cWeaponsToolkit::onCreateWeaponNextButtonChanged, this);
	weaponName->Bind(wxEVT_TEXT, &cWeaponsToolkit::onWeaponNameChanged, this);
	weaponId->Bind(wxEVT_TEXT, &cWeaponsToolkit::onWeaponIdChanged, this);
	weaponModel->Bind(wxEVT_TEXT, &cWeaponsToolkit::onWeaponModelChanged, this);

}