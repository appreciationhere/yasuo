### Bare Metal
- async work
- log service
- memory manager
- tlfs & slab mm

### frameworks
地基: 包括 mm, rtos 等系统基础平台, 用作基础、通用、跨领域

### services
业务功能服务, 用作具体、完整、有业务属性;通过消息/API对外提供服务

### components
粒度小、复用性高、内聚性强。是构建services和应用的“零件库”, 如加密算法组件,JSON解析组件;
