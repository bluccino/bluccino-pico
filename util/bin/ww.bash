#Docker#!/bin/bash
# ww.bash - workwith (work with given environment)
# use with ww (alias ww='source ww.bash')

   if [ "$*" == "-?" ]; then
      echo '   usage: ww <topic>          # work with environment'
      echo '          ww                  # cd $WORK'
      echo '          ww .                # set WORK=`pwd`'
      echo '          ww ..               # cd to parent directory and ww .'
      echo '          ww a                # work with AI (Semantic)'
      echo '          ww <n>              # cd to directory <n>-... and ww .'
      echo ''
      echo '          ww bdoc             # work with Bluccino/bluccino-doc'
      echo '          ww bs               # work with Bluco SW'
      echo '          ww bh               # work with Bluco HW development'
      echo '          ww bl               # work with Bluccino'
      echo '          ww bm               # work with Bluccino/mbed'
      echo '          ww pr               # work with Bluccino/principles'
      echo '          ww br               # work with Blue Railway'
      echo '          ww bq               # work with Bluccino/quicktour'
      echo '          ww c                # work with C-stuff'
      echo '          ww d                # work with Doc'
      echo '          ww do               # work with Docker'
      echo '          ww e                # work with Environment'
      echo '          ww f                # work with 36zero'
      echo '          ww fb               # work with 36zero/beacon'
      echo '          ww fg               # work with 36zero/gateway'
      echo '          ww fl               # work with 36zero/libraries'
      echo '          ww fw               # work with 36zero/wearable'
      echo '          ww fh               # work with 36zero/hardware'
      echo '          ww fm               # work with 36zero/manufacturing'
      echo '          ww f@               # work with fuseAware/@legacy'
      echo '          ww fs               # work with fuseAware/study'
      echo '          ww fx               # work with Floxxo/floxxo'
      echo '          ww h                # work with Jupyter'
      echo '          ww j                # work with Jupyter'
      echo '          ww m                # work with Matlab'
      echo '          ww mc               # work with motor cycle solution display'
      echo '          ww bp               # work with Bluccino/bluccino-pico'
      echo '          ww s                # work with Study'
      echo '          ww t                # work with Train'
      echo '          ww bd               # work with Bluccino/bluccino-develop'
      echo '          ww bdl              # work with Bluccino/bluccino-develop/lessons'
      echo '          ww bds              # work with Bluccino/bluccino-develop/samples'
      echo '          ww bdo              # work with Bluccino/docker'
      echo '          ww bt               # work with Bluccino/Tutorial'
      echo '          ww x                # work with Excellent/lan-driver'
      echo '          ww z                # work with Zstuff'
      echo '          ww zb               # work with Zstuff/blucino'
      echo '          ww zt               # work with Zstuff/traffic'
      echo '          ww Z                # work with Zephyr'
      echo ''
      echo '          ww t1               # setup terminal 1'
      echo '          ww t2               # setup terminal 2'
      echo '          ww t3               # setup terminal 3'
      echo ''
      echo '   multiple args'
      echo '          ww 1 5              # change to 01-.../05-...'
      echo '          ww .. ..            # change to ../..'

   fi

#===============================================================================
# check for 2-digit arg
#===============================================================================

   DIGITS='0 1 2 3 4 5 6 7 8 9'
   PREFIX=''
   for DIGIT in $DIGITS
   do
      if [ "$1" == "$DIGIT" ]; then
         PREFIX=0
      fi
   done

   DIGITS='00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20'

   if [ -d $PREFIX$1-* ]; then
      ec -g $PREFIX$1-*
      cd $PREFIX$1-*
      ww .
   else
      for DIGIT in $DIGITS
      do
         if [ "$PREFIX$1" == "$DIGIT" ]; then
            cd ../$DIGIT-*
            . ww.bash .
         fi
      done
   fi

   if [ "$*" == ".." ]; then
      cd ..
      ww .
   fi

#===============================================================================
# ww command without args (cd to $WORK)
#===============================================================================

   if [ "$*" == "" ]; then
      cd $WORK
      ec -g "working in: $WORK"
      ls
   fi

#===============================================================================
# ww . (set WORK environment variable to match current directory)
#===============================================================================

   if [ "$*" == "." ]; then
      WORK=`pwd`
      ec -y "current working directory: $WORK"
      ls
   fi

#===============================================================================
# BLUCO environment
#===============================================================================

   BLUCOSW=$GIT/Bluco/Bluco-SW
   BLUCOHW=$GIT/Bluco/Bluco-HW

   if [ "$*" == "br" ]; then
      cd $GIT/Train/bluetrain
      bgr -b
   fi

   if [ "$*" == "bs" ]; then
      cd $BLUCOSW
      bgr -b
   fi

# Bluco Hardware

   if [ "$*" == "bh" ]; then
      cd $BLUCOHW
      bgr -m
   fi

# Bluco Project

   if [ "$*" == "bp" ]; then
      cd $GIT/Bluccino/bluccino-pico
      bgr -m
   fi

#===============================================================================
# BLUCCINO environment
#===============================================================================

   if [ "$*" == "bl" ]; then
      cd $BLUCCINO/tutorial
      bgr -b
   fi

   if [ "$*" == "bm" ]; then
      cd $BLUCCINO/mbed
      bgr -b
   fi

   if [ "$*" == "pr" ]; then
      cd $BLUCCINO/principles
      bgr -g
   fi

   if [ "$*" == "bq" ]; then
      cd $BLUCCINO/tutorial/quicktour
      bgr -b
   fi

#===============================================================================
# BLUCCINO training
#===============================================================================

   if [ "$*" == "bt" ]; then
      cd $BLUCCINO/tutorial
      bgr -b
   fi

