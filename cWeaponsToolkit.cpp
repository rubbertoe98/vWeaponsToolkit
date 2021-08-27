#include "cWeaponsToolkit.h"
#include <Windows.h>
#include <string>
#include <vector> 
#include <locale>
#include <codecvt>
#include <wx/msgdlg.h>
#include "vendor/rapidxml/rapidxml_ext.h"
#include <fstream>
#include <wx/checkbox.h>
#include <direct.h>
#include "cWeaponAsset.h"

int cWeaponsToolkit::getWeaponCount() {
	int count = 0;

	for (const char* i : generatedWeapon->nativeWeapons) {
		if (i)
			count += 1;
	}
	return count;
}

int cWeaponsToolkit::getWeaponComponentCount() {
	int count = 0;

	for (const char* i : generatedWeapon->nativeComponents) {
		if (i)
			count += 1;
	}
	return count;
}

int cWeaponsToolkit::getAmmoInfoCount() {
	int count = 0;

	for (const char* i : generatedWeapon->nativeAmmoInfos) {
		if (i)
			count += 1;
	}
	return count;
}

int cWeaponsToolkit::getNextAvailableSlotId()
{
	std::ifstream slotFILE;
	slotFILE.open("SLOT", std::ios::in);

	if (slotFILE.fail())
	{
		//wxMessageBox("Failed to find SLOT file, re-creating.", "vWeaponsToolkit", wxICON_ERROR);
		std::ofstream outfile;
		outfile.open("SLOT", std::ios::out);
		outfile << 400;
		return 400;
	}
	else {
		char charSlotId[10];
		slotFILE.getline(charSlotId, 10);
		int slotId = std::stoi(std::string(charSlotId));

		std::ofstream outfile;
		outfile.open("SLOT", std::ios::out | std::ios::trunc);
		outfile << (slotId + 1);

		return slotId;
	}

	return 400;
}

int cWeaponsToolkit::getAudioItemsCount()
{
	int count = 0;

	for (const char* i : generatedWeapon->audioItems) {
		if (i)
			count += 1;
	}
	return count;
}

int cWeaponsToolkit::getAmmoTypesCount()
{
	int count = 0;

	for (const char* i : generatedWeapon->ammoTypes) {
		if (i)
			count += 1;
	}
	return count;
}

int cWeaponsToolkit::getDamageTypesCount()
{
	int count = 0;

	for (const char* i : generatedWeapon->damageTypes) {
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
	generatedWeapon->setWeaponTemplate(std::string(evt.GetString()));
	rapidxml::xml_document<> doc;
	rapidxml::xml_node<>* root_node;
	std::ifstream theFile(std::string( "templates/weapons/" + generatedWeapon->getWeaponTemplate() + "/weapons.meta"));
	std::vector<char> buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');
	doc.parse<0>(&buffer[0]);
	
	root_node = doc.first_node("CWeaponInfoBlob");

	for (rapidxml::xml_node<>* infos_1 = root_node->first_node("Infos"); infos_1; infos_1 = infos_1->next_sibling())
	{
		for (rapidxml::xml_node<>* item_1 = infos_1->first_node("Item"); item_1; item_1 = item_1->next_sibling())
		{
			for (rapidxml::xml_node<>* infos_2 = item_1->first_node("Infos"); infos_2; infos_2 = infos_2->next_sibling())
			{
				for (rapidxml::xml_node<>* item_2 = infos_2->first_node("Item"); item_2; item_2 = item_2->next_sibling())
				{
					for (rapidxml::xml_node<>* weapon_node = item_2->first_node("Name"); weapon_node; weapon_node = weapon_node->next_sibling())
					{
						if (std::string(weapon_node->name()) == "Model") {
							generatedWeapon->setWeaponModel(weapon_node->value());
							weaponModelTextCtrl->SetValue(weapon_node->value());
						}
						else if (std::string(weapon_node->name()) == "Audio") {
							generatedWeapon->setAudioItem(weapon_node->value());
							audioItemComboBox->SetValue(wxString(weapon_node->value()));
						}
						else if (std::string(weapon_node->name()) == "DamageType") {
							generatedWeapon->setWeaponDamageType(weapon_node->value());
							damageTypesComboxBox->SetValue(wxString(weapon_node->value()));
						}
						else if (std::string(weapon_node->name()) == "Damage") {
							if (std::string(weapon_node->first_attribute()->name()) == "value") {
								generatedWeapon->setWeaponDamage(std::stof(weapon_node->first_attribute()->value()));
								weaponDamageTextCtrl->SetValue(wxString(weapon_node->first_attribute()->value()));
							}
						}
						else if (std::string(weapon_node->name()) == "WeaponRange") {
							if (std::string(weapon_node->first_attribute()->name()) == "value") {
								generatedWeapon->setWeaponRange(std::stof(weapon_node->first_attribute()->value()));
								weaponRangeTextCtrl->SetValue(wxString(weapon_node->first_attribute()->value()));
							}
						}
						else if (std::string(weapon_node->name()) == "AmmoInfo") {
							if (std::string(weapon_node->first_attribute()->name()) == "ref") {
								generatedWeapon->setAmmoType(weapon_node->first_attribute()->value());
								ammoTypesComboBox->SetValue(wxString(weapon_node->first_attribute()->value()));
							}
						}
						else if (std::string(weapon_node->name()) == "AnimReloadRate") {
							if (std::string(weapon_node->first_attribute()->name()) == "value") {
								generatedWeapon->setWeaponReloadSpeedMultiplier(std::stof(weapon_node->first_attribute()->value()));
								weaponReloadModifierTextCtrl->SetValue(wxString(weapon_node->first_attribute()->value()));
							}
						}
						else if (std::string(weapon_node->name()) == "HeadShotDamageModifierPlayer") {
							if (std::string(weapon_node->first_attribute()->name()) == "value") {
								generatedWeapon->setWeaponHeadShotDamageModifierPlayer(std::stof(weapon_node->first_attribute()->value()));
								weaponHeadshotDamageModifierTextCtrl->SetValue(wxString(weapon_node->first_attribute()->value()));
							}
						}
						//todo weapon fire rate in weaponanimations.meta
					}
				}
			}
		}
	}
}

void cWeaponsToolkit::onWeaponNameChanged(wxCommandEvent& evt)
{
	generatedWeapon->setWeaponName(std::string(evt.GetString()));
}

void cWeaponsToolkit::onWeaponIdChanged(wxCommandEvent& evt)
{
	generatedWeapon->setWeaponId(std::string(evt.GetString()));
}

void cWeaponsToolkit::onWeaponModelChanged(wxCommandEvent& evt)
{
	generatedWeapon->setWeaponModel(std::string(evt.GetString()));
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

	generatedWeapon->setValidWeaponModelFound(false);
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
				}
				else if (s == generatedWeapon->getWeaponModel() + ".ytd") {
					filesFoundListCtrl->SetItemTextColour(i, wxColour(70, 200, 0));
				}
				else if (s == generatedWeapon->getWeaponModel() + "+hi.ytd") {
					filesFoundListCtrl->SetItemTextColour(i, wxColour(70, 200, 0));
				}
				//Addon Mods/Components
				else if (s.find("_mag1") != std::string::npos) {
					filesFoundListCtrl->SetItemTextColour(i, wxColour(0, 70, 200));
				}
				else if (s.find("_mag2") != std::string::npos) {
					filesFoundListCtrl->SetItemTextColour(i, wxColour(0, 70, 200));
				}
				else if (s.find("_afgrip") != std::string::npos) {
					filesFoundListCtrl->SetItemTextColour(i, wxColour(0, 70, 200));
				}
				else if (s.find("_supp") != std::string::npos) {
					filesFoundListCtrl->SetItemTextColour(i, wxColour(0, 70, 200));
				}
				else if (s.find("_medium") != std::string::npos) {
					filesFoundListCtrl->SetItemTextColour(i, wxColour(0, 70, 200));
				}
				else if(s != generatedWeapon->getWeaponModel() + ".ydr")
				{
					filesFoundListCtrl->SetItemTextColour(i, wxColour(200, 40, 0));
				}
			}
		}
	}
}

