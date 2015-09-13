#include "stdafx.h"
#include<math.h>
#include<iostream>
#include<conio.h>
#include<time.h>
#include<string.h>
#include<stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <cstdio>  
#include <cstdlib>  
#include <fstream>
#include <vector>
#include <list>

using namespace std;
#define M_A_X 999990000  //MAX定义为30万
typedef vector< vector<int> >  vvt;
#ifndef Index
struct Index
{
	int x, y;
};
#endif


vector<Index> test(int inN)
{

	vector<Index> mytest;
	double r = 3.0;
	int TIMES = 1;
	int N = inN;
	int k = 6;
	srand((unsigned)time(0));
	while (TIMES--)
	{

		vvt  vv, vv1, matrix, bit, bit1;
		vvt::iterator iter;
		vector<int>::iterator intiter, intiter2, intiter3, intiter7;
		vector<double>::iterator intiter8;
		vector<int> vi, vi1, row, row1, row2, vi2, vi3, s, breaknode, ND, ND1, ND2, nextposition, ND4, ND5;
		vector<double> capacity, ND3, ND6, ND7, B;
		vector<float> weight1, weight;
		int i, j, edge, number, signal, i1, size, signal1;
		double i0, c0, T1;
		double prob, Psum, Q;

		Q = 1 / (r - 1);
		i0 = 1;
		T1 = 0;
		for (i = 0; i < N; i++)
		{
			T1 = T1 + 1 / pow((i + i0), Q);
		}
		c0 = 1 / T1;
		row.clear();
		bit.clear();
		bit1.clear();
		for (i = 0; i < N; i++)
		{
			bit.push_back(row);
			bit1.push_back(row);

		}
		weight.clear();
		for (i = 1; i <= N; i++)
		{
			weight.push_back(c0 / pow((i + i0 - 1), Q));
		}
		T1 = 0;
		for (i = 0; i < N; i++)
		{
			T1 = T1 + weight[i];
		}
		for (i = 0; i < N; i++)
		{
			weight[i] = weight[i] / T1;
		}

		number = k*N / 2;

		edge = 0;
		while (edge < number)
		{
			nextposition.clear();
			for (j = 0; j < 2; j++)
			{
				prob = rand() / float(RAND_MAX);
				// cout<<"prob="<<prob<<endl;
				Psum = 0.0;
				signal = 0;
				size = weight.size();
				for (i1 = 0; i1 < size; i1++)
				{
					Psum = Psum + weight[i1];
					if (prob < Psum)
					{
						nextposition.push_back(i1);
						signal = 1;
						break;
					}

				}
				if (signal == 0)
				{
					nextposition.push_back(i1 - 1);
				}
			}

			if (nextposition[0] != nextposition[1])
			{
				signal1 = 0;
				for (intiter = bit1[nextposition[1]].begin(); intiter != bit1[nextposition[1]].end(); intiter++)
				{
					if (*intiter == nextposition[0])
					{
						signal1 = 1;
						break;
					}
				}
				if (signal1 == 0)
				{
					bit1[nextposition[1]].push_back(nextposition[0]);
					bit1[nextposition[0]].push_back(nextposition[1]);
					bit[nextposition[0]].push_back(nextposition[1]);
					edge++;
				}
			}
		}

		vvt::iterator intiter11;
		for (i = 1, intiter11 = bit.begin(); intiter11 != bit.end(); i++, intiter11++)
		{
			row.clear();
			row = *intiter11;
			for (intiter = row.begin(); intiter != row.end(); intiter++)
			{
				/*
				printf("%u %u\n",i,((*intiter)+1));
				ofstream ftest("graph.txt", ios::app);
				ftest<<i<<" "<<((*intiter)+1)<<endl;
				ftest.close();
				*/
				Index* tmp = new Index;
				tmp->x = i;
				tmp->y = ((*intiter) + 1);
				mytest.push_back(*tmp);
				delete tmp;
			}

		}
		//	puts("-1 -1");

	}
	return mytest;
}

