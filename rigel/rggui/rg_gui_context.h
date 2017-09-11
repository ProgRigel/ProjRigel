#pragma once
#include <rgcore\rgcore.h>

namespace rg {

	class RgGUI;
	class RgGUIDrawBuffer;

	class RgGUIContext {

	public:
		void Release();
		void Reset();
	public:
		void DrawLine();
		void DrawRect(const RgVec2& lp,const RgVec2& size) const;

	private:
		RgGUIContext();
		~RgGUIContext();

		RgGUIContext(const RgGUIContext&) = delete;
		RgGUIContext& operator=(const RgGUIContext&) = delete;

		RgGUIDrawBuffer * m_pDrawBuffer = nullptr;

	public:
		friend class RgGUI;
	};
}