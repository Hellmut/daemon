#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>
#include <libpq-fe.h>
#include <bcm2835.h>
FILE * fp;

#define PIN RPI_V2_GPIO_P1_31

typedef struct Out_action_tag{
    int out_port;
    int out_state;
    int change;
} Out_action;

void do_exit(PGconn *conn) {
    
    PQfinish(conn);
    exit(1);
}


int db_check_command(Out_action * act){
    PGconn *conn = PQconnectdb("user=datauser dbname=rpidatabase");

    if (PQstatus(conn) == CONNECTION_BAD) {
        
        fprintf(stderr, "Connection to database failed: %s\n",
            PQerrorMessage(conn));
        do_exit(conn);
    }

    int ver = PQserverVersion(conn);

    //printf("Server version: %d\n", ver);
    
    PGresult *res = PQexec(conn, "SELECT * FROM m_outlet_wcommand WHERE done='false' ");    
    
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {

        //printf("No data retrieved\n");        
        PQclear(res);
        do_exit(conn);
    }    

    //fprintf(fp,"%s\n", PQgetvalue(res, 0, 0));

    int rows = PQntuples(res);   
    int cols = PQnfields(res); 

    for(int i=0; i<rows; i++) {
         act->out_port = atoi(PQgetvalue(res,i,3));
         act->out_state =  atoi(PQgetvalue(res,i,4)); 
         act->change = 1;
        for (int j=0; j<cols; j++) {
            fprintf(fp," %s |", PQgetvalue(res, i, j));
        }
        fprintf(fp,"\n");
        char buffer[1024];
        snprintf(buffer, sizeof(buffer), "UPDATE m_outlet_wcommand SET done='true' where ID=%s", PQgetvalue(res,i,0));
        PQexec(conn, buffer);
         
        break;
    }    

    PQclear(res);
    PQfinish(conn);
    return 0;
}

int out_command(Out_action * out_action){
    fprintf(fp,"Port = %d State= %d\n", out_action->out_port, out_action->out_state);
    fflush(fp);

  if (!bcm2835_init())
      return 1;
    // Set the pin to be an output
    bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_OUTP);

    if (out_action->out_state == 1){
        bcm2835_gpio_write(PIN, HIGH);
        fprintf(fp,"HIGH\n");
        fflush(fp);
    }
    else{
        bcm2835_gpio_write(PIN, LOW);    
        fprintf(fp,"LOW\n");
        fflush(fp);
    }
  
  bcm2835_close();

    out_action = NULL;
    return 0;
}

static void deinit_daemon()
{
    fclose(fp);
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

    /* Open the log file */
    fp = fopen("/dev/null", "w+");
}

int main()
{
    int i=0;
    init_daemon();
    //fp = fopen("/var/log/Log.txt", "w+");

    if(fp == NULL){
       // printf("FIle descriptor in not set!\n");
        exit(-1);
    }

    fprintf(fp, "First daemon started.\n");
    fflush(fp);
    
    Out_action act, *out_action = &act;

    act.change=0;
    while (1)
    {
         db_check_command(out_action);
		if (act.change == 1){
		    out_command(out_action);
                    act.change=0;
		}
        fprintf(fp, "Daemon loop...\n");
        fflush(fp);
        sleep (1);
        if(i>10) {
            system("fswebcam --no-banner --jpeg 85 -r 640x480 /srv/http/cimage.jpg");
            i=0;
        }
        i++;
        // break;
    }

    fprintf(fp, "First daemon terminated.\n");
    fflush(fp);
    deinit_daemon();

    return EXIT_SUCCESS;
}




