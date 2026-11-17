#include"header.c"
extern void comment_removal(FILE *fp,FILE *out){
	int ch,prev=0,slash=0;
	int single=0,multi=0; // flags
	while((ch=fgetc(fp))!=-1){
		if(single){ // inside // comment
			if(ch=='\n'){   // comment ends at end of line
				single=0;
				fputc('\n',out); // keep the line break
			}
		}
		else if(multi){  // inside /* */ comment
			if(ch=='\n')
				fputc('\n',out);// keep line structure
			if(prev=='*' && ch=='/'){// */ found, comment over
				multi=0;
				ch=0;
			}
			prev=ch;
		}
		else{  // normal code
			if(slash){ // previous char was a '/' (not written yet)
				slash=0;
				if(ch=='/'){ // // found
					single=1;
					continue;
				}
				else if(ch=='*'){ // /* found
					multi=1;
					prev=0;
					fputc(' ',out);
					continue;
				}
				else fputc('/',out);// it was only a divide, write it now
			}
			if(ch=='/') slash=1;  // wait for next char before writing
			else fputc(ch,out);
		}
	}
	printf("Comments removed\n");
}
