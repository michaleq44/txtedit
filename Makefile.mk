PROJECT_VERSION = "1.2.2"

debug:
	rm -rf build/debug
	mkdir -p build/debug/bin
	mkdir build/debug/data
	cp -f ./data/style.css ./data/icon.png ./build/debug/data
	gcc src/main.c -o build/debug/bin/txtedit.exe -Iinc -I${MSYS_PATH}/ucrt64/include/gtk-3.0 -I${MSYS_PATH}/ucrt64/include/pango-1.0 -I${MSYS_PATH}/ucrt64/include/harfbuzz -I${MSYS_PATH}/ucrt64/include/cairo -I${MSYS_PATH}/ucrt64/include/freetype2 -I${MSYS_PATH}/ucrt64/include/pixman-1 -I${MSYS_PATH}/ucrt64/include/gdk-pixbuf-2.0 -I${MSYS_PATH}/ucrt64/include/libpng16 -I${MSYS_PATH}/ucrt64/include/webp -DLIBDEFLATE_DLL -I${MSYS_PATH}/ucrt64/include/atk-1.0 -I${MSYS_PATH}/ucrt64/include/fribidi -I${MSYS_PATH}/ucrt64/include/glib-2.0 -I${MSYS_PATH}/ucrt64/lib/glib-2.0/include -lgtk-3 -lgdk-3 -lz -lgdi32 -limm32 -lshell32 -lole32 -luuid -lwinmm -ldwmapi -lsetupapi -lcfgmgr32 -lhid -lwinspool -lcomctl32 -lcomdlg32 -lpangocairo-1.0 -lpangowin32-1.0 -lpango-1.0 -lcairo-gobject -lcairo -lharfbuzz -lgdk_pixbuf-2.0 -latk-1.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0 -lintl -lfreetype -DDEBUG
	cd build/debug/bin ; ./txtedit

_r:
	rm -rf build/release
	mkdir -p build/release/bin/
	mkdir build/release/data
	cp -f ./data/style.css ./data/icon.png ./build/release/data
	windres src/icon.rc ./build/release/bin/icon.o
	gcc -c src/main.c -o build/release/bin/txtedit.o -Iinc -I${MSYS_PATH}/ucrt64/include/gtk-3.0 -I${MSYS_PATH}/ucrt64/include/pango-1.0 -I${MSYS_PATH}/ucrt64/include/harfbuzz -I${MSYS_PATH}/ucrt64/include/cairo -I${MSYS_PATH}/ucrt64/include/freetype2 -I${MSYS_PATH}/ucrt64/include/pixman-1 -I${MSYS_PATH}/ucrt64/include/gdk-pixbuf-2.0 -I${MSYS_PATH}/ucrt64/include/libpng16 -I${MSYS_PATH}/ucrt64/include/webp -DLIBDEFLATE_DLL -I${MSYS_PATH}/ucrt64/include/atk-1.0 -I${MSYS_PATH}/ucrt64/include/fribidi -I${MSYS_PATH}/ucrt64/include/glib-2.0 -I${MSYS_PATH}/ucrt64/lib/glib-2.0/include -O3
	gcc ./build/release/bin/txtedit.o ./build/release/bin/icon.o -o build/release/bin/txtedit.exe -lgtk-3 -lgdk-3 -lz -lgdi32 -limm32 -lshell32 -lole32 -luuid -lwinmm -ldwmapi -lsetupapi -lcfgmgr32 -lhid -lwinspool -lcomctl32 -lcomdlg32 -lpangocairo-1.0 -lpangowin32-1.0 -lpango-1.0 -lcairo-gobject -lcairo -lharfbuzz -lgdk_pixbuf-2.0 -latk-1.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0 -lintl -mwindows -O3
	rm -f build/release/bin/*.o

pkg: _r
	rm -rf "./release/v$(PROJECT_VERSION)"
	rm -f "./release/v$(PROJECT_VERSION).zip"
	mkdir -p "./release/v$(PROJECT_VERSION)/data"
	cp -rf ./release/bin "./release/v$(PROJECT_VERSION)/"
	cp -rf ./release/share "./release/v$(PROJECT_VERSION)/"
	cp -f ./data/style.css ./data/icon.png "./release/v$(PROJECT_VERSION)/data"
	cp -f ./data/icon.ico "./release/v$(PROJECT_VERSION)/txtedit.ico"
	cp -f ./README.md "./release/v$(PROJECT_VERSION)/"
	cp -f ./LICENSE "./release/v$(PROJECT_VERSION)/"
	cp -f ./build/release/bin/txtedit.exe "./release/v$(PROJECT_VERSION)/bin/"
	cd release ; zip -rv "./txtedit v$(PROJECT_VERSION)-win64.zip" "./v$(PROJECT_VERSION)"
	iscc ./setup.iss

release: _r
	cd build/release/bin ; ./txtedit