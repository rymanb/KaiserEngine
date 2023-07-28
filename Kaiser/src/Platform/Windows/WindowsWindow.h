#pragma once
#pragma once

#include "Kaiser/Core/Window.h"

#include <GLFW/glfw3.h>

#include "Kaiser/Renderer/GraphicsContext.h"

namespace Kaiser {

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return mData.Width; }
		inline unsigned int GetHeight() const override { return mData.Height; }

		// Window attributes
		inline void SetEventCallback(const EventCallbackFn& callback) override { mData.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		inline virtual void* GetNativeWindow() const { return mWindow; }
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		GLFWwindow* mWindow;
		GraphicsContext* mContext;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData mData;
	};

}