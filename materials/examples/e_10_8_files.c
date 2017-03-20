/****************************************************************************

   Demonstration of File-Related Library Calls

****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( void )
{
    char filename[L_tmpnam]; // L_tmpnam defined in stdio.h
    char *strs[] = { "Hello\n", "Goodbye\n", "Cat\n", "Dog\n", NULL};
    char **mover = strs;
    char line[80], command[80];
    FILE *fp;

    // Open temporary file
    fp = tmpfile(); // opened in w+ mode
    for ( ; *mover != NULL; mover++) fputs(*mover, fp);
    fclose(fp);

    // Get name for a file that will not conflict with existing names
    if (tmpnam(filename) == NULL)
    {
        printf("Could not get non-conflicting filename.\n");
        exit(1);
    }
    printf("\nFilename obtained is: %s\n\n", filename);
    fp = fopen(filename, "w+");
    for (mover = strs; *mover != NULL; mover++) fputs(*mover, fp);
    rewind(fp);
    while (fgets(line, 80, fp)) printf("%s", line);
    putchar('\n');
    fclose(fp);
    getchar();

    // Is "filename" there?
    //sprintf(command, "ls -l %s", filename);
    sprintf(command, "type %s", filename);
    system("dir");
    system(command);
    getchar();

    if (rename(filename, "garbage.txt") != 0)
    {
        printf("Could not rename: %s\n", filename);
        remove(filename);
        system(command); // file not found error?!
        exit(2);
    }
    getchar();
    // If we got here rename succeeded
    system("type garbage.txt");

    return 0;
}
