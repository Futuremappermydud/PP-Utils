#include "PPUtils.hpp"

std::map<std::string, RawPPData> PPData;

RawPPData DeserializeIntoRawPPData(rapidjson::Value& obj)
{
	RawPPData data;

	data._Easy_SoloStandard = 0.0f;
	data._Normal_SoloStandard = 0.0f;
	data._Hard_SoloStandard = 0.0f;
	data._Expert_SoloStandard = 0.0f;
	data._ExpertPlus_SoloStandard = 0.0f;

	if(obj.HasMember("_Easy_SoloStandard"))
		data._Easy_SoloStandard = obj["_Easy_SoloStandard"].GetFloat();

	if(obj.HasMember("_Normal_SoloStandard"))
		data._Normal_SoloStandard = obj["_Normal_SoloStandard"].GetFloat();
	
	if(obj.HasMember("_Hard_SoloStandard"))
		data._Hard_SoloStandard = obj["_Hard_SoloStandard"].GetFloat();
		
	if(obj.HasMember("_Expert_SoloStandard"))
		data._Expert_SoloStandard = obj["_Expert_SoloStandard"].GetFloat();
	
	if(obj.HasMember("_ExpertPlus_SoloStandard"))
		data._ExpertPlus_SoloStandard = obj["_ExpertPlus_SoloStandard"].GetFloat();

	return data;
}

const std::string URI_PREFIX = "https://cdn.pulselane.dev/";
const std::string FILE_NAME = "raw_pp.json";

Il2CppObject* PP_WebRequestAPI;
Il2CppObject* PP_DownloadHandler;
Il2CppObject* PP_WebRequestAsyncOp;
Il2CppString* PP_JsonStr;

size_t writeFunction(void* ptr, size_t size, size_t nmemb, std::string* data) {
    data->append((char*)ptr, size * nmemb);
    return size * nmemb;
}

void PPDownloader_WebRequest() 
{
	if(curl) {
    	curl_easy_setopt(curl, CURLOPT_URL, std::string(URI_PREFIX + FILE_NAME).c_str());
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, std::string("PP Utils" + modInfo.version).c_str());
        curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
        curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
        
        std::string response_string;
        std::string header_string;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);
        
        char* url;
        long response_code;
        double elapsed;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
        curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &elapsed);
        curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &url);
        
        curl_easy_perform(curl);
		rapidjson::Document d;
		d.Parse(response_string);

		//VSCode doesnt like rapidjson so you can ignore the "errors"
		for (auto itr = d.MemberBegin(); itr != d.MemberEnd(); ++itr)
		{
			RawPPData data = DeserializeIntoRawPPData(itr->value);
			PPData.insert({itr->name.GetString(), data});
		}
		getLogger().debug(std::to_string(PPData.size()));	
		PPData_Init(PPData);
        curl_easy_cleanup(curl);
		curl_global_cleanup();
        curl = NULL;
	}
}
