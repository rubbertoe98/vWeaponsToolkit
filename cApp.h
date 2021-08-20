#pragma once

#include "wx/wx.h"
#include "vWeaponsToolkit.h"

class cApp : public wxApp
{
public:
	virtual bool OnInit();

private:
	cMain* m_frame1 = nullptr;
};

