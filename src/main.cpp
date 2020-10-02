#include "../include/Main.hpp"
#include "../include/PPUtils.hpp"
#include <thread>

CURL *curl;
CURLcode res;

extern "C" void setup(ModInfo& info) {
    info.id = "PPUtils";
    info.version = "0.1.0";
    modInfo = info;
}

extern "C" void load() {
    il2cpp_functions::Init();
 
    curl_global_init(CURL_GLOBAL_DEFAULT);
    auto curl = curl_easy_init();

    std::thread thread(PPDownloader_WebRequest);

    thread.detach();
}