//##### Author: Imane Laarousi
//##### UID: u1379840
//##### Class: CS6013
#include "shelpers.h"
#include <iostream>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int cd(char *path) {
    return chdir(path);
}

int main(int argc, const char * argv[]) {
    try {

        std::string line;
        char *buffer;

        while ((buffer = readline("$ "))) {
//    while (getline(std::cin, line)) {
            auto tokens = tokenize(buffer);
            auto commands = getCommands(tokens);
            std::vector<pid_t> pids;

            for (int i = 0; i < commands.size(); i++) {
                int pid = fork();
                Command c = commands[i];
                    // if fork() returns -1 -->failed to fork
                if (pid < 0) {

                    perror("The fork failed");

                } else if (pid == 0) {// if fork() returns 0 -->fork success and child created

                    int fdIn = dup2(c.inputFd, 0);// dup2 -- duplicate an existing file descriptor , In dup2(), the value of the new descriptor fildes2 is specified.

                    if (fdIn == -1) {
                        perror("fdIn failed");
                        exit(1);
                    }

                    int fdOut = dup2(c.outputFd, 1);//dup2 -- duplicate an existing file descriptor output file descriptor 1
                    if (fdOut == -1) {
                        perror("fdOut failed");
                        exit(1);
                    }

                    if (c.execName == "cd") { //test if cd doesnt need to fork()

                        if (tokens.size() == 1)
                            cd(getenv("HOME"));
                        else if (cd((char *)(tokens[1].c_str())) < 0)
                            perror("cd command did not work");

                        /* Skip the fork */
                        continue;

                    }
//execvp() function provide an array of point-ers to null-terminated strings that represent the argument list available
 //to the new program
                    int ret = execvp(c.execName.c_str(), const_cast<char* const *>(c.argv.data()));
                    if (ret == -1) {
                        perror("execvp failed");
                        exit(1);
                    }
                } else {

                    // in parent
                    if (c.inputFd != 0)
                        close(c.inputFd);
                    if (c.outputFd != 1)
                        close(c.outputFd);

                    pids.push_back(pid);
                    int returnStatus;

                    if (!c.background) {//if run in backgroup true
                        for (pid_t p: pids) {
                            waitpid(p, &returnStatus, 0);//The waitpid() system call suspends execution of the calling process until a child specified by pid argument has changed state. By default, waitpid() waits only for terminated children, but this behavior is modifiable via the options arg

                        }

                    } else {

                        for (pid_t p: pids) {
                            std::cout << p << std::endl;
                        }
                    }
                }
            }
            free(buffer);
        }
        return 0;

    } catch (std::runtime_error exn) {

        std::cerr << exn.what() << std::endl;

        return 1;
    }
}
