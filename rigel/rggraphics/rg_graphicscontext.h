#pragma once

namespace rg {
	class RgGraphicsContext
	{
	public:
		RgGraphicsContext();
		
	protected:
		virtual ~RgGraphicsContext();
		virtual void init() = 0;
		virtual void release() = 0;

		RgGraphicsContext(const RgGraphicsContext&) = delete;
		const RgGraphicsContext& operator=(const RgGraphicsContext&) = delete;

	public:
		friend class RgGraphicsAPI;
	};
}
