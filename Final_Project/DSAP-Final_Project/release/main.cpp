#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <vector>
#include <map>

#include "util.hpp"
#include "tetris.hpp"

using namespace std;

static unsigned int score = 0;
static unsigned int used_cube_num = 0;
static unsigned int cubes_num = 50;
static bool game_over = false;
static vector<vector<Position> > Ztable;
static vector<vector<Position> > Ltable;
static vector<vector<Position> > Qtable;
static vector<vector<Position> > Stable;
static vector<vector<Position> > Itable;
static vector<vector<Position> > Jtable;
static vector<vector<Position> > Ttable;

void initTables(); // 用來初始化方塊表
void updateScore(int elim_lines = 0, int combos = 0); // 用來更新分數
bool updateRegion(DiredCube dired_cube, Region &region, Tetris t); // 用來更新畫面
bool checkOverlap(vector<Position> positions, Region region);
int updateElims(Region &region); // 用來判斷消除方塊
Cubes initCubes(char *file=nullptr); // 產生方塊
// 取得更新方塊所需的座標點 list，因為一個方塊是由多個座標點組成
vector<Position> getUpdatePosList(DiredCube dir_cube, int y);

int main(int argc, char *argv[])
{
	int elim_lines = 0;
	int combo = 0;
    DiredCube dired_cube;
	Cubes cubes;
	Tetris t;
	// 初始化地圖
	Region region = \
		Region (
			HEIGHT, // box 長
			vector<int>(WIDTH, 0) // box 寬
		);

	initTables();

	if (argc == 2)
		cubes = initCubes(argv[1]); // e.g. ./main.exe cube_list.txt
	else
		cubes = initCubes(); // e.g. ./main.exe

	while (!cubes.empty()) { // 方塊 queue 中還有方塊還沒使用
        dired_cube = cubes.front();
		cubes.pop(); // 取得方塊並 pop 掉

		/* 取得學生在經過運算後所決定下個方塊位置，以及方塊移動與旋轉的順序 */
        queue<int> q = t.nextPos(dired_cube, region);
		DiredCube tmp_cube = dired_cube;
		int next_x = dired_cube.x;
		int next_dir = static_cast<int>(dired_cube.dir);
		
		while (!q.empty()) { // 如果還有 operation 還沒做
			switch (q.front()) {
				case CounterClockwise:
					next_dir = (next_dir+1) % DIRECTION_NUM;
					break;
				case Clockwise:
					next_dir--;
					if (next_dir < 0)
						next_dir += DIRECTION_NUM;
					break;
				case Left:
					next_x--;
					break;
				case Right:
					next_x++;
					break;
			}
			q.pop();
			tmp_cube = DiredCube {
				dired_cube.cube,
				static_cast<Direction>(next_dir),
				next_x
			};
			// 產生方塊的座標 list
			vector<Position> positions = getUpdatePosList(tmp_cube, 0);
			
			// 判斷操作過程是否會撞到牆 or 與其他方塊重疊，如果會就不做後續的 operation
			if (checkOverlap(positions, region))
				break;
			else
				dired_cube = tmp_cube;
		}
		/* 已經處理完學生傳入的 operation */


		// 如果更新失敗，代表遊戲結束
        if (!updateRegion(dired_cube, region, t))
            break;

		// 消除方塊，並看消除的行數有多少
		elim_lines = updateElims(region);
		if (elim_lines) {
			combo++; // 連續消除加分
			updateScore(elim_lines, combo); // 如果該回合有消除，就根據 combo 數以及消除行數來更新分數
		} else {
			combo = 0; // 該回合沒有消除，歸零連續消除
		}
    }
	
	game_over = true; // 當遊戲結束時設為 true，因為最後分數會加總使用方塊數量
    updateScore();
    cout << "Final score: " << score << '\n';

    return 0;
}

