

#include "loadshader.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

const char* shader(const char* filename)
{


	char* data = NULL;

	FILE* fdata = fopen(filename, "rb");
	assert(fdata);
	fseek(fdata, 0, SEEK_END);
	size_t fileSizeBytes = ftell(fdata);
	rewind(fdata);

	data = calloc(fileSizeBytes + 1, 1);
	assert(data);

	int character;
	
	size_t index = 0;

	while ((character = fgetc(fdata)) != EOF)
	{


		assert(index < fileSizeBytes);
		data[index++] = (char)(character);

	}

	data[fileSizeBytes] = '\0';

	return (const char*)(data);

}