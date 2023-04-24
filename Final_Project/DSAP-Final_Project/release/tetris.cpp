#include <iostream>
#include <unistd.h>
#include <cmath>
#include <math.h>

#include "tetris.hpp"

using namespace std;
/* implement this function */
/*
而整個 queue 代表你在此回合的所有行為，
此刻你移動，就會將 Left or Right 存進 queue 中；
此刻你移動，就會將 Clockwise or CounterClockwise 存進 queue 中；
舉例來說：
[None, Clockwise, Left, Left]，
代表： 不做事 -> 順時鐘轉 -> 左移 -> 左移

cube有Cube cube; Direction dir; int x; 三個參數，
region 為二維陣列[][]
*/

/*
queue<int> Tetris::nextPos(DiredCube cube, Region region)
{
    queue<int> q;
    vector<int> skipV(region[0].size(),0);
    vector<float> bestPos = {0,0};
    int bestDir = 0;
    int flag = 0;

    int height = 0;
    int width = 0;
    int moveX = 0;
    int rotate = 0;

    if(cube.cube == 0)
    {  //Icube
        for(int i = 0; i < region[0].size(); i++)
        {
            skipV[i] = 0;
        }
        vector<vector<int>> E(4,vector<int>(1,1));
        vector<vector<int>> N(1,vector<int>(4,1));
        for(int i = 0; i < region.size() - E.size() + 1; i++) //map height
        {
            float i2 = i;
            for(float j = 0; j < region[0].size() - E[0].size() + 1; j++) //map width
            {
                if(skipV[j] == 1) // 表示那一行已經不可能再放入方塊
                {
                    continue;
                }

                int ii = 0;
                for(int k = i; k < E.size() + i; k++)
                {
                    //int ii = 0;
                    int jj = 0;
                    for(float l = j; l < E[0].size() + j; l++)
                    {
                        //int jj = 0;
                        if(region[k][l] == 1 && E[ii][jj] == 1) //當地圖與方塊撞到則跳出方塊的長寬比較
                        {
                            flag = 1;
                            skipV[l] = 1;
                            break;
                        } 
                        jj++;                    
                    }
                    
                    if(flag == 1) // 當地圖與方塊撞到則跳出方塊的長寬比較
                    {
                        break;
                    }
                    ii++;  
                }
                if(flag == 0) // 當地圖沒有與方塊撞到，紀錄該位置
                {
                    if(ceil((i2 + i2 + 3) / 2) > bestPos[1])
                    {                        
                        float yax = ceil((i2 + i2 + 3) / 2);

                        bestPos = {j,yax};
                        bestDir = 0;
                    }                        
                }
                if(flag == 1) // 當地圖與方塊撞到，不紀錄該位置，並將flag調回0
                {
                    flag = 0;
                }
            }
        }

        for(int i = 0; i < region[0].size(); i++)
        {
            skipV[i] = 0;
        }
        for(int i = 0; i < region.size() - N.size() + 1; i++)
        {
            float i2 = i;
            for(float j = 0; j < region[0].size() - N[0].size() + 1; j++)
            {
                if(skipV[j] == 1) // 表示那一行已經不可能再放入方塊
                {
                    continue;
                }

                int ii = 0;                
                for(int k = i; k < N.size() + i; k++)
                {
                    //int ii = 0;
                    int jj = 0;
                    for(float l = j; l < N[0].size() + j; l++)
                    {
                        //int jj = 0;
                        if(region[k][l] == 1 && N[ii][jj] == 1) //當地圖與方塊撞到則跳出方塊的長寬比較
                        {
                            flag = 1;
                            skipV[l] = 1;
                            break;
                        } 
                        jj++;                    
                    }
                    if(flag == 1) // 當地圖與方塊撞到則跳出方塊的長寬比較
                    {
                        break;
                    }
                    ii++;  
                }
                if(flag == 0) // 當地圖沒有與方塊撞到，紀錄該位置
                {
                    if(ceil((i2 + i2 + 0) / 2) > bestPos[1]) 
                    {
                        float yax = ceil((i2 + i2 + 0) / 2); 
                        
                        bestPos = {j,yax};
                        bestDir = 1;
                    }                        
                 }
                if(flag == 1) // 當地圖與方塊撞到，不紀錄該位置，並將flag調回0
                {
                    flag = 0;
                }
            }
        }
    }
    
    if(cube.cube == 1)
    {  //Jcube
        vector<vector<int>> E(3,vector<int>(2,1));
        E[0][0]=0;
        E[1][0]=0;
        vector<vector<int>> N(2,vector<int>(3,1));
        N[1][0]=0;
        N[1][1]=0;
        vector<vector<int>> W(3,vector<int>(2,1));
        W[1][1]=0;
        W[2][1]=0;
        vector<vector<int>> S(2,vector<int>(3,1));
        S[0][1]=0;
        S[0][2]=0;
        for(int i = 0; i < region[0].size(); i++)
        {
            skipV[i] = 0;
        }
        for(int i = 0; i < region.size() - E.size() + 1; i++)
        {
            float i2 = i;
            for(float j = 0; j < region[0].size() - E[0].size() + 1; j++)
            {
                if(skipV[j] == 1) // 表示那一行已經不可能再放入方塊
                {
                    continue;
                }
                int ii = 0;
                
                for(int k = i; k < E.size() + i; k++)
                {
                    int jj = 0;
                    for(float l = j; l < E[0].size() + j; l++)
                    {
                        
                        if(region[k][l] == 1 && E[ii][jj] == 1) //當地圖與方塊撞到則跳出方塊的長寬比較
                        {
                            flag = 1;
                            skipV[l] = 1;
                            break;
                        } 
                        jj++;                    
                    }
                    if(flag == 1) // 當地圖與方塊撞到則跳出方塊的長寬比較
                    {
                        break;
                    }
                    ii++;  
                }
                if(flag == 0) // 當地圖沒有與方塊撞到，紀錄該位置
                {
                    if((i2 + i2 + 2) / 2 > bestPos[1])
                    {
                        float yax = (i2 + i2 + 2) / 2;
                        bestPos = {j,yax};
                        bestDir = 0;
                    }                        
                 }
                else if(flag == 1) // 當地圖與方塊撞到，不紀錄該位置，並將flag調回0
                {
                    flag = 0;
                }
            }
        }
        for(int i = 0; i < region[0].size(); i++)
        {
            skipV[i] = 0;
        }
        for(int i = 0; i < region.size() - N.size() + 1; i++)
        {
            float i2 = i;
            for(float j = 0; j < region[0].size() - N[0].size() + 1; j++)
            {
                if(skipV[j] == 1) // 表示那一行已經不可能再放入方塊
                {
                    continue;
                }
                int ii = 0;
                
                for(int k = i; k < N.size() + i; k++)
                {
                    int jj = 0;
                    for(float l = j; l < N[0].size() + j; l++)
                    {
                        
                        if(region[k][l] == 1 && N[ii][jj] == 1) //當地圖與方塊撞到則跳出方塊的長寬比較
                        {
                            flag = 1;
                            skipV[l] = 1;
                            break;
                        } 
                        jj++;                    
                    }
                    if(flag == 1) // 當地圖與方塊撞到則跳出方塊的長寬比較
                    {
                        break;
                    }
                    ii++;  
                }
                if(flag == 0) // 當地圖沒有與方塊撞到，紀錄該位置
                {
                    if((i2 + i2 + 1) / 2 > bestPos[1])
                    {
                        float yax = (i2 + i2 + 1) / 2;
                        bestPos = {j,yax};
                        bestDir = 1;
                    }                        
                 }
                else if(flag == 1) // 當地圖與方塊撞到，不紀錄該位置，並將flag調回0
                {
                    flag = 0;
                }
            }
        }
        for(int i = 0; i < region[0].size(); i++)
        {
            skipV[i] = 0;
        }
        for(int i = 0; i < region.size() - W.size() + 1; i++)
        {
            float i2 = i;
            for(float j = 0; j < region[0].size() - W[0].size() + 1; j++)
            {
                if(skipV[j] == 1) // 表示那一行已經不可能再放入方塊
                {
                    continue;
                }
                int ii = 0;
                
                for(int k = i; k < W.size() + i; k++)
                {
                    int jj = 0;
                    for(float l = j; l < W[0].size() + j; l++)
                    {
                        
                        if(region[k][l] == 1 && W[ii][jj] == 1) //當地圖與方塊撞到則跳出方塊的長寬比較
                        {
                            flag = 1;
                            skipV[l] = 1;
                            break;
                        } 
                        jj++;                    
                    }
                    if(flag == 1) // 當地圖與方塊撞到則跳出方塊的長寬比較
                    {
                        break;
                    }
                    ii++;  
                }
                if(flag == 0) // 當地圖沒有與方塊撞到，紀錄該位置
                {
                    if((i2 + i2 + 2) / 2 > bestPos[1])
                    {
                        float yax = (i2 + i2 + 2) / 2;
                        bestPos = {j,yax};
                        bestDir = 2;
                    }                        
                 }
                else if(flag == 1) // 當地圖與方塊撞到，不紀錄該位置，並將flag調回0
                {
                    flag = 0;
                }
            }
        }
        for(int i = 0; i < region[0].size(); i++)
        {
            skipV[i] = 0;
        }
        for(int i = 0; i < region.size() - S.size() + 1; i++)
        {
            float i2 = i;
            for(float j = 0; j < region[0].size() - S[0].size() + 1; j++)
            {
                if(skipV[j] == 1) // 表示那一行已經不可能再放入方塊
                {
                    continue;
                }
                int ii = 0;
                
                for(int k = i; k < S.size() + i; k++)
                {
                    int jj = 0;
                    for(float l = j; l < S[0].size() + j; l++)
                    {
                        
                        if(region[k][l] == 1 && S[ii][jj] == 1) //當地圖與方塊撞到則跳出方塊的長寬比較
                        {
                            flag = 1;
                            skipV[l] = 1;
                            break;
                        } 
                        jj++;                    
                    }
                    if(flag == 1) // 當地圖與方塊撞到則跳出方塊的長寬比較
                    {
                        break;
                    }
                    ii++;  
                }
                if(flag == 0) // 當地圖沒有與方塊撞到，紀錄該位置
                {
                    if((i2 + i2 + 1) / 2 >= bestPos[1])
                    {
                        float yax = (i2 + i2 + 1) / 2;
                        bestPos = {j,yax};
                        bestDir = 3;
                    }                        
                 }
                else if(flag == 1) // 當地圖與方塊撞到，不紀錄該位置，並將flag調回0
                {
                    flag = 0;
                }
            }
        }

    }    

    if(cube.cube == 2)
    {  //Lcube
        vector<vector<int>> E(3,vector<int>(2,1));
        E[0][1]=0;
        E[1][1]=0;
        vector<vector<int>> N(2,vector<int>(3,1));
        N[0][0]=0;
        N[0][1]=0;
        vector<vector<int>> W(3,vector<int>(2,1));
        W[1][0]=0;
        W[2][0]=0;
        vector<vector<int>> S(2,vector<int>(3,1));
        S[1][1]=0;
        S[1][2]=0;
        for(int i = 0; i < region[0].size(); i++)
        {
            skipV[i] = 0;
        }
        for(int i = 0; i < region.size() - E.size() + 1; i++)
        {
            float i2 = i;
            for(float j = 0; j < region[0].size() - E[0].size() + 1; j++)
            {
                if(skipV[j] == 1) // 表示那一行已經不可能再放入方塊
                {
                    continue;
                }
                int ii = 0;
                
                for(int k = i; k < E.size() + i; k++)
                {
                    int jj = 0;
                    for(float l = j; l < E[0].size() + j; l++)
                    {
                        
                        if(region[k][l] == 1 && E[ii][jj] == 1) //當地圖與方塊撞到則跳出方塊的長寬比較
                        {
                            flag = 1;
                            skipV[l] = 1;
                            break;
                        } 
                        jj++;                    
                    }
                    if(flag == 1) // 當地圖與方塊撞到則跳出方塊的長寬比較
                    {
                        break;
                    }
                    ii++;  
                }
                if(flag == 0) // 當地圖沒有與方塊撞到，紀錄該位置
                {
                    if((i2 + i2 + 2) / 2 > bestPos[1])
                    {
                        float yax = (i2 + i2 + 2) / 2;
                        bestPos = {j,yax};
                        bestDir = 0;
                    }                        
                 }
                else if(flag == 1) // 當地圖與方塊撞到，不紀錄該位置，並將flag調回0
                {
                    flag = 0;
                }
            }
        }
        for(int i = 0; i < region[0].size(); i++)
        {
            skipV[i] = 0;
        }
        for(int i = 0; i < region.size() - N.size() + 1; i++)
        {
            float i2 = i;
            for(float j = 0; j < region[0].size() - N[0].size() + 1; j++)
            {
                if(skipV[j] == 1) // 表示那一行已經不可能再放入方塊
                {
                    continue;
                }
                int ii = 0;
                
                for(int k = i; k < N.size() + i; k++)
                {
                    int jj = 0;
                    for(float l = j; l < N[0].size() + j; l++)
                    {
                        
                        if(region[k][l] == 1 && N[ii][jj] == 1) //當地圖與方塊撞到則跳出方塊的長寬比較
                        {
                            flag = 1;
                            skipV[l] = 1;
                            break;
                        } 
                        jj++;                    
                    }
                    if(flag == 1) // 當地圖與方塊撞到則跳出方塊的長寬比較
                    {
                        break;
                    }
                    ii++;  
                }
                if(flag == 0) // 當地圖沒有與方塊撞到，紀錄該位置
                {
                    if((i2 + i2 + 1) / 2 >= bestPos[1])
                    {
                        float yax = (i2 + i2 + 1) / 2;
                        bestPos = {j,yax};
                        bestDir = 1;
                    }                        
                 }
                else if(flag == 1) // 當地圖與方塊撞到，不紀錄該位置，並將flag調回0
                {
                    flag = 0;
                }
            }
        }
        for(int i = 0; i < region[0].size(); i++)
        {
            skipV[i] = 0;
        }
        for(int i = 0; i < region.size() - W.size() + 1; i++)
        {
            float i2 = i;
            for(float j = 0; j < region[0].size() - W[0].size() + 1; j++)
            {
                if(skipV[j] == 1) // 表示那一行已經不可能再放入方塊
                {
                    continue;
                }
                int ii = 0;
                
                for(int k = i; k < W.size() + i; k++)
                {
                    int jj = 0;
                    for(float l = j; l < W[0].size() + j; l++)
                    {
                        
                        if(region[k][l] == 1 && W[ii][jj] == 1) //當地圖與方塊撞到則跳出方塊的長寬比較
                        {
                            flag = 1;
                            skipV[l] = 1;
                            break;
                        } 
                        jj++;                    
                    }
                    if(flag == 1) // 當地圖與方塊撞到則跳出方塊的長寬比較
                    {
                        break;
                    }
                    ii++;  
                }
                if(flag == 0) // 當地圖沒有與方塊撞到，紀錄該位置
                {
                    if((i2 + i2 + 2) / 2 > bestPos[1])
                    {
                        float yax = (i2 + i2 + 2) / 2;
                        bestPos = {j,yax};
                        bestDir = 2;
                    }                        
                 }
                else if(flag == 1) // 當地圖與方塊撞到，不紀錄該位置，並將flag調回0
                {
                    flag = 0;
                }
            }
        }
        for(int i = 0; i < region[0].size(); i++)
        {
            skipV[i] = 0;
        }
        for(int i = 0; i < region.size() - S.size() + 1; i++)
        {
            float i2 = i;
            for(float j = 0; j < region[0].size() - S[0].size() + 1; j++)
            {
                if(skipV[j] == 1) // 表示那一行已經不可能再放入方塊
                {
                    continue;
                }
                int ii = 0;
                
                for(int k = i; k < S.size() + i; k++)
                {
                    int jj = 0;
                    for(float l = j; l < S[0].size() + j; l++)
                    {
                        
                        if(region[k][l] == 1 && S[ii][jj] == 1) //當地圖與方塊撞到則跳出方塊的長寬比較
                        {
                            flag = 1;
                            skipV[l] = 1;
                            break;
                        } 
                        jj++;                    
                    }
                    if(flag == 1) // 當地圖與方塊撞到則跳出方塊的長寬比較
                    {
                        break;
                    }
                    ii++;  
                }
                if(flag == 0) // 當地圖沒有與方塊撞到，紀錄該位置
                {
                    if((i2 + i2 + 1) / 2 > bestPos[1])
                    {
                        float yax = (i2 + i2 + 1) / 2;
                        bestPos = {j,yax};
                        bestDir = 3;
                    }                        
                 }
                else if(flag == 1) // 當地圖與方塊撞到，不紀錄該位置，並將flag調回0
                {
                    flag = 0;
                }
            }
        }

    }

    if(cube.cube == 3)
    {   //Qcube
        vector<vector<int>> E(2,vector<int>(2,1));
        for(int i = 0; i < region.size() - E.size() + 1; i++)
        {
            float i2 = i;
            for(float j = 0; j < region[0].size() - E[0].size() + 1; j++)
            {
                if(skipV[j] == 1) // 表示那一行已經不可能再放入方塊
                {
                    continue;
                }
                int ii = 0;
                
                for(int k = i; k < E.size() + i; k++)
                {
                    int jj = 0;
                    for(float l = j; l < E[0].size() + j; l++)
                    {
                        
                        if(region[k][l] == 1 && E[ii][jj] == 1) //當地圖與方塊撞到則跳出方塊的長寬比較
                        {
                            flag = 1;
                            skipV[l] = 1;
                            break;
                        } 
                        jj++;                    
                    }
                    if(flag == 1) // 當地圖與方塊撞到則跳出方塊的長寬比較
                    {
                        break;
                    }
                    ii++;  
                }
                if(flag == 0) // 當地圖沒有與方塊撞到，紀錄該位置
                {
                    if((i2 + i2 + 3) / 2 > bestPos[1])
                    {
                        float yax = (i2 + i2 + 3) / 2;
                        bestPos = {j,yax};
                        bestDir = 0;
                    }                        
                 }
                else if(flag == 1) // 當地圖與方塊撞到，不紀錄該位置，並將flag調回0
                {
                    flag = 0;
                }
            }
        }
    }

    if(cube.cube == 4)
    {  //Scube
        vector<vector<int>> E(2,vector<int>(3,1));
        E[0][0]=0;
        E[1][2]=0;
        vector<vector<int>> N(3,vector<int>(2,1));
        N[2][0]=0;
        N[0][1]=0;
        for(int i = 0; i < region[0].size(); i++)
        {
            skipV[i] = 0;
        }
        for(int i = 0; i < region.size() - E.size() + 1; i++)
        {
            float i2 = i;
            for(float j = 0; j < region[0].size() - E[0].size() + 1; j++)
            {
                if(skipV[j] == 1) // 表示那一行已經不可能再放入方塊
                {
                    continue;
                }
                int ii = 0;
                
                for(int k = i; k < E.size() + i; k++)
                {
                    int jj = 0;
                    for(float l = j; l < E[0].size() + j; l++)
                    {
                        
                        if(region[k][l] == 1 && E[ii][jj] == 1) //當地圖與方塊撞到則跳出方塊的長寬比較
                        {
                            flag = 1;
                            skipV[l] = 1;
                            break;
                        } 
                        jj++;                    
                    }
                    if(flag == 1) // 當地圖與方塊撞到則跳出方塊的長寬比較
                    {
                        break;
                    }
                    ii++;  
                }
                if(flag == 0) // 當地圖沒有與方塊撞到，紀錄該位置
                {
                    if((i2 + i2 + 1) / 2 > bestPos[1])
                    {
                        float yax = (i2 + i2 + 1) / 2;
                        bestPos = {j,yax};
                        bestDir = 0;
                    }                        
                 }
                else if(flag == 1) // 當地圖與方塊撞到，不紀錄該位置，並將flag調回0
                {
                    flag = 0;
                }
            }
        }
        for(int i = 0; i < region[0].size(); i++)
        {
            skipV[i] = 0;
        }
        for(int i = 0; i < region.size() - N.size() + 1; i++)
        {
            float i2 = i;
            for(float j = 0; j < region[0].size() - N[0].size() + 1; j++)
            {
                if(skipV[j] == 1) // 表示那一行已經不可能再放入方塊
                {
                    continue;
                }
                int ii = 0;
                
                for(int k = i; k < N.size() + i; k++)
                {
                    int jj = 0;
                    for(float l = j; l < N[0].size() + j; l++)
                    {
                        
                        if(region[k][l] == 1 && N[ii][jj] == 1) //當地圖與方塊撞到則跳出方塊的長寬比較
                        {
                            flag = 1;
                            skipV[l] = 1;
                            break;
                        } 
                        jj++;                    
                    }
                    if(flag == 1) // 當地圖與方塊撞到則跳出方塊的長寬比較
                    {
                        break;
                    }
                    ii++;  
                }
                if(flag == 0) // 當地圖沒有與方塊撞到，紀錄該位置
                {
                    if((i2 + i2 + 2) / 2 > bestPos[1])
                    {
                        float yax = (i2 + i2 + 2) / 2;
                        bestPos = {j,yax};
                        bestDir = 1;
                    }                        
                 }
                else if(flag == 1) // 當地圖與方塊撞到，不紀錄該位置，並將flag調回0
                {
                    flag = 0;
                }
            }
        }

    }

    if(cube.cube == 5)
    {  //Tcube
        vector<vector<int>> E(2,vector<int>(3,1));
        E[1][2]=0;
        E[1][0]=0;
        vector<vector<int>> N(3,vector<int>(2,1));
        N[2][1]=0;
        N[0][1]=0;
        vector<vector<int>> W(2,vector<int>(3,1));
        W[0][0]=0;
        W[0][2]=0;
        vector<vector<int>> S(3,vector<int>(2,1));
        S[0][0]=0;
        S[2][0]=0;
        for(int i = 0; i < region[0].size(); i++)
        {
            skipV[i] = 0;
        }
        for(int i = 0; i < region.size() - E.size() + 1; i++)
        {
            float i2 = i;
            for(float j = 0; j < region[0].size() - E[0].size() + 1; j++)
            {
                if(skipV[j] == 1) // 表示那一行已經不可能再放入方塊
                {
                    continue;
                }
                int ii = 0;
                
                for(int k = i; k < E.size() + i; k++)
                {
                    int jj = 0;
                    for(float l = j; l < E[0].size() + j; l++)
                    {
                        
                        if(region[k][l] == 1 && E[ii][jj] == 1) //當地圖與方塊撞到則跳出方塊的長寬比較
                        {
                            flag = 1;
                            skipV[l] = 1;
                            break;
                        } 
                        jj++;                    
                    }
                    if(flag == 1) // 當地圖與方塊撞到則跳出方塊的長寬比較
                    {
                        break;
                    }
                    ii++;  
                }
                if(flag == 0) // 當地圖沒有與方塊撞到，紀錄該位置
                {
                    if((i2 + i2 + 1) / 2 > bestPos[1])
                    {
                        float yax = (i2 + i2 + 1) / 2;
                        bestPos = {j,yax};
                        bestDir = 0;
                    }                        
                 }
                else if(flag == 1) // 當地圖與方塊撞到，不紀錄該位置，並將flag調回0
                {
                    flag = 0;
                }
            }
        }
        for(int i = 0; i < region[0].size(); i++)
        {
            skipV[i] = 0;
        }
        for(int i = 0; i < region.size() - N.size() + 1; i++)
        {
            float i2 = i;
            for(float j = 0; j < region[0].size() - N[0].size() + 1; j++)
            {
                if(skipV[j] == 1) // 表示那一行已經不可能再放入方塊
                {
                    continue;
                }
                int ii = 0;
                
                for(int k = i; k < N.size() + i; k++)
                {
                    int jj = 0;
                    for(float l = j; l < N[0].size() + j; l++)
                    {
                        
                        if(region[k][l] == 1 && N[ii][jj] == 1) //當地圖與方塊撞到則跳出方塊的長寬比較
                        {
                            flag = 1;
                            skipV[l] = 1;
                            break;
                        } 
                        jj++;                    
                    }
                    if(flag == 1) // 當地圖與方塊撞到則跳出方塊的長寬比較
                    {
                        break;
                    }
                    ii++;  
                }
                if(flag == 0) // 當地圖沒有與方塊撞到，紀錄該位置
                {
                    if((i2 + i2 + 2) / 2 > bestPos[1])
                    {
                        float yax = (i2 + i2 + 2) / 2;
                        bestPos = {j,yax};
                        bestDir = 1;
                    }                        
                 }
                else if(flag == 1) // 當地圖與方塊撞到，不紀錄該位置，並將flag調回0
                {
                    flag = 0;
                }
            }
        }
        for(int i = 0; i < region[0].size(); i++)
        {
            skipV[i] = 0;
        }
        for(int i = 0; i < region.size() - W.size() + 1; i++)
        {
            float i2 = i;
            for(float j = 0; j < region[0].size() - W[0].size() + 1; j++)
            {
                if(skipV[j] == 1) // 表示那一行已經不可能再放入方塊
                {
                    continue;
                }
                int ii = 0;
                
                for(int k = i; k < W.size() + i; k++)
                {
                    int jj = 0;
                    for(float l = j; l < W[0].size() + j; l++)
                    {
                        
                        if(region[k][l] == 1 && W[ii][jj] == 1) //當地圖與方塊撞到則跳出方塊的長寬比較
                        {
                            flag = 1;
                            skipV[l] = 1;
                            break;
                        } 
                        jj++;                    
                    }
                    if(flag == 1) // 當地圖與方塊撞到則跳出方塊的長寬比較
                    {
                        break;
                    }
                    ii++;  
                }
                if(flag == 0) // 當地圖沒有與方塊撞到，紀錄該位置
                {
                    if((i2 + i2 + 1) / 2 >= bestPos[1])
                    {
                        float yax = (i2 + i2 + 1) / 2;
                        bestPos = {j,yax};
                        bestDir = 2;
                    }                        
                 }
                else if(flag == 1) // 當地圖與方塊撞到，不紀錄該位置，並將flag調回0
                {
                    flag = 0;
                }
            }
        }
        for(int i = 0; i < region[0].size(); i++)
        {
            skipV[i] = 0;
        }
        for(int i = 0; i < region.size() - S.size() + 1; i++)
        {
            float i2 = i;
            for(float j = 0; j < region[0].size() - S[0].size() + 1; j++)
            {
                if(skipV[j] == 1) // 表示那一行已經不可能再放入方塊
                {
                    continue;
                }
                int ii = 0;
                
                for(int k = i; k < S.size() + i; k++)
                {
                    int jj = 0;
                    for(float l = j; l < S[0].size() + j; l++)
                    {
                        
                        if(region[k][l] == 1 && S[ii][jj] == 1) //當地圖與方塊撞到則跳出方塊的長寬比較
                        {
                            flag = 1;
                            skipV[l] = 1;
                            break;
                        } 
                        jj++;                    
                    }
                    if(flag == 1) // 當地圖與方塊撞到則跳出方塊的長寬比較
                    {
                        break;
                    }
                    ii++;  
                }
                if(flag == 0) // 當地圖沒有與方塊撞到，紀錄該位置
                {
                    if((i2 + i2 + 2) / 2 >= bestPos[1])
                    {
                        float yax = (i2 + i2 + 2) / 2;
                        bestPos = {j,yax};
                        bestDir = 3;
                    }                        
                 }
                else if(flag == 1) // 當地圖與方塊撞到，不紀錄該位置，並將flag調回0
                {
                    flag = 0;
                }
            }
        }

    }

    if(cube.cube == 6)
    {  //Zcube
        vector<vector<int>> E(2,vector<int>(3,1));
        E[0][2]=0;
        E[1][0]=0;
        vector<vector<int>> N(3,vector<int>(2,1));
        N[2][1]=0;
        N[0][0]=0;
        for(int i = 0; i < region[0].size(); i++)
        {
            skipV[i] = 0;
        }
        for(int i = 0; i < region.size() - E.size() + 1; i++)
        {
            float i2 = i;
            for(float j = 0; j < region[0].size() - E[0].size() + 1; j++)
            {
                if(skipV[j] == 1) // 表示那一行已經不可能再放入方塊
                {
                    continue;
                }
                int ii = 0;
                
                for(int k = i; k < E.size() + i; k++)
                {
                    int jj = 0;
                    for(float l = j; l < E[0].size() + j; l++)
                    {
                        
                        if(region[k][l] == 1 && E[ii][jj] == 1) //當地圖與方塊撞到則跳出方塊的長寬比較
                        {
                            flag = 1;
                            skipV[l] = 1;
                            break;
                        } 
                        jj++;                    
                    }
                    if(flag == 1) // 當地圖與方塊撞到則跳出方塊的長寬比較
                    {
                        break;
                    }
                    ii++;  
                }
                if(flag == 0) // 當地圖沒有與方塊撞到，紀錄該位置
                {
                    if((i2 + i2 + 1) / 2 > bestPos[1])
                    {
                        float yax = (i2 + i2 + 1) / 2;
                        bestPos = {j,yax};
                        bestDir = 0;
                    }                        
                 }
                else if(flag == 1) // 當地圖與方塊撞到，不紀錄該位置，並將flag調回0
                {
                    flag = 0;
                }
            }
        }
        for(int i = 0; i < region[0].size(); i++)
        {
            skipV[i] = 0;
        }
        for(int i = 0; i < region.size() - N.size() + 1; i++)
        {
            float i2 = i;
            for(float j = 0; j < region[0].size() - N[0].size() + 1; j++)
            {
                if(skipV[j] == 1) // 表示那一行已經不可能再放入方塊
                {
                    continue;
                }
                int ii = 0;
                
                for(int k = i; k < N.size() + i; k++)
                {
                    int jj = 0;
                    for(float l = j; l < N[0].size() + j; l++)
                    {
                        
                        if(region[k][l] == 1 && N[ii][jj] == 1) //當地圖與方塊撞到則跳出方塊的長寬比較
                        {
                            flag = 1;
                            skipV[l] = 1;
                            break;
                        } 
                        jj++;                    
                    }
                    if(flag == 1) // 當地圖與方塊撞到則跳出方塊的長寬比較
                    {
                        break;
                    }
                    ii++;  
                }
                if(flag == 0) // 當地圖沒有與方塊撞到，紀錄該位置
                {
                    if((i2 + i2 + 2) / 2 > bestPos[1])
                    {
                        float yax = (i2 + i2 + 2) / 2;
                        bestPos = {j,yax};
                        bestDir = 1;
                    }                        
                 }
                else if(flag == 1) // 當地圖與方塊撞到，不紀錄該位置，並將flag調回0
                {
                    flag = 0;
                }
            }
        }

    }





    //operation
    moveX = bestPos[0] - cube.x;
    rotate = bestDir - cube.dir;  
 
    
    if(rotate < 0)
    {
        for(int i = 0; i < abs(rotate); i++)
        {
            q.push(Clockwise);
        }
    }
    if(rotate > 0)
    {
        for(int i = 0; i < abs(rotate); i++)
        {
            q.push(CounterClockwise);
        }
    }
    if(moveX < 0)
    {
        for(int i = 0; i < abs(moveX); i++)
        {
           q.push(Left);
        }
    }
    if(moveX > 0)
    {
        for(int i = 0; i < abs(moveX); i++)
        {
            q.push(Right);
        }
    } 
   

    #if DEBUG
    for (int i = 0; i < 50; i++) {
        q.push(rand() % 5);
    }
    #endif


    return q;
}*/

