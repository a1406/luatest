#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>

#define MAX_CLIENT 10

int max_fd(int a[], int n)  
{  
    int max = 0;  
    for(int i = 0; i < n; i++)  
    {  
        if(max < a[i])  
        {  
            max = a[i];  
        }  
    }  
    return  max;  
}

int add_fd(int a[], int n, int fd)
{
	if (n >= MAX_CLIENT)
		return (-1);
	a[n] = fd;
	return (0);
}

int del_fd(int a[], int n, int fd)
{
	for (int i = 0; i < n; ++i)
	{
		if (a[i] == fd)
		{
			memmove(&a[i], &a[i+1], sizeof(int) * (n - i - 1));
			return (0);
		}
	}
	return (-1);
}

//设置socket连接为非阻塞模式
void setnonblocking(int sockfd) {
    int opts;

    opts = fcntl(sockfd, F_GETFL);
    if(opts < 0) {
        perror("fcntl(F_GETFL)\n");
        exit(1);
    }
    opts = (opts | O_NONBLOCK);
    if(fcntl(sockfd, F_SETFL, opts) < 0) {
        perror("fcntl(F_SETFL)\n");
        exit(1);
    }
}

int network_main(int port)
{
    int server_sock = 0;  
    struct sockaddr_in server_addr;  
    memset(&server_addr, 0, sizeof(server_addr));  
  
    if((server_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)  
    {  
        printf("create socket error\n");
		return (-1);
    }  
  
    server_addr.sin_family = AF_INET;  
    server_addr.sin_addr.s_addr =htonl(INADDR_ANY);  
    server_addr.sin_port = htons(port);  
      
    if(bind(server_sock, (struct sockaddr*)&server_addr,sizeof(server_addr)) == -1)  
    {  
        printf("bind error\n");  
        return (-1);  
    }     
      
    if(listen(server_sock, 5) == -1)  
    {     
        printf("listent error\n");
        return (-1);  
    }  
      
    fd_set fd[2];  
    FD_ZERO(&fd[0]);  
    FD_SET(server_sock, &fd[0]);  
    int sock[MAX_CLIENT + 1];
	int n_client = 1;
    sock[0] = server_sock;  
      
    while(1)  
    {  
		struct timeval tv = {1, 0};  
		FD_ZERO(&fd[1]);  
		fd[1] = fd[0];  
		int ret = select(max_fd(sock, n_client) + 1, &fd[1], NULL, NULL, &tv);  
		if(ret < 0)  
		{  
			printf("select error\n");
			return (-1);
		}  
		else if(ret == 0)  
		{  
//		   printf("time out\n");
			continue;
		}  
		if(FD_ISSET(sock[0], &fd[1]))
		{
			--ret;
			if (n_client < MAX_CLIENT)
			{
				struct sockaddr_in client_addr;  
				memset(&client_addr, 0, sizeof(client_addr));  
				unsigned int len = sizeof(client_addr);  
				int new_sock=accept(sock[0],(struct sockaddr*)&client_addr, &len);  
				if(new_sock == -1)  
				{  
					printf("accept error\n");
					continue;
				}
				add_fd(sock, n_client, new_sock);
				FD_SET(new_sock, &fd[0]);  
				n_client++;
				printf("accept from client %d\n", new_sock);
			}
		}  
          
		char recvbuf[1024];
//		char sendbuf[1024];
		for(int i = 1; i < n_client && ret > 0; i++)  
		{  
			if(!FD_ISSET(sock[i], &fd[1]))
				continue;
			--ret;
			int n = recv(sock[i], recvbuf, sizeof(recvbuf), 0);
			if (n <= 0)
			{     
				printf("recv error\n");
				FD_CLR(sock[i], &fd[0]);  
				close(sock[i]);
				del_fd(sock, n_client, sock[i]);
				n_client--;  
				continue;  
			}
			recvbuf[n] = '\0';

			printf("recv %s\n", recvbuf);
  
// 			strcpy(sendbuf, recvbuf);  
//  
// 			if(send(sock[i], sendbuf, sizeof(sendbuf), 0) <= 0)  
// 			{     
// 				cout<<"send error"<<endl;  
// 				FD_CLR(sock[i], &fd[0]);  
// 				close(sock[i]);  
// 				sock[i] = 0;  
// 				count--;  
// 				continue;  
// 			}  
		}  
	}  
	return (0);
}
