// SPDX-License-Identifier: UNLICENSED
#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <hello1.h>

MODULE_AUTHOR("Presniakov Artem <6200211@gmail.com>");
MODULE_DESCRIPTION("Hello2 function.");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_PARM_DESC(count, "Кількість викликів функції print_hello.");

extern void print_hello(void); // Оголошення експортованої функції

// Параметр кількості викликів
static unsigned int count = 1;
module_param(count, uint, 0444);

static int __init hello2_init(void)
{
	unsigned int i;

	if (count == 0 || (count >= 5 && count <= 10)) {
		pr_warn("Попередження: продовжуємо з count=%u\n", count);
	} else if (count > 10) {
		pr_err("Помилка: модуль не завантажений через некоректний count=%u\n", count);
		return -EINVAL;
	}

	for (i = 0; i < count; i++) {
		print_hello();
	}

	return 0;
}

static void __exit hello2_exit(void)
{
	pr_info("Модуль Hello2 виключений.\n");
}

module_init(hello2_init);
module_exit(hello2_exit);
