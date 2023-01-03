#include <renderer/chunk_mesh.hpp>
#include <iostream>

ChunkMesh::ChunkMesh(const std::vector<Block> &blocks, int cx, int cz){
    this->blocks = blocks;
    this->cx = cx;
    this->cz = cz;
}

bool ChunkMesh::is_transparent(int x, int y, int z){
    if(y < 0 || y > 255 || x < 0 || x > 15 || z < 0 || z > 15) return 1;


    Block b = blocks.at(x + y * 16 + z * 16 * 256);
    switch (b.get_type())
    {
    case 0:
    case 20:
        return 1;
    
    default:
        return 0;
    }
}

void ChunkMesh::build(){
    for(int x = 0; x < 16; x++){
        for(int y = 0; y< 256; y++){
            for(int z = 0; z < 16; z++){
                Block b = blocks.at(x + y * 16 + z * 16 * 256);//blocks.at(x + 16 * (y + 16 * z));
                
                if(b.get_type() == 0) continue;

                if(is_transparent(x - 1, y, z)){
                    for(int i = 0; i < 18; i+=3){
                        vertices.push_back(cube_vertex_left[i] + x + (cx * 16));
                        vertices.push_back(cube_vertex_left[i + 1] + y);
                        vertices.push_back(cube_vertex_left[i + 2] + z + (cz * 16));
                    }
                    
                    add_texture_face(b.get_type(), Face::LEFT, texture_coords);
                }

                if(is_transparent(x + 1, y, z)){
                    for(int i = 0; i < 18; i+=3){
                        vertices.push_back(cube_vertex_right[i] + x + (cx * 16));
                        vertices.push_back(cube_vertex_right[i + 1] + y);
                        vertices.push_back(cube_vertex_right[i + 2] + z + (cz * 16));
                    }
                    
                    add_texture_face(b.get_type(), Face::RIGHT, texture_coords);
                }

                if(is_transparent(x, y - 1, z)){
                    for(int i = 0; i < 18; i+=3){
                        vertices.push_back(cube_vertex_bottom[i] + x + (cx * 16));
                        vertices.push_back(cube_vertex_bottom[i + 1] + y);
                        vertices.push_back(cube_vertex_bottom[i + 2] + z + (cz * 16));
                    }
                    
                    add_texture_face(b.get_type(), Face::BOTTOM, texture_coords);
                }

                if(is_transparent(x, y + 1, z)){
                    for(int i = 0; i < 18; i+=3){
                        vertices.push_back(cube_vertex_top[i] + x + (cx * 16));
                        vertices.push_back(cube_vertex_top[i + 1] + y);
                        vertices.push_back(cube_vertex_top[i + 2] + z + (cz * 16));
                    }
                    
                    add_texture_face(b.get_type(), Face::TOP, texture_coords);
                }

                if(is_transparent(x, y, z - 1)){
                    for(int i = 0; i < 18; i+=3){
                        vertices.push_back(cube_vertex_back[i] + x + (cx * 16));
                        vertices.push_back(cube_vertex_back[i + 1] + y);
                        vertices.push_back(cube_vertex_back[i + 2] + z + (cz * 16));
                    }
                    
                    add_texture_face(b.get_type(), Face::BACK, texture_coords);
                }

                if(is_transparent(x, y, z + 1)){
                    for(int i = 0; i < 18; i+=3){
                        vertices.push_back(cube_vertex_front[i] + x + (cx * 16));
                        vertices.push_back(cube_vertex_front[i + 1] + y);
                        vertices.push_back(cube_vertex_front[i + 2] + z + (cz * 16));
                    }
                    
                    add_texture_face(b.get_type(), Face::FRONT, texture_coords);
                }
                
            }
        }
    }

    vertices_size = vertices.size();
    texture_size = texture_coords.size();

    vBuff = new GLfloat[vertices_size];
    tBuff = new GLfloat[texture_size];
    for(int i = 0; i < vertices_size; i++){
        vBuff[i] = vertices.at(i);
    }

    for(int i = 0; i < texture_size; i++){
        tBuff[i] = texture_coords.at(i);
    }
    vertices.clear();
    texture_coords.clear();

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices_size, vBuff, GL_STATIC_DRAW);

    glGenBuffers(1, &TBO);
    glBindBuffer(GL_ARRAY_BUFFER, TBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * texture_size, tBuff, GL_STATIC_DRAW);

    delete[] vBuff;
    delete[] tBuff;

}

void ChunkMesh::render(GLuint &texture){
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

    glDrawArrays(GL_TRIANGLES, 0, vertices_size / 3);
    glDisableVertexAttribArray(0);
}

ChunkMesh::~ChunkMesh(){
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &TBO);
    glDeleteVertexArrays(1, &VAO);
}