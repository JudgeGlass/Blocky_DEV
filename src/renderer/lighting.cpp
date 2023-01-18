#include <renderer/lighting.hpp>

void gen_lighting(Chunk *c, World *world){
    std::queue<LightNode> lightQueue;

    for(int y = 255; y >= 0; y--){
        for(int x = 0; x < 16; x++){
            for(int z = 0; z < 16; z++){
                Block *b = c->get_block(x, y, z);

                if(b->get_is_sky()){
                    //std::cout << "ADDING:\tX: " << x << "\tY: " << y << "\tZ: " << z << std::endl;
                    lightQueue.emplace(x, y, z, c);
                }

//                if(!b->get_is_sky()){
//                    b->set_light_level(1.0f);
//                }
            }
        }
    }

    while(lightQueue.empty() == false){
        //std::cout << "Light Queue Size; " << lightQueue.size() << std::endl;
        LightNode &node = lightQueue.front();

        Chunk *chunk = node.chunk;

        unsigned char x = node.x;

        unsigned char y = node.y;

        unsigned char z = node.z;

        //std::cout << "X: " << std::to_string((int)x) << "\tY: " << std::to_string(y) << "\tZ: " << std::to_string(z) << "\tCX: " << chunk->get_cx() << "\tCZ: " << chunk->get_cz() << std::endl;

        lightQueue.pop();

        if(x < 0 || y < 0 || z < 0) continue;

        float light = chunk->get_block(x, y, z)->get_light();

        Block *b_left = nullptr;
        Block *b_right = nullptr;
        Block *b_top = nullptr;
        Block *b_bottom = nullptr;
        Block *b_front = nullptr;
        Block *b_back = nullptr;

        int cx = chunk->get_cx();
        int cz = chunk->get_cz();

        if(x - 1 >= 0) b_left = chunk->get_block(x - 1, y, z);
        else{
            if(cx - 1 >= 0){
                b_left = world->get_chunk(cx - 1, cz)->get_block(15, y, z);
            }
        }

        if(x + 1 < 16) b_right = chunk->get_block(x + 1, y, z);
        else{
            if(cx + 1 < 16){
                b_right = world->get_chunk(cx + 1, cz)->get_block(0, y, z);
            }
        }

        if(z + 1 < 16) b_front = chunk->get_block(x, y, z + 1);
        else{
            if(cz + 1 < 16){
                b_front = world->get_chunk(cx, cz + 1)->get_block(x, y, 0);
            }
        }

        if(z - 1 >= 0) b_back = chunk->get_block(x, y, z - 1);
        else{
            if(cz - 1 >= 0){
                b_back = world->get_chunk(cx, cz - 1)->get_block(x, y, 15);
            }
        }

        if(y - 1 >= 0){
            b_bottom = chunk->get_block(x, y - 1, z);
        }
        if(y + 1 < 255){
            b_top = chunk->get_block(x, y + 1, z);
        }

        if(b_left != nullptr){
            if(b_left->get_type() == ID::AIR && b_left->get_light() + 2 <= light){

                b_left->set_light_level(light - 1);

                if(x - 1 < 0){
                    lightQueue.emplace(15, y, z, world->get_chunk(cx - 1, cz));
                }else {
                    lightQueue.emplace(x - 1, y, z, chunk);
                }
            }
        }

        if(b_right != nullptr){
            if(b_right->get_type() == ID::AIR && b_right->get_light() + 2 <= light){
                b_right->set_light_level(light - 1);

                if(x + 1 > 15){
                    lightQueue.emplace(0, y, z, world->get_chunk(cx + 1, cz));
                }else {
                    lightQueue.emplace(x + 1, y, z, chunk);
                }
            }
        }

        if(b_front != nullptr){
            if(b_front->get_type() == ID::AIR && b_front->get_light() + 2 <= light){
                b_front->set_light_level(light - 1);

                if(z + 1 > 15){
                    lightQueue.emplace(x, y, 0, world->get_chunk(cx, cz + 1));
                }else {
                    lightQueue.emplace(x, y, z + 1, chunk);
                }
            }
        }

        if(b_back != nullptr){
            if(b_back->get_type() == ID::AIR && b_back->get_light() + 2 <= light){
                b_back->set_light_level(light - 1);

                if(z - 1 < 0){
                    lightQueue.emplace(x, y, 15, world->get_chunk(cx, cz - 1));
                }else {
                    lightQueue.emplace(x, y, z - 1, chunk);
                }
            }
        }

        if(b_top != nullptr){
            if(b_top->get_type() == ID::AIR && b_top->get_light() + 2 <= light){
                b_top->set_light_level(light - 1);

                lightQueue.emplace(x, y + 1, z, chunk);
            }
        }

        if(b_bottom != nullptr) {
            if (b_bottom->get_type() == ID::AIR && b_bottom->get_light() + 2 <= light) {
                b_bottom->set_light_level(light - 1);

                lightQueue.emplace(x, y - 1, z, chunk);
            }
        }
    }

    std::cout << "LIGHT DONE!" << std::endl;
}