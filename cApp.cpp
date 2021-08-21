#include "cApp.h"

wxIMPLEMENT_APP(cApp);

bool cApp::OnInit()
{
	m_frame1 = new cWeaponsToolkit();
	m_frame1->Show();

	return true;
}
