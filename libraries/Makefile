LIBS := libprintf.a klib.a libtinf.a libvtconsole.a

all: $(LIBS)
	@true
	
$(LIBS): %.a: %
	@echo Building library $<
	@make --no-print-directory -C $< all
	@cp $</$@ .

clean:
	@echo Cleaning libs
	@rm $(shell find . -type f -name '*.a') $(shell find . -type f -name '*.o') 2> /dev/null || true
