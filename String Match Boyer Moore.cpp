#include<bits/stdc++.h>
using namespace std;

vector<string> readPage(int pgno){
	vector<string> lines;	
	string filename;
	char linesin[1000][1000];
	if(pgno<=9){
	filename = "page_1.txt";
	filename[5]='0'+pgno;}
	else{
	filename = "page_10.txt";
	filename[5]='0'+ pgno/10;
	filename[6]='0'+ pgno%10;}
	int k=0;
	ifstream ifile;
	ifile.open(filename.c_str(), ios::in);
	if(!ifile){
		cout<<"File "<<filename<<" not opened properly!";
		return lines;
	}
	
	while(ifile.getline(linesin[k], 1000)){
		lines.push_back(linesin[k]);
		k++;
	}
	ifile.close();
	return lines;
}
 
void preprocess1( string word, int size, int parray[256])
{
    int i;
    // Initialize all occurrences as -1
    for (i = 0; i < 256; i++)
         parray[i] = -1;
    // Fill the actual value of last occurrence of a character
    for (i = 0; i < size; i++)
         parray[(int) word[i]] = i;
}

void BMSearch( string word,  string lines, int lineno,int pgno,int &flag)
{
    int m = word.size();
    int n = lines.size();;
    int parray[256];
 
    preprocess1(word, m, parray);
 
    int shift = 0,j;  
    while(shift <= (n - m))
    {
        j = m-1;
 
        //Moving index from back:
        while((j >= 0) && (word[j] == lines[shift+j])){
            j--;
 		}
        
        //if found, j will be -1
        if (j ==-1)
        {//check if it's an independent word
		if((shift == 0 && lines[shift + m] == ' ') || (shift == n-m && lines[shift - 1] == ' ')||(lines[shift - 1] == ' ' && lines[shift + m] == ' '))
            {cout<<"Page "<<pgno<<" Line "<<lineno<<endl;
            flag=1;}
 
           //shift:
            if(shift<n-m)
			shift += m-parray[toascii(lines[shift+m])] ;
			else
			shift++;
        }
 		//if match not found:
        else{
		   if(j>parray[toascii(lines[shift+j])])
		   shift+=j-parray[toascii(lines[shift+j])];
		   else
		   shift++;
		}
    }
}

int main(){
	ifstream queries;
	int pgno=1,lineno;
	vector <string> lines;
	queries.open("queries.txt");
	while(!queries.eof()){
		string word;
		queries>>word;
		cout<<"Word: "<<word<<endl;
		cout<<"Occurrences:"<<endl;
		int flag=0;
		pgno=1;
		for(int i=1;i<=25;i++){
			lines=readPage(pgno);
			lineno=1;
			for(int j=0;j<lines.size();j++){
			BMSearch(word,lines[j],lineno,pgno,flag);
			lineno++;
			}
			pgno++;
		}
		if(flag==0)
		cout<<"None"<<endl;
		}
	queries.close();
	return 0;
}
