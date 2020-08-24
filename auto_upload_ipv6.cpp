//
//#include <iostream>
//#include <fstream>
//#include <string.h>
//using namespace std;
//ofstream WriteFile;
//ifstream ReadFile;
//char g_str[100];
//char tmp[100];
//int main()
//{
//	ReadFile.open("a.txt", ios_base::in | ios::binary | ios::ate);
//	char * buffer;
//	long size;
//	size = ReadFile.tellg();
//	ReadFile.seekg(0, ios::beg);
//	buffer = new char[size+1];
//	ReadFile.read(buffer, size);
//	buffer[size] = '\0';
//	ReadFile.close();
//
//	char * b1;
//	char * b3;
//	for(int i = 0; i< size;i++){
//		if(buffer[i]=='['){
//			b1 = new char[i+2];
//			memcpy(b1, buffer, i+1);
//			b1[i+1] = '\0';
//		}
//		if(buffer[i]==']'){
//			b3 = new char[size];
//			memcpy(b3, buffer+i, size-i+1);
//			b3[size-i+1] = '\0';
//			break;
//		}
//	}
//
//	char b2[100] = "2409:893c:52:fe66:55d:5bfe:82bd:8e56";
//	char * w = new char[size+40];
//	memset(w,0,sizeof(w));
//	strcat(w, b1);
//	strcat(w, b2);
//	strcat(w, b3);
//
//	WriteFile.open("a.txt", ios_base::out | ios::binary );
//	WriteFile << w;
//	WriteFile.close();
//	_sleep(1000);
//	/*ReadFile.open("a.txt", ios_base::in);
//	ReadFile >> g_str;
//	ReadFile.close();
//	while(1)
//	{
//		_sleep(1000);
//		memset(tmp, 0, sizeof(tmp));
//		ReadFile.open("a.txt", ios_base::in);
//		ReadFile >> tmp;
//		ReadFile.close();
//		if(strcmp(tmp, g_str) != 0){
//			memset(g_str, 0, sizeof(g_str));
//			strcpy(g_str, tmp);
//
//			cout << "modify!" << endl;
//
//
//		}
//	}*/
//
//}


#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <Winsock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib ")  //linking to the library

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

ofstream myWriteFile;
ifstream myReadFile;
char g_str[100];
char tmp[100];
char ip6[50] = {0};

int get_ip()
{
    struct addrinfo *ailist, *aip;
    struct addrinfo hint;
    struct sockaddr_in6 *sinp6;
    PHOSTENT hostinfo;
    char hostname[255] = {0}; //主机名   
    char *port = "3294";      //端口号 
    const char *addr;
    int ilRc;
    gethostname(hostname, sizeof(hostname));
    
    hint.ai_family = AF_INET6;        //hint 的限定设置
    hint.ai_socktype = SOCK_STREAM;   //这里可是设置 socket type    比如  SOCK_DGRAM
    hint.ai_flags = AI_PASSIVE;       // flags 的标志很多。常用的有AI_CANONNAME;
    hint.ai_protocol = 0;             //设置协议  一般为0，默认
    hint.ai_addrlen = 0;              //下面不可以设置，为0，或者为NULL
    hint.ai_canonname = NULL;
    hint.ai_addr = NULL;
    hint.ai_next = NULL;
    ilRc = getaddrinfo(hostname, port, &hint, &ailist); //通过主机名获得地址信息
    if (ilRc < 0)
    {
        char str_error[100];
        strcpy(str_error, (char *)gai_strerror(errno));
        printf("str_error = %s", str_error);
        return 0;
    }
    if(ailist == NULL)
    {
        printf("sorry not find the IP address,please try again \n");
    }

    for (aip = ailist; aip != NULL; aip = aip->ai_next) //显示获取的信息
    {
        aip->ai_family == AF_INET6;
        sinp6 = (struct sockaddr_in6 *)aip->ai_addr;    //为什么是for 循环 ，先向下看
        int i;
        //printf("ipv6 addr = ");
        /*for(i = 0; i < 16; i++)
        {
            if(((i-1)%2) && (i>0))
            {
                printf(":");
            }
            printf("%02x",sinp6->sin6_addr.u.Byte[i]);
        }*/
		memset(ip6, 0, sizeof(ip6));
		if(sinp6->sin6_addr.u.Byte[0] != 0xfe)
		{
			sprintf(ip6, "%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x", sinp6->sin6_addr.u.Byte[0], sinp6->sin6_addr.u.Byte[1], sinp6->sin6_addr.u.Byte[2], sinp6->sin6_addr.u.Byte[3], sinp6->sin6_addr.u.Byte[4], sinp6->sin6_addr.u.Byte[5], sinp6->sin6_addr.u.Byte[6], sinp6->sin6_addr.u.Byte[7], sinp6->sin6_addr.u.Byte[8], sinp6->sin6_addr.u.Byte[9], sinp6->sin6_addr.u.Byte[10], sinp6->sin6_addr.u.Byte[11], sinp6->sin6_addr.u.Byte[12], sinp6->sin6_addr.u.Byte[13], sinp6->sin6_addr.u.Byte[14], sinp6->sin6_addr.u.Byte[15]);
			printf("ipv6 addr = %s\n", ip6);
		}
    }
	if(ip6[0] == 0) strcpy(ip6, "fe80::1234");
	myWriteFile.open("ip.txt", ios_base::out | ios::binary );
    myWriteFile << ip6;
    myWriteFile.close();
	return 0;
}

