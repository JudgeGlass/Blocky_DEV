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
                if(y > 60){
                    //blocks.push_back(Block(x, y, z, ID::AIR));
                    blocks[x + y * 16 + z * 16 * 256] = Block(x, y, z, ID::AIR);
                }else if(y == 60){
                    //blocks.push_back(Block(x, y, z, ID::GRASS));
                    blocks[x + y * 16 + z * 16 * 256] = Block(x, y, z, ID::GRASS);
                }else if(y > 55){
                    //blocks.push_back(Block(x, y, z, ID::DIRT));
                    blocks[x + y * 16 + z * 16 * 256] = Block(x, y, z, ID::DIRT);
                }else{
                    //blocks.push_back(Block(x, y, z, ID::STONE));
                    blocks[x + y * 16 + z * 16 * 256] = Block(x, y, z, ID::STONE);
                }
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
    std::cout << "NEW BLOCK: " << std::to_string(blocks[12 + 60 * 16 + 12 * 16 * 256].get_type()) << "\tCX: " << cx << "\tCZ: " << cz << std::endl;
    chunk_mesh->rebuild(blocks);
}

Block Chunk::get_block(unsigned char x, unsigned char y, unsigned char z) const {
    //std::cout << "GET_BLOCK(): X: " << std::to_string(x) << "\tY: " << std::to_string(y) << "\tZ: " << std::to_string(z) << "\tT: " << (x + y + z) << std::endl;
    //return blocks.at(x + y * 16 + z * 16 * 256);
    return blocks[x + y * (cw+1) + z * (cl + 1) * (ch + 1)];
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

void Chunk::set_block(unsigned char x, unsigned char y, unsigned char z, unsigned char id){
    //blocks.at(x + y * 15 + z * 16 * 256).set_type(id);
    blocks[x + y * 16 + z * 16 * 256].set_type(id);
    //chunk_mesh->build();
}


void Chunk::render(GLuint texture){
    chunk_mesh->render(texture);
}