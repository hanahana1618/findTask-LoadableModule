#include <linux/init.h>      // Macros used to mark up functions e.g., __init __exit
#include <linux/module.h>    // Core header for loading LKMs into the kernel
#include <linux/kernel.h>    // Contains types, macros, functions for the kernel - printk()
#include <linux/errno.h>     // error codes
#include <linux/sched.h>     //scheduler  
#include <linux/string.h> //kernel string library 


MODULE_LICENSE("GPL");       ///< The license type -- this affects runtime behavior
MODULE_AUTHOR("Jorge Lima");       ///< The author -- visible when you use modinfo
MODULE_DESCRIPTION("A simple Linux Loadable Module");  ///< The description -- see modinfo
MODULE_VERSION("1.0");              ///< The version of the module

static char *name = "init";   ///< An example LKM argument -- default value is "world"
struct stask_struct *task; ///<Pointer to task structure
static void find_proc(char *process); ///<Function to find a specidied running process

module_param(name, charp, S_IRUGO);
///< Param desc. charp = char ptr, S_IRUGO can be read/not changed

MODULE_PARM_DESC(name, "The name of the process to be found");  ///< parameter descript

/** @brief The LKM initialization function
 *  The static keyword restricts the visibility of the function to within this C file. The __init
 *  macro means the function is only used at initialization
 *  time and that it can be discarded and its memory freed up after that point.
 *  @return returns 0 if successful
 */
static int __init hello_init(void){
	printk(KERN_INFO "init function\n");
 	 find_proc(name);
  	 return 0;
}


/**@brief The find_proc function iterate over the task struct to find 
* the process given by user. I found it prints the process PID and name
* if not, it prints not found
*/
static void find_proc(char *process)
{
	unsigned char not_found = 1; 
	for_each_process(task) {
		if(!strcmp(task->comm,process)){
			printk(KERN_INFO "for_each_process()\n");
			not_found = 0;
		}
	  }	

	if(not_found)
	{
		printk(KERN_INFO "Process <%s> not found\n",process);
	}
}


/** @brief The LKM cleanup function
*  Similar to the initialization function, it is static. The __exit macro notifies if this
*  code is used for a built-in driver (not a LKM) that this function is not required.
*/
static void __exit hello_exit(void){
   printk(KERN_INFO "TDR: Goodbye %s from the Test LKM!\n", name);
}

/** @brief A module must use the module_init() module_exit() macros from linux/init.h, 
*   which identify the initialization function at insertion time and the cleanup function 
*/

module_init(hello_init);
module_exit(hello_exit);




