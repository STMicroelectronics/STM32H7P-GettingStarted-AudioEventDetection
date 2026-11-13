/**
  ******************************************************************************
  * @file    gs_utils.c
  * @author  STMicroelectronics AIS application team
  * @version $Version$
  * @date    $Date$
  * @brief   utilities for audio and sensing getting started
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "gs_utils.h"
#include "mx_led.h"
#include "app_config.h"
#include "dpu_config.h"
#include "ai_device_adaptor.h"
#include "cpu_stats.h"
#include "stai.h"
#include "network.h"

#ifdef APP_LCD
#include "oled.h"
#include "pict_baby_cry.h"
#include "pict_bird_chirp.h"
#include "pict_dog_bark.h"
#include "pict_unknown.h"
#include "pict_sleep.h"
#include "pict_clap.h"
#include "pict_rooster.h"
#include "pict_st_logo.h"
#endif

/* Private function prototypes -----------------------------------------------*/
static void print_cpu_stats(void);
static void reset_cpu_stats(void);
static void system_setting_log(void);

#ifdef APP_LCD
typedef struct _ai_class_t {
  const char     *name;
  const uint8_t *picto;
} ai_class_t;
#else
typedef const char * ai_class_t;
#endif

#ifdef APP_LCD
static ai_class_t ai_class[AI_MODEL_CLASS_NUMBER]= \
{
  {"chirping birds", pict_bird_chirp},
  {"clapping", pict_clap},
  {"crying baby", pict_baby_cry},
  {"dog", pict_dog_bark},
  {"rooster", pict_rooster},
};
#else
  static ai_class_t ai_class[AI_MODEL_CLASS_NUMBER]=AI_MODEL_CLASS_LIST;
#endif

static uint32_t prev_ai_disp_tick = 0;

/* External functions --------------------------------------------------------*/

/**
* @brief  Displays System settings
* @param  None
* @retval None
*/
void print_system_setting(void)
{
  system_setting_log();
  PRINTF(SEPARATION_LINE);
#ifdef USE_HSP
  PRINTF("\r\nHSP Acceleration used for Preprocessing\r\n");
#else
  PRINTF("\r\nMCU used for Preprocessing\r\n");  
#endif
}

/**
* @brief  Displays The main menu
* @param  None
* @retval None
*/
void print_menu(void)
{
  static  uint32_t prev_tick=0;
  uint32_t tick = HAL_GetTick();
  if (tick - prev_ai_disp_tick >= AI_DISP_PERIOD)
  {
    prev_ai_disp_tick = tick;
    PRINTF("\r\n\nlistening...                                    \r\n");
    PRINTF("\r\x1B[A\x1B[A\x1B[A");
#ifdef APP_LCD
    oled_load_pict(pict_sleep);
#endif
    fflush(stdout);
  }
  if (tick - prev_tick >= MENU_DISP_PERIOD)
  {
    led_toggle(PROCESS_LED);
    time_stats_store(TIME_STAT_TOT, (float)(tick - prev_tick));
    prev_tick = tick ;
    print_cpu_stats();
    fflush(stdout);
  }
}
/**
  * @brief  Prints the build/version UART header.
  * @param  None
  * @retval None
  */
