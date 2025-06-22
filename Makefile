
PREFIX = "/usr/local"

# The default target usually compiles the project. But in this project, there is nothing to compile.
# Since we don't want that an unexpected target is executed when the user simply hits "make" on the
# command line, we add a phony default target "nothing" which merely prints a message.

nothing :
	@echo "Nothing to compile - this is a header-only library"

install :
	cp easytest.hpp $(PREFIX)/include
	cp easytest.sh $(PREFIX)/lib

uninstall :
	rm -f $(PREFIX)/include/easytest.hpp
	rm -f $(PREFIX)/lib/easytest.sh

.PHONY : nothing

