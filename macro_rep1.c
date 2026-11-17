#include"header.c"
char macro_name[50][100];
char macro_body[50][100];
int count=0;
//functions list:
void store_macro_name(FILE *fp);
void store_macro_body(FILE *fp);
void replace_macro(char word[],FILE *out);
void macro_replacement(FILE *fp,FILE *out);

void store_macro_name(FILE *fp){
    int ch,j=0;

    ch=fgetc(fp);
    while(ch==' ' || ch=='\t')
        ch=fgetc(fp);

    while(ch!=' ' && ch!='\t' && ch!='\n' && ch!=-1){
        macro_name[count][j++]=ch;
        ch=fgetc(fp);
    }
    macro_name[count][j]='\0';
}

void store_macro_body(FILE *fp){
    int ch,j=0;

    ch=fgetc(fp);
    while(ch==' ' || ch=='\t')
        ch=fgetc(fp);

    while(ch!=' ' && ch!='\t' && ch!='\n' && ch!=-1){
        macro_body[count][j++]=ch;
        ch=fgetc(fp);
    }
    macro_body[count][j]='\0';
    count++;
}

void replace_macro(char word[],FILE *out){
    char temp[100];
    int i,j,k,flag;

    i=0;
    while(word[i]!='\0'){
        if((word[i]>='A' && word[i]<='Z') ||
           (word[i]>='a' && word[i]<='z') ||
           (word[i]>='0' && word[i]<='9') ||
           word[i]=='_'){

            j=0;
            while((word[i]>='A' && word[i]<='Z') ||
                  (word[i]>='a' && word[i]<='z') ||
                  (word[i]>='0' && word[i]<='9') ||
                  word[i]=='_'){
                temp[j++]=word[i++];
            }
            temp[j]='\0';

            flag=0;
            for(k=0;k<count;k++){
                if(strcmp(temp,macro_name[k])==0){
                    fprintf(out,"%s",macro_body[k]);
                    flag=1;
                    break;
                }
            }

            if(flag==0)
                fprintf(out,"%s",temp);
        }
        else{
            fprintf(out,"%c",word[i]);
            i++;
        }
    }
}

void macro_replacement(FILE *fp,FILE *out){
    int ch,i;
    char word[100];

    while((ch=fgetc(fp))!=-1){

        if(ch=='#'){
            i=0;
            word[i++]=ch;
            ch=fgetc(fp);

            while(ch!=' ' && ch!='\t' && ch!='\n' && ch!=-1){
                word[i++]=ch;
                ch=fgetc(fp);
            }
            word[i]='\0';

            if(strcmp(word,"#define")==0){
                store_macro_name(fp);
                store_macro_body(fp);

                while(ch!='\n' && ch!=-1)
                    ch=fgetc(fp);
            }
            else{
                fprintf(out,"%s",word);
                if(ch!=-1)
                    fprintf(out,"%c",ch);
            }
        }
        else{
            i=0;

            while(ch!=' ' && ch!='\t' && ch!='\n' && ch!=-1){
                word[i++]=ch;
                ch=fgetc(fp);
            }

            word[i]='\0';
            replace_macro(word,out);

            if(ch!=-1)
                fprintf(out,"%c",ch);
        }
    }printf("Mcros replaced\n");
}
