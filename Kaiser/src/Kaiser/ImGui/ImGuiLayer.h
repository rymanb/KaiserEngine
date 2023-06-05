#pragma once

#include "Kaiser/Layer.h"
#include "Kaiser/Core.h"

namespace Kaiser
{
	class KAISER_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate() override;
		virtual void OnEvent(Event& event) override;
		
		void Begin();
		void End();
		
		void BlockEvents(bool block) { m_BlockEvents = block; }
		
		void SetDarkThemeColors();
	
	private:

		
		bool m_BlockEvents = true;
	
	};
}