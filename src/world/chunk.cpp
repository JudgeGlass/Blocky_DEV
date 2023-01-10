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

    for(auto &b: blocks){
        if(b.get_type() == ID::AIR && !b.get_is_sky()) {
            b.set_light_level(0.0f);
        }
    }

    for(int y = 255; y > -1; y--){
        for(int z = 0; z < cl+1; z++){
            for(int x = 0; x < cw+1; x++){
                Block b = get_block(x, y, z);
                

                if(b.get_type() == ID::AIR && b.get_is_sky()) continue;

                

                float left = 0.0f, right = 0.0f, front = 0.0f, back = 0.0f, top = 0.0f, bottom = 0.0f;
                if(x - 1 >= 0){
                    Block b_left = get_block(x - 1, y, z);
                    if(b_left.get_type() == ID::AIR){
                        left = b_left.get_light();
                    }else{
                        left = 0;
                    }
                }else{
                    if(cx - 1 < 0) left = 0;
                    else{
                        Block b_left = world->get_chunk(cx - 1, cz)->get_block(15, y, z);
                        if(b_left.get_type() == ID::AIR){
                            left = b_left.get_light();
                        }else{
                            left = 0;
                        }
                    }
                }

                if(x + 1 < 16){
                    Block b_right = get_block(x + 1, y, z);
                    if(b_right.get_type() == ID::AIR){
                        right = b_right.get_light();
                    }
                }else{
                    if(cx + 1 > 15) right = 0;
                    else{
                        Block b_right = world->get_chunk(cx + 1, cz)->get_block(0, y, z);
                        if(b_right.get_type() == ID::AIR){
                            right = b_right.get_light();
                        }else{
                            right = 0;
                        }
                    }
                }

                if(z - 1 >= 0){
                    Block b_front = get_block(x, y, z - 1);
                    if(b_front.get_type() == ID::AIR){
                        front = b_front.get_light();
                    }else{
                        front = 0;
                    }
                }else{
                    if(cz - 1 < 0) front = 0;
                    else{
                        Block b_front = world->get_chunk(cx, cz - 1)->get_block(x, y, 15);
                        if(b_front.get_type() == ID::AIR){
                            front = b_front.get_light();
                        }else{
                            front = 0;
                        }
                    }
                }

                if(z + 1 < 16){
                    Block b_back = get_block(x, y, z + 1);
                    if(b_back.get_type() == ID::AIR){
                        back = b_back.get_light();
                    }else{
                        back = 0;
                    }
                }else{
                    if(cz + 1 > 15) back = 0;
                    else{
                        Block b_back = world->get_chunk(cx, cz + 1)->get_block(x, y, 0);
                        if(b_back.get_type() == ID::AIR){
                            back = b_back.get_light();
                        }else{
                            back = 0;
                        }
                    }
                }

                if(y - 1 >= 0){
                    Block b_bottom = get_block(x, y - 1, z);
                    if(b_bottom.get_type() == ID::AIR){
                        bottom = b_bottom.get_light();
                    }else{
                        bottom = 0;
                    }
                }else{
                    bottom = 0;
                }

                if(y + 1 < 256){
                    Block b_top = get_block(x, y + 1, z);
                    if(b_top.get_type() == ID::AIR){
                        top = b_top.get_light();
                    }else{
                        top = 0;
                    }
                }else{
                    top = 0;
                }

                float levels[6];
                levels[0] = left;
                levels[1] = right;
                levels[2] = front;
                levels[3] = back;
                levels[4] = top;
                levels[5] = bottom;


                float max = levels[0];
                bool has_zero = false;
                for(int i = 0; i < 6; i++){
                    if(levels[i] == 0.0f) has_zero = true;
                    if(levels[i] > max) max = levels[i];
                }

                if(has_zero)
                    if(max - 1 <= 0.0) max = 1.0f;
                //std::cout << "MAX: " << max << std::endl;
                

                b.set_light_level(max - 1);
                blocks[x + y * 16 + z * 16 * 256] = b;
            }
        }
    }
}

const Block& Chunk::get_block(unsigned char x, unsigned char y, unsigned char z)  {
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