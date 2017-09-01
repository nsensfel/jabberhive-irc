SUBCOMPONENTS = $(dir $(filter-out "./Makefile",$(wildcard ./*/Makefile)))
SUBCOMPONENTS_EXPORT = $(addsuffix /export.a,$(SUBCOMPONENTS))
################################################################################
SRC_FILES = $(wildcard ./*.c)
OBJ_FILES = $(SRC_FILES:.c=.o)
DEP_FILES = $(SRC_FILES:.c=.d)
################################################################################
build: export.a

export.a: $(OBJ_FILES) $(SUBCOMPONENTS_EXPORT)
	ar -crT $@ $^

$(SUBCOMPONENTS_EXPORT):
	$(MAKE) -C $(dir $@) export.a

clean:
	rm -f $(OBJ_FILES)
	rm -f $(DEP_FILES)
	rm -f export.a
	for subcmp in $(SUBCOMPONENTS) ; do \
		$(MAKE) -C $$subcmp clean ; \
	done
################################################################################
%.d: %.c
	@set -e; rm -f $@; \
		$(CC) -M $(CPPFLAGS) $< > $@.$$$$; \
		sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
		rm -f $@.$$$$

include $(DEP_FILES)
