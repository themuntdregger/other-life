#ifdef EYE_CANDY

// I N C L U D E S ////////////////////////////////////////////////////////////

#include "eye_candy.h"
#include "math_cache.h"

#include "effect_wind.h"

namespace ec
{

// C L A S S   F U N C T I O N S //////////////////////////////////////////////

WindParticle::WindParticle(Effect* _effect, ParticleMover* _mover, const Vec3 _pos, const Vec3 _velocity, const coord_t _min_height, const coord_t _max_height, const WindEffect::WindType _type) : Particle(_effect, _mover, _pos, _velocity)
{
  state = 0;
  flare_max = 1.0;
  flare_exp = 1.0;
  flare_frequency = 1.0;
  min_height = _min_height;
  max_height = _max_height;
  type = _type;
  angle_t angle, rise;
  switch (type)
  {
    case WindEffect::LEAVES:
    {
      color[0] = 0.35 + randcolor(0.3);
      color[1] = 0.2 + randcolor(0.2);
      color[2] = 0.0 + randcolor(0.25);
      size = 0.08;
      alpha = 1.0;
      subtype = rand() % 3;	// Store it in case we need it later -- say, for a texture.
      switch (subtype)
      {
        case 0:	// Maple
        {
          angle = randangle(30 * (PI / 180)) + (240 * (PI / 180));
          rise = randangle(30 * (PI / 180)) + (-10 * (PI / 180));
          rotation_axes[0] = Vec3(sin(angle) * cos(rise), sin(rise), cos(angle) * cos(rise));
          axis_weights[0] = (sin(rise) + 0.2) * (randangle(0.3) + 0.85);
          angle = -randangle(30 * (PI / 180)) + (120 * (PI / 180));
          rise = randangle(30 * (PI / 180)) + (-10 * (PI / 180));
          rotation_axes[1] = Vec3(sin(angle) * cos(rise), sin(rise), cos(angle) * cos(rise));
          axis_weights[1] = (sin(rise) + 0.2) * (randangle(0.3) + 0.85);
          angle = randangle(30 * (PI / 180)) + (165 * (PI / 180));
          rise = randangle(30 * (PI / 180)) + (-10 * (PI / 180));
          rotation_axes[2] = Vec3(sin(angle) * cos(rise), sin(rise), cos(angle) * cos(rise));
          axis_weights[2] = (sin(rise) + 0.2) * (randangle(0.3) + 1.0);
          break;
        }
        case 1: // Oak
        {
          angle = randangle(30 * (PI / 180)) + (220 * (PI / 180));
          rise = randangle(40 * (PI / 180)) + (-12 * (PI / 180));
          rotation_axes[0] = Vec3(sin(angle) * cos(rise), sin(rise), cos(angle) * cos(rise));
          axis_weights[0] = (sin(rise) + 0.2) * (randangle(0.2) + 0.5);
          angle = -randangle(30 * (PI / 180)) + (140 * (PI / 180));
          rise = randangle(40 * (PI / 180)) + (-12 * (PI / 180));
          rotation_axes[1] = Vec3(sin(angle) * cos(rise), sin(rise), cos(angle) * cos(rise));
          axis_weights[1] = (sin(rise) + 0.2) * (randangle(0.2) + 0.5);
          angle = randangle(20 * (PI / 180)) + (170 * (PI / 180));
          rise = randangle(20 * (PI / 180)) + (-7 * (PI / 180));
          rotation_axes[2] = Vec3(sin(angle) * cos(rise), sin(rise), cos(angle) * cos(rise));
          axis_weights[2] = (sin(rise) + 0.2) * (randangle(0.3) + 1.0);
          break;
        }
        case 2:	// Ash
        {
          angle = randangle(30 * (PI / 180)) + (200 * (PI / 180));
          rise = randangle(40 * (PI / 180)) + (-12 * (PI / 180));
          rotation_axes[0] = Vec3(sin(angle) * cos(rise), sin(rise), cos(angle) * cos(rise));
          axis_weights[0] = (sin(rise) + 0.2) * (randangle(0.15) + 0.3);
          angle = -randangle(30 * (PI / 180)) + (160 * (PI / 180));
          rise = randangle(40 * (PI / 180)) + (-12 * (PI / 180));
          rotation_axes[1] = Vec3(sin(angle) * cos(rise), sin(rise), cos(angle) * cos(rise));
          axis_weights[1] = (sin(rise) + 0.2) * (randangle(0.15) + 0.3);
          angle = randangle(20 * (PI / 180)) + (170 * (PI / 180));
          rise = randangle(15 * (PI / 180)) + (-6 * (PI / 180));
          rotation_axes[2] = Vec3(sin(angle) * cos(rise), sin(rise), cos(angle) * cos(rise));
          axis_weights[2] = (sin(rise) + 0.2) * (randangle(0.3) + 1.0);
          break;
        } 
      }
      break;
    }
    case WindEffect::FLOWER_PETALS:
    {
      color[0] = 0.6;
      color[1] = 0.2 + randcolor(0.15);
      color[2] = 0.2 + randcolor(0.15);
      size = 0.035 + randangle(0.025);
      alpha = 0.9;

      angle = randangle(60 * (PI / 180)) + (210 * (PI / 180));
      rise = randangle(60 * (PI / 180)) + (-20 * (PI / 180));
      rotation_axes[0] = Vec3(sin(angle) * cos(rise), sin(rise), cos(angle) * cos(rise));
      axis_weights[0] = (sin(rise) + 0.2) * (randangle(0.3) + 0.5);
      angle = -randangle(60 * (PI / 180)) + (90 * (PI / 180));
      rise = randangle(60 * (PI / 180)) + (-20 * (PI / 180));
      rotation_axes[1] = Vec3(sin(angle) * cos(rise), sin(rise), cos(angle) * cos(rise));
      axis_weights[1] = (sin(rise) + 0.2) * (randangle(0.3) + 0.5);
      angle = randangle(60 * (PI / 180)) + (150 * (PI / 180));
      rise = randangle(60 * (PI / 180)) + (-20 * (PI / 180));
      rotation_axes[2] = Vec3(sin(angle) * cos(rise), sin(rise), cos(angle) * cos(rise));
      axis_weights[2] = (sin(rise) + 0.2) * (randangle(0.3) + 0.5);
      break;
    }
    case WindEffect::SNOW:
    {
      color[0] = 0.8 + randcolor(0.2);
      color[1] = 0.8 + randcolor(0.2);
      color[2] = 0.9 + randcolor(0.1);
      size = 0.006 + randcolor(0.004);
      alpha = 0.7;

      angle = 240 * (PI / 180);
      rotation_axes[0] = Vec3(sin(angle), 0.0, cos(angle));
      axis_weights[2] = randangle(0.1) + 0.5;
      angle = 120 * (PI / 180);
      rotation_axes[1] = Vec3(sin(angle), 0.0, cos(angle));
      axis_weights[2] = randangle(0.1) + 0.5;
      angle = 180 * (PI / 180);
      rotation_axes[2] = Vec3(sin(angle), 0.0, cos(angle));
      axis_weights[2] = randangle(0.1) + 0.5;
      break;
    }
  }
/*
  // Normalize axis weights
  percent_t sum = 0;
  for (int i = 0; i < 3; i++)
    coord_t distance_squared = (camera - *(e->pos)).magnitude_squared();
    sum += axis_weights[i];
  for (int i = 0; i < 3; i++)
    axis_weights[i] /= sum;
*/
}

bool WindParticle::idle(const Uint64 delta_t)
{
  if (effect->recall)
    return false;
  
  WindEffect* wind_effect = (WindEffect*)effect;
  const Uint64 age = get_time() - born;
  const interval_t usec = delta_t / 1000000.0;
  const Vec3 cur_wind = get_wind_vec();

//  std::cout << "Wind vec: " << cur_wind.magnitude() << ", " << cur_wind << std::endl;
  float divisor;
  switch (type)
  {
    case WindEffect::LEAVES:
    {
      divisor = 100000;
      break;
    }
    case WindEffect::FLOWER_PETALS:
    {
      divisor = 200000;
      break;
    }
    case WindEffect::SNOW:
    {
      divisor = 300000;
      break;
    }
    default: // Should never reach.
    {
      divisor = 0;
      break;
    }
  }

  const float scalar = math_cache.powf_05_close((interval_t)delta_t / divisor);
  velocity = velocity * scalar + cur_wind * (1.0 - scalar);
  
  if (pos.y < min_height)
  {
    velocity /= ((min_height - pos.y + 1.0) * 8);
    pos.y = min_height;
    if (!(rand() % 3))
      velocity.y = -velocity.y * 1.5;
  }
  else
  {
    pos.y -= 0.2 * usec;
    if (pos.y < min_height)
      pos.y = min_height;
  }
  
//  std::cout << "Pos: " << pos << std::endl;
//  std::cout << "Velocity: " << velocity.magnitude() << ", " << velocity << std::endl;

  if (age > 50000000)
  {
    state = 1;
  }

  if (state == 0)
  {
    if (pos.y > max_height)
      velocity.y -= delta_t / 2000000.0;

    Vec3 shifted_pos = pos - wind_effect->center;
    const coord_t radius = fastsqrt(square(shifted_pos.x) + square(shifted_pos.z));
    coord_t max_radius = 0.0;
    const angle_t angle = atan2(shifted_pos.x, shifted_pos.z);
    for (std::vector<PolarCoordElement>::const_iterator iter = wind_effect->bounding_range.begin(); iter != wind_effect->bounding_range.end(); iter++)
      max_radius += iter->get_radius(angle);
    if (radius > max_radius)
    {	// Pass it off to a neighboring effect.
      if (wind_effect->neighbors.size() == 0)
      {
        state = 1;
        return true;
      }
      std::vector<WindEffect::WindNeighbor>::iterator iter;
      for (iter = wind_effect->neighbors.begin(); iter != wind_effect->neighbors.end(); iter++)
      {
        if ((angle > iter->start_angle) && (angle <= iter->end_angle))
          break;
      }
      if (iter == wind_effect->neighbors.end())
        iter = wind_effect->neighbors.begin();
      if (iter->neighbor == NULL)
      {
        state = 1;
        return true;
      }
      effect->particles.erase(this);
      effect = iter->neighbor;
      effect->particles[this] = true;
    }
  }
  else
  {
    pos.y += delta_t / 800000.0;
    if (pos.y > max_height * 2)
    {
      return false;
    }
  }
    
  // Rotate the blowing object.
  angle_t rot_scalar;
  switch (type)
  {
    case WindEffect::LEAVES:
    {
      rot_scalar = 2.0;
      break;
    }
    case WindEffect::FLOWER_PETALS:
    {
      rot_scalar = 3.5;
      break;
    }
    case WindEffect::SNOW:
    {
      rot_scalar = 30.0;
      break;
    }
    default: // Should never reach.
    {
      rot_scalar = 0;
      break;
    }
  }
  if (pos.y >= min_height + 0.05)
  {
    for (int i = 0; i < 3; i++)
    {
      const angle_t rot = rot_scalar * randangle(10.0) * usec * axis_weights[i] * (rotation_axes[i].dot(cur_wind)) * (3.0 + velocity.y) + randangle(0.6) * usec;
      Quaternion cur_rotation;
      cur_rotation.from_axis_and_angle(rotation_axes[i], rot);
      quaternion *= cur_rotation;
    }
  }

  return true;
}

GLuint WindParticle::get_texture(const Uint16 res_index)	// Shouldn't be needed.  But just in case...
{
  switch (type)
  {
    case WindEffect::LEAVES:
      return base->TexFlare.get_texture(res_index);
    case WindEffect::FLOWER_PETALS:
      return base->TexCrystal.get_texture(res_index);
    case WindEffect::SNOW:
      return base->TexSimple.get_texture(res_index);
  }
  return 0;	// Control should never reach here.
}

void WindParticle::draw(const Uint64 usec)
{
  coord_t distance_squared = (base->camera - pos).magnitude_squared();
  if (distance_squared > MAX_DRAW_DISTANCE_SQUARED)
    return;

  glEnable(GL_LIGHTING);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_TEXTURE_2D);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glPushMatrix();
//  glLoadIdentity();
  float new_matrix[16];
  glTranslatef(pos.x, pos.y, pos.z);
  glMultMatrixf(quaternion.get_matrix(new_matrix));
  GLuint texture;
  switch (type)
  {
    case WindEffect::LEAVES:
    {
      switch (subtype)
      {
        case 0:	// Maple
        {
          texture = base->TexLeafMaple.get_texture(2);
          break;
        }
        case 1: // Oak
        {
          texture = base->TexLeafOak.get_texture(2);
          break;
        }
        case 2:	// Ash
        {
          texture = base->TexLeafAsh.get_texture(2);
          break;
        } 
        default: // Should never reach.
        {
          texture = 0;
          break;
        }
      }
      break;
    }
    case WindEffect::FLOWER_PETALS:
    {
      texture = base->TexPetal.get_texture(2);
      break;
    }
    case WindEffect::SNOW:
    {
      texture = base->TexSnowflake.get_texture(2);
      break;
    }
    default: // Should never reach.
    {
      texture = 0;
      break;
    }
  }

