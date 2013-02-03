#include <render/glcontext.h>
#include <main/world.h>

using namespace core;
using namespace render;

int main( void )
{
    World::I().initWorld();
    GLContext::I().initContext();
    GLContext::I().connectToWorld();
    do{
        GLContext::I().renderScene();
    }while(World::I().runnig);

    GLContext::I().clearContext();
    return 0;
}

