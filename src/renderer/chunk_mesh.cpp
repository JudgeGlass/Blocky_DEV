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
    light_levels.clear();
    for(int x = 0; x < cw + 1; x++){
        for(int y = 0; y< ch + 1; y++){
            for(int z = 0; z < cl + 1; z++){
                Block b = blocks[x + y * (cl + 1) + z * (cw + 1) * (ch + 1)]; //blocks.at(x + 16 * (y + 16 * z));
                //if(b.get_type() == 0) continue;

                float light = b.get_light() / 15.0f;
                float lightL = 1.0f, lightR = 1.0f, lightT = 1.0f, lightB = 1.0f, lightF = 1.0f, lightRR = 1.0f;
                if(x - 1 > 0){
                    if(blocks[(x - 1) + y * (cl + 1) + z * (cw + 1) * (ch + 1)].get_type() == ID::AIR)
                        lightL = blocks[(x - 1) + y * (cl + 1) + z * (cw + 1) * (ch + 1)].get_light();
                }else{
                    if(cx - 1 >= 0) lightL = world->get_chunk(cx - 1, cz)->get_block(15, y, z).get_light();
                }

                if(x + 1 < 16){
                    if(blocks[(x + 1) + y * (cl + 1) + z * (cw + 1) * (ch + 1)].get_type() == ID::AIR)
                        lightR = blocks[(x + 1) + y * (cl + 1) + z * (cw + 1) * (ch + 1)].get_light();
                }else{
                    if(cx + 1 < 16) lightR = world->get_chunk(cx + 1, cz)->get_block(0, y, z).get_light();
                }

                if(z - 1 > 0){
                    if(blocks[x + y * (cl + 1) + (z - 1) * (cw + 1) * (ch + 1)].get_type() == ID::AIR){
                        lightRR = blocks[x + y * (cl + 1) + (z - 1) * (cw + 1) * (ch + 1)].get_light();
                    }
                }else{
                    if(cz - 1 >= 0) lightRR = world->get_chunk(cx, cz - 1)->get_block(x, y, 15).get_light();
                }

                if(z + 1 < 16){
                    if(blocks[x + y * (cl + 1) + (z + 1) * (cw + 1) * (ch + 1)].get_type() == ID::AIR){
                        lightF = blocks[x + y * (cl + 1) + (z + 1) * (cw + 1) * (ch + 1)].get_light();
                    }
                }else{
                    if(cz + 1 < 16) lightF = world->get_chunk(cx, cz + 1)->get_block(x, y, 0).get_light();
                }

                if(y - 1 > 0){
                    if(blocks[x + (y - 1) * (cl + 1) + z * (cw + 1) * (ch + 1)].get_type() == ID::AIR)
                        lightB = blocks[x + (y - 1) * (cl + 1) + z * (cw + 1) * (ch + 1)].get_light();
                } 
                if(y + 1 < 256){
                    if(blocks[x + (y + 1) * (cl + 1) + z * (cw + 1) * (ch + 1)].get_type() == ID::AIR)
                        lightT = blocks[x + (y + 1) * (cl + 1) + z * (cw + 1) * (ch + 1)].get_light();
                } 

                lightL /= 15.0f;
                lightR /= 15.0f;
                lightT /= 15.0f;
                lightB /= 15.0f;
                lightF /= 15.0f;
                lightRR /= 15.0f;


                //std::cout << "LL: " << lightL << "\tLR: " << lightR << "\tLT: " << lightT << "\tLB: " << lightB << "\tLF: " << lightF << "\tLRR: " << lightRR << std::endl;
                

                // float lightL = light + 0.02f;
                // float lightR = light + 0.02f;
                // float lightT = light + 0.04f;
                // float lightB = light + 0.01f;
                // float lightF = light + 0.025f;
                // float lightRR = light + 0.025f;
                
                
                

                if(is_transparent(x - 1, y, z, b.get_type())){
                    if(b.get_type() != ID::AIR){
                        for(int i = 0; i < 18; i+=3){
                            vertices.push_back(cube_vertex_left[i] + x + (cx * 16));
                            vertices.push_back(cube_vertex_left[i + 1] + y);
                            vertices.push_back(cube_vertex_left[i + 2] + z + (cz * 16));
                            light_levels.push_back(lightL + 0.02f);
                        }
                        
                        add_texture_face(b.get_type(), Face::LEFT, texture_coords);
                    }
                }

                if(is_transparent(x + 1, y, z, b.get_type())){
                    if(b.get_type() != ID::AIR){
                        for(int i = 0; i < 18; i+=3){
                            vertices.push_back(cube_vertex_right[i] + x + (cx * 16));
                            vertices.push_back(cube_vertex_right[i + 1] + y);
                            vertices.push_back(cube_vertex_right[i + 2] + z + (cz * 16));
                            light_levels.push_back(lightR + 0.02f);
                        }
                        
                        add_texture_face(b.get_type(), Face::RIGHT, texture_coords);
                    }
                }

                if(is_transparent(x, y - 1, z, b.get_type())){
                    if(b.get_type() != ID::AIR){
                        for(int i = 0; i < 18; i+=3){
                            vertices.push_back(cube_vertex_bottom[i] + x + (cx * 16));
                            vertices.push_back(cube_vertex_bottom[i + 1] + y);
                            vertices.push_back(cube_vertex_bottom[i + 2] + z + (cz * 16));
                            light_levels.push_back(lightB + 0.01f);
                        }
                        
                        add_texture_face(b.get_type(), Face::BOTTOM, texture_coords);
                    }
                }

                if(is_transparent(x, y + 1, z, b.get_type())){
                    if(b.get_type() != ID::AIR){
                        for(int i = 0; i < 18; i+=3){
                            vertices.push_back(cube_vertex_top[i] + x + (cx * 16));
                            vertices.push_back(cube_vertex_top[i + 1] + y);
                            vertices.push_back(cube_vertex_top[i + 2] + z + (cz * 16));
                            light_levels.push_back(lightT + 0.04f);
                        }
                        
                        add_texture_face(b.get_type(), Face::TOP, texture_coords);
                    }
                }

                if(is_transparent(x, y, z - 1, b.get_type())){
                    if(b.get_type() != ID::AIR){
                        for(int i = 0; i < 18; i+=3){
                            vertices.push_back(cube_vertex_back[i] + x + (cx * 16));
                            vertices.push_back(cube_vertex_back[i + 1] + y);
                            vertices.push_back(cube_vertex_back[i + 2] + z + (cz * 16));
                            light_levels.push_back(lightRR + 0.025f);
                        }
                        
                        add_texture_face(b.get_type(), Face::BACK, texture_coords);
                    }                  
                }

                if(is_transparent(x, y, z + 1, b.get_type())){
                    if(b.get_type() != ID::AIR){
                        for(int i = 0; i < 18; i+=3){
                            vertices.push_back(cube_vertex_front[i] + x + (cx * 16));
                            vertices.push_back(cube_vertex_front[i + 1] + y);
                            vertices.push_back(cube_vertex_front[i + 2] + z + (cz * 16));
                            light_levels.push_back(lightF + 0.025f);
                        }
                        
                        add_texture_face(b.get_type(), Face::FRONT, texture_coords);
                    }
                }
                
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

    glBindBuffer(GL_ARRAY_BUFFER, TVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * tvertices_size, tvBuff, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, TTBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * ttexture_size, ttBuff, GL_STATIC_DRAW);


    glBindVertexArray(0);
    

    delete[] vBuff;
    delete[] tBuff;
    delete[] tvBuff;
    delete[] ttBuff;
    delete[] lBuff;

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

void ChunkMesh::render_transparent(GLuint texture){
    glBindVertexArray(VAO);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_ALPHA_TEST);

    glEnableVertexAttribArray(0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(texture, 0);

    // Vertex data
    glBindBuffer(GL_ARRAY_BUFFER, TVBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);

    // Texture data
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, TTBO);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void *) 0);


    glDrawArrays(GL_TRIANGLES, 0, tvertices_size / 3);
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