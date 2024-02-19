# makefile to run tests
# before running make be sure that environment variable BOARD is set accordingly

help:
		@echo '  make samples'
		@echo '  make study-03'

build:
		mkdir build

#===============================================================================
# samples and studies
#===============================================================================

# dependencies

samples: build/samples.log
		@ec -y samples:
		@cat build/samples.log

study-03: build/study-03.log
		@ec -y study/03-console:
		@cat build/study-03.log

#===============================================================================
# making builds in lessons subdirectories
#===============================================================================

build/samples.log: build
		run -o samples.log ../samples nin -pm

build/study-03.log: build
		run -o study-03.log ../study/03* nin -pm
