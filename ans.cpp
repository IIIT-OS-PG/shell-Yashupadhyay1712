#include<iostream>
#include<stdio.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<errno.h>
#include<vector>
#include<string>
#include<stdlib.h> 
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<fstream>
#include "iodir.h"
using namespace std;
fstream fin,f,fr;
int frecord=0;
void pipel(string s)
{
		char ar[s.size()+1];
		int i;
		for(i=0;i<s.size();i++)
			ar[i]=s[i];
		ar[i]='\0';
		i=0;
		int argco=1;
		char *token=strtok(ar," ");
		char *args[1000];
		char **temp=args;
		while (token != NULL)
			 { 
		        *temp++=token;
		        if(argco>2)
		        h=h+token+" ";
		        argco++;
		        token = strtok(NULL," "); 
			 }
		 *temp=NULL;
		 if(fork()==0)
		 status=execvp(ar,args);
		 wait(NULL);
}

int parse(string s)
{
		
		char ar[s.size()+1];
		int i;
		for(i=0;i<s.size();i++)
			ar[i]=s[i];
		ar[i]='\0';
		i=0;
		int argco=1;
		char *token=strtok(ar," ");
		char *args[1000];
		char **temp=args;
		string chk=token,h="";
		string r=searchalias(chk);
		if(r!="NULL")
		{
			int k=parse(r);
			if(k==0)
				return 0;	
		}
		else
		{		
			while (token != NULL)
			 { 
		        *temp++=token;
		        if(argco>2)
		        h=h+token+" ";
		        argco++;
		        token = strtok(NULL," "); 
			 }
			 *temp=NULL;
			
	   		if(chk=="cd")
			{
				if(*args[1]=='~'||(argco==2))
					{
						chdir("/home");
					}
				else
					chdir(args[1]);
				return 1;
			}
			else if(chk=="alias")
			{
				alias(args[1],h);
				return 1;
			}
			else if(chk=="open")
			{
				string runnow=runapp(s);
				if(runnow!="NULL")
				{
					int w;
					string app=s.substr(5);
					runnow=runnow+app;
					cout<<runnow;
					char ay[runnow.size()+1];
					for(w=0;w<runnow.size();w++)
						ay[w]=runnow[w];
					ay[w]='\0';
					w=0;
					char *tokn=strtok(ay," ");
					char *ags[1000];
					char **tmp=ags;
					while (tokn != NULL)
					 { 
				        *tmp++=tokn;
				        tokn = strtok(NULL," "); 
					 }
					 *tmp=NULL;
					if(fork()==0)
						{
							status=execvp(ay,ags);
							exit(0);
						}
					else wait(NULL);
				}
				return 1;
			}
			else if(chk=="exit")
			{
				cout<<"******   Bye Visit Again    *******\n";
				return 0;
			}
			else if(chk=="history")
			{
				string str;
				int i=0;
				
				f.open("myshellhistory.txt",ios::in);
				while(getline(f,str))
				{
					cout<<i++<<str<<"\n";
				}
				f.close();
				return 1;				
			}
			else if(chk=="$?")
			{
				if(status==0)
					cout<<"0: command not found";
				else
					cout<<"0: command not found";
				return 1;
			}	
			else if(chk=="echo")
			{
				int sr,po,flg=0;
				string snew="";
				for(sr=0;sr<s.size();sr++)
				{
					if(s[sr]=='$')
					{
						flg=1;
						break;
					}
				}
				if(flg)
				{
					if(s[sr+1]=='$')
					{
						cout<<getpid();
						return 1;
					}
					
					snew=s.substr(sr+1);
					char astr[snew.size()+1];
					for (po = 0; po < snew.size(); ++po)
					{
						if(snew[po]==' ')
							{
								snew[po]='\0';
								break;
							}
					}
					cout<<searchalias(snew);
					return 1;

				}
			}	 
			int pid=fork();
			if(pid==0)
			{
				//cout<<status<<"\n";
				status=execvp(ar,args);
				//cout<<status<<"\n";
			    exit(0);
			}
			else
				wait(NULL);
		}
		return 1;
}
int run(string s)
{
	    char arr[1]={0};
	    int r=iodp(arr,s);
	    int i;
	    char ar[s.size()+1];
			for(i=0;i<s.size();i++)
			ar[i]=s[i];
			ar[i]='\0';
		if(r==2)
		{
			ioexecd(ar);
			return 0;
		}
		else
		if(r==1)
		{
			ioexec(ar);
			return 0;
		}
		else 
		{

			return 1;
		}
}
int main()
{
	string s;
	shell sh;
	cout<<"<*******    WELCOME TO MY SHELL   ********>\n";
	while(1)
	{
		char cwd[1000];
		int i;
		getcwd(cwd,sizeof(cwd));
		string tilde="/home/yash";
		cout<<"\nyash@Yash:"<<cwd<<" "<<ps1<<" ";
		getline(cin,s);
		if(s=="record start")
			{
				frecord=1;
				continue;
			}
		else if(s=="record stop")
			{
				frecord=0;
				continue;
			}
		char arr[s.size()+1];
		int q=0;
		while(s[q]==' '){
			q++;
		}
		s=s.substr(q);

		for(i=0;i<s.size();i++)
			arr[i]=s[i];
		arr[i]='\0';
		
		if(frecord)
		{
			fr.open("scriptrecord.txt",ios :: app);
			fr<<s<<"\n";
			fr.close();
			string snew=s+" >> ";	
			storeoutput(s);
		}

		fin.open("myshellhistory.txt",ios :: app);
		fin<<s<<"\n";
		fin.close();


		//pipe work
		if(cpipe(s)==1)
		{
			vector<string> vc;
			string str="";
			for (int i = 0; i < s.size(); ++i)
			{
				if(s[i]!='|')
					str+=s[i];
				else if(s[i]=='|')
				{
					vc.push_back(str);
					str="";
					while(s[i+1]==' ')
					{
						i++;
					}
				}
			}
			vc.push_back(str);
			int f,x;int p[2];
			for ( f = 0; f< vc.size()-1; ++f)
			{
				if (pipe(p) < 0) 
    			exit(1);
    			x=dup(1);
				char ar[vc[f].size()+1];
				int i;
				string  st=vc[f];
				for(i=0;i<st.size();i++)
					ar[i]=st[i];
				ar[i]='\0';
				i=0;
				int argco=1;
				char *token=strtok(ar," ");
				char *args[1000];
				char **temp=args;
				string chk=token,h="";
				while (token != NULL)
				 { 
			        *temp++=token;
			        token = strtok(NULL," "); 
				 }
				 *temp=NULL;
					
				int pid=fork();

				if(pid==0)
				{
					dup2(p[1],1);
					close(p[0]);
					status=execvp(ar,args);
				    abort();
				}
				wait(NULL);
				dup2(p[0],0);
				close(p[1]);
			}			
			int r=iodp(arr,vc[f]); 
			char ar[vc[f].size()+1];
			for(i=0;i<vc[f].size();i++)
			ar[i]=s[i];
			ar[i]='\0';
			if (r==2)
				{
					if(fork()==0)
					{
						char *token=strtok(ar,">");
						char *args[1000];
						char **temp=args;
						*temp++=token;
						*temp=NULL;
						x=open("myrc.txt",O_WRONLY | O_APPEND);
						dup2(p[1],x);
						status=execvp(ar,args);
						exit(0);
					}
					else
					wait(NULL);
					dup2(x,0);
					continue;
				}
			if (r==1)
				{
					ioexec(ar);
					dup2(x,0);
					continue;
				}
			else
				{
				pipel(vc[f]);
				dup2(x,0);
				continue;
				}
		
		}

		//for redirection
		int r=iodp(arr,s);
		if(r==2)
		{
			char ar[s.size()+1];
			for(i=0;i<s.size();i++)
			ar[i]=s[i];
			ar[i]='\0';
			int p;
			for(p=0;p<s.size();p++)
			{
				if(s[p]=='>'&& s[p+1]==' ')
					break;
			}
			string filename=s.substr(p+2);
			ioexecd(ar);
			continue;
		}
		else
		if(r==1)
		{
			char ar[s.size()+1];
			for(i=0;i<s.size();i++)
			ar[i]=s[i];
			ar[i]='\0';
			ioexec(ar);
			continue;
		}
		int cont=parse(s);
			if(cont==0)
				break;
	}
	return 0;
}