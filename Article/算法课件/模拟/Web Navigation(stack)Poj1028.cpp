#include<iostream>
#include<string>
#include<stack>

using namespace std;

stack<string> forwardStack,backwardStack;

int main()
{
	string comm;
	string curUrl("http://www.acm.org/");

	while(comm.compare("QUIT"))
	{
		cin>>comm;
		if(comm.compare("VISIT")==0)
		{
			backwardStack.push(curUrl);
			cin>>curUrl;
			cout<<curUrl<<endl;
			while(!forwardStack.empty())
            {
                forwardStack.pop();
            }
		}
		if(comm.compare("BACK")==0)
		{
			if(backwardStack.empty())
				cout<<"Ignored"<<endl;
			else
			{
				forwardStack.push(curUrl);
				curUrl = backwardStack.top();
				backwardStack.pop();
				cout<<curUrl<<endl;
			}
		}
		if(comm.compare("FORWARD")==0)
		{
			if(forwardStack.empty())
				cout<<"Ignored"<<endl;
			else
			{
				backwardStack.push(curUrl);
				curUrl = forwardStack.top();
				forwardStack.pop();
				cout<<curUrl<<endl;
			}
		}
	}
	return 0;
}

