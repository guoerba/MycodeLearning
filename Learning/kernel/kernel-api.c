————————————————
1.原子操作
	void atomic_set(atomic_t *v, int i);
	void atomic_add(int i, atomic_t *v);
	void atomic_sub(int i, atomic_t *v);
	void atomic_inc(atomic_t *v);
	void atomic_inc_and_test(atomic_t *v);
	void atomic_add_and_test(int i, atomic_t *v);
	void atomic_add_and_test(int i, atomic_t *v);

————————————————
2.锁
2.1自旋锁
	忙等待，无调度开销
	进程抢占被禁止
	锁定期间不能睡觉
		spinlock_t lock;
		spin_lock_init(&lock);
		spin_lock(&lock); // 获取自旋锁，保护临界区
		...临界区
		spin_unlock(&lock); // 解锁

	spin_lock_irqsave：// 禁止内核抢占，关闭中断，保存中断状态寄存器的标志位
		spin_lock_irq() = spin_lock() + local_irq_disable()
		spin_unlock_irq = spin_unlock() + local_irq_enable()
		spin_lock_irqsave = spin_lock() + local_irq_save()
		spin_lock_irqrestore() = spin_unlock() + local_irq_restore()
		spin_lock_bh() = spin_lock() + local_bh_disable()
		spin_nlock_bh() = spin_unlock() + local_bh_enable()
2.2信号量
	拿不到就切换进程，有调度开销
	锁定期间可以睡觉，不用于中断上下文
		DECLARE_MUTEX(mount_sem);
		down(&mount_sem); //获取信号量，保护临界区
		...临界区
		up(&mount_sem); // 释放信号量
2.3互斥量（代替信号量）
		#include <linux/mutex.h>
		/*静态声明一个互斥量，如果需要动态创建一个互斥量，使用mutex_init()*/
		static DEFINE_MUTEX(mutex);
		mutex_lock(&mutex);
		...临界区
		mutex_unlock(&mutex);
2.4读写锁
	多个执行单元被允许同时进入临界区，读者自旋锁可以这样定义：
		rwlock_t rwlock = RW_LOCK_UNLOCKED;
		read_lock(&rwlock);
		...临界区
		read_unlock(&rwlock);
	如果一个写执行单元，其他的读和写都不被允许进入：
		rwlock_t rwlock = RW_LOCK_UNLOCKED;
		write_lock(&rwlock);
		...临界区
		write_unlock(&rwlock);
2.5读-拷贝-更新（RCU）
	其基本理念是读执行单元不需要加锁，但是写执行单元会变得更加复杂，它们会在数据结构的一份拷贝上执行更新操作

————————————————
3.同步(completion)
	struct completion done;
	static int arm11mcu_spi_txrx(struct spi_device *spi, struct spi_transfer *t)
	{
		init_completion(&done);
		...
		wait_for_completion(&done);
		...
	}
	static irqreturn_t arm11mcu_spi_irq(int irq, void *dev)
	{
		...
		complete(&hw->done);
		return IRQ_HANDLED;
	}

————————————————
4.等待队列
等待队列的用法，阻塞与非阻塞模板
	static ssize_t xxx_write(struct file *file, const char *buffer, size_t count, loff_t *ppos)
	{
		...
		DECLARE_WAITQUEUE(wait, current);//*
		add_wait_queue(&xxx_wait, &wait);//*
		 
		ret = count;
		/*等待设备缓冲可写*/
		do
		{
			avail = device_writable(...);
			if (avail < 0);// 设备不可写
				__set_current_state(TASK_INTERRUPTIBLE); //* 改变进程状态
				
			if (avail < 0) {
				if (file->f_flags & O_NONBLOCK) { // 非阻塞
					if (!ret)
						ret = -EAGAIN;
					goto out;
				}
			}
			schedule(); //* 调度其他进程执行
			if (signal_pending(current)) { //* 如果是因为信号唤醒
				if (!ret)
					ret = -ERESTARTSYS;
				goto out;
			}
		} while(avail < 0);

		/*写设备缓冲区*/
		device_write(...);

		out:
		remove_wait_queue(&xxx_wait, &wait); //* 将等待队列移出等待队列头
		set_current_state(TASK_RUNNING); //* 设置进程状态为运行态
		return ret;
	}

————————————————
5.Linux内核延时
5.1忙等待（cpu空转）
	/*等待发生在不能引起睡眠的情况*/
	void ndelay(unsigned long nsecs);
	void udelay(unsigned long usecs);
	void mdelay(unsigned long msecs);
	/*延迟100个jiffies*/
	unsigned long delay = jiffies + 100;
	while(time_before(jiffies, delay));

	/*再延迟2s*/
	unsigned long delay = jiffies + 2*HZ
	while(time_before(jiffies, delay));
	
5.2睡眠延时(将cpu释放给别的线程)
	void msleep(unsigned int millisecs);
	unsigned long msleep_interruptible(unsigned int millisecs);
	void ssleep(unsigned int seconds);
	sleep_on_timeout(wait_queue_head_t *q, unsigned long timeout);
	interruptible_sleep_on_timeout(wait_queue_head_t *q, unsigend long timeout);

————————————————
6.内核定时器
	在Linux内核中，timer_list结构体的实例对应一个定时器
	struct timer_list {
		struct list_head entry;//定时器列表
		unsigned long expires;//定时器到期时间
		void (*function)(unsgiend long);//定时器处理函数
		unsigned long data;// 作为参数被传入定时器处理函数
		struct timer_base_s *base;
	}
	当定时器满后，function成员将被执行，data成员是传入其中的参数，expires则是定时器到期时间
	void init_timer(struct timer_list *timer);
	void add_timer(struct timer_list *timer);
	void del_timer(struct timer_list *timer);
	void mod_timer(struct timer_list *timer, unsigned long expires);
	使用范例：
		xxx_func1(...)
		{
			struct xxx_dev *dev = filp->private_data;
			...
			/*初始化定时器*/
			init_timer(&dev->xxx_timer);
			dev->xxx_timer.function = &xxx_do_timer;
			dev->xxx_timer.data = (unsigned long)dev;
			dev->xxx_timer.expires = jiffies + delay;
			/*添加（注册）定时器*/
			add_timer(&dev->xxx_timer);
		}
		
		/*定时器处理函数*/
		static void xxx_do_timer(unsigned long arg)
		{
			struct xxx_device *dev = (struct xxx_device *)arg;
			...
			/*调度定时器再执行*/
			dev->xxx_timer.expires = jiffies + delay;
			add_timer(&dev->xxx_timer);
			...
		}

————————————————
7.软中断
7.1Tasklet
	/*定义tasklet和底半部函数并关联*/
	void xxx_do_tasklet(unsigned long);
	DECLARE_TASKLET(xxx_tasklet, xxx_do_tasklet, 0);// 定义了一个名为xxx_tasklet的tasklet_struct结构体的实例
	/*中断处理底半部函数*/
	void xxx_do_tasklet(unsigned long)
	{
		...
	}
	/*中断处理顶半部*/
	irqreturn_t xxx_interrupt(int irq, void *dev_id, struct pt_regs *regs)
	{
		...
		tasklet_schedule(&xxx_tasklet);
		...
	}
	
