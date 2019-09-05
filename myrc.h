#include<iostream>
#include<string>
#include<unistd.h>
#include<vector>
using namespace std;
string ps1="~~>",ps2="!!",e="exit",h="history",ll="ls -alf",c="clear",egrep="egrep --color=auto",la="ls -A",l="ls -CF",grep="grep --color=auto",fgrep="fgrep --color=auto";
vector<pair<string,string>>v;


int initial;
// string path="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin", home="/home/yash";
void alias(string s,string r)
{
	int f=0,c= 0;
	for (auto it = v.begin(); it != v.end(); ++it)
    {
    	c++;
    	//cout<<c<<" "<<initial;
      if (it->first == s)
      {
       if(c>initial)
        {
       	it->second=r;
       	//cout<<r;
               // return f;
        }
      f=1;
      break;
      }
    }
	if(f==0)
	{
		v.push_back(make_pair(s,r));
		initial;
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
		v.push_back(make_pair("h",h));
		v.push_back(make_pair("ll",ll));
		v.push_back(make_pair("c",c));
		v.push_back(make_pair("l",l));
		v.push_back(make_pair("la",la));
		// v.push_back(make_pair("grep",grep));e
		// v.push_back(make_pair("fgrep",fgrep));		
		// v.push_back(make_pair("egrep",egrep));
		v.push_back(make_pair("e",e));
		initial=v.size();
	}
	
	// string alias(string str)
	// {
	// 	if(str == ll)
	// 		return "ls -l";
	// }
	// string searchalias(string c)
	// {
		// for (auto it = v.begin(); it != v.end(); ++it)
	 //    {
	 //      if (it->first == c)
	 //      {
	 //        string f=it->second;
	 //        return f;
	 //      }
	 //    }
	 //    return NULL;
	// }
};