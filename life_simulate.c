#pragma warning(push, 0)
#include <stdint.h>

#define WIN32_LEAN_AND_MEAN
#define UNICODE
#include <windows.h>
#pragma(pop)

#pragma warning(disable :5045)

typedef struct
{
  uint32_t x;
  uint32_t y;
} start_coord_t;

uint8_t *simulate_life(uint32_t grid_dim, start_coord_t *initial_points, uint32_t initial_point_count)
{
  //TODO: Implement this function!
  return 0;
}

