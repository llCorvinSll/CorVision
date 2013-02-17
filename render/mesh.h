#ifndef MESH_H
#define MESH_H

#include "glinclude.h"
#include "math/mathgl.h"
#include <stdint.h>
#include <vector>


namespace render{
#define VERT_POSITION  0
#define VERT_TEXCOORD  1
#define VERT_NORMAL    2


struct Vertex{
    float position[3];
    float texcoord[2];
    float normal[3];
};


class Mesh{
public:
    GLuint VertexBuffer;

    math::Vector3 Position;
    math::Matrix3 Rotation;

    std::vector<math::Vector3> vertices;
    std::vector<math::Vector2> uvs;
    std::vector<math::Vector3> normals;

    void Create();
    void Render();
    math::Matrix4 getModelMatrix();
    bool loadFromOBJ(const char * path);

    void Remove();


    Mesh();

};
}

#endif // MESH_H
