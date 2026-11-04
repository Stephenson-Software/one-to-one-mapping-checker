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
# is defined but not called from main(), when one is called more than once
# (which would otherwise hide an uncalled one from a plain count), or when the
# number of `passed` lines differs from the number of registered tests.
test:
	@$(MAKE) --no-print-directory clean testing
	@out=$$(printf 'n\n' | ./testing) || { echo "FAIL: ./testing exited with status $$?"; exit 1; }; \
	printf '%s\n' "$$out"; \
	defined=$$(sed -nE 's/^void (runTest[A-Za-z0-9_]*)\(.*/\1/p' src/testing.cpp | sort); \
	called=$$(sed -nE 's/^[[:space:]]+(runTest[A-Za-z0-9_]*)\(\);.*/\1/p' src/testing.cpp | sort); \
	uncalled=$$(printf '%s\n%s\n' "$$defined" "$$called" | sort | uniq -u); \
	duplicated=$$(printf '%s\n' "$$called" | uniq -d); \
	registered=$$(grep -cE '^[[:space:]]+runTest[A-Za-z0-9_]*\(\);' src/testing.cpp); \
	passed=$$(printf '%s\n' "$$out" | grep -c ' passed'); \
	if printf '%s\n' "$$out" | grep -q ' failed'; then echo "FAIL: a test printed failed"; exit 1; fi; \
	if [ -n "$$uncalled" ]; then echo "FAIL: runTest functions defined but not called from main():" $$uncalled; exit 1; fi; \
	if [ -n "$$duplicated" ]; then echo "FAIL: runTest functions called more than once from main():" $$duplicated; exit 1; fi; \
	if [ "$$passed" -ne "$$registered" ]; then echo "FAIL: $$passed tests passed but $$registered are registered in main()"; exit 1; fi; \
	echo "OK: $$passed/$$registered tests passed"

.PHONY: all clean test
