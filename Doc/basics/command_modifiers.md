
# Command Modifiers

There are two modifiers for commands : `=` and `\`.

Command override schema :

```
 binary \
   |
function =
   |
 alias
```

The `\` modifier will ensure you to fallback on the binary command.

The `=` modifier will ensure you to fallback on the function command. (if there is no such function, the binary is used)

Note : ouside interactive context, the `=` modifier is ineffective.

e.g:
```bash
while ls # /bin/ls

alias ls='ls -l' # (interactive context only)

function ls {
  ls arguments | grep -v %'*.o'
}

# interactive context
ls # B (alias)
=ls # function
\ls # /bin/ls

# any other context
ls # function
=ls # function
\ls # /bin/ls
```

