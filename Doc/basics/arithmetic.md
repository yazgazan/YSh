
# Arithmetic

opinions needed :

- The bitwise xor operator is ^. This is usualy the logical operator too, but we don't have booleans ...  
  Any idea on how to make the distiction between the bitwise and logical xor ? `^^` ?
- prefixes and suffixes operators ++ and --, four possibilities :
  1. usual c behavior
  1. only suffixes, c behavior
  1. only suffices, prefix behavior
  1. no prefix nor suffix : avoids all possible confusions, improve readability, only one way to do assignation.

IMHO, option 3 or 4 could be the way to go, but this could be confusing for people used to the c behavior and taking advantage of it (which is bad practice im my opinion).

There are two ways to do arithmetic in ysh : inline and scope.
Only floating point (double) numbers are suported.

Unless ==, != or special conditions, everything is considered a number.

## Inline Arithmetic

Example:
```bash
echo "$[1 + 1]" # prints 2
echo [1 + 1] # prints 2
toto=5
echo [toto * 3] # prints 15
function hey(num1, num2) {
  echo [num1 * num1 + num2]
}
echo [toto - $(hey 2 3)] # prints '-2' (note that the subcommand require the '$' specifier in arithmetic scope since parenthesis are interpreted as priority operators)

# conditional structures' conditions are arithmetic
if toto < 6 {
  echo "toto is less than 6 !"
}
```

## Scoped Arithmetic

In an Arithmetic scope, any arguments will be evaluated, expect inside `$()`.

Example:
```bash
function square(n) {
  [
    return n * n
  ]
}
echo (square 2) # prints 4

Alternate form :
function cube(n) [
  return n * n * n
]
echo (cube 2) # prints 8
```

## assignation

Only `=` assignations are concidered valid. no `+=` and such.

```bash
a=1 # valid
a=a+1 # valid
a+=1 # not valid
```

## Available Arithmetics operations

- basic operators : * / + - %
- unaries operators : + -
- prefixs : ++ --
- postfixs : ++ --
- comparaison operators : == > < >= <= !=
- logical operators : ! &&
- bitwise operators : ~ & | ^ << >>
- special conditions (text preservative) : (big bash grep)
  - -a "file" : 1 if file exists.
  - -b "file" : 1 if file exists and is a block special file.
  - -c "file" : 1 if file exists and is a character special file.
  - -d "file" : 1 if file exists and is a directory.
  - -e "file" : 1 if file exists.
  - -f "file" : 1 if file exists and is a regular file.
  - -g "file" : 1 if file exists and is set-group-id.
  - -h "file" : 1 if file exists and is a symbolic link.
  - -k "file" : 1 if file exists and its "ticky" bit is set.
  - -p "file" : 1 if file exists and is a named pipe (FIFO).
  - -r "file" : 1 if file exists and is readable.
  - -s "file" : 1 if file exists and has a size greater than zero.
  - -t fd : 1 if file descriptor fd is open and refers to a terminal.
  - -u "file" : 1 if file exists and its set-user-id bit is set.
  - -w "file" : 1 if file exists and is writable.
  - -x "file" : 1 if file exists and is executable.
  - -G "file" : 1 if file exists and is owned by the effective group id.
  - -L "file" : 1 if file exists and is a symbolic link.
  - -N "file" : 1 if file exists and has been modified since it was last read.
  - -O "file" : 1 if file exists and is owned by the effective user id.
  - -S "file" : 1 if file exists and is a socket.
  - "file1" -ef "file2" : 1 if file1 and file2 refer to the same device and inode numbers.
  - "file1" -nt "file2" : 1 if file1 is newer (according to modification date) than file2, or if file1 exists and file2 does not.
  - "file1" -ot "file2" : 1 if file1 is older than file2, or if file2 exists and file1 does not.
  - -v "varname" : 1 if the shell variable varname exists.
  - -z "string" : 1 if the length of the string is zero.
  - -n "string" : 1 if the length of the string is not zero.

