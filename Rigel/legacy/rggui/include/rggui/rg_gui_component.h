#pragma once
#include <rgcore\rg_math.h>
#include <functional>
#include <vector>
#include <string>
#include <ctime>

namespace rg {

	enum class RgGUIControllerType {
		ContextMenu,
		TextInput,
	};

	class RgGUIContext;

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
		RgVec4 windowColor;

		bool enabled = true;
		bool resizeable = true;
		bool closeable = false;
		bool moveable = true;

		long winid;
		int order = 0;

		RgFloat windowMinWidth = 120;
		RgFloat windowMinHeight = 40;

		//1 not drawed
		//2 init draw
		//0 init draw done
		unsigned char _initdraw = 1;
		bool _isfocused = false;
		bool _isreused = false;
		bool _ondraw = false;

		//-----events-----

		//move
		bool _onWindowMove = false;
		RgVec4 _onWindowMoveRectStart;
		//resize
		bool _onWindowResize = false;
		unsigned char _onWindowResizeMode = 0; //3:width/height 1:height 2:width

		//-----events end-----

		RgVec4 _windowrectNext;

		//buffer
		unsigned int _buffer_vertex_begin = 0;
		unsigned int _buffer_vertex_end = 0;
		unsigned int _buffer_text_begin = 0;
		unsigned int _buffer_text_end = 0;

		void SetWindowRect(const RgVec4& r);

		void RestrictWindow() {
			windowrect.z = windowrect.z < windowMinWidth ? windowMinWidth : windowrect.z;
			windowrect.w = windowrect.w < windowMinHeight ? windowMinHeight : windowrect.w;
		}

		void focused();
		void lost_focuse();

		RgGUIWindow();
		RgGUIWindow(const RgGUIWindow&) = delete;
		RgGUIWindow& operator=(const RgGUIWindow&) = delete;

	};
}