  glBindTexture(GL_TEXTURE_2D, texture);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT);
  glColor4f(color[0] * 3, color[1] * 3, color[2] * 3, alpha);
  glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
  glColor4f(color[0] * 1.5, color[1], color[2], alpha);

  if (effect->LOD < 4)
  {
    glBegin(GL_QUADS);
    {
      glNormal3f(0.0, 1.0, 0.0);
      glTexCoord2f(0.0, 0.0);
      glVertex3f(-size, 0.0, -size);
      glTexCoord2f(1.0, 0.0);
      glVertex3f(size, 0.0, -size);
      glTexCoord2f(1.0, 1.0);
      glVertex3f(size, 0.0, size);
      glTexCoord2f(0.0, 1.0);
      glVertex3f(-size, 0.0, size);
    }
    glEnd();
  }
  else
  {
    glBegin(GL_TRIANGLE_FAN);
    {
      glNormal3f(0.0, 1.0, 0.0);
      glTexCoord2f(0.5, 0.0);
      glVertex3f(0.0, 0.0, -size);
      glNormal3f(-0.3, 0.95, 0.0);
      glTexCoord2f(0.0, 0.5);
      glVertex3f(-size, size / 5, 0.0);
      glNormal3f(0.0, 1.0, 0.0);
      glTexCoord2f(0.5, 1.0);
      glVertex3f(0.0, 0.0, size);
      glNormal3f(0.3, 0.95, 0.0);
      glTexCoord2f(1.0, 0.5);
      glVertex3f(size, size / 5, 0.0);
    }
    glEnd();
  }

  glPopMatrix();
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE);
  glDisable(GL_LIGHTING);
}

