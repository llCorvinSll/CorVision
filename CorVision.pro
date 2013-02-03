TEMPLATE = app
CONFIG -= console
CONFIG -= app_bundle
CONFIG -= qt

GLFW_DIR=C:/devTools/cpplibs/glfw-2.7.7.bin.WIN32
MIN_GW_LIB=C:/devTools/MinGW/x32/posix/i686-w64-mingw32/lib
GLEW_DIR=C:/devTools/cpplibs/glew-1.9.0 #-MinGW-x32-posix
GL_DIR=C:\devTools\cpplibs\glm-0.9.4.1

INCLUDEPATH +=$${GL_DIR}
INCLUDEPATH +=$${GLFW_DIR}/include/
INCLUDEPATH +=$${GLEW_DIR}/include/

LIBS += -lglfw -L$${GLFW_DIR}/lib-mingw/
LIBS += -lopengl32 -L$${MIN_GW_LIB}
LIBS += -lglew32 -L$${GLEW_DIR}/lib/

SOURCES += main.cpp \
    render/glcontext.cpp \
    main/world.cpp


HEADERS += \
    math/vec4.h \
    math/vec3.h \
    math/vec2.h \
    math/quat.h \
    math/mathgl.h \
    math/math3d.h \
    math/mat4.h \
    math/mat3.h \
    math/mat2.h \
    render/glcontext.h \
    main/world.h \
    render/glinclude.h

