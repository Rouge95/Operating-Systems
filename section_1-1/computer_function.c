#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define RESET "\033[0m"
#define CPU_COLOR "\033[31m"    // Red
#define MEMORY_COLOR "\033[34m" // Blue
#define DRIVER_COLOR "\033[33m" // Yellow
#define DEVICE_COLOR "\033[36m" // Cyan
#define SYSTEM_COLOR "\033[32m" // Green

// Slow down steps for readability
void pause_step() { sleep(2); }

// Simulate CPU fetching instruction from memory
void cpu_fetch_instruction() {
  pause_step();
  printf(CPU_COLOR "CPU: Fetching instruction from Memory...\n" RESET);
}

// Simulate CPU decoding instruction
void cpu_decode_instruction() {
  pause_step();
  printf(CPU_COLOR "CPU: Decoding instruction...\n" RESET);
}

// Simulate CPU executing instruction
void cpu_execute_instruction() {
  pause_step();
  printf(CPU_COLOR "CPU: Executing instruction...\n" RESET);
}

// Simulated device operation (like keyboard or disk)
void *device_operation(void *arg) {
  const char *device_name = (const char *)arg;

  pause_step();
  printf(DEVICE_COLOR "%s: Device ready.\n" RESET, device_name);

  pause_step();
  printf(DEVICE_COLOR "%s: Performing operation...\n" RESET, device_name);

  sleep(2); // simulate delay

  pause_step();
  printf(DEVICE_COLOR "%s: Operation complete. Raising interrupt.\n" RESET,
         device_name);

  pause_step();
  printf(CPU_COLOR "CPU: Interrupt received from %s. Handling...\n" RESET,
         device_name);

  pause_step();
  printf(CPU_COLOR "CPU: Resuming normal execution.\n" RESET);

  return NULL;
}

int main() {
  pthread_t keyboard_thread, disk_thread;

  printf(SYSTEM_COLOR "System: Modern Computer Simulation Starting...\n" RESET);

  // Step 1: CPU fetch-decode-execute cycle
  cpu_fetch_instruction();
  cpu_decode_instruction();
  cpu_execute_instruction();

  // Step 2: CPU requests I/O from devices
  pause_step();
  printf(DRIVER_COLOR "Device Driver: Sending request to Keyboard and Disk "
                      "controllers.\n" RESET);

  // Start device threads
  pthread_create(&keyboard_thread, NULL, device_operation, "Keyboard");
  pthread_create(&disk_thread, NULL, device_operation, "Disk");

  // Step 3: CPU continues executing other instructions
  pause_step();
  printf(CPU_COLOR
         "CPU: Performing other tasks while devices operate...\n" RESET);
  pause_step();
  printf(CPU_COLOR "CPU: Still executing instructions...\n" RESET);

  // Wait for devices to finish
  pthread_join(keyboard_thread, NULL);
  pthread_join(disk_thread, NULL);

  pause_step();
  printf(MEMORY_COLOR
         "Memory: All operations complete, data stored/retrieved.\n" RESET);
  pause_step();
  printf(SYSTEM_COLOR "System: Modern Computer Simulation Complete.\n" RESET);

  return 0;
}
