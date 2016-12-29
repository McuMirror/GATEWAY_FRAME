使用软件版本信息:
Stm32CubeMX       			4.16  
firmware Package for family STM32F4    	1.130
keil       				5.17
	

当前实现的功能:

1:freertos:
包括最多15个任务(包含8个w5500 socket任务,不含空闲任务)
	常驻任务:
		shelltask:处理shell命令
		system_core:维护系统运行
		serial_opeart:处理串口数据
		flash_server:操作本地flash(建议只有这个任务操作flash)
		fatfs_operater:操作SD卡和USB U盘
		watcher_test:用于监视/测试系统
		web_server:为web网页设置占用的socket服务
	非常驻任务:(可以调用函数 产生/结束 任务)
		socket0  socket1 ... socket7 为相应的socket服务

2.fatfs:
SD卡读写   USB U盘读写

3:w5500
tcp服务器  tcp客户机  udp连接  web网页配置

4:业务逻辑:
 字典: 通过shell 添加/查找/删除/保存/载入 
 设备协议: 通过shell 添加/保存/载入
 实现翻译主体框架


