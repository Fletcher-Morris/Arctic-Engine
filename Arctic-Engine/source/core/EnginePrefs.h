#pragma once

#ifndef ENGINEPREFS_H_INCLUDED
#define ENGINEPREFS_H_INCLUDED

#include <fstream>
#include <iostream>
#include <string>

class EnginePrefs
{

public:
	static EnginePrefs* Instance();
	virtual ~EnginePrefs();
	void LoadPrefs();
	void SaveDefaults();

	bool editor = true;
	float guiScale = 1;
	bool guiDark = true;

private:
	std::string m_defaultsString;

protected:
	EnginePrefs();
	EnginePrefs(const EnginePrefs& prefs);
	EnginePrefs& operator=(const EnginePrefs& prefs);
	static EnginePrefs* m_instance;
};

#endif // !ENGINEPREFS_H_INCLUDED