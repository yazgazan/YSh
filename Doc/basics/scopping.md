
# Variables Scopping

opinions needed :

- should conditional structures' body be independent scopes ?
- should arithmetic scopes be scopes ? (any idea for arithmetic scopes that are not scopes ?)
- should uppercase variables should be globals by default ?
- are anonymous scope necessary ? a good idea ?
- could anonymous scopes be replaced by lamda functions ? (see variables.md)
- should functions be able to access upper scope's variables ?

Variables can be local or global. Variables are local by default.

Local variables are accessible in the scope they're declared only (and any nested scopes).

Here is a list of the differents scopes :

- global scope
- function's scope
- loop
- anonyme scope
- arithmetic scope
- interactive scope

Function arguments do not overwrite global scope variables.

Global variables are accessibles in any scope.

Example :

```bash
test1="ha"
test2="ho"

echo test1 # print 'ha'

function testfn(test1) {
  test3="hey"

  echo test1 # will print the first argument value. upper scope's test1 become inaccessible.
  echo test2 # will print 'ho'
  echo test3 # will print 'hey'
}

testfn 'hi' # will print 'hi' and 'ho'

echo test1 # will print 'ha'
echo test3 # test3 is not defined here, won't print anything.
```

You can specify whether a variable is local or global.

```bash
localvar="hello world"

{ #anonyme scope

  test1="ha"
  global test2="ho"
  TEST3="hey"
  local TEST4="blah"

  echo localvar # upper scope variables are accessible, will print 'hello world'
}

echo test1 # test1 is not defined here, it will print ''
echo test2 # test2 has been defined as global, it will print 'ho'
echo TEST3 # TEST3 is Uppercase, it is defined as global, will print 'blah'
echo TEST4 # TEST4 is define as local, will print ''

```

