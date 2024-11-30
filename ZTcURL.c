//Code form the following example has been used: https://curl.se/libcurl/c/externalsocket.html
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

				  CURLU *h;

                                  CURLUcode uc;

				  h = curl_url();

				  uc = curl_url_set(h, CURLUPART_URL, argv[1], 0);

				  char *full_url = NULL;

				  char *host, *port, *path, *query;

    				  if(!uc) {
        
					  curl_url_get(h, CURLUPART_HOST, &host, 0);
        
					  curl_url_get(h, CURLUPART_PORT, &port, 0);
	 
					  curl_url_get(h, CURLUPART_PATH, &path, 0);
        
					  curl_url_get(h, CURLUPART_QUERY, &query, 0);
        
					  CURLU *urlp;
	
					  urlp = curl_url();

					  if (!urlp) {
        	
							fprintf(stderr, "Failed to create CURLU handle\n");
        	
							return 1;
    	
					  }

					  CURLUcode rc;

					  rc = curl_url_set(urlp, CURLUPART_URL, "http://99.99.99.99:9999", 0);
   
       					  if (rc) {
        
		 				   fprintf(stderr, "Failed to set base URL: %s\n", curl_url_strerror(rc));
        
		 				   curl_url_cleanup(urlp);
        
		 				   return 1;
    	
					  }

					  rc = curl_url_set(urlp, CURLUPART_PATH, path, CURLU_URLENCODE);
    
					  if (rc) {
        
						   fprintf(stderr, "Failed to set path: %s\n", curl_url_strerror(rc));
        
						   curl_url_cleanup(urlp);
        
						   return 1;
    
					  }

					  rc = curl_url_set(urlp, CURLUPART_QUERY, query, CURLU_URLENCODE);
    
					  if (rc) {
        
						   fprintf(stderr, "Failed to set query: %s\n", curl_url_strerror(rc));
        
						   curl_url_cleanup(urlp);
        
						   return 1;
    
					  }

					  rc = curl_url_get(urlp, CURLUPART_URL, &full_url, 0);
    
					  if (rc) {
        
					  	   fprintf(stderr, "Failed to get full URL: %s\n", curl_url_strerror(rc));
        
					  	   curl_url_cleanup(urlp);
        
					  	   return 1;
    
					  }

    					  /* Clean up */
    					  curl_url_cleanup(urlp);
		
					  curl_free(path);
        
					  curl_free(query);
    
    				} else {
        				  
					fprintf(stderr, "Error parsing URL: %s\n", curl_easy_strerror(uc));
    				
				}

    				curl_url_cleanup(h);

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
					    /*
                                             * Note that libcurl internally thinks that you connect to the host and
                                             * port that you specify in the URL option.
                                             */
                                            curl_easy_setopt(curl, CURLOPT_URL, full_url);

                                            /* call this function to get a socket */
                                            curl_easy_setopt(curl, CURLOPT_OPENSOCKETFUNCTION, opensocket);

					    Ziti_lib_init();

					    const char *identity_file = argv[2];

                                  	    ziti_context ztx = Ziti_load_context(identity_file);

                                  	    ziti_socket_t sock = Ziti_socket(SOCK_STREAM);

					    Ziti_connect_addr(sock, host, (unsigned int)strtoul(port, NULL, 10));

                                            curl_easy_setopt(curl, CURLOPT_OPENSOCKETDATA, &sock);

                                            /* call this function to set options for the socket */
                                            curl_easy_setopt(curl, CURLOPT_SOCKOPTFUNCTION, sockopt_callback);

                                            res = curl_easy_perform(curl);

					    printf("\n");

					    Ziti_lib_shutdown();
						
                                            curl_easy_cleanup(curl);

                                            close(sockfd);

                                            if(res) {

                                                      printf("libcurl error: %d\n", res);

                                                      return 4;

                                            }
	
					    curl_free(host);
 
                                            curl_free(port);

					    curl_free(full_url);

                                  }

                                #ifdef _WIN32
                                  WSACleanup();
                                #endif

                                  return 0;

}
