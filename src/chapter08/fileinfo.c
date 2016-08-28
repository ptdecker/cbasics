/* Exercise 8-05:  return size and last modified date of files in a directory recursing through the directories
 *
 * "Modify the fsize program to print the other information contained in the inode entry."
 */

// NOTE: K&R implements custom versions of opendir(), readdir(), and closedir().  At this point, I'm to lazy to
//       do so given the mess that is modern OS development since the authoriship of K&R.  Doing so is left as
//       an exercise to future students.  :-)

/*@ -modobserver */

// Includes

#include <dirent.h>     // for opendir(), readdir(), and closedir()
#include <limits.h>     // for PATH_MAX
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>   // for stat()
#include <time.h>

/*
 * dirwalk:  apply fcn to all files in a directory
 */

static void dirwalk(char *dir, void (*fcn)(char *)) {

    char name[PATH_MAX];
    struct dirent *dp;
    DIR *dfd;

    if ((dfd = opendir(dir)) == NULL) {
        fprintf(stderr, "dirwalk: cannot open %s\n", dir);
        return;
    }

    while ((dp = readdir(dfd)) != NULL) {

        if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0 || dp->d_name[0] == '.')
            continue;

        if (strlen(dir) + strlen(dp->d_name) + 2 > sizeof(name))
            fprintf(stderr, "dirwalk: name %s/%s too long\n", dir, dp->d_name);
        else {
            (void)snprintf(name, PATH_MAX, "%s/%s", dir, dp->d_name);
            (*fcn)(name);
        }
    }

    (void)closedir(dfd);
}

/*
 * finfo: print the size, name, and last modified date of file "name"
 */

static void finfo(char *name) {

    struct stat stbuf;
    time_t filetime;
    char *timestr;

    if (stat(name, &stbuf) == -1) {
        fprintf(stderr, "finfo: cannot access %s\n", name);
        return;
    }

    if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
        dirwalk(name, finfo);

    filetime = stbuf.st_mtime;
    timestr = ctime(&filetime);
    timestr[strlen(timestr)-1] = '\0'; // erase terminating '\n' that ctime() auto adds

    printf("%8lld %s (modified %s)\n", (long long)stbuf.st_size, name, timestr);
}

/* Main */

int main(int argc, char **argv) {

    if (argc == 1)
        finfo(".");
    else
        while (--argc > 0)
            finfo(*++argv);

    exit(EXIT_SUCCESS);
}
