# Sobel
Application of Sobel algorithm. 

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
