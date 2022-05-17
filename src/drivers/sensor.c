#include "sensor.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

sensor sensorNew(char port)
{
    sensor s;
    s.exists = 0;

    DIR *d;
    struct dirent *dir;
    d = opendir(SENSOR_PREFIX);

    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            // match 's' (from "sensor") in dir->d_name to locate sensor directories
            if (dir->d_name[0] == 's') {
                char mdname[40] = SENSOR_PREFIX;
                char mdnamec[35], addr_raw[14];
                strcat(mdname, dir->d_name);
                strcpy(mdnamec, mdname);            // copy mdname to mdnamec
                strcat(mdname, "/address");         // get mdname'/address' file path

                FILE *addr_fp;
                addr_fp = fopen(mdname, "r");
                fgets(addr_raw, 14, addr_fp);        // read address

                // check if found sensor port matches given port
                if (port == addr_raw[12])
                {
                    // copy addr. and concat. aprrop. file names
                    strcpy(s.command, mdnamec);
                    strcpy(s.value, mdnamec);
                    strcpy(s.mode, mdnamec);
                    strcpy(s.decimals, mdnamec);
                    strcat(s.command, "/command");
                    strcat(s.value, "/value");
                    strcat(s.mode, "/mode");
                    strcat(s.decimals, "/decimals");

                    // cache decimals
                    FILE *fp;
                    char val[4];
                    fp = fopen(s.decimals, "r");
                    fgets(val, 4, fp);

                    s.decimal = 1;
                    for (int i = 0; i < atoi(val); i++) s.decimal *= 0.1;
                    fclose(fp);

                    // cache length of `s.value` and shift null terminator
                    s.value_len = strlen(s.value);
                    s.value[s.value_len + 1] = '\0';
                    s.exists = 1;
                    break;
                }
                fclose(addr_fp);
            }
        }
        closedir(d);
    }
    if (!s.exists) printf("Sensor not found on port %c\n", port);
    return s;
}

void sensorSetMode(sensor s, char *mode)
{
    FILE *fp;
    fp = fopen(s.mode, "w");
    fprintf(fp, "%s", mode);
    fclose(fp);
}

void sensorReset(sensor *s)
{
    // update decimals
    FILE *fp;
    char val[4];
    fp = fopen(s->decimals, "r");
    fgets(val, 4, fp);

    s->decimal = 1;
    for (int i = 0; i < atoi(val); i++) s->decimal *= 0.1;
    fclose(fp);
}

void sensorCommand(sensor s, char *command)
{
    FILE *fp;
    fp = fopen(s.command, "w");
    fprintf(fp, "%s", command);
    fclose(fp);
}

int sensorRead(sensor s, char n)
{
    FILE *fp;
    s.value[s.value_len] = n;
    fp = fopen(s.value, "r");

    char val[10];
    fgets(val, 10, fp);

    fclose(fp);
    return atoi(val);
}

double sensorReadDecimal(sensor s, char n)
{
    return s.decimal * sensorRead(s, n);
}
