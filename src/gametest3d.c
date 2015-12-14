/**
 * gametest3d
 * @license The MIT License (MIT)
 *   @copyright Copyright (c) 2015 EngineerOfLies
 *    Permission is hereby granted, free of charge, to any person obtaining a copy
 *    of this software and associated documentation files (the "Software"), to deal
 *    in the Software without restriction, including without limitation the rights
 *    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *    copies of the Software, and to permit persons to whom the Software is
 *    furnished to do so, subject to the following conditions:
 *    The above copyright notice and this permission notice shall be included in all
 *    copies or substantial portions of the Software.
 *    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *    SOFTWARE.
 */
#include <math.h>
#include <stdio.h>
#include "mgl_callback.h"
#include "simple_logger.h"
#include "graphics3d.h"
#include "shader.h"
#include "obj.h"
#include "vector.h"
#include "sprite.h"
#include "entity.h"
#include "space.h"

int items[4];
#define ITEM_PAPERS 0
#define ITEM_BRASS 1
#define ITEM_PISTOL 2
int bbOn = 0;
int health = 100;
void set_camera(Vec3D position, Vec3D rotation);
void unset_camera(Vec3D position, Vec3D rotation);
Sprite *hptexture;
Sprite *inventory;
Sprite *hp[3];
Sprite *item_Sprites[3];
Vec3D verts[4];
Entity *player;

void drawHealthText(Vec3D offset)
{
	GLfloat matrix[16]; 
	Vec2D uVs[4];
	Vec3D verts[4];
	verts[0].x=-1;
	verts[0].y=1;
	verts[0].z=1;

	verts[1].x=-1;
	verts[1].y=0.66f;
	verts[1].z=1;

	verts[2].x=-0.5f;
	verts[2].y=1;
	verts[2].z=1;

	verts[3].x=-0.5f;
	verts[3].y=0.66f;
	verts[3].z=1;
	

	uVs[0].x=0;
	uVs[0].y=0;

	uVs[1].x=0;
	uVs[1].y=1;
	
	uVs[2].x=1;
	uVs[2].y=0;

	uVs[3].x=1;
	uVs[3].y=1;

	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	glLoadIdentity();

	gluOrtho2D(-1.0f,1,-1,1);
    glEnable(GL_BLEND);
    glColorMaterial(GL_FRONT,GL_DIFFUSE);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,hptexture->texture);
	glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glTranslatef(-offset.x,-offset.y,-offset.z);
	//glRotatef(90.0f,1.0f,0,0);
	glPushMatrix();
	glBegin(GL_TRIANGLES);

    glTexCoord2f(uVs[0].x,uVs[0].y);
	glVertex3f(verts[0].x,verts[0].y,verts[0].z);

	glTexCoord2f(uVs[1].x,uVs[1].y);
	glVertex3f(verts[1].x,verts[1].y,verts[1].z);

	glTexCoord2f(uVs[2].x,uVs[2].y);
	glVertex3f(verts[2].x,verts[2].y,verts[2].z);

	glTexCoord2f(uVs[2].x,uVs[2].y);
	glVertex3f(verts[2].x,verts[2].y,verts[2].z);

	glTexCoord2f(uVs[1].x,uVs[1].y);
	glVertex3f(verts[1].x,verts[1].y,verts[1].z);

	glTexCoord2f(uVs[3].x,uVs[3].y);
	glVertex3f(verts[3].x,verts[3].y,verts[3].z);

	glEnd();
    
    glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
    glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	//glMultMatrixf(matrix);
	
}

