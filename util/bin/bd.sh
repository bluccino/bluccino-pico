##!/bin/bash
# brd: board selection (setup BOARD environment variable)

   if [ "$*" == "-?" ]; then
      echo '   usage: brd <arg> <tnet>  # NDK52 board #1 selection'
      echo '          brd n1 1          # NDK52 (PCA10040) @ USB 682805980 (for Zephyr v2.7.0)'
      echo '          brd n2 2          # NDK52 (PCA10040) @ USB 682088541 (for Zephyr v2.7.0)'
      echo '          brd n3 3          # NDK52 (PCA10040) @ USB 682947131 (for Zephyr v2.7.0)'
      echo '          brd n4            # NDK52 (PCA10056) @ USB 683483566 (for Zephyr v2.7.0)'
      echo '          brd n5            # NDK52 (PCA10040) @ USB 682799342 (for Zephyr v2.7.0)'
      echo '          brd n6            # nRF21540 SDK     @ USB 683172676 (for Zephyr v2.7.0)'
      echo ''
      echo '          brd p1            # NDK52 (PCA10112) @ USB 683172676 (for Zephyr v2.7.0)'
      echo '          brd p2            # NDK52 (PCA10112) @ USB 683422499 (for Zephyr v2.7.0)'
      echo ''
      echo '          brd N1            # NDK52 (PCA10040) @ USB 682805980 (for Zephyr v1.14.0)'
      echo '          brd N2            # NDK52 (PCA10040) @ USB 682088541 (for Zephyr v1.14.0)'
      echo '          brd N3            # NDK52 (PCA10040) @ USB 682947131 (for Zephyr v1.14.0)'
      echo ''
      echo '          brd nd            # nRF52840 Dongle (PCA10059)'
      echo '          brd s0            # Nucleo L031K6 @ USB 770697819'
      echo '          brd s1            # Nucleo L476RG @ USB 772392233'
      echo '          brd s2            # Nucleo L053RG @ USB 218330737'
      echo '          brd s3            # Nucleo L053RG @ USB 771461457'
      echo '          brd s4            # Nucleo L053R8 @ USB ???'
      echo '          brd m1            # select micro:bit board (BBC Microbit)'
      echo '          brd b1            # select Bluco (via j-link Base #1)'
      echo '          brd b2            # select Bluco (via j-link Base #2)'
      echo '          brd b3            # select Bluco (via j-link Base #3)'
      echo
      echo '          brd W             # select Wearable (via j-link Base b3)'
      echo '          brd B             # select Beacon (via DK board n4)'
      echo
      echo '          brd q3            # select qemu_cortex_m3'
      echo
      echo '          brd               # show current board settings'
      echo ''
      echo '   note: source brd <arg> has equivalent effect'
      echo ''
      echo '   remark: setting connection clause in Segger emProject file:'
      echo '          Connection="USB 770697819"   # Hugos NUCL031 board'
      echo '          Connection="USB 772392233"   # Hugos NUCL476 board'
      echo '          Connection="USB 771721744"   # Hugos NUCL053 board'
      echo '          Connection="USB 683483566"   # Hugos NDK52 #4 board'
      #exit 0
   fi

#===============================================================================
# How to set Segger connection in emProject file:
#
# <!DOCTYPE CrossStudio_Project_File>
# <solution Name="07-l051cub-bluco" target="8" version="2">
#   <project Name="07-l051cub-bluco">
#     <configuration
#       Connection="USB 50125677"
#===============================================================================


   SUMMARY=false              # by default
   TITLE="???"                # empty TITLE

#===============================================================================
# first identify yourself
#===============================================================================

    WHO="???"               # by default

    if [ `whoami` == "hux" ] || [ `whoami` == "ihux" ]; then
        WHO='ihux'
        echo "   board setup for user $WHO:"
    fi

    if [ `whoami` == "arpad" ] || [ `whoami` == "arpadpopradi" ]; then
        WHO='arpad'
        echo "   board setup for user $WHO:"
    fi

    if [ $WHO == "???" ]; then
        echo "*** error: cannot identify user!"
    fi

