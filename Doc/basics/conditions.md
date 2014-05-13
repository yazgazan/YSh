
# Conditions

There is only one type of conditions : if. No switch here.

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

# alternative form
if toto < 2;
  echo "toto is less than 2"
elseif toto > 2;
  echo "toto is greater than 2"
endif
# prints nothing
```

