#pragma once
#include <rgcore\rg_math.h>
#include <functional>
#include <vector>
#include <string>

namespace rg {


	struct RgGUIMenuItem{
		std::string label;
		std::function<void()> callback = nullptr;

		RgGUIMenuItem(const std::string& _label, std::function<void()> _callback) :label(_label), callback(_callback) {}
	};

	struct RgGUIMenuItemList :public RgGUIMenuItem
	{
		std::vector<RgGUIMenuItem> subitems;
		void AddMenuItem(const RgGUIMenuItem& item);

		RgGUIMenuItemList(const std::string& _label) :RgGUIMenuItem(_label, nullptr){}

	};

	struct RgGUIGenericMenu : public RgGUIMenuItemList{
		bool horizontal = true;
		RgGUIGenericMenu(std::string _label, bool _hori, std::function<void(RgGUIGenericMenu *)> _initfunc = nullptr) :RgGUIMenuItemList(_label) {
			horizontal = _hori;
			label = _label;
			if (_initfunc != nullptr) {
				_initfunc(this);
			}
		}
	};
}