#===============================================================================
# setup for ihux
#===============================================================================

#-------------------------------------------------------------------------------
# setup NDK52 board environment for ihux
#-------------------------------------------------------------------------------

    if [ $WHO == ihux ] && [ "$1" == "n1" ]; then
        echo "   select Nordic NDK52832 board NDK52 #1 @ $WHO (nRF52-PCA10040)"
        #export BOARD=nrf52_pca10040
        export BOARD=nrf52dk_nrf52832
        export SEGGER="682805980"
        export FLASHING=1
        SUMMARY=true
    fi

    if [ $WHO == ihux ] && [ "$1" == "n2" ]; then
        echo "   select Nordic NDK52832 board NDK52 #2 @ $WHO (nRF52-PCA10040)"
        #export BOARD=nrf52_pca10040
        export BOARD=nrf52dk_nrf52832
        export SEGGER="682088541"
        export FLASHING=1
        SUMMARY=true
    fi

    if [ $WHO == ihux ] && [ "$1" == "n3" ]; then
        echo "   select Nordic NDK52832 board NDK52 #2 @ $WHO (nRF52-PCA10040)"
        #export BOARD=nrf52_pca10040
        export BOARD=nrf52dk_nrf52832
        export SEGGER="682947131"
        export FLASHING=1
        SUMMARY=true
    fi

    if [ $WHO == ihux ] && [ "$1" == "n4" ]; then
        echo "   select Nordic NDK52840 board NDK52 #4 @ $WHO (nRF52-PCA10056)"
#       export BOARD=nrf52840_pca10056
        export BOARD=nrf52840dk_nrf52840
        export SEGGER="683483566"
        export FLASHING=1
        SUMMARY=true
    fi

    if [ $WHO == ihux ] && [ "$1" == "n5" ]; then
        echo "   select Nordic NDK52832 board NDK52 #5 @ $WHO (nRF52-PCA10040)"
        #export BOARD=nrf52_pca10040
        export BOARD=nrf52dk_nrf52832
        export SEGGER="682799342"
        export FLASHING=1
        SUMMARY=true
    fi

    if [ $WHO == ihux ] && [ "$1" == "n6" ]; then
        echo "   select Nordic NDK52840 board NDK52 #6 @ $WHO (nRF52-PCA10056)"
#       export BOARD=nrf52840_pca10056
        export BOARD=nrf52840dk_nrf52840
        export SEGGER="683254604"
        export FLASHING=1
        SUMMARY=true
    fi

# power beacons

    if [ $WHO == ihux ] && [ "$1" == "p1" ]; then
        echo "   select Nordic nRF21540 board NDK52 #7 @ $WHO (nRF52-PCA10112)"
        export BOARD=nrf21540dk_nrf52840
        export SEGGER="683172676"
        export FLASHING=1
        SUMMARY=true
    fi

    if [ $WHO == ihux ] && [ "$1" == "p2" ]; then
        echo "   select Nordic nRF21540 board NDK52 #7 @ $WHO (nRF52-PCA10112)"
        export BOARD=nrf21540dk_nrf52840
        export SEGGER="683422499"
        export FLASHING=1
        SUMMARY=true
    fi

# legacy

    if [ $WHO == ihux ] && [ "$1" == "N1" ]; then
        echo "   select Nordic NDK52832 board NDK52 #1 @ $WHO (nRF52-PCA10040)"
        export BOARD=nrf52_pca10040
        #export BOARD=nrf52dk_nrf52832
        export SEGGER="682805980"
        export FLASHING=1
        SUMMARY=true
    fi

    if [ $WHO == ihux ] && [ "$1" == "N2" ]; then
        echo "   select Nordic NDK52832 board NDK52 #2 @ $WHO (nRF52-PCA10040)"
        export BOARD=nrf52_pca10040
        #export BOARD=nrf52dk_nrf52832
        export SEGGER="682088541"
        export FLASHING=1
        SUMMARY=true
    fi

    if [ $WHO == ihux ] && [ "$1" == "N3" ]; then
        echo "   select Nordic NDK52832 board NDK52 #2 @ $WHO (nRF52-PCA10040)"
        export BOARD=nrf52_pca10040
        #export BOARD=nrf52dk_nrf52832
        export SEGGER="682947131"
        export FLASHING=1
        SUMMARY=true
    fi

