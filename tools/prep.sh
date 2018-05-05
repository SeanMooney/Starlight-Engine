#!/bin/bash

toolDir=$(X= cd -- "$(dirname -- "$0")" && pwd -P)

first_run=${first_run:-False}

if [ "${first_run}" != "False" ]; then
    git submodule init
    git submoulde update
    ../external/vcpkg/bootstrap.sh
fi

sudo apt install -y  xorg-dev libgl-dev libglu-dev
#${toolDir}/../external/vcpkg/vcpkg install libepoxy glfw3 cereal catch2 ms-gsl blaze
${toolDir}/../external/vcpkg/vcpkg install glew glfw3 cereal catch2 ms-gsl spdlog abseil bullet3 eigen3
