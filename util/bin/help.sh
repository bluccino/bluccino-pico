#!/bin/bash
# help: help for Pico utilities

  if [ "$*" == "" ]; then
    echo  "  help bash   # help on BASH commands"
    echo  "  help util   # help on local utilities"
    exit 0
  fi

  if [ "$*" == "bash" ]; then
    ec -g "Help on BASH commands"
    bash -c help
    exit 0
  fi

  if [ "$*" == "util" ]; then
    ec -g "Help on special utilities"
    echo  "  bd -?       # board setup"
    echo  "  ec -?       # echo args with color options"
    echo  "  ev -?       # set/list environment variable(s)"
    echo  "  te -?       # terminal utility"
    echo  "  we -?       # west command shorthands"
    echo  "  ze -?       # select zephyr version"
    exit 0
  fi
