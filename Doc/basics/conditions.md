
# Conditions

There is only one type of conditions : if. No switch, unless and other fancy conditional structures here.

The condition part always is an arithmetic scope.

Example:
```bash
toto=2

# if / elseif / else
if toto < 2 {
  echo "toto is less than 2"
}
elseif toto > 2 {
  echo "toto is greater than 2"
}
else {
  echo "toto is equal to 2"
} # prints 'toto is equal to 2'

```

Note :

- an empty string is false, any other string is true, unless its a number (0 = false, !0 = true).

