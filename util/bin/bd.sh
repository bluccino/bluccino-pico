##!/bin/bash
# bd.sh: board selection (setup BOARD environment variable)

   if [ "$*" == "-?" ]; then
      echo '  usage: bd                               # show board settings'
      echo '         bd -l                            # list all boards'
      echo '         bd -! <tag> <id> <segger> <info> # define a board'
      echo '         bd <tag>                         # select board by given tag'
      echo ''
      echo '         bd -! 832dk nrf52dk_nrf52832 682799342    # define a board `832dk`'
      echo '         bd -! 840dk nrf52840dk_nrf52840 683483566 # define a board `840dk`'
      echo '         bd -! dongle nrf52840dongle_nrf52840      # define a board `dongle`'
      echo ''
      echo '         bd 832dk                  # select board `832dk`'
      echo ''
      echo '  see also: bd,ec,ev,te'
      #exit 0
   fi

#===============================================================================
# define board
#===============================================================================

  if [ "$1" == "-!" ]; then
    shift
    if [ "$1" == "" ]; then
      bash $REPO/util/bin/bd.sh -?
    else
      export BRDID="$1"
      export BOARD="$2"
      export SEGGER="$3"
      export BRDINFO="$4"

      if [ -d "$REPO/util/etc/boards" ]; then
         echo "  export BRDID=$BRDID"      >$REPO/util/etc/boards/$BRDID
         echo "  export BOARD=$BOARD"     >>$REPO/util/etc/boards/$BRDID
         echo "  export SEGGER=$SEGGER"   >>$REPO/util/etc/boards/$BRDID
         echo "  export BRDINFO='"$BRDINFO"'" >>$REPO/util/etc/boards/$BRDID
      else
        ec -r '*** error: missing $REPO/util/etc/boards directory'
      fi
    fi
  fi

#===============================================================================
# list all boards or select board
#===============================================================================

  if [ "$1" == "-l" ]; then
    _TAGS_=`ls $REPO/util/etc/boards`

    ec -g "Defined Boards:"
    for _TAG_ in $_TAGS_
    do
      bash $REPO/util/bin/bd.sh -p $_TAG_
    done

  elif [ "$1" != "" ] && [ "$2" == "" ]; then
    if [ -f $REPO/util/etc/boards/"$1" ]; then
      source $REPO/util/etc/boards/"$1"
      bash $REPO/util/bin/bd.sh
    else
      bash $REPO/util/bin/ec.sh -r "*** error: board $1 not defined!"
    fi
  fi

#===============================================================================
# print board info
#===============================================================================

  if [ "$1" == "-p" ] && [ "$2" != "" ]; then
    source "$REPO/util/etc/boards/$2"
    if [ "$BRDINFO" == "" ]; then
      echo "  $2:  $BOARD, #$SEGGER"
    else
      echo "  $2:  $BOARD, #$SEGGER ($BRDINFO)"
    fi
  fi

#===============================================================================
# summary of board settings
#===============================================================================

  if [ "$*" == "" ] ; then
    ec -g "Board Settings: $BRDID"
    ec    "  BOARD:   $BOARD"
    ec    "  SEGGER:  $SEGGER"
    ec    "  BRDINFO: $BRDINFO"
  fi