// 根據 table.png，將每個方塊對應到的座標 list 建立成一個 table
void initTables()
{
	Ztable = {
		vector<Position> {Position {0, 0}, Position {1, 0}, Position {1, 1}, Position {2, 1}},
		vector<Position> {Position {0, 1}, Position {0, 2}, Position {1, 0}, Position {1, 1}},
		vector<Position> {Position {0, 0}, Position {1, 0}, Position {1, 1}, Position {2, 1}},
		vector<Position> {Position {0, 1}, Position {0, 2}, Position {1, 0}, Position {1, 1}},
	};

	Ltable = {
		vector<Position> {Position {0, 0}, Position {0, 1}, Position {0, 2}, Position {1, 2}},
		vector<Position> {Position {0, 1}, Position {1, 1}, Position {2, 0}, Position {2, 1}},
		vector<Position> {Position {0, 0}, Position {1, 0}, Position {1, 1}, Position {1, 2}},
		vector<Position> {Position {0, 0}, Position {0, 1}, Position {1, 0}, Position {2, 0}},
	};

	Qtable = {
		vector<Position> {Position {0, 0}, Position {0, 1}, Position {1, 0}, Position {1, 1}},
		vector<Position> {Position {0, 0}, Position {0, 1}, Position {1, 0}, Position {1, 1}},
		vector<Position> {Position {0, 0}, Position {0, 1}, Position {1, 0}, Position {1, 1}},
		vector<Position> {Position {0, 0}, Position {0, 1}, Position {1, 0}, Position {1, 1}},
	};

	Stable = {
		vector<Position> {Position {0, 1}, Position {1, 0}, Position {1, 1}, Position {2, 0}},
		vector<Position> {Position {0, 0}, Position {0, 1}, Position {1, 1}, Position {1, 2}},
		vector<Position> {Position {0, 1}, Position {1, 0}, Position {1, 1}, Position {2, 0}},
		vector<Position> {Position {0, 0}, Position {0, 1}, Position {1, 1}, Position {1, 2}},
	};

	Itable = {
		vector<Position> {Position {0, 0}, Position {0, 1}, Position {0, 2}, Position {0, 3}},
		vector<Position> {Position {0, 0}, Position {1, 0}, Position {2, 0}, Position {3, 0}},
		vector<Position> {Position {0, 0}, Position {0, 1}, Position {0, 2}, Position {0, 3}},
		vector<Position> {Position {0, 0}, Position {1, 0}, Position {2, 0}, Position {3, 0}},
	};

	Jtable = {
		vector<Position> {Position {0, 2}, Position {1, 0}, Position {1, 1}, Position {1, 2}},
		vector<Position> {Position {0, 0}, Position {1, 0}, Position {2, 0}, Position {2, 1}},
		vector<Position> {Position {0, 0}, Position {0, 1}, Position {0, 2}, Position {1, 0}},
		vector<Position> {Position {0, 0}, Position {0, 1}, Position {1, 1}, Position {2, 1}},
	};

	Ttable = {
		vector<Position> {Position {0, 0}, Position {1, 0}, Position {1, 1}, Position {2, 0}},
		vector<Position> {Position {0, 0}, Position {0, 1}, Position {0, 2}, Position {1, 1}},
		vector<Position> {Position {0, 1}, Position {1, 0}, Position {1, 1}, Position {2, 1}},
		vector<Position> {Position {0, 1}, Position {1, 0}, Position {1, 1}, Position {1, 2}},
	};
}

