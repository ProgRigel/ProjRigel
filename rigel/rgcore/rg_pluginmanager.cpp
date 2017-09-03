#include "rg_pluginmanager.h"
#include <iostream>

namespace rg {
	bool RgPluginManager::registerPlugin(RgPluginBase* plugin)
	{
		plugin->LoadPlugin();
		m_vplugins.push_back(plugin);
		return true;
	}
	void RgPluginManager::initPlugins()
	{
		for each (auto p in m_vplugins)
		{
			p->LoadPlugin();
		}
	}
	void RgPluginManager::releasePlugins()
	{
		if (m_vplugins.capacity() == 0) return;
		for each (auto p in m_vplugins)
		{
			if(p != nullptr)
				p->ReleasePlugin();
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
