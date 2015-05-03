#include "interface.h"

Interface::Interface()
{

}

Interface::Interface(IndexHandler*& theHandler)
{
    handler = theHandler;
    built = false;
    mode = 0;
    endSearch = false;
    cout << "Welcome to KITESearch!\n" << endl;
    setMode();
}

void Interface::setMode(){
    while(!endSearch){
        cout<< "\nEnter the Mode" << endl;
        cout<< "=> Interactive" << endl;
        cout<< "=> Maintenance" << endl;
        cout << "Mode: ";
        cin >> modeStr;
        modeStr = toLowerCase(modeStr);
        bool check = false;
        while(!check){
            if (modeStr == "interactive" ){
                cout << " You have selected " << modeStr <<endl;
                mode = 1;
                modeStr= "";
                options();
            }
            else if (modeStr == "maintenance"){
                cout << " You have selected " << modeStr <<endl;
                mode = 2;
                modeStr = "";
                runMaintenance();
            }
            else{
                cout<< "I did not understand '"<< modeStr << "'"<< endl;
                cout<< "\nEnter the Mode" << endl;
                cout<< "=> Interactive" << endl;
                cout<< "=> Maintenance" << endl;
                cout << "Mode: ";
                cin >> modeStr;
                modeStr = toLowerCase(modeStr);
            }
        }
    }
}
void Interface::getCommand(){
    string cmd = "";
    string asr = "";
    
    cout<< "Enter command: ";
    cin >> cmd;
    cmd = toLowerCase(cmd);
    cout << "Your command was " << cmd << endl;
    cout << "correct? (yes or no)" << endl;
    cin >> asr;
    asr = toLowerCase(asr);
    command(cmd,asr);
}

void Interface::command(string cmd, string asr){
    bool check = false;
    while(!check){
        if (asr == "yes"){
            if(mode == 1){
                if (cmd == ""){
                    cout << "There was no command" << endl;
                    options();
                }else if(cmd == "search"){
                    search();
                    
                }else if(cmd == "options"){
                    options();
                }else if(cmd == "setmode"){
                    setMode();
                }else if (cmd == "runavl"){
                    runAVL();
                    reCommand();
                }else if(cmd == "runhash"){
                    runHash();
                    reCommand();
                }else if(cmd == "addFile"){
                    permissionDenied(cmd);
                }else if (cmd == "clearIndex"){
                    permissionDenied(cmd);
                }else if(cmd == "quit"){
                    quit();
                }
            }else if (mode == 2){
                if(cmd == "clearindex"){
                    clearIndex();
                    reCommand();
                }else if(cmd == "addfile"){
                    string path;
                    cout<< "please input the file path to the file you would like to add to the index" << endl;
                    cout<< " to go back type back or type anything else to continue"<<endl;
                    cout << ":"<<endl;
                    cin >> path;
                    if (path != "back"){
                        cout << "File Path = "<< path <<endl;
                        addFileToIndex(path);
                        cout<<"file added"<<endl;
                        reCommand();
                    }else{
                        runMaintenance();
                    }
                }else if(cmd == "setMode"){
                    setMode();
                }else if(cmd == "search"){
                    permissionDenied(cmd);
                }else if (cmd == "runavl"){
                    permissionDenied(cmd);
                }else if(cmd == "runhash"){
                    permissionDenied(cmd);
                }else if(cmd == "options"){
                    options();
                }else if(cmd == "quit"){
                    quit();
                }else{
                    cout<<"I did not understand that command" << endl;
                    options();
                }
            }
        }else if (asr == "no"){
            cout << "returning" <<endl;
            getCommand();
        }else {
            cout<< "I did not understand '"<< asr << "'"<< endl;
            cout << "Your command was " << cmd << endl;
            cout << "correct? (yes or no)" << endl;
            cin >> asr;
            asr = toLowerCase(asr);
        }
    }
}

