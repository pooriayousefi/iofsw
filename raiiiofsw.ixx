export module raiiiofsw;
import <type_traits>;
import <filesystem>;
import <stdexcept>;
import <typeinfo>;
import <fstream>;
import <string>;

// toolb0x namespace
export namespace toolb0x
{
	// Resource Acquisition Is Initialization (RAII) namespace
	namespace raii
	{
		// basic input file stream
		template<typename Elem, typename Traits = std::char_traits<Elem>, typename Alloc = std::allocator<Elem>>
		struct basic_input_file_stream_wrapper
		{
			// type definitions
			using file_stream_type = std::basic_ifstream<Elem, Traits>;
			using type = basic_input_file_stream_wrapper<Elem, Traits, Alloc>;
			using string_type = std::basic_string<Elem, Traits, Alloc>;
			using stream_buffer_iterator = std::istreambuf_iterator<Elem, Traits>;

			// members
			file_stream_type file_stream;

			// ctors./dtor.
			basic_input_file_stream_wrapper() :file_stream{} {}
			virtual ~basic_input_file_stream_wrapper() { if (is_open()) close(); }

			// overloaded ops.
			template<typename T> constexpr auto operator>>(T& value) -> type& { file_stream >> value; return *this; }

			// methods
			auto is_open() -> bool { return file_stream.is_open(); }
			auto close() -> void { file_stream.close(); }
			auto open(std::filesystem::path file_path, std::ios_base::openmode open_mode = std::ios_base::in) -> void
			{
				file_stream.open(file_path, std::ios_base::in | open_mode);
				if (!is_open())
					throw std::runtime_error(
						std::string{
							std::string{"ERROR! Cannot open "} +
							file_path.string() +
							std::string{" file in toolb0x::raii::basic_input_file_stream_wrapper<"} +
							std::string{typeid(Elem).name()} +
							std::string{", "} +
							std::string{typeid(Traits).name()} +
							std::string{", "} +
							std::string{ typeid(Alloc).name() } +
							std::string{ ">::open() method." }
						}.c_str()
					);
			}
		};

		// binary specialized basic input file stream
		template<>
		struct basic_input_file_stream_wrapper<std::byte>
		{
			// type definitions
			using file_stream_type = std::basic_ifstream<std::byte>;
			using type = basic_input_file_stream_wrapper<std::byte>;
			using string_type = std::basic_string<std::byte>;
			using stream_buffer_iterator = std::istreambuf_iterator<std::byte>;

			// members
			file_stream_type file_stream;

			// ctors./dtor.
			basic_input_file_stream_wrapper() :file_stream{} {}
			virtual ~basic_input_file_stream_wrapper() { if (is_open()) close(); }

			// overloaded ops.
			template<typename T> constexpr auto operator>>(T& value) -> type& { file_stream >> value; return *this; }

			// methods
			auto is_open() -> bool { return file_stream.is_open(); }
			auto close() -> void { file_stream.close(); }
			auto open(std::filesystem::path file_path, std::ios_base::openmode open_mode = std::ios_base::in | std::ios_base::binary)
			{
				file_stream.open(file_path, std::ios_base::in | std::ios_base::binary | open_mode);
				if (!is_open())
					throw std::runtime_error(
						std::string{
							std::string{"ERROR! Cannot open "} +
							file_path.string() +
							std::string{" file in toolb0x::raii::basic_input_file_stream_wrapper<std::byte>::open() method." }
						}.c_str()
					);
			}
		};

		// basic output file stream
		template<typename Elem, typename Traits = std::char_traits<Elem>, typename Alloc = std::allocator<Elem>>
		struct basic_output_file_stream_wrapper
		{
			// type definitions
			using file_stream_type = std::basic_ofstream<Elem, Traits>;
			using type = basic_output_file_stream_wrapper<Elem, Traits, Alloc>;
			using string_type = std::basic_string<Elem, Traits, Alloc>;
			using stream_buffer_iterator = std::ostreambuf_iterator<Elem, Traits>;

