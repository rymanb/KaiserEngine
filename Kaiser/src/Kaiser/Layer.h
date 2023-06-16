#pragma once
#include "Kaiser/Core.h"
#include "Kaiser/Events/Event.h"

namespace Kaiser {

	class Scene;
	
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}
		virtual void OnImGuiRender() {}

		inline const std::string& GetName() const { return mDebugName; }
		const Ref<Scene>& GetActiveScene() const { return mActiveScene; }
	protected:
		std::string mDebugName;
		
		Ref<Scene> mActiveScene;
		
	};

}