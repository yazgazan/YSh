
# Job Control

Job Control is inspired from bash's. The only difference is that the '%' is not needed when using bg and bg. Two functions are introduced : kj and detach.

## kj (kill job)

Usage : kj [signal] job

Kill the job. A signal can be provided (example : kj -USR2 1).

## detach (detach job from the shell/script)

Usage : detach job

