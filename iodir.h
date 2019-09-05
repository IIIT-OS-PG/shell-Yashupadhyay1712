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
			arr[l]=s[l];
		arr[l]='\0';
		char *token=strtok(arr," ");
		char *args[1000];
		//char **temp=args;
		// cout<<"btmb";
		// if(s.find(" | "))
		// 	return 1;
		while (token != NULL)
		 { 
	        //*temp++=token;
	        if(strcmp(token,"|")==0)
	        	return 1;
	        token = strtok(NULL," "); 
		 }
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
		cout<<token<<"\t";
		*temp++=token;
		token = strtok(NULL," ");
	}
	*temp=NULL;

	int pid=fork();
	if(pid==0)
		{
			execvp(arr,args);
		    exit(0);
		}
	else
		wait(NULL);
}
void ioexec(char *arr)
{
	int i;
    //cout<<arr<<"\n";
	i = open("myrc.txt",O_WRONLY | O_CREAT);
	int stdi = dup(1);
	dup2(i,1);
	//cout<<arr<<"\n";
	char *token=strtok(arr,">");
	//cout<<token<<"vfv";
	ex(token);
	dup2(stdi,1);
    close(i); 
	 // 
}
void ioexecd(char *arr)
{
	int i;
	i = open("myrc.txt",O_WRONLY | O_APPEND);
	int stdi = dup(1);
	dup2(i,1);
	//cout<<arr<<"\n";
	char *token=strtok(arr,">>");
	//cout<<token<<"vfv";
	ex(token);
	dup2(stdi,1);
    close(i);

}

void expipe(string s)
{
		char ar[s.size()+1];
		int l;
		for(l=0;l<s.size();l++)
			ar[l]=s[l];
		ar[l]='\0';
		char *token=strtok(ar,"|");
		char *args[1000];
		string h="";
		char **temp=args;
		while (token != NULL)
		 { 
	  			*temp++=token;
	  			h=token;
	  			// vc.push_back(token);
		 // 	s=token;
		 // 	for(l=0;l<s.size();l++)
			// token[l]=s[l];
			// token[l]='\0';
	  //       
	  			// int r=iodp(ar,h);
	  			// cout<<r<<" "<<token;
	  	// 		if(r==2)
				// {
				// 	// cout<<"\tfjf"<<arr;
				// 	char a[h.size()+1];
				// 	int i;
				// 	for(i=0;i<h.size();i++)
				// 	a[i]=h[i];
				// 	a[i]='\0';
				// 	ioexecd(a);
				// 	// continue;
				// }
				// else
				// if(r==1)
				// {
				// 	//cout<<"\tfjf"<<arr;
				// 	char ar[h.size()+1];
				// 	int i;
				// 	for(i=0;i<h.size();i++)
				// 	ar[i]=h[i];
				// 	ar[i]='\0';
				// 	ioexec(ar);
				// 	// continue;
				// }
	  			token = strtok(NULL,"|");
			}
			// cout<<vc[vc.size()-1];			// cout<<token;
	  //       token = strtok(NULL,"|"); 
		 
		 // int f=0;
		 // while(*args[f]!=NULL)
		 // {
		 // // 	

}
