#include "FS.h"
/*
functioun for work with file in filesystem
*/

String readFile(fs::FS &fs, const char * path){
    File file = fs.open(path);
    if(!file || file.isDirectory()){
        return String("s");
    }

    String temp_str;
    while(file.available()){
        temp_str += file.readString();
    }
    file.close();
    return temp_str;
}

void writeFile(fs::FS &fs, const char * path, const char * message){
    File file = fs.open(path, FILE_WRITE);
    if(!file){
        return;
    }
    if(file.print(message)){
        // Serial.println("- file written");
    } else {
        // Serial.println("- write failed");
    }
    file.close();
}

void deleteFile(fs::FS &fs, const char * path){
    if(fs.remove(path)){
        // Serial.println("- file deleted");
    } else {
        // Serial.println("- delete failed");
    }
}