#include "interface.h"

Interface::Interface()
{
    cout<< "Starting wikiSearch" << endl;
    setMode();
    built = false;
    mode = 0;
}

void Interface::setMode(){
    while(endPro){
        cout << "/n Welcome to KiteSearch!" << endl;
        cout<< "/n Enter the Mode: " << endl;
        cout<< "/n 1 Interactive" << endl;
        cout<< "/n 2 Maintenance" << endl;
        cin >> strMode;
        lowerCase(strMode);
         cout << "/n You have selected " << strMode <<endl;
        if (strMode == "interactive" ){
            mode = 1;
            options();
        }
        if (strMode == "maintenance"){
            mode = 2;
            runMaintenance();
        }
        else{
            cout<< "/n not a valid command" << endl;
            return setMode();
        }
    }
}

void Interface::command(){
    cout<< "Enter command: "<< endl;
    string cmd;
    string squery;
    string asr;
    cin >> cmd;
    lowerCase(cmd);
    if(cmd.substr(0,6) == "string"){
        cout<< "You chose search" << endl;
        cout << "Please enter your query here: " << endl;
        getline(cin,squery);
        lowerCase(squery);
        search(squery);

    }else {
        cout << "Your command was " << cmd << endl;
        cout << "correct? (y/n)" << endl;
        cin >> asr;
        lowerCase(asr);
        if (asr == "y"){
            if (cmd == ""){
                cout << "There was no command" << endl;
                options();
            }else if(cmd == "options"){
                options();
            }else if(cmd == "setmode"){
                setMode();
            }else if (cmd == "runavl"){
                runAVL();
            }else if(cmd == "runhash"){
                runHash();
            }else if(cmd == "quit"){
                quit();
            }else if(cmd == "clearindex"){
                clearIndex();
            }else if(cmd == "addfile"){
                string path;
                cout<< "please input the file path to the file you would like to add to the index" << endl;
                cout<< "/n to return to main menu type yes"<<endl;
                cout << ":"<<endl;
                cin >> path;
                if (path != "yes"){
                    cout << "File Path = "<< path <<endl;
                    addFileToIndex(path);
                    cout<<"file added"<<endl;
                    options();
                }else{
                    options();
                }

            }
            else{
                cout<<"I did not understand that command" << endl;
                options();
            }

        }else{
            options();
        }
    }
}

void Interface::options(){
    cout << "/n Interactive Mode" << endl;
    cout << "/n Here are the commands we have available" << endl;
    cout << "/n setMode" <<endl;
    cout << "/n search" << endl;
    cout << "/n Use 'AND ' followed by words to combine results" << endl;
    cout << "/n Use 'OR ' followed by words to or results" << endl;
    cout << "/n Use 'NOT' followed by words to exclude results" << endl;
    cout << "/n runAVL" << endl;
    cout << "/n runHash" << endl;
    cout << "/n type options to repeat these options at any time" << endl;
    command();
}

void Interface::runMaintenance(){
    cout<< "/n Maintenance Mode:" <<endl;
    cout << "/n Here are the commands we have available" << endl;
    cout << "/n setMode" <<endl;
    cout << "/n clearIndex" << endl;
    cout << "/n addFile" << endl;
    command();

}

void Interface::search(string word){

}

void Interface::runAVL(){
    if(built == true){
        clearIndex();
    }
    cout<< "Building AVL Tree" << endl;
    cout<< "Building..." << endl;
    index = new IndexHandler(false);
}

void Interface::runHash(){
    if(built == true){
        clearIndex();
    }
    cout<< "Building Hash Tree" << endl;
    cout<< "Building..." << endl;
    index = new IndexHandler(true);
}
void Interface::addFileToIndex(string path){


}
void Interface::clearIndex(){
    if (built = true){

    }
}


void Interface::quit(){
    cout<<"Thank you very much for using Kite Search" << endl;
}

void Interface::lowerCase(string w){
    for(int i = 0; i < w.length(); i ++){
        w[i] = tolower(w[i]);
    }
}

