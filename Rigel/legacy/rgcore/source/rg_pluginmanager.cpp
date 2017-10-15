#pragma once
#include "rgcore.h"
#include "rg_pluginmanager.h"
#include "rg_pluginbase.h"

namespace rg {
	bool RgPluginManager::registerPlugin(RgPluginBase* plugin)
	{
		plugin->m_hInstance = LoadLibrary(plugin->m_wsName.c_str());
		plugin->LoadPlugin();
		std::cout << "loading___" << std::endl;
		m_vplugins.push_back(plugin);
		return true;
	}
	void RgPluginManager::initPlugins()
	{
		for each (auto p in m_vplugins)
		{
			p->m_hInstance = LoadLibrary(p->m_wsName.c_str());
			p->LoadPlugin();
		}
	}
	void RgPluginManager::releasePlugins()
	{
		if (m_vplugins.capacity() == 0) return;
		for each (auto p in m_vplugins)
		{
			if (p != nullptr)
			{
				if (p->m_hInstance != NULL)
				{
					FreeLibrary(p->m_hInstance);
				}
				p->ReleasePlugin();
			}
				delete p;
		}
		std::vector<RgPluginBase*>().swap(m_vplugins);

	}

	RgPluginManager::RgPluginManager()
	{
	}
	RgPluginManager::~RgPluginManager()
	{
		releasePlugins();
	}
}
