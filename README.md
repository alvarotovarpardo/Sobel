# Sobel
Scalable application of Sobel algorithm. 

## Compilation
CMake is required.
Conan can be installed (Python & Pip is required) through
```bash
pip install conan
conan profile detect
```

Sobel project can be compiled with
```bash
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
```
Once compiled, the console application can be distributed via Sobel/dist folder using
```bash
cmake --install . --config Release --prefix "../dist"
```

- Cli -> For console application; .exe file generated @ build/cli/(build_type)/SobelCli.exe
- Android -> For Android App + basic UI
- <img width="215" height="445" alt="Captura de pantalla 2026-07-15 122308" src="https://github.com/user-attachments/assets/e47bcd67-1703-4732-88df-e4490e08d2e7" />

# Code features 
## Design patterns
- Factory: *FilterBase* acts as a pure abstract interface allowing the implementation of other filters in the future without re-defining the existing code.
- Singleton: *Logger* guarantees a single global instance for safe logging through mutex to prevent thread collision.
- Bridge: The intent of *android_bridge* (Android) is to separate the implementation from the 'Core' abstraction (more below).
## Architecture
Modular and multilayered architecture to ensure scalability is chosen.
* **Core (`/core`):** Intended to provide nuclear features and heavy workload for filtering processes. It is the common code for different applications.
* **CLI (`/cli`):** The Command Line Interface wrapper. It consumes the core library to provide a terminal-based execution environment with I/O and user arguments.
* **Android (`/android`):** The mobile application layer. It acts as a bridge between the C++ core and the Android environment.
* **Qt (`/qt`):** The graphical desktop interface layer. **To be implemented**.
## Memory management
- Dynamic instances by using unique pointers, ensuring that the memory is freed if an exception/crash occurs.
## Scalability
- Architecture: a multilayer architecture that separates the pure filtering logic in _core_ from user interfaces, *cli*, *android*, *qt* allows an specific compilation depending on the user's needs.
- Package Management: **Conan** + **CMake** makes the compilation easily duplicated without forcing the user to install or compile libraries manually in any platform.
- Single Responsibility: Classes like *Util*, *ImageProcessor* allows to easily increase functionality by responsability division (not giant classes).
## Performance
- **OpenMP** integrated in the core of filtering processes to achieve performance improvement.
- **OpenCL**: To be implemented.
## Weak points, technical debt and disadvantages
- `main.cpp` does too much (path logic, flow control, ...). This should be delegated into other classes.
- OpenCV coupled to core: The biggest technical debt. `/core` depends on OpenCV, which forces the programmer to make cross-compilation or have the library installed to use some core features in other platforms, such as `qt` or `android`. It's been patched with `#ifndef __ANDROID__` macro. Futher, it forces the programmer to use OpenCV even if the interfaces don't use it.
