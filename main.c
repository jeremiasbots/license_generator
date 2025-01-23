#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include "writeLicense.h"

#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
    #define PATH_SEPARATOR "\\"
#else
    #include <unistd.h>
    #define PATH_SEPARATOR "/"
#endif

int fileExists(const char *fileName) {
    struct stat buffer;
    return (stat(fileName, &buffer) == 0);
}

int getActualYear() {
    time_t tiempo_actual = time(NULL);
    if (tiempo_actual == -1) {
        fprintf(stderr, "Error getting time\n");
        return 0;
    }

    struct tm *fecha_local = localtime(&tiempo_actual);
    if (fecha_local == NULL) {
        fprintf(stderr, "Error converting time\n");
        return 0;
    }

    return fecha_local->tm_year + 1900;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: li <command> <type> <filename?>\n");
        return 0;
    }
    if (argv[1] == NULL) {
        printf("Usage: li <command> <type> <filename?>\n");
        return 0;
    }
    if (argv[2] == NULL) {
        printf("Usage: li <command> <type> <filename?>\n");
        return 0;
    }
    if (strcmp(argv[1], "gen") != 0 && strcmp(argv[1], "config-owner") != 0) {
        printf("Usage: li <command> <type> <filename?>\n");
        return 0;
    }
    char *ruta_usuario;
    char ruta_completa[1024];
#if defined(_WIN32) || defined(_WIN64)
    ruta_usuario = getenv("USERPROFILE");
#else
    ruta_usuario = getenv("HOME");
#endif
    if (ruta_usuario == NULL) {
        fprintf(stderr, "Failed to get user directory path.\n");
        return 0;
    }
    snprintf(ruta_completa, sizeof(ruta_completa), "%s%s%s", ruta_usuario, PATH_SEPARATOR, "license_owner.txt");
    if (strcmp(argv[1], "gen") == 0) {
        if (!fileExists(ruta_completa)) {
            fprintf(stderr, "File %s does not exist. Use li config-owner <username>.\n", ruta_completa);
            return 0;
        }
        FILE *fp;
        fp = fopen(ruta_completa, "r");
        if (fp == NULL) {
            fprintf(stderr, "Error opening file %s!\n", ruta_completa);
            return 0;
        }
        char owner[85];
        fgets(owner, 85, fp);
        fclose(fp);
        char *filename;
        if (argv[3] == NULL) {
            filename = "LICENSE.md";
        } else {
            filename = strtok(argv[3], " ");
        }
        char *token = strtok(argv[2], " ");
        if (token != NULL) {
            if (strcmp(argv[2], "mit") == 0) {
                writeMITLicense(getActualYear(), owner, filename);
            }
            if (strcmp(argv[2], "apache2") == 0) {
                writeApache2License(getActualYear(), owner, filename);
            }
            if (strcmp(argv[2], "bsd4") == 0) {
                writeBSD4License(getActualYear(), owner, filename);
            }
            if (strcmp(argv[2], "bsd3") == 0) {
                writeBSD3License(getActualYear(), owner, filename);
            }
            if (strcmp(argv[2], "bsd2") == 0) {
                writeBSD2License(getActualYear(), owner, filename);
            }
            if (strcmp(argv[2], "gplv3") == 0) {
                writeGPLv3License(filename);
            }
            if (strcmp(argv[2], "isc") == 0) {
                writeISCLicense(getActualYear(), owner, filename);
            }
        } else {
            printf("Usage: li <type> <filename?>\n");
            return 0;
        }
    } else if (strcmp(argv[1], "config-owner") == 0) {
        if (argv[2] == NULL) {
            printf("Usage: li config-owner <owner_name>\n");
            return 0;
        }
        FILE *fp;
        fp = fopen(ruta_completa, "w");
        if (fp == NULL) {
            printf("Error opening file!\n");
            return 0;
        }
        char* owner = strtok(argv[2], " ");
        fprintf(fp, owner);
        fclose(fp);
    }
    return 0;
}