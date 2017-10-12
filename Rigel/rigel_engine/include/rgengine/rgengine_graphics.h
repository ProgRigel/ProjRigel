#pragma once
#include <rggraphics\rggraphics.h>

namespace rg::rgengine {

	struct RgEngineExternalAdapter;

	class RgEngineGraphics {
	public:
		static RgEngineGraphics* GetInstance();
		static RgEngineGraphics* Release(RgEngineGraphics *);
		bool Init(const RgEngineExternalAdapter& adapter);

		//Public APIs

	private:
		RgEngineGraphics();
		~RgEngineGraphics();
		void Release();
		RgEngineGraphics(const RgEngineGraphics&) = delete;
		RgEngineGraphics& operator=(const RgEngineGraphics&) = delete;

		static RgEngineGraphics* m_pInstance;
		rg::RgGraphicsContext * m_pRgGraphicsContext = nullptr;

	private:
		void InternalProcessWindowResize(unsigned int width, unsigned int height);
		void InternalProcessWindowExitResize();
		void InternalProcessWindowEnterResize();
		bool m_bOnWindowDrag = false;


	};
}