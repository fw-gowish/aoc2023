#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Seed location
const int LINE_SEEDS = 0;

// Map locations
const int LINE_SEED_TO_SOIL_START = 2;
const int LINE_SEED_TO_SOIL_END = 40;
const int LINE_SEED_TO_SOIL_LENGTH = LINE_SEED_TO_SOIL_END - LINE_SEED_TO_SOIL_START - 1;

const int LINE_SOIL_TO_FERTILIZER_START = 41;
const int LINE_SOIL_TO_FERTILIZER_END = 61;
const int LINE_SOIL_TO_FERTILIZER_LENGTH = LINE_SOIL_TO_FERTILIZER_END - LINE_SOIL_TO_FERTILIZER_START - 1;

const int LINE_FERTILIZER_TO_WATER_START = 62;
const int LINE_FERTILIZER_TO_WATER_END = 72;
const int LINE_FERTILIZER_TO_WATER_LENGTH = LINE_FERTILIZER_TO_WATER_END - LINE_FERTILIZER_TO_WATER_START - 1;

const int LINE_WATER_TO_LIGHT_START = 73;
const int LINE_WATER_TO_LIGHT_END = 100;
const int LINE_WATER_TO_LIGHT_LENGTH = LINE_WATER_TO_LIGHT_END - LINE_WATER_TO_LIGHT_START - 1;

const int LINE_LIGHT_TO_TEMPERATURE_START = 101;
const int LINE_LIGHT_TO_TEMPERATURE_END = 148;
const int LINE_LIGHT_TO_TEMPERATURE_LENGTH = LINE_LIGHT_TO_TEMPERATURE_END - LINE_LIGHT_TO_TEMPERATURE_START - 1;

const int LINE_TEMPERATURE_TO_HUMIDITY_START = 149;
const int LINE_TEMPERATURE_TO_HUMIDITY_END = 175;
const int LINE_TEMPERATURE_TO_HUMIDITY_LENGTH = LINE_TEMPERATURE_TO_HUMIDITY_END - LINE_TEMPERATURE_TO_HUMIDITY_START - 1;

const int LINE_HUMIDITY_TO_LOCATION_START = 176;
const int LINE_HUMIDITY_TO_LOCATION_END = 197;
const int LINE_HUMIDITY_TO_LOCATION_LENGTH = LINE_HUMIDITY_TO_LOCATION_END - LINE_HUMIDITY_TO_LOCATION_START - 1;

struct Map {
  long destination;
  long source;
  long length;
};

void parseSeeds(char line[], long seeds[]) {
  // Explode line
  char *token = strtok(line, " ");

  // Parse seeds
  int seedIndex = -1;
  while(token != NULL) {
    if(seedIndex > -1) {
      long seed = atol(token);
      seeds[seedIndex] = seed;
    }
    token = strtok(NULL, " ");
    seedIndex ++;
  }
}

void parseMapLine(char line[], long output[]) {
  // Explode line
  char *token = strtok(line, " ");

  int outputIndex = 0;
  while(token != NULL) {
    long value = atol(token);
    output[outputIndex] = value;
    token = strtok(NULL, " ");
    outputIndex ++;
  }
}

long applyMap(long input, struct Map map[], int mapLength) {
  for(int i = 0; i < mapLength; i ++) {
    long startIndex = map[i].source;
    long endIndex = map[i].source + map[i].length;
    if(input >= startIndex && input < endIndex) {
      long delta = map[i].destination - map[i].source;
      return input + delta;
    }
  }

  return input;
}