int main()
{
	WORD wVersionRequested;
    WSADATA wsaData;
    int err;
    wVersionRequested = MAKEWORD( 1, 1 );
    err = WSAStartup( wVersionRequested, &wsaData );//initiate the ws2_32.dll and match the version
    if ( err != 0 )
    {
        return 0;
    }
    if ( LOBYTE( wsaData.wVersion ) != 1 ||   //if the version is not matched ,then quit and terminate the ws3_32.dll 
        HIBYTE( wsaData.wVersion ) != 1 )
    {
        WSACleanup( );
        return 0;
    }
	//get_ip();

    myReadFile.open("ip.txt", ios_base::in);
    myReadFile >> g_str ;
    //cout << g_str << endl;
    myReadFile.close();
	int index = 0;
    while(1)
    {
        _sleep(1000);
		if((index) % 20 == 0) { get_ip(); index = 0; }
		index++;
        memset(tmp, 0, sizeof(tmp));
        myReadFile.open("ip.txt", ios_base::in);
        myReadFile >> tmp;
        myReadFile.close();
        if(strcmp(tmp, g_str) != 0){
            memset(g_str, 0, sizeof(g_str));
            strcpy(g_str, tmp);

            myReadFile.open("WeiJinchuang.github.io/index.html", ios_base::in | ios::binary | ios::ate);
            char * buffer;
            long size;
            size = myReadFile.tellg();
            myReadFile.seekg(0, ios::beg);
            buffer = new char[size+1];
            myReadFile.read(buffer, size);
            buffer[size] = '\0';
            myReadFile.close();
            char * b1;
            char * b3;
            for(int i = 0; i< size;i++){
                if(buffer[i]=='['){
                    b1 = new char[i+2];
                    memcpy(b1, buffer, i+1);
                    b1[i+1] = '\0';
                }
                if(buffer[i]==']'){
                    b3 = new char[size];
                    memcpy(b3, buffer+i, size-i+1);
                    b3[size-i+1] = '\0';
                    break;
                }
            }

            char * w = new char[size+50];
            memset(w,0,sizeof(w));
            strcat(w, b1);
            strcat(w, g_str);
            strcat(w, b3);

            myWriteFile.open("WeiJinchuang.github.io/index.html", ios_base::out | ios::binary );
            myWriteFile << w;
            myWriteFile.close();

            system("cd ./WeiJinchuang.github.io/ && git add . && git commit -m \"ww\" && git push -u origin master ");

        }
    }
}