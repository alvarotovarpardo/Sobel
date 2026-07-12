# Sobel
Application of Sobel algorithm. 
## Compilation with Conan

Conan can be installed through
```bash
pip install conan
conan profile detect
```

Sobel project can be compiled with
```bash
mkdir build
cd build
conan install .. --output-folder=. -g CMakeDeps -g CMakeToolchain --build=missing -r conancenter
cmake .. -DCMAKE_POLICY_DEFAULT_CMP0091="NEW" -DCMAKE_TOOLCHAIN_FILE="build/generators/conan_toolchain.cmake" -G "Visual Studio 17 2022" 
cmake --build . --config Release
```

## Compilation without Conan (Using system libraries)

If Conan is not used, one must install the dependencies on his own. It is: OpenCV [...].
Sobel can be compiled with
LINUX:
```bash
mkdir build && cd build
cmake .. -DCMAKE_PREFIX_PATH="$(brew --prefix opencv)"
cmake --build . --config Release
```
WINDOWS:
