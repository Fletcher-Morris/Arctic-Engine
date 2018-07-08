#pragma once

#ifndef ENGINEPREFS_H_INCLUDED
#define ENGINEPREFS_H_INCLUDED


class EnginePrefs
{

public:
	static EnginePrefs* Instance();
	virtual ~EnginePrefs();

	void LoadPrefs();

protected:
	EnginePrefs();
	EnginePrefs(const EnginePrefs& prefs);
	EnginePrefs& operator=(const EnginePrefs& prefs);
	static EnginePrefs* m_instance;
};

#endif // !ENGINEPREFS_H_INCLUDED