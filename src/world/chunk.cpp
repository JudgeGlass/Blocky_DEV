#include <world/chunk.hpp>

#include <iostream>
#include <cstdlib>

Chunk::Chunk(const int cx, const int cz, const unsigned char cw, const unsigned char cl, const unsigned char ch, World *world){
    this->cx = cx;
    this->cz = cz;
    this->cw = cw;
    this->cl = cl;
    this->ch = ch;
    this->world = world;
}

Chunk::~Chunk(){
    delete chunk_mesh;
}

void Chunk::generate(){
    srand(time(NULL));
    std::cout << "Building terrain..." << std::endl;
    std::cout << "CX: " << cx << "\tCY: " << cz << "\tCW: " << cw << "\tCL: " << cl << "\tCH: " << std::to_string(ch) << std::endl; 
    for(int x = 0; x < cw+1; x++){       
        for(int y = 0; y < ch+1; y++){
            for(int z = 0; z < cl+1; z++){
                float n = abs(SimplexNoise::noise((float)(x+cx*cw + ((float)rand() / (RAND_MAX))) / 80, (float)(z+cz*cl + ((float)rand() / (RAND_MAX))) / 80) * 12);
                int l_start = (int)n+ 120;
                //std::cout << "N: " << n << std::endl;


                if(y < 20 && y > 15 && x < 11 && x > 8){
                    blocks[x + y * 16 + z * 16 * 256] = Block(x, y, z, ID::AIR, 1.0f, false);
                    continue;
                }

                if(y <= l_start){
                    if(y == l_start)
                        blocks[x + y * 16 + z * 16 * 256] = Block(x, y, z, ID::GRASS, 1.0f, false);
                    else if(y <= l_start - 1 && y >= l_start - 6)
                        blocks[x + y * 16 + z * 16 * 256] = Block(x, y, z, ID::DIRT, 1.0f, false);
                    else
                        blocks[x + y * 16 + z * 16 * 256] = Block(x, y, z, ID::STONE, 1.0f, false);
                }else{
                    blocks[x + y * 16 + z * 16 * 256] = Block(x, y, z, ID::AIR, 15.0f, true);
                }
                // if(y > 60){
                //     //blocks.push_back(Block(x, y, z, ID::AIR));
                //     blocks[x + y * 16 + z * 16 * 256] = Block(x, y, z, ID::AIR);
                // }else if(y == 60){
                //     //blocks.push_back(Block(x, y, z, ID::GRASS));
                //     blocks[x + y * 16 + z * 16 * 256] = Block(x, y, z, ID::GRASS);
                // }else if(y > 55){
                //     //blocks.push_back(Block(x, y, z, ID::DIRT));
                //     blocks[x + y * 16 + z * 16 * 256] = Block(x, y, z, ID::DIRT);
                // }else{
                //     //blocks.push_back(Block(x, y, z, ID::STONE));
                //     blocks[x + y * 16 + z * 16 * 256] = Block(x, y, z, ID::STONE);
                // }
            }
        }
    }

    chunk_mesh = new ChunkMesh(blocks, cx, cz, cw, cl, ch, disable_faces, world);
    
    //chunk_mesh->build();
}

void Chunk::build_mesh(){
    chunk_mesh->build();
}

void Chunk::rebuild_mesh(){
    chunk_mesh->rebuild(blocks);
}

