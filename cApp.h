#pragma once

#include "wx/wx.h"
#include "cWeaponsToolkit.h"

class cApp : public wxApp
{
public:
	virtual bool OnInit();

private:
	cWeaponsToolkit* m_frame1 = nullptr;
};

