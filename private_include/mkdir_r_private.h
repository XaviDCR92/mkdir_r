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
#ifndef MKDIR_R_PRIVATE_H
#define MKDIR_R_PRIVATE_H

/**
 * Creates a directory using OS-specific API.
 * @param dir Directory path.
 * @return 0 if successful, -1 otherwise.
 * @note Sets @c errno to @c ENOTDIR if one of the elements from @c path is not
 * a directory.
 */
int mkdir_r_port(const char *const dir);

#endif /* MKDIR_R_PRIVATE_H */
