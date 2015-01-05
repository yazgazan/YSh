
# Loops

There are only one type of loop : for.

The condition part always is an arithmetic scope, except for `for read ...`.

Any variables declared in the condition is local to the for scope.

## for

There are three forms of 'for' loops : the classic, read and "while" forms.

### Classic form

Example:
```bash
for i = 0; i < 10; i++ {
  echo -n i
} # prints '0123456789'

```

### read form

The read form read a lines into the specified var.
It can read lines from files, buffers and named pipes. 
The variable is local to the for scope

Example:
```bash
# file
for read 'test.txt' in line {
  echo line
} # print the file

# buffer (specifying the newline symbols)
i=0
for read buff1 ";" "\n" in token sep { # note that buff1 must exists as a buffer (though you could use the '@' specifier)
  # here, separators are ; and \n, they are stored in $sep.
  if sep == "\n" {
    echo "new line !"
    i=0
  }
  echo "$i : $token"
  i=[i+1]
} # print the token list (parse a csv file)

# named pipes
cat test.txt |:ptest
for read :ptest in line {
  echo line
} # print the file (useless use of a named pipe ...)

```

### "while" form

```bash

i=0

for i < 10 {
  echo "write a line ..."
  i=[i+1]
}
```

