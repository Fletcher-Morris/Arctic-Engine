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
	if(input)
	{
		std::string line;
		char key[256];
		char value[256];
		while (input)
		{
			input.getline(key, 256, ' ');
			input.getline(value, 256, '\n');
			bool doPrint = false;
			if (std::string(key) == "editor")
			{
				if (std::string(value) == "true") { editor = true; }
				else { editor = false; }
				doPrint = true;
			}
			else if (std::string(key) == "gui_scale")
			{
				guiScale = std::stof(std::string(value));
				doPrint = true;
			}
			else if (std::string(key) == "gui_dark")
			{
				if (std::string(value) == "true") { guiDark = true; }
				else { guiDark = false; }
				doPrint = true;
			}
			if (doPrint) { std::cout << key << " " << value << std::endl; }
		}
	}
	else
	{
		std::cout << "Failed Loading Engine Preferences" << std::endl;
		SaveDefaults();
	}
}

void EnginePrefs::SaveDefaults()
{
	std::cout << "Saving Default Engine Preferences" << std::endl;
	std::ofstream file("EnginePrefs.ini");
	file << m_defaultsString;
	file.close();

	editor = true;
	guiScale = 1;
	guiDark = true;
}

EnginePrefs::EnginePrefs()
{
	editor = true;
	guiScale = 1;
	guiDark = true;

	m_defaultsString = "editor true\ngui_scale 1\ngui_dark false";
}

EnginePrefs::EnginePrefs(const EnginePrefs & prefs)
{
}
