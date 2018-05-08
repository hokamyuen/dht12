#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define DEV_PATH "/dev/DHT12"

int main(void)
{
	int fd;
	char read_buf[5];
	char sign;
	printf("dht12 test\n");
	fd = open(DEV_PATH, O_RDONLY);
	if(fd < 0)
	{
		printf("open %s failed\n", DEV_PATH);
		return 0;
	}
	while(1)
	{
		read(fd, read_buf, 5);
		if(read_buf[4] == (read_buf[0] + read_buf[1] + read_buf[2] + read_buf[3]))
		{
			printf("semi: %d.%d%\n", read_buf[0], read_buf[1]);
			if(read_buf[3] & 0x80)
				sign = '-';
			else
				sign = '+';
			printf("temp: %c%d.%d\n", sign, read_buf[2], read_buf[3] & 0x7f);
		}
		else
		{
			printf("check failed\n");
		}
		sleep(3);
	}
	return 0;
}