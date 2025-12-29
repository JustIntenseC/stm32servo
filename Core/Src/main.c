/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Основной файл программы
  ******************************************************************************
  * @attention
  *
  * Авторские права (c) 2025 STMicroelectronics.
  * Все права защищены.
  *
  * Это программное обеспечение лицензировано на условиях, которые можно найти
  * в файле LICENSE в корневом каталоге этого программного компонента.
  * Если этот файл отсутствует, программное обеспечение предоставляется "как есть".
  ******************************************************************************
  */
/* USER CODE END Header */

/* Подключение заголовочных файлов --------------------------------------------*/
#include "main.h"

/* Пользовательские подключения ---------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Пользовательские определения типов -----------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Пользовательские макросы --------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Пользовательские переменные -----------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Прототипы пользовательских функций ----------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Пользовательский код -------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  Точка входа в приложение.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  // Здесь можно добавить инициализацию пользовательских переменных или код
  /* USER CODE END 1 */

  /* Конфигурация микроконтроллера ------------------------------------------*/

  // Сброс всех периферийных устройств, инициализация Flash и SysTick
  HAL_Init();

  /* USER CODE BEGIN Init */
  // Пользовательская инициализация
  /* USER CODE END Init */

  // Конфигурация системного тактирования
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  // Пользовательская инициализация после настройки тактирования
  /* USER CODE END SysInit */

  // Инициализация всех настроенных периферийных устройств
  MX_GPIO_Init();  // Инициализация портов ввода-вывода
  MX_TIM1_Init();  // Инициализация таймера TIM1

  /* USER CODE BEGIN 2 */
  // Запуск ШИМ на канале 1 таймера TIM1
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);

  // Примеры установки скважности (закомментированы):
  // __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 72);   // 5% скважности
  // __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 108);  // 7.5% скважности
  // __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 144);  // 10% скважности
  /* USER CODE END 2 */

  /* Бесконечный цикл */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    // Установка скважности 7.5%
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 108);

    // Установка скважности 5%
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 72);

    // Установка скважности 7.5%
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 108);

    // Установка скважности 10%
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 144);

    // Переключение состояния пина PC13 (например, для мигания светодиодом)
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);

    // Задержка 500 мс
    HAL_Delay(500);

    /* USER CODE BEGIN 3 */
    // Пользовательский код в основном цикле
    /* USER CODE END 3 */
  }
}

/**
  * @brief  Конфигурация системного тактирования
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  // Инициализация генераторов тактового сигнала
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;  // Используем внешний генератор HSE
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;  // Включаем HSE
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;  // Делитель HSE = 1
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;  // Включаем HSI
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;  // Включаем PLL
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;  // Источник PLL - HSE
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;  // Умножитель PLL = 9
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();  // Обработка ошибки
  }

  // Конфигурация тактирования CPU, AHB и APB
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;  // Источник SYSCLK - PLL
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;  // Делитель AHB = 1
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;  // Делитель APB1 = 2
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;  // Делитель APB2 = 1

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();  // Обработка ошибки
  }
}

/**
  * @brief  Инициализация таймера TIM1
  * @param  None
  * @retval None
  */
static void MX_TIM1_Init(void)
{
  /* USER CODE BEGIN TIM1_Init 0 */
  // Включаем тактирование таймера TIM1
  __HAL_RCC_TIM1_CLK_ENABLE();
  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM1_Init 1 */
  // Пользовательская инициализация перед настройкой таймера
  /* USER CODE END TIM1_Init 1 */

  // Конфигурация таймера TIM1
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 1000 - 1;  // Предделитель = 1000
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;  // Режим счёта: вверх
  htim1.Init.Period = 1440 - 1;  // Период = 1440 (ARR)
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;  // Деление тактовой частоты = 1
  htim1.Init.RepetitionCounter = 0;  // Счётчик повторений = 0
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;  // Отключаем предзагрузку ARR

  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();  // Обработка ошибки
  }

  // Конфигурация источника тактирования таймера
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;  // Источник тактирования - внутренний
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();  // Обработка ошибки
  }

  // Инициализация ШИМ
  if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
  {
    Error_Handler();  // Обработка ошибки
  }

  // Конфигурация канала ШИМ
  sConfigOC.OCMode = TIM_OCMODE_PWM1;  // Режим ШИМ1
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;  // Полярность: высокий уровень
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;  // Полярность дополнительного выхода: высокий уровень
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;  // Быстрый режим отключён
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;  // Состояние простоя: сброс
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;  // Состояние простоя дополнительного выхода: сброс

  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();  // Обработка ошибки
  }

  /* USER CODE BEGIN TIM1_Init 2 */
  // Пользовательская инициализация после настройки таймера
  /* USER CODE END TIM1_Init 2 */
}

/**
  * @brief  Инициализация портов ввода-вывода
  * @param  None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */
  // Пользовательская инициализация перед настройкой GPIO
  /* USER CODE END MX_GPIO_Init_1 */

  // Включаем тактирование порта GPIOC
  __HAL_RCC_GPIOC_CLK_ENABLE();

  // Конфигурация пина PC13 как выхода с низким уровнем
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

  // Инициализация пина PC13 как выхода
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;  // Режим: выход, push-pull
  GPIO_InitStruct.Pull = GPIO_NOPULL;  // Без подтяжки
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;  // Скорость: низкая
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  // Конфигурация пина PA8 как альтернативной функции (для ШИМ)
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;  // Режим: альтернативная функция, push-pull
  GPIO_InitStruct.Pull = GPIO_NOPULL;  // Без подтяжки
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;  // Скорость: высокая
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */
  // Пользовательская инициализация после настройки GPIO
  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
/* Пользовательский код 4 */
/* USER CODE END 4 */

/**
  * @brief  Обработчик ошибок
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  // Отключаем прерывания и зацикливаемся
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Вывод информации об ошибке assert_param
  * @param  file: указатель на имя файла
  * @param  line: номер строки
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  // Пользовательская реализация вывода информации об ошибке
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

