#pragma warning(push, 0)
#include <stdint.h>

#define WIN32_LEAN_AND_MEAN
#define UNICODE
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#pragma(pop)

#pragma warning(disable :5045)
#pragma warning(disable :4711)

typedef struct
{
  uint32_t x;
  uint32_t y;
} start_coord_t;

int get_alive_neighbors(start_coord_t *initial_points, uint32_t initial_point_count, int x, int y)
{
  int count = 0;

  for (uint32_t j = 0; j < initial_point_count; j++) {
    if (initial_points[j].x == x && initial_points[j].y == y) {
      count += 10;
      continue;
    }
    if ((initial_points[j].x == x || initial_points[j].x - 1 == x || initial_points[j].x + 1 == x) && (initial_points[j].y == y || initial_points[j].y - 1 == y || initial_points[j].y + 1 == y))
      count++;
  }
  return count;
}

uint8_t *simulate_life(uint32_t grid_dim, start_coord_t *initial_points, uint32_t initial_point_count)
{
  uint8_t *map;

  char buff[255];
  map = (uint8_t *)calloc((grid_dim * grid_dim), sizeof(uint8_t));

  for (uint32_t i = 0; i < grid_dim*grid_dim; i++) {
    map[i] = 0;
  }

  for (uint32_t i = 0; i < initial_point_count; i++) {
    snprintf(buff, 255, "x: %d, y: %d\n", initial_points[i].x, initial_points[i].y);
    OutputDebugStringA(buff);
    // map[(initial_points[i].y * grid_dim) + initial_points[i].x] = 1;
  }
  OutputDebugStringA("=======================\n");
  int count = 0;
  for (uint32_t y = 0; y < grid_dim; y++) {
    for (uint32_t x = 0; x < grid_dim; x++) {
      count = 0;
      count = get_alive_neighbors(initial_points, initial_point_count, x, y);
      if (count == 3 || count == 12 || count == 13)
        map[y*grid_dim + x] = 1;
      else
        map[y*grid_dim + x] = 0;
    }
  }
  Sleep(1000);
  return map;
}

