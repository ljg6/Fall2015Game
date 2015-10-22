#include <stdlib.h>
#include "entity.h"
#include "simple_logger.h"

static Entity *__entity_list = NULL;
static int __entity_max = 0;
static int __entity_initialized = 0;

static void entity_deinitialize();

void entity_init(int maxEntity)
{
    if (__entity_initialized)
    {
        slog("already initialized");
        return;
    }
    __entity_list = (Entity *)malloc(sizeof(Entity)*maxEntity);
    memset(__entity_list,0,sizeof(Entity)*maxEntity);
    __entity_max = maxEntity;
    __entity_initialized = 1;
    slog("initialized %i entities",maxEntity);
    atexit(entity_deinitialize);
}

static void entity_deinitialize()
{
    int i;
    for (i = 0;i < __entity_max;i++)
    {
        if (__entity_list[i].inuse)
        {
            entity_free(&__entity_list[i]);
        }
    }
    free(__entity_list);
    __entity_max = 0;
    __entity_initialized = 0;
}

void entity_free(Entity *ent)
{
    if (!ent)
    {
        slog("passed a null entity");
        return;
    }
    ent[0].inuse = 0;
    obj_free(ent->objModel);
    FreeSprite(ent->texture);
}

Entity *entity_new()
{
    int i;
    for (i = 0; i < __entity_max;i++)
    {
        if (!__entity_list[i].inuse)
        {
            memset(&__entity_list[i],0,sizeof(Entity));
            __entity_list[i].inuse = 1;
            vec3d_set(__entity_list[i].scale,1,1,1);
            vec4d_set(__entity_list[i].color,1,1,1,1);
            return &__entity_list[i];
        }
    }
    return NULL;
}

void entity_draw_all()
{
    int i;
    for (i = 0;i < __entity_max;i++)
    {
        if (__entity_list[i].inuse)
        {
            entity_draw(&__entity_list[i]);
        }
    }
}

void entity_draw(Entity *ent)
{
	Vec3D box[8];
    if (!ent)
    {
        return;
    }

	//making a bounding box cube.
	box[0].x=ent->body.bounds.x;
	box[0].y=ent->body.bounds.y-ent->body.bounds.h;
	box[0].z=ent->body.bounds.z+ent->body.bounds.d;

	box[1].x=ent->body.bounds.x+ent->body.bounds.w;
	box[1].y=ent->body.bounds.y-ent->body.bounds.h;
	box[1].z=ent->body.bounds.z+ent->body.bounds.d;
	
	box[2].x=ent->body.bounds.x;
	box[2].y=ent->body.bounds.y;
	box[2].z=ent->body.bounds.z+ent->body.bounds.d;

	box[3].x=ent->body.bounds.x+ent->body.bounds.w;
	box[3].y=ent->body.bounds.y;
	box[3].z=ent->body.bounds.z+ent->body.bounds.d;
	
	box[4].x=ent->body.bounds.x;
	box[4].y=ent->body.bounds.y;
	box[4].z=ent->body.bounds.z;

	box[5].x=ent->body.bounds.x+ent->body.bounds.w;
	box[5].y=ent->body.bounds.y;
	box[5].z=ent->body.bounds.z;
	
	box[6].x=ent->body.bounds.x;
	box[6].y=ent->body.bounds.y-ent->body.bounds.h;
	box[6].z=ent->body.bounds.z;

	box[7].x=ent->body.bounds.x+ent->body.bounds.w;
	box[7].y=ent->body.bounds.y-ent->body.bounds.h;
	box[7].z=ent->body.bounds.z;

    obj_draw(
        ent->objModel,
        ent->body.position,
        ent->rotation,
        ent->scale,
        ent->color,
        ent->texture
    );
}

int entity_is_entity(void *data)
{
    if (!data)return 0;
    if (!__entity_initialized)return 0;
    if ((Entity *)data < __entity_list)return 0;
    if ((Entity *)data >= (__entity_list + __entity_max))return 0;
    return 1;
}










/*eol@eof*/
