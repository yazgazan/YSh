
# Functions

Functions definitions replace any alias/binaries/functions previously declared. However, binaries and alias can still reached, functions can'tt.

## Function declaration

Better with examples :

```
function namefunc1 {
  # ...
}

# alternative form:
function namefunc1;
  # ...
endfunction
```

## arguments

Named and list arguments :

```
function namefunc2(var1, var2) {
  echo $var1 $arguments[0]
  echo $var2 $arguments[1]
}
namefunc2 4 2 # displays `4 4\n2 2`

function namefunc3() {
  echo $arguments[0] $arguments[2]
}
namefunc3 8 3 4 # displays `8 4`
```

