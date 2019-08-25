#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
int idflag=0, litsize=0;char lit[50][50];
int isKeyword(char buffer[]){
	char keywords[32][10] = {"auto","break","case","char","const","continue","default",
				"do","double","else","enum","extern","float","for","goto",
				"if","int","long","register","return","short","signed",
				"sizeof","static","struct","switch","typedef","union",
				"unsigned","void","volatile","while"};
	int i, flag = 0;
	
	for(i = 0; i < 32; ++i){
		if(strcmp(keywords[i], buffer) == 0){
			flag = 1;
			if(i==3 || i==8 || i==12 || i==16 || i==17 || i== 20)	{
				idflag=1;//printf("caught identifier\n");
			}
			break;
		}
	}
	
	return flag;
}

int isPreprocessor(char buffer[], int i){
	
	if(buffer[i]=='#'){
		printf("# is a special symbol\n");
		++i;
		while(isspace(buffer[i])) i++; // remove leading whitespaces
		while(buffer[i]!='<' && !(isspace(buffer[i]) ) ) { printf("%c",buffer[i]); ++i;}
		printf(" is a preprocessor directive\n");
		while(isspace(buffer[i])) i++; // remove leading whitespaces
		if(buffer[i]=='<'){
			printf("< is a special symbol\n");
			++i;
			while(buffer[i]!='>' && !(isspace(buffer[i]) ) ) { printf("%c",buffer[i]); ++i;}
			printf(" is a library\n");
			if(buffer[i]=='>')
			printf("> is a special symbol\n");
		}
		return 1;
	}else{
		return 0;
	}
	

}
int iscomment(char buffer[],int pos,FILE *fp){
	if(buffer[pos]=='/'){
		if(buffer[pos+1]=='/')
			return 1;
		else if(buffer[pos+1]=='*'){
			pos=pos+2;
			
	     		int len,flag=0;
		endcomment:len=strlen(buffer);
			if(flag==1)
				pos=0;
			while(pos<len){
				if(buffer[pos]=='*'){
					if(pos+1<len)
						if(buffer[pos+1]=='/')
						return 1;
				}
				else{
					++pos;
				}
			}
			if(fgets(buffer,100,fp)!=NULL)
				flag=1;
				goto endcomment;
			
		}
	}
	else
		return 0;
}

int isoperator(char ch,char a){
	switch(ch){
		case '+': if(a=='+'){ 
				printf("++ is an operator\n");
				return 1;
			  }
			  else{
			
				printf("+ is an operator\n");break;

			}
		case '-': printf("- is an operator\n");break;
		case '<': if(a=='='){ 
				printf("<= is an operator\n");
				return 1;
			  }
				else if(a=='<'){ 
				printf("<< is an operator\n");
				return 1;
			  }
			  else{
			
				printf("< is an operator\n");break;

			}
		case '>': if(a=='='){ 
				printf(">= is an operator\n");
				return 1;
			  }
			else if(a=='>'){ 
				printf(">> is an operator\n");
				return 1;
			  }
			  else{
			
				printf("> is an operator\n");break;

			}
		case '&': if(a=='&'){ 
				printf("&& is an operator\n");
				return 1;
			  }
			  else{
			
				printf("& is an operator\n");break;

			}
		case '|': if(a=='|'){ 
				printf("|| is an operator\n");
				return 1;
			  }
			  else{
			
				printf("| is an operator\n");break;

			}
		case '/': if(a=='/'){ 
				//printf(">= is an operator\n");
				return 2;
			  }
			  else{
			
				printf("/ is an operator\n");break;

			}
		case '=': if(a=='='){ 
				printf("== is an operator\n");
				return 1;
			  }
			  else{
			
				printf("= is an operator\n");break;

			}
		case '*': printf("* is an operator\n");break;
		case '%': printf("% is an operator\n");break;
		case '?': printf("? is an operator\n");break;
		case ':': printf(": is an operator\n");break;
		case '^': printf("^ is an operator\n");break;
		


	}
	return 0;
		
}

