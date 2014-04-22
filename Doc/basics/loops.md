
# Loops

There are two types of loops : for and while.

The condition part always is an arithmetic scope.

Any variables declared in the for condition is local to its scope.

## for

There are to forms of 'for' loops. classic and read.

### Classic

Example:
```
for i = 0; i < 10; i++ {
  echo -n i
} # prints '0123456789'

# Alternative form :
for i = 9; i >= 0; i--;
  echo -n i
endfor # prints '9876543210'

```

### read

The read form read a lines into the specified var.
It can read lines from files, buffers and named pipes. 
The variable is local to the for scope

Example:
```
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
  i=[i++]
} # print the token list (parse a csv file)

# named pipes
cat test.txt |:ptest
for read :ptest in line {
  echo line
} # print the file (useless use of a named pipe ...)

```

