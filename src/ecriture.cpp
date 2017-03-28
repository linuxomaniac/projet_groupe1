#include <stdio.h>
#include <fstream>

using namespace std;


int main(int argc, char const* argv[])
{
    if (argc != 3){
        printf("erreur nombre d'arguments ./a.out in.dat out.flo\n");
    }
    int width, height;

    printf("%s  %s\n",argv[1],argv[2]);

    ifstream file(argv[1], ios::in);

    file >> width >> height;

    printf("%d  %d\n",width,height);

    float **ptr;
    ptr = new float* [height];
    for(int i=0; i<height; i++)
        ptr[i] = new float[2*width];



    for(int i=0; i<height; i++)
        for(int j=0; j<width; j++){
            file >> ptr[i][2*j] >> ptr[i][2*j+1];
            //printf("%f  %f\n",ptr[i][2*j],ptr[i][2*j+1]);
        }

    file.close();


    FILE *fic = fopen(argv[2], "wb");
    if(fic == 0)
        printf("erreur lors de la creation du fichier\n");


    // write the header
    fprintf(fic, "PIEH");
    if ((int)fwrite(&width,  sizeof(int),   1, fic) != 1 ||
	(int)fwrite(&height, sizeof(int),   1, fic) != 1)
        printf("erreur lors de l'ecriture de l'en-tete\n");

    // write the rows
    int n = 2 * width;
    for (int j = 0; j < height; j++) {
        if ((int)fwrite(ptr[j], sizeof(float), n, fic) != n)
            printf("erreur lors de l'ecriture des donnees\n");
    }

    fclose(fic);


    return 0;
}
