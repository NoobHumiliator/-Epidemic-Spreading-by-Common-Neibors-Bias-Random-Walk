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
#define M_A_X 999990000  //MAX����Ϊ30��
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
	srand((unsigned)time(NULL));   //��ʼ�����������
	while (true)
	{
		double randomnumber = 0;
		int t = 0;  //ͳ��������ѭ��ִ���˶��ٱ�
		int N = 1000;  //�����С
		int overflag = 0; //�Ƿ����ر� 
		int S = 0;//�׸�Ⱦ�ڵ�ĸ���  ��δ��Ⱦ�ڵ㣩
		int I = 0;//��Ⱦ�ڵ�ĸ�  ��    �������ڵ㣩
		int R = 0;//���߽ڵ�          �����߽ڵ㣩
		int IMAX = 0; //������Ⱦ������I�ﵽ�����ֵ
		int RMAX = 0; //����ʱ�̵�R��ֵ
		int nextloop = 0; // ��һ����ַ
		double degreesum = 0; //ͳ�ƽڵ�ĶȺ�
		double degree_begin = 0; //��ƫ������ߵĸ��ʷ��� ���俪ʼ
		double degree_end = 0;   //��ƫ������ߵĸ��ʷ��� �������
		double rand_num = 0;    //0-1֮������С��
		double alpha = 0; //��ƫ������ߵĲ���
		double mu = 0.2;   //��  ����ϵ��
		double gamma = 0;    //�� �׸нڵ��������ϵ��  ��Ϊ������߹��̴�Ⱦ�ٶȽ�����������ϵ�����õ��㹻��
		double delta = 0.1;    //�� ��Ⱦ�ڵ��������ϵ��  ��Ϊ������߹��̴�Ⱦ�ٶȽ���  ������ϵ�����õ��㹻��
		vector<int> temp_inf;  //�Խ�Ҫ����Ⱦ�Ľڵ�洢һ��
		vector<int> temp_imu;  //�Խ�Ҫ�����ߵĽڵ�洢һ��
		list<int> ele;      //����������߹��̵�����λ��
		vector<int> last; //��ʾ��һ����˭����˭��Ⱦ�� last[3]=2; 3�Žڵ㱻2������Ⱦ
		int spread = 1;   //ÿ����Ⱦ�ڵ㣨�����ڵ㣩ÿ���ͷų����ٸ�����
		int s = rand() % (N - 1); //s start    ����Ҹ���ʼʱ��Ĵ����ڵ��λ�� 
		vector< vector<int> > CN(N);  //��ʾ��ͬ�ھӵĶ�ά����  CN[4][5]=6  4�Žڵ���5�Žڵ���6����ͬ�ھ�
		vector< vector<int> > a(N); //��ʾ����ṹ�Ķ�ά����   �ճ���һ��λ���б�ʶ��0δ��Ⱦ�ڵ�  1�����ڵ� 2���߽ڵ� 
		cout << "��ʼ�ĸ�Ⱦ�ڵ�λ��Ϊ" << s << endl;


		for (int start = 0; start < N; start++)   //��ʼ��
		{
			a[start].push_back(-1);
			CN[start].push_back(-1);
		}

		for (int graphclear = 0; graphclear < N; graphclear++)
		{
			a[graphclear].clear();
			CN[graphclear].clear();
		}
		for (int startkind = 0; startkind < N; startkind++)   //���нڵ�ĵ�һλ��ֵ����ʶ���нڵ�ĳ�ʼ״��
		{
			if (startkind != s)     //������Ǹ�Ⱦ�ڵ�
			{
				a[startkind].push_back(0);
			} //0��ʾ�׸�Ⱦ�ڵ�
			else
			{
				a[startkind].push_back(1);
			} //1��ʾ��Ⱦ�ڵ� 
		}
		for (int start_cn = 0; start_cn < N; start_cn++)   //���нڵ�ĵ�һλ��ֵ����ʶ���нڵ�ĳ�ʼ״��
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
		//////////////////////////////////////////////////CN�ļ���

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
						//cout <<k<<"��"<< i << "��" << j << "��ͬ�ھ�" << endl;
						CN[i][j]++;
						CN[j][i]++;
					}
					next_to_i = 0;
					next_to_j = 0;
				}
				//cout << i << "��" << j << "��ͬ�ھ���Ϊ" << CN[i][j] << endl;
			}
		}
		///////////////////////////////////////////////////////
		/*
		for (int degreecount=0;degreecount<N;degreecount++)
		{
		//cout<<"���Ϊ"<<degreecount<<"�Ľڵ��Ϊ"<<a[degreecount].size()-1<<endl;
		//getch();
		}
		*/

		//////////////////////////////////////////////////////////////////////////////////�����ʼ����������ʼ��Ⱦ����
		for (alpha = -2.0; alpha <= -2.0; alpha = alpha + 0.2)
		{
			for (int restart = 0; restart < N; restart++)   //���нڵ�ĵ�һλ���¸�ֵ
			{
				if (restart != s)     //������Ǹ�Ⱦ�ڵ�
				{
					a[restart][0] = 0;
				} //0��ʾ�׸�Ⱦ�ڵ�
				else
				{
					a[restart][0] = 1;
				} //1��ʾ��Ⱦ�ڵ� 
			}
			last.clear();
			for (int last_clear = 0; last_clear < N; last_clear++)
			{
				last.push_back(-1);
			}
			while (1)
			{
				////////////////////////////////////////////////////////////////////////����ÿ����Ⱦ���������ڵ��ͷ����ӳ���
				t++; //����
				for (int elespread = 0; elespread < N; elespread++)    //�������нڵ�
				{
					if (a[elespread][0] == 1)    //�����ǰ�ڵ��Ǹ�Ⱦ�ڵ�
					{
						for (int spread_process = 0; spread_process < spread; spread_process++)   //ÿ����Ⱦ�ڵ��ͷų�spread������
						{
							ele.push_back(elespread);        //����ѹ�����β��
						}
					}
				}
				//cout << "�����ڵ����Ӹ���" << ele.size() << endl;
				////////////////////////////////////////////////////////////////////////////��һ�� ����Ⱦ
				for (list<int>::iterator i = ele.begin(); i != ele.end();)            //list�����Ƕ�̬��С��ʹ�õ���������ȫ������
				{
					//system("pause");
					nextloop = 0; //����break��continue����д��ѭ��ǰ�� 
					degreesum = 0;//�Ⱥ�����
					if (a[*i][0] == 1 && (a[*i].size() - 1) != 0)   //�����ǰ�ڵ��Ǵ����ڵ� ����������һ���ھ�
					{
						for (int degree_count = 1; degree_count < a[*i].size(); degree_count++) //ͳ�ƽڵ��ھӵĶ�
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
								//cout << *i << "�Ǳ�" << last[*i] <<"��Ⱦ��"<< endl;
							}
						}
						//cout << degreesum << endl;
						rand_num = (double)rand() / RAND_MAX;

						if (degreesum > 0.000000001)
						{
							for (int deg = 1; deg<a[*i].size(); deg++) //ͳ�ƽڵ��ھӵĶ�
							{
								if (a[*i][deg] != last[*i] && CN[*i][a[*i][deg]] != 0)
								{
									degree_begin = degree_end;
									degree_end = degree_end + pow(CN[*i][a[*i][deg]], alpha) / degreesum;
									cout << *i << "�ھ���" << a[*i][deg] << "����CNΪ" << CN[*i][a[*i][deg]] << "Ϊ����������" << degree_begin << "-" << degree_end << endl;
									if (rand_num>degree_begin&&rand_num < degree_end)
									{
										nextloop = deg; break;
									}
									else
									{
									}
								}
							}
							degree_begin = 0; //��������
							degree_end = 0;
							//cout<<*i<<"��һ����ַ"<<a[*i][nextloop]<<endl;
						}
						else   //degreesumΪ0
						{
							nextloop = 1 + rand() % (a[*i].size() - 1);
							//cout << "û�д�CN���ھ����ѡһ��" <<a[*i][nextloop] << endl;
						}
						if (a[a[*i][nextloop]][0] == 1 || a[a[*i][nextloop]][0] == 2)   //�����һ���Ľڵ�Ϊ���߽ڵ㣬���߸�Ⱦ�ڵ㣨�����ڵ㣩
						{
							ele.erase(i++); continue;
						}     //ɾ������ Ȼ�������ǰ��
						else
						{
						}
						// cout<<"��ǰ��ַΪ"<<*i<<"��һ����ַΪ"<<a[*i][nextloop]<<endl;
						if (a[a[*i][nextloop]][0] == 0)   //�������һ�������С�ڦ�,����һ���Ľڵ���δ��Ⱦ�ڵ�
						{
							temp_inf.push_back(a[*i][nextloop]);
							last[a[*i][nextloop]] = *i;
							ele.erase(i++);
							continue;
						} //���½�Ҫ����Ⱦ�Ľڵ���,ɾ�����ӣ���������ǰ�� 
					}
					else
					{
						ele.erase(i++);
					}         //��ǰ�ڵ㲻�Ǵ����ڵ�,����û���ھӣ�ɾ�����ӣ�������Ҳǰ��
				}
				for (int inf = 0; inf < temp_inf.size(); inf++)
				{
					a[temp_inf[inf]][0] = 1;
				}    //����Ⱦ�ı�ʾ����Ϊ1 ����Ⱦ��
				temp_inf.clear();    //����Ⱦ����ʱ�������
				/*/////////////////////////////////////////////////////////////////////////////�ڶ���������
				for (int imu=0;imu<N;imu++)
				{
				if(a[imu][0]==2)   //�����ǰ�ڵ������߽ڵ�
				{
				for (int immune=1;immune<a[imu].size();immune++)  //����һ�鵱ǰ�ڵ���ھ�
				{
				if((double)rand()/RAND_MAX<mu&&a[a[imu][immune]][0]==1)   //�������һ�������С�ڦ�,���뵱ǰ�ڵ��ڽӣ��Ӵ����Ľڵ��Ǹ�Ⱦ�ڵ�
				{temp_imu.push_back(a[imu][immune]);} //���½�Ҫ�����ߵĽڵ���
				}
				}
				}
				for (int im=0;im<temp_imu.size();im++)
				{a[temp_imu[im]][0]=2;}    //�����ߵĽڵ��ʾ����Ϊ2 ��������
				temp_imu.clear();    //����Ⱦ�ı������
				*//////////////////////////////////////////////////////////////////////////////��������������
				for (int selfimu = 0; selfimu < N; selfimu++)
				{
					//	 if(a[selfimu][0]==0&&(double)rand()/RAND_MAX<gamma)   //�����ǰ�ڵ����׸�Ⱦ�ڵ㣬��������һ��С�ڦõ������
					//	 {a[selfimu][0]=2;} //״̬��ʶ����Ϊ2   ������
					if (a[selfimu][0] == 1 && (double)rand() / RAND_MAX < delta)   //�����ǰ�ڵ��Ǹ�Ⱦ�ڵ㣨�����ڵ㣩����������һ��С�ڦĵ������
					{
						a[selfimu][0] = 2;
						//cout << selfimu << "������" << endl;
					} //״̬��ʶ����Ϊ2   ������		 
				}
				/////////////////////////////////////////////////////////////////////////////��Ⱦ����ȫ������ �������������
				for (int count = 0; count < N; count++)
				{                              // 0δ��Ⱦ�ڵ�  1�����ڵ� 2���߽ڵ� 
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
				//////////////////////////////////////��Ļ���
				/*
				cout << "��Ⱦ���е���" << t << "��" << endl;
				cout << "S�׸�Ⱦ(δ��Ⱦ)�ڵ����:" << S << endl;
				cout << "I��Ⱦ(�����ڵ�)�ڵ����:" << I << endl;
				cout << "R���߽ڵ����:" << R << endl;
				*/
				if (I > IMAX)  //IMAX��I�����ֵ
				{
					IMAX = I;
				}
				////////////////////////////////////////�ı����
				ofstream ftest("result.txt", ios::app);
				ftest << alpha << " " << t << " " << S << " " << I << " " << R << endl;
				ftest.close();
				RMAX = R;
				////////////////////////////////////////
				S = 0;    //����������  ����
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
					degree_end = 0;   //��ƫ������ߵĸ��ʷ��� �������
					rand_num = 0;    //0-1֮������С��
					temp_inf.clear();  //�Խ�Ҫ����Ⱦ�Ľڵ�洢һ��
					temp_imu.clear();  //�Խ�Ҫ�����ߵĽڵ�洢һ��
					ele.clear();      //����������߹��̵�����λ��
					break;
				}
			}
		}
	}
}
