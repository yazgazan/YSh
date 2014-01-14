
# Buffers

Buffers can be used as temporary files, except that no files are created.
Buffers can be very memory consuming, it should be used with greate care.

## Creation

Buffers are automatically declared when used with redirection :

```
cat > @buffname
```

Buffers can be created outside a redirection, deletion is not automatic.

```
create_buff @buffname
```

## Deletion

Buffers are automatically deleted when they are back to empty.

```
cat < @buffname
```

Manually created buffers can be deleted with the delete\_buff builtin :

```
delete_buff @buffname
```

## Builtins tools

```
create_buff @buffer
list_buff # list all opened buffers
create_buff # create a new buffer
delete_buff # delete a manualy created buffer
cat_buff # print the buffer content to standard output, buffer is not consumed
echo @buffer # buffers support string conversion
```