std::string cWeaponsToolkit::removeWeaponFileExtension(std::string s)
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

void cWeaponsToolkit::onAddComponent(wxCommandEvent& evt)
{
	cWeaponComponent* component = new cWeaponComponent;
	std::string componentName = std::string(weaponComponentsComboBox->GetStringSelection());

	if (componentName == "")
		componentName = "COMPONENT_AT_RAILCOVER_01";

	component->setComponentTemplate(componentName);
	component->setComponentName(componentName);
	component->setModelName(std::string(componentModelNameTextCtrl->GetValue()));
	try {
		component->setClipSize(std::stoi(std::string(componentClipSizeTextCtrl->GetValue())));
	}
	catch (const std::invalid_argument& e) {
		component->setClipSize(0);
	}
	catch (const std::out_of_range& e) {
		component->setClipSize(0);
	}	
	component->setAmmoInfo(std::string(weaponAmmoInfoComboBox->GetStringSelection()));

	generatedWeapon->components.push_back(component);
	weaponComponentsListCtrl->InsertItem(0, component->getComponentName());
}
	
void cWeaponsToolkit::onRemoveComponent(wxCommandEvent& evt)
{
	weaponComponentsListCtrl->DeleteItem(selectedComponent);

	cWeaponComponent* component = nullptr;

	try {
		component = generatedWeapon->components.at(selectedComponent);

		if (component)
			generatedWeapon->components.erase(generatedWeapon->components.begin() + selectedComponent);
	}
	catch (const std::out_of_range& e) {
		wxMessageBox("No weapon component to remove.", wxT("vWeaponToolkit"), wxICON_EXCLAMATION);
	}
}

void cWeaponsToolkit::onSelectComponent(wxCommandEvent& evt)
{
	selectedComponent = weaponComponentsListCtrl->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);

	cWeaponComponent* currentComponent = nullptr;

	try {
		currentComponent = generatedWeapon->components.at(selectedComponent);
	}
	catch (const std::out_of_range& e) {

	}

	if (currentComponent) {
		componentNameTextCtrl->SetValue(currentComponent->getComponentName());
		componentModelNameTextCtrl->SetValue(currentComponent->getModelName());
		componentLODTextCtrl->SetValue(std::to_string(currentComponent->getModelLOD()));

		if (currentComponent->getClipSize()) {
			componentClipSizeTextCtrl->SetValue(std::to_string(currentComponent->getClipSize()));
			componentClipSizeTextCtrl->Enable(true);
			componentClipSizeTextCtrl->SetEditable(true);

			weaponAmmoInfoComboBox->Enable(true);
			weaponAmmoInfoComboBox->SetEditable(true);
		}
		else {
			componentClipSizeTextCtrl->SetValue("");
			componentClipSizeTextCtrl->Enable(false);
			componentClipSizeTextCtrl->SetEditable(false);

			weaponAmmoInfoComboBox->Enable(false);
			weaponAmmoInfoComboBox->SetEditable(false);
		}

		weaponAmmoInfoComboBox->SetValue(currentComponent->getAmmoInfo());
		checkboxDevMode->SetValue(currentComponent->isComponentEnabled());
	}
}

void cWeaponsToolkit::onComponentTemplateChanged(wxCommandEvent& evt)
{	
	cWeaponComponent* currentComponent = nullptr;

	try {
		currentComponent = generatedWeapon->components.at(selectedComponent);
	}
	catch (const std::out_of_range& e) {

	}

	if (currentComponent)
		currentComponent->setComponentTemplate(std::string(evt.GetString()));

	rapidxml::xml_document<> doc;
	rapidxml::xml_node<>* root_node;
	std::ifstream theFile(std::string("templates/components/" + evt.GetString() + "/weaponcomponents.meta"));
	std::vector<char> buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');
	doc.parse<0>(&buffer[0]);

	root_node = doc.first_node("CWeaponComponentInfoBlob");

	componentClipSizeTextCtrl->SetValue("");
	componentClipSizeTextCtrl->Enable(false);
	componentClipSizeTextCtrl->SetEditable(false);

	weaponAmmoInfoComboBox->SetValue("Default Ammo");
	weaponAmmoInfoComboBox->Enable(false);
	weaponAmmoInfoComboBox->SetEditable(false);

	for (rapidxml::xml_node<>* infos_1 = root_node->first_node("Infos"); infos_1; infos_1 = infos_1->next_sibling())
	{
		for (rapidxml::xml_node<>* item_1 = infos_1->first_node("Item"); item_1; item_1 = item_1->next_sibling()) {
			for (rapidxml::xml_node<>* component_node = item_1->first_node("Name"); component_node; component_node = component_node->next_sibling()) {
				if (std::string(component_node->name()) == "Name") {
					if (currentComponent)
						currentComponent->setComponentName(component_node->value());

					componentNameTextCtrl->SetValue(component_node->value());
				}
				else if (std::string(component_node->name()) == "Model") {
					if (currentComponent)
						currentComponent->setModelName(component_node->value());

					componentModelNameTextCtrl->SetValue(component_node->value());
				}

				if (std::string(component_node->name()) == "ClipSize") {
					if (std::string(component_node->first_attribute()->name()) == "value") {
						if (currentComponent)
							currentComponent->setClipSize((int)component_node->value());

						componentClipSizeTextCtrl->SetValue(component_node->first_attribute()->value());
						componentClipSizeTextCtrl->Enable(true);
						componentClipSizeTextCtrl->SetEditable(true);

						weaponAmmoInfoComboBox->Enable(true);
						weaponAmmoInfoComboBox->SetEditable(true);
					}
				}

				if (std::string(component_node->name()) == "AmmoInfo") {
					if (currentComponent)
						currentComponent->setAmmoInfo(component_node->value());

					weaponAmmoInfoComboBox->SetValue(component_node->value());
				}
			}
		}
	}
}

