//#pragma once
//
//#pragma once
//
//#include "Kaiser/Core/Core.h"
//
//#include "Framebuffer.h"
//
//namespace Kaiser {
//
//	struct RenderPassSpecification
//	{
//		Ref<Framebuffer> TargetFramebuffer;
//	};
//
//	class RenderPass
//	{
//	public:
//		virtual ~RenderPass() {}
//
//		virtual const RenderPassSpecification& GetSpecification() const = 0;
//
//		static Ref<RenderPass> Create(const RenderPassSpecification& spec);
//	};
//
//}