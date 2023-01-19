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


                if(y < 20 && y > 15 ) {
                    blocks[x + y * 16 + z * 16 * 256] = Block(x, y, z, ID::AIR, 1, false);
                    continue;
                }

                if(y <= l_start){
                    if(y == l_start)
                        blocks[x + y * 16 + z * 16 * 256] = Block(x, y, z, ID::GRASS, 1, false);
                    else if(y <= l_start - 1 && y >= l_start - 6)
                        blocks[x + y * 16 + z * 16 * 256] = Block(x, y, z, ID::DIRT, 1, false);
                    else
                        blocks[x + y * 16 + z * 16 * 256] = Block(x, y, z, ID::STONE, 1, false);
                }else{
                    blocks[x + y * 16 + z * 16 * 256] = Block(x, y, z, ID::AIR, 15, true);
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
    gen_lighting(this, world);
}

void Chunk::clear_lighting(){
    for(auto& b: blocks){
        if(!b.get_is_sky())
            b.set_light_level(1);
    }
}

Block* Chunk::get_block(unsigned char x, unsigned char y, unsigned char z)  {
    int i = x + y * 16 + z * 16 * 256;
    return &blocks[i];
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