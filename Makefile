COMPILER=GNU
BENCHMARK=

ifndef COMPILER
$(error No compiler specified!)
endif

ifndef BENCHMARK
$(error No benchmark specified!)
endif

SRC_DIR=./src


build_benchmark_novec:
	@$(MAKE) -C $(SRC_DIR) COMPILER=$(COMPILER) BENCHMARK=$(BENCHMARK) $(BENCHMARK)_novec

build_benchmark_vec:
	@$(MAKE) -C $(SRC_DIR) COMPILER=$(COMPILER) BENCHMARK=$(BENCHMARK) $(BENCHMARK)_vec

build_benchmark_llm_vec:
	@$(MAKE) -C $(SRC_DIR) COMPILER=$(COMPILER) BENCHMARK=$(BENCHMARK) $(BENCHMARK)_llm_vec

.PHONY: clean
clean:
	$(MAKE) -C $(SRC_DIR) COMPILER=$(COMPILER) clean

