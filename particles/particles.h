#ifndef __PARTICLES_H__
#define __PARTICLES_H__

#define NUM_PARTICLES 1000

#include <raylib.h>
typedef struct {
  int active;
  Vector2 pos;
  Vector2 vel;
  int size_begin;
  int size_end;
  float lifetime;
  float life_remaining;
} Particle;

typedef struct {
  Particle particles_pool[NUM_PARTICLES];
  int pool_index;
} ParticleState;

void update_particles(ParticleState *, float);
void draw_particles(ParticleState *);
void emit_particle(ParticleState *, Vector2);

#endif // !__PARTICLES_H__
