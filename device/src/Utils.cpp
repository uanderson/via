#include "Arduino.h"

// Module includes
#include "Core.h"
#include "Utils.h"

/**
 * Generates an unique identifier by generating 20 random bytes and using them
 * to select characters from a list of 62 characters (a-z, A-Z, and 0-9). The
 * generated ID is stored in the provided `id` array, which must have a length
 * of at least 21 bytes to accommodate the null terminator.
 *
 * @param id where the generated ID will be stored
 */
void generateId(uid id) {
  byte values[20];

  for (int index = 0; index < 20; index++) {
    values[index] = random(0, 255);
  }

  char alphabet[] =
      "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

  for (int index = 0; index < 20; index++) {
    id[index] = alphabet[values[index] % 62];
  }

  id[20] = '\0';
}