queue<int> Tetris::nextPos(DiredCube cube, Region region)
{
    queue<int> q;
    srand(time(NULL));
    for (int i = 0; i < 50; i++)
    {
        int y = rand() % 4;
        if(y == 0)
            q.push(Left);
        else if(y == 1)
            q.push(Right);
        else if(y == 2)
            q.push(Clockwise);
        else
            q.push(CounterClockwise);
    }

    #if DEBUG
    for (int i = 0; i < 50; i++) {
        q.push(rand() % 5);
    }
    #endif

    return q;
}

#if SHOW
/**
 * Don't change those codes below
 * It's just for show tetris
 **/
void Tetris::renderRegion(Region region)
{
    for (size_t i = 0; i < (region.size() / 2) + 6; i++)
        cout << '_';
    
    cout << '\n';
    for (size_t i = 0; i < region.size(); i++) {
        cout << '|';
        for (size_t j = 0; j < region[i].size(); j++) {
            if (region[i][j] == 0) {
                cout << ' ';
            } else {
                cout << '@';
            }
        }
        cout << "|\n";
    }

    for (size_t i = 0; i < (region.size() / 2) + 6; i++)
        cout << '_';
    
    cout << '\n';
}

void Tetris::emulateDown(Region region, vector<Position> positions)
{
	for (int i = 0; i < positions.size(); i++) {
		region[ positions[i].second ][ positions[i].first ] = 1;
	}
    
	clear();
	renderRegion(region);
	usleep(SPEED);
}
#endif
