#include "shelpers.h"

////////////////////////////////////////////////////////////////////////
// Example test commands you can try once your shell is up and running:
//
// ls
// ls | nl
// cd [dir]
// cat < shelpers.cpp
// cat < shelpers.cpp | nl
// cat shelpers.cpp | nl
// cat shelpers.cpp | nl | head -50 | tail -10
// cat shelpers.cpp | nl | head -50 | tail -10 > ten_lines.txt
//
// - The following two commands are equivalent.  [data.txt is sent into nl and the
//   output is saved to numbered_data.txt.]
//
// nl > numbered_data.txt < data.txt
// nl < data.txt > numbered_data.txt
//
// - Assuming numbered_data.txt has values in it... try running:
//   [Note this probably doesn't work like one might expect...
//    does it behave the same as your normal shell?]
//
// nl < numbered_data.txt > numbered_data.txt
//
// - The following line is an error (input redirection at end of line).
//   It should fail gracefully (ie, 1) without doing anything, 2) cleaning
//   up any file descriptors that were opened, 3) giving an appropriate
//   message to the user).
//
// cat shelpers.cpp | nl | head -50 | tail -10 > ten_lines.txt < abc
//
////////////////////////////////////////////////////////////////////////
// This routine is used by tokenize().  You do not need to modify it.

bool splitOnSymbol(std::vector<std::string>& words, int i, char c){
    if(words[i].size() < 2){ return false; }
    int pos;
    if((pos = words[i].find(c)) != std::string::npos){
        if(pos == 0){
            //starts with symbol
            words.insert(words.begin() + i + 1, words[i].substr(1, words[i].size() -1));
            words[i] = words[i].substr(0,1);
        } else {
            //symbol in middle or end
            words.insert(words.begin() + i + 1, std::string{c});
            std::string after = words[i].substr(pos + 1, words[i].size() - pos - 1);
            if(!after.empty()){
                words.insert(words.begin() + i + 2, after);
            }
            words[i] = words[i].substr(0, pos);
        }
        return true;
    } else {
        return false;
    }

}
////////////////////////////////////////////////////////////////////////
// You do not need to modify tokenize().
std::vector<std::string> tokenize(const std::string& s){

    std::vector<std::string> ret;
    int pos = 0;
    int space;
    //split on spaces
    while((space = s.find(' ', pos)) != std::string::npos){
        std::string word = s.substr(pos, space - pos);
        if(!word.empty()){
            ret.push_back(word);
        }
        pos = space + 1;
    }

    std::string lastWord = s.substr(pos, s.size() - pos);
    if(!lastWord.empty()){
        ret.push_back(lastWord);
    }

    for(int i = 0; i < ret.size(); ++i){
        for(auto c : {'&', '<', '>', '|'}){
            if(splitOnSymbol(ret, i, c)){
                --i;
                break;
            }
        }
    }

    return ret;

}


std::ostream& operator<<(std::ostream& outs, const Command& c){
    outs << c.execName << " argv: ";
    for(const auto& arg : c.argv){ if(arg) {outs << arg << ' ';}}
    outs << "fds: " << c.inputFd << ' ' << c.outputFd << ' ' << (c.background ? "background" : "");
    return outs;
}

//returns an empty vector on error
/*

 You'll need to fill in a few gaps in this function and add appropriate error handling
 at the end.

 */
std::vector<Command> getCommands(const std::vector<std::string>& symbols){
    std::vector<Command> commands(std::count(symbols.begin(), symbols.end(), "|") + 1);  //1 + num |'s commands

    int first = 0;

    int last = std::find(symbols.begin(), symbols.end(), "|") - symbols.begin();
    bool error = false;

    for(int cmdNumber = 0; cmdNumber < commands.size(); ++cmdNumber){
        if((symbols[first] == "&") || (symbols[first] == "<") ||
           (symbols[first] == ">") || (symbols[first] == "|")){
            error = true;
            break;
        }

        commands[cmdNumber].execName = symbols[first];
        commands[cmdNumber].argv.push_back(symbols[first].c_str()); //argv0 = program name
        std::cout << "execName start: " << commands[cmdNumber].execName << std::endl;
        commands[cmdNumber].inputFd = 0;
        commands[cmdNumber].outputFd = 1;
        commands[cmdNumber].background = false;

        for(int j = first + 1; j < last; ++j){
            if(symbols[j] == ">" || symbols[j] == "<" ) {

                /*Handle I/O redirection symbols
                       //
                       // Note, that only the FIRST command can take input redirection
                       // (all others get input from a pipe)
                       // Only the LAST command can have output redirection!//
               */
                //assert(false);
            }
            else if (symbols[j] == ">") {

                    commands[cmdNumber].outputFd = open(symbols[j + 1].c_str(), O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
                    if (commands[cmdNumber].outputFd < 0)
                        perror("error writing to file\n");
                    // add nullptr to signal to execName end of args
                    commands[cmdNumber].argv.push_back(nullptr);

                }
                // input file, setting stdin to name of file provided
               else if (symbols[j] == "<") {

                    commands[cmdNumber].inputFd = open(symbols[j + 1].c_str(), O_RDONLY);
                    if (commands[cmdNumber].inputFd < 0)
                        perror("error opening file\n");

                }else if(symbols[j] == "&"){
                //Fill this in if you choose to do the optional "background command" part
                commands[cmdNumber].background = true;

//        assert(false);
            } else {
                //otherwise this is a normal command line argument!
                commands[cmdNumber].argv.push_back(symbols[j].c_str());
            }

        }
        if( !error ) {
            if (cmdNumber > 0) {
                /* there are multiple commands.  Open a pipe and
                 connect the ends to the fds for the commands!
                 */
                int fd[2];
                int p = pipe(fd);
                if (p != 0)
                    perror("error creating pipe\n");

                commands[cmdNumber].inputFd = fd[0];
                commands[cmdNumber - 1].outputFd = fd[1];
                //assert(false);
            }
            //execName wants argv to have a nullptr at the end!
            commands[cmdNumber].argv.push_back(nullptr);

            //find the next pipe character
            first = last + 1;
            if (first < symbols.size()) {
                last = std::find(symbols.begin() + first, symbols.end(), "|") - symbols.begin();
            }
        }
    }

    if(error){
        //close any file descriptors you opened in this function!

        assert(false);

    }

    return commands;
}
