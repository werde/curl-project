#include <string>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <curl/curl.h>

static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{

    printf("Got data size - %u, num - %u\n", size, nmemb);
    printf("%s\n", ptr);
    return size*nmemb;
}

static size_t cb_write_header_data(char *buffer, size_t size, size_t nitems, void *userdata)
{
    printf("Got headers size - %u, num - %u\n", size, nitems);
    printf("%s\n", buffer);
    return size*nitems;
}

struct curl_slist* make_headers()
{
    struct curl_slist* csl;

    csl = curl_slist_append(csl, "Host: google.com");
    csl = curl_slist_append(csl, "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
    csl = curl_slist_append(csl, "Accept-Language: ru-RU,ru;q=0.8,en-US;q=0.5,en;q=0.3");
    //csl = curl_slist_append(csl, "Cookie: VISITOR_INFO1_LIVE=rz2JQIX4iDA; PREF=cvdm=grid&f1=50000000&al=ru; SID=wgZUGREinnsGSwG2FLRMrD-LTo0RmPDzq1UNakxpj7zj3y2hCLfOSMe0cbEj5KrZu6VVqw.; HSID=AVxgsMqVshDBWiaLg; SSID=A--xL26-AQLBb0xTq; APISID=fMb2Oj2K61uKplGi/AxQ305EEnb5lG8K4a; SAPISID=eAS4wOcUF2Q7YkQc/ABkT6_aFi_NyC8Int; CONSENT=YES+RU.ru+; LOGIN_INFO=AFmmF2swRQIhAMrqK-6z1XTJCxwuL7NRQ9Zm6W01jBoExZB45-Y1VFvvAiA_mG6JfrBOkMZCeEfbTfDFqNmhMmZNKlM5gcOhCZ4n_Q:QUQ3MjNmenZBY0I2ZHY4dElBTG4xZWUzeUQtNGdGdkpGU244LUtreVZfOXp3SnZTTllkQkVsbjVlb1hDZG9RbEVJRXJvdVU2cUFNVHVIekE5WjJrWVZSelhHOUFaX3g2MDdyMzBkd21nXy1yOWxfQzJnSVZnOWw0SDF1UFpCbUtWSVpycFBqdkZBU3o5aEdnT21Obm12V1I0ejlJRXY3WnlpdWN4ZThaMldxdkhvV0hmSmZ1cHA4; SIDCC=AN0-TYvc71oFp1LqobWR4gedz4azVEtACjYH7A8K6qQtp5xfkyhA3D9mWXCYedHSn-DY8jpGff0; YSC=S80wuTfLzhQ");
    csl = curl_slist_append(csl, "Connection: keep-alive");
    csl = curl_slist_append(csl, "Upgrade-Insecure-Requests: 1");

    return csl;
};

void ssl_init(struct curl_slist* csl)
{
    const char *pPassphrase = NULL;

    static const char *pCertFile = "testcert.pem";
    static const char *pCACertFile = "cacert.pem";
    static const char *pHeaderFile = "dumpit";

    const char *pKeyName;
    const char *pKeyType;
    const char *pEngine;
    https://curl.haxx.se/libcurl/c/simplessl.html

}

int main()
{
    CURL* curl_handle;
    struct curl_slist* csl = make_headers();

    curl_global_init(CURL_GLOBAL_ALL);
    curl_handle = curl_easy_init();

    curl_easy_setopt(curl_handle, CURLOPT_URL, "http://google.com");
    curl_easy_setopt(curl_handle, CURLOPT_SSLENGINE, "dynamic");
    curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 6.0; rv:52.0) Gecko/20100101 Firefox/52.0");

    curl_easy_setopt(curl_handle, CURLOPT_HTTPHEADER, csl);
    curl_easy_setopt(curl_handle, CURLOPT_ACCEPT_ENCODING, "gzip, deflate, br");
    curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl_handle, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl_handle, CURLOPT_HEADERFUNCTION, cb_write_header_data);

    CURLcode res = curl_easy_perform(curl_handle);
    if(res != CURLE_OK)
        printf("error: %s\n", curl_easy_strerror(res));

    curl_easy_cleanup(curl_handle);
    return 0;
}
