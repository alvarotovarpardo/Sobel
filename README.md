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
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
```
Once compiled, the console application can be distributed via Sobel/dist folder using
```bash
cmake --install . --config Release --prefix "../dist"
```

- Cli -> For console application; .exe file generated @ build/cli/(build_type)/SobelCli.exe