void split(char buffer[],int pos,int len){
	char temp[50];
	
	while(pos<len){
		int i=0;
		while(pos<len && buffer[pos]!='(' && buffer[pos]!='<' && buffer[pos]!=',' && buffer[pos]!='+' && buffer[pos]!='-' && buffer[pos]!='*' && buffer[pos]!='/' && buffer[pos]!=')' && buffer[pos]!='=' & buffer[pos]!='[' 
                       && buffer[pos]!=']' && buffer[pos]!='{'&& buffer[pos]!='}' && buffer[pos]!=';' && buffer[pos]!=','&& !( isspace( buffer[pos] ) )   ){

			temp[i]=buffer[pos];
			++i; ++pos;
		}
		temp[i]='\0';
		if(isKeyword(temp)){
			printf("%s is a keyword\n",temp);
		}
		else{
			if(strlen(temp)>=1){
				int i=0;
				while(isspace(temp[i])) i++;
				while(isspace(buffer[pos])) pos++;
				if(temp[0]=='"'){
					printf("\" is a symbol\n");
					strcpy(temp,"");
					while(buffer[pos]!='"' && pos<len){
						temp[i]=buffer[pos];
						++i; ++pos;

					}
					temp[i]='\0';
					printf("%s is a literal\n",temp);
					printf("\" is a symbol\n");
					++pos;
					continue;
				}
				else if(temp[0]==','){
					printf(", is a symbol\n");

					char t[20]; int i=0;
					pos++;
					while(isalnum(buffer[pos]) ){
						t[i]=buffer[pos];
						++i;++pos;
					}
					t[i]='\0';
					printf("%s is an identifier\n",t);
					isoperator(buffer[pos+1],'\0');
					--pos;
					

				}
				else if(temp[0]=='/' && temp[1]=='/'){
					pos=len;continue;


				}//else{	printf("hi%chi\n",buffer[pos-2]);
					
				//}
				if(idflag){//printf("Entered\n");
					strcpy(lit[litsize++],temp);
					idflag=0;printf("%s\n",lit[litsize-1]);
					printf("%s is literal\n",temp);
				}else{	

					int fflag=0;
					for(int i=0;i<litsize;++i){
						if(strcmp(lit[i],temp)==0){
							fflag=1;
							break;
						}
					
					}
					if(fflag)
						printf("%s is a valid identifier\n",temp);
					else{
						int flag=1;
						for(int i=0;i<strlen(temp);i++){
							if(!isdigit(temp[i])){
								flag=0;
								break;
							}
						}
						if(flag)
							printf("%s is a constant\n",temp);
						else if(strcmp(temp,"printf")==0)
							printf("%s is a literal",temp);
						else
							printf("%s is an invalid identifier\n",temp);
				
					}
				}
			}
				int flag=isoperator(buffer[pos],buffer[pos+1]);
				//printf("hi%chi\n",buffer[pos]);
					if(flag==1) ++pos;
					else if(flag==2) pos=len;
			strcpy(temp,"");
		}
		
		switch(buffer[pos]){
			case '(': printf("( is a symbol\n");break;
			case ')':	printf(") is a symbol\n");break;
			case '{': printf("{ is a symbol\n");break;
			case '}':	printf("} is a symbol\n");break;
			case ';':	printf("; is a symbol\n");break;
			//case '=':	printf("= is an operator\n");break;
			case ',':	printf(", is a symbol\n");
					
					break;

		}
		++pos;
	}

}


void main(){
	char buffer[100];
	FILE *fp;
	fp=fopen("test","r");
	//read line
	while(fgets(buffer,100,fp)!=NULL){	
		int len=strlen(buffer), i=0;
		while(isspace(buffer[i])) i++; // remove leading whitespaces
		
		if(isPreprocessor(buffer,i))
			continue;
		if(iscomment(buffer,i, fp)){
			printf("comment\n");
			continue;
		}
		split(buffer,i,len);
	}

}
