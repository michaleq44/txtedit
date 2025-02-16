# txtedit
featureless text editor FOR WINDOWS (for now) written in c using gtk3

## compilation
Instructions on how to compile.

### dependencies
requires:
- gtk3 libs in PATH
- MSYS2 root directory in MSYS_PATH environmental variable
- mingw-w64-ucrt-x86_64-gtk3 package installed in MSYS2 for gtk3
- mingw-w64-ucrt-x86_64-gcc package installed in MSYS2 for gcc
- MSYS2 /ucrt64/bin/ and /usr/bin/ in PATH
- make or cmake as a compilation method (you can also copy the command from the Makefile.mk to the console)

### instructions
- go into the repo's root directory
- run:
    - `cmake` with `Debug/Release` build type (eg. `cmake {args} -DCMAKE_BUILD_TYPE=Debug`) (I use CLion so I don't know how CMake actually works)
    - `make debug` or `make release`
- congratulations! you have compiled my beautiful program! now, because of the dependencies you have all the libraries needed but if you were to redistribute a modified version make sure to include all the dlls in the release
- if you don't trust my abilities you can use `ldd txtedit.exe` in order to check the needed dlls
- the `data` and `share` directories (the latter is from the release) have to be one folder depth higher than the executable (i.e. in the same directory as the bin folder)

## GOOD LUCK (you should uninstall VSCode or whatever you use now)