void cWeaponsToolkit::onComponentNameChanged(wxCommandEvent& evt)
{
	cWeaponComponent* currentComponent = nullptr;

	try {
		currentComponent = generatedWeapon->components.at(selectedComponent);
	}
	catch (const std::out_of_range& e) {

	}

	if (currentComponent) {
		currentComponent->setComponentName(std::string(evt.GetString()));

		weaponComponentsListCtrl->SetItemText(selectedComponent, evt.GetString());
	}
}

void cWeaponsToolkit::onComponentModelNameChanged(wxCommandEvent& evt)
{
	cWeaponComponent* currentComponent = nullptr;

	try {
		currentComponent = generatedWeapon->components.at(selectedComponent);
	}
	catch (const std::out_of_range& e) {

	}

	if (currentComponent) {
		currentComponent->setModelName(std::string(evt.GetString()));
	}
}

void cWeaponsToolkit::onComponentLODChanged(wxCommandEvent& evt)
{
	cWeaponComponent* currentComponent = nullptr;

	try {
		currentComponent = generatedWeapon->components.at(selectedComponent);
	}
	catch (const std::out_of_range& e) {

	}

	if (currentComponent) {
		try {
			int intLOD = std::stoi(std::string(evt.GetString()));
			currentComponent->setModelLOD(intLOD);
		}
		catch (const std::invalid_argument& e) {
			currentComponent->setModelLOD(0.0);
		}
		catch (const std::out_of_range& e) {
			currentComponent->setModelLOD(0.0);
		}
	}
}

void cWeaponsToolkit::onComponentClipSizeChanged(wxCommandEvent& evt)
{
	cWeaponComponent* currentComponent = nullptr;

	try {
		currentComponent = generatedWeapon->components.at(selectedComponent);
	}
	catch (const std::out_of_range& e) {

	}

	if (currentComponent) {
		try {
			currentComponent->setClipSize(std::stoi(std::string(evt.GetString())));
		}
		catch (const std::invalid_argument& e) {
			currentComponent->setClipSize(0);
		}
		catch (const std::out_of_range& e) {
			currentComponent->setClipSize(0);
		}
	}
}

void cWeaponsToolkit::onComponentAmmoInfoChanged(wxCommandEvent& evt)
{
	cWeaponComponent* currentComponent = nullptr;

	try {
		currentComponent = generatedWeapon->components.at(selectedComponent);
	}
	catch (const std::out_of_range& e) {

	}

	if (currentComponent) {
		try {
			currentComponent->setAmmoInfo(std::string(evt.GetString()));
		}
		catch (const std::invalid_argument& e) {
			currentComponent->setAmmoInfo("");
		}
		catch (const std::out_of_range& e) {
			currentComponent->setAmmoInfo("");
		}
	}
}

void cWeaponsToolkit::onWeaponHeadshotDamageModifierChanged(wxCommandEvent& evt)
{
	generatedWeapon->setWeaponHeadShotDamageModifierPlayer(std::stof(std::string(evt.GetString())));
}

void cWeaponsToolkit::onExportTabPressed(wxCommandEvent& evt)
{
	exportListCtrl->DeleteAllItems();
	for (auto c : generatedWeapon->weaponAssets)
	{
		std::string weapon = getAssetIdFromAsset(c->assetName);
		long itemIndex = exportListCtrl->InsertItem(0, c->assetName); 
		exportListCtrl->SetItem(itemIndex, 1, weapon);

		if (weapon == "N/A")
		{
			exportListCtrl->SetItemTextColour(itemIndex, wxColour(200, 40, 0));
		}
		else
		{
			exportListCtrl->SetItemTextColour(itemIndex, wxColour(70, 200, 0));
		}
	}
}

void cWeaponsToolkit::onComponentEnabledCheckboxChanged(wxCommandEvent& evt)
{
	cWeaponComponent* currentComponent = nullptr;

	try {
		currentComponent = generatedWeapon->components.at(selectedComponent);
	}
	catch (const std::out_of_range& e) {

	}

	if (currentComponent) {
		if (evt.GetSelection()) {
			currentComponent->setComponentEnabled(true);
		}
		else {
			currentComponent->setComponentEnabled(false);
		}
	}
}

void cWeaponsToolkit::onExportDirectoryChanged(wxCommandEvent& evt)
{
	exportDirectory = std::string(exporterDirectoryPicker->GetPath());
}

