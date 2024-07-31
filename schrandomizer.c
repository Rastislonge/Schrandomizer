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
        int number = (rand() % (30 - 300 + 1)) + 30;
        cJSON_SetNumberValue(beatsPerMinute, number);
      }

      // need to fix intruments to randomize based on type or it makes jsons that just won't work for beepbox

      // instruments
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
                  int instruments_count = cJSON_GetArraySize(instruments);
                  printf("Number of instruments: %d\n", instruments_count);
                  for (int i = 0; i < instruments_count; ++i) {
                      cJSON *instrument = cJSON_GetArrayItem(instruments, i);
                      if (instrument != NULL) {

                          //chord
                          const char *chords_list[] = {
                            "harmony",
                            "strum",
                            "arpeggio",
                            "chord",
                            "arpeggio_straight"
                          };
                          int random_chord = rand() % (sizeof(chords_list) / sizeof(chords_list[0]));
                          cJSON *chord = cJSON_GetObjectItem(instrument, "chord");
                          if (chord != NULL) {
                            printf("New chord set: %s\n", chords_list[random_chord]);
                            cJSON_SetValuestring(chord, chords_list[random_chord]);
                          }

                          // volume
                          cJSON *volume = cJSON_GetObjectItem(instrument, "volume");
                          if (volume != NULL) {
                            int random_volume = (rand() % (30 - 100 + 1)) + 30;
                            cJSON_SetNumberValue(volume, random_volume);
                          }

                          //noteFilter
                          cJSON *noteFilter = cJSON_GetObjectItem(instrument, "noteFilter");
                          if (noteFilter != NULL) {
                            //type
                            const char *noteFilter_types_list[] = {
                            "low-pass",
                            "high-pass",
                            "band-pass",
                            "notch"
                            };
                            cJSON *noteFilter_type = cJSON_GetObjectItem(noteFilter, "type");
                            int random_noteFilter_type = rand() % (sizeof(noteFilter_types_list) / sizeof(noteFilter_types_list[0]));
                            printf("New noteFilter type set: %s\n", noteFilter_types_list[random_noteFilter_type]);
                            cJSON_SetValuestring(noteFilter_type, noteFilter_types_list[random_noteFilter_type]);
                            
                            //cutoffHz
                            cJSON *noteFilter_cutoffHz = cJSON_GetObjectItem(noteFilter, "cutoffHz");
                            int random_HZ = (rand() % (20 - 20000 + 1)) + 20;
                            float random_HZ_float = (rand() % 100) / 100.0;
                            float HZ = random_HZ + random_HZ_float;
                            printf("New noteFilter cutoffHz set: %.2f\n", HZ);
                            cJSON_SetNumberValue(noteFilter_cutoffHz, HZ);

                            //linearGain
                            cJSON *noteFilter_linearGain = cJSON_GetObjectItem(noteFilter, "linearGain");
                            float random_linearGain = (rand() % 10) / 10.0;
                            printf("New noteFilter linearGain set: %.1f\n", random_linearGain);
                            cJSON_SetNumberValue(noteFilter_linearGain, random_linearGain);
                          }
                          
                          // chorus
                          cJSON *chorus = cJSON_GetObjectItem(instrument, "chorus");
                          if (chorus != NULL) {
                            int random_chorus = (rand() % (1 - 100 + 1)) + 1;
                            printf("New chorus set: %d\n", random_chorus);
                            cJSON_SetNumberValue(chorus, random_chorus);
                          }

                          // reverb
                          cJSON *reverb = cJSON_GetObjectItem(instrument, "reverb");
                          if (reverb != NULL) {
                            int random_reverb = (rand() % (1 - 100 + 1)) + 1;
                            printf("New reverb set: %d\n", random_reverb);
                            cJSON_SetNumberValue(reverb, random_reverb);
                          }
                          //spectrum
                          cJSON *spectrums = cJSON_GetObjectItem(instrument, "spectrum");
                          if (spectrums != NULL) {
                            int spectrum_count = cJSON_GetArraySize(spectrums);
                            printf("Number of spectrum: %d\n", spectrum_count);
                            for (int i = 0; i < spectrum_count; ++i) {
                              cJSON *spectrum = cJSON_GetArrayItem(spectrums, i);
                              if (spectrum != NULL) {
                                int random_spectrum = (rand() % (1 - 100 + 1)) + 1;
                                printf("New spectrum set: %d\n", random_spectrum);
                                cJSON_SetNumberValue(spectrum, random_spectrum);
                          }
                        }  
                      }
                    }  
                  }
               }
               // edit pitches by tick (channels -> patterns -> notes -> pitches)
               cJSON *patterns = cJSON_GetObjectItem(channel, "patterns");
               if (patterns != NULL) {
                 cJSON *notes = cJSON_GetObjectItem(patterns, "notes");
                 if (notes != NULL) {
                   cJSON *pitches = cJSON_GetObjectItem(notes, "pitches");
                   if (pitches != NULL) {
                     int pitches_count = cJSON_GetArraySize(pitches);
                     printf("Number of pitches: %d\n", pitches_count);
                     for (int i = 0; i < pitches_count; ++i) {
                       cJSON *pitch = cJSON_GetArrayItem(pitches, i);
                       if (pitch != NULL) {
                        // random_pitch
                        int random_pitch = (rand() % (1 - 69 + 1)) + 1;
                        printf("New pitch set: %d\n", random_pitch);
                        cJSON_SetNumberValue(pitch, random_pitch);
                       }
                     }
                 }
               }
            }
           cJSON *sequences = cJSON_GetObjectItem(channel, "sequence");
              if (sequences != NULL) {
                int sequences_count = cJSON_GetArraySize(sequences);
                printf("Number of sequences: %d\n", sequences_count);
                for (int i = 0; i < sequences_count; ++i) {
                  cJSON *sequence = cJSON_GetArrayItem(sequences, i);
                  if (sequence != NULL) {
                    // random_sequence
                    int random_sequence = (rand() % (1 - 10 + 1));
                    printf("New sequence set: %d\n", random_sequence);
                    cJSON_SetNumberValue(sequence, random_sequence);
                    }
                  }
                } 
         }
      }
    }

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
// - Randomize note placements (ticks)