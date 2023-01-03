#include <world/chunk.hpp>

#include <iostream>
#include <cstdlib>

Chunk::Chunk(const int cx, const int cz, const unsigned char cw, const unsigned char cl, const unsigned char ch){
    this->cx = cx;
    this->cz = cz;
    this->cw = cw;
    this->cl = cl;
    this->ch = ch;
}

Chunk::~Chunk(){
    delete chunk_mesh;
}

void Chunk::generate(){
    srand(time(NULL));
    std::cout << "Building terrain..." << std::endl;
    std::cout << "CX: " << cx << "\tCY: " << cz << "\tCW: " << cw << "\tCL: " << cl << "\tCH: " << ch << std::endl; 
    for(int x = 0; x < cw; x++){
        for(int y = 0; y < ch; y++){
            for(int z = 0; z < cl; z++){
                if(rand() % 10 == 0){
                    blocks.push_back(Block(x, y, z, 0));
                    continue;
                }

                blocks.push_back(Block(x, y, z, 1));
            }
        }
    }

    chunk_mesh = new ChunkMesh(blocks, cx, cz);

    chunk_mesh->build();
}


void Chunk::render(GLuint &texture){
    chunk_mesh->render(texture);
}