void cWeaponsToolkit::onExportButtonPressed(wxCommandEvent& evt)
{
	if (!generatedWeapon->getValidWeaponModelFound())
	{
		wxMessageBox("Failed to export weapon, valid model files were not found.", wxT("vWeaponToolkit"), wxICON_ERROR);
		return;
	}

	char c_exportDir[500] = "";
	char c_exportStreamDir[500] = "";
	char c_exportMetasDir[500] = "";

	if (exportDirectory == "") {
		wxMessageBox("Failed to export weapon, no export directory found.", wxT("vWeaponToolkit"), wxICON_ERROR);
		return;
	}

	strcat(c_exportDir, exportDirectory.c_str());
	strcat(c_exportDir, "\\");

	if (generatedWeapon->getWeaponName() == "") {
		wxMessageBox("Failed to export weapon, no weapon ID found.", wxT("vWeaponToolkit"), wxICON_ERROR);
		return;
	}
	strcat(c_exportDir, generatedWeapon->getWeaponName().c_str());
	strcat(c_exportStreamDir, c_exportDir);
	strcat(c_exportMetasDir, c_exportDir);
	strcat(c_exportStreamDir, "\\stream");
	strcat(c_exportMetasDir, "\\meta");

	//Create directories.
	int weapon_result = _mkdir(c_exportDir);
	int stream_result = _mkdir(c_exportStreamDir);
	int metas_result = _mkdir(c_exportMetasDir);

	if (weapon_result == 0) {
		
	}
	else {
		wxMessageBox("Failed to export weapon, failed to create folder.", wxT("vWeaponToolkit"), wxICON_ERROR);
		return;
	}

	//Create fxmanifest
	char c_exportManifestDir[500] = "";
	strcat(c_exportManifestDir, c_exportDir);
	strcat(c_exportManifestDir, "\\fxmanifest.lua");
	std::ofstream manifest(c_exportManifestDir);
	if (manifest.is_open())
	{
		manifest << "fx_version 'cerulean'\n";
		manifest << "games {'gta5'}\n";
		manifest << "description 'Add-on weapon generated using vWeaponsToolkit'\n\n";

		manifest << "files{\n";
		manifest << "	'**/weaponcomponents.meta',\n";
		manifest << "	'**/weaponarchetypes.meta',\n";
		manifest << "	'**/weaponanimations.meta',\n";
		manifest << "	'**/pedpersonality.meta',\n";
		manifest << "	'**/weapons.meta',\n";
		manifest << "}\n";
		manifest << "\n";
		manifest << "data_file 'WEAPONCOMPONENTSINFO_FILE' '**/weaponcomponents.meta'\n";
		manifest << "data_file 'WEAPON_METADATA_FILE' '**/weaponarchetypes.meta'\n";
		manifest << "data_file 'WEAPON_ANIMATIONS_FILE' '**/weaponanimations.meta'\n";
		manifest << "data_file 'PED_PERSONALITY_FILE' '**/pedpersonality.meta'\n";
		manifest << "data_file 'WEAPONINFO_FILE' '**/weapons.meta'\n";
		manifest.close();
	}

	//Copy model assets to stream folder
	for (cWeaponAsset* a : generatedWeapon->weaponAssets) {
		std::ifstream  src(a->assetAbsolutePath, std::ios::binary);
		std::ofstream  dst(exportDirectory + "/" + generatedWeapon->getWeaponName() + "/stream/" + a->assetName, std::ios::binary);

		dst << src.rdbuf();
	}

	exportWeaponsMeta(c_exportMetasDir);
	exportWeaponsAnimationsMeta(c_exportMetasDir);
	exportPedPersonalityMeta(c_exportMetasDir);
	exportWeaponArchetypesMeta(c_exportMetasDir);
	exportWeaponComponentsMeta(c_exportMetasDir);

	wxMessageBox(std::string("Successfully exported weapon to: ") + exportDirectory.c_str() + "\\" + generatedWeapon->getWeaponName(), wxT("vWeaponToolkit"), wxICON_INFORMATION);
}

void cWeaponsToolkit::exportWeaponsMeta(char* c_exportMetasDir)
{
	//Generate weapons.meta
	rapidxml::xml_document<> doc;
	rapidxml::xml_node<>* root_node;
	std::ifstream theFile(std::string("templates/weapons/" + generatedWeapon->getWeaponTemplate() + "/weapons.meta"));
	std::vector<char> buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');
	doc.parse<0>(&buffer[0]);

	root_node = doc.first_node("CWeaponInfoBlob");

	std::string slotName = std::string("SLOT_") + generatedWeapon->getWeaponId();
	char* weaponId = doc.allocate_string(generatedWeapon->getWeaponId().c_str());
	char* weaponModel = doc.allocate_string(generatedWeapon->getWeaponModel().c_str());
	char* weaponAudioItem = doc.allocate_string(generatedWeapon->getWeaponAudioItem().c_str());
	char* damageType = doc.allocate_string(generatedWeapon->getWeaponDamageType().c_str());
	char* damage = doc.allocate_string(std::to_string(generatedWeapon->getWeaponDamage()).c_str());
	char* headshotDamageModifier = doc.allocate_string(std::to_string(generatedWeapon->getWeaponHeadShotDamageModifierPlayer()).c_str());
	char* ammoType = doc.allocate_string(generatedWeapon->getAmmoType().c_str());
	char* HumanNameHash = doc.allocate_string(generatedWeapon->getWeaponId().c_str());
	char* SlotName = doc.allocate_string(slotName.c_str());
	char* reloadSpeedMulti = doc.allocate_string(std::to_string(generatedWeapon->getWeaponReloadSpeedMultiplier()).c_str());
	char* weaponRange = doc.allocate_string(std::to_string(generatedWeapon->getWeaponRange()).c_str());

	rapidxml::xml_node<>* slotItem_node = root_node->first_node("SlotNavigateOrder")->first_node("Item")->first_node("WeaponSlots")->first_node("Item");
	char* slotId = doc.allocate_string(std::to_string(getNextAvailableSlotId()).c_str());
	slotItem_node->first_node("OrderNumber")->first_attribute()->value(slotId);
	slotItem_node->first_node("Entry")->first_node()->value(SlotName);

	rapidxml::xml_node<>* weaponItem_node = root_node->first_node("Infos")->first_node("Item")->first_node("Infos")->first_node("Item");
	weaponItem_node->first_node("Name")->first_node()->value(weaponId);
	weaponItem_node->first_node("Slot")->first_node()->value(SlotName);
	weaponItem_node->first_node("Model")->first_node()->value(weaponModel);
	weaponItem_node->first_node("Audio")->first_node()->value(weaponAudioItem);
	weaponItem_node->first_node("DamageType")->first_node()->value(damageType);
	weaponItem_node->first_node("HumanNameHash")->first_node()->value(HumanNameHash);
	weaponItem_node->first_node("Damage")->first_attribute()->value(damage);
	weaponItem_node->first_node("HeadShotDamageModifierPlayer")->first_attribute()->value(headshotDamageModifier);
	weaponItem_node->first_node("AmmoInfo")->first_attribute()->value(ammoType);
	weaponItem_node->first_node("AnimReloadRate")->first_attribute()->value(reloadSpeedMulti);
	weaponItem_node->first_node("WeaponRange")->first_attribute()->value(weaponRange);

	rapidxml::xml_node<>* component_node = weaponItem_node->first_node("AttachPoints");

	for (auto c : generatedWeapon->components) {
		rapidxml::xml_node<>* item_node = doc.allocate_node(rapidxml::node_element, "Item", "");
		component_node->prepend_node(item_node);

		rapidxml::xml_node<>* components_node = doc.allocate_node(rapidxml::node_element, "Components", 0);
		component_node->first_node("Item")->prepend_node(components_node);

		rapidxml::xml_node<>* components_item_node = doc.allocate_node(rapidxml::node_element, "Item", 0);
		component_node->first_node("Item")->first_node("Components")->prepend_node(components_item_node);

		char* componentName = doc.allocate_string(c->getComponentName().c_str());
		rapidxml::xml_node<>* components_name_node = doc.allocate_node(rapidxml::node_element, "Name", componentName);
		component_node->first_node("Item")->first_node("Components")->first_node("Item")->prepend_node(components_name_node);

		rapidxml::xml_node<>* components_enabled_node = doc.allocate_node(rapidxml::node_element, "Default", 0);
		component_node->first_node("Item")->first_node("Components")->first_node("Item")->prepend_node(components_enabled_node);

		rapidxml::xml_attribute<>* components_enabled_attr = doc.allocate_attribute("value", c->isComponentEnabled() ? "true" : "false");
		component_node->first_node("Item")->first_node("Components")->first_node("Item")->first_node("Default")->prepend_attribute(components_enabled_attr);


		rapidxml::xml_document<> comp_doc;
		rapidxml::xml_node<>* comp_root_node;
		std::ifstream componentFile(std::string("templates/components/" + c->getComponentTemplate() + "/weaponcomponents.meta"));
		std::vector<char> comp_buffer((std::istreambuf_iterator<char>(componentFile)), std::istreambuf_iterator<char>());
		comp_buffer.push_back('\0');
		comp_doc.parse<0>(&comp_buffer[0]);

		comp_root_node = comp_doc.first_node("CWeaponComponentInfoBlob");
		char* attachBone = doc.allocate_string(comp_root_node->first_node("Infos")->first_node("Item")->first_node("AttachBone")->value());

		rapidxml::xml_node<>* attachbone_node = doc.allocate_node(rapidxml::node_element, "AttachBone", attachBone);
		component_node->first_node("Item")->prepend_node(attachbone_node);

		comp_doc.clear();
	}

	std::string xml_as_string;
	rapidxml::print(std::back_inserter(xml_as_string), doc);

	char c_weaponsMetaDir[500] = "";
	strcat(c_weaponsMetaDir, c_exportMetasDir);
	strcat(c_weaponsMetaDir, "\\weapons.meta");
	std::ofstream fileStored(c_weaponsMetaDir);
	fileStored << xml_as_string;
	fileStored.close();
	doc.clear();
}

