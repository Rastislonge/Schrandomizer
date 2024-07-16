#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"
#include <time.h>

int main() {

    srand(time(NULL));

    //Open and format the json file to a string
    char * file_buffer = 0;
    long length;
    FILE * f = fopen ("base.json", "rb");
    if (f)
    {
      fseek (f, 0, SEEK_END);
      length = ftell (f);
      fseek (f, 0, SEEK_SET);
      file_buffer = malloc (length);
      if (file_buffer)
      {
        fread (file_buffer, 1, length, f);
      }
      fclose (f);
    }

  if (file_buffer) {

      // Parse the JSON string into a cJSON object
      cJSON *root = cJSON_Parse(file_buffer);
      if (root == NULL) {
          fprintf(stderr, "Error parsing JSON\n");
          return 1;
      }



     ////// ELEMENTS TO EDIT //////

      // Key
      cJSON *key = cJSON_GetObjectItem(root, "key");
      if (key != NULL) {

        const char *keys[] = {
        "B",
        "A#",
        "A",
        "G#",
        "G",
        "F#",
        "F",
        "E",
        "D#",
        "D",
        "C#",
        "C"
        };

        int random_key = rand() % (sizeof(keys) / sizeof(keys[0]));
        cJSON_SetValuestring(key, keys[random_key]);
      }

      // beatsPerMinute
      cJSON *beatsPerMinute = cJSON_GetObjectItem(root, "beatsPerMinute");
      if (key != NULL) {
        int min = 30;
        int max = 300;
        int number = (rand() % (min - max + 1)) + min;
        cJSON_SetNumberValue(beatsPerMinute, number);
      }

      // instruments -> type
      cJSON *channels = cJSON_GetObjectItem(root, "channels");
      if (channels != NULL && cJSON_IsArray(channels)) {
        printf("Channels found\n");
        int channels_count = cJSON_GetArraySize(channels);
        printf("Number of channels: %d\n", channels_count);
        for (int j = 0; j < channels_count; ++j) {
            cJSON *channel = cJSON_GetArrayItem(channels, j);
            if (channel != NULL) {
              printf("Processing channel %d\n", j);
              cJSON *instruments = cJSON_GetObjectItem(channel, "instruments");
              if (instruments != NULL) {
                printf("Instruments array found in channel %d\n", j);
                const char *instruments_list[] = {
                "chip",
                "FM",
                "noise",
                "spectrum",
                "drumset",
                "harmonics",
                "pwn",
                "pickedString",
                "supersaw"
                };
                  int random_instrument = rand() % (sizeof(instruments_list) / sizeof(instruments_list[0]));
                  int instruments_count = cJSON_GetArraySize(instruments);
                  printf("Number of instruments: %d\n", instruments_count);
                  for (int i = 0; i < instruments_count; ++i) {
                      cJSON *instrument = cJSON_GetArrayItem(instruments, i);
                      if (instrument != NULL) {
                          cJSON *type = cJSON_GetObjectItem(instrument, "type");
                          if (type != NULL) {
                              printf("New type set: %s\n", instruments_list[random_instrument]);
                              cJSON_SetValuestring(type, instruments_list[random_instrument]);
                          }
                      }
                  }
               }
            }
         }
      }

      // chord

      // noteFilter -> all

      // volume

      // chorus

      // reverb

      // edit pitches by tick

      // spectrum

      // sequence

    ////// END OF ELEMENTS TO EDIT //////



      // Convert the cJSON object back to a JSON string
      char *modified_json_string = cJSON_Print(root);
      if (modified_json_string == NULL) {
          fprintf(stderr, "Error printing JSON\n");
          cJSON_Delete(root);
          return 1;
      }

      // Print the modified JSON string
      printf("Modified JSON string: %s\n", modified_json_string);
      
      // Save the new json
      FILE *fp = fopen("schrandomized.json", "ab");
      if (fp != NULL)
      {
        fputs(modified_json_string, fp);
        fclose(fp);
      }

      // Clean up
      cJSON_Delete(root);
      free(modified_json_string);
      free(fp);
    }

    return 0;
}

// TODO
// - Add more keys to randomize (there's a lot...)
// - Add control for which elements to and to not randomize with flags and/or gui
// - Integrated json to wav/mid/mp3 conversion with BeepBox api(?)