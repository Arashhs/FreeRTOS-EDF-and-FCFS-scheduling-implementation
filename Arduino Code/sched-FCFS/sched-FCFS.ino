#include <Arduino_FreeRTOS.h>

/* TO USE THIS FILE (FCFS), SET configUSE_FCFS_SCHEDULER in FreeRTOSConfig.h to 1 and configUSE_EDF_SCHEDULER to 0 */

const int led1 = 22;
const int led2 = 23;
const int led3 = 24;
const int led4 = 25;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);

 /* xTaskCreateEDF(lightUp, "task1", 128, &led1, 1, NULL, 90); //Last parameter is the relative deadline
  xTaskCreateEDF(lightUp, "task2", 128, &led2, 1, NULL, 60);
  xTaskCreateEDF(lightUp, "task3", 128, &led3, 1, NULL, 80);
  xTaskCreateEDF(lightUp, "task4", 128, &led4, 1, NULL, 70); */

  //for FCFS scheduling
  xTaskCreateFCFS(lightUp, "task1", 128, &led1, NULL); //xTaskCreateFCFS is xTaskCreate in which uxpriority field is deleted because it is not used.
  xTaskCreateFCFS(lightUp, "task2", 128, &led2, NULL);
  xTaskCreateFCFS(lightUp, "task3", 128, &led3, NULL);
  xTaskCreateFCFS(lightUp, "task4", 128, &led4, NULL); 
  vTaskStartScheduler();
}

// the loop function runs over and over again forever
void loop() {

}


/* light up for 3s */
void lightUp(void* pvParameters)
{
  int ledpin = *(int*)pvParameters;
  for(;;)
  {
    digitalWrite(ledpin, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(3000);                       // wait for 3 seconds
    digitalWrite(ledpin, LOW);    // turn the LED off by making the voltage LOW
    vTaskDelay( 50 / portTICK_PERIOD_MS ); 
  }
}
