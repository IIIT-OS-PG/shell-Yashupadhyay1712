#include<iostream>
#include<stdio.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<errno.h>
#include<vector>
#include<stdlib.h> 
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include "myrc.h"
#include<fstream>
using namespace std;

int cpipe(string s)
{
		char arr[s.size()+1];
		int l;
		for(l=0;l<s.size();l++)
			if(s[l]=='|')
				return 1;
			else continue;
		return 0;
}
int iodp(char *ar,string s)
{

		char a[s.size()+1];
		int i;
		for(i=0;i<s.size();i++)
			a[i]=s[i];
		a[i]='\0';
		char *t=strtok(a," ");
		char *args[1000];
		while (t != NULL)
		 { 
	        if(strcmp(t,">>")==0)
	        	return 2;
	        if(strcmp(t,">")==0)
	        	return 1;
	        t= strtok(NULL," "); 
		 }
		 return 0;
}

void ex(char *arr)
{
	
	char *token=strtok(arr," ");
	char *args[1000];
	char **temp=args;
	while (token != NULL)
	{ 
		*temp++=token;
		token = strtok(NULL," ");
	}
	*temp=NULL;
	int pid=fork();
	if(pid==0)
	{
		status=execvp(arr,args);
	    exit(0);
	}
	else
		wait(NULL);
}
void ioexec(char *arr)
{
	int i;
	i = open("myrc.txt",O_WRONLY | O_CREAT);
	int stdi = dup(1);
	dup2(i,1);
	char *token=strtok(arr,">");
	ex(token);
	dup2(stdi,1);
    close(i);  
}
void storeoutput(string s)
{
	int i,x;
	//cout<<filename;
	char arr[s.size()+1];
	for(x=0;x<s.size();x++)
		arr[x]=s[x];
	arr[x]='\0';
	i = open("scriptrecord.txt",O_WRONLY | O_APPEND);
	int stdi = dup(1);
	dup2(i,1);
	char *token=strtok(arr,">>");
	ex(token);
	dup2(stdi,1);
    close(i);
}
void ioexecd(char *arr)
{
	int i;
	//cout<<filename;
	i = open("myrc.txt",O_WRONLY | O_APPEND);
	int stdi = dup(1);
	dup2(i,1);
	char *token=strtok(arr,">>");
	ex(token);
	dup2(stdi,1);
    close(i);
}

// void expipe(string s)
// {
// 		char ar[s.size()+1];
// 		int l;
// 		for(l=0;l<s.size();l++)
// 			ar[l]=s[l];
// 		ar[l]='\0';
// 		char *token=strtok(ar,"|");
// 		char *args[1000];
// 		string h="";
// 		char **temp=args;
// 		while (token != NULL)
// 		{ 
//   			*temp++=token;
//   			h=token;
//   			token = strtok(NULL,"|");
// 		}
// }
