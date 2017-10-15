#include "rggraphics.h"
#include "rg_render_target.h"

namespace rg {
	RgRenderTarget::RgRenderTarget()
	{
	}
	RgRenderTarget::~RgRenderTarget()
	{
		Release();
	}
	void * RgRenderTarget::GetColorBufferPtr()
	{
		return m_pColorBufferPtr;
	}
	void * RgRenderTarget::GetDepthBufferPtr()
	{
		return m_pDepthBufferPtr;
	}
	void RgRenderTarget::SetColorBufferPtr(void * ptr)
	{
		m_pColorBufferPtr = ptr;
	}
	void RgRenderTarget::SetDepthBufferPtr(void * ptr)
	{
		m_pDepthBufferPtr = ptr;
	}
	void RgRenderTarget::Release()
	{
		if (m_pColorBufferPtr != nullptr || m_pDepthBufferPtr != nullptr) {
			RgLogE() << "render target not released!";
		}
	}
}

