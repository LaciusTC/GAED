INETDIR = $(HOME)/inet4

BUILD_OPTIONS = -f --deep -I$(INETDIR)/src \
				-I$(INETDIR)/src/inet/common/ \
				-L$(INETDIR)/src/ \
				-o simpleNetwork

.PHONY: all clean cleanall makefiles makefiles-dbg checkmakefiles

all: checkmakefiles
	echo "INETDIR = "$(INETDIR)
	cd src && $(MAKE)

clean: checkmakefiles
	cd src && $(MAKE) clean

cleanall: checkmakefiles
	cd src && $(MAKE) MODE=release clean
	cd src && $(MAKE) MODE=debug clean
	rm -f src/Makefile

makefiles:
	echo "INETDIR = "$(INETDIR)
	cd src && opp_makemake $(BUILD_OPTIONS) -lINET

makefiles-dbg:
	cd src && opp_makemake $(BUILD_OPTIONS) -lINET_dbg

checkmakefiles:
	@if [ ! -f src/Makefile ]; then \
	echo; \
	echo '======================================================================='; \
	echo 'src/Makefile does not exist. Please use "make makefiles" to generate it!'; \
	echo '======================================================================='; \
	echo; \
	exit 1; \
	fi
