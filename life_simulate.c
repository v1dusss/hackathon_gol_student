#pragma warning(push, 0)
#include <stdint.h>

#define WIN32_LEAN_AND_MEAN
#define UNICODE
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#pragma(pop)

#pragma warning(disable :5045)
#pragma warning(disable :4711)

// #define TRUE 1
// #define FALSE 0

bool first_run = true;
uint32_t one_map_size;
typedef struct
{
  uint32_t x;
  uint32_t y;
} start_coord_t;

void print_map(uint8_t *map, uint32_t grid_dim, bool first_map)
{
  int cell = 0;

  int map_buffer;
  if (!first_map) {
    map_buffer = one_map_size;
    OutputDebugStringA("map 1:\n");
  } else {
    map_buffer = 0;
    OutputDebugStringA("map 0:\n");
  }


  for (int y = 0; y < grid_dim; y++) {
    if (y == 0) {
      for (int i = 0; i < grid_dim + 1; i++)
        OutputDebugStringA("+");
      OutputDebugStringA("\n+");
    }

    for (int x = 0; x < grid_dim; x++) {
      cell = (y * grid_dim + x) + map_buffer;
      if (map[cell] == 1)
        OutputDebugStringA("o");
      else
        OutputDebugStringA(" ");
    }
    OutputDebugStringA("+\n+");
  }
  for (int i = 0; i < grid_dim + 2; i++)
    OutputDebugStringA("+");
}

void clear_map(uint8_t *map, uint32_t grid_dim, bool first_map)
{
  int buffer = 0;
  if (!first_map)
    buffer = one_map_size;

  for(int i = buffer; i < one_map_size + buffer; i++) {
    map[i] = 0;
  }
}

void swap_maps(uint8_t *map, uint32_t grid_dim)
{
  for (int i = 0; i < one_map_size; i++) {
    map[i + one_map_size] = map[i];
  }
  clear_map(map, grid_dim, true);
}

// int get_alive_neighbors(start_coord_t *initial_points, uint32_t initial_point_count, int x, int y)
// {
//   int count = 0;

//   for (uint32_t j = 0; j < initial_point_count; j++) {
//     if (initial_points[j].x == x && initial_points[j].y == y) {
//       count += 10;
//       continue;
//     }
//     if ((initial_points[j].x == x || initial_points[j].x - 1 == x || initial_points[j].x + 1 == x) && (initial_points[j].y == y || initial_points[j].y - 1 == y || initial_points[j].y + 1 == y))
//       count++;
//   }
//   return count;
// }

// int get_alive_neighbors_for_map(uint8_t *map, uint32_t grid_dim, uint8_t cell)
// {
//   int count = 0;

//   for (int dy = -1; dy < 2; dy++) {
//     for (int dx = -1; dx < 2; dx++) {
//       if (dx == 0 && dy == 0)
//         continue;
//       int cell_old = cell + one_map_size;
//       int neighbor = cell_old + (dy *grid_dim + dx);

//       if ((neighbor >= one_map_size && neighbor <= one_map_size * 2) && map[neighbor] == 1)
//         count++;
//     }
//   }
//   return count;
// }

int get_alive_neighbors_on_edge(uint8_t *map, uint8_t *map_old, uint32_t grid_dim, uint8_t cell, int x, int y)
{
  int count = 0;

  (void)map;

  bool up = false;
  bool down = false;
  bool left = false;
  bool right = false;

  if (y == 0) {
    up = true;
  } else if (y == grid_dim - 1) {
    down = true;
  }
  if (x == 0) {
    left = true;
  } else if (x == grid_dim - 1) {
    right = true;
  }
  
  for (int dy = -1; dy < 2; dy++) {
    for (int dx = -1; dx < 2; dx++) {
      if (dx == 0 && dy == 0)
        continue;
      int neighbor = cell + (dy *grid_dim + dx);
      if (dy == -1 && up == true)
        neighbor += one_map_size;
      if (dy == 1 && down == true)
        neighbor -= one_map_size;

      if (dx == -1 && left == true)
        neighbor += grid_dim;
      if (dx == +1 && right == true)
        neighbor -= grid_dim;
      if (map_old[neighbor] == 1)
        count++;
    }
  }
  return count;
}

int get_alive_neighbors(uint8_t *map, uint8_t *map_old, uint32_t grid_dim, uint8_t cell)
{
  int count = 0;

  (void)map;
  
  for (int dy = -1; dy < 2; dy++) {
    for (int dx = -1; dx < 2; dx++) {
      if (dx == 0 && dy == 0)
        continue;
      int neighbor = cell + (dy *grid_dim + dx);

      if (map_old[neighbor] == 1)
        count++;
    }
  }
  return count;
}

uint8_t *simulate_life(uint32_t grid_dim, start_coord_t *initial_points, uint32_t initial_point_count)
{
  static uint8_t *map;
    char buff[255];
  one_map_size = grid_dim * grid_dim;
  // snprintf(buff, 255, " one_map_size: %d\n", one_map_size);
  // OutputDebugStringA(buff);
  if (first_run == true) {
    OutputDebugStringA("malloc it\n");
    map = (uint8_t *)calloc((one_map_size * 2), sizeof(uint8_t));
    // clear_map(map, grid_dim, true);
    // clear_map(map, grid_dim, false);
    first_run = false;
    for (int i = 0; i < initial_point_count; i++) {
      int y = initial_points[i].y;
      int x = initial_points[i].x;
      map[y * grid_dim + x] = 1;
    }

    // print_map(map, grid_dim, true);
    // OutputDebugStringA("\n");
    // print_map(map, grid_dim, false);
    // Sleep(500);
    return map;
  } else {
    // OutputDebugStringA("no malloc\n");
    swap_maps(map, grid_dim);

    // OutputDebugStringA("\n=================================\n");
    // OutputDebugStringA("swap_maps:\n");
    // print_map(map, grid_dim, true);
    // OutputDebugStringA("\n");
    // print_map(map, grid_dim, false);
    // OutputDebugStringA("\n---------------------------------\n");
  }
  // for (uint32_t i = 0; i < grid_dim*grid_dim; i++) {
  //   map[i] = 0;
  // }

  // for (uint32_t i = 0; i < initial_point_count; i++) {
  //   snprintf(buff, 255, "x: %d, y: %d\n", initial_points[i].x, initial_points[i].y);
  //   OutputDebugStringA(buff);
  //   // map[(initial_points[i].y * grid_dim) + initial_points[i].x] = 1;
  // }
  // OutputDebugStringA("=======================\n");
  uint8_t *map_old = &map[one_map_size];
  int count = 0;
  for (uint32_t y = 0; y < grid_dim; y++) {
    for (uint32_t x = 0; x < grid_dim; x++) {
      int cell = y * grid_dim + x;
      count = 0;
      if (y == 0 || x == 0 || y == grid_dim - 1 || x == grid_dim - 1)
        count = get_alive_neighbors_on_edge(map, map_old, grid_dim, cell, x, y);
        // count = get_alive_neighbors_on_edge(map, map_old, grid_dim, cell);
      else
        count = get_alive_neighbors(map, map_old, grid_dim, cell);
      if ((map_old[cell] == 1 && count == 2) || count == 3)
        map[y*grid_dim + x] = 1;
      else
        map[y*grid_dim + x] = 0;
    }
  }

  // OutputDebugStringA("Final:\n");
  // print_map(map, grid_dim, true);
  // OutputDebugStringA("\n");
  // print_map(map, grid_dim, false);
  // Sleep(200);
  return map;
}

