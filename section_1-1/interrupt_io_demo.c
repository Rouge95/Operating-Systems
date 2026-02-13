#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define RESET "\033[0m"
#define CPU_COLOR "\033[31m"     // Red
#define DRIVER_COLOR "\033[33m"  // Yellow
#define DEVICE1_COLOR "\033[36m" // Cyan
#define DEVICE2_COLOR "\033[35m" // Magenta
#define SYSTEM_COLOR "\033[32m"  // Green

// Slow down each step for readability
void pause_step() { sleep(3); }

// Simulated interrupt handler
void interrupt_handler(const char *cpu_name) {
  pause_step();
  printf(CPU_COLOR "%s: Interrupt received.\n" RESET, cpu_name);

  pause_step();
  printf(CPU_COLOR "%s: Saving process state...\n" RESET, cpu_name);

  pause_step();
  printf(CPU_COLOR "%s: Executing Interrupt Service Routine (ISR)...\n" RESET,
         cpu_name);

  pause_step();
  printf(CPU_COLOR "%s: Restoring state and resuming normal execution.\n" RESET,
         cpu_name);
}

// Simulated device operation
void *device_operation(void *arg) {
  const char *device_name = (const char *)arg;

  pause_step();
  if (device_name[6] == '1')
    printf(DEVICE1_COLOR "%s: Starting I/O operation...\n" RESET, device_name);
  else
    printf(DEVICE2_COLOR "%s: Starting I/O operation...\n" RESET, device_name);

  pause_step();
  if (device_name[6] == '1')
    printf(DEVICE1_COLOR "%s: Performing I/O...\n" RESET, device_name);
  else
    printf(DEVICE2_COLOR "%s: Performing I/O...\n" RESET, device_name);

  sleep(3); // Simulate longer device operation

  pause_step();
  if (device_name[6] == '1')
    printf(DEVICE1_COLOR "%s: I/O complete. Raising interrupt.\n" RESET,
           device_name);
  else
    printf(DEVICE2_COLOR "%s: I/O complete. Raising interrupt.\n" RESET,
           device_name);

  interrupt_handler("CPU");

  return NULL;
}

int main() {
  pthread_t device1_thread, device2_thread;

  pause_step();
  printf(SYSTEM_COLOR
         "System: Starting interrupt-driven I/O simulation.\n" RESET);

  pause_step();
  printf(SYSTEM_COLOR
         "Process: Requesting I/O operation on Device1 and Device2.\n" RESET);

  pause_step();
  printf(DRIVER_COLOR "Device Driver: Programming device controllers.\n" RESET);

  // Start two devices
  pthread_create(&device1_thread, NULL, device_operation, "Device1");
  pthread_create(&device2_thread, NULL, device_operation, "Device2");

  pause_step();
  printf(CPU_COLOR
         "CPU: Performing other tasks while devices operate...\n" RESET);

  pause_step();
  printf(CPU_COLOR "CPU: Still working...\n" RESET);

  // Wait for devices to finish
  pthread_join(device1_thread, NULL);
  pthread_join(device2_thread, NULL);

  pause_step();
  printf(SYSTEM_COLOR "System: Interrupt-driven I/O cycle complete.\n" RESET);

  return 0;
}