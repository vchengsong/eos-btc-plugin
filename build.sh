#!/usr/bin/env bash

SOURCE_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

ARCH=$( uname )
if [ "${SOURCE_DIR}" == "${PWD}" ]; then
  BUILD_DIR="${PWD}/build"
else
  BUILD_DIR="${PWD}"
fi
#CMAKE_BUILD_TYPE=Release
CMAKE_BUILD_TYPE=Debug

BUILD_DIR="${PWD}/build"


if [ ! -d "${BUILD_DIR}" ]; then
  if ! mkdir -p "${BUILD_DIR}"
  then
     printf "Unable to create build directory %s.\\n Exiting now.\\n" "${BUILD_DIR}"
     exit 1;
  fi
fi

if ! cd "${BUILD_DIR}"
then
  printf "Unable to enter build directory %s.\\n Exiting now.\\n" "${BUILD_DIR}"
  exit 1;
fi


if [ -z "$CMAKE" ]; then
  CMAKE=$( command -v cmake )
fi

if ! "${CMAKE}"  "${SOURCE_DIR}"
then
  printf "\\n\\t>>>>>>>>>>>>>>>>>>>> CMAKE building has exited with the above error.\\n\\n"
  exit -1
fi

if ! make -j1
then
  printf "\\n\\t>>>>>>>>>>>>>>>>>>>> MAKE building has exited with the above error.\\n\\n"
  exit -1
fi





