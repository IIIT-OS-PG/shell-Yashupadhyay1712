#include<iostream>
#include<string>
#include<unistd.h>
#include<vector>
using namespace std;
string ps1="~~>",ps2="!!",e="exit",h="history",ll="ls -alf",c="clear",egrep="egrep --color=auto",la="ls -A",l="ls -CF",grep="grep --color=auto",fgrep="fgrep --color=auto";

//for aliases
vector<pair<string,string>>v;

//for application connection
vector<pair<string,string>>app;

int initial,status;

string PATH="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin", HOME="/home/yash";

string runapp(string s)
{
	int sz,q;
	for(q=0;q<s.size();q++)
	{
		if(s[q]=='.')
			break;
	}
	string x=s.substr(q);
	// cout<<x;
	for (auto it = app.begin(); it != app.end(); ++it)
	{
		if (it->first == x)
			{
				// cout<<x;
				return it->second;
			}
	}
	return "NULL";
}
void alias(string s,string r)
{
	int f=0,c= 0;
	for (auto it = v.begin(); it != v.end(); ++it)
    {
    	  c++;
	      if (it->first == s)
	      {
	       if(c>initial)
	        {
	       	it->second=r;
	       	}
	      f=1;
	      break;
	      }
    }
	if(f==0)
	{
		v.push_back(make_pair(s,r));
	}
}
string searchalias(string c)
	{
		for (auto it = v.begin(); it != v.end(); ++it)
	    {
	      if (it->first == c)
	      {
	        string f=it->second;
	        return f;
	      }
	    }
	    return "NULL";
	}
class shell
{
public:
	shell()
	{
		v.push_back(make_pair("PATH",PATH));
		v.push_back(make_pair("HOME",HOME));
		v.push_back(make_pair("h",h));
		v.push_back(make_pair("ll",ll));
		v.push_back(make_pair("c",c));
		v.push_back(make_pair("l",l));
		v.push_back(make_pair("la",la));
		v.push_back(make_pair("e",e));
		app.push_back(make_pair(".mp4","vlc "));
		app.push_back(make_pair(".webm","vlc "));
		app.push_back(make_pair(".mp3","vlc "));
		app.push_back(make_pair(".wav","vlc "));
		app.push_back(make_pair(".mpjpeg","vlc "));
		app.push_back(make_pair(".txt","subl "));
		app.push_back(make_pair(".cpp","subl "));
		app.push_back(make_pair(".c","subl "));
		app.push_back(make_pair(".h","subl "));
		app.push_back(make_pair(".pdf","libreoffice "));
		initial=v.size();
	}	
};