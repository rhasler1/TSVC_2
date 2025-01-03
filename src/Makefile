include ../makefiles/Makefile.defs

COMMON_FILES = dummy.o common.o

BIN_DIR = ../bin/$(COMPILER)

libs = -lm

# Add specific flags for AVX-enabled compilation
BENCHMARK_VEC_FLAGS = -W -O3 -mavx2 -lm -ftree-vectorizer-verbose=3 -ftree-vectorize -fopt-info-vec-optimized -g

# Default target builds everything
all : $(BIN_DIR)/tsvc_vec $(BIN_DIR)/tsvc_novec $(BIN_DIR)/benchmark $(BIN_DIR)/benchmark_llm_vec

# Targets for "make benchmark" and "make benchmark_vec"
benchmark: $(BIN_DIR)/benchmark

benchmark_llm_vec: $(BIN_DIR)/benchmark_llm_vec
	@true

# Rule to build the benchmark binary
$(BIN_DIR)/benchmark : benchmark.o driver.o $(COMMON_FILES)
	@mkdir -p $(BIN_DIR)
	$(CC) $^ $(libs) -o $@

# Rule to build the benchmark_llm_vec binary
$(BIN_DIR)/benchmark_llm_vec : benchmark_llm_vec.o driver.o $(COMMON_FILES)
	@mkdir -p $(BIN_DIR)
	$(CC) $^ $(libs) -o $@

# Compile rules for benchmark.c and driver.c
benchmark.o : benchmark.c
	$(CC) $(flags) -c -o $@ $<

benchmark_llm_vec.o : benchmark_llm_vec.c
	$(CC) $(flags) $(BENCHMARK_VEC_FLAGS) -c -o $@ $<

driver.o : driver.c
	$(CC) $(flags) -c -o $@ $<

dummy.o : dummy.c
	$(CC) $(flags) -c -o $@ $<

common.o : common.c
	$(CC) $(flags) -c -o $@ $<

# Original rules
%_novec.o:%.c .FORCE
	$(CC) $(flags) $(novecflags) -c -o $@ $<

%_vec.o:%.c .FORCE
	$(CC) $(flags) $(vecflags) -c -o $@ $<

# Compiled with IEEE math flags to make initialization/checksum calculations more reproducible
%.o:%.c .FORCE
	$(CC) $(flags) $(vecflags) $(ieee_math_flags) -c -o $@ $<

.PHONY: .FORCE clean all benchmark benchmark_vec
.FORCE:
	@true

clean :
	rm -f *.o *.s $(BIN_DIR)/benchmark $(BIN_DIR)/benchmark_llm_vec