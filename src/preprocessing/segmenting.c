#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SEGMENT 250000 //approximate target size of small file

long file_size(char *name);//function definition below

int main(void)
{
    int segments=0, i, accum;
    FILE *fp1, *fp2;
    char smallFileName[300];
    char filename[300]={"./250000_WORDS_"};//base name for small files.
    char largeFileName[]={"./COMBINED_WORDS.txt"};//change to your path
    long sizeFile = file_size(largeFileName);
    segments = sizeFile/SEGMENT + 1;//ensure end of file
    char line[100];

    fp1 = fopen(largeFileName, "r");
    if(fp1)
    {
        for(i=0;i<segments;i++)
        {
            accum = 0;
            sprintf(smallFileName, "%s%d.txt", filename, i);
            fp2 = fopen(smallFileName, "w");
            if(fp2)
            {
                while(fscanf(fp1,"%s\n", line) != EOF && (accum < SEGMENT))
                {
                    fprintf(fp2, "%s\n", line);
                    accum++;//track size of growing file
                }
                fclose(fp2);
            }
        }
        fclose(fp1);
    }
    return 0;
}

long file_size(char *name)
{
    FILE* fp = fopen(name, "r");
    if (fp == NULL) {
        printf("Error opening file %s", name);
        return 1;
    }

    int file_length = 0;
    char str[100];
    while (fscanf(fp, "%s\n", str) != EOF) {
        file_length++;
    }
    fclose(fp);
    return file_length;
}