#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>

uint32_t getNbo(uint32_t x){
	
	uint32_t x1 = (x & 0xff000000) >> 24;
	uint32_t x2 = (x & 0x00ff0000) >> 8;
	uint32_t x3 = (x & 0x0000ff00) << 8;
	uint32_t x4 = (x & 0x000000ff) << 24;

	return x1|x2|x3|x4;

}

uint32_t addNbo(uint32_t a, uint32_t b){
	return a + b;
}

int main(int argc, char *argv[]){
	
	if(argc != 3){
		printf("syntax : add-nbo <file1> <file2>\n");
		printf("sample : add-nbo a.bin c.bin\n");
	
		return -1;
	}

	FILE *fd;

	uint32_t buf[1] = {0};
	uint32_t a = 0;
	uint32_t b = 0;
	uint32_t result = 0;

	fd = fopen(argv[1], "rb");
	fread(buf, 1, 4, fd);
	fclose(fd);

	a = getNbo(buf[0]);

	fd = fopen(argv[2], "rb");
	fread(buf, 1, 4, fd);
	fclose(fd);

	b = getNbo(buf[0]);

	result = addNbo(a, b);

	printf("%d(%#x) + %d(%#x) = %d(%#x)\n", a, a, b, b, result, result);

	return 0;
}
