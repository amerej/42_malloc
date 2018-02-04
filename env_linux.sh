#!/bin/bash

export LD_PRELOAD=$PWD/libft_malloc.so 
export LD_LIBRARY_PATH=.
$@