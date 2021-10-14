1.游戏初始化 initial_game()
2.地图生成 initial_map()
3.游戏规则 game_rule()
*4.加载图片 load()






ExMessage msg;
getmessage(&msg, EM_MOUSE);
if (msg.lbutton) {
	int y = msg.y / IMGSIZE + 1;
	int x = msg.x / IMGSIZE + 1;

	if (map【y】【x】 >= 19 && map【y】【x】 <= 28) {
		map【y】【x】 -= 20;
	}
	return map【y】【x】;
}
else if (msg.rbutton) {
	int y = msg.y / IMGSIZE + 1;
	int x = msg.x / IMGSIZE + 1;
	if (map【y】【x】 >= 19 && map【y】【x】 <= 28) {
		map【y】【x】 += 20;
	}
	else if (map【y】【x】 >= 40) {
		map【y】【x】 -= 20;
	}
}