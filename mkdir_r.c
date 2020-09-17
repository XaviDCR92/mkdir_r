/*
   Copyright 2020 Xavier Del Campo Romero

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
#include "mkdir_r.h"
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <stdio.h>

static int mkdir_r_lvl(const char *const path, int level)
{
    int ret = -1;
    char *dir = NULL;
    DIR *d = NULL;

    if (!strlen(path))
        goto exit;

    const char *c = path;
    int cur_level = 0;

    while (cur_level <= level)
    {
        for (; *c && *c != '\\' && *c != '/'; c++)
            ;

        if (*c)
            c++;

        cur_level++;
    }

    const size_t sz = c - path + 1;

    dir = malloc(sz);

    if (!dir)
        goto exit;

    memcpy(dir, path, sz - 1);
    dir[sz - 1] = '\0';

    d = opendir(dir);

    if (!d && mkdir(dir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH))
    {
        perror("mkdir");
        goto exit;
    }

    if (*c)
        mkdir_r_lvl(path, cur_level);

    /* No more levels left. */
    ret = 0;

exit:
    if (dir)
        free(dir);

    if (d)
        closedir(d);

    return ret;
}

int mkdir_r(const char *const path)
{
    return mkdir_r_lvl(path, 0);
}
