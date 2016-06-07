#include <iostream>
#include <cstdlib>
#include <cerrno>
#include <cstring>
#include <stdexcept>

#include <unistd.h>
#include <sys/stat.h>

#include <config.hpp>
#include <daemonizer.hpp>


void Daemonizer::deinit_daemon()
{
}

void Daemonizer::init_daemon()
{
    pid_t pid;

    /* Fork off the parent process */
    pid = fork();
    cout <<" Proces forked" << std::endl;

    /* An error occurred */
    if (pid < 0)
        throw std::runtime_error(strerror(errno));

    /* Success: Let the parent terminate */
    if (pid > 0)
        std::exit(EXIT_SUCCESS);

    /* On success: The child process becomes session leader */
    if (setsid() < 0)
        throw std::runtime_error(strerror(errno));

    /* Set new file permissions */
    umask(0);

    /* Change the working directory to the root directory */
    if (chdir("/") < 0)
        throw std::runtime_error(strerror(errno));

    /* Close stdin. stdout and stderr */
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

}





