PROJECT_VERSION = "1.1.0"

debug:
	rm -rf build/release
	mkdir -p build/debug/bin
	cp -rf ./data ./build/debug/
	gcc main.c -o build/debug/bin/txtedit.exe -I${MSYS_PATH}/ucrt64/include/gtk-3.0 -I${MSYS_PATH}/ucrt64/include/pango-1.0 -I${MSYS_PATH}/ucrt64/include/harfbuzz -I${MSYS_PATH}/ucrt64/include/cairo -I${MSYS_PATH}/ucrt64/include/freetype2 -I${MSYS_PATH}/ucrt64/include/pixman-1 -I${MSYS_PATH}/ucrt64/include/gdk-pixbuf-2.0 -I${MSYS_PATH}/ucrt64/include/libpng16 -I${MSYS_PATH}/ucrt64/include/webp -DLIBDEFLATE_DLL -I${MSYS_PATH}/ucrt64/include/atk-1.0 -I${MSYS_PATH}/ucrt64/include/fribidi -I${MSYS_PATH}/ucrt64/include/glib-2.0 -I${MSYS_PATH}/ucrt64/lib/glib-2.0/include -lgtk-3 -lgdk-3 -lz -lgdi32 -limm32 -lshell32 -lole32 -luuid -lwinmm -ldwmapi -lsetupapi -lcfgmgr32 -lhid -lwinspool -lcomctl32 -lcomdlg32 -lpangocairo-1.0 -lpangowin32-1.0 -lpango-1.0 -lcairo-gobject -lcairo -lharfbuzz -lgdk_pixbuf-2.0 -latk-1.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0 -lintl -DDEBUG
	cd build/debug/bin ; ./txtedit

release:
	rm -rf build/release
	mkdir -p build/release/bin
	cp -rf ./data ./build/release
	windres icon.rc ./build/release/bin/icon.o
	gcc -c main.c -o build/release/bin/txtedit.o -I${MSYS_PATH}/ucrt64/include/gtk-3.0 -I${MSYS_PATH}/ucrt64/include/pango-1.0 -I${MSYS_PATH}/ucrt64/include/harfbuzz -I${MSYS_PATH}/ucrt64/include/cairo -I${MSYS_PATH}/ucrt64/include/freetype2 -I${MSYS_PATH}/ucrt64/include/pixman-1 -I${MSYS_PATH}/ucrt64/include/gdk-pixbuf-2.0 -I${MSYS_PATH}/ucrt64/include/libpng16 -I${MSYS_PATH}/ucrt64/include/webp -DLIBDEFLATE_DLL -I${MSYS_PATH}/ucrt64/include/atk-1.0 -I${MSYS_PATH}/ucrt64/include/fribidi -I${MSYS_PATH}/ucrt64/include/glib-2.0 -I${MSYS_PATH}/ucrt64/lib/glib-2.0/include
	gcc ./build/release/bin/txtedit.o ./build/release/bin/icon.o -o build/release/bin/txtedit.exe -lgtk-3 -lgdk-3 -lz -lgdi32 -limm32 -lshell32 -lole32 -luuid -lwinmm -ldwmapi -lsetupapi -lcfgmgr32 -lhid -lwinspool -lcomctl32 -lcomdlg32 -lpangocairo-1.0 -lpangowin32-1.0 -lpango-1.0 -lcairo-gobject -lcairo -lharfbuzz -lgdk_pixbuf-2.0 -latk-1.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0 -lintl -mwindows
	rm -f build/release/bin/*.o

	rm -rf "./release/v$(PROJECT_VERSION)"
	rm -f "./release/v$(PROJECT_VERSION).zip"
	mkdir "./release/v$(PROJECT_VERSION)"
	cp -rf ./release/bin "./release/v$(PROJECT_VERSION)/"
	cp -rf ./release/share "./release/v$(PROJECT_VERSION)/"
	cp -rf ./data "./release/v$(PROJECT_VERSION)/"
	cp -f ./icon.ico "./release/v$(PROJECT_VERSION)/"
	cp -f ./README.md "./release/v$(PROJECT_VERSION)/"
	cp -f ./LICENSE "./release/v$(PROJECT_VERSION)/"
	cp -f ./build/release/bin/txtedit.exe "./release/v$(PROJECT_VERSION)/bin/"
	cd release ; zip -rv "./txtedit v$(PROJECT_VERSION)-win64.zip" "./v$(PROJECT_VERSION)"
	iscc ./setup.iss

	cd build/release/bin ; ./txtedit