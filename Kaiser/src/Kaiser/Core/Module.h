#pragma once

#include "Kaiser/Core/Core.h"
#include <string_view>



	namespace Kaiser
	{

	class Module;


		struct IEngine
		{
			virtual void Add(Ref<Module> module, std::string_view name) = 0;
			virtual Ref<Module> Get(std::string_view name) const = 0;
			virtual void Init() = 0;
			virtual void Update(float dt) = 0;
			virtual void Shutdown() = 0;

			template<typename T>
			Ref<T> Get() const
			{

				Ref<Module> module = Get(T::Name());



				return static_pointer_cast<T>(module);
			}

			template<typename T, typename ... Args>
			void Add(Args&&... args)
			{
				Add(Ref<T>(new T(std::forward<Args>(args)...)), T::Name());
			}
			

			virtual ~IEngine() = default;
		};

		//! Base Module for systems
		class Module
		{
		public:
			Module() :mParent(nullptr) {}

			virtual void Load() {};
			//! Virtual Init function
			virtual void Init() = 0;
			//! Virtual Update function
			virtual void Update() = 0;

			virtual void Unload() {};
			//! Virtual Shutdown function
			virtual void Shutdown() = 0;

			void SetParent(IEngine* engine) { mParent = engine; };

			IEngine* GetParent(void) const
			{
				return mParent;
			}

			template<typename T>
			Ref<T> Get() const
			{
				return GetParent()->Get<T>();
			}

			//! Virtual Deconstructor function
			virtual ~Module() = default;

		private:
			IEngine* mParent;
		};

	}

