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
// #include "myrc.h"
#include<fstream>
#include "iodir.h"
using namespace std;

int parse(string s)
{
		
		char ar[s.size()+1];
		int i;
		fstream fin,f;
		fin.open("myshellhistory.txt",ios :: app);

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
			// cout<<r<<"lk";
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
		        // *temp=token;
		        argco++;
		        token = strtok(NULL," "); 
			 }
			 *temp=NULL;
			fin<<s<<"\n";
			fin.close();
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
				//cout<<args[1]<<" "<<h;
				alias(args[1],h);
				return 1;
			}
			else if(chk=="exit")
			{
				cout<<"Bye Visit Again\n";
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
		 
			int pid=fork();
			if(pid==0)
			{
				execvp(ar,args);
			    exit(0);
			}
			else
				wait(NULL);
		}
		// 
		// f.open("myshellhistory.txt");
		// dup(f,'1');
		// f.close();
			
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
			//cout<<"1";
			ioexecd(ar);
			return 0;
		}
		else
		if(r==1)
		{
			//cout<<"\tfjf"<<arr;
			//cout<<"2";
			ioexec(ar);
			return 0;
			// continue;
		}//cout<<"11";
		else 
			{

				return 1;
			}
}
int main()
{
	string s;
	shell sh;
	
	while(1)
	{
		char cwd[1000];
		int i;
		getcwd(cwd,sizeof(cwd));
		string tilde="/home/yash";
		cout<<"yash@Yash:"<<cwd<<" "<<ps1<<" ";
		getline(cin,s);
		char arr[s.size()+1];
		for(i=0;i<s.size();i++)
			arr[i]=s[i];
		arr[i]='\0';
		// cout<<arr<<"\n";
		cout<<"***********\n";
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
					vc.push_back(str);str="";
					while(s[i+1]==' ')
					{
						i++;
					}
				}
			}
			vc.push_back(str);
			//cout<<"***********"<<vc.size()<<"\n";
				// cout<<run(vc)
			// if(run(vc[i]))
			// {
					int p[2];
					if (pipe(p) < 0) 
        			exit(1);
        			int x=dup(1);
        			
        			int f;
					for ( f = 0; f< vc.size()-1; ++f)
					{
						//cout<<vc[f]<<" \n";
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
						        // if(argco>2)
						        // h=h+token+" ";
						        // // *temp=token;
						        // argco++;
						        token = strtok(NULL," "); 
							 }
								 *temp=NULL;
								
							int pid=fork();

							if(pid==0)
							{
								dup2(p[1],1);
								execvp(ar,args);
							    exit(0);
							}
							else
							{
								
								wait(NULL);
								dup2(p[0],0);
							}
					}
					close(p[1]);
					
					parse(vc[f]);
					dup2(x,0);
					continue;
			// }
		}

			int r=iodp(arr,s);
			if(r==2)
			{
				// cout<<"\tfjf"<<arr;
				char ar[s.size()+1];
				for(i=0;i<s.size();i++)
				ar[i]=s[i];
				ar[i]='\0';
				ioexecd(ar);
				continue;
			}
			else
			if(r==1)
			{
				//cout<<"\tfjf"<<arr;
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









		// char ar[s.size()+1];
		// int i;
		// // shell shl;
		// for(i=0;i<s.size();i++)
		// 	ar[i]=s[i];

		// ar[i]='\0';
		// i=0;
		// char *token=strtok(ar," ");
		// char *args[1024];
		// char **temp=args;
		// string chk=token,h="";
		// string r=searchalias(chk);
		// if(r!="NULL")
		// {
		// 	int k=parse(r);
			
		// }
		// else
		// {		
		// 	while (token != NULL)
		// 	 { 
		//         *temp++=token;
		//         h+=token;
		//         token = strtok(NULL," "); 
		//         //chk =token;
		// 	 }
		// 	// fout<<"\n"<<h<<"\n";
	 //   		*temp = NULL;
	 //   		if(chk=="cd")
		// 	{
		// 		chdir(args[1]);
		// 		return 1;
		// 	}
		// 	if(chk=="exit")
		// 	{
		// 		return 0;
		// 	}
		// 	// if(chk=="history")
		// 	// {
		// 	// 	string str;
		// 	// 	int i=0;
		// 	// 	// fout.close();
		// 	// 	// cout<<"vbkt";
		// 	// 	while(getline(fin,str))
		// 	// 	{
		// 	// 		cout<<i++<<str<<"\n";
		// 	// 	}
		// 	// 	// fin.close();
		// 	// 	continue;
		// 	// }
	
		// 	int pid=fork();
		// 	if(pid==0)
		// 		{
		// 			execvp(ar,args);
		// 		    exit(0);
		// 		}
		// 	else
		// 		wait(NULL);
		// }		
		// return 1;


// void token(string s)
// {
// 		char ar[s.size()+1];
// 		int i;
// 		fstream fin,f;
// 		fin.open("myshellhistory.txt",ios :: app);

// 		for(i=0;i<s.size();i++)
// 			ar[i]=s[i];
// 		ar[i]='\0';
// 		i=0;
// 		int argco=1;
// 		char *token=strtok(ar," ");
// 		char *args[1000];
// 		char **temp=args;
// 		string chk=token,h="";
// 		string r=searchalias(chk);
// 		if(r!="NULL")
// 		{
// 			cout<<r<<"lk";
// 			//int k=parse(r);
// 			// if(k==0)return 0;
			
// 		}
// 		else
// 		{		
// 			while (token != NULL)
// 			 { 
// 		        *temp++=token;
// 		        if(argco>2)
// 		        h=h+token+" ";
// 		        // *temp=token;
// 		        argco++;
// 		        token = strtok(NULL," "); 
// 			 }
// 			fin<<s<<"\n";
// 			fin.close();

// }
// }

//ye pi ==0 wla
//int rd=chkrd(s);
		// cout<<rd<<"  "<<s<<"  ";
		// if(rd==1)
		// {
		// 	int pi=fork();
		// 	if(pi==0)
		// 	{
		// 		char ar[s.size()+1];
		// 		int i,j;
		// 		// fstream fin,f;
		// 		// fin.open("myshellhistory.txt",ios :: app);
		// 		// j=open("file.txt", O_WRONLY | O_RDONLY);
		// 		// dup2(j,1);
		// 		for(i=0;i<s.size();i++)
		// 			ar[i]=s[i];
		// 		ar[i]='\0';
		// 		i=0;
		// 		int argco=1;
		// 		char *token=strtok(ar,">");
		// 		char *args[1000];
		// 		char **temp=args;
		// 		// if(strcmp(token,"NULL")!=0)
		// 		cout<<token<<" ";
		// 		// for(int k=0;)
		// 		string s=token;
		// 		i=parse(s);i=0;
		// 		//cout<<token<<" ";
		// 	    //token = strtok(NULL," ");
		// 	    // cout<<token; 
		// 		exit(0);
		// 	}
		// 	else wait(NULL);	
		// }
// int chkrd(string s)
// {
// 		char ar[s.size()+1];
// 		int i;
// 		// fstream fin,f;
// 		// fin.open("myshellhistory.txt",ios :: app);

// 		for(i=0;i<s.size();i++)
// 			ar[i]=s[i];
// 		ar[i]='\0';
// 		i=0;
// 		int argco=1;
// 		char *token=strtok(ar," ");
// 		char *args[1000];
// 		char **temp=args;

// 		while (token != NULL)
// 			 { 
// 		        *temp++=token;
// 		        if(strcmp(token,">")==0)
// 		        	{
// 		        		i=1;
// 		        		break;
// 		        	}
// 		        token = strtok(NULL," "); 
// 			 }
// 			 return i;
// }