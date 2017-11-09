#include <linux/init.h>      // Macros used to mark up functions e.g., __init __exit
#include <linux/module.h>    // Core header for loading LKMs into the kernel
#include <linux/kernel.h>    // Contains types, macros, functions for the kernel - printk()
#include <linux/errno.h>     // error codes
#include <linux/sched.h>     //scheduler for the kernel, include the PID info  
#include <linux/string.h>    //include string compare      

MODULE_LICENSE("GPL");       ///< The license type -- this affects runtime behavior
MODULE_AUTHOR("Prieto Castro");       ///< The author -- visible when you use modinfo
MODULE_DESCRIPTION("A Linux loadable module that checks is a process is running and reports it. Written for Embedded OS at FIU.");  ///< The description -- see modinfo
MODULE_VERSION("0.1");              ///< The version of the module

static char *name = "init";   ///< An example LKM argument -- default value is "world"
struct task_struct *task;
//unsigned char flag = 0;

module_param(name, charp, S_IRUGO);
///< Param desc. charp = char ptr, S_IRUGO can be read/not changed

MODULE_PARM_DESC(name, "The name to display in /var/log/kern.log");  ///< parameter descript

/** @brief The LKM initialization function
 *  The static keyword restricts the visibility of the function to within this C file. The __init
 *  macro means the function is only used at initialization
 *  time and that it can be discarded and its memory freed up after that point.
 *  @return returns 0 if successful
 */
static int __init hello_init(void){
   printk(KERN_INFO "TDR: Finding process %s in list of running processes\n", name);

   //task = current->mm;

   for_each_process(task) {
      if(strcmp(task->comm, name)) {
	printk(KERN_INFO "Found process with PID %d", task->pid);
        //flag = 1;
        //break;
        return 0;
      }
      //else {
      //  printk(KERN_INFO "" );
      //}

      //printk("TASK.COMM: Current running process %s\n", task->comm);
   }

   
   printk(KERN_INFO "Not Found %s", name);
   

   return 0;
}


/** @brief The LKM cleanup function
*  Similar to the initialization function, it is static. The __exit macro notifies if this
*  code is used for a built-in driver (not a LKM) that this function is not required.
*/
static void __exit hello_exit(void){
   printk(KERN_INFO "TDR: Goodbye from the Test LKM!\n");
}

/** @brief A module must use the module_init() module_exit() macros from linux/init.h, 
*   which identify the initialization function at insertion time and the cleanup function 
*/

module_init(hello_init);
module_exit(hello_exit);




