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
}

EnginePrefs::EnginePrefs()
{
}

EnginePrefs::EnginePrefs(const EnginePrefs & prefs)
{
}
