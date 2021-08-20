#include "vWeaponsToolkit.h"

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "vWeaponsToolkit", wxPoint((wxSystemSettings::GetMetric(wxSYS_SCREEN_X) / 2) - (800/2), (wxSystemSettings::GetMetric(wxSYS_SCREEN_Y) / 2) - (500 /2)), wxSize(windowWidth, windowHeight))
{
	// Initialize wxWidgets Menu.

	// MenuBar
	wxMenuBar* menuBar = new wxMenuBar;
	
	wxMenu* fileMenu = new wxMenu;
	fileMenu->Append(wxID_ANY, wxT("&New Add-on Weapon"));
	fileMenu->Append(wxID_EXIT);

	wxMenu* emptyMenu = new wxMenu;

	menuBar->Append(fileMenu, "&File");;
	SetMenuBar(menuBar);

	// Top-level panel to hold all the contents of the frame
	wxPanel* panel = new wxPanel(this, wxID_ANY);	

	// Tabs
	menuTabs = new wxAuiNotebook(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_NB_TOP);
	panelTab = new wxPanel(menuTabs, wxID_ANY);
	menuTabs->AddPage(panelTab, L"Add-on Weapon");

	settingsTab = new wxPanel(menuTabs, wxID_ANY);
	menuTabs->AddPage(settingsTab, L"Settings");

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
}