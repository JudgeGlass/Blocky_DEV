#include <renderer/hud.hpp>

HUD::HUD(std::shared_ptr<Player> player){
    this->player = player;
}



void HUD::render(double delta){
    drawDebug();
}

void HUD::drawDebug() {
    ImGui::Begin("Game Info:");
    ImGui::SetWindowSize(ImVec2(300, 200));
    ImGui::SetWindowPos(ImVec2(0, 0));
    ImGui::Text("Game Version: %s", VERSION);
    ImGui::Text("Pos[X/Y/Z]: %.02f / %.02f / %.02f", player->get_pos().x, player->get_pos().y, player->get_pos().z);
    ImGui::Text("Cam[yaw/pitch]: %.02f / %.02f", player->get_cam_pos().x, player->get_cam_pos().y);
    ImGui::Text("Show Polys: %s", (player->get_show_polygons()) ? "true" : "false");
    ImGui::Text("Block[type/light]: %d / %d", player->get_current_block().get_type(), player->get_current_block().get_light());
    //ImGui::GetWindowDrawList()->AddText(ImVec2(250, 250), ImColor(255, 255, 255, 255), "+");
    ImGui::End();
}

HUD::~HUD(){

}