# compose title

#  if [ "$BOARD" == "nrf52_pca10040" ] && [ "$SEGGER" == "682805980" ]; then
   if [ "$BOARD" == "nrf52dk_nrf52832" ] && [ "$SEGGER" == "682805980" ]; then
       TITLE="n1 - iHux NDK52 #1"
   fi

#  if [ "$BOARD" == "nrf52_pca10040" ] && [ "$SEGGER" == "682088541" ]; then
   if [ "$BOARD" == "nrf52dk_nrf52832" ] && [ "$SEGGER" == "682088541" ]; then
       TITLE="n2 - iHux NDK52 #2"
   fi

#  if [ "$BOARD" == "nrf52_pca10040" ] && [ "$SEGGER" == "682947131" ]; then
   if [ "$BOARD" == "nrf52dk_nrf52832" ] && [ "$SEGGER" == "682947131" ]; then
       TITLE="n3 - iHux NDK52 #3"
   fi

   if [ "$BOARD" == "nrf52840dk_nrf52840" ] && [ "$SEGGER" == "683483566" ]; then
       TITLE="n4 - iHux NDK52 #4"
   fi

   if [ "$BOARD" == "nrf52dk_nrf52832" ] && [ "$SEGGER" == "682799342" ]; then
       TITLE="n5 - iHux NDK52 #5"
   fi

   if [ "$BOARD" == "nrf52840dk_nrf52840" ] && [ "$SEGGER" == "683254604" ]; then
       TITLE="n6 - iHux NDK52 #6"
   fi

# power beacons

   if [ "$BOARD" == "nrf21540dk_nrf52840" ] && [ "$SEGGER" == "683172676" ]; then
       TITLE="p1 - iHux PowerBeacon"
   fi

   if [ "$BOARD" == "nrf21540dk_nrf52840" ] && [ "$SEGGER" == "683422499" ]; then
       TITLE="p2 - iHux PowerBeacon"
   fi

#-------------------------------------------------------------------------------
# legacy setup for NDK boards
#-------------------------------------------------------------------------------

   if [ "$BOARD" == "nrf52_pca10040" ] && [ "$SEGGER" == "682805980" ]; then
#  if [ "$BOARD" == "nrf52dk_nrf52832" ] && [ "$SEGGER" == "682805980" ]; then
       TITLE="N1 - iHux NDK52 #1"
   fi

   if [ "$BOARD" == "nrf52_pca10040" ] && [ "$SEGGER" == "682088541" ]; then
#  if [ "$BOARD" == "nrf52dk_nrf52832" ] && [ "$SEGGER" == "682088541" ]; then
       TITLE="N2 - iHux NDK52 #2"
   fi

   if [ "$BOARD" == "nrf52_pca10040" ] && [ "$SEGGER" == "682947131" ]; then
#  if [ "$BOARD" == "nrf52dk_nrf52832" ] && [ "$SEGGER" == "682947131" ]; then
       TITLE="N3 - iHux NDK52 #3"
   fi

#-------------------------------------------------------------------------------
# setup nRF52840 dongle environment for ihux
#-------------------------------------------------------------------------------

    if [ $WHO == ihux ] && [ "$1" == "nd" ]; then
        echo "   select nRF52840 dongle @ $WHO (nRF52-PCA10059)"
#       export BOARD=nrf52840_pca10059
        export BOARD=nrf52840dongle_nrf52840
        export SEGGER=""
        export FLASHING=0
        SUMMARY=true
    fi

# compose title

   if [ "$BOARD" == "nrf52840dongle_nrf52840" ]; then
       TITLE="nd - iHux Nordic Dongle"
   fi

