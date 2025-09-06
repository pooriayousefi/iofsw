# IOFSW - RAII I/O File Stream Wrappers

[![Build Status](https://github.com/pooriayousefi/iofsw/actions/workflows/ci.yml/badge.svg)](https://github.com/pooriayousefi/iofsw/actions/workflows/ci.yml)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C++20](https://img.shields.io/badge/C%2B%2B-20-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B20)
[![CMake](https://img.shields.io/badge/CMake-3.20%2B-green.svg)](https://cmake.org/)

A modern C++20 RAII (Resource Acquisition Is Initialization) I/O file stream wrapper module. IOFSW provides safe, exception-aware file handling with automatic resource management and comprehensive error checking.

## 🚀 Features

- **C++20 Modules**: Modern module interface for clean imports
- **RAII Compliance**: Automatic resource management and cleanup
- **Exception Safety**: Comprehensive error handling and reporting
- **Template-Based**: Generic implementation supporting various character types
- **Type Safety**: Compile-time type checking and validation
- **Cross-Platform**: Works on Linux (g++), macOS (clang++), and Windows (MSVC)

## 🎯 Quick Start

```cpp
import raiiiofsw;
#include <iostream>
#include <string>

int main() {
    try {
        // Input file stream wrapper
        toolb0x::raii::input_file_stream_wrapper input;
        input.open("data.txt");
        
        std::string line;
        while (input >> line) {
            std::cout << line << std::endl;
        }
        // File automatically closed when 'input' goes out of scope
        
        // Output file stream wrapper
        toolb0x::raii::output_file_stream_wrapper output;
        output.open("output.txt");
        output << "Hello, World!" << std::endl;
        // File automatically closed when 'output' goes out of scope
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    return 0;
}
```

## 📚 API Reference

### Core Wrapper Classes

#### `basic_input_file_stream_wrapper<Elem, Traits, Alloc>`

RAII wrapper for input file streams with automatic resource management.

```cpp
template<typename Elem, typename Traits = std::char_traits<Elem>, 
         typename Alloc = std::allocator<Elem>>
struct basic_input_file_stream_wrapper {
    // Constructor/Destructor
    basic_input_file_stream_wrapper();
    virtual ~basic_input_file_stream_wrapper();
    
    // File operations
    void open(std::filesystem::path file_path, 
              std::ios_base::openmode open_mode = std::ios_base::in);
    void close();
    bool is_open();
    
    // Stream operations
    template<typename T> 
    auto operator>>(T& value) -> type&;
};
```

#### `basic_output_file_stream_wrapper<Elem, Traits, Alloc>`

RAII wrapper for output file streams with automatic resource management.

```cpp
template<typename Elem, typename Traits = std::char_traits<Elem>, 
         typename Alloc = std::allocator<Elem>>
struct basic_output_file_stream_wrapper {
    // Constructor/Destructor
    basic_output_file_stream_wrapper();
    virtual ~basic_output_file_stream_wrapper();
    
    // File operations
    void open(std::filesystem::path file_path, 
              std::ios_base::openmode open_mode = std::ios_base::out);
    void close();
    bool is_open();
    
    // Stream operations
    template<typename T> 
    auto operator<<(const T& value) -> type&;
};
```

### Type Aliases

```cpp
// Convenient type aliases for common use cases
using input_file_stream_wrapper = basic_input_file_stream_wrapper<char>;
using output_file_stream_wrapper = basic_output_file_stream_wrapper<char>;
using winput_file_stream_wrapper = basic_input_file_stream_wrapper<wchar_t>;
using woutput_file_stream_wrapper = basic_output_file_stream_wrapper<wchar_t>;
```

## 🔧 Advanced Features

### Exception Safety

All operations provide strong exception safety guarantees:

```cpp
try {
    toolb0x::raii::input_file_stream_wrapper input;
    input.open("nonexistent_file.txt");  // Throws std::runtime_error
} catch (const std::runtime_error& e) {
    std::cerr << "File operation failed: " << e.what() << std::endl;
}
```

### Automatic Resource Management

File handles are automatically closed when wrapper objects go out of scope:

```cpp
{
    toolb0x::raii::output_file_stream_wrapper output;
    output.open("temp.txt");
    output << "Temporary data";
} // File automatically closed here, even if exceptions occur
```

### Multi-Character Support

Support for different character types and encodings:

```cpp
// Wide character support
toolb0x::raii::winput_file_stream_wrapper wide_input;
wide_input.open(L"unicode_file.txt");

std::wstring wide_line;
wide_input >> wide_line;
```

## 🏗️ Building from Source

```bash
# Clone repository
git clone https://github.com/pooriayousefi/iofsw.git
cd iofsw

# Build with CMake
cmake --preset=default
cmake --build build/default

# Run tests
./build/default/iofsw_test
```

## 📊 Use Cases

- **File Processing**: Safe file reading and writing operations
- **Data Persistence**: Application data storage with guaranteed cleanup
- **Log Management**: Automatic log file handling
- **Configuration Files**: Safe configuration file parsing
- **Resource Management**: Any scenario requiring automatic file handle cleanup

## 🔧 Requirements

- C++20 compatible compiler with modules support (GCC 11+, Clang 13+, MSVC 2022+)
- CMake 3.20 or later
- Standard library with filesystem support

## 📄 License

This project is licensed under the MIT License - see the [LICENSE.txt](LICENSE.txt) file for details.

---

**Author**: [Pooria Yousefi](https://github.com/pooriayousefi)  
**Repository**: [https://github.com/pooriayousefi/iofsw](https://github.com/pooriayousefi/iofsw)
