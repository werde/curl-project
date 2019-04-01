#include <string>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <curl/curl.h>

static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
    size_t written = 0;
    printf("kokokoko%s\n", ptr);//fwrite(ptr, size, nmemb, (FILE *)stream);
    return written;
}

int main()
{
    CURL *curl_handle;
    static const char *headerfilename = "head.out";
    FILE *headerfile;
    static const char *bodyfilename = "body.out";
    FILE *bodyfile;

    curl_global_init(CURL_GLOBAL_ALL);
    curl_handle = curl_easy_init();

    curl_easy_setopt(curl_handle, CURLOPT_URL, "http://www.youtube.com");
    curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 6.0; rv:52.0) Gecko/20100101 Firefox/52.0");
    https://curl.haxx.se/libcurl/c/CURLOPT_HTTPHEADER.html
    curl_easy_setopt(curl_handle, CURLOPT_HTTPHEADER, array('Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8'));
    curl_easy_setopt(curl_handle, CURLOPT_ACCEPT_ENCODING, "gzip, deflate, br");
    curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);
    //curl_easy_setopt(curl_handle, CURLOPT_HEADERDATA, headerfile);
    //curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, bodyfile);

    curl_easy_perform(curl_handle);
    curl_easy_cleanup(curl_handle);

    return 0;
}
