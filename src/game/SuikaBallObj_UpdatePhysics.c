#include "game/SuikaBallObjPhysicsPrivate.h"

#pragma use_lmw_stmw on
void SuikaBallObj_UpdatePhysics(SuikaBallPhysics *ball, Mtx kart, Vec *kart_velocity, float radius)
{
 Mtx kick_rotation;
 BallProbes old_points, new_points;
 Mtx rolling_rotation;
 Vec contact, normal, delta, work, center, right, forward;
 float ground;
 float old_x, old_y, old_z, distance;
 unsigned char wall_hit, on_ground;
 int i, j;
 ball->hit = 0;
 distance = radius + ball->radius;
 old_x = ball->position.x; old_y = ball->position.y; old_z = ball->position.z;
 if (kart && kart_velocity) {
  right.x=kart[0][0]; right.y=kart[1][0]; right.z=kart[2][0];
  forward.x=kart[0][2]; forward.y=kart[1][2]; forward.z=kart[2][2];
  center.x=kart[0][3]; center.y=kart[1][3]; center.z=kart[2][3];
  Vec3_Subtract(&ball->position,&center,&delta);
  if (Vec3_Magnitude(&delta)<distance) {
   float side_abs, side, speed;
   ball->hit=1;
   Vec3_Normalize(&delta,&delta);
   ball->position.x=delta.x*distance+center.x;
   ball->position.y=delta.y*distance+center.y;
   ball->position.z=delta.z*distance+center.z;
   Vec3_Normalize(&ball->velocity,&work);
   if (Vec3_Dot(&delta,&work)<0.0f) {
    PSVECScale(&delta,&work,-2.0f*Vec3_Dot(&delta,&ball->velocity));
    PSVECAdd(&work,&ball->velocity,&ball->velocity);
   }
   work.x=delta.x*radius; work.y=delta.y*radius; work.z=delta.z*radius;
   {
    float forward_dot = Vec3_Dot(&work,&forward);
    if (!forward_dot) goto collision_done;
    side=Vec3_Dot(&work,&right);
    if (side<0.0f) side_abs=-side; else side_abs=side;
    speed=Vec3_Magnitude(kart_velocity);
    if (side_abs<=ball->radius*ball->inner) {
     ball->velocity.x+=2.0f*(kart[0][2]*speed);
     ball->velocity.y+=2.0f*(kart[1][2]*speed)+1.0f;
     ball->velocity.z+=2.0f*(kart[2][2]*speed);
     ball->spin=0.0f;
    } else if (side_abs<=ball->radius*(ball->inner+ball->outer)) {
     float ratio=(side_abs-ball->radius*ball->inner)/(ball->radius*ball->outer);
     if(side<0.0f) ratio*=-1.0f;
     PSMTXRotRad(kick_rotation,'Y',0.017453292f*(45.0f*ratio));
     PSMTXConcat(kart,kick_rotation,kick_rotation);
     ball->velocity.x+=1.5f*(kick_rotation[0][2]*speed);
     ball->velocity.y+=1.5f*(kick_rotation[1][2]*speed)+1.0f;
     ball->velocity.z+=1.5f*(kick_rotation[2][2]*speed);
     ball->spin=0.0f;
    } else {
     ball->spin=speed;
     if(side>0.0f) ball->spin_axis.y=1.0f; else ball->spin_axis.y=-1.0f;
     ball->spin_axis.x=0.0f; ball->spin_axis.z=0.0f;
     ball->velocity.x=0.0f; ball->velocity.z=0.0f;
    }
   }
  }
 }
collision_done:
 {
  float speed=Vec3_Magnitude(&ball->velocity);
  if(speed>10.0f) {
   float scale=10.0f/speed;
   ball->velocity.x*=scale; ball->velocity.y*=scale; ball->velocity.z*=scale;
  }
 }
 PSVECAdd(&ball->position,&ball->velocity,&ball->position);
 old_points=SuikaBallObj_UpdatePhysics_rodata_80355918;
 old_points.v[0].x=old_x+ball->radius; old_points.v[0].y=old_y; old_points.v[0].z=old_z;
 old_points.v[1].x=old_x-ball->radius; old_points.v[1].y=old_y; old_points.v[1].z=old_z;
 old_points.v[2].x=old_x; old_points.v[2].y=old_y; old_points.v[2].z=old_z+ball->radius;
 old_points.v[3].x=old_x; old_points.v[3].y=old_y; old_points.v[3].z=old_z-ball->radius;
 new_points=SuikaBallObj_UpdatePhysics_rodata_80355948;
 new_points.v[0].x=ball->position.x+ball->radius; new_points.v[0].y=ball->position.y; new_points.v[0].z=ball->position.z;
 new_points.v[1].x=ball->position.x-ball->radius; new_points.v[1].y=ball->position.y; new_points.v[1].z=ball->position.z;
 new_points.v[2].x=ball->position.x; new_points.v[2].y=ball->position.y; new_points.v[2].z=ball->position.z+ball->radius;
 new_points.v[3].x=ball->position.x; new_points.v[3].y=ball->position.y; new_points.v[3].z=ball->position.z-ball->radius;
 wall_hit=0;
 for(i=0;i<4;i++) {
  if(Terrain_RaycastWall(&old_points.v[i],&new_points.v[i],&contact,&normal)==1) {
   Vec3_Subtract(&contact,&new_points.v[i],&delta); delta.y=0.0f;
   PSVECAdd(&ball->position,&delta,&ball->position);
   for(j=i;j<4;j++) PSVECAdd(&new_points.v[j],&delta,&new_points.v[j]);
   wall_hit=1;
  }
 }
 if(wall_hit) {
  Vec3_Normalize(&ball->velocity,&work);
  if(Vec3_Dot(&normal,&work)>0.0f) {
   PSVECScale(&normal,&work,-2.0f*Vec3_Dot(&normal,&ball->velocity));
   PSVECAdd(&work,&ball->velocity,&ball->velocity);
   ball->velocity.x*=ball->restitution; ball->velocity.z*=ball->restitution;
  }
 }
 on_ground=0;
 if(Terrain_GetGroundHeight(&ball->position,&ground,0,0)) {
  if(ball->position.y-ball->radius<ground) {
   ball->position.y=ground+ball->radius; ball->velocity.y*=-ball->restitution;
  }
  if(ball->position.y<1.0f+(ground+ball->radius) && ball->position.y>(ground+ball->radius)-1.0f) on_ground=1;
 }
 if(ball->object) {
  if(ball->spin!=0.0f) {
   PSMTXRotAxisRad(rolling_rotation,&ball->spin_axis,0.01f*(3.1415927f*ball->spin));
   PSMTXConcat(rolling_rotation,ball->matrix,ball->matrix);
  } else {
   float speed;
   work.x=ball->velocity.z; work.y=0.0f; work.z=-ball->velocity.x;
   speed=Vec3_Magnitude(&work);
   if(speed>0.0f) {
    PSMTXRotAxisRad(rolling_rotation,&work,0.01f*(3.1415927f*speed));
    PSMTXConcat(rolling_rotation,ball->matrix,ball->matrix);
   }
  }
  ball->matrix[0][3]=ball->position.x; ball->matrix[1][3]=ball->position.y; ball->matrix[2][3]=ball->position.z;
  Object_DriveAnimMatrix(ball->object);
 }
 if(ball->damp) {
  ball->velocity.x*=0.9f; ball->velocity.z*=0.9f;
 } else if(on_ground) {
  ball->velocity.x*=ball->ground_drag; ball->velocity.z*=ball->ground_drag;
 } else {
  ball->velocity.x*=ball->air_drag; ball->velocity.z*=ball->air_drag;
 }
 ball->velocity.y-=ball->gravity; ball->spin*=0.98f;
}
#pragma use_lmw_stmw reset
