################################################################################
PTHREADS_LIB_FLAGS = -pthread
LIBIRCCLIENT_LIB_FLAGS =
include Makefile_libircclient
################################################################################
CFLAGS += -O3
CFLAGS += -D_POSIX_SOURCE
CFLAGS += -D_POSIX_C_SOURCE=200809L
CFLAGS += $(PTHREADS_LIB_FLAGS)
CFLAGS += $(LIBIRCCLIENT_LIB_FLAGS)
################################################################################
EXECUTABLE = jh-irc
SRC_DIR = ./src
################################################################################
export
################################################################################

build: $(EXECUTABLE)

$(EXECUTABLE): $(SRC_DIR)/export.a
	$(CC) $(CFLAGS) -o $@ $<

$(SRC_DIR)/export.a: .JUST_CHECK
	$(MAKE) -C $(SRC_DIR) export.a

clean:
	$(MAKE) -C $(SRC_DIR) clean
	rm -f $(EXECUTABLE)

.JUST_CHECK:
