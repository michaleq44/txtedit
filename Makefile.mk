debug:
	mkdir -f build
	mkdir -f build/bin
	gcc main.c -o build/bin/txtedit.exe -I${MSYS_PATH}/ucrt64/include/gtk-3.0 -I${MSYS_PATH}/ucrt64/include/pango-1.0 -I${MSYS_PATH}/ucrt64/include/harfbuzz -I${MSYS_PATH}/ucrt64/include/cairo -I${MSYS_PATH}/ucrt64/include/freetype2 -I${MSYS_PATH}/ucrt64/include/pixman-1 -I${MSYS_PATH}/ucrt64/include/gdk-pixbuf-2.0 -I${MSYS_PATH}/ucrt64/include/libpng16 -I${MSYS_PATH}/ucrt64/include/webp -DLIBDEFLATE_DLL -I${MSYS_PATH}/ucrt64/include/atk-1.0 -I${MSYS_PATH}/ucrt64/include/fribidi -I${MSYS_PATH}/ucrt64/include/glib-2.0 -I${MSYS_PATH}/ucrt64/lib/glib-2.0/include -lgtk-3 -lgdk-3 -lz -lgdi32 -limm32 -lshell32 -lole32 -luuid -lwinmm -ldwmapi -lsetupapi -lcfgmgr32 -lhid -lwinspool -lcomctl32 -lcomdlg32 -lpangocairo-1.0 -lpangowin32-1.0 -lpango-1.0 -lcairo-gobject -lcairo -lharfbuzz -lgdk_pixbuf-2.0 -latk-1.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0 -lintl
	cd build/bin ; ./txtedit

release:
	mkdir -f build
	mkdir -f build/bin
	gcc main.c -o build/bin/txtedit.exe -I${MSYS_PATH}/ucrt64/include/gtk-3.0 -I${MSYS_PATH}/ucrt64/include/pango-1.0 -I${MSYS_PATH}/ucrt64/include/harfbuzz -I${MSYS_PATH}/ucrt64/include/cairo -I${MSYS_PATH}/ucrt64/include/freetype2 -I${MSYS_PATH}/ucrt64/include/pixman-1 -I${MSYS_PATH}/ucrt64/include/gdk-pixbuf-2.0 -I${MSYS_PATH}/ucrt64/include/libpng16 -I${MSYS_PATH}/ucrt64/include/webp -DLIBDEFLATE_DLL -I${MSYS_PATH}/ucrt64/include/atk-1.0 -I${MSYS_PATH}/ucrt64/include/fribidi -I${MSYS_PATH}/ucrt64/include/glib-2.0 -I${MSYS_PATH}/ucrt64/lib/glib-2.0/include -lgtk-3 -lgdk-3 -lz -lgdi32 -limm32 -lshell32 -lole32 -luuid -lwinmm -ldwmapi -lsetupapi -lcfgmgr32 -lhid -lwinspool -lcomctl32 -lcomdlg32 -lpangocairo-1.0 -lpangowin32-1.0 -lpango-1.0 -lcairo-gobject -lcairo -lharfbuzz -lgdk_pixbuf-2.0 -latk-1.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0 -lintl -mwindows
	cd build/bin ; ./txtedit