#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    fd_set         rfds;
    struct timeval tv;
	char buf[201];
	int max_fd = 0;

	for (;;)
	{
		tv.tv_sec  = 3;
		tv.tv_usec = 600;
		FD_ZERO(&rfds);
		FD_SET(0, &rfds);
		int retval = select(max_fd + 1, &rfds, NULL, NULL, &tv);
		if (retval == -1)
		{
			perror("select error");
			exit(1);
		}
		else if (retval)
		{  //retval>0说明监听的集合中有改变
			if (FD_ISSET(max_fd, &rfds))
			{  //所关心的文件应在集合中
				int nread = read(max_fd, buf, 200);
				if (nread <= 0)
				{
					perror("read failed");
					exit(1);
				}
				buf[nread] = '\0';
				printf("read[%d] %s\n", nread, buf);
			}
		}
		else
		{
			printf("timeout\n");
		}
	}
    return 0;
}