void Interface::options(){
    cout << " \nInteractive Mode" << endl;
    cout << "Here are the commands we have available" << endl;
    cout << "   => setMode" <<endl;
    cout << "   => search" << endl;
    cout << "   => runAVL" << endl;
    cout << "   => runHash" << endl;
    cout << "   => type options to repeat these options at any time" << endl;
    getCommand();
}

void Interface::runMaintenance(){
    cout << "Maintenance Mode:" <<endl;
    cout << "Here are the commands we have available" << endl;
    cout << "   => setMode" <<endl;
    cout << "   => clearIndex" << endl;
    cout << "   => addFile" << endl;
    getCommand();
    
}

void Interface::search(){
    string sQuery = "";
    string input = "";
    cout<< "You Chose Search!" << endl;
    cout << "      Use 'AND' at the beginnign of your query to docs with both words in them" << endl;
    cout << "      Use 'OR' at the beginning of your query to get docs that have any of the words in them" << endl;
    cout << "      Use 'NOT' in between results with words to exclude results" << endl;
    cout << "      Examples: AND Boston NOT Pig"<< endl;
    cout << "                OR Boston Pig"<< endl;
    cout << "                Boston" << endl;
    cout << "Please enter your query here: " << endl;
    cin >> input;
    getline(cin, sQuery);
    input +=  sQuery ;
    cout << input << endl;
    
    reCommand();
}

void Interface::runAVL(){
    if(built == true){
        clearIndex();
    }
    cout<< "Building AVL Tree" << endl;
    cout<< "Building..." << endl;
    index = new IndexHandler(false);
    cout<< "AVL Tree Built" << endl;
    built = true;
}

void Interface::runHash(){
    if(built == true){
        clearIndex();
    }
    cout<< "Building Hash Tree" << endl;
    cout<< "Building..." << endl;
    index = new IndexHandler(true);
    cout<< "Hash Table Built" << endl;
    built = true;
}
void Interface::addFileToIndex(string path){
    
    
}
void Interface::permissionDenied(string w){
    string asr = "";
    bool t = false;
    if (mode == 1){
        cout << "You are in ineractive mode" << endl;
        cout << "you are not allowed to call " << w << "in interactive mode" << endl;
        cout << "Would you like to switch to maintenance and run the command? (yes or no)" << endl;
        cin >> asr;
        asr = toLowerCase(asr);
        while(!t){
            if (asr == "yes"){
                mode = 2;
                t = true;
                command(w, "yes");
            }else if (asr == "no"){
                t = true;
                options();
            }else{
                cout<< "I did not understand '"<< asr << "'"<< endl;
                t = true;
                permissionDenied(w);
            }
        }
    }else if (mode == 2){
        cout << "You are in maintenance mode" << endl;
        cout << "you are not allowed to call " << w << "in maintenance mode" << endl;
        cout << "Would you like to switch to interactive and run the command? (yes or no)" << endl;
        cin >> asr;
        asr = toLowerCase(asr);
        while(!t){
            if (asr == "yes"){
                mode = 1;
                t = true;
                command(w, "yes");
            }else if (asr == "no"){
                t = true;
                runMaintenance();
            }else{
                cout<< "I did not understand '"<< asr << "'"<< endl;
                t = true;
                permissionDenied(w);
            }
        }
    }
    
}
//if they want to perform another command
void Interface::reCommand(){
    string asr = "";
    bool t = false;
    cout<< "would you like to perform another command? (yes or no) " << endl;
    cin >> asr;
    asr = toLowerCase(asr);
    while (!t){
        if(asr == "yes"){
            if (mode == 1){
                options();
            }else if (mode == 2){
                runMaintenance();
            }
        }else if(asr == "no"){
            quit();
        }else{
            cout << "Im sorry. I didnt understand "<< asr <<endl;
            t = true;
            reCommand();
        }
        
    }
}

void Interface::clearIndex(){
    if (built == true){
        
    }
}


void Interface::quit(){
    cout<<"Thank you very much for using Kite Search" << endl;
}

string Interface::toLowerCase(string w){
    for(int i = 0; i < w.length(); i ++){
        w[i] = tolower(w[i]);
    }
    return w;
}

