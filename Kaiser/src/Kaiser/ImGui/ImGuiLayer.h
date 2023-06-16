#pragma once

#include "Kaiser/Layer.h"
#include "Kaiser/Core.h"

namespace Kaiser
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		
		virtual void OnUpdate() override;
		
		
		void Begin();
		void End();
		
		void BlockEvents(bool block) { m_BlockEvents = block; }
		
		void SetDarkThemeColors();
	
	private:

		
		bool m_BlockEvents = true;
	
	};
}