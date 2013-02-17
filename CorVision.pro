TEMPLATE = app
CONFIG -= console
CONFIG -= app_bundle
CONFIG -= qt

GLFW_DIR=C:/devTools/cpplibs/glfw-2.7.7.bin.WIN32
MIN_GW_LIB=C:/devTools/MinGW/x32/posix/i686-w64-mingw32/lib
GLEW_DIR=C:/devTools/cpplibs/glew-1.9.0 #-MinGW-x32-posix

INCLUDEPATH +=$${GLFW_DIR}/include/
INCLUDEPATH +=$${GLEW_DIR}/include/

LIBS += -lglfw -L$${GLFW_DIR}/lib-mingw/
LIBS += -lopengl32 -L$${MIN_GW_LIB}
LIBS += -lglew32 -L$${GLEW_DIR}/lib/

HEADERS += \
    core/world.h \
    core/camera.h \
    math/vector4.h \
    math/vector3.h \
    math/vector2.h \
    math/quat.h \
    math/matrix4.h \
    math/matrix3.h \
    math/matrix2.h \
    math/mathgl.h \
    math/math3d.h \
    render/renderprogram.h \
    render/renderobject.h \
    render/glinclude.h \
    render/glcontext.h \
    util/Logger.h \
    render/mesh.h

SOURCES += \
    core/world.cpp \
    core/camera.cpp \
    render/renderprogram.cpp \
    render/renderobject.cpp \
    render/glcontext.cpp \
    util/Logger.cpp \
    main.cpp \
    render/mesh.cpp


