#include"header.c"
int main(int argc,char *argv[]){
        FILE *fp,*out,*in,*tmp;
        if(argc!=2){
                printf("Usage: ./mypreprocessor filename.c\n");
                return 1;
        }
        fp=fopen(argv[1],"r");
        if(fp==0){
                printf("File not present\n");
                return 1;
        }

        out=fopen("output.i","w");
        macro_replacement(fp,out);
        fclose(fp);
        fclose(out);

        in=fopen("output.i","r");//comments removal
        tmp=fopen("temp.i","w");
        comment_removal(in,tmp);
        fclose(in);
        fclose(tmp);
        remove("output.i");//delete the old one
        rename("temp.i","output.i"); //temp.i now becomes output.i
        
	in=fopen("output.i","r");
        tmp=fopen("temp.i","w");
        header_file_inclusion(in,tmp);
        fclose(in);
        fclose(tmp);
        remove("output.i");
        rename("temp.i","output.i");

        printf("Preprocessing completed\n");
        return 0;
}