#-------------------------------------------------------------------------------
# setup STL476, STL031 and STL053 board environment for ihux
#-------------------------------------------------------------------------------

    if [ $WHO == ihux ] && [ "$1" == "s0" ]; then
        echo "   select STM L031G6 board #0 @ $WHO"
        export BOARD=stm32l031
        export SEGGER="770697819"
        export BOARDID=s0
        export FLASHING=0
        SUMMARY=true
    fi

    if [ $WHO == ihux ] && [ "$1" == "s1" ]; then
        echo "   select STM L476RG board #1 @ $WHO"
        export BOARD=stm32l476rg
        export SEGGER="774369984"
        export BOARDID=s1
        export FLASHING=0
        SUMMARY=true
    fi

    if [ $WHO == ihux ] && [ "$1" == "s2" ]; then
        echo "   select STM L053RG board #2 @ $WHO"
        export BOARD=stm32l053rg
        export SEGGER="218330737"
        export BOARDID=s2
        export FLASHING=0
        SUMMARY=true
    fi

    if [ $WHO == ihux ] && [ "$1" == "s3" ]; then
        echo "   select STM L053RG board #3 @ $WHO"
        export BOARD=nucleo_l053r8
        export SEGGER="771461457"
        export BOARDID=s3
        export FLASHING=0
        SUMMARY=true
    fi

    if [ $WHO == ihux ] && [ "$1" == "s4" ]; then
        echo "   select STM L053R8 board #4 @ $WHO"
        export BOARD=nucleo_l053r8
        export SEGGER=""
        export BOARDID=2163100625
        export FLASHING=0
        SUMMARY=true
    fi

# compose title

   if [ "$BOARD" == "stm32l031" ] && [ "$SEGGER" == "770697819" ]; then
       TITLE="s0 - iHux NUCL031 Board"
   fi

   if [ "$BOARD" == "stm32l476rg" ] && [ "$SEGGER" == "774369984" ]; then
       TITLE="s1 - iHux NUCL0476 Board"
   fi

   if [ "$BOARD" == "stm32l053rg" ] && [ "$SEGGER" == "218330737" ]; then
       TITLE="s2 - iHux NUCL053 Board"
   fi

   if [ "$BOARD" == "nucleo_l053r8" ] && [ "$SEGGER" == "771461457" ]; then
       TITLE="s3 - iHux NUCL053 Board"
   fi

   if [ "$BOARD" == "nucleo_l053r8" ] && [ "$BOARDID" == "2163100625" ]; then
       TITLE="s4 - iHux NUCL053 Board $BOARDID)"
	 fi

#-------------------------------------------------------------------------------
# setup BLUCO environment for ihux
#-------------------------------------------------------------------------------

    if [ $WHO == "ihux" ] && [ "$1" == "b1" ]; then
        echo "   select Bluco @ J-Link base #1 @ $WHO (J-Link Base)"
#       export BOARD=nrf52_pca10040
        export BOARD=nrf52dk_nrf52832
        export SEGGER="50120104"
        export FLASHING=1
        SUMMARY=true
    fi

    if [ $WHO == "ihux" ] && [ "$1" == "b2" ]; then
        echo "   select Bluco @ J-Link base #2 @ $WHO (J-Link Base)"
#       export BOARD=nrf52_pca10040
        export BOARD=nrf52dk_nrf52832
        export SEGGER="50125677"
        export FLASHING=1
        SUMMARY=true
    fi

    if [ $WHO == "ihux" ] && [ "$1" == "b3" ]; then
        echo "   select Bluco @ J-Link base #3 @ $WHO (J-Link Base)"
#       export BOARD=nrf52_pca10040
        export BOARD=nrf52dk_nrf52832
        export SEGGER="50124392"
        export FLASHING=1
        SUMMARY=true
    fi

#-------------------------------------------------------------------------------
# compose title
#-------------------------------------------------------------------------------