Vec3 WindParticle::get_wind_vec() const
{
  const WindEffect* e = (WindEffect*)effect;
  const float time_offset = (float)((unsigned short)(get_time() / 10000)) * PI / 2000.0;	// Translation: Convert to milliseconds, truncate the higher-order digits, convert to a float, make it wraparound in radians, and scale it down some.
  const unsigned short individual_offset = (unsigned short)(long)(void*)(this); 	// Based on the memory address in order to give each particle a unique bias.
  srand(individual_offset);
  const float offset = randfloat() * 0.5;

  const coord_t x = 1.0 * sin(offset + pos.x * 0.5283 + pos.z * 0.7111 + time_offset * 0.6817) * sin(offset + pos.x * 1.2019 + pos.z * 0.5985 + time_offset * 1.5927) * e->max_adjust / (fabs(pos.y - e->center.y) + 1);
  const coord_t y = 1.0 * sin(offset + pos.x * 0.4177 + pos.z * 1.3127 + time_offset * 1.1817) * sin(offset + pos.x * 0.5828 + pos.z * 0.6888 + time_offset * 2.1927) * e->max_adjust * 1.5;
  const coord_t z = 1.0 * sin(offset + pos.x * 1.1944 + pos.z * 0.9960 + time_offset * 1.6817) * sin(offset + pos.x * 0.6015 + pos.z * 1.4809 + time_offset * 1.4927) * e->max_adjust / (fabs(pos.y - e->center.y) + 1);

//  Vec3 random_component;
//  random_component.randomize(max_adjust / 4);
//  std::cout << this << ",\t" << pos << ",\t" << velocity << ":\t" << Vec3(x, y, z) << ",\t" << (e->overall_wind + Vec3(x, y, z)) << std::endl;
//  std::cout << "  **\t" << offset << ",\t" << (pos.x * 1.9283) << ",\t" << (pos.z * 2.4111) << ",\t" << (time_offset * 2.2817) << " =>\t" << sin(offset + pos.x * 1.9283 + pos.z * 2.4111 + time_offset * 2.2817) << std::endl;
//  std::cout << "  **\t" << offset << ",\t" << (pos.x * 3.4019) << ",\t" << (pos.z * 2.0985) << ",\t" << (time_offset * 4.1927) << " =>\t" << sin(offset + pos.x * 3.4019 + pos.z * 2.0985 + time_offset * 4.1927) << std::endl;
  return e->overall_wind + Vec3(x, y, z);// + random_component;
}

