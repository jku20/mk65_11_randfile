#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#define SIZE 10
#define OUTFILE "numbers.out"

int main() {
    int i;
    int fin = open("/dev/random",O_RDONLY);
    if(fin == -1) {
        printf("error: %s\n",strerror(errno));

        return 1;
    }

    int nums[SIZE];

    printf("\nGenerating Random Numbers:\n");

    int worked = 1;
    worked = read(fin,nums,sizeof(nums));
    if(worked == -1) {
        printf("error: %s\n",strerror(errno));

        return 1;
    }

    for(i = 0; i < SIZE; i++) {
        printf("%15d at index %d\n",nums[i],i);
    }

    printf("\nWriting numbers to file...\n");

    int fout = open(OUTFILE,O_WRONLY | O_CREAT, 0644);
    if(fout == -1) {
        printf("error: %s\n",strerror(errno));

        return 1;
    }
    worked = write(fout,nums,sizeof(nums));
    if(worked == -1) {
        printf("error: %s\n",strerror(errno));

        return 1;
    }
    
    printf("\nReading numbers from the file...\n");

    fin = open("numbers.out",O_RDONLY);
    if(fin == -1) {
        printf("error: %s\n",strerror(errno));

        return 1;
    }
    worked = read(fin,nums,sizeof(nums));
    if(worked == -1) {
        printf("error: %s\n",strerror(errno));

        return 1;
    }

    printf("\nVerification that written numbers are the same\n");
    for(i = 0; i < SIZE; i++) {
        printf("%15d at index %d\n",nums[i],i);
    }

    return 0;
}
