#include <world/world.hpp>

World::World(int width, int depth){
    this->width = width;
    this->depth = depth;

    player = new Player(glm::vec3(0, 65, 0), this);
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
        c->build_lighting();
        c->build_mesh();
    }
}

void World::render(GLuint &texture){
    for(auto& chunk: chunks){
        glm::vec2 p_pos = {player->get_pos().x, player->get_pos().z};
        glm::vec2 c_pos = glm::vec2(chunk->get_cx() * 16, chunk->get_cz() * 16);

        if(glm::distance(p_pos, c_pos) < 128){
            chunk->render(texture);
        }
    }
}

void World::rander_transparent(GLuint &texture){
    for(auto& chunk: chunks){
        glm::vec2 p_pos = {player->get_pos().x, player->get_pos().z};
        glm::vec2 c_pos = glm::vec2(chunk->get_cx() * 16, chunk->get_cz() * 16);

        if(glm::distance(p_pos, c_pos) < 128){
            //chunk->render_transparent(texture);
        }
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