void drawHealthBar(Vec3D offset)
{
	GLfloat matrix[16]; 
	Vec2D health1_uVs[4];
	Vec3D health1_verts[4];
	int i;

	Vec2D health2_uVs[4];
	Vec3D health2_verts[4];

	Vec2D health3_uVs[4];
	Vec3D health3_verts[4];

	health1_verts[0].x=-1;
	health1_verts[0].y=1;
	health1_verts[0].z=1;

	health1_verts[1].x=-1;
	health1_verts[1].y=0.66f;
	health1_verts[1].z=1;

	health1_verts[2].x=-0.5f;
	health1_verts[2].y=1;
	health1_verts[2].z=1;

	health1_verts[3].x=-0.5f;
	health1_verts[3].y=0.66f;
	health1_verts[3].z=1;
	
	health1_uVs[0].x=0;
	health1_uVs[0].y=0;

	health1_uVs[1].x=0;
	health1_uVs[1].y=1;
	
	health1_uVs[2].x=1;
	health1_uVs[2].y=0;

	health1_uVs[3].x=1;
	health1_uVs[3].y=1;
	
	glMatrixMode(GL_PROJECTION);
	//glGetFloatv (GL_MODELVIEW_MATRIX, matrix);
	
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(-1.0f,1,-1,1);
    glEnable(GL_BLEND);
    glColorMaterial(GL_FRONT,GL_DIFFUSE);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(-offset.x,-offset.y,-offset.z);
	//glRotatef(90.0f,1.0f,0,0);
	glPushMatrix();

	for(i=0;i<3;i++)
	{
		if(health>=33*(i+1))
		{
			glBindTexture(GL_TEXTURE_2D,hp[i]->texture);
	
			glBegin(GL_TRIANGLES);

			glTexCoord2f(health1_uVs[0].x,health1_uVs[0].y);
			glVertex3f(health1_verts[0].x,health1_verts[0].y,health1_verts[0].z);

			glTexCoord2f(health1_uVs[1].x,health1_uVs[1].y);
			glVertex3f(health1_verts[1].x,health1_verts[1].y,health1_verts[1].z);

			glTexCoord2f(health1_uVs[2].x,health1_uVs[2].y);
			glVertex3f(health1_verts[2].x,health1_verts[2].y,health1_verts[2].z);

			glTexCoord2f(health1_uVs[2].x,health1_uVs[2].y);
			glVertex3f(health1_verts[2].x,health1_verts[2].y,health1_verts[2].z);

			glTexCoord2f(health1_uVs[1].x,health1_uVs[1].y);
			glVertex3f(health1_verts[1].x,health1_verts[1].y,health1_verts[1].z);

			glTexCoord2f(health1_uVs[3].x,health1_uVs[3].y);
			glVertex3f(health1_verts[3].x,health1_verts[3].y,health1_verts[3].z);

			glEnd();
		}
	}
    
    glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
    glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	//glMultMatrixf(matrix);
	
}

void draw_inventory_item(Vec3D offset, int i)
{
	GLfloat matrix[16]; 
	Vec2D item1_uVs[4];
	Vec3D item1_verts[4];

	Vec2D item2_uVs[4];
	Vec3D item2_verts[4];

	Vec2D item3_uVs[4];
	Vec3D item3_verts[4];

	item1_verts[0].x=-1;
	item1_verts[0].y=1;
	item1_verts[0].z=0.9f;

	item1_verts[1].x=-1;
	item1_verts[1].y=0.66f;
	item1_verts[1].z=0.9f;

	item1_verts[2].x=-0.5f;
	item1_verts[2].y=1;
	item1_verts[2].z=0.9f;

	item1_verts[3].x=-0.5f;
	item1_verts[3].y=0.66f;
	item1_verts[3].z=0.9f;
	
	item1_uVs[0].x=0;
	item1_uVs[0].y=0;

	item1_uVs[1].x=0;
	item1_uVs[1].y=1;
	
	item1_uVs[2].x=1;
	item1_uVs[2].y=0;

	item1_uVs[3].x=1;
	item1_uVs[3].y=1;
	
	glMatrixMode(GL_PROJECTION);
	//glGetFloatv (GL_MODELVIEW_MATRIX, matrix);
	
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(-1.0f,1,-1,1);
    glEnable(GL_BLEND);
    glColorMaterial(GL_FRONT,GL_DIFFUSE);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	
	//glRotatef(90.0f,1.0f,0,0);
	glPushMatrix();
glTranslatef(-offset.x,-offset.y,-offset.z);
	
	glBindTexture(GL_TEXTURE_2D,item_Sprites[i]->texture);
	
	glBegin(GL_TRIANGLES);

	glTexCoord2f(item1_uVs[0].x,item1_uVs[0].y);
	glVertex3f(item1_verts[0].x,item1_verts[0].y,item1_verts[0].z);

	glTexCoord2f(item1_uVs[1].x,item1_uVs[1].y);
	glVertex3f(item1_verts[1].x,item1_verts[1].y,item1_verts[1].z);

	glTexCoord2f(item1_uVs[2].x,item1_uVs[2].y);
	glVertex3f(item1_verts[2].x,item1_verts[2].y,item1_verts[2].z);

	glTexCoord2f(item1_uVs[2].x,item1_uVs[2].y);
	glVertex3f(item1_verts[2].x,item1_verts[2].y,item1_verts[2].z);

	glTexCoord2f(item1_uVs[1].x,item1_uVs[1].y);
	glVertex3f(item1_verts[1].x,item1_verts[1].y,item1_verts[1].z);

	glTexCoord2f(item1_uVs[3].x,item1_uVs[3].y);
	glVertex3f(item1_verts[3].x,item1_verts[3].y,item1_verts[3].z);

	glEnd();
		
	
    
    glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
    glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	//glMultMatrixf(matrix);
	
}

