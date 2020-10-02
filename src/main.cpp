#include "../include/Main.hpp"
#include "../include/PPUtils.hpp"

CURL *curl;
CURLcode res;

extern "C" void setup(ModInfo& info) {
    // Set the ID and version of this mod
    info.id = "PPUtils";
    info.version = "0.1.0";
    modInfo = info;
}

extern "C" void load() {
    il2cpp_functions::Init();
 
    curl_global_init(CURL_GLOBAL_DEFAULT);
    auto curl = curl_easy_init();

    
}