int main() {
  // Allocate memory
  long seeds[20];
  struct Map mapSeedToSoil[LINE_SEED_TO_SOIL_LENGTH];
  int mapSeedToSoilIndex = 0;
  struct Map mapSoilToFertilizer[LINE_SOIL_TO_FERTILIZER_LENGTH];
  int mapSoilToFertilizerIndex = 0;
  struct Map mapFertilizerToWater[LINE_FERTILIZER_TO_WATER_LENGTH];
  int mapFertilizerToWaterIndex = 0;
  struct Map mapWaterToLight[LINE_WATER_TO_LIGHT_LENGTH];
  int mapWaterToLightIndex = 0;
  struct Map mapLightToTemperature[LINE_LIGHT_TO_TEMPERATURE_LENGTH];
  int mapLightToTemperatureIndex = 0;
  struct Map mapTemperatureToHumidity[LINE_TEMPERATURE_TO_HUMIDITY_LENGTH];
  int mapTemperatureToHumidityIndex = 0;
  struct Map mapHumidityToLocation[LINE_HUMIDITY_TO_LOCATION_LENGTH];
  int mapHumidityToLocationIndex = 0;
  
  // Parse file into allocated memory
  char line[212];
  int lineIndex = 0;
  FILE *fp = fopen("5.txt", "r");
  while(fgets(line, 212, fp)) {
    if(lineIndex == LINE_SEEDS) {
      parseSeeds(line, seeds);
    }
    if(lineIndex > LINE_SEED_TO_SOIL_START && lineIndex < LINE_SEED_TO_SOIL_END) {
      long output[3];
      parseMapLine(line, output);
      struct Map map;
      map.destination = output[0];
      map.source = output[1];
      map.length = output[2];
      mapSeedToSoil[mapSeedToSoilIndex] = map;
      mapSeedToSoilIndex ++;
    }
    if(lineIndex > LINE_SOIL_TO_FERTILIZER_START && lineIndex < LINE_SOIL_TO_FERTILIZER_END) {
      long output[3];
      parseMapLine(line, output);
      struct Map map;
      map.destination = output[0];
      map.source = output[1];
      map.length = output[2];
      mapSoilToFertilizer[mapSoilToFertilizerIndex] = map;
      mapSoilToFertilizerIndex ++;
    }
    if(lineIndex > LINE_FERTILIZER_TO_WATER_START && lineIndex < LINE_FERTILIZER_TO_WATER_END) {
      long output[3];
      parseMapLine(line, output);
      struct Map map;
      map.destination = output[0];
      map.source = output[1];
      map.length = output[2];
      mapFertilizerToWater[mapFertilizerToWaterIndex] = map;
      mapFertilizerToWaterIndex ++;
    }
    if(lineIndex > LINE_WATER_TO_LIGHT_START && lineIndex < LINE_WATER_TO_LIGHT_END) {
      long output[3];
      parseMapLine(line, output);
      struct Map map;
      map.destination = output[0];
      map.source = output[1];
      map.length = output[2];
      mapWaterToLight[mapWaterToLightIndex] = map;
      mapWaterToLightIndex ++;
    }
    if(lineIndex > LINE_LIGHT_TO_TEMPERATURE_START && lineIndex < LINE_LIGHT_TO_TEMPERATURE_END) {
      long output[3];
      parseMapLine(line, output);
      struct Map map;
      map.destination = output[0];
      map.source = output[1];
      map.length = output[2];
      mapLightToTemperature[mapLightToTemperatureIndex] = map;
      mapLightToTemperatureIndex ++;
    }
    if(lineIndex > LINE_TEMPERATURE_TO_HUMIDITY_START && lineIndex < LINE_TEMPERATURE_TO_HUMIDITY_END) {
      long output[3];
      parseMapLine(line, output);
      struct Map map;
      map.destination = output[0];
      map.source = output[1];
      map.length = output[2];
      mapTemperatureToHumidity[mapTemperatureToHumidityIndex] = map;
      mapTemperatureToHumidityIndex ++;
    }
    if(lineIndex > LINE_HUMIDITY_TO_LOCATION_START && lineIndex < LINE_HUMIDITY_TO_LOCATION_END) {
      long output[3];
      parseMapLine(line, output);
      struct Map map;
      map.destination = output[0];
      map.source = output[1];
      map.length = output[2];
      mapHumidityToLocation[mapHumidityToLocationIndex] = map;
      mapHumidityToLocationIndex ++;
    }
    
    lineIndex ++;
  }

  // Convert seeds to locations
  long locations[20];
  for(int i=0; i<20; i++) {
    long input = seeds[i];
    input = applyMap(input, mapSeedToSoil, LINE_SEED_TO_SOIL_LENGTH);
    input = applyMap(input, mapSoilToFertilizer, LINE_SOIL_TO_FERTILIZER_LENGTH);
    input = applyMap(input, mapFertilizerToWater, LINE_FERTILIZER_TO_WATER_LENGTH);
    input = applyMap(input, mapWaterToLight, LINE_WATER_TO_LIGHT_LENGTH);
    input = applyMap(input, mapLightToTemperature, LINE_LIGHT_TO_TEMPERATURE_LENGTH);
    input = applyMap(input, mapTemperatureToHumidity, LINE_TEMPERATURE_TO_HUMIDITY_LENGTH);
    input = applyMap(input, mapHumidityToLocation, LINE_HUMIDITY_TO_LOCATION_LENGTH);
    locations[i] = input;
  }

  long smallestLocation = locations[0];
  for(int i=1; i<20; i++) {
    if(locations[i] < smallestLocation) {
      smallestLocation = locations[i];
    }
  }

  // Print the seeds
  printf("Seeds: ");
  for(int i=0; i<20; i++) {
    printf("%ld ", seeds[i]);
  }

  // Print the maps
  printf("\n\nMap Seed to Soil:\n");
  for(int i=0; i<LINE_SEED_TO_SOIL_LENGTH; i++) {
    printf("%ld %ld %ld\n", mapSeedToSoil[i].destination, mapSeedToSoil[i].source, mapSeedToSoil[i].length);
  }

  printf("\nMap Soil to Fertilizer:\n");
  for(int i=0; i<LINE_SOIL_TO_FERTILIZER_LENGTH; i++) {
    printf("%ld %ld %ld\n", mapSoilToFertilizer[i].destination, mapSoilToFertilizer[i].source, mapSoilToFertilizer[i].length);
  }

  printf("\nMap Fertilizer to Water:\n");
  for(int i=0; i<LINE_FERTILIZER_TO_WATER_LENGTH; i++) {
    printf("%ld %ld %ld\n", mapFertilizerToWater[i].destination, mapFertilizerToWater[i].source, mapFertilizerToWater[i].length);
  }

  printf("\nMap Water to Light:\n");
  for(int i=0; i<LINE_WATER_TO_LIGHT_LENGTH; i++) {
    printf("%ld %ld %ld\n", mapWaterToLight[i].destination, mapWaterToLight[i].source, mapWaterToLight[i].length);
  }

  printf("\nMap Light to Temperature:\n");
  for(int i=0; i<LINE_LIGHT_TO_TEMPERATURE_LENGTH; i++) {
    printf("%ld %ld %ld\n", mapLightToTemperature[i].destination, mapLightToTemperature[i].source, mapLightToTemperature[i].length);
  }

  printf("\nMap Temperature to Humidity:\n");
  for(int i=0; i<LINE_TEMPERATURE_TO_HUMIDITY_LENGTH; i++) {
    printf("%ld %ld %ld\n", mapTemperatureToHumidity[i].destination, mapTemperatureToHumidity[i].source, mapTemperatureToHumidity[i].length);
  }

  printf("\nMap Humidity to Location:\n");
  for(int i=0; i<LINE_HUMIDITY_TO_LOCATION_LENGTH; i++) {
    printf("%ld %ld %ld\n", mapHumidityToLocation[i].destination, mapHumidityToLocation[i].source, mapHumidityToLocation[i].length);
  }

  // Print smallest location
  printf("Smallest location: %ld\n", smallestLocation);

  // Close file
  fclose(fp);
  return 0;
}