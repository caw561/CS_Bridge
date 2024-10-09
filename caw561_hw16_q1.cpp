#include <iostream>
#include <stack>
#include <fstream>
#include <string>

using namespace std;

bool checkBeginEnd(string& line);
bool checkPascal(string& line);
void openFile(ifstream& file);

int main()
{
    ifstream inFile;
    string input;
    openFile(inFile);
    
    getline(inFile, input);

    if(checkPascal(input)){
        cout<<"True";
    }
    else{
        cout<<"False";
    }
    

    return 0;

}

bool checkBeginEnd(string& line)
{
    if((line.find("begin")!=string::npos)&&(line.find("end")!=string::npos))
        return true;
    return false;
}

bool checkPascal(string& line)
{
    stack<char> Pascal;

    if(checkBeginEnd(line)){
        for(int i=(line.find("begin")); i<line.find("end"); i++){
            switch(line[i]){
                case '{':
                    Pascal.push(line[i]);
                    break;
                case '[':
                    Pascal.push(line[i]);
                    break;
                case '(':
                    Pascal.push(line[i]);
                    break;
                case '}':
                    if(Pascal.top()=='{'){
                        Pascal.pop();
                    }
                    else{
                        return false;
                    }
                    break;
                case ']':
                    if(Pascal.top()=='['){
                        Pascal.pop();
                    }
                    else{
                        return false;
                    }
                    break;
                case ')':
                    if(Pascal.top()=='('){
                        Pascal.pop();
                    }
                    else{
                        return false;
                    }
                    break;
                default:
                    break;

            }
        }
        
        if(Pascal.empty()){
             return true;
        }
    }
    return false;
}

void openFile(ifstream& file)
{
    string filename;
    cout<<"Please enter file name: \n";
    cin>>filename;

    file.open(filename);
    while(!file){
        cout<<"File failed to open! Please reenter name: \n";
        cin>>filename;
        file.clear();
        file.open(filename);
    }
}