WindEffect::WindEffect(EyeCandy* _base, bool* _dead, Vec3* _pos, std::vector<ec::Obstruction*>* _obstructions, const float _density, const std::vector<PolarCoordElement> _bounding_range, const WindType _type, const Vec3 _prevailing_wind)
{
  if (EC_DEBUG)
    std::cout << "WindEffect (" << this << ") created." << std::endl;
  base = _base;
  dead = _dead;
  pos = _pos;
  center = *pos;
  obstructions = _obstructions;
  type = _type;
  prevailing_wind = _prevailing_wind;
  overall_wind = prevailing_wind;
  max_adjust = 0.2 + prevailing_wind.magnitude() * 0.5;
  overall_wind_adjust = Vec3(0.0, 0.0, 0.0);
  bounding_range = _bounding_range;
  mover = new GradientMover(this);
  spawner = new FilledPolarCoordsSpawner(_bounding_range);
  max_LOD1_count = (int)(spawner->get_area() * _density * 1.0) / 10;
  count = LOD * max_LOD1_count;
  switch (type)
  {
    case LEAVES:
    {
      count *= 1;
      break;
    }
    case FLOWER_PETALS:
    {
      count *= 3;
      break;
    }
    case SNOW:
    {
      count *= 8;
      break;
    }
  }
}

