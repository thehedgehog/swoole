#include "swoole.h"
#include "Server.h"

int swFactory_create(swFactory *factory)
{
	factory->running = 1;
	factory->dispatch = swFactory_dispatch;
	factory->finish = swFactory_finish;
	factory->start = swFactory_start;
	factory->shutdown = swFactory_shutdown;
	factory->end = swFactory_end;
	return SW_OK;
}
int swFactory_start(swFactory *factory)
{
	return SW_OK;
}

int swFactory_shutdown(swFactory *factory)
{
	return SW_OK;
}

int swFactory_dispatch(swFactory *factory, swEventData *req)
{
	swTrace("New Task:%s\n", req->data);
	factory->last_from_id = req->info.from_id;
	return factory->onTask(factory, req);
}

int swFactory_end(swFactory *factory, swEvent *cev)
{
	swServer *serv = factory->ptr;
	return swServer_close(serv, cev);
}

int swFactory_finish(swFactory *factory, swSendData *resp)
{
	return factory->onFinish(factory, resp);
}

int swFactory_check_callback(swFactory *factory)
{
	if (factory->onTask == NULL)
	{
		return SW_ERR;
	}
	if (factory->onFinish == NULL)
	{
		return SW_ERR;
	}
	return SW_OK;
}
