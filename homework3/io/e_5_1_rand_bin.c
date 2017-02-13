/*********************************************************
    Examples: 5.1 Demonstration of Functions to Manipulate
                  Random Access Files
/*********************************************************/

#include <stdio.h>
#include <stdlib.h>  // exit
#define FILENAME "e51.dat"

//int main(int argc, char *argv[])
int main(void)
{
    FILE *fp;
    int i[] = {1, 2, 3, 4, 5}, j[5], k;
    long pos;

    //if ((fp = fopen(argv[1]), "w+b")) == NULL)
    if ((fp = fopen(FILENAME, "w+b")) == NULL)
    {
        //printf("Could not open %s.\n", argv[1]);
        printf("Could not open %s.\n", FILENAME);
        exit(1);
    }
    fwrite(i, sizeof(int), 5, fp);
    rewind(fp);
    pos = ftell(fp); // byte offset from beginning of file
    printf("We are %ld bytes from beginning of file.\n", pos);
    fread(j, sizeof(int), 5, fp);
    for (k = 0; k < 5; k++ ) printf("j[%d] = %d  ", k, j[k]);
    pos = ftell(fp); // byte offset from beginning of file
    printf("\nWe are %ld bytes from beginning of file.\n", pos);

    fseek(fp, 2 * sizeof (int), SEEK_SET); // points to 3
    k = 6;
    fwrite(&k, sizeof(int), 1, fp); // overwrites 3 with 6
    fseek(fp, -1 * sizeof (int), SEEK_CUR); // is 6 there?
    fread(&k, sizeof (int), 1, fp);
    printf("\n\nInteger obtained is %d.\n", k);
    pos = ftell(fp); // byte offset from beginning of file
    printf("We are %ld bytes from beginning of file.\n", pos);
    rewind(fp);
    fread(j, sizeof(int), 5, fp);
    for (k = 0; k < 5; k++ ) printf("j[%d] = %d  ", k, j[k]);

    k = 13;
    fseek(fp, -1 * sizeof (int), SEEK_END); // Points at 5
    fwrite(&k, sizeof(int), 1, fp); // overwrites 5 with 13
    fseek(fp, -1 * sizeof (int), SEEK_CUR); // is 13 there?
    fread(&k, sizeof (int), 1, fp);
    printf("\n\nInteger obtained is %d.\n", k);
    pos = ftell(fp); // byte offset from beginning of file
    printf("We are %ld bytes from beginning of file.\n", pos);
    rewind(fp);
    fread(j, sizeof(int), 5, fp);
    for (k = 0; k < 5; k++ ) printf("j[%d] = %d  ", k, j[k]);

    fclose(fp);

    return 0;
}