void cWeaponsToolkit::exportWeaponsAnimationsMeta(char* c_exportMetasDir)
{
	rapidxml::xml_document<> doc;
	rapidxml::xml_node<>* root_node;
	std::ifstream theFile(std::string("templates/weapons/" + generatedWeapon->getWeaponTemplate() + "/weaponanimations.meta"));
	std::vector<char> buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');
	doc.parse<0>(&buffer[0]);

	root_node = doc.first_node("CWeaponAnimationsSets");

	char* weaponId = doc.allocate_string(generatedWeapon->getWeaponId().c_str());
	char* weaponFireRateModifier = doc.allocate_string(std::to_string(generatedWeapon->getWeaponFireRateMultiplier()).c_str());

	for (rapidxml::xml_node<>* node = root_node->first_node("WeaponAnimationsSets")->first_node("Item")	; node; node = node->next_sibling())
	{
		node->first_node("WeaponAnimations")->first_node("Item")->first_attribute()->value(weaponId);
		node->first_node("WeaponAnimations")->first_node("Item")->first_node("AnimFireRateModifier")->first_attribute()->value(weaponFireRateModifier);
	}

	std::string xml_as_string;
	rapidxml::print(std::back_inserter(xml_as_string), doc);

	char c_weaponsMetaDir[500] = "";
	strcat(c_weaponsMetaDir, c_exportMetasDir);
	strcat(c_weaponsMetaDir, "\\weaponanimations.meta");
	std::ofstream fileStored(c_weaponsMetaDir);
	fileStored << xml_as_string;
	fileStored.close();
	doc.clear();
}

void cWeaponsToolkit::exportPedPersonalityMeta(char* c_exportMetasDir)
{
	rapidxml::xml_document<> doc;
	rapidxml::xml_node<>* root_node;
	std::ifstream theFile(std::string("templates/weapons/" + generatedWeapon->getWeaponTemplate() + "/pedpersonality.meta"));
	std::vector<char> buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');
	doc.parse<0>(&buffer[0]);

	root_node = doc.first_node("CPedModelInfo__PersonalityDataList");

	char* weaponId = doc.allocate_string(generatedWeapon->getWeaponId().c_str());	

	for (rapidxml::xml_node<>* node = root_node->first_node("MovementModeUnholsterData")->first_node("Item"); node; node = node->next_sibling())
	{
		node->first_node("UnholsterClips")->first_node("Item")->first_node("Weapons")->first_node("Item")->first_node()->value(weaponId);
	}

	rapidxml::xml_node<>* movementmode_node = root_node->first_node("MovementModes")->first_node("Item");
	for (rapidxml::xml_node<>* node = movementmode_node; node; node = node->next_sibling())
	{
		for (rapidxml::xml_node<>* node_2 = node->first_node("MovementModes")->first_node("Item"); node_2; node_2 = node_2->next_sibling())
		{
			node_2->first_node("Item")->first_node("Weapons")->first_node("Item")->first_node()->value(weaponId);
		}
	}

	std::string xml_as_string;
	rapidxml::print(std::back_inserter(xml_as_string), doc);

	char c_weaponsMetaDir[500] = "";
	strcat(c_weaponsMetaDir, c_exportMetasDir);
	strcat(c_weaponsMetaDir, "\\pedpersonality.meta");
	std::ofstream fileStored(c_weaponsMetaDir);
	fileStored << xml_as_string;
	fileStored.close();
	doc.clear();
}

