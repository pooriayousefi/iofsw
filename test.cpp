
#include <type_traits>
#include <exception>
#include <iostream>
#include <utility>
#include <chrono>
#include <thread>
import raiiiofsw;
using namespace toolb0x;
namespace
{
	template<typename F, typename... Args>
	decltype(auto) runtime(F&& f, Args&&... args)
	{
		if constexpr (std::is_same_v<std::invoke_result_t<F, Args...>, void>)
		{
			auto ti{ std::chrono::high_resolution_clock::now() };
			std::invoke(std::forward<F>(f), std::forward<Args>(args)...);
			auto tf{ std::chrono::high_resolution_clock::now() };
			return std::chrono::duration<double>(tf - ti).count();
		}
		if constexpr (!std::is_same_v<std::invoke_result_t<F, Args...>, void>)
		{
			auto ti{ std::chrono::high_resolution_clock::now() };
			auto retval{ std::invoke(std::forward<F>(f), std::forward<Args>(args)...) };
			auto tf{ std::chrono::high_resolution_clock::now() };
			return std::make_pair(std::move(retval), std::chrono::duration<double>(tf - ti).count());
		}
	}
}
int main()
{
	auto countdown = [](size_t nsec)
		{
			std::cout << "\n\ncountdown: T-";
			for (auto i{ static_cast<int>(nsec) }; i >= 0; --i)
			{
				std::this_thread::sleep_for(std::chrono::seconds(1));
				std::cout << i << ' ';
			}
		};
	try
	{
		raii::native::narrow_encoded::input_file_stream_wrapper ifsw1{};
		ifsw1.open(L"x.txt");
		(ifsw1.is_open() ? std::cout << "x.txt file is open.\n" : std::cout << "x.txt file is not open!\n");

		raii::utf8::output_file_stream_wrapper ofsw1{};
		ofsw1.open(L"x.txt", std::ios::app);
		ofsw1 << std::u8string{ u8"\nI was inserted by another stream!:)\n" };
		return 0;
	}
	catch (const std::exception& xxx)
	{
		std::cerr << xxx.what() << std::endl;
		return 1;
	}
}
