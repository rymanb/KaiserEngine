#include "stdafx.h"
#include "WindowsWindow.h"
#include "Kaiser/Core/Trace.h"

#include "Kaiser/Core/Events/AppEvent.h"
#include "Kaiser/Core/Events/KeyEvent.h"
#include "Kaiser/Core/Events/MouseEvent.h"

#include "Platform/OpenGL/OpenGLContext.h"





namespace Kaiser {

	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char* description)
	{
		KS_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		mData.Title = props.Title;
		mData.Width = props.Width;
		mData.Height = props.Height;


		KS_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		
		if (!s_GLFWInitialized)
		{
			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			KS_CORE_ASSERT(success, "Could not intialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			 
			s_GLFWInitialized = true;
		}

		mWindow = glfwCreateWindow((int)props.Width, (int)props.Height, mData.Title.c_str(), nullptr, nullptr);

		mContext = new OpenGLContext(mWindow);
		mContext->Init();
		

		KS_CORE_ASSERT(status, "Failed to initialize Glad!");
		glfwSetWindowUserPointer(mWindow, &mData);
		SetVSync(true);

		// Set GLFW callbacks
		glfwSetWindowSizeCallback(mWindow, [](GLFWwindow* win, int width, int height)
			{
				auto& data = *(WindowData*)glfwGetWindowUserPointer(win);
				data.Width = width;
				data.Height = height;

				WindowResizeEvent event(width, height);
				data.EventCallback(event);
			});

		glfwSetWindowCloseCallback(mWindow, [](GLFWwindow* win)
			{
				auto& data = *(WindowData*)glfwGetWindowUserPointer(win);
				WindowCloseEvent event;
				data.EventCallback(event);
			});
		glfwSetKeyCallback(mWindow, [](GLFWwindow* win, int key, int scancode, int action, int mods)
			{
				auto& data = *(WindowData*)glfwGetWindowUserPointer(win);
				switch (action)
				{
					case GLFW_PRESS:
					{
						KeyPressedEvent event(key, 0);
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleasedEvent event(key);
						data.EventCallback(event);
						break;
					}
					case GLFW_REPEAT:
					{
						KeyPressedEvent event(key, 1);
						data.EventCallback(event);
						break;
					}
				}
			});
		glfwSetMouseButtonCallback(mWindow, [](GLFWwindow* win, int button, int action, int mods)
			{
				auto& data = *(WindowData*)glfwGetWindowUserPointer(win);
				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
				
				}
			});

		glfwSetScrollCallback(mWindow, [](GLFWwindow* win, double x, double y)
			{
				auto& data = *(WindowData*)glfwGetWindowUserPointer(win);

				MouseScrolledEvent event((float)x, (float)y);
				data.EventCallback(event);
			});
		glfwSetCursorPosCallback(mWindow, [](GLFWwindow* win, double x, double y)
			{
				auto& data = *(WindowData*)glfwGetWindowUserPointer(win);

				MouseMovedEvent event((float)x, (float)y);
				data.EventCallback(event);
			});
		
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(mWindow);
		delete mContext;
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		mContext->SwapBuffers();

	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		mData.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return mData.VSync;
	}

}