void draw_player_inventory(Vec3D offset)
{
	int i;
	GLfloat matrix[16]; 
	Vec2D uVs[4];
	Vec3D verts[4];
	verts[0].x=-0.5f;
	verts[0].y=0.5f;
	verts[0].z=1;

	verts[1].x=-0.5f;
	verts[1].y=-0.5f;
	verts[1].z=1;

	verts[2].x=0.5f;
	verts[2].y=0.5f;
	verts[2].z=1;

	verts[3].x=0.5f;
	verts[3].y=-0.5f;
	verts[3].z=1;
	
	uVs[0].x=0;
	uVs[0].y=0;

	uVs[1].x=0;
	uVs[1].y=1;
	
	uVs[2].x=1;
	uVs[2].y=0;

	uVs[3].x=1;
	uVs[3].y=1;

	
	glMatrixMode(GL_PROJECTION);
	//glGetFloatv (GL_MODELVIEW_MATRIX, matrix);
	
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(-1.0f,1,-1,1);
    glEnable(GL_BLEND);
    glColorMaterial(GL_FRONT,GL_DIFFUSE);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,inventory->texture);
	glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(-offset.x,-offset.y,-offset.z);
	//glRotatef(90.0f,1.0f,0,0);
	glPushMatrix();
	glBegin(GL_TRIANGLES);

    glTexCoord2f(uVs[0].x,uVs[0].y);
	glVertex3f(verts[0].x,verts[0].y,verts[0].z);

	glTexCoord2f(uVs[1].x,uVs[1].y);
	glVertex3f(verts[1].x,verts[1].y,verts[1].z);

	glTexCoord2f(uVs[2].x,uVs[2].y);
	glVertex3f(verts[2].x,verts[2].y,verts[2].z);

	glTexCoord2f(uVs[2].x,uVs[2].y);
	glVertex3f(verts[2].x,verts[2].y,verts[2].z);

	glTexCoord2f(uVs[1].x,uVs[1].y);
	glVertex3f(verts[1].x,verts[1].y,verts[1].z);

	glTexCoord2f(uVs[3].x,uVs[3].y);
	glVertex3f(verts[3].x,verts[3].y,verts[3].z);

	glEnd();
    
    glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
    glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	//glMultMatrixf(matrix);
	for(i=0;i<4;i++)
	{
		if(items[i] == 1)
		{
			draw_inventory_item(vec3d(0,0,0),i);
		}
	}
}

void touch_callback(void *data, void *context)
{
    Entity *me,*other;
    Body *obody;
    if ((!data)||(!context))return;
    me = (Entity *)data;
    obody = (Body *)context;
    if (entity_is_entity(obody->touch.data))
    {
        other = (Entity *)obody->touch.data;
        //slog("%s is ",other->name);
    }
    //slog("touching me.... touching youuuuuuuu");
	me->body.velocity.x=0;
	me->body.velocity.y=0;
	me->body.velocity.z=0;
}

void touch_inventory_callback(void *data, void *context)
{
    Entity *me,*other;
    Body *obody;
    if ((!data)||(!context))return;
    me = (Entity *)data;
    obody = (Body *)context;
    if (entity_is_entity(obody->touch.data))
    {
        other = (Entity *)obody->touch.data;
		if(other == player)
		{
			items[me->type]=1;
		}
        //slog("%s is ",other->name);
    }
   
}

