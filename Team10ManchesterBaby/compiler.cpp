#include <string>
#include <iostream>
#include <fstream>

using namespace std;

//A class for storage locations to store the number and data from each storage location
class storageLocation {
    string locationNumber;
    string storedData;
    bool used;

public:
    storageLocation(){
        locationNumber = "-1";
        storedData = "0";
        used = false;
    }
    storageLocation(string location, string data){
        locationNumber = location;
        storedData = data;
        used = false;
    }
    string getData(){return storedData;}
    string getLocation(){return locationNumber;}
    bool getUsed(){return used;}
    void setData(string data){storedData = data;}
    void setUsed(){used=true;}
    void setNode(string location, string data){
        locationNumber=location;
        storedData = data;
    }
};

//Translates Binary to an Integer
int backwardsBinaryToInt(string binary, bool negativePossible = false){
    int translationOfDigit=1;
    int realNumber = 0;
    int length = binary.length();
    if(negativePossible){
        length--;
    }
    for(int i=0; i<length;i++){
        if(binary[i] == '1'){
            realNumber += translationOfDigit;
        }
        translationOfDigit *= 2;
    }
    if(negativePossible){
        if(binary[length]==1){
            realNumber *= -1;
        }
    }
    return(realNumber);
}

//Puts a number to the power of another number
long toThePowerOf(int number, int power){
    if(power == 0){
        return 1;
    }
    if(power<0){
        cout<<"Power can't be negative"<<endl;
        throw "Negative Power";
    }
    long currentInt=1;
    for(int i=0;i<power;i++){
        currentInt *= number;
    }
    return currentInt;
}

//Translates an integer to binary of the length given
string backwardsIntToBinary(int number, int lengthOfBinary, bool negativePossible = false){
    string binary;
    for(int i=lengthOfBinary-1; i>=0; i--){
        binary+='I';
    }
    if(negativePossible){
        lengthOfBinary--;
        //last digit 1 = negative
        if(number<0){
            binary[lengthOfBinary]=1;
            number *= -1;
        }
        //last digit 1 = positive
        else{
            binary[lengthOfBinary]=0;
        }
    }
    long divider = toThePowerOf(2,lengthOfBinary-1);
    for(int i=lengthOfBinary-1; i>=0; i--){
        if(number>=divider){
            binary[i]='1';
            number -= divider;
        }
        else{
            binary[i]='0';
        }
        divider /= 2;
    }
    return binary;
}

//Saves a file's individual lines to the commands array
int saveFile(string commands[], string fileName, int commandsLength){
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
        commands[i] = line;
        i++;
    }
    readFile.close();
    return 0;
}

//Translates the instruction in the command to an integer
int checkInstruction(string command, int numberOfCommandBits, int starter){
    string binaryOfNumber = "";
    for(int i=0; i<numberOfCommandBits;i++){
        binaryOfNumber+=command[starter+i];
    }
    cout<<"Running Command: "<<  binaryOfNumber << ". Which is ";
    return backwardsBinaryToInt(binaryOfNumber);
}

//Gets the storage location saved in a command
string getOperand(string line, int till){
   string binaryOfNumber = "";
    for(int i=0; i<till;i++){
        binaryOfNumber+=line[i];
    }
    return binaryOfNumber;
}

//Prints what is stored in each storage location. Used for testing
// void printStorageLocations(storageLocation storageLocations[],int spaceForVariables){
//     for(int i =0;i<spaceForVariables;i++){
//         cout<<storageLocations[i].getData()<<endl;;
//     }
// }

//Inputs a storage location into the storage location array
void inputStorageLocation(storageLocation storageLocations[], storageLocation singular, int spaceForVariables){
    for(int i=0; i<spaceForVariables; i++){
        if(!storageLocations[i].getUsed()){
            storageLocations[i].setNode(singular.getLocation(),singular.getData());
            storageLocations[i].setUsed();
            return;
        }
    }
}

//Gets the data from an array of storage locations given a location wanted
string getData(storageLocation storageLocations[], string location, int spaceForVariables){
    for(int i =0;i<spaceForVariables;i++){
        if(storageLocations[i].getLocation()==location){
            return storageLocations[i].getData();
        }
        if(storageLocations[i].getLocation()=="-1"){
            break;
        }
    }
    cout<<"Data location not found"<<endl;
}

//Stores data in a location given in an array of storage locations
void storeDataAtLocation(storageLocation storageLocations[], string location, string data,int spaceForVariables){
    for(int i =0;i<spaceForVariables;i++){
        if(storageLocations[i].getLocation()==location || storageLocations[i].getLocation() == "-1"){
            storageLocations[i].setNode(location,data);
        }
    }
}

//Return the int in the store location in the command
int jmp(string operand, storageLocation storageLocations[], int spaceForVariables){
    cout<<"Changing the control instruction to what is stored in memory location "<<operand<<endl;
    return backwardsBinaryToInt(getData(storageLocations, operand, spaceForVariables));
}

