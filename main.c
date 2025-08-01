#include "include/header.h"

/*int main(void) {
  t_cub cub3d;

  init_cub(&cub3d);

  cub3d.player->dir = vec_rotate(cub3d.player->dir, 1.0);
  cub3d.player->plane = vec_rotate(cub3d.player->plane, 1.0);

  mlx_loop_hook(cub3d.mlx, &main_loop, &cub3d);
  mlx_hook(cub3d.win, KEYPRESS, KEYPRESS_MASK, &handle_keypress, &cub3d);
  mlx_hook(cub3d.win, DESTROY_NOTIFY, IGNORE_MASK, &game_exit, &cub3d);

  mlx_loop(cub3d.mlx);

  return (0);
}*/

#include <fcntl.h> 

#define ASD 42

int main(void)
{
    int fd = open("Makefile", O_RDONLY);
    if (fd == -1)
    {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    char *linha;
    printf("%s", (char *)get_next_line(fd));
    while ((linha = get_next_line(fd)) != NULL)
    {
        printf("%s", linha);
        free(linha);       
    }

    close(fd);
    return 0;
}