Entity *newCube(Vec3D position,const char *name)
{
    Entity * ent;
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
    ent->objModel = obj_load("models/chair.obj");
    ent->texture = LoadSprite("models/outUVcarp.png",1024,1024);
    vec3d_cpy(ent->body.position,position);
	//slog("wall size %f,%f,%f",ent->objModel->size.x,ent->objModel->size.y,ent->objModel->size.z);
    cube_set(ent->body.bounds,-ent->objModel->size.x/2,-ent->objModel->size.y/2,-ent->objModel->size.z/2,ent->objModel->size.x,
		ent->objModel->size.y,ent->objModel->size.z);
	 ent->type = ITEM_BRASS;
    sprintf(ent->name,"%s",name);
    mgl_callback_set(&ent->body.touch,touch_inventory_callback,ent);
    return ent;
}

Entity *newEnemy(Vec3D position,const char *name)
{
    Entity * ent;
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
    ent->objModel = obj_load("models/badguy.obj");
    ent->texture = LoadSprite("models/badguyuvs.png",1024,1024);
    vec3d_cpy(ent->body.position,position);
	//slog("wall size %f,%f,%f",ent->objModel->size.x,ent->objModel->size.y,ent->objModel->size.z);
    cube_set(ent->body.bounds,-ent->objModel->size.x/2,-ent->objModel->size.y/2,-ent->objModel->size.z/2,ent->objModel->size.x,
		ent->objModel->size.y,ent->objModel->size.z);

    sprintf(ent->name,"%s",name);
    mgl_callback_set(&ent->body.touch,touch_callback,ent);
    return ent;
}

Entity *newFloor(Vec3D position,const char *name)
{
    Entity * ent;
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
    ent->objModel = obj_load("models/8by8floor.obj");
    ent->texture = LoadSprite("models/8by8uv.png",-1,-1);
    vec3d_cpy(ent->body.position,position);
	
    cube_set(ent->body.bounds,-ent->objModel->size.x/2,-ent->objModel->size.y/2,-ent->objModel->size.z/2,ent->objModel->size.x,
		ent->objModel->size.y,ent->objModel->size.z);
    sprintf(ent->name,"%s",name);
    mgl_callback_set(&ent->body.touch,touch_callback,ent);
    return ent;
}

Entity *newWall(Vec3D position,const char *name)
{
    Entity * ent;
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
    ent->objModel = obj_load("models/wall.obj");
    ent->texture = LoadSprite("models/walltexture.png",1024,1024);
    vec3d_cpy(ent->body.position,position);
	
    cube_set(ent->body.bounds,-ent->objModel->size.x/2,-ent->objModel->size.y/2,-ent->objModel->size.z/2,ent->objModel->size.x,
		ent->objModel->size.y,
	ent->objModel->size.z);
		
    sprintf(ent->name,"%s",name);
    mgl_callback_set(&ent->body.touch,touch_callback,ent);
    return ent;
}

Entity *newBox(Vec3D position,const char *name)
{
    Entity * ent;
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
    ent->objModel = obj_load("models/testbox.obj");
    ent->texture = LoadSprite("models/alphanew.png",1024,1024);
    vec3d_cpy(ent->body.position,position);
	
    cube_set(ent->body.bounds,-ent->objModel->size.x/2,-ent->objModel->size.y/2,-ent->objModel->size.z/2,ent->objModel->size.x,
		ent->objModel->size.y,
	ent->objModel->size.z);
		
    sprintf(ent->name,"%s",name);
    mgl_callback_set(&ent->body.touch,touch_callback,ent);
    return ent;
}

Entity *newDemoWall(Vec3D position,const char *name)
{
    Entity * ent;
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
    ent->objModel = obj_load("models/techwall1.obj");
    ent->texture = LoadSprite("models/walltexture.png",1024,1024);
    vec3d_cpy(ent->body.position,position);
    cube_set(ent->body.bounds,-ent->objModel->size.x/2,-ent->objModel->size.y/2,-ent->objModel->size.z/2,ent->objModel->size.x,
		ent->objModel->size.y,ent->objModel->size.z);
		
    sprintf(ent->name,"%s",name);
    mgl_callback_set(&ent->body.touch,touch_callback,ent);
    return ent;
}

