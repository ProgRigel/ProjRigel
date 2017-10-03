#pragma once
#include <rgcore\rg_inc.h>
#include <rgcore\rg_window.h>
#include <rgcore\rg_math.h>
#include <stack>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <map>

#include "rg_gui_style.h"
#include "rg_gui_component.h"
namespace rg {

	class RgGUIContext;
	struct RgGUIState;
	struct RgGUIStateWindow;
	struct RgGUIStateContextMenu;



	struct RgGUIStateWindow {

		bool skipDraw = false;

		//current drawing window
		RgGUIWindow * stateWindow = nullptr;
		//focus
		RgGUIWindow * windowFocused = nullptr;
		std::map<long, RgGUIWindow *> windowMap;

		//draw relatex
		float stateWindowOrder = 0;

		RgGUIWindow * GetWindow(long winid);
		void DrawWindow(RgGUIWindow * window, RgGUIContext * ctx);
		void DrawWindowEnd(RgGUIWindow * window, RgGUIContext * ctx);

		void GUIBegin(const RgGUIState& state, RgGUIContext * ctx);
		bool GUIEnd(const RgGUIState& state, RgGUIContext * ctx);
		void register_win(RgGUIWindow* win);
		bool verify_valid(long winid);


		bool IsSkipUpdate(const RgGUIState& state) const;
	};

	struct RgGUIState {
		void PorcessEvent(const RgWindowInput* input);

		//colors
		RgVec4 colorBg;
		RgVec4 colorFont;
		RgVec4 color;
		RgVec4 colorRestored;

		//group
		std::stack<RgVec4> GroupRectStack;			//group stack
		RgVec4 WindowGroupRect = RgVec4::Zero;		//main window group rect

		//menu
		bool guiMenuBar = false;
		bool guiMenuBarHorizontal = false;
		RgFloat guiMenuBarOffset = 0;
		RgFloat guiMenuBarHeight = 0;

		//events
		RgWindowEventType eventType;
		RgVec2 eventMousePos;

		RgVec2 evemtDragStartPos;
		RgVec2 eventDragEndPos;
		RgVec2 eventDragOffsetPos;
		unsigned int eventDragState = 0;

		bool eventMouseLeftButton = false;
		bool eventMouseLeftDown = false;
		bool eventMouseLeftUp = false;

		bool eventUsed = false;

		//draw order
		float currentDrawOrder = 0;
		void DrawOrderIncreae();
		void ResetDrawOrder();

	};

	struct RgGUIStateContextMenu {
		std::vector<int> menuHashs;
		std::unordered_map<int, RgVec4> menuMap;
		bool newMenuContext = false;
	};
}