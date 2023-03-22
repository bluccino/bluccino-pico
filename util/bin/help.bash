#!/bin/bash
# help: help for Pico utilities

  if [ "$*" == "" ]; then
    echo  "  help bash   # help on BASH commands"
    echo  "  help pico   # help on PICO utilities"
    exit 0
  fi

  if [ "$*" == "bash" ]; then
    ec -g "Help on BASH commands"
    bash -c help
    exit 0
  fi

  if [ "$*" == "pico" ]; then
    ec -g "Help on PICO utilities"
    echo  "  ec -?       # echo args with color options"
    echo  "  bd -?       # board setup"
    echo  "  te -?       # terminal utility"
    echo  "  we -?       # west command shorthands"
    echo  "  ze -?       # select zephyr version"
    exit 0
  fi