#===============================================================================
# BLUCCINO develop
#===============================================================================

   if [ "$*" == "bd" ]; then
      cd $BLUCCINO/bluccino-develop
      bgr -b
   fi

   if [ "$*" == "bdb" ]; then
      cd $BLUCCINO/bluccino-develop/ble
      bgr -b; pwd; ls
   fi

   if [ "$*" == "bdl" ]; then
      cd $BLUCCINO/bluccino-develop/lessons
      bgr -b; pwd; ls
   fi

   if [ "$*" == "bdo" ]; then
      cd $BLUCCINO/bluccino-docker
      bgr -b; pwd; ls
   fi

   if [ "$*" == "bds" ]; then
      cd $BLUCCINO/bluccino-develop/samples
      bgr -b; pwd; ls
   fi

   if [ "$*" == "bdz" ]; then
      cd $BLUCCINO/bluccino-develop/zephyr
      bgr -b; pwd; ls
   fi

#===============================================================================
# Bluccino Doc
#===============================================================================

   if [ "$*" == "bdoc" ]; then
      cd $BLUCCINO/bluccino-doc
      bgr -b
   fi

#===============================================================================
# C-stuff
#===============================================================================

   if [ "$*" == "c" ]; then
      cd $GIT/Work/Cstuff
      bgr -c
   fi

#===============================================================================
# Docker
#===============================================================================

   if [ "$*" == "do" ]; then
      cd $GIT/Docker
      bgr -c
   fi

#===============================================================================
# fuseAware
#===============================================================================

   FA360=$FA/36zero

   if [ "$*" == "f" ]; then
      cd $FA
      bgr -r
   fi

   if [ "$*" == "fb" ]; then
      cd $FA360/beacon
      bgr -r
   fi

   if [ "$*" == "fg" ]; then
      cd $FA360/gateway
      bgr -r
   fi

   if [ "$*" == "fl" ]; then
      cd $FA360/libraries
      bgr -r
   fi

   if [ "$*" == "fw" ]; then
      cd $FA360/wearable
      bgr -r
   fi

   if [ "$*" == "fh" ]; then
      cd $FA360/hardware
      bgr -r
   fi

   if [ "$*" == "fm" ]; then
      cd $FA360/manufacturing
      bgr -r
   fi

   if [ "$*" == "f@" ]; then
      cd $FA/@legacy
      bgr -r
   fi

   if [ "$*" == "fs" ]; then
      cd $FA360/study
      bgr -g
   fi

#===============================================================================
# Floxxo
#===============================================================================

   FLOXXO=$GIT/Floxxo/floxxo

   if [ "$*" == "fx" ]; then
      cd $FLOXXO
      bgr -g
   fi

#===============================================================================
# AI/Semantic environment
#===============================================================================

   if [ "$*" == "a" ]; then
      cd $GIT/Semantic
      bgr -r
   fi

#===============================================================================
# DOC environment
#===============================================================================

   if [ "$*" == "d" ]; then
      cd $GIT/Environment/doc
      bgr -y
   fi

# Bluco Hardware

   if [ "$*" == "h" ]; then
      cd $BLUCOHW
      bgr -k
   fi

# Environment

   if [ "$*" == "e" ]; then
      cd $GIT/Environment/usr
      bgr -k
   fi

#===============================================================================
# Excellent
#===============================================================================

   if [ "$*" == "x" ]; then
      cd $GIT/Excellent/lan-driver
      bgr -b
   fi

#===============================================================================
# STUDY environment
#===============================================================================

   if [ "$*" == "s" ]; then
      cd $STUDY
      bgr -g
   fi

#===============================================================================
# Jupyter environment
#===============================================================================

   if [ "$*" == "j" ]; then
      cd $GIT/Semantic/Jupyter
      bgr -m
   fi

#===============================================================================
# Matlab environment
#===============================================================================

   if [ "$*" == "m" ]; then
      cd $GIT/M
      bgr -k
   fi

#===============================================================================
# Motor cycle solution display environment
#===============================================================================

   if [ "$*" == "mc" ]; then
      cd $GIT/Display/mc-solution-display
      bgr -k
   fi

#===============================================================================
# Train
#===============================================================================

   if [ "$*" == "t" ]; then
      cd $GIT/Train/bluetrain
      bgr -b
   fi

# Zephyr demo environment

   if [ "$*" == "z" ]; then
      cd $ZSTUFF
      bgr -y
   fi

# Zephyr demo environment, bluccino demos

   if [ "$*" == "zb" ]; then
      cd $ZSTUFF/bluccino
      bgr -b
   fi

# Zephyr demo environment, traffic demos

   if [ "$*" == "zt" ]; then
      cd $ZSTUFF/traffic
      bgr -r
   fi

# Zephyr environment

   if [ "$*" == "Z" ]; then
      cd $ZEPHYR/zephyr
      bgr -y
      gis
   fi

# Terminal 1

   if [ "$*" == "t1" ]; then
      bgr -bk
      tel -1
   fi

# Terminal 2

   if [ "$*" == "t2" ]; then
      bgr -gk
      tel -2
   fi

# Terminal 3

   if [ "$*" == "t3" ]; then
      bgr -rk
      tel -3
   fi

#===============================================================================
# ww $* (set WORK environment variable to match existing directory)
#===============================================================================

   if [ -d "$*" ] && [ "$*" != "." ] && [ "$*" != ".." ]; then
      cd "$*"
      WORK=`pwd`
      ec -y "current working directory: $WORK"
      ls
   fi

#===============================================================================
# Is there more to do?
# - usage: ww .. ..
#          ww 1 5     # change to 01-.../05-...
#===============================================================================

	if [ "$2" != "" ]; then
    shift
    . ww.bash $*  # continue processing
  fi
