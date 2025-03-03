cmake_minimum_required(VERSION 3.30)
project(txtedit LANGUAGES C VERSION 1.2.2)

set(CMAKE_C_STANDARD 11)

# ewrwfsfssfd
set(K " ")

set(MSYS_PATH "$ENV{MSYS_PATH}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

if (CMAKE_BUILD_TYPE MATCHES Release)
    message("Compiling Release build...")
    set(CMAKE_EXE_LINKER_FLAGS "-mwindows")
elseif (CMAKE_BUILD_TYPE MATCHES Debug)
    set(CMAKE_C_FLAGS "-DDEBUG")
    message("Compiling Debug build...")
endif ()

include_directories("${CMAKE_SOURCE_DIR}/inc" "${MSYS_PATH}/ucrt64/include/gtk-3.0" "${MSYS_PATH}/ucrt64/include/pango-1.0" "${MSYS_PATH}/ucrt64/include/harfbuzz" "${MSYS_PATH}/ucrt64/include/cairo" "${MSYS_PATH}/ucrt64/include/freetype2" "${MSYS_PATH}/ucrt64/include/pixman-1" "${MSYS_PATH}/ucrt64/include/gdk-pixbuf-2.0" "${MSYS_PATH}/ucrt64/include/libpng16" "${MSYS_PATH}/ucrt64/include/webp -DLIBDEFLATE_DLL" "${MSYS_PATH}/ucrt64/include/atk-1.0" "${MSYS_PATH}/ucrt64/include/fribidi" "${MSYS_PATH}/ucrt64/include/glib-2.0" "${MSYS_PATH}/ucrt64/lib/glib-2.0/include")
add_executable(txtedit src/main.c
        inc/main.h
        inc/menubar/menubar.h
        inc/menubar/file.h
        inc/menubar/help.h
        inc/editor.h)

target_link_libraries(txtedit "gtk-3" "gdk-3" "z" "gdi32" "imm32" "shell32" "ole32" "uuid" "winmm" "dwmapi" "setupapi" "cfgmgr32" "hid" "winspool" "comctl32" "comdlg32" "pangowin32-1.0" "pangocairo-1.0" "pango-1.0" "harfbuzz" "atk-1.0" "cairo-gobject" "cairo" "gdk_pixbuf-2.0" "gio-2.0" "gobject-2.0" "glib-2.0" "intl")