#include <linux/module.h>
#include <linux/init.h>
#include <linux/kmod.h>
#include <linux/earlysuspend.h>
#include <linux/fs.h>

<<<<<<< HEAD
static u64 resumejiffies;

static void fstrim_early_suspend(struct early_suspend *handler)
{
	static u64 awakejiffies;

	awakejiffies += (jiffies - resumejiffies);

	if (awakejiffies >= 360 * HZ) {
=======
static void fstrim_early_suspend(struct early_suspend *handler)
{
	static unsigned long lasttrimjiffies;

	if (jiffies - lasttrimjiffies >= 900 * HZ) {
>>>>>>> 7625a1a... trim /cache partition on suspend if the partition has not been trimmed for more than 15 minutes
		char *argv[] = { "/sbin/fstrim", "/cache", NULL };
		static char *envp[] = {
        		"HOME=/",
        		"TERM=linux",
        		"PATH=/sbin", NULL };

		call_usermodehelper( argv[0], argv, envp, UMH_WAIT_EXEC );

<<<<<<< HEAD
		awakejiffies = 0;
	}
}

static void fstrim_late_resume(struct early_suspend *handler)
{
	resumejiffies = jiffies;
}

static struct early_suspend suspend_fstrim = {
	.suspend = fstrim_early_suspend,
	.resume = fstrim_late_resume,
=======
		lasttrimjiffies = jiffies;
	}
}

static struct early_suspend suspend_fstrim = {
	.suspend = fstrim_early_suspend,
>>>>>>> 7625a1a... trim /cache partition on suspend if the partition has not been trimmed for more than 15 minutes
};

void __init suspend_fstrim_init(void)
{
	register_early_suspend(&suspend_fstrim);
}
