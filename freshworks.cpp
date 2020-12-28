// Author Vasu Jain
// 17314@iiitu.ac.in

#include<bits/stdc++.h>
#include <direct.h>
#include<ctime>
using namespace std;

string DBNAME;
string dir = "C:/Users/admin/Desktop/";


//Function to validate the input
bool valid(string key,string value)
{
	if(key.length()<=32 && value.length()*sizeof(char) <= 16*1024*1024)
	{
		return true;
	}
	return false;
}

// Function to create a key-value
string createD(string key,string value,int ttl)
{	
  string filepath = dir + "/" + key + ".txt";
  ifstream f(filepath.c_str());
  if(!f.good())
   {
   	if(ttl !=0)
   	{
    ofstream MyFile(filepath);
    MyFile << value +"@" + to_string(time(0) + ttl);
    MyFile.close();
    }
    else{
    ofstream MyFile(filepath);
    MyFile << value;
    MyFile.close();
	}
    return "Succefully recorded Key-Value";   	
   }
   else{
   	return "Key Already Exists";
   }
	
}



// Function to read a Key
void readD(string key)
{
string s;
string filepath = dir + "/" +key + ".txt";

ifstream f(filepath.c_str());
   if(!f.good())
   {
   	cout<<"No such Key exists"<<endl;
   }
   else{
    cout<<"Value for key "<<key<<" is ";
    ifstream MyReadFile(filepath);
    while (getline (MyReadFile, s)) {
    	
    	
    	if(s.find("@")<s.length())
    	{
    		stringstream geek(s.substr(s.find('@')+1,s.length()-1)); 
            int x = 0; 
            geek >> x;
            
             if(x >= time(0))
			 {
			   cout<<s.substr(0, s.find('@'));	
			 }		
			 else{
			 	cout<<"Sorry time expired";
			 }
		}
		else{
			cout<<s;
		}
       
    }
    MyReadFile.close();
   }
}


// Function to delete a Key
string deleteD(string key)
{
   string s;
   string filepath = dir + "/" + key + ".txt";
   ifstream f(filepath.c_str());
   if(!f.good())
   {
   	return "No such Key exists";
   }
   else{
    while (getline (f, s)) {
   	if(s.find("@")<s.length())
    	{
    		stringstream geek(s.substr(s.find('@')+1,s.length()-1)); 
            int x = 0; 
            geek >> x;
            
             if(x >= time(0))
			 {
			 	f.close();
			 remove(filepath.c_str());
	         return "Key deleted sucessfully";
			 }		
			 else{
			 	return "Sorry ttl expired";
			 }
		}
		else{
		 f.close();
	     remove(filepath.c_str());
	     return "Key deleted sucessfully";
		}
    }
}
}
int main()
{

	cout<<"Welcome to Key-Value database"<<endl;
	cout<<"New DB? [y/n]"<<endl;
	
	char NewDB;
	cin>>NewDB;
	if(NewDB == 'y' || NewDB == 'Y')
	{
		cout<<"Enter DB name to create a new one"<<endl;
		cin>>DBNAME;
		dir = dir + DBNAME;
	int check;
    check = mkdir(dir.c_str()); 
    
	if (!check) 
	{
        cout<<"Database created successfully"<<endl;
    }
    else{
        cout<<"Database exists already"<<endl;  
	    cout<<dir<<endl;
		cout<<"Switched to DB"<<endl;
	}
	}
	else{
		
		cout<<"Enter DB name you want to access"<<endl;
		cin>>DBNAME;
		dir = dir + DBNAME;
		if(!mkdir(dir.c_str()))
		{
			cout<<"No DB with this name found, New Database created successfully"<<endl;
			cout<<dir<<endl;
		    cout<<"Switched to DB"<<endl;
		}
		else{
		cout<<dir<<endl;
		cout<<"Switched to DB"<<endl;
		}

	}

	cout<<"You have operations like C for create, D for delete, R for read, E for terminating the Application"<<endl;
	
	while(1)
	{
		
	cout<<"Enter Operation"<<endl;
	char operation;
	cin>>operation;
	
	
	
	if(operation == 'C')
	{
		cout<<"Enter Key and its Value and TTL in seconds (0 IF NOT REQURED) space separated to create"<<endl;
		string key;
		string value;
		int time;
		
		cin>>key;
		cin>>value;
		cin>>time;
		
		if(valid(key,value))
		{
			cout<<createD(key,value,time)<<endl;
		}
		else{
			cout<<"Input Validation error"<<endl;
		}
	}
	else if(operation == 'D')
	{
		cout<<"Enter Key to delete"<<endl;
		string key;
		cin>>key;
		cout<<deleteD(key)<<endl;  
	}
	else if(operation == 'R')
	{
		cout<<"Enter Key to read"<<endl;
		string key;
		cin>>key;
		readD(key);
		cout<<endl;
		
	}
	else if (operation == 'E')
	{
		cout<<"Thanks for using KEY-VALUE Database";
		return 0;
	}
	else{
		cout<<"Invalid operation"<<endl;
	}
}
}
