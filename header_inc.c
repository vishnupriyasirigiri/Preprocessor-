#include"header.c"
extern void header_file_inclusion(FILE *fp, FILE *out)
{
    char ch, filename[50], path[80] = "/usr/include/";
    int i = 0, flag = 0;

    while((ch=fgetc(fp))!=-1){
        if(ch == '<'){
            flag = 1; //make flag 1 if < is present
            i = 0;
        }
        else if(ch == '>'){
            flag = 0; //make flag 0 if > is present
            filename[i] = '\0';
            strcat(path, filename);//concatinate filename to path

            FILE *fd = fopen(path, "r");//open file after concatinating with path

            if(fd == 0){
                printf("%s file not present\n", filename);
                return;
            }
            else{
                while((ch = fgetc(fd)) != -1)
                    fputc(ch, out);//headerfile inclusion
    		
		strcpy(path,"/usr/include/");

                fclose(fd);
            }
        }
        else if(flag == 1){
            filename[i] = ch; //copy filename from ch char by char if its between < >
            i++;
        }
        else fputc(ch, out); //put rest of the file contents in output file
    }
    printf("Header file is included\n");
}

