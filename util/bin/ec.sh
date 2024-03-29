#!/bin/bash
# ec.bash: echo args with color options

  if [ "$*" == "-?" ]; then
    echo 'usage: ec ...     # (uncolored) echo ...'
    echo '       ec -r ...  # (red)'
    echo '       ec -g ...  # (green)'
    echo '       ec -y ...  # (yellow)'
    echo '       ec -b ...  # (blue)'
    echo '       ec -m ...  # (magenta)'
    echo '       ec -c ...  # (cyan)'
    echo '       ec -0 ...  # (no color)'
    exit 1;
  fi

#===============================================================================
# let's go ...
#===============================================================================

   if [ "$1" == "-r" ]; then
     printf "\x1b[31m"
     shift; echo $*
     printf "\x1b[0m"
     exit 0
   fi

   if [ "$1" == "-g" ]; then
     printf "\x1b[32m"
     shift; echo $*
     printf "\x1b[0m"
     exit 0
   fi

   if [ "$1" == "-y" ]; then
     printf "\x1b[33m"
     shift; echo $*
     printf "\x1b[0m"
     exit 0
   fi

   if [ "$1" == "-b" ]; then
     printf "\x1b[34m"
     shift; echo $*
     printf "\x1b[0m"
     exit 0
   fi

   if [ "$1" == "-m" ]; then
     printf "\x1b[35m"
     shift; echo $*
     printf "\x1b[0m"
     exit 0
   fi

   if [ "$1" == "-c" ]; then
     printf "\x1b[36m"
     shift; echo $*
     printf "\x1b[0m"
     exit 0
   fi

   if [ "$1" == "-0" ]; then
     printf "\x1b[0m"
     shift; echo $*
     exit 0
   fi

#===============================================================================
# default
#===============================================================================

   echo "$*"