			// members
			file_stream_type file_stream;

			// ctors./dtor.
			basic_output_file_stream_wrapper() :file_stream{} {}
			virtual ~basic_output_file_stream_wrapper() { if (is_open()) close(); }

			// overloaded ops.
			template<typename T> constexpr auto operator<<(const T& value) -> type& { file_stream << value; return *this; }
			template<typename T> constexpr auto operator<<(T&& value) noexcept -> type& { file_stream << value; return *this; }

			// methods
			auto is_open() -> bool { return file_stream.is_open(); }
			auto close() -> void { file_stream.flush(); file_stream.close(); }
			auto open(std::filesystem::path file_path, std::ios_base::openmode open_mode = std::ios_base::out) -> void
			{
				file_stream.open(file_path, std::ios::out | open_mode);
				if (!is_open())
					throw std::runtime_error(
						std::string{
							std::string{"ERROR! Cannot open "} +
							file_path.string() +
							std::string{" file in toolb0x::raii::basic_output_file_stream_wrapper<"} +
							std::string{typeid(Elem).name()} +
							std::string{", "} +
							std::string{typeid(Traits).name()} +
							std::string{", "} +
							std::string{ typeid(Alloc).name() } +
							std::string{ "::open() method." }
						}.c_str()
					);
			}
		};

		// binary specialized basic output file stream 
		template<>
		struct basic_output_file_stream_wrapper<std::byte>
		{
			// type definitions
			using file_stream_type = std::basic_ofstream<std::byte>;
			using type = basic_output_file_stream_wrapper<std::byte>;
			using string_type = std::basic_string<std::byte>;
			using stream_buffer_iterator = std::ostreambuf_iterator<std::byte>;

			// members
			file_stream_type file_stream;

			// ctors/dtor
			basic_output_file_stream_wrapper() :file_stream{} {}
			virtual ~basic_output_file_stream_wrapper() { if (is_open()) close(); }

			// overloaded ops.
			template<typename T> constexpr auto operator<<(const T& value) -> type& { file_stream << value; return *this; }
			template<typename T> constexpr auto operator<<(T&& value) noexcept -> type& { file_stream << value; return *this; }

			// methods
			auto is_open() -> bool { return file_stream.is_open(); }
			auto close() -> void { file_stream.flush(); file_stream.close(); }
			auto open(std::filesystem::path file_path, std::ios_base::openmode open_mode = std::ios_base::out | std::ios_base::binary) -> void
			{
				file_stream.open(file_path, std::ios::out | std::ios_base::binary | open_mode);
				if (!is_open())
					throw std::runtime_error(
						std::string{
							std::string{"ERROR! Cannot open "} +
							file_path.string() +
							std::string{" file in toolb0x::raii::basic_output_file_stream_wrapper<std::byte>::open() method." }
						}.c_str()
					);
			}
		};

		namespace native
		{
			namespace narrow_encoded 
			{
				using input_file_stream_wrapper = basic_input_file_stream_wrapper<char>;
				using output_file_stream_wrapper = basic_output_file_stream_wrapper<char>;
			}
			namespace wide_encoded
			{
				using input_file_stream_wrapper = basic_input_file_stream_wrapper<wchar_t>;
				using output_file_stream_wrapper = basic_output_file_stream_wrapper<wchar_t>;
			}
		}
		namespace utf8
		{
			using input_file_stream_wrapper = basic_input_file_stream_wrapper<char8_t>;
			using output_file_stream_wrapper = basic_output_file_stream_wrapper<char8_t>;
		}
		namespace binary
		{
			using input_file_stream_wrapper = basic_input_file_stream_wrapper<std::byte>;
			using output_file_stream_wrapper = basic_output_file_stream_wrapper<std::byte>;
		}
	}
}