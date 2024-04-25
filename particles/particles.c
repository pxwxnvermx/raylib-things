#include "particles.h"
#include "raylib.h"
#include "raymath.h"
#include <stdlib.h>

void update_particles(ParticleState *particle_state, float delta) {
  for (size_t i = 0; i < NUM_PARTICLES; i++) {
    Particle *particle = &particle_state->particles_pool[i];
    if (particle->active == 0)
      continue;

    if (particle->life_remaining <= 0.0f) {
      particle->active = 0;
      continue;
    }

    particle->life_remaining -= delta;
    particle->pos = Vector2Add(
        particle->pos, Vector2Multiply(particle->vel, (Vector2){delta, delta}));
  }
}

void draw_particles(ParticleState *particle_state) {
  for (size_t i = 0; i < NUM_PARTICLES; i++) {
    Particle particle = particle_state->particles_pool[i];
    float life = particle.life_remaining / particle.lifetime;
    Color color = Fade(BLACK, life);
    int size = Lerp(particle.size_end, particle.size_begin, life);
    DrawRectangleV(particle.pos, (Vector2){size, size}, color);
  }
  return;
}

void emit_particle(ParticleState *particle_state, Vector2 pos) {
  Particle *particle =
      &particle_state->particles_pool[particle_state->pool_index];
  particle->active = 1;
  particle->pos = pos;
  particle->vel = (Vector2){
      GetRandomValue(0, 1) - 0.5f,
      GetRandomValue(0, 1) - 0.5f,
  };
  particle->lifetime = 1.0f;
  particle->life_remaining = 1.0f;
  particle->size_begin = 50;
  particle->size_end = 0;

  particle_state->pool_index--;
  if (particle_state->pool_index < 0) {
    particle_state->pool_index = NUM_PARTICLES - 1;
  }
}
