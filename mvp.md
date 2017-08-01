
I envision YSh to be (at least for now) an experimentation platform. To that effect, it's components
should be easily interchangable. The initial implementation will consist of a basic REPL, separated
in \<N> components:

- the Reader: reads the line from the user (likely to be using readline initialy)
- the Parser: produces an AST from the line read.
- the Interpreter: consumes (and execute) the AST
- the State manager: responsible for the shell's states. The states consist of a collection of
  scoped objects (environment variables, variables, aliases, etc). Only the Interpreter should
  modify the state

In order to start experimenting rapidely, the following features should be implemented in the base
implementation:

- executing a binary with a list of arguments (duh!)
- piping
- control structures (we can probably get away with only implementing the `&&` and `||`)
- environment variables
- locally scoped variables
- basic job control (C-z and `fg`)
- builtins (`fg` and `export` should be enough to start with)
- being able to run a script
- lazy evaluation (necessary for control structures)

Ideally, it would be nice to be able to swap the different components dynamically via shared libraries
(no need to re-compile the main executable).
