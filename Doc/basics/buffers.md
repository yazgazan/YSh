
# Buffers

Buffers can be used as temporary files, except that no files are created.
There are no limits on the memory used by Buffers, it should thus be used carefully.

## Creation

Buffers are automatically created when declared within a redirection, deletion will be automatic when the buffer gets empty :

```bash
cat > @buffname
```

Buffers can be created outside a redirection, deletion is not automatic.

```bash
create_buff "buffname"
```

Note :

- an alternative would be the have the buffer destroyed when the buffer *gets* empty (thus after having been filled).  
  The difference between a `create_buff` and a @ buffer is that the @ buffer will be destroyed immediatly after beeing created if it is still empty.

Note : the '@' token is used to specify the buffer creation. Therefore is useless if the buffer was already created :

```bash
create_buff "buffname"
cat > buffname
```

(Though the '@' is still required in interactive mode since we must differentiate the buffer name from a file name)


## Deletion

Buffers are automatically deleted when they are empty.

```bash
cat < buffname
cat < @buffname # in interactive mode
```

Manually created buffers can be deleted with the delete\_buff builtin :

```bash
delete_buff "buffname"
```

## Builtins tools

```bash
list_buff # list all opened buffers (should display the buffers size with -l[h] option).
create_buff "buffname" [buff_size] # create a new buffer (a buffer size can be specified so the buffer is pre-allocated, the buffer will still be able to grow though)
delete_buff buffname # delete a manualy created buffer
cat_buff buffname # print the buffer content to standard output, buffer is not consumed
echo buffer # buffers support string conversion
```

Note that if a buffer is created twice using `create_buff`, it will not be emptied. A side effect will be that using the '@' identifier with cat\_buff or in strings convertion (echo ...) won't change a thing (except ensuring the buffer exists or the variable represent a buffer) :

```bash
toto="plop"
echo toto # will print "plop", toto is consumed
echo @toto # prints nothing, toto is empty
toto="plop"
echo @toto # prints 'toto', toto is consumed
```

