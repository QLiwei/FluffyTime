# Fluffy Time（ふわふわ時間）

## uCOS3 CPU利用率统计

> 总的CPU利用率\各任务的CPU利用率





```c
/*
************************************************************************************************************************
*                                                DETERMINE THE CPU CAPACITY
*
* Description: This function is called by your application to establish CPU usage by first determining how high a 32-bit
*              counter would count to in 1/10 second if no other tasks were to execute during that time.  CPU usage is
*              then determined by a low priority task which keeps track of this 32-bit counter every second but this
*              time, with other tasks running.  CPU usage is determined by:
*
*                                             OS_Stat_IdleCtr
*                 CPU Usage (%) = 100 * (1 - ------------------)
*                                            OS_Stat_IdleCtrMax
*
* Argument(s): p_err      is a pointer to a variable that will contain an error code returned by this function.
*
*                             OS_ERR_NONE              The call was successful
*                             OS_ERR_OS_NOT_RUNNING    If uC/OS-III is not running yet
*
* Returns    : none
*
* Note(s)    : none
************************************************************************************************************************
*/

void  OSStatTaskCPUUsageInit (OS_ERR  *p_err)
{
    OS_ERR   err;
    OS_TICK  dly;
    CPU_SR_ALLOC();


    err = OS_ERR_NONE;                                          /* Initialize err explicitly for static analysis.       */

#ifdef OS_SAFETY_CRITICAL
    if (p_err == (OS_ERR *)0) {
        OS_SAFETY_CRITICAL_EXCEPTION();
        return;
    }
#endif

#if (OS_CFG_INVALID_OS_CALLS_CHK_EN > 0u)
    if (OSRunning != OS_STATE_OS_RUNNING) {                     /* Is the kernel running?                               */
       *p_err = OS_ERR_OS_NOT_RUNNING;
        return;
    }
#endif

#if ((OS_CFG_TMR_EN > 0u) && (OS_CFG_TASK_SUSPEND_EN > 0u))
    OSTaskSuspend(&OSTmrTaskTCB, &err);
    if (err != OS_ERR_NONE) {
       *p_err = err;
        return;
    }
#endif

    OSTimeDly(2u,                                               /* Synchronize with clock tick                          */
              (OS_OPT  )OS_OPT_TIME_DLY,
              (OS_ERR *)&err);
    if (err != OS_ERR_NONE) {
       *p_err = err;
        return;
    }
    CPU_CRITICAL_ENTER();
    OSStatTaskCtr = 0u;                                         /* Clear idle counter                                   */
    CPU_CRITICAL_EXIT();

    dly = 0u;
    if (OSCfg_TickRate_Hz > OSCfg_StatTaskRate_Hz) {
        dly = (OS_TICK)(OSCfg_TickRate_Hz / OSCfg_StatTaskRate_Hz);
    }
    if (dly == 0u) {
        dly =  (OSCfg_TickRate_Hz / 10u);
    }

    OSTimeDly(dly,                                              /* Determine MAX. idle counter value                    */
              OS_OPT_TIME_DLY,
              &err);

#if ((OS_CFG_TMR_EN > 0u) && (OS_CFG_TASK_SUSPEND_EN > 0u))
    OSTaskResume(&OSTmrTaskTCB, &err);
    if (err != OS_ERR_NONE) {
       *p_err = err;
        return;
    }
#endif

    CPU_CRITICAL_ENTER();
#if (OS_CFG_TS_EN > 0u)
    OSStatTaskTimeMax = 0u;
#endif

    OSStatTaskCtrMax  = OSStatTaskCtr;                          /* Store maximum idle counter count                     */
    OSStatTaskRdy     = OS_STATE_RDY;
    CPU_CRITICAL_EXIT();
   *p_err             = OS_ERR_NONE;
}

```

