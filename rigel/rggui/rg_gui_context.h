#pragma once
#include <rgcore\rg_window.h>

namespace rg {

	class RgGUI;
	class RgGUIDrawBuffer;

	struct RgGUIState {
		RgVec4 Color;
	};

	class RgGUIContext {

	public:
		void Release();
		void Reset();

		void SetDirty(bool dirty);
		bool IsDirty();
	public:

		void BeginGUI(const RgWindowEvent&);
		void EndGUI();

		void DrawLine();
		void DrawRect(const RgVec2& lp,const RgVec2& size) const;
		bool GUIButton(const RgVec2& lp, const RgVec2& size) const;

		bool CheckMousePos(const RgVec2& lp, const RgVec2& size) const;

		RgGUIDrawBuffer * GetDrawBuffer();

	private:
		RgGUIContext();
		~RgGUIContext();

		RgGUIContext(const RgGUIContext&) = delete;
		RgGUIContext& operator=(const RgGUIContext&) = delete;

		bool m_bDirty = false;
		RgGUIDrawBuffer * m_pDrawBuffer = nullptr;

		const RgWindowInput * m_pWindowInput = nullptr;

	public:
		friend class RgGUI;
	};
}