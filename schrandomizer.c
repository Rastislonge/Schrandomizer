#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"
#include <time.h>

int main(int argc, char *argv[]) {

    int k = 0, bpm = 0, chrd = 0, vlm = 0, ntFltr_tp = 0, ntFltr_ctoffHz = 0, ntFltr_lnGn = 0, chrs = 0, rvb = 0, spct = 0, ptc = 0, tk = 0, sqc = 0, help = 0;
    char *file_path = NULL;

    for (int i = 1; i < argc; ++i) { 
        if (strcmp(argv[i], "--key") == 0) {
          k = 1;
        } 
        else if (strcmp(argv[i], "--beatsPerMinute") == 0) {
          bpm = 1;
        }
        else if (strcmp(argv[i], "--chord") == 0) {
          chrd = 1;
        }
        else if (strcmp(argv[i], "--volume") == 0) {
          vlm = 1;
        }
        else if (strcmp(argv[i], "--noteFilter_type") == 0) {
          ntFltr_tp = 1;
        }
        else if (strcmp(argv[i], "--noteFilter_cutoffHz") == 0) {
          ntFltr_ctoffHz = 1;
        }
        else if (strcmp(argv[i], "--noteFilter_linearGain") == 0) {
          ntFltr_lnGn = 1;
        }
        else if (strcmp(argv[i], "--chorus") == 0) {
          chrs = 1;
        }
        else if (strcmp(argv[i], "--reverb") == 0) {
          rvb = 1;
        }
        else if (strcmp(argv[i], "--spectrum") == 0) {
          spct = 1;
        }
        else if (strcmp(argv[i], "--pitch") == 0) {
          ptc = 1;
        }
        else if (strcmp(argv[i], "--tick") == 0) {
          tk = 1;
        }
        else if (strcmp(argv[i], "--sequence") == 0) {
          sqc = 1;
        }
        else if (strcmp(argv[i], "--all") == 0) {
          k = 1;
          bpm = 1;
          chrd = 1;
          vlm = 1;
          ntFltr_tp = 1;
          ntFltr_ctoffHz = 1;
          ntFltr_lnGn = 1;
          chrs = 1;
          rvb = 1;
          spct = 1;
          ptc = 1;
          tk = 1;
          sqc = 1;
        }
        else if (strcmp(argv[i], "--help") == 0) { printf("-----------------------------Schrandomizer usage-----------------------------\nUSING NO PARAMS WILL RESULT IN NO CHANGES\n\n--key: enable key schrandomization\n--beatsPerMinute: enable bpm schrandomization\n--chord: enable chord schrandomization\n--volume: enable volume schrandomization\n--noteFilter_type: enable the notefilter's type schrandomization\n--noteFilter_cutoffHz: enable the notefilter's herz limit schrandomization\n--noteFilter_linearGain: enable the notefilter's linear gain schrandomization\n--chorus: enable chorus schrandomization\n--reverb: enable reverb schrandomization\n--spectrum: enable spectrum schrandomization\n--pitch: enable pitch schrandomization\n--tick: enable tick schrandomization\n--sequence: enable sequence schrandomization\n--all: for the ultimate schrandomization experience\n\nExample usage: ./schrandomizer (or schrandomizer.exe on windows) --all base.json\n-----------------------------------------------------------------------------"); return 0; }
        else {
          file_path = argv[i];
        }
    }

    //check for file param
    if (file_path == NULL) {
        fprintf(stderr, "No file path provided.\n\nExample usage to randomize all params: ./schrandomizer (or schrandomizer.exe on windows) --all base.json\n\nRUNNING WITH NO PARAM DOES NOTHING\n\nRun ./schrandomizer (or schrandomizer.exe on windows) --help for more info.");
        return 1;
    } 

    srand(time(NULL));

    //Open and format the json file to a string
    char * file_buffer = 0;
    long length;
    FILE * f = fopen (file_path, "rb");
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

      //key
      cJSON *key = cJSON_GetObjectItem(root, "key");
      if (key != NULL && k) {

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

      //beatsPerMinute
      cJSON *beatsPerMinute = cJSON_GetObjectItem(root, "beatsPerMinute");
      if (beatsPerMinute != NULL && bpm) {
        int number = (rand() % (30 - 300 + 1)) + 30;
        cJSON_SetNumberValue(beatsPerMinute, number);
      }

      //instruments
      cJSON *channels = cJSON_GetObjectItem(root, "channels");
      if (channels != NULL && cJSON_IsArray(channels)) {
        int channels_count = cJSON_GetArraySize(channels);
        for (int j = 0; j < channels_count; ++j) {
            cJSON *channel = cJSON_GetArrayItem(channels, j);
            if (channel != NULL) {
              cJSON *instruments = cJSON_GetObjectItem(channel, "instruments");
              if (instruments != NULL) {
                  int instruments_count = cJSON_GetArraySize(instruments);
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
                          if (chord != NULL && chrd) {
                            cJSON_SetValuestring(chord, chords_list[random_chord]);
                          }

                          //volume
                          cJSON *volume = cJSON_GetObjectItem(instrument, "volume");
                          if (volume != NULL && vlm) {
                            int random_volume = (rand() % (30 - 100 + 1)) + 30;
                            cJSON_SetNumberValue(volume, random_volume);
                          }

                          // noteFilter
                          cJSON *noteFilterArray = cJSON_GetObjectItem(instrument, "noteFilter");
                          if (noteFilterArray != NULL && cJSON_IsArray(noteFilterArray)) {
                              int noteFilterCount = cJSON_GetArraySize(noteFilterArray);
                              for (int nfIndex = 0; nfIndex < noteFilterCount; ++nfIndex) {
                                  cJSON *noteFilter = cJSON_GetArrayItem(noteFilterArray, nfIndex);
                                  if (noteFilter != NULL) {
                                      // type
                                      if (ntFltr_tp) {
                                          const char *noteFilter_types_list[] = {
                                              "low-pass",
                                              "high-pass",
                                              "band-pass",
                                              "notch"
                                          };
                                          cJSON *noteFilter_type = cJSON_GetObjectItem(noteFilter, "type");
                                          if (noteFilter_type != NULL) {
                                              int random_noteFilter_type = rand() % (sizeof(noteFilter_types_list) / sizeof(noteFilter_types_list[0]));
                                              cJSON_SetValuestring(noteFilter_type, noteFilter_types_list[random_noteFilter_type]);
                                          }
                                      }
                                      // cutoffHz
                                      if (ntFltr_ctoffHz) {
                                          cJSON *noteFilter_cutoffHz = cJSON_GetObjectItem(noteFilter, "cutoffHz");
                                          if (noteFilter_cutoffHz != NULL) {
                                              int random_HZ = (rand() % (20000 - 20 + 1)) + 20; // Ensure the range is correct
                                              float random_HZ_float = (rand() % 100) / 100.0;
                                              float HZ = random_HZ + random_HZ_float;
                                              cJSON_SetNumberValue(noteFilter_cutoffHz, HZ);
                                          }
                                      }
                                      // linearGain
                                      if (ntFltr_lnGn) {
                                          cJSON *noteFilter_linearGain = cJSON_GetObjectItem(noteFilter, "linearGain");
                                          if (noteFilter_linearGain != NULL) {
                                              float random_linearGain = ((float)rand() / (float)(RAND_MAX)) * 15.0;
                                              cJSON_SetNumberValue(noteFilter_linearGain, random_linearGain);
                                          }
                                      }
                                  }
                              }
                          }
                          
                          //chorus
                          cJSON *chorus = cJSON_GetObjectItem(instrument, "chorus");
                          if (chorus != NULL && chrs) {
                            int random_chorus = (rand() % (1 - 100 + 1)) + 1;
                            cJSON_SetNumberValue(chorus, random_chorus);
                          }

                          //reverb
                          cJSON *reverb = cJSON_GetObjectItem(instrument, "reverb");
                          if (reverb != NULL && rvb) {
                            int random_reverb = (rand() % (1 - 100 + 1)) + 1;
                            cJSON_SetNumberValue(reverb, random_reverb);
                          }

                          //spectrum
                          cJSON *spectrums = cJSON_GetObjectItem(instrument, "spectrum");
                          if (spectrums != NULL && spct) {
                            int spectrum_count = cJSON_GetArraySize(spectrums);
                            for (int i = 0; i < spectrum_count; ++i) {
                              cJSON *spectrum = cJSON_GetArrayItem(spectrums, i);
                              if (spectrum != NULL) {
                                int random_spectrum = (rand() % (1 - 100 + 1)) + 1;
                                cJSON_SetNumberValue(spectrum, random_spectrum);
                          }
                        }  
                      }
                    }  
                  }
               }
               //edit pitches by tick (channels -> patterns -> notes -> pitches)
               cJSON *patterns = cJSON_GetObjectItem(channel, "patterns");
               if (patterns != NULL) {
                //printf("Found patterns\n");
                 int patterns_count = cJSON_GetArraySize(patterns);
                 //printf("Number of patterns: %d\n", patterns_count);
                 for (int i = 0; i < patterns_count; ++i) {
                  cJSON *pattern = cJSON_GetArrayItem(patterns, i);
                  if (pattern != NULL) {
                    //printf("Processing pattern: %d\n", i);
                    cJSON *notes = cJSON_GetObjectItem(pattern, "notes");
                    if (notes != NULL) {
                      //printf("Found notes\n");
                      int notes_count = cJSON_GetArraySize(notes);
                      //printf("Number of notes: %d\n", patterns_count);
                      for (int i = 0; i < notes_count; ++i) {
                       cJSON *note = cJSON_GetArrayItem(notes, i);
                       if (note != NULL) {
                        cJSON *pitches = cJSON_GetObjectItem(note, "pitches");
                        if (pitches != NULL && ptc) {
                          //printf("Found pitches\n");
                          int pitches_count = cJSON_GetArraySize(pitches);
                          //printf("Number of pitches: %d\n", pitches_count);
                          for (int i = 0; i < pitches_count; ++i) {
                            cJSON *pitch = cJSON_GetArrayItem(pitches, i);
                            if (pitch != NULL) {
                              // random_pitch
                              int random_pitch = (rand() % (1 - 69 + 1)) + 1;
                              //printf("New pitch set: %d\n", random_pitch);
                              cJSON_SetNumberValue(pitch, random_pitch);
                            }
                          }
                        }
                      //ticks
                      cJSON *points = cJSON_GetObjectItem(note, "points");
                      if (points != NULL && tk) {
                        int points_count = cJSON_GetArraySize(points);
                        for (int i = 0; i < points_count; ++i) {
                          cJSON *point = cJSON_GetArrayItem(points, i);
                          if (point != NULL && cJSON_IsObject(point)) {
                          int random_tick = (rand() % (32 / 2 + 1)) * 2;
                          cJSON *tick = cJSON_GetObjectItem(point, "tick");
                          cJSON_SetNumberValue(tick, random_tick);
                         }
                        }
                      }
                    }
                  }
                }
              }
            }
           }
           //sequence 
           cJSON *sequences = cJSON_GetObjectItem(channel, "sequence");
              if (sequences != NULL && sqc) {
                int sequences_count = cJSON_GetArraySize(sequences);
                for (int i = 0; i < sequences_count; ++i) {
                  cJSON *sequence = cJSON_GetArrayItem(sequences, i);
                  if (sequence != NULL) {
                    //random_sequence
                    int random_sequence = (rand() % (1 - 10 + 1));
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
      //printf("Modified JSON string: %s\n", modified_json_string);
      
      // Save the new json
      FILE *fp = fopen("schrandomized.json", "w+");
      if (fp != NULL)
      {
        fputs(modified_json_string, fp);
        fclose(fp);
      }

      // Clean up
      cJSON_Delete(root);
      free(modified_json_string);
    }

    return 0;
}

// TODO
// - Need to fix intruments to randomize based on type or it makes jsons that just won't work for beepbox
// - Fix the tick randomization generating too few notes