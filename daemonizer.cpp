#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>

#include <iostream>

#include <config.hpp>


static void deinit_daemon()
{
    
}

static void init_daemon()
{
    pid_t pid;

    /* Fork off the parent process */
    pid = fork();

    /* An error occurred */
    if (pid < 0)
        exit(EXIT_FAILURE);

    /* Success: Let the parent terminate */
    if (pid > 0)
        exit(EXIT_SUCCESS);

    /* On success: The child process becomes session leader */
    if (setsid() < 0)
        exit(EXIT_FAILURE);

    /* Set new file permissions */
    umask(0);

    /* Change the working directory to the root directory */
    /* or another appropriated directory */
    chdir("/");

    /* Close stdin. stdout and stderr */
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

}

int main()
{
    int i=0;
    init_output();
#ifdef DEBUG
    cout<< "Damenon initialization skiped."<< std::endl;
#else
    init_daemon();
    cout<<"First daemon started."<<std::endl;
#endif
    

    
#ifdef DEBUG
    cout<<"Daemon deinitialization skiped."<< std::endl;
#else
    deinit_daemon();
    cout<<"First daemon terminated."<<std::endl;
#endif
    deinit_output();
    return EXIT_SUCCESS;
}




