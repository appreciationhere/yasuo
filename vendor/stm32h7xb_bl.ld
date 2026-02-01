SECTIONS  
{
  .init_table : {
    KEEP(*(init.item.0))
    KEEP(*(init.item.1))
    KEEP(*(init.item.2))
    KEEP(*(init.item.3))
    KEEP(*(init.item.4))
    KEEP(*(task.item.0))
    KEEP(*(task.item.1))
    KEEP(*(task.item.2))
    KEEP(*(cli.cmd.0))
    KEEP(*(cli.cmd.1))
    KEEP(*(cli.cmd.2))
    KEEP(*(cli.cmd.3))
    KEEP(*(cli.cmd.4))
  } > FLASH
  .sys_ram : {
    *(.sys_data*)
  } > DTCMRAM AT> FLASH
}
