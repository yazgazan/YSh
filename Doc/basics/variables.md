
# Variables

## Strings

Strings can be declared with the = operator.
Examples :

```
var1="blah"   # direct from string
var2=$(cmd)   # from a command output
var3=$var4    # from an other variable
```

## objects

Object can be created from the = opeartor :

```
var1=[]   # for arrays
var2={}   # for hashes
```

Objects can only contain strings.
Array's keys can only be numbers.
Hash's keys can only be strings.

Note : as vars can't be numeric values,
numeric strings (as "0") will be considered as a numeric 0 when needed.

## Array

An array is declared empty. It should be filled starting from the first index (0) :

```
array1=[]
array1[0]=25
array1[1]=24
# ...
```

However, if an index is set and that index is not the size of the current array,
the array will grow to that index, filling all unset field with empty strings.

Array's items can be accessed like normal variables :

```
array1=[]
array1[0]=test1
array1[]=test2 # will use next free index
echo $array1[0] # will print "test1"
echo $array1[10] # will print an empty string
```

Undefined indexes resolves to empty string, when an out-of-range index is used,
the array is not grown.

Arrays support string conversion :

```
array=[]
array[]=test1
array[]=test2
echo $array # will print 'test1 test2'
```

## Hash

A Hash is declared empty, it can be filled with whatever key you want to use
as long it is strings

```
hash1={}
hash1[key1]=val1
hash1["hey2"]=val2
hash1[$(cmd)]="val3"
```

Hash's items can be accessed like any variables :

```
hash1={}
hash1[key1]=val1
hash1["hey2"]=val2
echo $hash1[key1] # will print val1
echo $hash1[key2] # will print val2
```

Undefined indexes resolves to empty string.

Hash support string conversion

```
hash1={}
hash1[k1]=v1
hash1[k2]=v2
hash1[k3]=v3
echo $hash1 # will print 'k1=v1 k2=v2 k3=v3'
```

## Builtins helpers

### Array

```
array=[]
array_count $array # print the array size (0 in this case)
array_pop $array # will reduce array size by one
array_pop_back $array # same as array_pop, but delete the first item
array_push_back $array val # shift the array to the right and [0] is set to val
array_delete $array index # delete the specified index, shift the remaining items
array_insert $array index val # insert val to index, other indexes are shifted accordingly
cpy=(array_copy $array) # copy an array
```

### Hashes

```
hash={}
hash_count $hash # print the hash size (0 in this case)
hash_delete $hash index # delete the index
hash_has_index $hash index # return 0 if $hash[index] is defined, a positive number otherwise
hash_get_index $hash val # return first index with $hash[index] == val
hash_count_val $hash val # return the number of val present in $hash
cpy=(hash_copy $hash) # copy a hash
```

