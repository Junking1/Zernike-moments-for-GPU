#include "read_save_file.h"

#include <stdlib.h>
#include <stdio.h>

#include <string.h>

char * GetIniKeyString( char *title, char *key, char *filename) 
{ 
	FILE *fp; 
	char szLine[1024];
	static char tmpstr[1024];
	int rtnval;
	int i = 0; 
	int flag = 0; 
	char *tmp;

	if((fp = fopen(filename, "r")) == NULL) 
	{ 
		printf("have   no   such   file \n");
		return (char*)""; 
	}
	while(!feof(fp)) 
	{ 
		rtnval = fgetc(fp); 
		if(rtnval == EOF) 
		{ 
			break; 
		} 
		else 
		{ 
			szLine[i++] = rtnval; 
		} 
		if(rtnval == '\n') 
		{ 

	

			szLine[--i] = '\0';
			i = 0; 
			tmp = strchr(szLine, '='); 

			if(( tmp != NULL )&&(flag == 1)) 
			{ 
				if(strstr(szLine,key)!=NULL) 
				{ 
					//×¢ÊÍÐÐ
					if ('#' == szLine[0])
					{
					}
					else if ( '/' == szLine[0] && '/' == szLine[1] )
					{
						
					}
					else
					{
						//ÕÒŽòkey¶ÔÓŠ±äÁ¿
						strcpy(tmpstr,tmp+1); 
						fclose(fp);
						return tmpstr; 
					}
				} 
			}
			else 
			{ 
				strcpy(tmpstr,"["); 
				strcat(tmpstr,title); 
				strcat(tmpstr,"]");
				if( strncmp(tmpstr,szLine,strlen(tmpstr)) == 0 ) 
				{
					//ÕÒµœtitle
					flag = 1; 
				}
			}
		}
	}
	fclose(fp); 
	return (char *)""; 
}

int GetIniKeyInt(  char *title, char *key, char *filename)
{
	return atoi(GetIniKeyString(title,key,filename));
}
//float////////////////////////////////////////////////////////
float GetIniKeyFloat( char *title, char *key, char *filename)
{
        return atof(GetIniKeyString(title,key,filename));
}


void GetIntData(char * filename , int * data , int length )
{
   FILE * fp;
   char bstr[20];

   fp =fopen(filename,"r");
	if(fp==NULL)
	{
		printf("file %s \n find int file err!\n", filename);
		return ;
	}
  for(int i =0;i<length;i++)
     {    
      fgets(bstr,20,fp);
      bstr[strlen(bstr)]='\0';
      data[i]=atoi(bstr);
     } 
  fclose(fp);
}

void GetUnsignedShortData(char * filename , unsigned short * data , int length)
{
    FILE * fp;
    char bstr[20];

    fp =fopen(filename,"r");
	if(fp==NULL)
	{
		printf("file %s \n find ushort file err!\n", filename);
		return ;
	}
   for(int i =0;i<length;i++)
      {
       fgets(bstr,20,fp);
       bstr[strlen(bstr)]='\0';
       data[i]=atoi(bstr);
      }
   fclose(fp);
}

void GetFloatData(char * filename , float * data , int length )
{
   FILE * fp;
   char bstr[20];

   fp =fopen(filename,"r");
	if(fp==NULL)
	{
		printf("file %s \n find float file err!\n", filename);
		return ;
	}
  for(int i =0;i<length;i++)
     {    
      fgets(bstr,20,fp);
      bstr[strlen(bstr)]='\0';
      data[i]=atof(bstr);
     } 
  fclose(fp);
}

void GetDoubleData(char * filename , double * data , int length )
{
   FILE * fp;
   char bstr[20];

   fp =fopen(filename,"r");

   if(fp==NULL)
	{
		printf("file %s \n find double file err!\n", filename);
		return;
	}

  for(int i =0;i<length;i++)
     {
      fgets(bstr,20,fp);
      bstr[strlen(bstr)]='\0';
      data[i]=atof(bstr);
     }
  fclose(fp);
}

void GetBinaryDate(char * filename, void * data, int size, int length)
{
	FILE * fp;
	fp = fopen(filename,"rb");
	if(fp==NULL)
	{
		printf("file %s \n find binary file err!\n", filename);
		return ;
	}
	fread(data, size, length, fp);
}


void SaveIntData(char * filename, int *data,int length)
{
	FILE * fp;
	fp = fopen(filename,"w");
	if(fp==NULL)
	{
		printf("file %s \n save int file err!\n", filename);
		return ;
	}
	for(int i=0;i<length;i++)
	{
		fprintf(fp,"%d\n",data[i]);
	}
	fclose(fp);
}
void SaveFloatData(char *filename,float *data,int length)
{
	FILE * fp;
	fp = fopen(filename,"w");
	if(fp==NULL)
	{
		printf("file %s \n save float file err!\n", filename);
		return ;
	}
	for(int i=0;i<length;i++)
	{
		fprintf(fp,"%f\n",data[i]);
	}

	fclose(fp);
}

void SaveUnsignedShortData(char *filename,unsigned short *data,int length)
{
	FILE * fp;
	fp = fopen(filename,"w");
	if(fp==NULL)
	{
		printf("file %s \n save ushort file err!\n", filename);
		return ;
	}
	for(int i=0;i<length;i++)
	{
		fprintf(fp,"%d\n",data[i]);
	}

	fclose(fp);
}

void SaveDoubleData(char *filename,double *data,int length)
{
	FILE * fp;
	fp = fopen(filename,"w");
	if(fp==NULL)
	{
		printf("file %s \n save double file err!\n", filename);
		return ;
	}
	for(int i=0;i<length;i++)
	{
		fprintf(fp,"%f\n",data[i]);
	}

	fclose(fp);
}

void SaveBinaryDate(char * filename, void * data, int size,int length)
{
	FILE * fp;
	fp = fopen(filename,"wb");
	if(fp==NULL)
	{
		printf("file %s \n open binary file err!\n", filename);
		return ;
	}

		fwrite(data,size,length, fp);
		fclose(fp);

}