Entity *newDemoWallCenter(Vec3D position,const char *name)
{
    Entity * ent;
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
    ent->objModel = obj_load("models/techwall4.obj");
     ent->texture = LoadSprite("models/walltexture.png",1024,1024);
    vec3d_cpy(ent->body.position,position);
	
    cube_set(ent->body.bounds,-ent->objModel->size.x/2,-ent->objModel->size.y/2,-ent->objModel->size.z/2,ent->objModel->size.x,
		ent->objModel->size.y,
	ent->objModel->size.z);
		
    sprintf(ent->name,"%s",name);
    mgl_callback_set(&ent->body.touch,touch_callback,ent);
    return ent;
}

Entity *newDemoDoor(Vec3D position,const char *name)
{
    Entity * ent;
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
    ent->objModel = obj_load("models/techdoor.obj");
    ent->texture = LoadSprite("models/seamless-wood-texture-free-35.png",1024,1024);
    vec3d_cpy(ent->body.position,position);
	
    cube_set(ent->body.bounds,-ent->objModel->size.x/2,-ent->objModel->size.y/2,-ent->objModel->size.z/2,ent->objModel->size.x,
		ent->objModel->size.y,
	ent->objModel->size.z);
		
    sprintf(ent->name,"%s",name);
    mgl_callback_set(&ent->body.touch,touch_callback,ent);
    return ent;
}

Entity *newDemoTable(Vec3D position,const char *name)
{
    Entity * ent;
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
    ent->objModel = obj_load("models/techtable.obj");
     ent->texture = LoadSprite("models/metal_bare_0002_02_preview.png",1024,1024);
    vec3d_cpy(ent->body.position,position);
	
    cube_set(ent->body.bounds,-ent->objModel->size.x/2,-ent->objModel->size.y/2,-ent->objModel->size.z/2,ent->objModel->size.x,
		ent->objModel->size.y,
	ent->objModel->size.z);
		
    sprintf(ent->name,"%s",name);
    mgl_callback_set(&ent->body.touch,touch_callback,ent);
    return ent;
}

Entity *newDemoGun(Vec3D position,const char *name)
{
    Entity * ent;
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
    ent->objModel = obj_load("models/techgun.obj");
     ent->texture = LoadSprite("models/metal_bare_0002_02_preview.png",1024,1024);
	 ent->type = ITEM_PISTOL;
    vec3d_cpy(ent->body.position,position);
	
    cube_set(ent->body.bounds,-ent->objModel->size.x/2,-ent->objModel->size.y/2,-ent->objModel->size.z/2,ent->objModel->size.x,
		ent->objModel->size.y,
	ent->objModel->size.z);
		
    sprintf(ent->name,"%s",name);
    mgl_callback_set(&ent->body.touch,touch_callback,ent);
    return ent;
}

Entity *newDemoKnife(Vec3D position,const char *name)
{
    Entity * ent;
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
    ent->objModel = obj_load("models/techknife.obj");
     ent->texture = LoadSprite("models/metal_bare_0002_02_preview",1024,1024);
    vec3d_cpy(ent->body.position,position);
	
    cube_set(ent->body.bounds,-ent->objModel->size.x/2,-ent->objModel->size.y/2,-ent->objModel->size.z/2,ent->objModel->size.x,
		ent->objModel->size.y,
	ent->objModel->size.z);
		
    sprintf(ent->name,"%s",name);
    mgl_callback_set(&ent->body.touch,touch_callback,ent);
    return ent;
}

Entity *newDemoBrass(Vec3D position,const char *name)
{
    Entity * ent;
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
    //ent->objModel = obj_load("models/techbrass.obj");
     //ent->texture = LoadSprite("models/brass01.png",1024,1024);
	 ent->objModel = obj_load("models/chair.obj");
    ent->texture = LoadSprite("models/outUVcarp.png",1024,1024);
	 ent->type = ITEM_BRASS;
    vec3d_cpy(ent->body.position,position);
	
    cube_set(ent->body.bounds,-ent->objModel->size.x/2,-ent->objModel->size.y/2,-ent->objModel->size.z/2,ent->objModel->size.x,
		ent->objModel->size.y,
	ent->objModel->size.z);
		
    sprintf(ent->name,"%s",name);
    mgl_callback_set(&ent->body.touch,touch_callback,ent);
    return ent;
}