Cubes initCubes(char *file)
{
	string s;
	Cubes cubes;

	// e.g. ./main.exe cube_list.txt
	// 如果有給予第二個參數，就把第二個參數所對應到的檔案內容讀出
	if (file != nullptr) {
		string strfile(file);
		string delim = ",";
		ifstream cube_file(strfile);

		/*
		內容會像是 0-2-10,2-1-15,5-0-3 的形式，意即
		0-2-10: 0 -> Icube, 2 -> West, x -> 10
		2-1-15: 2 -> Lcube, 1 -> North, x -> 15
		5-0-3: 5 -> Tcube, 0 -> East, x -> 3
		*/
		getline(cube_file, s);
		cube_file.close();

		/* parse 檔案結構並且存在變數 cubes 中 */
		auto start = 0;
		auto end = s.find(delim);
		cubes_num = 0;

		while (end != string::npos) {
			cubes.push(
				DiredCube {
					static_cast<Cube>((s.substr(start, end-start)[0] - '0') % CUBE_NUM),
					static_cast<Direction>((s.substr(start, end-start)[2] - '0') % DIRECTION_NUM),
					stoi(s.substr(start+4, end-start))
				}
			);
			cubes_num++;

			// 找下一個 ','
			start = end + delim.length();
			end = s.find(delim, start);
		}

		if (cubes_num) {
			cubes.push(
				// 最後一個 element 沒有 ','
				DiredCube {
					static_cast<Cube>((s.substr(start, end-start)[0] - '0') % CUBE_NUM),
					static_cast<Direction>((s.substr(start, end-start)[2] - '0') % DIRECTION_NUM),
					stoi(s.substr(start+4, end-start))
				}
			);
			cubes_num++;
		}
	// e.g. ./main.exe
	// 如果沒有給檔案名稱，就直接 random 產生
	} else {
		srand(time(NULL)); // 根據當前時間隨機化 seed 並產生隨機值
		for (int i = 0; i < cubes_num; i++)
			#if DEBUG
			// debug mode 時，會固定產生 "直的 I 型方塊"，並且 "x 軸為 12"
				cubes.push(DiredCube {Icube, East, 12});
			#else
				cubes.push(
					DiredCube {
						static_cast<Cube>(rand() % CUBE_NUM),
						static_cast<Direction>(rand() % DIRECTION_NUM),
						rand() % (WIDTH-4) // -3 避免橫的 I 方塊在下降時就會 collision
					});
			#endif
	}

	return cubes;
}

bool checkOverlap(vector<Position> positions, Region region)
{
	for (size_t i = 0; i < positions.size(); i++) {
		// 與其他方塊重疊
		if (region[ positions[i].second ][ positions[i].first ])
			return true;
		// 超出 box 範圍
		if (positions[i].first < 0 || positions[i].first >= WIDTH ||
			positions[i].second < 0 || positions[i].second >= HEIGHT)
		return true;
	}

	return false;
}

void updateScore(int elim_lines, int combos)
{
	// 如果遊戲結束，會根據使用方塊的數量做加分
    if (game_over) {
        score += used_cube_num * SCORE_UNIT;
        return;
    }

	// 計算分數
    int elim_score = SCORE_UNIT * floor(pow(1.6, elim_lines));
    int combo_score = elim_score * floor(pow(1.3, combos));

    score += combo_score;
}

// 由於方塊皆從 y=0 開始降落，因此此 function 以 y=0 ~ y=50 共 50 steps 更新方塊，
// 並且過程中如果一開始就撞到其他方塊 (到頂)，或是超過 box 大小 (無效座標)，就會被視為遊戲結束
// 如果下一步會與其他方塊相撞，代表下一步要停止，就更新座標被視為更新成功
bool updateRegion(DiredCube dired_cube, Region &region, Tetris t)
{
	bool collision = false; // 判斷有無碰撞
	bool first = true; // 判斷是否為第一次執行
	int y = 0; // 當前 y 軸
	vector<Position> positions = getUpdatePosList(dired_cube, y); // 取得已更新的方塊座標 list

	// 如果一開始就跟其他方塊重疊，代表已經到頂，遊戲結束
	for (size_t i = 0; i < positions.size(); i++) {
		if (region[ positions[i].second ][ positions[i].first ])
			return false;
	}
	
	// 如果還沒發生相撞，以及還沒碰到底
	while (!collision && y < HEIGHT) {
		if (first)
			first = false;
		else 
			positions = getUpdatePosList(dired_cube, y);
		
		// Show mode 會畫出當前位置，去模擬方塊下降的情況
		#if SHOW
			t.emulateDown(region, positions);
		#endif

		for (size_t i = 0; i < positions.size(); i++) {
			// 正常的 box 範圍內
			if (positions[i].first >= 0 && positions[i].first < WIDTH &&
				positions[i].second >= 0 && positions[i].second < HEIGHT) {
				// 下一步會碰到底
				if (positions[i].second+1 == HEIGHT) {
					collision = true;
					break;
				// 下一步會與方塊相撞
				} else if (region[ positions[i].second+1 ][ positions[i].first ]) {
					collision = true;
					break;
				}
			} else {
				return false; // 超出 box 範圍
			}
		}

		// 如果發生 collision
		if (collision) {
			// 更新 box
			for (size_t i = 0; i < positions.size(); i++) {
				region[ positions[i].second ][ positions[i].first ] = 1;
			}
			break;
		}
		
		y++;
	}
	used_cube_num++;

	return true;
}

