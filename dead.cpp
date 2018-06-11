#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
void fancyText(string);
char* convertToCharArray(string);

/*int main(){
	string d = "Hello, it's me";
	string m = "I was wondering if after all these years you'd like to meet";
	
	fancyText(d);
	fancyText(m);
}*/

char* convertToCharArray(string s){
	int n = s.length();
	static char t[100];

	strcpy(t , s.c_str());
	return t;
}


void fancyText(string s, bool end){
	int b = s.length();
	int i;
	char *p;
	char m1[b+1];
	p = convertToCharArray(s);

	for(i = 0; i < b; i++)
	{
		m1[i] = *(p + i);
	}
	for(int i = 0; i<b ; i++){
		cout<<m1[i]<<flush;
		usleep(50000);
	}
	if(end == true)
		cout<<endl;

}