Entity *newPlayer(Vec3D position,const char *name)
{
    Entity * ent;
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
    ent->objModel = NULL;
     ent->texture = NULL;
    vec3d_cpy(ent->body.position,position);
	vec3d_cpy(ent->position,position);
	
    cube_set(ent->body.bounds,-0.5f,-0.5f,-0.5f,1,1,1,);
		
    sprintf(ent->name,"%s",name);
    mgl_callback_set(&ent->body.touch,touch_callback,ent);
    return ent;
}

int main(int argc, char *argv[])
{
	int inventory_open = 0;
    int i;
    float r = 0;
    Space *space;
	int current_Time;
	int last_Time;
	float delta;
	float speed = 10;
    Entity *cube1,*cube2;
	Entity *floor1, *floor2, *floor3, *floor4;
	Entity *wall1, *wall2, *wall3, *wall4;
	Entity *techwall1, *techwall2, *techwall3, *techwall4, *techwall5, *techwall6, *techwall7, *techwall8;
	Entity *techdoor1;
	Entity *wallCenter1, *wallCenter2;
	Entity *demoTable1;
	Entity *techgun1;
	Entity *techknife1;
	Entity *techbrass1;
	Entity *box1;
    char bGameLoopRunning = 1;
    Vec3D cameraPosition = {0,-10,0.3};
    Vec3D cameraRotation = {90,0,0};
    SDL_Event e;
    //Obj *bgobj;
    Sprite *bgtext;
	int iResolution;
	int iGlobalTime;
    
    init_logger("gametest3d.log");
    if (graphics3d_init(1024,768,1,"gametest3d",33) != 0)
    {
        return -1;
    }
    model_init();
    obj_init();
    entity_init(255);
	//glUseProgram(graphics3d_get_shader_program());
	iResolution = glGetUniformLocation(graphics3d_get_shader_program(), "iResolution");
    iGlobalTime = glGetUniformLocation(graphics3d_get_shader_program(), "iGlobalTime");
    //bgobj = obj_load("models/mountainvillage.obj");
    //bgtext = LoadSprite("models/mountain_text.png",1024,1024);
    hptexture = LoadSprite("models/health.png",256,102);
	hp[0] = LoadSprite("models/hp1.png",256,102);
	hp[1] = LoadSprite("models/hp2.png",256,102);
	hp[2] = LoadSprite("models/hp3.png",256,102);
	item_Sprites[ITEM_BRASS] = LoadSprite("models/brass.png",800,600);
	item_Sprites[ITEM_PISTOL] = LoadSprite("models/pistol.png",800,600);
	item_Sprites[ITEM_PAPERS] = LoadSprite("models/papers.png",800,600);
	inventory = LoadSprite("models/inventory.png",800,800);
    cube1 = newCube(vec3d(10,-1.2,.5),"Cubert");  //(vec3d(0,-1.2,0)
    cube2 = newCube(vec3d(0,0,2),"Hobbes");
	floor1 = newFloor(vec3d(8,0,-0.6),"TheFloor 1");  //vec3d(-2.26,-2.26,0)
	floor2 = newFloor(vec3d(0,0,-0.6),"TheFloor 2");
	floor3 = newFloor(vec3d(0,8,-0.6),"TheFloor 3");
	floor4 = newFloor(vec3d(8,8,-0.6),"TheFloor 4");
	player = newPlayer(vec3d(0,-10,0.3),"Player");
	techwall1 = newDemoWall(vec3d(10,0,0),"Wall 1");
	techwall2 = newDemoWall(vec3d(0,0,0),"Wall 2"); //(8,0,0)
	techwall3 = newDemoWall(vec3d(0,0,0),"Wall 3"); //(0,4,0)
	techwall4 = newDemoWall(vec3d(0,0,0),"Wall 4"); //(4,4,0)
	techwall5 = newDemoWall(vec3d(0,0,0),"Wall 5"); //(4,0,0)
	techwall6 = newDemoWall(vec3d(0,0,0),"Wall 6"); 
	techdoor1 = newDemoDoor(vec3d(0,0,0),"Door 1"); 
	techgun1 = newDemoGun(vec3d(0,0,0),"Gun 1"); 
	techknife1 = newDemoKnife(vec3d(0,0,0),"Knife 1"); 
	techbrass1 = newCube(vec3d(6,0,0),"Brass 1"); 
	wallCenter1 = newDemoWallCenter(vec3d(0,0,0),"Wall Center1");
	wallCenter2 = newDemoWallCenter(vec3d(0,0,0),"Wall Center2"); //(0,2.45,0)
	demoTable1 = newDemoTable(vec3d(0,0,-0.35),"Demo Table");

	techwall3->rotation =vec3d(0,0,0); //(0,0,90)
	techwall4->rotation =vec3d(0,0,0); //(0,0,90)
	techwall5->rotation =vec3d(0,0,0); //(0,0,90)
	techwall6->rotation =vec3d(0,0,0); //(0,0,90)

	/*wall1 = newWall(vec3d(1.5,-1.5,1.5),"Wall 1");
	wall2 = newWall(vec3d(0,0,.5),"Wall 2");
	wall2->rotation =vec3d(0,0,90);
	wall3 = newWall(vec3d(-1.5,-1.5,1.5),"Wall 3");
	//wall3->rotation =vec3d(0,0,90);
	//wall4 = newWall(vec3d(0,0,0),"Wall 4",vec3d(-2.26,-2.26,0),vec3d(4.52,4.52,1));*/
	//cube1->rotation = vec3d(0,0,0);
	//cube2->rotation = vec3d(0,0,0);
	//box1 = newBox(vec3d(0,0,3),"Box 1");
	
    
    cube2->body.velocity.z = 0.1;
	cube1->body.velocity.x = -0.1;
	//wall1->body.velocity.z = -0.1;
	//wall2->body.velocity.z = -0.1;
	//wall3->body.velocity.z = -0.1;
    
    space = space_new();
    space_set_steps(space,100);
    
    space_add_body(space,&floor1->body);
	space_add_body(space,&floor2->body);
	space_add_body(space,&floor3->body);
	space_add_body(space,&floor4->body);
	space_add_body(space,&cube1->body);
    //space_add_body(space,&cube2->body);
	space_add_body(space,&techwall1->body);
	space_add_body(space,&techwall2->body);
	space_add_body(space,&techwall3->body);
	space_add_body(space,&techwall4->body);
	space_add_body(space,&techwall5->body);
	space_add_body(space,&techwall6->body);
	space_add_body(space,&demoTable1->body);
	space_add_body(space,&wallCenter1->body);
	space_add_body(space,&player->body);
	//space_add_body(space,&wall1->body);
	space_add_body(space,&techgun1->body);
	space_add_body(space,&techknife1->body);
	space_add_body(space,&techknife1->body);
	player->body.position = cameraPosition;
	player->rotation = cameraRotation;
	for(i=0;i<4;i++)
	{
		items[i]=0;
	}

	current_Time = SDL_GetTicks();
    while (bGameLoopRunning)
    {

		last_Time = current_Time;
		current_Time = SDL_GetTicks();
		delta = (current_Time - last_Time) / 1000.0f;
		cameraPosition = player->body.position;
		cameraRotation = player->rotation;
		
        for (i = 0; i < 100;i++)
        {
            space_do_step(space);
        }
		player->body.velocity.y =0;
		player->body.velocity.x =0;
        while ( SDL_PollEvent(&e) ) 
        {
            if (e.type == SDL_QUIT)
            {
                bGameLoopRunning = 0;
            }
            else if (e.type == SDL_KEYDOWN)
            {
				if(e.key.keysym.sym == SDLK_b)
				{
					bbOn = !bbOn;
				}else if(e.key.keysym.sym == SDLK_e)
				{
					inventory_open =!inventory_open;
					
				}else if (e.key.keysym.sym == SDLK_ESCAPE)
                {
                    bGameLoopRunning = 0;
                }
                else if (e.key.keysym.sym == SDLK_SPACE)
                {
                    cameraPosition.z++;
                }
                else if (e.key.keysym.sym == SDLK_z)
                {
                    cameraPosition.z--;
                }
                else if (e.key.keysym.sym == SDLK_w)
                {
					player->body.velocity = vec3d(-sin(player->rotation.z * DEGTORAD)*speed*delta,cos(player->rotation.z * DEGTORAD)*speed*delta,0);
					
                }
                else if (e.key.keysym.sym == SDLK_s)
                {
                    player->body.velocity = vec3d(sin(player->rotation.z * DEGTORAD)*speed*delta,-cos(player->rotation.z * DEGTORAD)*speed*delta,0);
					
                }
                else if (e.key.keysym.sym == SDLK_d)
                {
					player->body.velocity = vec3d(cos(player->rotation.z * DEGTORAD)*speed*delta,sin(player->rotation.z * DEGTORAD)*speed*delta,0);
                    //vec3d_add(cameraPosition,cameraPosition,vec3d(cos(cameraRotation.z * DEGTORAD),sin(cameraRotation.z * DEGTORAD),0));
					
                }
                else if (e.key.keysym.sym == SDLK_a)
                {
					player->body.velocity = vec3d(-cos(player->rotation.z * DEGTORAD)*speed*delta,-sin(player->rotation.z * DEGTORAD)*speed*delta,0);
                    //vec3d_add(cameraPosition,cameraPosition,vec3d(-cos(cameraRotation.z * DEGTORAD),-sin(cameraRotation.z * DEGTORAD),0));
					
                }
                else if (e.key.keysym.sym == SDLK_LEFT)
                {
                    //cameraRotation.z += 1;
					player->rotation.z +=1;
					
                }
                else if (e.key.keysym.sym == SDLK_RIGHT)
                {
                    //cameraRotation.z -= 1;
					player->rotation.z -= 1;
                }
                else if (e.key.keysym.sym == SDLK_UP)
                {
                    //cameraRotation.x += 1;
					player->rotation.x += 1;
                }
                else if (e.key.keysym.sym == SDLK_DOWN)
                {
                    //cameraRotation.x -= 1;
					player->rotation.x -= 1;
				}else if(e.key.keysym.sym == SDLK_t)
					health -= 33;
            }
			else if (e.type == SDL_MOUSEMOTION)
			{
				if(e.motion.y < 192)
				{
					//cameraRotation.x += 1;
					player->rotation.x +=1;
				}
				else if(e.motion.y > 496)
				{
					//cameraRotation.x -= 1;
					player->rotation.x -=1;
				}
				if(e.motion.x <256)
				{
					//cameraRotation.z += 1;
					player->rotation.z +=1;
				}
				else if(e.motion.x > 768)
				{
					//cameraRotation.z -= 1;
					player->rotation.z -=1;
				}

			}
			else if(e.type == SDL_MOUSEBUTTONDOWN)
			{
				if(e.button.button == SDL_BUTTON_LEFT)
				{
					vec3d_add(
                        cameraPosition,
                        cameraPosition,
                        vec3d(
                            -sin(cameraRotation.z * DEGTORAD),
                            cos(cameraRotation.z * DEGTORAD),
                            0
                        ));
				}
			}
        }
		

		

		
		

        graphics3d_frame_begin();
		
        glUniform3f(iResolution, 1024.0f, 768.0f, 100.0f);
		glUniform1f(iGlobalTime, SDL_GetTicks()/1000.0f);
        glPushMatrix();
		
        set_camera(cameraPosition,cameraRotation);
		
		
		entity_draw_all();
		 unset_camera(cameraPosition,cameraRotation);
		
        
        if (r > 360)r -= 360;
        glPopMatrix();
		drawHealthText(vec3d(0,0.1,0.1));
		drawHealthBar(vec3d(0,0.2,0.1));
		if(inventory_open)
			draw_player_inventory(vec3d(0,0,0));
		vec3d_cpy(player->position,player->body.position);
		glPopMatrix();
        /* drawing code above here! */
        graphics3d_next_frame();
    } 
    return 0;
}

void set_camera(Vec3D position, Vec3D rotation)
{
    glRotatef(-rotation.x, 1.0f, 0.0f, 0.0f);
    glRotatef(-rotation.y, 0.0f, 1.0f, 0.0f);
    glRotatef(-rotation.z, 0.0f, 0.0f, 1.0f);
    glTranslatef(-position.x,
                 -position.y,
                 -position.z);
}
void unset_camera(Vec3D position, Vec3D rotation)
{
	glTranslatef(position.x,
                 position.y,
                 position.z);

	 glRotatef(rotation.z, 0.0f, 0.0f, 1.0f);
	  glRotatef(rotation.y, 0.0f, 1.0f, 0.0f);
    glRotatef(rotation.x, 1.0f, 0.0f, 0.0f);
   
   
    
}
/*eol@eof*/