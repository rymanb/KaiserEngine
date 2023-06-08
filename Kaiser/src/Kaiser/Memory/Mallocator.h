#pragma once

namespace Kaiser
{
	template <class T>
	struct Mallocator
	{
		typedef T value_type;

		Mallocator() = default;
		template <class U> constexpr Mallocator(const Mallocator <U>&) noexcept {}

		T* allocate(std::size_t n)
		{
#undef max
			if (n > std::numeric_limits<std::size_t>::max() / sizeof(T))
				throw std::bad_array_new_length();

			if (auto p = static_cast<T*>(std::malloc(n * sizeof(T)))) {
				return p;
			}

			throw std::bad_alloc();
		}

		void deallocate(T* p, std::size_t n) noexcept {
			std::free(p);
		}
	};
}