#  if [ "$BOARD" == "nrf52_pca10040" ] && [ "$SEGGER" == "50120104" ]; then
   if [ "$BOARD" == "nrf52dk_nrf52832" ] && [ "$SEGGER" == "50120104" ]; then
       TITLE="b1 - iHux Bluco @ j-link Base #1"
   fi

#  if [ "$BOARD" == "nrf52_pca10040" ] && [ "$SEGGER" == "50125677" ]; then
   if [ "$BOARD" == "nrf52dk_nrf52832" ] && [ "$SEGGER" == "50125677" ]; then
       TITLE="b2 - iHux Bluco @ j-link Base #2"
   fi

#  if [ "$BOARD" == "nrf52_pca10040" ] && [ "$SEGGER" == "50124392" ]; then
   if [ "$BOARD" == "nrf52dk_nrf52832" ] && [ "$SEGGER" == "50124392" ]; then
       TITLE="b3 - iHux Bluco @ j-link Base #3"
   fi

   if [ "$BOARD" == "nrf52_pca10040" ] && [ "$SEGGER" == "682088541" ]; then
       TITLE="n2 - iHux NDK52 #2"
   fi

#-------------------------------------------------------------------------------
# setup microbit board environment for ihux
#-------------------------------------------------------------------------------

   if [ $WHO == "ihux" ] && [ "$1" == "m1" ]; then
        echo "select micro:bit board (BBC Microbit)"
        export BOARD=bbc_microbit
        export FLASHING=0
        SUMMARY=true
   fi

#-------------------------------------------------------------------------------
# setup QEMU board environment for ihux
#-------------------------------------------------------------------------------

   if [ $WHO == "ihux" ] && [ "$1" == "q3" ]; then
        echo "select qemu_cortex_m3 board (QEMU)"
        export BOARD=qemu_cortex_m3
        export SEGGER=""
        export FLASHING=0
        SUMMARY=true
   fi

   if [ "$BOARD" == "qemu_cortex_m3" ]; then
       TITLE="q3 - iHux QEMU cortex M3 Board"
   fi

#===============================================================================
# setup for arpad
#===============================================================================

#-------------------------------------------------------------------------------
# setup NDK52 board environment for arpad
#-------------------------------------------------------------------------------

    if [ $WHO == "arpad!" ] && [ "$1" == "n1" ]; then
        echo "select Nordic NDK52 board NDK52 #1 @ $WHO (nRF52-PCA10040)"
        export BOARD=nrf52_pca10040
        export SEGGER=""
        export FLASHING=0
        SUMMARY=true
    fi

#-------------------------------------------------------------------------------
# setup BEACON or WEARABLE environment for ihux
#-------------------------------------------------------------------------------

#WEARABLE

    if [ $WHO == "ihux" ] && [ "$1" == "W" ]; then
        ec -g "   board setup for wearable"
        . board b3
        SUMMARY=""    # suppress summary (already summarized)
    fi

# BEACON

    if [ $WHO == ihux ] && [ "$1" == "B" ]; then
        ec -m "   board setup for beacon"
        . board n4
        SUMMARY=""    # suppress summary (already summarized)
    fi

#===============================================================================
# set telnet index, if provided
#===============================================================================

    if [ "$2" != "" ]; then
       export TNET=$2
    fi

#===============================================================================
# set interface for Segger RTT tools (JLinkExe,JlinkRTTLogger)
#===============================================================================

    export SEGGER_DVC=""      # by default empty

    if [ "$BOARD" == "nrf52dk_nrf52832" ]; then
       export SEGGER_DVC="NRF52832_XXAA"
    fi

    if [ "$BOARD" == "nrf52840dk_nrf52840" ]; then
       export SEGGER_DVC="NRF52840_XXAA"
    fi

#===============================================================================
# summary of board settings
#===============================================================================

    if [ "$SUMMARY" != "" ]; then
        if [ "$TNET" == "" ]; then
            TNET=1
        fi
        ec -g "   current board setting:" $BOARD '('$TITLE')'
        echo "   Segger S/N:            $SEGGER ($SEGGER_DVC) @ Telnet #$TNET"
    fi