vector<Position> getUpdatePosList(DiredCube dir_cube, int y)
{
	vector<Position> pos_list;

	// 根據 cube type 與 direction，將對應到的 table element 取出，並以 (x,y) 作為相對座標的 (0,0)
	// 將方塊的絕對座標加到變數 pos_list 中
	if (dir_cube.cube == Icube) {
		for (size_t i = 0; i < Itable[dir_cube.dir].size(); i++) {
			pos_list.push_back(pair<int, int>(
				dir_cube.x + Itable[dir_cube.dir][i].first,
				y + Itable[dir_cube.dir][i].second));
		}
	} else if (dir_cube.cube == Jcube) {
		for (size_t i = 0; i < Jtable[dir_cube.dir].size(); i++) {
			pos_list.push_back(pair<int, int>(
				dir_cube.x + Jtable[dir_cube.dir][i].first,
				y + Jtable[dir_cube.dir][i].second));
		}
	} else if (dir_cube.cube == Lcube) {
		for (size_t i = 0; i < Ltable[dir_cube.dir].size(); i++) {
			pos_list.push_back(pair<int, int>(
				dir_cube.x + Ltable[dir_cube.dir][i].first,
				y + Ltable[dir_cube.dir][i].second));
		}
	} else if (dir_cube.cube == Qcube) {
		for (size_t i = 0; i < Qtable[dir_cube.dir].size(); i++) {
			pos_list.push_back(pair<int, int>(
				dir_cube.x + Qtable[dir_cube.dir][i].first,
				y + Qtable[dir_cube.dir][i].second));
		}
	} else if (dir_cube.cube == Scube) {
		for (size_t i = 0; i < Stable[dir_cube.dir].size(); i++) {
			pos_list.push_back(pair<int, int>(
				dir_cube.x + Stable[dir_cube.dir][i].first,
				y + Stable[dir_cube.dir][i].second));
		}
	} else if (dir_cube.cube == Tcube) {
		for (size_t i = 0; i < Ttable[dir_cube.dir].size(); i++) {
			pos_list.push_back(pair<int, int>(
				dir_cube.x + Ttable[dir_cube.dir][i].first,
				y + Ttable[dir_cube.dir][i].second));
		}
	} else if (dir_cube.cube == Zcube) {
		for (size_t i = 0; i < Ztable[dir_cube.dir].size(); i++) {
			pos_list.push_back(pair<int, int>(
				dir_cube.x + Ztable[dir_cube.dir][i].first,
				y + Ztable[dir_cube.dir][i].second));
		}
	}

	return pos_list;
}

int updateElims(Region &region)
{
	int sum, i, lines = 0;

	for (i = 0; i < HEIGHT; i++) {
		sum = 0;
		
		// 計算此行有幾個方塊
		for (int j = 0; j < WIDTH; j++) {
			if (region[i][j])
				sum++;
		}

		// 如果 sum == WIDTH，代表該行已經滿了，可以消除
		if (sum == WIDTH) {
			lines++;
			region.erase(region.begin() + i); // 消除該行方塊
			region.insert(region.begin(), vector<int>(WIDTH, 0)); // 新增一行空白方塊
		}
	}

	return lines;
}