struct Command{
  String cmd[5];
};

std::map<String, Command> CommandKey;


int tempCommandMapIndex = 0;
String tempCommandArray[5];

void initCommand(std::string str, std::string delimiter = "\n"){
  size_t pos = 0;
  int i = 0;
  String tempKeyCommand;
  Command tempCmd;

  std::string token;
  while ((pos = str.find(delimiter)) != std::string::npos) {
      token = str.substr(0, pos);
      if(delimiter == "\n"){
        initCommand(token, ",");
      }
      if(delimiter == ","){
        if(i == 0) tempKeyCommand = token.c_str();
        else tempCmd.cmd[i-1] = token.c_str();
        i++;   
      }
      str.erase(0, pos + delimiter.length());
  }
  if(i != 0){
    CommandKey.insert(std::make_pair(tempKeyCommand, tempCmd));
  }
}