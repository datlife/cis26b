/*******************************************************
    Examples: 5.0 Text Files: Write/Read
/*******************************************************/

#include <stdio.h>
#include <math.h>

int main (void)
{
    // Text Files
    FILE *fp;
    double x, y;
    long int a;

    x = sqrt(3.0); // 1.732051;

    fp = fopen("num.txt", "w");
    fprintf(fp, "%f", x);
    fclose(fp);

    fp = fopen("num.txt", "r");
    fscanf(fp, "%lf", &y);
    fclose(fp);

    printf("TEXT Files:\n");
    printf("%f is ", x);
    if (x != y) printf("NOT ");
    printf("EQUAL to \n%f\n\n", y);

    // Binary Files
    fp = fopen("num.dat", "wb"); // write binary
    fwrite(&x, sizeof (double), 1, fp);
    //write from x, 1 item the size of a double to file fp
    fclose(fp);

    fp = fopen("num.dat", "rb"); // read binary
    fread(&y, sizeof (double), 1, fp);
    // read into y, 1 item the size of a double from file fp
    fclose(fp);

    printf("BINARY Files:\n");
    printf("%f is ", x);
    if (x != y) printf("NOT ");
    printf("EQUAL to \n%f\n\n", y);

    return 0;
}

