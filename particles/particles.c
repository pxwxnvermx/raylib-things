#include "particles.h"
#include "raylib.h"
#include "raymath.h"
#include <stdlib.h>

void update_particles(ParticleState *particle_state, float delta) {
  for (size_t i = 0; i < NUM_PARTICLES; i++) {
    Particle *particle = &(particle_state->particles_pool[i]);
    if (particle->active == 0)
      continue;

    if (particle->life_remaining <= 0.0f) {
      particle->active = 0;
      continue;
    }

    particle->life_remaining -= delta;
    particle->pos.x += particle->vel.x * delta;
    particle->pos.y += particle->vel.y * delta;
  }
}

void draw_particles(ParticleState *particle_state) {
  for (size_t i = 0; i < NUM_PARTICLES; i++) {
    Particle particle = particle_state->particles_pool[i];
    float life = particle.life_remaining / particle.lifetime;
    Color color = Fade(ORANGE, life);
    int size = Lerp(particle.size_end, particle.size_begin, life);
    DrawCircleV(particle.pos, size, color);
  }
  return;
}

void emit_particle(ParticleState *particle_state, Vector2 pos) {
  Particle *particle =
      &particle_state->particles_pool[particle_state->pool_index];
  particle->active = 1;
  particle->pos = pos;
  particle->size_begin = 10;
  particle->size_end = 5;
  particle->vel = (Vector2){
      particle->size_begin * 10.0f - GetRandomValue(0, 100) * 0.5f,
      particle->size_begin * 10.0f - GetRandomValue(0, 100) * 0.5f,
  };
  particle->lifetime = 1.0f;
  particle->life_remaining = 1.0f;

  particle_state->pool_index--;
  if (particle_state->pool_index < 0) {
    particle_state->pool_index = NUM_PARTICLES - 1;
  }
}
