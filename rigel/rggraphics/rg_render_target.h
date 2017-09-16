#pragma once


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

	private:
		RgRenderTarget(const RgRenderTarget&) = delete;
		RgRenderTarget& operator=(const RgRenderTarget&) = delete;

		void * m_pColorBufferPtr = nullptr;
		void * m_pDepthBufferPtr = nullptr;

	};
}