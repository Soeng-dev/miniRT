// ch 2
 //	ex.mlx = mlx_init();
 //	ex.win = mlx_new_window(ex.mlx, 300, 300, "ex");
 //	img.img = mlx_new_image(ex.mlx, 256, 256);
 //	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.linelen, &img.endian);
 //	for (int x = imgwidth - 1; x >= 0; --x)
 //	{
 //		for (int y = 0; y < imgheight; ++y)
 //		{
 //			int r = (int)floor(((double)x / (imgwidth - 1)) * (double)255 + 0.5);
 //			int g = (int)floor(((double)y / (imgheight - 1)) * (double)255 + 0.5);
 //			int b = (int)floor(0.25 * (double)255 + 0.5);
 //			int color = 0;
 //			color = (r << 16) | (g << 8) | (b);
 //			pixput(&img, x, y, color);
 //		}
 //	}
