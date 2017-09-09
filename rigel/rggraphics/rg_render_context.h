#pragma once
#include <memory>

namespace rg {

	class RgGraphicsContext;
	class RgBuffer;
	class RgShader;
	class RgMaterial;

	class RgRenderContext {

	protected:
		RgRenderContext();
		virtual ~RgRenderContext();

		RgRenderContext(const RgRenderContext&) = delete;
		RgRenderContext& operator=(const RgRenderContext&) = delete;


	public:
		virtual void InputSetBuffer(std::shared_ptr<RgBuffer> buffer);
		virtual void InputSetMaterial(std::shared_ptr<RgMaterial> material);
		virtual void InputSetShader(std::shared_ptr<RgShader> shader);
		virtual void InputSetPrimitiveTopology();

		virtual void DrawIndexed(unsigned int size);
		virtual void Draw();

	public:
		friend class RgGraphicsContext;
	};
}