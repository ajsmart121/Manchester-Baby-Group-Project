#include "compiler.cpp"
#include <vector>
#include <algorithm>

using namespace std;

//class variable - holds information to create variables easily
class variable {
    string name = "";
    string value = "";
    string lineNum = "";

public:
    variable() { name = ""; value = ""; lineNum="";}
    string getName(){ return name; }
    string getValue(){ return value; }
    string getLineNum(){ return lineNum; }
    void setName(string newName){ name = newName; }
    void setValue(string newValue){ value = newValue; }
    void setLineNum(string newLineNum){ lineNum = newLineNum; }
};

//class to hold information for each line/instruction
class Line {
    string command = "111";
    string variable = "";           //memory location or variable
    string starter = "";            //either variable name, start or end

public: 
    string getCommand(){ return command; }
    string getVariable(){ return variable; }
    string getStarter(){ return starter; }
    void setCommand(string newcommand) { command = newcommand; }
    void setVariable(string newVariable) { variable = newVariable; }
    void setStarter(string newStarter) { starter = newStarter; }
};

//splits the line into seperate instructions using the line class
vector<Line> splitter(vector<Line> saveTo,string array[], int lengthOfArray){
    string currentWord;
    char previousChar='&';
    int saveSpace;
    saveTo.resize(32);

    for(int i=0;i<lengthOfArray;i++){
        saveSpace = 0;
        currentWord = "";
        previousChar = '&';
        
        for(int counter=0;counter<array[i].length();counter++){
            
            //Checking when to go to next line
            if(array[i][counter] == ';'){
                break;
            }
            //Checking when a new thing is being declared
            if(array[i][counter]==' ' & previousChar != ' '){
                if(saveSpace==0){
                    saveTo.at(i).setStarter(currentWord);
                }
                else if(saveSpace==1){
                    saveTo.at(i).setCommand(currentWord);
                }
                else if(saveSpace==2){
                    saveTo.at(i).setVariable(currentWord);
                }
                saveSpace++;
                currentWord = "";
            }
            if(array[i][counter] != ':' && array[i][counter] != ' '){
                currentWord+=array[i][counter];
            }
            previousChar=array[i][counter];
        }
    }
    cout<<"Comments Bypassed"<<endl;
    // for(int i=0; i<32;i++){
    //     cout<<"starter: " <<saveTo.at(i).getStarter()<<" command "<<saveTo.at(i).getCommand()<<" variable "<<saveTo.at(i).getVariable()<<endl;
    // }
    return saveTo;
}

//translates the command into the binary opcode
string translateCommand(string command) 
{
    if(command=="JMP"){
        return "000";
    }else if(command=="JRP"){
        return "100";
    }else if(command=="LDN"){
        return "010";
    }else if(command=="STO"){
        return "110";
    }else if(command=="SUB"){
        return "001";
    }else if(command=="CMP"){
        return "011";
    }else if(command=="STP"){
        return "111";
    }else{
        return "000";
    }

}


//check whats in split (the starter if it exists and the operand and the opcode and store them in the vector)
//then translates the line into binary and writes to file "assemberOutput.txt"
int checkLine(vector<Line> split) {
    // cout<<"I'm in you"<<endl;
    vector<variable> vars;
    // cout<<"\n \n \n \n \n " << endl;
    // cout<<"fuck"<<endl;
    variable tempVar;

    for(int i=0; i<split.size(); i++){
        if(split[i].getCommand() == "VAR"){
            tempVar.setLineNum(backwardsIntToBinary(i,13));
            tempVar.setName(split[i].getStarter());
            tempVar.setValue(backwardsIntToBinary(stoi(split[i].getVariable()), 32));

            vars.push_back(tempVar);
        }
    }
    cout<<"Found Variables"<<endl;

    for(int i=0; i<split.size();i++) {  
        if(split[i].getCommand()!="VAR"){
            bool changed = false; 
            for(int j=0; j<vars.size(); j++){
                if(split[i].getVariable() == vars.at(j).getName()){
                    split[i].setVariable(vars.at(j).getLineNum());
                    changed = true;
                }
            }
            if(changed==false){
                split[i].setVariable("0000000000000");
            }
        }
    }
    cout<<"Memory Locations Input in place of variables" << endl;

    ofstream newFile;
    newFile.open("assemblerOutput.txt");

    cout << "Commands translated"<<endl;

    for(int i=0; i<split.size();i++) {
        if(split[i].getCommand()!="VAR"){
            //cout<<split[i].getVariable()<<translateCommand(split[i].getCommand())<<"0000000000000000"<<endl;
            newFile<<split[i].getVariable()<<translateCommand(split[i].getCommand())<<"0000000000000000\n";
        }
        else{
            //cout<<backwardsIntToBinary(stoi(split[i].getVariable()),31)<<"0"<<endl;
            newFile<<backwardsIntToBinary(stoi(split[i].getVariable()),31)<<"0\n";
        }
    }

    newFile.close();
    cout<<"Saved binary to file"<< endl;
}

//reads in the file, hard coded if no filename is given
int readFile(string filename, string tempString[], string fileName = "BabyTest1-Assembler.txt" ) {

    int commandsLength = 32;

    string line;
    int i=0;
    ifstream readFile(fileName, ios::in);
    if (!readFile){
        return 1;
    }
    //reads in file line by line saving to the string wholeThing
    while(getline(readFile, line)) {
        if(i>=commandsLength){
            cout<<"Don't have enough storage space for this instruction set"<<endl;
            return 2;
        }
        if(line[0] != ';'){

            tempString[i] = line;
            i++;
        }
    }
    readFile.close();
    return 0;

}

//the "main", runs all the methods
int assembler(string fileName) {

    int commandlines = 32;
    string tempString[commandlines];
    vector<Line> split;

    readFile(fileName, tempString);
    //the split method

    split = splitter(split, tempString, commandlines);
    cout<<"Split sucessful"<<endl;

    checkLine(split);

    compiler(32,32,"assemblerOutput.txt");

    return 0;
    

}