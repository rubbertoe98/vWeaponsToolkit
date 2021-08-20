#pragma once

#include "wx/wx.h"
#include <wx/aui/aui.h>

class cMain : public wxFrame
{
public:
	cMain();

private:
	wxAuiNotebook* menuTabs;
	wxPanel* panelTab;
	wxPanel* settingsTab;
	wxPanel* debugLogTab;
};

