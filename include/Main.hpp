#pragma once

#include <unordered_set>
#include "../extern/beatsaber-hook/shared/utils/utils.h"
#include "../extern/beatsaber-hook/shared/utils/logging.hpp"
#include "../extern/modloader/shared/modloader.hpp"
#include "../extern/beatsaber-hook/shared/utils/il2cpp-utils.hpp" 
#include "../extern/beatsaber-hook/shared/utils/il2cpp-functions.hpp"
#include "../extern/beatsaber-hook/shared/utils/typedefs.h"
#include "../extern/beatsaber-hook/shared/config/config-utils.hpp"

#include "../extern/codegen/include/GlobalNamespace/BeatmapDifficulty.hpp"
#include "../extern/codegen/include/GlobalNamespace/GameplayModifiers.hpp"
#include "../extern/codegen/include/GlobalNamespace/GameplayModifiersModelSO.hpp"
#include "../extern/codegen/include/GlobalNamespace/BeatmapDifficulty.hpp"

#include <unordered_set>
#include <map>
#include <list>
#include <tuple> // for tuple 
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>

#include "../include/Curl/include/curl/curl.h"
#include "../include/Curl/include/curl/easy.h"

extern CURL *curl;
extern CURLcode res;

static ModInfo modInfo;

static const Logger& getLogger() {
    static const Logger logger(modInfo);
    return logger;
}

static std::vector<std::string> split(std::string const &str, const char delim)
{
    std::vector<std::string> out;
	size_t start;
	size_t end = 0;

	while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
	{
		end = str.find(delim, start);
		out.push_back(str.substr(start, end - start));
	}
    return out;
}

static std::string GetHash(std::string levelId)
{
    getLogger().debug(levelId);
    if (levelId.find("custom_level_"))
    {
        auto splits = split(levelId, '_');
        return splits[2];
    }
    getLogger().debug(levelId);
    return levelId;

}

void PPDownloader_WebRequest();