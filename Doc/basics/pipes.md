
# Pipes

## Simple pipes

Simple pipes should work like any other shell.

```bash
  cat "test.txt" | grep 'pattern' | wc -l
```

## Named pipes

The pipeline should be executed as soon as all named pipes have been resolved.

```bash
  cat "test.txt" |:p1,p2
  :p1 | grep 'pattern1' |:res
  :p2 | grep 'pattern2' |:res
  :res | wc -l
```

