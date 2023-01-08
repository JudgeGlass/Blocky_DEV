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
}

bool ChunkMesh::is_transparent(int x, int y, int z, unsigned char block_id){
    //std::cout << "DISABLE FACE: " << disable_faces << std::endl;
    if(y < 0 || y > ch || !disable_faces) return 1; // || x < 0 || x > 15 || z < 0 || z > 15
    Block b;
    if(x < 0){
        if(cx - 1 >= 0){
            b = world->get_chunk(cx - 1, cz)->get_block(15, y, z);
        }else{
            return 1;
        }
    }else if(x > cw){
        if(cx + 1 < 16){
            b = world->get_chunk(cx + 1, cz)->get_block(0, y, z);
        }else{
            return 1;
        }
    }else if(z < 0){
        if(cz - 1 >= 0){
            b = world->get_chunk(cx, cz - 1)->get_block(x, y, 15);
        }else{
            return 1;
        }
    }else if(z > cl){
        if(cz + 1 < 16){
            b = world->get_chunk(cx, cz + 1)->get_block(x, y, 0);
        }else{
            return 1;
        }
    }else{
        //b = blocks.at(x + y * 16 + z * 16 * 256);
        b = blocks[x + y * (cl + 1) + z * (cw + 1) * (ch + 1)];
    }

    
    

    if(b.get_type() == ID::GLASS && block_id == ID::GLASS) return 0; 

    switch (b.get_type())
    {
    case ID::AIR:
    case ID::GLASS:
        return 1;
    
    default:
        return 0;
    }
}

void ChunkMesh::build(){
    for(int x = 0; x < cw + 1; x++){
        for(int y = 0; y< ch + 1; y++){
            for(int z = 0; z < cl + 1; z++){
                Block b = blocks[x + y * (cl + 1) + z * (cw + 1) * (ch + 1)]; //blocks.at(x + 16 * (y + 16 * z));


                if(y == 60){
                    //std::cout << "BLOCK: " << std::to_string(b.get_type()) << std::endl;
                }
                
                if(b.get_type() == 0) continue;

                if(is_transparent(x - 1, y, z, b.get_type())){
                    for(int i = 0; i < 18; i+=3){
                        vertices.push_back(cube_vertex_left[i] + x + (cx * 16));
                        vertices.push_back(cube_vertex_left[i + 1] + y);
                        vertices.push_back(cube_vertex_left[i + 2] + z + (cz * 16));
                    }
                    
                    add_texture_face(b.get_type(), Face::LEFT, texture_coords);
                }

                if(is_transparent(x + 1, y, z, b.get_type())){
                    for(int i = 0; i < 18; i+=3){
                        vertices.push_back(cube_vertex_right[i] + x + (cx * 16));
                        vertices.push_back(cube_vertex_right[i + 1] + y);
                        vertices.push_back(cube_vertex_right[i + 2] + z + (cz * 16));
                    }
                    
                    add_texture_face(b.get_type(), Face::RIGHT, texture_coords);
                }

                if(is_transparent(x, y - 1, z, b.get_type())){
                    for(int i = 0; i < 18; i+=3){
                        vertices.push_back(cube_vertex_bottom[i] + x + (cx * 16));
                        vertices.push_back(cube_vertex_bottom[i + 1] + y);
                        vertices.push_back(cube_vertex_bottom[i + 2] + z + (cz * 16));
                    }
                    
                    add_texture_face(b.get_type(), Face::BOTTOM, texture_coords);
                }

                if(is_transparent(x, y + 1, z, b.get_type())){
                    for(int i = 0; i < 18; i+=3){
                        vertices.push_back(cube_vertex_top[i] + x + (cx * 16));
                        vertices.push_back(cube_vertex_top[i + 1] + y);
                        vertices.push_back(cube_vertex_top[i + 2] + z + (cz * 16));
                    }
                    
                    add_texture_face(b.get_type(), Face::TOP, texture_coords);
                }

                if(is_transparent(x, y, z - 1, b.get_type())){
                    for(int i = 0; i < 18; i+=3){
                        vertices.push_back(cube_vertex_back[i] + x + (cx * 16));
                        vertices.push_back(cube_vertex_back[i + 1] + y);
                        vertices.push_back(cube_vertex_back[i + 2] + z + (cz * 16));
                    }
                    
                    add_texture_face(b.get_type(), Face::BACK, texture_coords);
                }

                if(is_transparent(x, y, z + 1, b.get_type())){
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

    // glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices_size, vBuff, GL_STATIC_DRAW);

    //glGenBuffers(1, &TBO);
    glBindBuffer(GL_ARRAY_BUFFER, TBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * texture_size, tBuff, GL_STATIC_DRAW);

    //glBindVertexArray(0);
    //glBindBuffer(GL_ARRAY_BUFFER, 0);

    delete[] vBuff;
    delete[] tBuff;

}

void ChunkMesh::rebuild(Block *blocks){
    this->blocks = blocks;   

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