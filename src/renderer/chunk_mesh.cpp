#include <renderer/chunk_mesh.hpp>
#include <iostream>

ChunkMesh::ChunkMesh(const std::vector<Block> &blocks){
    this->blocks = blocks;
}

void ChunkMesh::build(){
    for(const auto &block: blocks){
        for(int i = 0; i < 108; i+=3){
            vertices.push_back(vertex_buffer[i] + (float) block.get_x());
            vertices.push_back(vertex_buffer[i + 1] + (float) block.get_y());
            vertices.push_back(vertex_buffer[i + 2] + (float )block.get_z());
        }

        for(int i = 0; i < 72; i++){
            texture_coords.push_back(texture_buffer[i]);
        }
    }

    vertices_size = vertices.size();
    texture_size = texture_coords.size();

    vBuff = new GLfloat[vertices_size];
    tBuff = new GLfloat[texture_size];
    for(int i = 0; i < vertices_size; i++){
        vBuff[i] = vertices.at(i);
        //std::cout << "T: " << tBuff[i] << "\tI: " << i << std::endl;
    }

    for(int i = 0; i < texture_size; i++){
        tBuff[i] = texture_coords.at(i);
    }
    vertices.clear();
    texture_coords.clear();

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices_size, vBuff, GL_STATIC_DRAW);

    glGenBuffers(1, &TBO);
    glBindBuffer(GL_ARRAY_BUFFER, TBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * texture_size, tBuff, GL_STATIC_DRAW);

    delete[] vBuff;
    delete[] tBuff;

}

void ChunkMesh::render(GLuint &texture){
    glEnableVertexAttribArray(0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(texture, 0);

    // Vertex data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);

    // Texture data
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, TBO);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void *) 0);

    glDrawArrays(GL_TRIANGLES, 0, vertices_size / 3);
    glDisableVertexAttribArray(0);
}