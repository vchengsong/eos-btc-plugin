#!/usr/bin/env bash

SOURCE_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

ARCH=$( uname )
if [ "${SOURCE_DIR}" == "${PWD}" ]; then
  BUILD_DIR="${PWD}/build"
else
  BUILD_DIR="${PWD}"
fi
CMAKE_BUILD_TYPE=Release

BUILD_DIR="${PWD}/build"

TIME_BEGIN=$( date -u +%s )


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

if ! "${CMAKE}" -DCMAKE_BUILD_TYPE="${CMAKE_BUILD_TYPE}" -DCMAKE_CXX_COMPILER="${CXX_COMPILER}" \
  -DCMAKE_C_COMPILER="${C_COMPILER}" -DWASM_ROOT="${WASM_ROOT}" -DCORE_SYMBOL_NAME="${CORE_SYMBOL_NAME}" \
  -DOPENSSL_ROOT_DIR="${OPENSSL_ROOT_DIR}" -DBUILD_MONGO_DB_PLUGIN=true \
  -DENABLE_COVERAGE_TESTING="${ENABLE_COVERAGE_TESTING}" -DBUILD_DOXYGEN="${DOXYGEN}" \
  -DCMAKE_INSTALL_PREFIX="/usr/local/eosio" "${SOURCE_DIR}"
then
  printf "\\n\\t>>>>>>>>>>>>>>>>>>>> CMAKE building EOSIO has exited with the above error.\\n\\n"
  exit -1
fi

if [ "${START_MAKE}" == "false" ]; then
  printf "\\n\\t>>>>>>>>>>>>>>>>>>>> EOSIO has been successfully configured but not yet built.\\n\\n"
  exit 0
fi

if [ -z ${JOBS} ]; then JOBS=$CPU_CORE; fi # Future proofing: Ensure $JOBS is set (usually set in scripts/eosio_build_*.sh scripts)
if ! make -j"${JOBS}"
then
  printf "\\n\\t>>>>>>>>>>>>>>>>>>>> MAKE building EOSIO has exited with the above error.\\n\\n"
  exit -1
fi

TIME_END=$(( $(date -u +%s) - ${TIME_BEGIN} ))



