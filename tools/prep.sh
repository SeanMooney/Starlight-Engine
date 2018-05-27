#!/bin/bash

toolDir=$(X= cd -- "$(dirname -- "$0")" && pwd -P)

first_run=${first_run:-False}

if [ "${first_run}" != "False" ]; then
    git submodule init
    git submoulde update
    ../external/vcpkg/bootstrap.sh
fi

# install opengl deps
sudo apt install -y  xorg-dev libgl-dev libglu-dev

#clean src deps
${toolDir}/../external/vcpkg/vcpkg list | cut -f 1 -d ":" | xargs ${toolDir}/../external/vcpkg/vcpkg remove
#install src deps
${toolDir}/../external/vcpkg/vcpkg install glew glfw3 cereal catch2 ms-gsl spdlog bullet3 glm liblzma