WindEffect::~WindEffect()
{
  delete mover;
  delete spawner;
  if (EC_DEBUG)
    std::cout << "WindEffect (" << this << ") destroyed." << std::endl;
}

coord_t WindEffect::get_radius(const angle_t angle) const
{
  coord_t radius = 0;
  for (std::vector<PolarCoordElement>::const_iterator iter = bounding_range.begin(); iter != bounding_range.end(); iter++)
    radius += iter->get_radius(angle);
  return radius;
}

void WindEffect::set_pass_off(std::vector<Effect*> pass_off_to)
{
  std::vector<WindEffect*> new_vec;
  for (std::vector<Effect*>::iterator iter = pass_off_to.begin(); iter != pass_off_to.end(); iter++)
    new_vec.push_back((WindEffect*)(*iter));
  set_pass_off(new_vec);
}

void WindEffect::set_pass_off(std::vector<WindEffect*> pass_off_to)
{
  // Get the max extents for each neighbor.
  for (std::vector<WindEffect*>::iterator iter = pass_off_to.begin(); iter != pass_off_to.end(); iter++)
  {
    WindNeighbor n;
    WindEffect* eff = *iter;
    n.neighbor = eff;
    const coord_t dist = (center - eff->center).magnitude();
    const angle_t angle = center.angle_to(eff->center);
    const angle_t opposite_angle = remainderf(angle + PI, 2 * PI);
    const coord_t radius1 = get_radius(angle);
    const coord_t radius2 = eff->get_radius(opposite_angle);
    if (dist > radius1 + radius2)
      continue;

    angle_t angle_shift = 0.01;
    angle_t start_angle = angle - angle_shift;
    for (; ; angle_shift += 0.01, start_angle -= 0.01)
    {
      if (start_angle < 0)
        start_angle += 2 * PI;
      const percent_t distance_penalty = cos(angle_shift);
      const coord_t radius1 = get_radius(angle);
      const coord_t radius2 = eff->get_radius(opposite_angle);
      const coord_t newdist = (radius1 + radius2) / distance_penalty;
      if (dist < newdist)
        break;
    }
    n.start_angle = start_angle;
    if (n.start_angle < 0)
      n.end_angle += 2 * PI;

    angle_shift = 0.01;
    float end_angle = angle - angle_shift;
    for (; ; angle_shift += 0.01, end_angle += 0.01)
    {
      if (end_angle >= 2 * PI)
        end_angle -= 2 * PI;
      const percent_t distance_penalty = cos(angle_shift);
      const coord_t radius1 = get_radius(angle);
      const coord_t radius2 = eff->get_radius(opposite_angle);
      const coord_t newdist = (radius1 + radius2) / distance_penalty;
      if (dist < newdist)
        break;
    }
    n.end_angle = end_angle;
    if (n.end_angle >= 2 * PI)
      n.end_angle -= 2 * PI;
    
    neighbors.push_back(n);
  }
  
  // Eliminate overlap and insert nulls between extents that don't reach each other.
  if (neighbors.size())
  {
    WindNeighbor* previous = &(*(neighbors.begin() + (neighbors.size() - 1)));
    for (int i = 0; i < (int)neighbors.size(); i++)
    {
      std::vector<WindNeighbor>::iterator iter = neighbors.begin() + i;
      WindNeighbor* current = &(*iter);
      angle_t end_angle = previous->end_angle;
      if (end_angle - current->start_angle > PI)
        end_angle -= 2 * PI;
      if (end_angle > current->start_angle)
      {	// Narrow down the angles.
        angle_t average = (end_angle + current->start_angle) / 2;
        if (average < 0)
          average += 2 * PI;
        previous->end_angle = average;
        current->start_angle = average;
      }
      else
      {	// Insert a null
        WindNeighbor n;
        n.neighbor = NULL;
        n.start_angle = previous->end_angle;
        n.end_angle = current->start_angle;
        neighbors.insert(iter, n);
        i++;
      }
      previous = current;
    }
  }

  // Spawn leaves
  while ((int)particles.size() < count)
  {
    const Vec3 coords = spawner->get_new_coords() + center + Vec3(0.0, 0.1 + randcoord(1.0), 0.0);
    Vec3 velocity;
    velocity.randomize(max_adjust / 4);
    velocity.y /= 2;
    Particle* p = new WindParticle(this, mover, coords, velocity, center.y + 0.05, center.y + 1.0, type);
    if (!base->push_back_particle(p))
      break;
  }
}

