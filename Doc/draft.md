
# Draft

Programmers friendly shell. Must be consistant, easy to read/write.

## Used tools :

- gnu readline 
- gnu history
- language yet to be defined (maybe C or Go)

## Basics:

Invocation Usages :

- ysh
- ysh scriptname [script arguments]
- ysh -[i]c command [command arguments]
- ysh [-i] filename [script arguments]

-c flag execute command  
-i flag run a repl in the command/script context

Full pipe/redirection support, and more. Support for multiples redirections.
Native support for buffers and named pipes.

Variables are scopped by default, need keyword to go global.  
Uppercase named variables are global by default  
Every globals are exported  
Scopes include global scope, functions, loops and anonymes scopes. loops and anonymes scopes are different, they will use upper scope variables if exists.  

Full support of list/hash, builtins for `list/hash -> string -> list/hash` conversions, default list/hash conversion  
e.g. :  

- `echo $list` => `item1 item2 item3`
- `echo $hash` => `--key1=item1 --key2=item2 --key3=item3`

Consistant list/hash access : `$list[0]` and `$hash["toto"]`. (no more ${titi[0]} ...)

Support for named arguments for function, no more `arg1=$1; arg2=$2 ...`. (eg : `function toto($arg1, $arg2) ...`)  
Support argument list (eg : `$arguments[0]`)

Flow parsing builtins and string manipulation (field, replace, substr, etc)

Arithmetic evaluation (where all vars are interpreted as numbers)

Obvious support for history, glob and completion.

## non-Basics functionalities :

- module imports (modules don't share global context)
- execution flow control (a script can modifiy itself while running) (wink to @Mayessache) (not available in repl)
- script compilation (translation to compilable language)
- syscalls support (can create socket, open files etc through c wrappers)
- partially self modifiable, using grammar extension, custom hooks and macros

## Variables types

Three variables types available :

- string
- objects (list/hash)
- internal types

Internal types can only be sent to ysh functions and compatibles builtins. Internal types will be used for exececution flow control, syscall wrappers.

Internal types only available using static typing in functions (syntax to be defined)

