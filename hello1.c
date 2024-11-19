// SPDX-License-Identifier: UNLICENSED
#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/list.h>
#include <linux/ktime.h>
#include <linux/slab.h>
#include <hello1.h>

MODULE_AUTHOR("Presniakov Artem <6200211@gmail.com>");
MODULE_DESCRIPTION("Hello1 module.");
MODULE_LICENSE("Dual BSD/GPL");

// Структура для списку
struct time_event {
	struct list_head list;
	ktime_t start_time;
	ktime_t end_time;
};

// Голови списку
static LIST_HEAD(time_list);

// Експортована функція
void print_hello(void)
{
	// Створюємо новий елемент
	struct time_event *event = kmalloc(sizeof(*event), GFP_KERNEL);
	if (!event) {
		pr_err("Помилка: не вдалося виділити пам'ять!\n");
		return;
	}

	// Засікаємо час до друку
	event->start_time = ktime_get();
	pr_info("Hello, world!\n");
	// Засікаємо час після друку
	event->end_time = ktime_get();

	// Додаємо елемент до списку
	list_add_tail(&event->list, &time_list);
}
EXPORT_SYMBOL(print_hello);

static void __exit hello1_exit(void)
{
	struct time_event *event;
	struct list_head *pos, *q;

	// Проходимо по списку та виводимо час виконання
	list_for_each_safe(pos, q, &time_list) {
		event = list_entry(pos, struct time_event, list);
		pr_info("Час друку: %lld нс\n",
		        ktime_to_ns(event->end_time) - ktime_to_ns(event->start_time));
		list_del(pos); // Видаляємо елемент зі списку
		kfree(event);  // Звільняємо пам'ять
	}
}

module_exit(hello1_exit);
