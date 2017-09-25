#pragma once
#include <vector>

namespace rg {

	class RgPluginBase;

	class RgPluginManager
	{
	public:
		static RgPluginManager& getInstance() {
			static RgPluginManager instance;
			return instance;
		}
		bool registerPlugin(RgPluginBase* plugin);
		void releasePlugins();
	private:
		void initPlugins();
		RgPluginManager();
		~RgPluginManager();
		RgPluginManager(const RgPluginManager&) = delete;
		RgPluginManager& operator=(const RgPluginManager&) = delete;
	private:
		static std::vector<RgPluginBase*> m_vplugins;
	};
}