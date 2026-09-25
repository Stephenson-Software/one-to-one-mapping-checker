# hacker challenge 4/20/2023

## Prompt
Write a method that returns true or false that can determine whether there exists a one-to-one character mapping from one string s1 to another s2.
For example, given s1 = abg and s2 = bcd, return true since we can map a to b, b to c, and g to d.
Given s1 = foo and s2 = bar, return false since the o cannot map to two different characters.

Please Note that your solution will be judged based on the following criteria: 
Does the solution address the given problem correctly. (Code Correct)
How readable/maintainable is the code? 
How efficient is the code? 

## Building

The solution lives entirely in `src/testing.cpp`. `make` compiles it with `g++ -std=c++17 -Wall -Wextra` into an executable named `testing` in the repository root:

```sh
make
```

Because a compiled `testing` is committed to the repository, nothing is rebuilt whenever that artifact is newer than the source — `make` reports `make: Nothing to be done for 'all'.` and `make testing` reports `make: 'testing' is up to date.`. The committed copy is also stored without the executable bit, so it has to be rebuilt before it can be run. The `clean` target removes it, which forces a rebuild:

```sh
make clean && make
```

Warnings are enabled, and the current source compiles cleanly with no diagnostics.

`cr.sh` bundles that clean rebuild with a run:

```sh
./cr.sh
```

## Running

```sh
./testing
```

The executable first prints the results of its built-in tests, one `passed` or `failed` line each, and then enters an interactive loop prompting `Run another test? (y/n):`. Answering `y` prompts for two strings and reports whether they are one-to-one mapped; any other answer exits. The tests report their results by printing only — the exit status is `0` whether they pass or fail — so the printed lines are the verdict.

The prompt blocks on standard input, so piping input (for example `printf 'n\n' | ./testing`) is required when the executable is run non-interactively.

### Running the tests non-interactively

The `test` target does that piping for you and turns the printed verdict into an exit status:

```sh
make test
```

It rebuilds `testing` from scratch (so the committed copy is never the one run), feeds `n` to the prompt, prints the suite's output, and then exits non-zero if any line contains `failed`, if a `runTest*()` function is defined in `src/testing.cpp` but not called from `main()`, or if fewer `passed` lines appear than there are calls registered in `main()`. On success its last line is `OK: N/N tests passed`, where `N` is the number of registered tests. This is the only invocation whose exit status reflects the test results.

## Implementation notes

`isOneToOneMapping(s1, s2)` runs the one-directional helper `checkMapping` in both directions, so a mapping is only reported as one-to-one when it holds from `s1` to `s2` *and* from `s2` back to `s1`. That is what makes `foo`/`bar` and `bar`/`foo` both return false: the first conflicts going forward, the second only going back.

Beyond the prompt, `checkMapping` returns false for three classes of input:

- strings of unequal length,
- empty strings — two empty strings are reported as *not* one-to-one mapped,
- strings containing a space character. Only `' '` is checked, so other whitespace such as a tab is accepted.

The interactive prompt reads each string as a whole line with `std::getline`, so a string containing a space can be entered there and is rejected by that rule. Only the first character of the `y/n` answer is read; the rest of that line is discarded.
