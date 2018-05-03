#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<stdlib.h>
#include <arpa/inet.h>

#define MAXSZ 128


int main()
{
    int sock;

    struct sockaddr_in serverAddress;

    int n;
    char msg1[MAXSZ];
    char msg2[MAXSZ];


    if((sock=socket(PF_INET,SOCK_STREAM,0))<0)
        printf("Error Creating Socket\n"),exit(1);
    else
        printf("Socket Created Successfully\n");    

    memset(&serverAddress,0,sizeof(serverAddress));
    serverAddress.sin_family=AF_INET;
    serverAddress.sin_addr.s_addr=htonl(INADDR_ANY);
    serverAddress.sin_port=htons(9999);


    if((connect(sock,(struct sockaddr *)&serverAddress,sizeof(serverAddress)))<0)
        printf("Error Connecting"),exit(1);

    while(1)
    {
        printf("\nEnter message to send to server:\n");
        scanf("%[^\n]%*c",msg1);

        (send(sock,msg1,strlen(msg1),0)) < 0 ? printf("Error Sending\n"),exit(1) : printf("Sent Success\n");
        (recv(sock,msg2,MAXSZ,0)) < 0 ? printf("Error Receiving\n"),exit(1) : printf("Recv Success\n");

        printf("Echoed Msg From Server: %s\n",msg2);
    }

    return 0;
}

