#include <renderer/chunk_mesh.hpp>
#include <iostream>
ChunkMesh::ChunkMesh(Block *blocks, int cx, int cz, const unsigned char cw, const unsigned char cl, const unsigned char ch, bool &disable_faces, World *world){
    this->blocks = blocks;
    this->cx = cx;
    this->cz = cz;
    this->cw =cw;
    this->cl = cl;
    this->ch = ch;
    this->disable_faces = disable_faces;
    this->world = world;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &TBO);

    glGenBuffers(1, &TVBO); // For transparent objects
    glGenBuffers(1, &TTBO);

    glGenBuffers(1, &LBO);
}

bool ChunkMesh::is_transparent(int x, int y, int z, unsigned char block_id){
    if(y < 0 || y > ch || !disable_faces) return true;
    Block *b = nullptr;
    if(x < 0){
        if(cx - 1 >= 0){
            b = world->get_chunk(cx - 1, cz)->get_block(15, y, z);
        }else{
            return true;
        }
    }else if(x > cw){
        if(cx + 1 < 16){
            b = world->get_chunk(cx + 1, cz)->get_block(0, y, z);
        }else{
            return true;
        }
    }else if(z < 0){
        if(cz - 1 >= 0){
            b = world->get_chunk(cx, cz - 1)->get_block(x, y, 15);
        }else{
            return true;
        }
    }else if(z > cl){
        if(cz + 1 < 16){
            b = world->get_chunk(cx, cz + 1)->get_block(x, y, 0);
        }else{
            return true;
        }
    }else{
        b = &blocks[x + y * (cl + 1) + z * (cw + 1) * (ch + 1)];
    }

    if(b->get_type() == ID::GLASS && block_id == ID::GLASS) return 0;

    switch (b->get_type())
    {
    case ID::AIR:
    case ID::GLASS:
        return true;
    
    default:
        return false;
    }
}

void ChunkMesh::build(){
    light_levels.clear();
    for(int x = 0; x < cw + 1; x++){
        for(int y = 0; y< ch + 1; y++){
            for(int z = 0; z < cl + 1; z++){
                Block b = blocks[x + y * (cl + 1) + z * (cw + 1) * (ch + 1)];

                float light = b.get_light() / 15.0f;
                float lightL = 15.0f, lightR = 15.0f, lightT = 15.0f, lightB = 15.0f, lightF = 15.0f, lightRR = 15.0f;

                lightL /= 15.0f;
                lightR /= 15.0f;
                lightT /= 15.0f;
                lightB /= 15.0f;
                lightF /= 15.0f;
                lightRR /= 15.0f;

                add_face(x, y, z, Face::LEFT, b.get_type(), lightL + 0.02f);
                add_face(x, y, z, Face::RIGHT, b.get_type(), lightR + 0.02f);
                add_face(x, y, z, Face::BOTTOM, b.get_type(), lightB + 0.01f);
                add_face(x, y, z, Face::TOP, b.get_type(), lightT + 0.04f);
                add_face(x, y, z, Face::BACK, b.get_type(), lightRR + 0.025f);
                add_face(x, y, z, Face::FRONT, b.get_type(), lightF + 0.025f);
           }
       }
   }

    vertices_size = vertices.size();
    texture_size = texture_coords.size();
    tvertices_size = tvertices.size();
    ttexture_size = ttexture_coords.size();
    light_level_size = light_levels.size();

    vBuff = new GLfloat[vertices_size];
    tBuff = new GLfloat[texture_size];
    tvBuff = new GLfloat[vertices_size];
    ttBuff = new GLfloat[texture_size];
    lBuff = new GLfloat[light_level_size];
    for(int i = 0; i < vertices_size; i++){
        vBuff[i] = vertices.at(i);
    }

    for(int i = 0; i < texture_size; i++){
        tBuff[i] = texture_coords.at(i);
    }

    for(int i = 0; i < tvertices_size; i++){
        tvBuff[i] = tvertices.at(i);
    }

    for(int i = 0; i < ttexture_size; i++){
        ttBuff[i] = ttexture_coords.at(i);
    }

    for(int i = 0; i < light_level_size; i++){
        lBuff[i] = light_levels.at(i);
    }

    vertices.clear();
    texture_coords.clear();
    tvertices.clear();
    ttexture_coords.clear();
    light_levels.clear();

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices_size, vBuff, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, TBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * texture_size, tBuff, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, LBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * light_level_size, lBuff, GL_STATIC_DRAW);


    glBindVertexArray(0);
    

    delete[] vBuff;
    delete[] tBuff;
    delete[] tvBuff;
    delete[] ttBuff;
    delete[] lBuff;

}

void ChunkMesh::add_face(int x, int y, int z, Face face, unsigned char type, float light){
    const float *face_vertex_array;
    int xx = x, yy = y, zz = z;
    switch (face) {
        case FRONT:
            zz += 1;
            face_vertex_array = cube_vertex_front;
            break;
        case BACK:
            zz -= 1;
            face_vertex_array = cube_vertex_back;
            break;
        case LEFT:
            xx -= 1;
            face_vertex_array = cube_vertex_left;
            break;
        case RIGHT:
            xx += 1;
            face_vertex_array = cube_vertex_right;
            break;
        case TOP:
            yy += 1;
            face_vertex_array = cube_vertex_top;
            break;
        case BOTTOM:
            yy -= 1;
            face_vertex_array = cube_vertex_bottom;
            break;
    }

    if(is_transparent(xx, yy, zz, type)){
        if(type != ID::AIR){
            add_face_vertices(face_vertex_array, x, y, z, light);

            add_texture_face(type, face, texture_coords);
        }
    }
}

void ChunkMesh::add_face_vertices(const float* vertex_array, int x, int y, int z, float light){
    for(int i = 0; i < 18; i+=3){
        vertices.push_back(vertex_array[i] + x + (cx * 16));
        vertices.push_back(vertex_array[i + 1] + y);
        vertices.push_back(vertex_array[i + 2] + z + (cz * 16));
        light_levels.push_back(light);
    }
}

void ChunkMesh::rebuild(Block *blocks){
    this->blocks = blocks;

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &TBO);
    glDeleteBuffers(1, &LBO);  

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &TBO);
    glGenBuffers(1, &LBO);   

    build();
}

void ChunkMesh::render(GLuint texture){
    glBindVertexArray(VAO);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_ALPHA_TEST);

    glEnableVertexAttribArray(0);
    

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(texture, 0);

    // Vertex data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);

    // Texture data
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, TBO);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void *) 0);

    // Light data
    glEnableVertexAttribArray(3);
    glBindBuffer(GL_ARRAY_BUFFER, LBO);
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 0, (void *) 0);

    glDrawArrays(GL_TRIANGLES, 0, vertices_size / 3);
    glDisableVertexAttribArray(0);

    glDisable(GL_BLEND);
    glDisable(GL_ALPHA_TEST);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

ChunkMesh::~ChunkMesh(){
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &TBO);
    glDeleteVertexArrays(1, &VAO);
}