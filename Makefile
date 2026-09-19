CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

all: testing

testing: src/testing.cpp
	@echo "---"
	@echo "Compiling testing.cpp"

	$(CXX) $(CXXFLAGS) src/testing.cpp -o testing

	@echo "Finished compiling testing.cpp"

clean:
	rm -f ./testing

# Rebuild from scratch (the committed binary may be stale or non-executable),
# run the suite non-interactively, and turn its printed verdict into an exit
# status. The tests only print `passed`/`failed` and the binary always exits 0,
# so this target fails when any test prints `failed`, when a runTest*() function
# is defined but not called from main(), or when fewer `passed` lines appear
# than there are registered tests.
test:
	@$(MAKE) --no-print-directory clean testing
	@out=$$(printf 'n\n' | ./testing) || { echo "FAIL: ./testing exited with status $$?"; exit 1; }; \
	printf '%s\n' "$$out"; \
	defined=$$(grep -c '^void runTest' src/testing.cpp); \
	registered=$$(grep -cE '^[[:space:]]+runTest[A-Za-z0-9_]*\(\);' src/testing.cpp); \
	passed=$$(printf '%s\n' "$$out" | grep -c ' passed'); \
	if printf '%s\n' "$$out" | grep -q ' failed'; then echo "FAIL: a test printed failed"; exit 1; fi; \
	if [ "$$defined" -ne "$$registered" ]; then echo "FAIL: $$defined runTest functions defined but $$registered called from main()"; exit 1; fi; \
	if [ "$$passed" -ne "$$registered" ]; then echo "FAIL: $$passed tests passed but $$registered are registered in main()"; exit 1; fi; \
	echo "OK: $$passed/$$registered tests passed"

.PHONY: all clean test
