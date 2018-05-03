#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAXSZ 128

int main()
{
    int sock;
    int newsock;

    struct sockaddr_in serverAddress;
    struct sockaddr_in clientAddress;

    int n;
    char msg[MAXSZ];
    int clientAddressLength;
    int pid;

    if((sock=socket(PF_INET,SOCK_STREAM,0))<0)
    {
        printf("Error Creating Socket\n");
        exit(1);
    }else
        printf("Socket Created Successfully\n");    

    memset(&serverAddress,0,sizeof(serverAddress));
    serverAddress.sin_family=AF_INET;
    serverAddress.sin_addr.s_addr=htonl(INADDR_ANY);
    serverAddress.sin_port=htons(9999);

    if((bind(sock,(struct sockaddr *)&serverAddress, sizeof(serverAddress)))<0)
        printf("Error Binding\n"),exit(1);
    else printf("Binding Successful\n");        

    if((listen(sock,5))<0)
        printf("Error Listening\n"),exit(1);
    else
        printf("Listening\n");

    while(1)
    {
        
        clientAddressLength=sizeof(clientAddress);
        if((newsock=accept(sock,(struct sockaddr*)&clientAddress,&clientAddressLength))<0)
            printf("Error Accepting\n"),exit(1);
        else 
            printf("Connected Client: %s\n",inet_ntoa(clientAddress.sin_addr));

        pid=fork();
        pid < 0 ? printf("Error Creating Child\n") : printf("Child Process Created with PID= %d\n",pid); 
        if(pid==0)
        {

            while(1)
            {
                if((n=recv(newsock,msg,MAXSZ,0))<=0)
                    printf("Error Receiving\n"),exit(1);
                else    
                    printf("Received from %s: %s\n",inet_ntoa(clientAddress.sin_addr),msg);
                    
                msg[n]='\0';
                if((send(newsock,msg,n,0))<=0)
                    printf("Send Error\n"),exit(1);
            }

        }
        else
        {
            close(newsock);
        }
    }

    return 0;
}
