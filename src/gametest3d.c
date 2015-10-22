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

void set_camera(Vec3D position, Vec3D rotation);

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
	slog("wall size %f,%f,%f",ent->objModel->size.x,ent->objModel->size.y,ent->objModel->size.z);
    cube_set(ent->body.bounds,-ent->objModel->size.x/2,-ent->objModel->size.y/2,-ent->objModel->size.z/2,ent->objModel->size.x,
		ent->objModel->size.y,
	ent->objModel->size.z);
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
    ent->objModel = obj_load("models/floor.obj");
    ent->texture = LoadSprite("models/floorcarpet.png",1024,1024);
    vec3d_cpy(ent->body.position,position);
	
    cube_set(ent->body.bounds,-ent->objModel->size.x/2,-ent->objModel->size.y/2,-ent->objModel->size.z/2,ent->objModel->size.x,
		ent->objModel->size.y,
	ent->objModel->size.z);
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

int main(int argc, char *argv[])
{
    int i;
    float r = 0;
    Space *space;
    Entity *cube1,*cube2;
	Entity *floor;
	Entity *wall1, *wall2, *wall3, *wall4;
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
    
    floor = newFloor(vec3d(0,0,0),"TheFloor");  //vec3d(-2.26,-2.26,0)
	wall1 = newWall(vec3d(1.5,-1.5,1.5),"Wall 1");
	wall2 = newWall(vec3d(0,0,.5),"Wall 2");
	wall2->rotation =vec3d(0,0,90);
	wall3 = newWall(vec3d(-1.5,-1.5,1.5),"Wall 3");
	//wall3->rotation =vec3d(0,0,90);
	//wall4 = newWall(vec3d(0,0,0),"Wall 4",vec3d(-2.26,-2.26,0),vec3d(4.52,4.52,1));
	cube1 = newCube(vec3d(10,-1.2,.5),"Cubert");  //(vec3d(0,-1.2,0)
    cube2 = newCube(vec3d(0,-1.2,5.27),"Hobbes");
	//cube1->rotation = vec3d(0,0,0);
	//cube2->rotation = vec3d(0,0,0);
	//box1 = newBox(vec3d(0,0,3),"Box 1");
	
    
    cube2->body.velocity.x = 0.1;
	cube1->body.velocity.x = -0.1;
	wall1->body.velocity.z = -0.1;
	wall2->body.velocity.z = -0.1;
	wall3->body.velocity.z = -0.1;
    
    space = space_new();
    space_set_steps(space,100);
    
    space_add_body(space,&floor->body);
	space_add_body(space,&cube1->body);
    space_add_body(space,&cube2->body);
	space_add_body(space,&wall1->body);
    while (bGameLoopRunning)
    {
        for (i = 0; i < 100;i++)
        {
            space_do_step(space);
        }
        while ( SDL_PollEvent(&e) ) 
        {
            if (e.type == SDL_QUIT)
            {
                bGameLoopRunning = 0;
            }
            else if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_ESCAPE)
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
                    vec3d_add(
                        cameraPosition,
                        cameraPosition,
                        vec3d(
                            -sin(cameraRotation.z * DEGTORAD),
                            cos(cameraRotation.z * DEGTORAD),
                            0
                        ));
                }
                else if (e.key.keysym.sym == SDLK_s)
                {
                    vec3d_add(
                        cameraPosition,
                        cameraPosition,
                        vec3d(
                            sin(cameraRotation.z * DEGTORAD),
                            -cos(cameraRotation.z * DEGTORAD),
                            0
                        ));
                }
                else if (e.key.keysym.sym == SDLK_d)
                {
                    vec3d_add(
                        cameraPosition,
                        cameraPosition,
                        vec3d(
                            cos(cameraRotation.z * DEGTORAD),
                            sin(cameraRotation.z * DEGTORAD),
                            0
                        ));
                }
                else if (e.key.keysym.sym == SDLK_a)
                {
                    vec3d_add(
                        cameraPosition,
                        cameraPosition,
                        vec3d(
                            -cos(cameraRotation.z * DEGTORAD),
                            -sin(cameraRotation.z * DEGTORAD),
                            0
                        ));
                }
                else if (e.key.keysym.sym == SDLK_LEFT)
                {
                    cameraRotation.z += 1;
                }
                else if (e.key.keysym.sym == SDLK_RIGHT)
                {
                    cameraRotation.z -= 1;
                }
                else if (e.key.keysym.sym == SDLK_UP)
                {
                    cameraRotation.x += 1;
                }
                else if (e.key.keysym.sym == SDLK_DOWN)
                {
                    cameraRotation.x -= 1;
                }
            }
        }

        graphics3d_frame_begin();
        glUniform3f(iResolution, 1024.0f, 768.0f, 100.0f);
		glUniform1f(iGlobalTime, SDL_GetTicks()/1000.0f);
        glPushMatrix();
        set_camera(
            cameraPosition,
            cameraRotation);
        
        entity_draw_all();  

        
        if (r > 360)r -= 360;
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

/*eol@eof*/