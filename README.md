# LoadableModule
Loadable Module for Linux

In order to debug and see error messages, open another terminal and execute: tail -f /var/log/kern.log

The module takes a parameter, in this case name, and can be set to look for that program instead of the default init. 
Sample: sudo insmod findTask.c name=bash

To remove module:
sudo rmmod findTask
