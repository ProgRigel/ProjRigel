#pragma once

namespace rg {

	class RgGUI;

	class RgGUIContext {

	public:
		void Release();

	private:
		RgGUIContext();
		~RgGUIContext();

		RgGUIContext(const RgGUIContext&) = delete;
		RgGUIContext& operator=(const RgGUIContext&) = delete;

	public:
		friend class RgGUI;
	};
}