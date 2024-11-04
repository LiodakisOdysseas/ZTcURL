/*Code form the following example has been used: https://curl.se/libcurl/c/externalsocket.html */
#include <ziti/zitilib.h>
#include <curl/curl.h>
#include <string.h>
#include <strings.h>

#ifdef _WIN32
#define close closesocket
#else
#include <unistd.h>
#endif

static curl_socket_t opensocket(void *clientp, curlsocktype purpose, struct curl_sockaddr *address){

                                                                                                    curl_socket_t sockfd;
                                                                                                    (void)purpose;
                                                                                                    (void)address;
                                                                                                    sockfd = *(curl_socket_t *)clientp;
                                                                                                    /* the actual externally set socket is passed in via the OPENSOCKETDATA
                                                                                                       option */
                                                                                                    return sockfd;

}

static int sockopt_callback(void *clientp, curl_socket_t curlfd, curlsocktype purpose){

                                                                                        (void)clientp;
                                                                                        (void)curlfd;
                                                                                        (void)purpose;
                                                                                        /* This return code was added in libcurl 7.21.5 */
                                                                                        return CURL_SOCKOPT_ALREADY_CONNECTED;

}

int main(int argc, char *argv[]){

                                  const char *identity_file = argv[1];

                                  Ziti_lib_init();

                                  ziti_context ztx = Ziti_load_context(identity_file);

                                  ziti_socket_t sock = Ziti_socket(SOCK_STREAM);

				  printf("Which service would you like to access?:");

				  char service_name[100];

				  if (fgets(service_name, sizeof(service_name), stdin) != NULL) {
        											// Remove the newline character if present
       										    		 size_t len = strlen(service_name);

	 									    		 if (len > 0 && service_name[len - 1] == '\n') service_name[len - 1] = '\0';

				  }

                                  int error = Ziti_connect(sock, ztx, service_name, NULL);

                                  CURL *curl;

                                  CURLcode res;

                                  curl_socket_t sockfd;

                                #ifdef _WIN32
                                  WSADATA wsaData;
                                  int initwsa = WSAStartup(MAKEWORD(2, 2), &wsaData);
                                  if(initwsa) {
                                    printf("WSAStartup failed: %d\n", initwsa);
                                    return 1;
                                  }
                                #endif

                                  curl = curl_easy_init();

                                  if(curl) {

					    char entity_id[100];

					    printf("Which entity would you like to query?:");

                                            if (fgets(entity_id, sizeof(entity_id), stdin) != NULL) {
                                                                                                		// Remove the newline character if present
                                                                                                 		size_t len = strlen(entity_id);

                                                                                                 		if (len > 0 && entity_id[len - 1] == '\n') entity_id[len - 1] = '\0';

                                  	    }

					    char url[80];

					    strcpy(url, "http://99.99.99.99:9999/v2/entities/");

					    strcat(url, entity_id);

					    /*
                                             * Note that libcurl internally thinks that you connect to the host and
                                             * port that you specify in the URL option.
                                             */
                                            curl_easy_setopt(curl, CURLOPT_URL, url);

                                            /* call this function to get a socket */
                                            curl_easy_setopt(curl, CURLOPT_OPENSOCKETFUNCTION, opensocket);
                                            curl_easy_setopt(curl, CURLOPT_OPENSOCKETDATA, &sock);

                                            /* call this function to set options for the socket */
                                            curl_easy_setopt(curl, CURLOPT_SOCKOPTFUNCTION, sockopt_callback);

                                            res = curl_easy_perform(curl);

                                            curl_easy_cleanup(curl);

                                            close(sockfd);

                                            if(res) {

                                                      printf("libcurl error: %d\n", res);

                                                      return 4;

                                            }

                                  }

                                #ifdef _WIN32
                                  WSACleanup();
                                #endif

                                  Ziti_lib_shutdown();

				  printf("\n");

                                  return 0;

}
