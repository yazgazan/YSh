
# Invocation

YSh usage :

```
  ysh [-C configscript] [-d dump.file] [-s dump.file] [-i (scriptname | command) [arguments ...]]
  ysn [-d dump.file] [-s dump.file] scriptname [arguments ...]
  ysh [-d dump.file] [-s dump.file] -c command [arguments ...]
```

- -i --interactive : run a repl at the end of the command/script, similar to the repl builtin
- -c --command : execute the following command.
- -C --config : source configscript before running repl (or with -i option).
- -s --state : load states (env/vars/funcs/aliases ...) from dump.file .
- -d --dump : save states (env/vars/funcs/aliases ...) to the dump.file at the end of the script/command/repl.

Config script naming (in priority order) :
- `[install dir]/yshrc`
- `$HOME/.yshrc`
- `$(pwd)/.yshrc`

Notes :

- In the first form, the default configscript will be loaded (see 'Config script naming' above) if -C is not present.
- In the first form, the configscript (default or specified) will be loaded after the command/script execution,  
  possibly overriding functions, variables and such.
- A command/script executed along with the -i option does not have the ability to use the alias builtin.
- The last two forms can't load any configscript
- With -i options, your configscript will be loaded, you can however use -C /dev/null to disable this behavior.  
  Moreover, any script-only functionalities will be disabled before runing the repl.
- The state file is loaded just before interactive/command/script. It might override configscript/env.
- The state file may be used to represent a finite-state machine.  
  Some builtins internal states might not be saved in dump.file (this should be indicated in the builtin's help section).  
  Some internal types (especially from third-party modules) might not be saved in the dump.file either.

