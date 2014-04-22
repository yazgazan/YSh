
# Buffers

Buffers can be used as temporary files, except that no files are created.
Buffers can be very memory consuming, it should be used with great care.

## Creation

Buffers are automatically declared when used with redirection :

```
cat > @buffname
```

Buffers can be created outside a redirection, deletion is not automatic.

```
create_buff "buffname"
```

Note : the '@' token is used to specify a buffer is used. Therefore is useless if the buffer was already created :

```
create_buff "buffname"
cat > buffname
```

(Though the '@' is still required in interactive mode since we must differentiate the buffer name from a file name)


## Deletion

Buffers are automatically deleted when they are empty.

```
cat < @buffname
```

Manually created buffers can be deleted with the delete\_buff builtin :

```
delete_buff "buffname"
```

## Builtins tools

```
create_buff "bufname"
list_buff # list all opened buffers
create_buff "buffname" # create a new buffer
delete_buff "buffname" # delete a manualy created buffer
cat_buff "buffname" # print the buffer content to standard output, buffer is not consumed
echo buffer # buffers support string conversion
```

Note that if a buffer is created twice, it will not be emptied. A side effect will be that using the '@' identifier with cat\_buff or in strings convertion (echo ...) won't change a thing (except ensuring the buffer exists or the variable represent a buffer) :

```
toto="plop"
echo toto # will print "plop"
echo @toto # will erease toto and create an empty buffer (prints nothing)
```

