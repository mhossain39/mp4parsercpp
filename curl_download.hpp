#include <curl/curl.h>
#include <curl/easy.h>

#include <cstdio>
#include <iostream>
#include <stdexcept>
#include <string>


// https://curl.se/libcurl/c/CURLOPT_XFERINFOFUNCTION.html

std::string extract_file_name(const std::string& url)
{
    int i = url.size();
    for (; i >= 0; i--)
    {
        if (url[i] == '/')
        {
            break;
        }
    }

    return url.substr(i + 1, url.size() - 1);
}

bool download(const std::string& url, const std::string& file_path)
{
    const std::string file_name = extract_file_name(url);



    CURL* curl;
    FILE* fp;
    CURLcode res;
    curl = curl_easy_init();
    if (curl)
    {
        fp = fopen(file_path.c_str(), "wb");
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1);
        // Perform a file transfer synchronously.
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(fp);
    }

    // Show cursor

    if (res == CURLE_OK)
    {
        return true;
    }
    else
    {
        return false;
    }
}

