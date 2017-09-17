#pragma once
#include <rgcore\rg_math.h>

namespace rg {
	class RgRenderTarget {

	public:
		RgRenderTarget();
		~RgRenderTarget();


		void * GetColorBufferPtr();
		void * GetDepthBufferPtr();
		void SetColorBufferPtr(void * ptr);
		void SetDepthBufferPtr(void* ptr);

		void Release();

		unsigned int BufferWidth;
		unsigned int BufferHeight;

	private:
		RgRenderTarget(const RgRenderTarget&) = delete;
		RgRenderTarget& operator=(const RgRenderTarget&) = delete;

		void * m_pColorBufferPtr = nullptr;
		void * m_pDepthBufferPtr = nullptr;

	};
}