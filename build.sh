#!/bin/bash

###
 # @Author: spongearale
 # @Date: 2024-03-29 22:16:52
 # @LastEditors: spongearale
 # @LastEditTime: 2024-03-29 22:24:00
 # @FilePath: /LeptSound/build.sh
 # @Description: 
 # 
 # Copyright (c) 2024 by spongearale, All Rights Reserved. 
### 

function build() {
    mkdir -p dist
    cmake -B ./build -DCMAKE_BUILD_TYPE=Release
    cmake --build ./build --config Release
}

build
