// ----- Davra Sample Code in C for Edge Devices -----
// Below code contains functionality for:
// 1) Creating or updating a Davra device
// 2) Sending in metric or event data to a device
// License: MIT License

#include <string.h>
#include <stdio.h>
#include <curl/curl.h>

//Fairly generic function for HTTP requests
int make_davra_request(char url[], char bearer_token[], char payload[], char method[]) {
    CURL *hnd = curl_easy_init();
    curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, method);
    curl_easy_setopt(hnd, CURLOPT_URL, url);
    struct curl_slist *headers = NULL;
    char auth_start[100] = "authorization: Bearer ";
    strcat(auth_start, bearer_token);
    headers = curl_slist_append(headers, auth_start);
    curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, payload);
    CURLcode res = curl_easy_perform(hnd);
    int response_code;
    curl_easy_getinfo(hnd, CURLINFO_RESPONSE_CODE, &response_code);
    return response_code;
}

//The variables below need to be updated with appropriate values for your own server and device
int main() {

    //API endpoint for creating and updating new devices in Davra
    //More information here: http://help.davra.com/#/api/devices/createupdate
    char devices_payload[] = "{\"name\": \"testDeviceFromCApp\",\"serialNumber\": \"testSerialNumberCApp1\"}";
    char devices_endpoint[] = "https://demo.davra.com/api/v1/devices";

    //API endpoint for sending metric and event data to Davra
    //More information here: http://help.davra.com/#/api/iotdata/put-iotdata
    char iotdata_endpoint[] = "https://demo.davra.com/api/v1/iotdata";
    char iotdata_payload[] = "{\"UUID\": \"testSerialNumberCApp1\",\"name\": \"rssi\",\"value\": -65,\"msg_type\": \"datum\"}";

    //Token for authentication
    char bearer_token[] = "your_own_token_here";

    //Create / update a device and display the HTTP response code
    printf("Creating or updating device ...\n\n");
    int devices_response = make_davra_request(devices_endpoint, bearer_token, devices_payload, "POST");
    printf("\n\nResponse from demo.davra.com devices endpoint: %d\n\n", devices_response);
    printf("Press ENTER to continue ...\n");

    //Pause execution until ENTER is pressed
    getchar();

    //Send in metric data and display the HTTP response code
    printf("Sending data to iotdata endpoint ...");
    int iotdata_response = make_davra_request(iotdata_endpoint, bearer_token, iotdata_payload, "PUT");
    printf("\n\nResponse from demo.davra.com iotdata endpoint: %d\n\n", iotdata_response);

    return 0;
}
