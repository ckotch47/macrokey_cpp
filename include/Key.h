std::string tempKeyArr[512];
int tempKeyArrIndex = 0;
const int maxArraySize = 6;

class Key{
  public:
    String name;
    int gpo;

    Key(String name, int gpo){
      this->gpo = gpo;
      this->name = name;
    }
};


Key tempKey[maxArraySize] = {
  Key("key0", 0), Key("key0", 0), Key("key0", 0), 
  Key("key0", 0), Key("key0", 0), Key("key0", 0)
};

void splitStringForKey(std::string str, std::string delimiter = "\n"){
  size_t pos = 0;
  std::string token;
  while ((pos = str.find(delimiter)) != std::string::npos) {
      token = str.substr(0, pos);
      if(delimiter == "\n"){
        splitStringForKey(token, ",");
      }
      if(delimiter == "," && tempKeyArrIndex < maxArraySize*2){
        tempKeyArr[tempKeyArrIndex] = token.c_str();
        tempKeyArrIndex++;
      }
      str.erase(0, pos + delimiter.length());
  }
}

void initKey(Key *keyArray){
  String tempFileBtn = readFile(SPIFFS, "/button.csv");
  splitStringForKey(tempFileBtn.c_str());
  int keyArrayIndex = 0;

  for(int i=0; i<maxArraySize*2; i+=2){
    if(tempKeyArr[i].length() > 0){
      keyArray[keyArrayIndex] = Key(tempKeyArr[i].c_str(), stoi(tempKeyArr[i+1]));
      keyArrayIndex++;
    }
  }
}

int findIndex(String arr[], String element) {
    int index = -1;
    int i = 0;
    while (true) {
        if (i > arr->length()) break;
        if (arr[i] == element) {
            index = i;
            break;
        }
        i++;
    }
    return index;
}

String getButton(){
  String tmp[6] = {"0", "0", "0", "0", "0", "0"};
  int j = 0;
  while (true){
    int btnDown = 0;
    for (int i=0; i<maxArraySize; i++){
      if (tempKey[i].gpo > 0 && digitalRead(tempKey[i].gpo) == LOW){
          btnDown = 1;
          if (findIndex(tmp, tempKey[i].name) == -1){
            tmp[j] = tempKey[i].name;
            j++;        
          }
        }
    }
    if (btnDown == 0){
      break;
    }    
  }
  String res = "";
  for(int i=0; i<6; i++){
    if(tmp[i] != "0") res += tmp[i];
  }
  return res;
}
