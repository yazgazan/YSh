
# Invocation

YSh usage :

```
  ysh [-C configscript]
  ysh scriptname [script arguments ...]
  ysh -[i]c command [command arguments ...]
  ysn [-i] scriptname [script arguments ...]
```

- -i --interactive : run a repl at the end of the command/script, similar to the repl builtin
- -c --command : execute the following command.
- -C --config : source configscript before running repl

Notes :
- In the first form, the default configscript from $HOME will be loaded. If -C is not present (the configscript name is still to be defined)
- The last three forms can't load any configscript
- With -i options, no configscript will be loaded, you can however source your own. Moreover, any script-only functionalities will be disable before runing the repl.

