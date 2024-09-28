

#include "..\src\Headers.h"
#include <iostream>

int main() {

    FileHeader header;

    printf("Sizeof file_id:      %d\n", sizeof(header.file_id));
    printf("Sizeof file_flags:   %d\n", sizeof(header.file_flags));
    printf("Sizeof file_verion:  %d\n", sizeof(header.file_version));
    printf("Sizeof file_type:    %d\n", sizeof(header.file_type));
    printf("Sizeof file_size:    %d\n", sizeof(header.file_size));
    printf("Sizeof data_offset:  %d\n", sizeof(header.data_offset));
    printf("Sizeof index_offset: %d\n", sizeof(header.index_offset));
    printf("Sizeof padding:      %d\n", sizeof(header.padding));
    printf("Sizeof header:       %d\n\n", sizeof(header));



    return 0;
}