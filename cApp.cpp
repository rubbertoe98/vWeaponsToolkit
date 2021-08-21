#include "cApp.h"

wxIMPLEMENT_APP(cApp);

bool cApp::OnInit()
{
	m_frame1 = new vWeaponsToolkit();
	m_frame1->Show();

	return true;
}
