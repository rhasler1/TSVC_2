include ../makefiles/Makefile.defs

COMMON_FILES = dummy.o common.o driver.o
BIN_DIR = ../bin/$(COMPILER)
libs = -lm


$(BENCHMARK)_novec: $(BIN_DIR)/$(BENCHMARK)_novec
	@true

$(BENCHMARK)_vec: $(BIN_DIR)/$(BENCHMARK)_vec
	@true

$(BENCHMARK)_llm_vec: $(BIN_DIR)/$(BENCHMARK)_llm_vec
	@true

$(BIN_DIR)/$(BENCHMARK)_%: $(BENCHMARK)_%.o $(COMMON_FILES)
	@mkdir -p $(BIN_DIR)
	$(CC) $^ $(libs) -o $@
	@rm $^


# Compilation rules
%_novec.o: benchmark_$(BENCHMARK).c
	$(CC) $(flags) $(novecflags) -c -o $@ $<

%_llm_vec.o: benchmark_$(BENCHMARK)_llm_vec.c
	$(CC) $(flags) $(novecflags) -c -o $@ $<

%_vec.o: benchmark_$(BENCHMARK).c
	$(CC) $(flags) $(vecflags) -c -o $@ $<

driver.o: driver.c
	$(CC) $(flags) -c -o $@ $<

dummy.o: dummy.c
	$(CC) $(flags) -c -o $@ $<

common.o: common.c
	$(CC) $(flags) -c -o $@ $<


.PHONY: clean
clean:
	rm -f *.o
	rm -f $(BIN_DIR)/*
