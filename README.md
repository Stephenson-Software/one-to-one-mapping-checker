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

The solution lives entirely in `src/testing.cpp`. `make` compiles it into an executable named `testing` in the repository root:

```sh
make
```

Because a compiled `testing` is committed to the repository, `make` reports `'testing' is up to date` whenever that artifact is newer than the source. The committed copy is also stored without the executable bit, so it has to be rebuilt before it can be run. Deleting it first forces a rebuild:

```sh
rm -f ./testing && make
```

`cr.sh` bundles that clean rebuild with a run. Its removal step is a bare `rm`, which reports an error when no executable is present, though the script carries on regardless. It carries no shebang and is not marked executable, so it is invoked through a shell rather than as `./cr.sh`:

```sh
bash cr.sh
```

## Running

```sh
./testing
```

The executable first prints the results of its built-in tests, one `passed` or `failed` line each, and then enters an interactive loop prompting `Run another test? (y/n):`. Answering `y` prompts for two strings and reports whether they are one-to-one mapped; any other answer exits. The tests report their results by printing only — the exit status is `0` whether they pass or fail — so the printed lines are the verdict.

The prompt blocks on standard input, so piping input (for example `printf 'n\n' | ./testing`) is required when the executable is run non-interactively.

## Implementation notes

`isOneToOneMapping(s1, s2)` runs the one-directional helper `checkMapping` in both directions, so a mapping is only reported as one-to-one when it holds from `s1` to `s2` *and* from `s2` back to `s1`. That is what makes `foo`/`bar` and `bar`/`foo` both return false: the first conflicts going forward, the second only going back.

Beyond the prompt, `checkMapping` returns false for three classes of input:

- strings of unequal length,
- empty strings — two empty strings are reported as *not* one-to-one mapped,
- strings containing a space character. Only `' '` is checked, so other whitespace such as a tab is accepted.

The interactive prompt reads with `std::cin >>`, which stops at whitespace, so a string containing a space cannot actually be entered there.
