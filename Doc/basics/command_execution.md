
# Command Substitution / Execution

## Command Substitution

There is only one kind of substitution : Parenthesis

```bash
toto=(ls) # expand to ls' standard output
echo toto
echo "dir : $(ls)" # the '$' specifier is required in string and interactive contexts
```

Note : outputs other than the standard output won't be wrapped unless you redirect theme to the first fd (&>1)

