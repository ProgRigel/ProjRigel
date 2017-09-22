#pragma once
#include <rgcore\rg_window.h>
#include "rg_gui_style.h"
#include <stack>
namespace rg {

#define RG_PARAM_RECT const RgVec2<RgFloat>&lp,const RgVec2<RgFloat>& size

	class RgGUI;
	class RgGUIDrawBuffer;

	struct RgGUIState {
		RgVec4<RgFloat> ColorBg;
		RgVec4<RgFloat> ColorFont;
		RgVec4<RgFloat> Color;
		
		std::stack<RgVec4<RgFloat>> GroupRectStack;

		void Reset();
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

		void BeginGroup(RG_PARAM_RECT);
		void EndGroup();

		bool CheckMousePos(const RgVec2<RgFloat>& lp, const RgVec2<RgFloat>& size) const;

		bool Clip(const RgVec4<RgFloat>& rect, RgVec2<RgFloat>& pos, RgVec2<RgFloat>& sz) const;
		bool _GroupClip(RgVec2<RgFloat>& pos, RgVec2<RgFloat>& sz) const;

		//draw
		void DrawLine();
		void DrawRect(const RgVec2<RgFloat>& lp,const RgVec2<RgFloat>& size) const;

		//controller
		bool GUIButton(const RgVec2<RgFloat>& lp, const RgVec2<RgFloat>& size) const;

		//state
		void SetColor(RgVec4<RgFloat> color);

		

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