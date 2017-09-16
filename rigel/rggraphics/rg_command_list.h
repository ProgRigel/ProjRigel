#pragma once


namespace rg {
	class RgCommandList {
	protected:
		RgCommandList();
		virtual ~RgCommandList();

	public:
		virtual void Release();
	};
}