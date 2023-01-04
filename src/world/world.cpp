#include <world/world.hpp>

World::World(int width, int depth){
    this->width = width;
    this->depth = depth;

    player = new Player(glm::vec3(0, 65, 20));
}

void World::generate(){
    for(int cx = 0; cx < width; cx++){
        for(int cz = 0; cz < depth; cz++){
            Chunk *c = new Chunk(cx, cz, 15, 15, 255, this);
            c->generate();
            chunks.push_back(c);
        }
    }

    for(const auto& c: chunks){
        c->buil_mesh();
    }
}

void World::render(GLuint &texture){
    for(auto& chunk: chunks){
        chunk->render(texture);
    }
}

Chunk* World::get_chunk(int cx, int cz){
    for(const auto& c: chunks){
        if(c->get_cx() == cx && c->get_cz() == cz){
            return c;
        }
    }

    return nullptr;
}

std::vector<Chunk*> World::get_chunks(){
    return chunks;
}

Player* World::get_player(){
    return player;
}

World::~World(){
    delete player;
    for(auto& chunk: chunks){
        delete chunk;
    }

    chunks.clear();
}