void main()
{
	srand((unsigned)time(NULL));   //初始化随机数种子
	while (true)
	{
		double randomnumber = 0;
		int t = 0;  //统计主程序循环执行了多少遍
		int N = 1000;  //网络大小
		int overflag = 0; //是否有重边 
		int S = 0;//易感染节点的个数  （未感染节点）
		int I = 0;//感染节点的个  数    （传播节点）
		int R = 0;//免疫节点          （免疫节点）
		int IMAX = 0; //整个感染过程中I达到的最大值
		int RMAX = 0; //收敛时刻的R的值
		int nextloop = 0; // 下一跳地址
		double degreesum = 0; //统计节点的度和
		double degree_begin = 0; //有偏随机行走的概率分配 区间开始
		double degree_end = 0;   //有偏随机行走的概率分配 区间结束
		double rand_num = 0;    //0-1之间的随机小数
		double alpha = 0; //有偏随机行走的参数
		double mu = 0.2;   //μ  免疫系数
		double gamma = 0;    //γ 易感节点的自免疫系数  因为随机行走过程传染速度较慢，自免疫系数设置的足够低
		double delta = 0.1;    //δ 感染节点的自免疫系数  因为随机行走过程传染速度较慢  自免疫系数设置的足够低
		vector<int> temp_inf;  //对将要被感染的节点存储一下
		vector<int> temp_imu;  //对将要被免疫的节点存储一下
		list<int> ele;      //储存随机行走过程的粒子位置
		vector<int> last; //表示上一个是谁，被谁感染的 last[3]=2; 3号节点被2号所感染
		int spread = 1;   //每个感染节点（传播节点）每次释放出多少个粒子
		int s = rand() % (N - 1); //s start    随机找个开始时候的传播节点的位置 
		vector< vector<int> > CN(N);  //表示共同邻居的二维数组  CN[4][5]=6  4号节点与5号节点有6个共同邻居
		vector< vector<int> > a(N); //表示网络结构的二维数组   空出第一个位进行标识：0未感染节点  1传播节点 2免疫节点 
		cout << "开始的感染节点位置为" << s << endl;


		for (int start = 0; start < N; start++)   //初始化
		{
			a[start].push_back(-1);
			CN[start].push_back(-1);
		}

		for (int graphclear = 0; graphclear < N; graphclear++)
		{
			a[graphclear].clear();
			CN[graphclear].clear();
		}
		for (int startkind = 0; startkind < N; startkind++)   //所有节点的第一位赋值，标识所有节点的初始状况
		{
			if (startkind != s)     //如果它是感染节点
			{
				a[startkind].push_back(0);
			} //0表示易感染节点
			else
			{
				a[startkind].push_back(1);
			} //1表示感染节点 
		}
		for (int start_cn = 0; start_cn < N; start_cn++)   //所有节点的第一位赋值，标识所有节点的初始状况
		{
			for (int cn_line = 0; cn_line < N; cn_line++)
			{
				CN[start_cn].push_back(0);
			}
		}
		int x, y;
		vector<Index> tst = test(N);
		for (int i = 0; i < tst.size(); i++)
		{
			cout << tst[i].x - 1 << "  " << tst[i].y - 1 << endl;
			a[tst[i].x - 1].push_back(tst[i].y - 1);
			a[tst[i].y - 1].push_back(tst[i].x - 1);
		}
		//////////////////////////////////////////////////CN的计算

		int next_to_i = 0;
		int next_to_j = 0;

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < i; j++)
			{
				for (int k = 0; k < N; k++)
				{
					for (int search_i = 1; search_i < a[i].size(); search_i++)
					{
						if (a[i][search_i] == k)
						{
							next_to_i = 1;
						}
					}
					for (int search_j = 1; search_j < a[i].size(); search_j++)
					{
						if (a[j][search_j] == k)
						{
							next_to_j = 1;
						}
					}
					if (next_to_i == 1 && next_to_j == 1)
					{
						//cout <<k<<"是"<< i << "与" << j << "共同邻居" << endl;
						CN[i][j]++;
						CN[j][i]++;
					}
					next_to_i = 0;
					next_to_j = 0;
				}
				//cout << i << "与" << j << "共同邻居数为" << CN[i][j] << endl;
			}
		}
		///////////////////////////////////////////////////////
		/*
		for (int degreecount=0;degreecount<N;degreecount++)
		{
		//cout<<"编号为"<<degreecount<<"的节点度为"<<a[degreecount].size()-1<<endl;
		//getch();
		}
		*/

		//////////////////////////////////////////////////////////////////////////////////网络初始化结束，开始感染过程
		for (alpha = -2.0; alpha <= -2.0; alpha = alpha + 0.2)
		{
			for (int restart = 0; restart < N; restart++)   //所有节点的第一位重新赋值
			{
				if (restart != s)     //如果它是感染节点
				{
					a[restart][0] = 0;
				} //0表示易感染节点
				else
				{
					a[restart][0] = 1;
				} //1表示感染节点 
			}
			last.clear();
			for (int last_clear = 0; last_clear < N; last_clear++)
			{
				last.push_back(-1);
			}
			while (1)
			{
				////////////////////////////////////////////////////////////////////////首先每个感染（传播）节点释放粒子出来
				t++; //计数
				for (int elespread = 0; elespread < N; elespread++)    //遍历所有节点
				{
					if (a[elespread][0] == 1)    //如果当前节点是感染节点
					{
						for (int spread_process = 0; spread_process < spread; spread_process++)   //每个感染节点释放出spread个粒子
						{
							ele.push_back(elespread);        //粒子压入队列尾部
						}
					}
				}
				//cout << "网络内的粒子个数" << ele.size() << endl;
				////////////////////////////////////////////////////////////////////////////第一步 ：感染
				for (list<int>::iterator i = ele.begin(); i != ele.end();)            //list现在是动态大小，使用迭代器遍历全部粒子
				{
					//system("pause");
					nextloop = 0; //用了break与continue清零写在循环前面 
					degreesum = 0;//度和清零
					if (a[*i][0] == 1 && (a[*i].size() - 1) != 0)   //如果当前节点是传播节点 ，且有至少一个邻居
					{
						for (int degree_count = 1; degree_count < a[*i].size(); degree_count++) //统计节点邻居的度
						{
							if (a[*i][degree_count] != last[*i])
							{
								if (CN[*i][a[*i][degree_count]] != 0)
								{
									degreesum = degreesum + pow(CN[*i][a[*i][degree_count]], alpha);
								}
							}
							else
							{
								//cout << *i << "是被" << last[*i] <<"感染的"<< endl;
							}
						}
						//cout << degreesum << endl;
						rand_num = (double)rand() / RAND_MAX;

						if (degreesum > 0.000000001)
						{
							for (int deg = 1; deg<a[*i].size(); deg++) //统计节点邻居的度
							{
								if (a[*i][deg] != last[*i] && CN[*i][a[*i][deg]] != 0)
								{
									degree_begin = degree_end;
									degree_end = degree_end + pow(CN[*i][a[*i][deg]], alpha) / degreesum;
									cout << *i << "邻居是" << a[*i][deg] << "它的CN为" << CN[*i][a[*i][deg]] << "为其分配的区间" << degree_begin << "-" << degree_end << endl;
									if (rand_num>degree_begin&&rand_num < degree_end)
									{
										nextloop = deg; break;
									}
									else
									{
									}
								}
							}
							degree_begin = 0; //区间清零
							degree_end = 0;
							//cout<<*i<<"下一跳地址"<<a[*i][nextloop]<<endl;
						}
						else   //degreesum为0
						{
							nextloop = 1 + rand() % (a[*i].size() - 1);
							//cout << "没有带CN的邻居随便选一个" <<a[*i][nextloop] << endl;
						}
						if (a[a[*i][nextloop]][0] == 1 || a[a[*i][nextloop]][0] == 2)   //如果下一跳的节点为免疫节点，或者感染节点（传播节点）
						{
							ele.erase(i++); continue;
						}     //删除粒子 然后迭代器前进
						else
						{
						}
						// cout<<"当前地址为"<<*i<<"下一跳地址为"<<a[*i][nextloop]<<endl;
						if (a[a[*i][nextloop]][0] == 0)   //如果生成一个随机数小于λ,且下一跳的节点是未感染节点
						{
							temp_inf.push_back(a[*i][nextloop]);
							last[a[*i][nextloop]] = *i;
							ele.erase(i++);
							continue;
						} //记下将要被感染的节点编号,删除粒子，迭代器向前进 
					}
					else
					{
						ele.erase(i++);
					}         //当前节点不是传播节点,或者没有邻居，删除粒子，迭代器也前进
				}
				for (int inf = 0; inf < temp_inf.size(); inf++)
				{
					a[temp_inf[inf]][0] = 1;
				}    //被感染的标示符置为1 被感染了
				temp_inf.clear();    //被感染的临时编号清零
				/*/////////////////////////////////////////////////////////////////////////////第二步：免疫
				for (int imu=0;imu<N;imu++)
				{
				if(a[imu][0]==2)   //如果当前节点是免疫节点
				{
				for (int immune=1;immune<a[imu].size();immune++)  //遍历一遍当前节点的邻居
				{
				if((double)rand()/RAND_MAX<mu&&a[a[imu][immune]][0]==1)   //如果生成一个随机数小于μ,且与当前节点邻接（接触）的节点是感染节点
				{temp_imu.push_back(a[imu][immune]);} //记下将要被免疫的节点编号
				}
				}
				}
				for (int im=0;im<temp_imu.size();im++)
				{a[temp_imu[im]][0]=2;}    //被免疫的节点标示符置为2 被免疫了
				temp_imu.clear();    //被感染的编号清零
				*//////////////////////////////////////////////////////////////////////////////第三步：自免疫
				for (int selfimu = 0; selfimu < N; selfimu++)
				{
					//	 if(a[selfimu][0]==0&&(double)rand()/RAND_MAX<gamma)   //如果当前节点是易感染节点，且生成了一个小于γ的随机数
					//	 {a[selfimu][0]=2;} //状态标识符置为2   自免疫
					if (a[selfimu][0] == 1 && (double)rand() / RAND_MAX < delta)   //如果当前节点是感染节点（传播节点），且生成了一个小于δ的随机数
					{
						a[selfimu][0] = 2;
						//cout << selfimu << "免疫了" << endl;
					} //状态标识符置为2   自免疫		 
				}
				/////////////////////////////////////////////////////////////////////////////感染过程全部结束 ，进入计数环节
				for (int count = 0; count < N; count++)
				{                              // 0未感染节点  1传播节点 2免疫节点 
					if (a[count][0] == 0)
					{
						S++;
					}
					if (a[count][0] == 1)
					{
						I++;
					}
					if (a[count][0] == 2)
					{
						R++;
					}
				}
				//////////////////////////////////////屏幕输出
				/*
				cout << "感染进行到第" << t << "步" << endl;
				cout << "S易感染(未感染)节点个数:" << S << endl;
				cout << "I感染(传播节点)节点个数:" << I << endl;
				cout << "R免疫节点个数:" << R << endl;
				*/
				if (I > IMAX)  //IMAX是I的最大值
				{
					IMAX = I;
				}
				////////////////////////////////////////文本输出
				ofstream ftest("result.txt", ios::app);
				ftest << alpha << " " << t << " " << S << " " << I << " " << R << endl;
				ftest.close();
				RMAX = R;
				////////////////////////////////////////
				S = 0;    //计数结束了  清零
				I = 0;
				R = 0;
				if (t == 150)
				{
					t = 0;
					ofstream gtest("finresult.txt", ios::app);
					gtest << alpha << " " << IMAX << " " << RMAX << endl;
					gtest.close();
					IMAX = 0;
					RMAX = 0;
					nextloop = 0;
					degreesum = 0;
					degree_begin = 0;
					degree_end = 0;   //有偏随机行走的概率分配 区间结束
					rand_num = 0;    //0-1之间的随机小数
					temp_inf.clear();  //对将要被感染的节点存储一下
					temp_imu.clear();  //对将要被免疫的节点存储一下
					ele.clear();      //储存随机行走过程的粒子位置
					break;
				}
			}
		}
	}
}
