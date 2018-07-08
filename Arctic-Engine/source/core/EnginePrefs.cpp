#include "EnginePrefs.h"

EnginePrefs * EnginePrefs::m_instance(0);

EnginePrefs * EnginePrefs::Instance()
{
	if (!m_instance) m_instance = new EnginePrefs();
	return m_instance;
}

EnginePrefs::~EnginePrefs()
{
	m_instance = 0;
}

void EnginePrefs::LoadPrefs()
{
	std::cout << "Loading Engine Preferences" << std::endl;
	std::ifstream input("EnginePrefs.ini");
	std::string line;
	char name[256];
	char value[256];
	while (input)
	{
		input.getline(name, 256, ' ');
		input.getline(value, 256, '\n');
		bool doPrint = false;
		if (std::string(name) == "editor")
		{
			if (std::string(value) == "true") { editor = true; }
			else { editor = false; }
			doPrint = true;
		}
		else if (std::string(name) == "gui_scale")
		{
			guiScale = std::stof(std::string(value));
			doPrint = true;
		}
		else if (std::string(name) == "gui_dark")
		{
			if (std::string(value) == "true") { guiDark = true; }
			else { guiDark = false; }
			doPrint = true;
		}
		if(doPrint){ std::cout << name << " " << value << std::endl; }
	}
}

EnginePrefs::EnginePrefs()
{
	editor = true;
	guiScale = 1;
	guiDark = true;
}

EnginePrefs::EnginePrefs(const EnginePrefs & prefs)
{
}
