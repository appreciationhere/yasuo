## env
use stm32cubeMX, firware: STM32Cube FW_H7 V1.12.0
make tool :
- xpack-arm-none-eabi-gcc-13.2.1-1.1
- make-3.81-bin + make-3.81-dep
debug :
- xpack-openocd-0.12.0-3
- tracealyzer
- Python 3.13.12
- VSCODE : Cortex-Debug
- art-pi
- stlink

### python
- python -m pip install windows-curses
- python -m pip install kconfiglib


## bared
- cpu 利用率最高  (保证任务除了主动打断, 不会打断)
- 实时响应：前后台系统 + 中断。
- 后台任务伪并行：时间片轮转或事件驱动
- 事件驱动 + 状态机 : 驱动注册和取消注册事件回调; 状态机判断系统状态执行对应操作;

如何保证实时性:
除了中断不会打断任务, 不耗时事件类任务中断中处理
定时器任务分为软和硬;
支持功能:
系统任务队列: system_async_work_add;
定时器(软/硬): 定时执行 类似 uv_timer, 多带了个类型选择参数;
task 延时:

## build
```make menuconfig```
```make```

