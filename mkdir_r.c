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
#include "mkdir_r_private.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int mkdir_r(const char *const path)
{
    int ret = -1;
    char *dup = NULL;

    if (!path || !*path)
    {
        errno = EINVAL;
        goto exit;
    }

    const size_t sz = strlen(path) + 1;

    dup = malloc(sz);

    if (!dup)
    {
        errno = ENOMEM;
        goto exit;
    }

    memcpy(dup, path, sz);
    char *c = dup;
    const char *dir = dup;
    int exit_fl = 0;

    for (c = dup, dir = dup; !exit_fl; c++)
    {
        switch (*c)
        {
            case '\0':
                exit_fl = 1;
                /* Fall through. */
            case '/':
            {
                const char cb = *c;

                *c = '\0';

                if (!*dir)
                    /* Path starting with delimiter character. */
                    ;
                else if (mkdir_r_port(dir))
                    goto exit;

                dir = dup;
                *c = cb;
            }
            break;
        }
    }

    ret = 0;

exit:
    if (dup)
        free(dup);

    return ret;
}