//Add the int in the store location in the command to control instuction and return that
void jrp(string operand, int &controlInstruction,storageLocation storageLocations[], int spaceForVariables){
    cout<<"Adding what is stored in memory location "<<operand<<" to the control instruction"<<endl;
    controlInstruction += backwardsBinaryToInt(getData(storageLocations, operand,spaceForVariables));
}

//save the negative of the int in the store location in the command to the accumulator
void ldn(string operand, int &accumulator,storageLocation storageLocations[],int spaceForVariables){
    cout<<"Saving the negative of what is in the storage location "<<operand<< " to the accumulator"<<endl;
    accumulator = backwardsBinaryToInt(getData(storageLocations, operand,spaceForVariables), true) *-1;
    cout<<"The accumulator is now "<<accumulator<<endl;
}

//save what's in the accumulator to the storage location in the command
void sto(string operand, int &accumulator,storageLocation storageLocations[], int lengthOfBinary,int spaceForVariables){
    cout<<"Saving what is in the accumulator ("<<accumulator<<") to the storage location "<<operand<<endl;
    storeDataAtLocation(storageLocations, operand, backwardsIntToBinary(accumulator,lengthOfBinary,true),spaceForVariables);
}

//subtract the int in the store location in the command from the accumulator
void sub(string operand, int &accumulator, storageLocation storageLocations[], int spaceForVariables){
    cout<<"Subtracting what is stored in store location "<< operand<< " from the accumulator"<<endl;
    accumulator -= backwardsBinaryToInt(getData(storageLocations, operand,spaceForVariables));
    cout<<"Accumulator is now "<<accumulator<<endl;
}

//If integer in the accumulator is negative increment the command instruction
void cmp(int accumulator, int &controlInstruction){
    cout<<"Adding one to the control instruction if the accumulator stores a negative number"<<endl;
    if(accumulator<0){
        cout<<"Adding one to the control instrucion as accumulator stores "<<accumulator<<endl;
        controlInstruction++;
    }
}

//Runs the compiler. This is the same as the main
void compiler(int spaceForInstructions=32,int sizeOfStorageLocation = 32, string fileName ="BabyTest1-MC.txt"){
    int accumulator; //integer that's used to store the solution to a calculation
    int controlInstruction; //stores the line the program is currently working on
    int startingLocationOfTheOpcode = 13;
    int lengthOfOpcode=3;
    int instructionToRun;
    string operand; // the binary of the storage location
    string commands[spaceForInstructions]; //The list of commands
    storageLocation variables[spaceForInstructions]; //The list of variables
    storageLocation *tempStorageLocation;
    tempStorageLocation = new storageLocation;
    tempStorageLocation->setNode("-1","0");
    //Saving the file to the commands
    saveFile(commands,fileName,spaceForInstructions);
    //Initialising the array of variables
    for(int i=0; i<spaceForInstructions;i++){
        variables[i] = *tempStorageLocation;
    }
    //Setting all variables
    for(int i=0;i<spaceForInstructions;i++){
        tempStorageLocation->setNode(backwardsIntToBinary(i,startingLocationOfTheOpcode),commands[i]);
        inputStorageLocation(variables, *tempStorageLocation,spaceForInstructions);   
    }

    //The brain power
    for(int controlInstruction=1;controlInstruction<spaceForInstructions;controlInstruction++){
        cout<<"\nAdding One to the Control Instruction"<<endl;
        instructionToRun = checkInstruction(commands[controlInstruction], lengthOfOpcode, startingLocationOfTheOpcode);
        operand = getOperand(commands[controlInstruction],startingLocationOfTheOpcode);

        if(instructionToRun == 0){
            cout<<"JMP"<<endl;
            controlInstruction = jmp(operand, variables,spaceForInstructions);
            cout<< "The control instruction is now set to " << controlInstruction <<endl;
        }
        else if(instructionToRun ==1){
            cout<<"JRP"<<endl;
            jrp(operand, controlInstruction, variables,spaceForInstructions);
            cout<< "The control instruction is now set to " << controlInstruction <<endl;
        }
        else if(instructionToRun ==2){
            cout<<"LDN"<<endl;
            ldn(operand, accumulator, variables,spaceForInstructions);
        }
        else if(instructionToRun ==3){
            cout<<"STO"<<endl;
            sto(operand, accumulator, variables, sizeOfStorageLocation,spaceForInstructions);
        }
        else if(instructionToRun ==4 || instructionToRun ==5){
            cout<<"SUB"<<endl;
            sub(operand,accumulator, variables,spaceForInstructions);
        }
        else if(instructionToRun ==6){
            cout<<"CMP"<<endl;
            cmp(accumulator,controlInstruction);
        }
        else if(instructionToRun ==7){
            cout<<"STP"<<endl;
            cout<<"The end of the program has been reached. Stopping now.\n"<<endl;
            return;
        }
    }
}