void cWeaponsToolkit::exportWeaponArchetypesMeta(char* c_exportMetasDir)
{
	rapidxml::xml_document<> doc;
	rapidxml::xml_node<>* root_node;
	std::ifstream theFile(std::string("templates/weapons/" + generatedWeapon->getWeaponTemplate() + "/weaponarchetypes.meta"));
	std::vector<char> buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');
	doc.parse<0>(&buffer[0]);

	root_node = doc.first_node("CWeaponModelInfo__InitDataList");
	char* weaponId = doc.allocate_string(generatedWeapon->getWeaponId().c_str());

	for (cWeaponAsset* a : generatedWeapon->weaponAssets) {
		size_t pos_ydr = a->assetName.find(".ydr");
		if (pos_ydr != std::string::npos)
		{
			//Weapon Models
			rapidxml::xml_node<>* item_node = doc.allocate_node(rapidxml::node_element, "Item", "");
			root_node->prepend_node(item_node);

			char* assetName = doc.allocate_string(removeWeaponFileExtension(a->assetName).c_str());
			rapidxml::xml_node<>* modelname_node = doc.allocate_node(rapidxml::node_element, "modelName", assetName);
			root_node->first_node("Item")->append_node(modelname_node);

			rapidxml::xml_node<>* texture_node = doc.allocate_node(rapidxml::node_element, "txdName", assetName);
			root_node->first_node("Item")->append_node(texture_node);

			rapidxml::xml_node<>* pfxasset_node = doc.allocate_node(rapidxml::node_element, "ptfxAssetName", "NULL");
			root_node->first_node("Item")->append_node(pfxasset_node);

			rapidxml::xml_node<>* lod_node = doc.allocate_node(rapidxml::node_element, "lodDist", 0);
			root_node->first_node("Item")->append_node(lod_node);

			char* assetLOD = doc.allocate_string(std::to_string(getAssetLODFromName(a->assetName)).c_str());
			rapidxml::xml_attribute<>* lod_attr = doc.allocate_attribute("value", assetLOD);
			root_node->first_node("Item")->first_node("lodDist")->append_attribute(lod_attr);
		}
	}

	std::string xml_as_string;
	rapidxml::print(std::back_inserter(xml_as_string), doc);

	char c_weaponsMetaDir[500] = "";
	strcat(c_weaponsMetaDir, c_exportMetasDir);
	strcat(c_weaponsMetaDir, "\\weaponarchetypes.meta");
	std::ofstream fileStored(c_weaponsMetaDir);
	fileStored << xml_as_string;
	fileStored.close();
	doc.clear();
}

void cWeaponsToolkit::exportWeaponComponentsMeta(char* c_exportMetasDir)
{
	int metas_result = _mkdir((std::string(c_exportMetasDir) + "\\components").c_str());	
	for (cWeaponComponent* c : generatedWeapon->components) {
		int metas_result = _mkdir((std::string(c_exportMetasDir) + "\\components\\" + c->getComponentName()).c_str());

		rapidxml::xml_document<> doc;
		rapidxml::xml_node<>* root_node;
		std::ifstream theFile(std::string("templates/components/" + c->getComponentTemplate() + "/weaponcomponents.meta"));
		std::vector<char> buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
		buffer.push_back('\0');
		doc.parse<0>(&buffer[0]);

		root_node = doc.first_node("CWeaponComponentInfoBlob");

		char* componentName = doc.allocate_string(c->getComponentName().c_str());
		char* componentModel = doc.allocate_string(c->getModelName().c_str());

		root_node->first_node("Infos")->first_node("Item")->first_node("Name")->first_node()->value(componentName);
		root_node->first_node("Infos")->first_node("Item")->first_node("Model")->first_node()->value(componentModel);

		if (c->getAmmoInfo() != "")
		{
			char* ammoInfo = doc.allocate_string(c->getAmmoInfo().c_str());
			char* clipSize = doc.allocate_string(std::to_string(c->getClipSize()).c_str());

			root_node->first_node("Infos")->first_node("Item")->first_node("AmmoInfo")->value(ammoInfo);
			root_node->first_node("Infos")->first_node("Item")->first_node("ClipSize")->first_attribute()->value(clipSize);
		}

		std::string xml_as_string;
		rapidxml::print(std::back_inserter(xml_as_string), doc);

		char c_weaponsMetaDir[500] = "";
		strcat(c_weaponsMetaDir, c_exportMetasDir);
		strcat(c_weaponsMetaDir, "\\components");
		strcat(c_weaponsMetaDir, ("\\" + c->getComponentName()).c_str());
		strcat(c_weaponsMetaDir, "\\weaponcomponents.meta");
		std::ofstream fileStored(c_weaponsMetaDir);
		fileStored << xml_as_string;
		fileStored.close();
		doc.clear();
	}
}

int cWeaponsToolkit::getAssetLODFromName(std::string assetName)
{
	for (cWeaponAsset* a : generatedWeapon->weaponAssets) {
		size_t pos_ydr = a->assetName.find(".ydr");
		if (pos_ydr != std::string::npos)
		{
			if (generatedWeapon->getWeaponModel() == removeWeaponFileExtension(assetName)) {
				return generatedWeapon->getWeaponLOD();
			}

			for (cWeaponComponent* c : generatedWeapon->components) {
				if (c->getModelName() == removeWeaponFileExtension(assetName)) {
					return c->getModelLOD();
				}
			}
		}
	}
	return 500;
}

std::string cWeaponsToolkit::getAssetIdFromAsset(std::string assetName)
{
	for (cWeaponAsset* a : generatedWeapon->weaponAssets) {
		if (generatedWeapon->getWeaponModel() == removeWeaponFileExtension(assetName)) {
			return generatedWeapon->getWeaponId();
		}

		for (cWeaponComponent* c : generatedWeapon->components) {
			if (c->getModelName() == removeWeaponFileExtension(assetName)) {
				return c->getComponentName();
			}
		}
	}
	return "N/A";
}

void cWeaponsToolkit::onAudioItemChanged(wxCommandEvent& evt)
{
	generatedWeapon->setAudioItem(std::string(audioItemComboBox->GetStringSelection()));
}

void cWeaponsToolkit::onAmmoTypeChanged(wxCommandEvent& evt)
{
	generatedWeapon->setAmmoType(std::string(ammoTypesComboBox->GetStringSelection()));
}

void cWeaponsToolkit::onDamageTypeChanged(wxCommandEvent& evt)
{
	
	generatedWeapon->setWeaponDamageType(std::string(damageTypesComboxBox->GetStringSelection()));
}

void cWeaponsToolkit::onWeaponDamageChanged(wxCommandEvent& evt)
{
	generatedWeapon->setWeaponDamage(std::stof(std::string(evt.GetString())));
}

void cWeaponsToolkit::onWeaponRangeChanged(wxCommandEvent& evt)
{
	generatedWeapon->setWeaponRange(std::stof(std::string(evt.GetString())));
}

void cWeaponsToolkit::onWeaponLODChanged(wxCommandEvent& evt)
{
	generatedWeapon->setWeaponLOD(std::stoi(std::string(evt.GetString())));
}

void cWeaponsToolkit::onWeaponReloadModifierChanged(wxCommandEvent& evt)
{
	generatedWeapon->setWeaponReloadSpeedMultiplier(std::stof(std::string(evt.GetString())));
}

