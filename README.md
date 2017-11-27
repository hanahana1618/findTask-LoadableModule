# LoadableModule
Loadable Module for Linux

The module returns the process id of a process running in Linux. The default process is init, if you wisht to change it then identify the new parameter when inserting the module.

Sample: sudo insmod findTask.ko name=bash

To remove module: sudo rmmod findTask

In order to debug and see error messages, open another terminal and execute: tail -f /var/log/kern.log
