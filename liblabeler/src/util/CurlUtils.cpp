#include <curl/curl.h>
#include <string>

using namespace std;

namespace Bioimagery {

    // CURL buffer
    static string curlBuffer;  
      
    // Callback function for CURL 
    static size_t curlWriter(char *data, size_t size, size_t nmemb,  
                      string *buffer)  
    {  
        // Append the data to the buffer    
        buffer->append(data, size * nmemb);  
        
        return size * nmemb;  
    }  

    static string curlGet(char* url) {
        CURL *curl;
        CURLcode res;

        curl = curl_easy_init();
        
        // Clear the curl buffer
        curlBuffer.clear();
        
        if(curl) {  
            curl_easy_setopt(curl, CURLOPT_URL, url);  
            curl_easy_setopt(curl, CURLOPT_HEADER, 0);  
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);  
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlWriter);  
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &curlBuffer);             

            res = curl_easy_perform(curl);
            if(res) {
                // Return the data
            } else {
                // Something went wrong getting the data
                fprintf(stderr, "Error GETing URL: %s -> %i \n", url, res);
            }
            
            curl_easy_cleanup(curl);
        }
        
        // TODO check if we want the null terminator
        return curlBuffer;

    }

}