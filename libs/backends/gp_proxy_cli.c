//SPDX-License-Identifier: LGPL-2.0-or-later
/*

   Copyright (c) 2019-2020 Cyril Hrubis <metan@ucw.cz>

 */

#include <string.h>
#include <errno.h>
#include <core/gp_debug.h>
#include <backends/gp_proxy_shm.h>
#include <backends/gp_proxy_proto.h>
#include <backends/gp_proxy_cli.h>

static int set_name(struct gp_proxy_cli *app, void *name, size_t size)
{
	char *ptr;

	if (app->name) {
		GP_DEBUG(1, "Name already set!");
		return 1;
	}

	ptr = malloc(size + 1);
	if (!ptr)
		return 1;

	memcpy(ptr, name, size);
	ptr[size] = 0;

	app->name = ptr;

	GP_DEBUG(0, "App name '%s'", app->name);
	return 0;
}

void gp_proxy_cli_rem(struct gp_proxy_cli **root, struct gp_proxy_cli *self)
{
	GP_DEBUG(1, "Freeing client (%p) fd %i", self, self->fd);

	if (self->next)
		self->next->prev = self->prev;

	if (self->prev)
		self->prev->next = self->next;

	if (*root == self)
		*root = self->next;

	free(self);
}

static int parse(struct gp_proxy_cli *self, struct gp_proxy_cli_ops *ops)
{
	union gp_proxy_msg *msg;
	int ret;

	while ((ret = gp_proxy_next(&self->buf, &msg)) == 1) {
		switch (msg->type) {
		case GP_PROXY_NAME:
			if (set_name(self, msg->payload, msg->size - 8))
				return 1;
		break;
		case GP_PROXY_EXIT:
			GP_DEBUG(1, "Client (%p) fd %i requests exit", self, self->fd);
			return 1;
		break;
		case GP_PROXY_UPDATE:
			if (!ops->update)
				return 0;

			ops->update(self, msg->rect.rect.x, msg->rect.rect.y,
			                  msg->rect.rect.w, msg->rect.rect.h);
		break;
		default:
			GP_DEBUG(1, "Client (%p) fd (%i) invalid request %i",
			         self, self->fd, msg->type);
			return 1;
		}
	}

	if (ret == -1)
		return 1;

	return 0;
}

int gp_proxy_cli_read(struct gp_proxy_cli *self, struct gp_proxy_cli_ops *ops)
{
	ssize_t ret;

	ret = gp_proxy_buf_recv(self->fd, &self->buf);

	if (ret > 0) {
		if (parse(self, ops))
			return 1;
	}

	if (ret == 0) {
		fprintf(stderr, "Connection closed\n");
		return 1;
	}

	if (ret < 0 && errno != EAGAIN) {
		fprintf(stderr, "Error in connection: %s\n", strerror(errno));
		return 1;
	}

	return 0;
}

struct gp_proxy_cli *gp_proxy_cli_add(struct gp_proxy_cli **root, int cli_fd)
{
	struct gp_proxy_cli *cli = malloc(sizeof(*cli));

	GP_DEBUG(1, "Allocating client (%p) fd %i", cli, cli_fd);

	if (!cli)
		return NULL;

	cli->fd = cli_fd;
	cli->next = *root;
	cli->prev = NULL;
	cli->name = NULL;

	gp_proxy_buf_init(&cli->buf);

	if (*root)
		(*root)->prev = cli;

	*root = cli;

	return cli;
}