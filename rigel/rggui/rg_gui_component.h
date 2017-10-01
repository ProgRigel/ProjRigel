#pragma once
#include <rgcore\rg_math.h>
#include <functional>
#include <vector>
#include <string>
#include <ctime>

namespace rg {

	//menu related
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

	//window

	struct RgGUIWindowBufferDesc {

	};

	struct RgGUIWindow {
		std::string title;
		RgVec4 windowrect;

		bool enabled = true;
		bool resizeable = true;
		bool closeable = false;
		bool moveable = true;

		long winid;
		int order = 0;

		//1 not drawed
		//2 init draw
		//0 init draw done
		unsigned char _initdraw = 1;
		bool _isfocused = false;

		unsigned int _buffer_vertex_begin = 0;
		unsigned int _buffer_vertex_end = 0;
		unsigned int _buffer_text_begin = 0;
		unsigned int _buffer_text_end = 0;


		void focused();
		void lost_focuse();

		RgGUIWindow();
		RgGUIWindow(const RgGUIWindow&) = delete;
		RgGUIWindow& operator=(const RgGUIWindow&) = delete;
	};
}