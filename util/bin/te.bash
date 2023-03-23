##!/bin/bash
# te.bash: attach to terminal # use with alias te='source te.bash'

   if [ "$*" == "-?" ]; then
      echo '   usage: te             # start current selected terminal'
      echo '          te -t <tag>    # attach to terminal #<tag>'
      echo '          te -a <tag>    # attach to current selected terminal'
      echo '          te -a <tag>    # attach to current selected terminal'
      echo '          te -d          # print dongle USB device'
      echo ''
      echo '          te -a 1        # attach to NETCAT Terminal #1'
      echo '          te -c 2        # run CU Terminal #2'
      echo '          te -n 1        # run NETCAT Terminal #1'
      echo '          te -t 3        # run TELNET Terminal #3'
      echo '          te -s 2        # run SCREEN Terminal #2'
      echo '          te -u 1        # run TIO Terminal #1 @ USB connection'
      echo ''
      echo '  Environment Varianbles'
      echo '     TE_TYPE             # terminal type'
      echo '     TE_TAG              # terminal tag'
   fi

#===============================================================================
# set TE_TYPE/TE_TAG defaults, and set terminal tag if provided
#===============================================================================

   if [ "$TE_TYPE" == "" ]; then
     export TE_TYPE=TELNET
   fi

   if [ "$TE_PORT" == "" ]; then
     export TE_PORT=19024
   fi

   if [ "$TE_TAG" == "" ]; then
     export TE_TAG=1
   fi

   if [ "$2" != "" ]; then
      TE_TAG=$2
   fi

   if [ "$TE_ARGS" == "" ]; then
      TE_ARGS="-n 1"
   fi

#===============================================================================
# run te without args
#===============================================================================

  if [ "$*" == "" ]; then
     ec -y te $TE_ARGS
     bash $REPO/util/bin/te.bash $TE_ARGS
  fi

#===============================================================================
# run a TELNET terminal
#===============================================================================

   if [ "$1" == "-t" ]; then
      TE_ARGS="$1 $TE_TAG"
      while true; do
#       tel -T 19024        # connect with telnet using port 19024
        telnet localhost $TE_PORT
				clear
				ec -0 "Telnet Terminal #$TE_TAG: connect to telnet @ port $TE_PORT"
				sleep 0.5
      done
   fi

#===============================================================================
# run a NETCAT terminal
#===============================================================================

   if [ "$1" == "-n" ]; then
      TE_ARGS="$1 $TE_TAG"
      while true; do
        nc -vc localhost $TE_PORT   # connect with telnet using given port
        clear
        ec -0 "NETCAT Terminal #$TE_TAG: connect to netcat @ port $TE_PORT"
        sleep 0.5
      done
   fi

#===============================================================================
# run a CU terminal
#===============================================================================

   if [ "$1" == "-c" ]; then
      TE_ARGS="$1 $TE_TAG"
      USB=`te -d`
      ec -y sudo cu -s 115200 -l $USB
      sudo cu -s 115200 -l $USB
   fi

#===============================================================================
# run a TIO terminal
# note: tio --socket inet:19024 `te -d` # redirect USB output to TCP socket/port
#===============================================================================

   if [ "$1" == "-u" ]; then
      TE_ARGS="$1 $TE_TAG"
      USB=`bash $REPO/util/bin/te.bash -d`
      ec -y tio $USB
      tio $USB
   fi

#===============================================================================
# find dongle USB device
#===============================================================================

   if [ "$*" == "-d" ]; then
      ls /dev/tty* | grep usb | grep -v usbmodem000
   fi
