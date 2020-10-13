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
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int mkdir_r_port(const char *const dir)
{
    if (!access(dir, 0))
    {
        struct stat sb;

        if (stat(dir, &sb))
            return -1;
        else if (!(sb.st_mode & S_IFDIR))
        {
            errno = ENOTDIR;
            return -1;
        }
    }
    else if (mkdir(dir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH))
        return -1;

    return 0;
}
