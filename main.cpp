#include <fstream>
#include <iostream>
#include <vector>
#include "json.hpp"

struct block_state {
    int id;
    int data;
    int runtime_id;
};

int main(int argc, const char * argv[]) {
    std::ifstream block_ids("blockids_map.json");
    std::ifstream palette("palette.json");
    
    auto block_ids_json = nlohmann::json::object();
    block_ids >> block_ids_json;
    auto palette_json = nlohmann::json::object();
    palette >> palette_json;
    
    int current_id = INT_MIN;
    int last_data = INT_MIN;
    int runtime_id = 0;
    
    std::vector<block_state> blocks = {};
    for (auto &block : palette_json["blocks"].items()) {
        struct block_state state;
        if(block_ids_json.contains(block.value()["name"])) {
            state.id = block_ids_json.find(block.value()["name"]).value();
        } else {
            state.id = -1;
        }
        if(state.id != current_id) {
            current_id = state.id;
            last_data = -1;
        }
        state.data = ++last_data;
        state.runtime_id = runtime_id++;
        blocks.push_back(state);
    }
    
    nlohmann::json j;
    int i = 0;
    for(block_state block : blocks) {
        j[i]["id"] = block.id;
        j[i]["data"] = block.data;
        j[i]["runtimeId"] = block.runtime_id;
        i++;
    }
    std::ofstream output("runtime_block_states.json");
    output << std::setw(4) << j << std::endl;
    return 0;
}
