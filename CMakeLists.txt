# Copyright 2020 Xavier Del Campo Romero
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
project(mkdir_r)
set(srcs "mkdir_r.c")

if(WIN32)
    set(srcs ${srcs} "win32.c")
else()
    set(srcs ${srcs} "posix.c")
endif()

add_library(${PROJECT_NAME} STATIC ${srcs})
target_include_directories(${PROJECT_NAME} PUBLIC ".")
target_include_directories(${PROJECT_NAME} PRIVATE "private_include")
