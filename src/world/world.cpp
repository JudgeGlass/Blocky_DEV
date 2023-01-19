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

void World::render_transparent(GLuint &texture){
    for(auto& chunk: chunks){
        glm::vec2 p_pos = {player->get_pos().x, player->get_pos().z};
        glm::vec2 c_pos = glm::vec2(chunk->get_cx() * 16, chunk->get_cz() * 16);

        if(glm::distance(p_pos, c_pos) < 128){
            //chunk->render_transparent(texture);
        }
    }
}

void World::rebuild_chunks_around(int cx, int cz){
    std::vector<int> w_vec;

    get_chunk(cx, cz)->clear_lighting();
    w_vec.push_back(cx);
    w_vec.push_back(cz);

    if(cx + 1 < 16){
        get_chunk(cx + 1, cz)->clear_lighting();
        w_vec.push_back(cx + 1);
        w_vec.push_back(cz);
    }

    if(cx - 1 >= 0){
        get_chunk(cx - 1, cz)->clear_lighting();
        w_vec.push_back(cx - 1);
        w_vec.push_back(cz);
    }

    if(cz - 1 >= 0){
        get_chunk(cx, cz - 1)->clear_lighting();
        w_vec.push_back(cx);
        w_vec.push_back(cz - 1);
    }

    if(cz + 1 < 16){
        get_chunk(cx, cz + 1)->clear_lighting();
        w_vec.push_back(cx);
        w_vec.push_back(cz + 1);
    }

    for(int i = 0; i < w_vec.size(); i+=2){
        get_chunk(w_vec.at(i), w_vec.at(i+1))->build_lighting();
        //get_chunk(w_vec.at(i), w_vec.at(i+1))->rebuild_mesh();
    }

    for(int i = 0; i < w_vec.size(); i+=2){
        get_chunk(w_vec.at(i), w_vec.at(i+1))->rebuild_mesh();
    }

    w_vec.clear();
}

Chunk* World::get_chunk(int cx, int cz){
//    for(const auto& c: chunks){
//        if(c->get_cx() == cx && c->get_cz() == cz){
//            return c;
//        }
//    }

    int index = cz + cx * 16;

    if(index > 16 * 16) return nullptr;

    return chunks.at(index);
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