void cWeaponsToolkit::onWeaponFireRateModifierChanged(wxCommandEvent& evt)
{
	generatedWeapon->setWeaponFireRateMultiplier(std::stof(std::string(evt.GetString())));
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
		generatedWeapon->weaponAssets.clear();		
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

				cWeaponAsset* weaponAsset = new cWeaponAsset();
				weaponAsset->assetName = std::string(wxString(file.cFileName));
				weaponAsset->assetAbsolutePath = std::string(wxString(fullDir));
				generatedWeapon->addWeaponAsset(weaponAsset);
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
	fileMenu->Append(wxID_ANY, wxT("&Created by Robbster"));

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

	menuTabs->Bind(wxEVT_AUINOTEBOOK_PAGE_CHANGED, &cWeaponsToolkit::onExportTabPressed, this);


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
	weaponTemplate->Append(wxArrayString(cWeaponsToolkit::getWeaponCount(), generatedWeapon->nativeWeapons));

	wxStaticText* weaponNameStaticText = new wxStaticText(createWeaponPanel, wxID_ANY, "Weapon Name:", wxPoint(250, 100));
	weaponNameTextCtrl = new wxTextCtrl(createWeaponPanel, wxID_ANY, "AK-47", wxPoint(250,120), wxSize(175, 25));

	wxStaticText* weaponIdStaticText = new wxStaticText(createWeaponPanel, wxID_ANY, "Weapon ID:", wxPoint(250, 160));
	weaponIdTextCtrl = new wxTextCtrl(createWeaponPanel, wxID_ANY, "WEAPON_AK47", wxPoint(250,180), wxSize(175, 25));

	wxStaticText* weaponModelStaticText = new wxStaticText(createWeaponPanel, wxID_ANY, "Weapon Model:", wxPoint(250, 220));
	weaponModelTextCtrl = new wxTextCtrl(createWeaponPanel, wxID_ANY, "w_ar_assaultrifle", wxPoint(250,240), wxSize(175, 25));

	//Event Handlers
	importerDirectoryPicker->Bind(wxEVT_COMMAND_DIRPICKER_CHANGED, &cWeaponsToolkit::onImportDirectoryChanged, this);
	weaponTemplate->Bind(wxEVT_COMBOBOX, &cWeaponsToolkit::onWeaponTemplateChanged, this);
	nextButton->Bind(wxEVT_BUTTON, &cWeaponsToolkit::onCreateWeaponNextButtonChanged, this);
	weaponNameTextCtrl->Bind(wxEVT_TEXT, &cWeaponsToolkit::onWeaponNameChanged, this);
	weaponIdTextCtrl->Bind(wxEVT_TEXT, &cWeaponsToolkit::onWeaponIdChanged, this);
	weaponModelTextCtrl->Bind(wxEVT_TEXT, &cWeaponsToolkit::onWeaponModelChanged, this);

	//TAB 2 - Configuration
	wxStaticText* audioItemStaticText = new wxStaticText(configTab, wxID_ANY, "Select Audio Item", wxPoint(20, 30));
	audioItemComboBox = new wxComboBox(configTab, wxID_ANY, "AUDIO_ITEM_PISTOL", wxPoint(20, 50), wxSize(175, 25));
	audioItemComboBox->Append(wxArrayString(cWeaponsToolkit::getAudioItemsCount(), generatedWeapon->audioItems));

	wxStaticText* weaponDamageStaticText = new wxStaticText(configTab, wxID_ANY, "Weapon Damage:", wxPoint(20, 90));
	weaponDamageTextCtrl = new wxTextCtrl(configTab, wxID_ANY, "0.0", wxPoint(20, 110), wxSize(175, 25));

	wxStaticText* weaponRangeStaticText = new wxStaticText(configTab, wxID_ANY, "Weapon Range:", wxPoint(20, 150));
	weaponRangeTextCtrl = new wxTextCtrl(configTab, wxID_ANY, "120.0", wxPoint(20, 170), wxSize(175, 25));

	wxStaticText* ammoTypesStaticText = new wxStaticText(configTab, wxID_ANY, "Ammo Type", wxPoint(20, 210));
	ammoTypesComboBox = new wxComboBox(configTab, wxID_ANY, "AMMO_PISTOL", wxPoint(20, 230), wxSize(175, 25));
	ammoTypesComboBox->Append(wxArrayString(cWeaponsToolkit::getAmmoTypesCount(), generatedWeapon->ammoTypes));

	wxStaticText* weaponLODStaticText = new wxStaticText(configTab, wxID_ANY, "LOD:", wxPoint(20, 270));
	weaponLODTextCtrl = new wxTextCtrl(configTab, wxID_ANY, "500.0", wxPoint(20, 290), wxSize(175, 25));

	wxStaticText* weaponReloadModifierStaticText = new wxStaticText(configTab, wxID_ANY, "Reload Speed Modifier:", wxPoint(20, 330));
	weaponReloadModifierTextCtrl = new wxTextCtrl(configTab, wxID_ANY, "1.0", wxPoint(20, 350), wxSize(175, 25));

	wxStaticText* weaponFireRateModifierStaticText = new wxStaticText(configTab, wxID_ANY, "Fire Rate Modifier:", wxPoint(220, 30));
	weaponFireRateModifierTextCtrl = new wxTextCtrl(configTab, wxID_ANY, "1.0", wxPoint(220, 50), wxSize(175, 25));

	wxStaticText* damageTypesStaticText = new wxStaticText(configTab, wxID_ANY, "Damage Type", wxPoint(220, 90));
	damageTypesComboxBox = new wxComboBox(configTab, wxID_ANY, "BULLET", wxPoint(220, 110), wxSize(175, 25));
	damageTypesComboxBox->Append(wxArrayString(cWeaponsToolkit::getDamageTypesCount(), generatedWeapon->damageTypes));

	wxStaticText* weaponHeadshotDamageModifierStaticText = new wxStaticText(configTab, wxID_ANY, "Headshot Damage Modifier:", wxPoint(220, 150));
	weaponHeadshotDamageModifierTextCtrl = new wxTextCtrl(configTab, wxID_ANY, "1.0", wxPoint(220, 170), wxSize(175, 25));

	//Event Handlers
	audioItemComboBox->Bind(wxEVT_COMBOBOX, &cWeaponsToolkit::onAudioItemChanged, this);
	ammoTypesComboBox->Bind(wxEVT_COMBOBOX, &cWeaponsToolkit::onAmmoTypeChanged, this);
	damageTypesComboxBox->Bind(wxEVT_COMBOBOX, &cWeaponsToolkit::onDamageTypeChanged, this);
	weaponDamageTextCtrl->Bind(wxEVT_TEXT, &cWeaponsToolkit::onWeaponDamageChanged, this);
	weaponRangeTextCtrl->Bind(wxEVT_TEXT, &cWeaponsToolkit::onWeaponRangeChanged, this);
	weaponLODTextCtrl->Bind(wxEVT_TEXT, &cWeaponsToolkit::onWeaponLODChanged, this);
	weaponReloadModifierTextCtrl->Bind(wxEVT_TEXT, &cWeaponsToolkit::onWeaponReloadModifierChanged, this);
	weaponFireRateModifierTextCtrl->Bind(wxEVT_TEXT, &cWeaponsToolkit::onWeaponFireRateModifierChanged, this);
	weaponHeadshotDamageModifierTextCtrl->Bind(wxEVT_TEXT, &cWeaponsToolkit::onWeaponHeadshotDamageModifierChanged, this);

	//TAB 3 - Components
	weaponComponentsListCtrl = new wxListCtrl(componentsTab, wxID_ANY, wxPoint(20, 20), wxSize(260, 340), wxLC_REPORT, wxDefaultValidator);
	wxListItem colComps;
	colComps.SetId(0);
	colComps.SetText(_("Components"));
	colComps.SetWidth(260);
	weaponComponentsListCtrl->InsertColumn(0, colComps);

	wxButton* addComponentButton = new wxButton(componentsTab, wxID_ANY, "Add Component", wxPoint(20, 370), wxSize(125,25));
	wxButton* removeComponentButton = new wxButton(componentsTab, wxID_ANY, "Remove Component", wxPoint(155, 370),wxSize(125, 25));

	wxStaticText* weaponComponentsStaticText = new wxStaticText(componentsTab, wxID_ANY, "Select Component Template", wxPoint(300, 20));
	weaponComponentsComboBox = new wxComboBox(componentsTab, wxID_ANY, "COMPONENT_AT_RAILCOVER_01", wxPoint(300, 40), wxSize(225, 25));
	weaponComponentsComboBox->Append(wxArrayString(cWeaponsToolkit::getWeaponComponentCount(), generatedWeapon->nativeComponents));

	wxStaticText* componentNameStaticText = new wxStaticText(componentsTab, wxID_ANY, "Component Name:", wxPoint(300, 80));
	componentNameTextCtrl = new wxTextCtrl(componentsTab, wxID_ANY, "COMPONENT_AT_RAILCOVER_01", wxPoint(300, 100), wxSize(225, 25));

	wxStaticText* componentModelNameStaticText = new wxStaticText(componentsTab, wxID_ANY, "Model Name:", wxPoint(300, 140));
	componentModelNameTextCtrl = new wxTextCtrl(componentsTab, wxID_ANY, "w_at_railcover_01", wxPoint(300, 160), wxSize(225, 25));

	wxStaticText* componentLODStaticText = new wxStaticText(componentsTab, wxID_ANY, "Model LOD:", wxPoint(300, 200));
	componentLODTextCtrl = new wxTextCtrl(componentsTab, wxID_ANY, "500.0", wxPoint(300, 220), wxSize(225, 25));

	wxStaticText* componentClipSizeStaticText = new wxStaticText(componentsTab, wxID_ANY, "Clip Size:", wxPoint(300, 260));
	componentClipSizeTextCtrl = new wxTextCtrl(componentsTab, wxID_ANY, "", wxPoint(300, 280), wxSize(225, 25));

	wxStaticText* weaponAmmoInfoStaticText = new wxStaticText(componentsTab, wxID_ANY, "Ammo Info", wxPoint(300, 320));
	weaponAmmoInfoComboBox = new wxComboBox(componentsTab, wxID_ANY, "Default Ammo", wxPoint(300, 340), wxSize(225, 25));
	weaponAmmoInfoComboBox->Append(wxArrayString(cWeaponsToolkit::getAmmoInfoCount(), generatedWeapon->nativeAmmoInfos));

	checkboxDevMode = new wxCheckBox(componentsTab, wxID_ANY, "Component Enabled", wxPoint(575, 103));

	//Event Handlers
	addComponentButton->Bind(wxEVT_BUTTON, &cWeaponsToolkit::onAddComponent, this);
	removeComponentButton->Bind(wxEVT_BUTTON, &cWeaponsToolkit::onRemoveComponent, this);
	weaponComponentsListCtrl->Bind(wxEVT_LIST_ITEM_SELECTED, &cWeaponsToolkit::onSelectComponent, this);
	weaponComponentsComboBox->Bind(wxEVT_COMBOBOX, &cWeaponsToolkit::onComponentTemplateChanged, this);
	weaponAmmoInfoComboBox->Bind(wxEVT_COMBOBOX, &cWeaponsToolkit::onComponentAmmoInfoChanged, this);
	componentNameTextCtrl->Bind(wxEVT_TEXT, &cWeaponsToolkit::onComponentNameChanged, this);
	componentModelNameTextCtrl->Bind(wxEVT_TEXT, &cWeaponsToolkit::onComponentModelNameChanged, this);
	componentLODTextCtrl->Bind(wxEVT_TEXT, &cWeaponsToolkit::onComponentLODChanged, this);
	componentClipSizeTextCtrl->Bind(wxEVT_TEXT, &cWeaponsToolkit::onComponentClipSizeChanged, this);
	checkboxDevMode->Bind(wxEVT_CHECKBOX, &cWeaponsToolkit::onComponentEnabledCheckboxChanged, this);

	//TAB 4 - Export
	exporterDirectoryPicker = new wxDirPickerCtrl(exportTab, wxID_ANY, "Export Folder", "", wxPoint(20, 370), wxSize(625, 25));
	wxButton* exportButton = new wxButton(exportTab, wxID_ANY, "Export", wxPoint(675, 370));

	exportListCtrl = new wxListCtrl(exportTab, wxID_ANY, wxPoint(20, 20), wxSize(730, 320), wxLC_REPORT, wxDefaultValidator);
	wxListItem assetColumn;
	assetColumn.SetId(0);
	assetColumn.SetText(_("Asset"));
	assetColumn.SetWidth(365);
	exportListCtrl->InsertColumn(0, assetColumn);

	wxListItem usedForColumn;
	usedForColumn.SetId(1);
	usedForColumn.SetText(_("Used for"));
	usedForColumn.SetWidth(365);
	exportListCtrl->InsertColumn(1, usedForColumn);

	//Event Handlers
	exporterDirectoryPicker->Bind(wxEVT_COMMAND_DIRPICKER_CHANGED, &cWeaponsToolkit::onExportDirectoryChanged, this);
	exportButton->Bind(wxEVT_BUTTON, &cWeaponsToolkit::onExportButtonPressed, this);

	wxCommandEvent* defaultTemplate = new wxCommandEvent();
	defaultTemplate->SetString("WEAPON_ASSAULTRIFLE");
	cWeaponsToolkit::onWeaponTemplateChanged(*defaultTemplate);
}