#include <world/chunk.hpp>

#include <iostream>

Chunk::Chunk(const int cx, const int cy, const unsigned char cw, const unsigned char cl, const unsigned char ch){
    this->cx = cx;
    this->cy = cy;
    this->cw = cw;
    this->cl = cl;
    this->ch = ch;
}

Chunk::~Chunk(){
    delete chunk_mesh;
}

void Chunk::generate(){
    std::cout << "Building terrain..." << std::endl;
    std::cout << "CX: " << cx << "\tCY: " << cy << "\tCW: " << cw << "\tCL: " << cl << "\tCH: " << ch << std::endl; 
    for(int x = 0; x < cw; x++){
        for(int y = 0; y < ch; y++){
            for(int z = 0; z < cl; z++){
                blocks.push_back(Block(x, y, z, 1));
                std::cout << "B: " << x + y + z << std::endl;
            }
        }
    }

    chunk_mesh = new ChunkMesh(blocks);

    chunk_mesh->build();
}


void Chunk::render(GLuint &texture){
    chunk_mesh->render(texture);
}