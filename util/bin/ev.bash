#!/bin/bash
# ev.bash: set/list utility related environment variable(s)

  if [ "$*" == "-?" ]; then
    echo '  usage: ev                        # list environment variables'
    echo '         ev -b nrf52dk_nrf52832    # set BOARD'
    echo '         ev -s 682799342           # set SEGGER ID'
    echo ''
    echo '  see also: bd,ec,ev,te,we,ze'
    exit 1;
  fi

#===============================================================================
# no args
#===============================================================================

	if [ "$*" == "" ]; then
    ec -g "Zephyr Settings"
    ec    "  ZEPHYR_BASE: $ZEPHYR_BASE"
    ec -g "Board Settings"
    ec    "  BOARD:       $BOARD"
    ec    "  SEGGER:      $SEGGER"
  fi

#===============================================================================
# set BOARD environment variable
#===============================================================================

  if [ "$1" == "-b" ] && [ "$2" != "" ]; then
    if [ "$3" ==  "" ]; then
      export BOARD="$2"
    else
      bash $REPO/util/bin/ev.bash -?
    fi
  fi

#===============================================================================
# set SEGGER environment variable
#===============================================================================

  if [ "$1" == "-s" ] && [ "$2" != "" ]; then
ec -r $2
    if [ "$3" ==  "" ]; then
      export SEGGER="$2"
    else
      bash $REPO/util/bin/ev.bash -?
    fi
  fi
