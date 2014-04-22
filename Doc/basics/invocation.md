
# Invocation

YSh usage :

```
  ysh [-C configscript] [-s dump.file]
  ysh [-s dump.file] scriptname [script arguments ...]
  ysh [-s dump.file] -[i]c command [command arguments ...]
  ysn [-s dump.file] [-i] scriptname [script arguments ...]
```

- -i --interactive : run a repl at the end of the command/script, similar to the repl builtin
- -c --command : execute the following command.
- -C --config : source configscript before running repl
- -s --state : load states (env/vars/funcs/aliases ...) from dump.file

Config script naming (in priority order) :
- `[install dir]/yshrc`
- `$HOME/.yshrc`
- `$(pwd)/.yshrc`

Notes :

- In the first form, the default configscript will be loaded (see 'Config script naming' above) if -C is not present.
- The last three forms can't load any configscript
- With -i options, no configscript will be loaded, you can however source your own. Moreover, any script-only functionalities will be disable before runing the repl.
- The state file is loaded just before interactive/command/script. It will override configscript/env.
- The state file may be used to represent a finite-state machine.

