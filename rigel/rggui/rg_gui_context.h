#pragma once
#include <rgcore\rg_window.h>
#include "rg_gui_style.h"
namespace rg {

	class RgGUI;
	class RgGUIDrawBuffer;

	struct RgGUIState {
		RgVec4 ColorBg;
		RgVec4 ColorFont;
		RgVec4 Color;
	};

	class RgGUIContext {

	public:
		void Release();
		void Reset();

		void SetDirty(bool dirty);
		bool IsDirty();
	public:

		//logic
		void BeginGUI(const RgWindowEvent&);
		void EndGUI();
		bool CheckMousePos(const RgVec2& lp, const RgVec2& size) const;

		//draw
		void DrawLine();
		void DrawRect(const RgVec2& lp,const RgVec2& size) const;

		//controller
		bool GUIButton(const RgVec2& lp, const RgVec2& size) const;

		//state
		void SetColor(RgVec4 color);

		

		RgGUIDrawBuffer * GetDrawBuffer();

	private:
		RgGUIContext();
		~RgGUIContext();

		RgGUIContext(const RgGUIContext&) = delete;
		RgGUIContext& operator=(const RgGUIContext&) = delete;

		bool m_bDirty = false;
		RgGUIState m_sState;
		RgGUIDrawBuffer * m_pDrawBuffer = nullptr;
		const RgWindowInput * m_pWindowInput = nullptr;

	public:
		friend class RgGUI;
	};
}