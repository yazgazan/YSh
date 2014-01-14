
# Variables Scopping

Variables can be local or globals. Variables are local by default.

Local variables are accessible in the curent scope only (or any nested scope).

Here is the list of scopes :

- global scope
- function
- loop
- anonyme scope
- arithmetic scope

Functions arguments does not overwrite global scope variables.

Globals variables are accessibles in any scope. Uppercase variables are globals by default.

Example :

```
test1=ha
test2=ho

echo "$test1" # print 'ha'

function testfn($test1) {
  test3=hey

  echo "$test1" # will print the first argument value
  echo "$test2" # will print 'ho'
  echo "$test3" # will print 'hey'
}

testfn 'hi' # will print 'hi' and 'ho'

echo "$test1" # will print 'ha'
echo "$test3" # $test3 is not defined here, it will print ''
```

You can specify whether a variable is local or global.

```
localvar="hello world"

{ #anonyme scope

  test1=ha
  global test2=ho
  TEST3=hey
  local TEST4=blah

  echo "$localvar" # upper scope variables are accessible, will print 'hello world'
}

echo "$test1" # $test1 is not defined here, it will print ''
echo "$test2" # $test2 has been defined as global, it will print 'ho'
echo "$TEST3" # $TEST3 is Uppercase, it is defined as global, will print 'blah'
echo "$TEST4" # $TEST4 is define as local, will print ''

```

Only loops and anonyme scopes can access upper scope variables, functions can't.