bool WindEffect::idle(const Uint64 usec)
{
  if ((recall) && (particles.size() == 0))
    return false;
    
  if (recall)
    return true;
    
  Vec3 velocity_shift;
  velocity_shift.randomize();
  velocity_shift.y /= 2;
  velocity_shift.normalize(0.00004 * 4 * fastsqrt(usec));
  overall_wind_adjust += velocity_shift;
  const coord_t magnitude = overall_wind_adjust.magnitude();
  if (magnitude > max_adjust * 3.5)
  {
//    std::cout << "Adjusting down." << std::endl;
    overall_wind_adjust /= (magnitude / (max_adjust * 3.5));
  }
//  std::cout << "Wind adjust: " << overall_wind_adjust.magnitude() << ", " << overall_wind_adjust << std::endl;
    
  if (fabs(overall_wind_adjust.y) > 0.15)
    overall_wind_adjust.y *= math_cache.powf_05_close(usec / 300000.0);

  overall_wind = prevailing_wind + overall_wind_adjust;

  count = LOD * max_LOD1_count;
  switch (type)
  {
    case LEAVES:
    {
      count *= 1;
      break;
    }
    case FLOWER_PETALS:
    {
      count *= 3;
      break;
    }
    case SNOW:
    {
      count *= 8;
      break;
    }
  }

  while ((int)particles.size() < count)
  {
    const Vec3 coords = spawner->get_new_coords() + center + Vec3(0.0, 1.0 + randcoord(1.0), 0.0);
    Vec3 velocity;
    velocity.randomize(max_adjust / 2);
    velocity.y /= 2;
    Particle* p = new WindParticle(this, mover, coords, velocity, center.y + 0.05, center.y + 4.0, type);
    if (!base->push_back_particle(p))
    {
      break;
    }
  }
    
  return true;
}

///////////////////////////////////////////////////////////////////////////////

};

#endif	// #ifdef EYE_CANDY