void Chunk::build_lighting(){

    std::queue<LightNode> lightQueue;

    for(int y = 255; y >= 0; y--){
        for(int x = 0; x < 16; x++){
            for(int z = 0; z < 16; z++){
                Block b = get_block(x, y, z);

                if(b.get_is_sky()){
                    lightQueue.emplace(x, y, z, this);
                }
            }
        }
    }

    while(lightQueue.empty() == false){
        LightNode &node = lightQueue.front();

        Chunk *chunk = node.chunk;

        lightQueue.pop();

        int x = node.x;

        int y = node.y;

        int z = node.z;

        int light = chunk->get_block(x, y, z).get_light();

        Block *b_left = nullptr;
        Block *b_right = nullptr;
        Block *b_top = nullptr;
        Block *b_bottom = nullptr;
        Block *b_front = nullptr;
        Block *b_back = nullptr;

        if(x - 1 >= 0) b_left = &chunk->get_block(x - 1, y, z);
        else{
            if(cx - 1 >= 0){
                b_left = &world->get_chunk(cx - 1, cz)->get_block(15, y, z);
            }
        }

        if(x + 1 < 16) b_right = &chunk->get_block(x + 1, y, z);
        else{
            if(cx + 1 < 16){
                b_right = &world->get_chunk(cx + 1, cz)->get_block(0, y, z);
            }
        }

        if(z + 1 < 16) b_front = &chunk->get_block(x, y, z + 1);
        else{
            if(cz + 1 < 16){
                b_front = &world->get_chunk(cx, cz + 1)->get_block(x, y, 0);
            }
        }

        if(z - 1 >= 0) b_back = &chunk->get_block(x, y, z - 1);
        else{
            if(cz - 1 >= 0){
                b_back = &world->get_chunk(cx, cz - 1)->get_block(x, y, 15);
            }
        }

        if(y - 1 >= 0){
            b_bottom = &chunk->get_block(x, y - 1, z);
        }
        if(y + 1 < 256){
            b_bottom = &chunk->get_block(x, y + 1, z);
        }

        //std::cout << "X: " << x << "\tY: " << y << "\tZ: " << z << "\tCX: " << chunk->get_cx() << "\tCZ: " << chunk->get_cz() << "\tL: " << light << std::endl;


        //std::cout << "LEFT" << std::endl;
        if(b_left != nullptr){
            if(b_left->get_type() != ID::AIR && b_left->get_light() + 2 <= light){
                
                b_left->set_light_level(light - 1);

                short index = (x - 1) + y * 16 + z * 16 * 256;
                if(x - 1 < 0){
                    chunk = world->get_chunk(cx - 1, cz);
                }

                lightQueue.emplace(x - 1, y, z, chunk);
            }
        }     


        //std::cout << "RIGHT" << std::endl;
        if(b_right != nullptr){
            if(b_right->get_type() != ID::AIR && b_right->get_light() + 2 <= light){
                b_right->set_light_level(light - 1);

                short index = (x + 1) + y * 16 + z * 16 * 256;
                if(x + 1 > 15){
                    chunk = world->get_chunk(cx + 1, cz);
                }

                lightQueue.emplace(x + 1, y, z, chunk);
            }
        }  


        //std::cout << "FRONT" << std::endl;
        if(b_front != nullptr){
            if(b_front->get_type() != ID::AIR && b_front->get_light() + 2 <= light){
                b_front->set_light_level(light - 1);

                short index = x + y * 16 + (z + 1) * 16 * 256;
                if(z + 1 > 15){
                    chunk = world->get_chunk(cx, cz + 1);
                }

                lightQueue.emplace(x, y, z + 1, chunk);
            }
        }   


        //std::cout << "BACK" << std::endl;
        if(b_back != nullptr){
            if(b_back->get_type() != ID::AIR && b_back->get_light() + 2 <= light){
                b_back->set_light_level(light - 1);

                short index = x + y * 16 + (z - 1) * 16 * 256;
                if(z - 1 < 0){
                    chunk = world->get_chunk(cx, cz - 1);
                }

                lightQueue.emplace(x, y, z - 1, chunk);
            }
        }   


        //std::cout << "TOP" << std::endl;
        if(b_top != nullptr){
            if(b_top->get_type() != ID::AIR && b_top->get_light() + 2 <= light){
                b_top->set_light_level(light - 1);

                short index = x + (y + 1) * 16 + z * 16 * 256;

                lightQueue.emplace(x, y + 1, z, chunk);
            }
        }


        //std::cout << "BOTTOM" << std::endl;
        if(b_bottom != nullptr){
            if(b_bottom->get_type() != ID::AIR && b_bottom->get_light() + 2 <= light){
                b_bottom->set_light_level(light - 1);

                short index = x + (y - 1) * 16 + z * 16 * 256;

                lightQueue.emplace(x, y - 1, z, chunk);
            }
        }



        //if(chunk->get_block(x).get_type() != ID::AIR && chunk->)
    }
}

Block& Chunk::get_block(unsigned char x, unsigned char y, unsigned char z)  {
    int i = x + y * 16 + z * 16 * 256;
    return blocks[i];
}

int Chunk::get_cx() const {
    return cx;
}
int Chunk::get_cz() const {
    return cz;
}

void Chunk::set_disable_faces(bool v){
    disable_faces = v;
}

void Chunk::set_block(Block b){
    //blocks.at(x + y * 15 + z * 16 * 256).set_type(id);
    blocks[b.get_x() + b.get_y() * 16 + b.get_z() * 16 * 256] = b;
    //chunk_mesh->build();
}


void Chunk::render(GLuint texture){
    chunk_mesh->render(texture);
}

void Chunk::render_transparent(GLuint texture){
    chunk_mesh->render_transparent(texture);
}