void print_app_header(void)
{
  PRINTF("\033[2J\033[3J\033[H"); /* clear terminal screen and scrollback */
  PRINTF(SEPARATION_LINE);
  PRINTF("    System configuration (%s)\n\r",APP_CONF_STR);
  PRINTF(SEPARATION_LINE);
  PRINTF("STM32H7P-GettingStarted-AED %s (%s)\n\r", APP_VERSION_STRING, APP_GIT_SHA1_STRING);
  PRINTF("Build date & time: %s %s\n\r", __DATE__, __TIME__);
  PRINTF("Compiler: GCC %d.%d.%d\n\r", __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
  PRINTF("HAL: %lu.%lu.%lu\n\r", (uint32_t)HAL_VERSION_MAIN,
           (uint32_t)HAL_VERSION_SUB1, (uint32_t)HAL_VERSION_SUB2);
  PRINTF("STEdgeAI Tools: %d.%d.%d\n\r", STAI_TOOLS_VERSION_MAJOR, STAI_TOOLS_VERSION_MINOR, STAI_TOOLS_VERSION_MICRO);
  PRINTF("NN model: %s\n\r", LL_ATON_NETWORK_ORIGIN_MODEL_NAME);
  PRINTF(SEPARATION_LINE);
  PRINTF("\n\r");
}

/**
* @brief  Displays Processing start message
* @param  None
* @retval None
*/
void print_header(void)
{
  PRINTF("\r\n");
  PRINTF(SEPARATION_LINE);
  PRINTF("# Start Processing\n\r");
  PRINTF(SEPARATION_LINE);
  PRINTF("| Time(seconds) |  Cpu  |  Pre  |  AI   |\n\r");
  PRINTF(SEPARATION_LINE);
  PRINTF("\033[?25l"); /* hide cursor (\033[?25l) */
}

/**
* @brief  Displays Processing stop message
* @param  None
* @retval None
*/
void print_footer(void)
{
  PRINTF("\r\n\n\n\n\n\n");
  PRINTF(SEPARATION_LINE);
  PRINTF("# Stop Processing\n\r");
  PRINTF(SEPARATION_LINE);
  PRINTF("\033[?25h\r\n"); /* un-hide cursor (\033[?25h) */
  led_off(PROCESS_LED);
}

/**
* @brief  Init CPU usage statistics
* @param  None
* @retval None
*/
void init_cpu_stats(void)
{
  time_stats_init();
  port_dwt_init(); 
  reset_cpu_stats();
}
/**
* @brief  Displays CPU usage statistics
* @param  None
* @retval None
*/
void print_cpu_stats_summary(void)
{
  uint32_t Pre_cnt = time_stats_get_cnt(TIME_STAT_PRE_PROC);
  uint32_t AI_cnt  = time_stats_get_cnt(TIME_STAT_AI_PROC);
  float Pre_avg    = (Pre_cnt == 0 ) ? 0.0F : \
    time_stats_get_sum(TIME_STAT_PRE_PROC) / Pre_cnt;
  float AI_avg    = (AI_cnt == 0 ) ? 0.0F : \
    time_stats_get_sum(TIME_STAT_AI_PROC) / AI_cnt;

  PRINTF("          CPU timing summary \n\r");
  PRINTF(SEPARATION_LINE);
  PRINTF("| Statistics        | Pre-Proc | AI     |\n\r");
  PRINTF(SEPARATION_LINE);
  PRINTF("| Number of call    | %8.0d| %8.0d|\r\n",\
    time_stats_get_cnt(TIME_STAT_PRE_PROC),\
    time_stats_get_cnt(TIME_STAT_AI_PROC));
  PRINTF("| Average (ms)      | %8.2f| %8.2f|\r\n",\
    Pre_avg,AI_avg);
  PRINTF("| Relative load (%%) | %8.2f| %8.2f|\r\n",\
    100*time_stats_get_sum(TIME_STAT_PRE_PROC) / time_stats_get_runtime(),\
    100*time_stats_get_sum(TIME_STAT_AI_PROC) / time_stats_get_runtime() );
  PRINTF(SEPARATION_LINE"\n\r");
}
/**
* @brief  Displays Classification results
* @param  p_out pointer to classification distribution
* @param  classes pointer to lasses array of string
* @retval None
*/
void print_ai_classes_output(float *p_out /*, const char ** classes*/ )
{
  float max_out = p_out[0];
  int max_idx = 0;
  for(int i = 1; i < AI_MODEL_CLASS_NUMBER; i++)
  {
    if(p_out[i] > max_out)
    {
      max_idx = i;
      max_out = p_out[i];
    }
  }
  if (max_out > AI_OOD_THR)
  {
    prev_ai_disp_tick = HAL_GetTick();

#ifdef APP_LCD
    PRINTF("\r\n\n\"%s\" (%d %%) detected after %ld s              \n\r",ai_class[max_idx].name,\
                                    (int)(max_out*100), (uint32_t)(time_stats_get_runtime())/1000);
    if(!oled_load_pict(ai_class[max_idx].picto))
    {
      PRINTF("Failed to load pictogram for class \"%s\"\n\r", ai_class[max_idx].name);
    }
#else
    PRINTF("\r\n\n\"%s\" (%d %%) detected after %ld s              \n\r",ai_class[max_idx],\
                                    (int)(max_out*100), (uint32_t)(time_stats_get_runtime())/1000);
#endif
  }
  else
  {
#ifdef APP_LCD
    if(!oled_load_pict(pict_unknown))
    {
      PRINTF("Failed to load pictogram for unknown class\n\r");
    }
#endif
    PRINTF("\r\n\nUnknown class after %ld s                 \n\r",\
                                    (uint32_t)(time_stats_get_runtime())/1000);
  }
  PRINTF("\r\x1B[A\x1B[A\x1B[A\x1");
  fflush(stdout);
}

/* Private user code ---------------------------------------------------------*/

static float pre_time_prev, ai_time_prev, run_time_prev ;

/**
 * @brief Resets the rolling CPU statistics values used for display.
 */
static void reset_cpu_stats(void)
{ 
  pre_time_prev  = 0.0F;
  ai_time_prev   = 0.0F;
  run_time_prev  = 0.0F; 
}

/**
 * @brief Prints the current CPU load statistics.
 */
static void print_cpu_stats(void)
{ 
  /* display real time statistics */
  float run_time      = time_stats_get_runtime();
  float pre_time      = time_stats_get_sum(TIME_STAT_PRE_PROC);
  float ai_time       = time_stats_get_sum(TIME_STAT_AI_PROC);
  float run_time_dif  = run_time - run_time_prev;
  float pre_time_dif  = pre_time - pre_time_prev;
  float ai_time_dif   = ai_time - ai_time_prev ;
  run_time_prev       = run_time ;
  pre_time_prev       = pre_time ;
  ai_time_prev        = ai_time ;

  PRINTF ("|       %-8ld|%6.2f%%|%6.2f%%|%6.2f%%|\r",\
    (uint32_t)(run_time/1000),\
    100*(pre_time_dif+ai_time_dif)/(run_time_dif),\
    100*pre_time_dif/run_time_dif,\
    100*ai_time_dif/run_time_dif);\
}

struct mcu_conf {
  /* default/minimal configuration */
  uint32_t sclk;    /* MCU frequency (Hz) */
  uint32_t hclk;    /* main system bus frequency (Hz) */
  uint32_t conf;    /* or-ed flag to describe cache,... (device dependent, see getFlashCacheConf() fct) */
  uint32_t devid;   /* device ID */
  uint32_t revid;   /* rev ID */
#if defined(HAS_EXTRA_CONF) && HAS_EXTRA_CONF > 0
  uint32_t extra[HAS_EXTRA_CONF];  /* extra info, device dependent */
#endif
};
#define MCONF_H7        (3 << 24)  /* Used for SR5E1 device - Cortex-m7 based */
#define MCONF_CORE_ICACHE    (1 << 10)
#define MCONF_CORE_DCACHE    (1 << 11)
#define MCONF_FPU       (1 << 16)

/**
 * @brief Builds the MCU flash and cache configuration flags.
 * @return Encoded flash, cache and FPU configuration.
 */
uint32_t getFlashCacheConf(void)
{
  uint32_t mconf = 0;

#if defined(STM32H7P)
 
  mconf |= MCONF_H7;
 
  __I uint32_t acr = FLASH->ACCR;
  mconf |= ((acr & FLASH_ACCR_LATENCY_Msk) >> FLASH_ACCR_LATENCY_Pos);
 
  __I uint32_t ccr = SCB->CCR;
 
  if (ccr & SCB_CCR_IC_Msk)
    mconf |= MCONF_CORE_ICACHE;
  if (ccr & SCB_CCR_DC_Msk)
    mconf |= MCONF_CORE_DCACHE;
 
#endif

#if (__FPU_PRESENT == 1) && __FPU_USED
  mconf |= MCONF_FPU;  /* FPU present and used */
#endif

  return mconf;
}

/**
 * @brief Reads the current MCU system configuration.
 * @param conf Pointer to the destination configuration structure.
 */
void getSysConf(struct mcu_conf *conf)
{
  if (!conf)
    return;

  conf->sclk = port_hal_get_cpu_freq();
  conf->hclk = port_hal_get_sys_freq();
  conf->conf = getFlashCacheConf();
  conf->devid = port_hal_get_dev_id();
  conf->revid = port_hal_get_rev_id();

#if defined(HAS_EXTRA_CONF) && HAS_EXTRA_CONF > 1
  port_hal_set_extra_conf(&conf->extra[0]);
#endif

}

/**
 * @brief Converts a Boolean value to a display string.
 * @param val Value to convert.
 * @return "True" for a non-zero value, otherwise "False".
 */
__STATIC_INLINE const char* bitToStr(uint32_t val)
{
  if (val)
    return "True";
  else
    return "False";
}
/**
 * @brief Converts a device identifier to its device family name.
 * @param dev_id Device identifier read from the MCU.
 * @return Device family name, or "UNKNOWN".
 */
static const char *devIdToStr(uint16_t dev_id)
{
  /* DEV_ID field from DBGMCU register (see BZ119679)*/
  const char *str;
  switch (dev_id) {
  case 0x450: str = "STM32H743/53/50xx and STM32H745/55/47/57xx"; break; /* Shark2M - see RM0433 & RM0399 */
  case 0x47b: str = "STM32H7Pxx"; break; /* H7P */
  case 0x480: str = "STM32H7A/7B"; break;  /* TinyShark2M */
  case 0x483: str = "STM32H7[2,3]x"; break;  /* LittleShark1M */
  default:    str = "UNKNOWN";
  }
  return str;
}

/**
 * @brief Logs compiler, device and system configuration information.
 */
static void system_setting_log(void)
{
    struct mcu_conf sys_conf;

    /* Display Device configuration */
  getSysConf(&sys_conf);

  PRINTF(DEVICE_FAMILY " device configuration...\r\n");
  PRINTF(" Device       : DevID:0x%04x (%s)\r\n",
      (int)sys_conf.devid,
      devIdToStr(sys_conf.devid)
  );
  PRINTF(" Core Arch.   : M%d - %s %s\r\n", __CORTEX_M, "FPU ", ((__FPU_USED) ? "used" : "not used!"));
  PRINTF(" SYSCLK clock : %u MHz\r\n", (int)sys_conf.sclk/1000000);
  PRINTF(" HCLK clock   : %u MHz\r\n", (int)sys_conf.hclk/1000000);

#if defined(STM32H7P)
  uint32_t ccr = SCB->CCR;
  PRINTF(" CACHE conf.  : $I/$D=(%s,%s)\r\n\n",
      bitToStr(ccr & SCB_CCR_IC_Msk),
      bitToStr(ccr & SCB_CCR_DC_Msk));
#endif
}
