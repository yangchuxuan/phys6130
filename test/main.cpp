// ConsoleApplication1.cpp : Defines the entry point for the console application.
//note: I'm not sure about the fomula 1, need futher chech in theoris.

//#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <random>
//#include <direct.h>
#include <string>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
using namespace std;

//this part should be move to somewhere
const int interactionswitch = 1;
double rateE = 1.5;
double rateARE = 0.6;//0.6;
double change = 0;
const int sitesize = 40;
int affinitysize = 0;
int site[sitesize] = {};
int siteBound[sitesize] = {};
int timemax = 0;
int activescore = 0;
int repressivescore = 0;
int scoreflag = 0;
int switchcount = 0;
double timestart = 0;// not ready to analyse data with in program
double Jin = 0;


double J[5][5] = {};

//for epsilonin[5][3] and epsilonout[5][3]
double delta_epsilon = 2;
//double epsilonin[5][3] = {};
//double epsilonout[5][3] = {};

double epsilonin[5][3] = { { 0, 0, 0 }, { -1 - delta_epsilon, -1, -1 + delta_epsilon }, { 1 - delta_epsilon, 1, 1 + delta_epsilon },
{ -1 + delta_epsilon, -1, -1 - delta_epsilon }, { 1 + delta_epsilon, 1, 1 - delta_epsilon } };
double epsilonout[5][3] = { { 0, 0, 0 }, { 3 - delta_epsilon, 3, 3 + delta_epsilon }, { 3 - delta_epsilon, 3, 3 + delta_epsilon },
{ 3 + delta_epsilon, 3, 3 - delta_epsilon }, { 3 + delta_epsilon, 3, 3 - delta_epsilon } };
//
//double epsilonin[5][3] = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 },
//{ 0, 0, 0 }, { 0, 0, 0 } };
//double epsilonout[5][3] = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 },
//{ 0, 0, 0 }, { 0, 0, 0 } };



double T[sitesize][5][5] = {};
double v[3][3] = {};//here v represent the speed of reaction, although in the paper the v is a constant
// and all the same for different kinds of reaction, here I use a 3*3 matrix, here v[1][0] represent v_1->0;
int main()
{

	double eGamma = 0;
	double eA = 0;
	double eGammaMax = 0;
	double eGammaMin = 0;
	int num;
	int tempnum;

	string s;
	ifstream fin;
	fin.open("config.txt");

	getline(fin, s);
	stringstream ss;
	ss << s;
	ss >> affinitysize;

	getline(fin, s);
	ss.clear();
	ss << s;
	ss >> eA;

	getline(fin, s);
	ss.clear();
	ss << s;
	ss >> eGammaMax;

	getline(fin, s);
	ss.clear();
	ss << s;
	ss >> eGammaMin;

	getline(fin, s);
	ss.clear();
	ss << s;
	ss >> timemax;


	getline(fin, s);
	ss.clear();
	ss << s;
	ss >> num;

	getline(fin, s);
	ss.clear();
	ss << s;
	ss >> change;

	getline(fin, s);
	ss.clear();
	ss << s;
	ss >> Jin;

	fin.close();
	cout << affinitysize << " " << eA << " " << eGammaMax<<" "<<eGammaMin<<" "<<timemax<<" "<<change<<endl;
	//system("pause");
	
	int simulation(double eGamma, double eA,int num);

	for (eGamma = eGammaMax; eGamma >= eGammaMin; eGamma = eGamma -change)
	{
		tempnum = num;
		while (tempnum >= 5)
		{
			
			cout << tempnum << " ";
			simulation(eGamma, eA, tempnum);
			tempnum = tempnum - 5;		
			//cout << switchcount << endl;
			//system("pause");
		}
	}
	

	return 0;
	
}


int simulation(double eGamma,double eA,int num)
{
	double timeavg = 0;
	double timestart = 0;
	double timeaccu = 0;
	num = num-4;
	char output_dir[120];
	char output_dir2[120];
	char fname1[120];
	char fname2[120];
	char fname3[120];
	//sprintf_s(output_dir, ".\\%s%3.1lf_%s%3.1lf\\","eGamma",eGamma,"eA",eA );
	//_mkdir(output_dir);
	snprintf(output_dir, sizeof(output_dir), ".//%s%3.1lf_%s%3.1lf//", "eGamma", eGamma, "eA", eA);
	mkdir(output_dir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	//sprintf_s(output_dir2, "%s\\%d\\", output_dir,num);
	//_mkdir(output_dir2);
	snprintf(output_dir2, sizeof(output_dir2), "%s//%d//", output_dir, num);
	mkdir(output_dir2, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	//sprintf_s(fname1, "%splotoutput.txt", output_dir2);
	snprintf(fname1, sizeof(fname1), "%splotoutput.txt", output_dir2);
	ofstream fout1;//for plot
	fout1.open(fname1);
	//sprintf_s(fname2, "%smatrixoutput.txt", output_dir2);
	snprintf(fname2, sizeof(fname2), "%smatrixoutput.txt", output_dir2);
	ofstream fout2;//for matrix
	fout2.open(fname2);
	//sprintf_s(fname3, "%stimedata.txt", output_dir2);
	snprintf(fname3, sizeof(fname3), "%stimedata.txt", output_dir2);
	ofstream fout3;
	fout3.open(fname3);


	int output();
	double partition_function();
	int matrix_multiply(double a[5][5], double b[5][5], double c[5][5]);
	double probability_function(int n, int state);
	int int_T_matrix();

	random_device rd;
	mt19937 gen(rd());
	int e = 0;
	int a = 0;
	int r = 0;
	int rmae = 0;
	int rmar = 0;
	int rmre = 0;
	int rmrr = 0;
	int amae = 0;
	int amaa = 0;
	int amre = 0;
	int amra = 0;
	int active = 0;
	int repressive = 0;
	int empty = 0;
	/*double ATPnumber = 1;
	double rateEAR = exp(-ATPnumber * 24);
	double rateamaAE = 0.1;
	double rateamrEA = 0.1;
	double ratermaRE = 0.1;
	double ratermrER = 0.1;*/

	double rateEAR = 1 / (1 / (rateARE*exp(-eA+delta_epsilon)) + 1 / (rateARE*exp(-eA+delta_epsilon))+1 / (rateARE*exp(-eA)));//Is this what it suppose to be?
	double rateamaAE = 0;
	double rateamrEA = 0;
	double ratermaRE = 0;
	double ratermrER = 0;
	rateamaAE = rateamrEA = ratermaRE = ratermrER = rateE*exp(eA-eGamma- delta_epsilon);

	//this part is used to initialize the value of site[sitesize],J[5][5],epsilonout[5][3],epsiloin[5][3]
	//for site[sitesize]
	for (int i = 0; i < sitesize; i++)
	{
		/*if (i < 15 || i>24)
		site[i] = 1;
		else
		site[i] = 1;*/
		/*int temp = 0;*/
		uniform_int_distribution<> temp(0, 2);
		switch (temp(gen))
		{
		case 0:
		{
			site[i] = 0;
			break;
		}
		case 1:
		{
			site[i] = 1;
			break;
		}
		case 2:
		{
			site[i] = 2;
			break;
		}
		default:
			break;
		}
		/*if (temp < 1)
		site[i] = 0;
		else
		if (temp < 2)
		site[i] = 1;
		else
		site[i] = 2;*/
	}
	//for J[5][5], there used to be a problem for initialize J, fixed 
	/*if (interactionswitch == 1)
	{
	for (int i = 0; i < 5; i++)
	{
	for (int j = 0; j < 5; j++)
	{
	if (i == j && (i != 0 || j != 0))
	J[j][j] = 3;
	else
	if (i == 0 || j == 0)
	J[i][j] = 0;
	else
	J[i][j] = -2;
	}
	}
	}*/
	if (interactionswitch == 1)
	{
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (i == j && (i != 0 || j != 0))
					J[j][j] = Jin;
				else
					if (i == 0 || j == 0)
						J[i][j] = 0;
					else
						J[i][j] = -Jin+1;
			}
		}
	}
	else
	{
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (i == j && (i != 0 || j != 0))
					J[j][j] = 0;
				else
					if (i == 0 || j == 0)
						J[i][j] = 0;
					else
						J[i][j] = 0;
			}
		}
	}

	/*cout << "J" << endl;
	for (int i = 0; i < 5; i++)
	{
	for (int j = 0; j < 5; j++)
	{
	cout << J[i][j] << ' ';
	}
	cout << endl;
	}*/


	cout << "eGamma: " << eGamma << " eA: " << eA << endl;
	//output();
	//in order to keep math work here, all this site array is begin with 1; 
	int sitermar[sitesize + 1] = {};
	int sitermrr[sitesize + 1] = {};
	int siteamaa[sitesize + 1] = {};
	int siteamra[sitesize + 1] = {};
	int sitermae[sitesize + 1] = {};
	int sitermre[sitesize + 1] = {};
	int siteamae[sitesize + 1] = {};
	int siteamre[sitesize + 1] = {};
	int siteactive[sitesize + 1] = {};
	int siterepressive[sitesize + 1] = {};
	int siteempty[sitesize + 1] = {};
	int sitee[sitesize + 1] = {};
	int sitea[sitesize + 1] = {};
	int siter[sitesize + 1] = {};
	double t = 0;
	double tempt1 = 0;
	double tempt2 = 0;
	double tempt3 = 0;
	double Hs = 0;
	double P[5] = {};
	int loopflag = 1;
	int repressivecount = 0;
	int activecount = 0;
	int emptycount = 0;
	switchcount = 0;
	activescore = 0;
	repressivescore = 0;
	repressivescore = 0;
	activescore = 0;
	
	while (switchcount<100 && t <= timemax+1)
	{
		e = a = r = rmar = rmae = rmre = rmrr = amaa = amae = amra = amre = 0;
		active = repressive = empty = 0;
		Hs = 0;
		activecount = 0;
		emptycount = 0;
		repressivecount = 0;
		int_T_matrix();
		double Z = partition_function();// for modification

		for (int n = 0; n < sitesize; n++)
		{


			for (int i = 0; i < 5; i++)
			{
				P[i] = probability_function(n, i);
				//If I want to observe the probability this is the best place
			}



			switch (site[n])
			{
			case 0:
			{
				repressive = repressive + 1;
				siterepressive[repressive] = n;
				//double totalP = probability_function(n, 0) + probability_function(n, 1) + probability_function(n, 2);
				double totalP = P[0] + P[1] + P[2];
				//cout << probability_function(n, 0) + probability_function(n, 1) + probability_function(n, 2) << endl;
				totalP = totalP / Z;
				//cout << totalP << endl;
				uniform_real_distribution<> tempf(0, totalP);
				double temp = tempf(gen);
				if (temp <= P[0]/Z /*probability_function(n, 0) / Z*/)
				{
					r = r + 1;
					siter[r] = n;
					siteBound[n] = 0;

				}
				else
				{
					if (temp <= totalP - P[2] / Z/*probability_function(n, 2) / Z*/)
					{
						rmar = rmar + 1;
						sitermar[rmar] = n;
						siteBound[n] = 1;

					}
					else
					{
						rmrr = rmrr + 1;
						sitermrr[rmrr] = n;
						siteBound[n] = 2;

					}
				}


				break;
			}
			case 1:
			{
				/*cout << "e:"<<P[0]/Z <<" rmae:"<< P[1]/Z<<" rmre:" << P[2]/Z <<" amae:"<< P[3]/Z<<" amre:" << P[4]/Z<< endl;
				system("pause");*/
				empty = empty + 1;
				siteempty[empty] = n;

				uniform_real_distribution<> tempf(0, 1);
				double temp = tempf(gen);
				double tempP = 0;
				int flag = 0;
				for (int tt = 0; tt < 5; tt++)
				{
					tempP = tempP + P[tt] / Z /*probability_function(n, tt) / Z*/;
					if (temp <= tempP)
					{
						flag = tt;
						break;
					}
				}

				/*double tempPPp = 0;
				for (int j = 0; j < 5; j++)
				{
				tempPPp = probability_function(n, j) / Z + tempPPp;
				}
				if (abs(tempPPp - 1) >0.000001)
				{
				cout << tempPPp << " ";
				system("pause");
				}*/

				/*if (tempP<1 || tempP>1)
				cout << tempP << " ";*/
				switch (flag)
				{
				case 0:
				{
					e = e + 1;
					sitee[e] = n;
					siteBound[n] = 0;
					break;
				}
				case 1:
				{
					rmae = rmae + 1;
					sitermae[rmae] = n;
					siteBound[n] = 1;

					break;
				}
				case 2:
				{
					rmre = rmre + 1;
					sitermre[rmre] = n;
					siteBound[n] = 2;

					break;
				}
				case 3:
				{
					amae = amae + 1;
					siteamae[amae] = n;
					siteBound[n] = 3;

					break;
				}
				case 4:
				{
					amre = amre + 1;
					siteamre[amre] = n;
					siteBound[n] = 4;

					break;
				}
				}



				break;
			}
			case 2:
			{
				active = active + 1;
				siteactive[active] = n;

				/*double totalP = probability_function(n, 0) + probability_function(n, 3) + probability_function(n, 4);*/
				double totalP = P[0] + P[3] + P[4];
				totalP = totalP / Z;
				uniform_real_distribution<> tempf(0, totalP);
				double temp = tempf(gen);
				if (temp <= P[0]/Z /*probability_function(n, 0) / Z*/)
				{
					a = a + 1;
					sitea[a] = n;
					siteBound[n] = 0;

				}
				else
				{
					if (temp <= totalP - P[4] / Z /*probability_function(n, 4) / Z*/)
					{
						amaa = amaa + 1;
						siteamaa[amaa] = n;
						siteBound[n] = 3;

					}
					else
					{
						amra = amra + 1;
						siteamra[amra] = n;
						siteBound[n] = 4;

					}
				}
				break;
			}
			default:
				break;
			}

		}



		//here to calculate the Hs
		//for (int n = 0; n < sitesize - 1; n++)
		//{
		//	if (n>sitesize / 2 - affinitysize / 2 - 2 && n < sitesize / 2 + affinitysize / 2)//within
		//	{
		//		for (int i = 0; i < 5; i++)
		//		{
		//			for (int j = 0; j < 5; j++)
		//			{
		//				Hs = Hs + epsilonin[siteBound[n]][site[n]] - J[siteBound[n]][siteBound[n + 1]];
		//			}
		//		}
		//	}
		//	else//without
		//	{
		//		for (int i = 0; i < 5; i++)
		//		{
		//			for (int j = 0; j < 5; j++)
		//			{
		//				Hs = Hs + epsilonout[siteBound[n]][site[n]] - J[siteBound[n]][siteBound[n + 1]];
		//			}
		//		}
		//	}
		//}
		//Hs = Hs + epsilonout[siteBound[39]][site[39]];


		double totalR = (rmae + rmrr + amae + amra)*rateE + rmar*ratermaRE + rmre*ratermrER + amaa*rateamaAE + amre*rateamrEA + (active+repressive/*r + a*/)*rateARE + e*rateEAR;//modified in 8/6 to make amaa and 
		uniform_real_distribution<> tempfirstf(0, totalR);
		double tempfirst = tempfirstf(gen);
		double tempR = 0;
		int flag = 0;
		for (int i = 0; i < 1; i++)
		{
			if ((rmae + rmrr + amae + amra) > 0)
			{
				tempR = (rmae + rmrr + amae + amra)*rateE + tempR;
				if (tempfirst <= tempR)
				{
					flag = 0;
					break;
				}
			}
			if ((rmar + rmre + amaa + amre) > 0)
			{
				tempR = tempR + rmar*ratermaRE + rmre*ratermrER + amaa*rateamaAE + amre*rateamrEA;
				if (tempfirst <= tempR)
				{
					flag = 1;
					break;
				}
			}
			if ((active+repressive) > 0)
			{
				tempR = tempR + (active + repressive)*rateARE;//modified in 8/6
				if (tempfirst <= tempR)
				{
					flag = 2;
					break;
				}
			}
			if (e > 0)
			{
				tempR = tempR + e*rateEAR;
				if (tempfirst <= tempR)
				{
					flag = 3;
					break;
				}
			}
		}

		switch (flag)
		{
		case 0:
		{
			uniform_real_distribution<> tempsecond(0, rmae + rmrr + amae + amra);
			double temp2 = tempsecond(gen);
			double tempR2 = 0;
			int flag2 = 0;
			//every number is begin with 0, what is the consequence of this if I use this??
			for (int i = 0; i < 1; i++)
			{
				if (rmae > 0)
				{
					tempR2 = tempR2 + rmae;
					if (temp2 <= tempR2)
					{
						flag2 = 0;
						break;
					}
				}
				if (rmrr > 0)
				{
					tempR2 = tempR2 + rmrr;
					if (temp2 <= tempR2)
					{
						flag2 = 1;
						break;
					}
				}
				if (amae > 0)
				{
					tempR2 = tempR2 + amae;
					if (temp2 <= tempR2)
					{
						flag2 = 2;
						break;
					}
				}
				if (amra > 0)
				{
					tempR2 = tempR2 + amra;
					if (temp2 <= tempR2)
					{
						flag2 = 3;
						break;
					}
				}

			}

			switch (flag2)
			{
			case 0:
			{
				uniform_int_distribution<> tempf(1, rmae);
				int tempsite = tempf(gen);
				site[sitermae[tempsite]] = 0;
				repressivecount = repressivecount + 1;
				break;
			}
			case 1:
			{
				uniform_int_distribution<> tempf(1, rmrr);
				int tempsite = tempf(gen);
				site[sitermrr[tempsite]] = 1;
				emptycount = emptycount + 1;
				break;
			}
			case 2:
			{
				uniform_int_distribution<> tempf(1, amae);
				int tempsite = tempf(gen);
				site[siteamae[tempsite]] = 2;
				activecount = activecount + 1;
				break;
			}
			case 3:
			{
				uniform_int_distribution<> tempf(1, amra);
				int tempsite = tempf(gen);
				site[siteamra[tempsite]] = 1;
				emptycount = emptycount + 1;
				break;
			}
			}
			break;
		}
		case 1:
		{
			uniform_real_distribution<> tempsecond(0, rmar + rmre + amaa + amre);
			double temp2 = tempsecond(gen);
			double tempR2 = 0;
			int flag2 = 0;
			for (int i = 0; i < 1; i++)
			{
				if (rmar > 0)
				{
					tempR2 = tempR2 + rmar;
					if (temp2 <= tempR2)
					{
						flag2 = 0;
						break;
					}
				}
				if (rmre > 0)
				{
					tempR2 = tempR2 + rmre;
					if (temp2 <= tempR2)
					{
						flag2 = 1;
						break;
					}
				}
				if (amaa > 0)
				{
					tempR2 = tempR2 + amaa;
					if (temp2 <= tempR2)
					{
						flag2 = 2;
						break;
					}
				}
				if (amre > 0)
				{
					tempR2 = tempR2 + amre;
					if (temp2 <= tempR2)
					{
						flag2 = 3;
						break;
					}
				}
			}

			switch (flag2)
			{
			case 0:
			{
				uniform_int_distribution<> tempf(1, rmar);
				int tempsite = tempf(gen);
				site[sitermar[tempsite]] = 1;
				emptycount = emptycount + 1;
				break;
			}
			case 1:
			{
				uniform_int_distribution<> tempf(1, rmre);
				int tempsite = tempf(gen);
				site[sitermre[tempsite]] = 0;
				repressivecount = repressivecount + 1;
				break;
			}
			case 2:
			{
				uniform_int_distribution<> tempf(1, amaa);
				int tempsite = tempf(gen);
				site[siteamaa[tempsite]] = 1;
				emptycount = emptycount + 1;
				break;
			}
			case 3:
			{
				uniform_int_distribution<> tempf(1, amre);
				int tempsite = tempf(gen);
				site[siteamre[tempsite]] = 2;
				activecount = activecount + 1;
				break;
			}
			}
			break;
		}
		case 2://here I need to add amaa+amra+rmar+rmrr+r + a as 8/6
		{
			uniform_real_distribution<> tempsecond(0, active + repressive);
			if (tempsecond(gen) <= active)
			{
				if (active > 0)
				{
					uniform_int_distribution<> tempf(1, active);
					int tempsite = tempf(gen);
					site[siteactive[tempsite]] = 1;
					emptycount = emptycount + 1;
				}
			}
			else
			{
				if (repressive > 0)
				{
					uniform_int_distribution<> tempf(1, repressive);
					int tempsite = tempf(gen);
					site[siterepressive[tempsite]] = 1;
					emptycount = emptycount + 1;
				}
			}

			break;
		}
		case 3:
		{
			uniform_real_distribution<> tempff(0, 1);
			if (tempff(gen) <= 0.5)
			{
				uniform_int_distribution<> tempf(1, e);
				int tempsite = tempf(gen);
				site[sitee[tempsite]] = 0;
				repressivecount = repressivecount + 1;

			}
			else
			{
				uniform_int_distribution<> tempf(1, e);
				int tempsite = tempf(gen);
				site[sitee[tempsite]] = 2;
				activecount = activecount + 1;
			}
			break;
		}

		}


		
		if (t > 20 && tempt2 > 2)
		{
			if (activecount > repressivecount)
			{
				if (repressivescore > 0)
				{
					repressivescore = repressivescore - 1;
				}
				if (activescore < 100)
				{
					activescore = activescore + 1;
					
				}
			}
			if (repressivecount > activecount)
			{
				if (activescore > 0)
				{
					activescore = activescore - 1;
				}
				if (repressivescore < 100)
				{
					repressivescore = repressivescore + 1;
				}
			}
		}
		switch(scoreflag)
		{
			case 0:
			{
				if (repressivescore > 50)
				{
					scoreflag = 2;
					timestart = t;

				}
				if (activescore > 50)
				{
					scoreflag = 1;
					timestart = t;
				}
				break;
			}
			case 1:
			{
				if (repressivescore > 50)
				{
					switchcount = switchcount + 1;
					scoreflag = 2;
					timeaccu = timeaccu + t - timestart;
					timestart = t;
					//fout3 << t << endl;
					/*cout << activescore << " " << repressivescore <<" "<<scoreflag<<endl;
					system("pause");*/
				}
				break;
			
			}
			case 2:
			{
				if (activescore > 50)
				{
					switchcount = switchcount + 1;
					scoreflag = 1;
					timeaccu = timeaccu + t - timestart;
					timestart = t;
					//fout3 << t << endl;
					/*cout << activescore << " " << repressivescore<< " " << scoreflag << endl;
					system("pause");*/
				}
				break;
			}

		}

		uniform_real_distribution<> tempf(0, 1);//here is for the time part
		double temp = 0;
		
		do
		{
			temp = tempf(gen);
		} while (temp == 0);
		//test large deltat problem
		/*double deltat = 0;*/
		/*do
		{
			deltat = (1.0 / totalR)*log(1.0 / temp);
		} while (deltat < 0.1);*/
		double deltat = (1.0 / totalR)*log(1.0 / temp);
		//if (deltat > 0.1)
		//{
		//	cout << 1 / (/*1 / rateARE*exp(-eA+delta_epsilon) + 1 / rateARE*exp(-eA+delta_epsilon)+*/1 / rateARE*exp(-eA))<< endl;
		//	cout << 1/(1/(rateARE*exp(-eA))) << endl;
		//	cout << (repressive + active)*rateARE << endl;
		//	cout << (rmae + rmrr + amae + amra)*rateE << endl;
		//	/*cout << "rate:" << rateE*exp(eA - eGamma - delta_epsilon) << endl;
		//	cout << "math:" << exp(eA - eGamma - delta_epsilon) << endl;
		//	cout <<"t:"<< t << " empty:" << empty << " repressive:" << repressive << " active:" << active << " r:" << r << " e:" << e << " a:" 
		//		<< a << " rmre:" << rmre << " rmrr:"
		//		<< rmrr << " rmae:" << rmae << " rmar:" << rmar << " amae:" << amae << " amaa:" << amaa << " amre:" << amre << " amra:" << amra
		//		<< " Hs:" << Hs << " " << endl;
		//	cout << "E_enzyme->AR:"<<(rmae + rmrr + amae + amra)*rateE <<" AR_enzyme->E:"<<rmar*ratermaRE + rmre*ratermrER + amaa*rateamaAE + 
		//		amre*rateamrEA <<" RA->E:"<<(r + a)*rateARE <<" E->AR:"<< e*rateEAR<<endl;
		//	cout <<"deltat:"<< deltat << " temp:" << temp << " totalR:" << totalR << endl;*/
		//	system("pause");
		//}


		//cout << deltat << endl;
		if (tempt3 > 1)
		{
			fout1 << t << " " << empty << " " << repressive << " " << active << " " << r << " " << e << " " << a << " " << rmre << " "
				<< rmrr << " " << rmae << " " << rmar << " " << amae << " " << amaa << " " << amre << " " << amra << " " << Hs << " " << endl;
			for (int i = 0; i < sitesize; i++)
			{
				/*double tempPP = 0;
				for (int j = 0; j < 5; j++)
				{
				tempPP = P[j] / Z + tempPP;
				}
				if (abs(tempPP - 1) >0.000001)
				{
				cout << tempPP << " ";
				system("pause");
				}*/
				fout2 << site[i] << " ";
			}
			fout2 << endl;
			tempt3 = 0;
		}
		if (tempt1 >= 2000)
		{
			tempt1 = 0;
			/*cout << "time:" << t << " empty:" << empty << " repressive:" << repressive << " active:" << active << " e:" << e <<
				" r:" << r << " a:" << a << endl;*/
			cout << t <<" "<<switchcount<< endl;

			/*for (int n = 0; n < sitesize; n++)
			{
				cout << site[n] << " ";

			}
			cout << endl;*/
		}

		if (tempt2 >= 20)
		{
			tempt2 = 0;

			for (int nn = 0; nn < sitesize; nn++)
			{
				uniform_real_distribution<> temp2f(0, 1);
				if (temp2f(gen) <= 0.5)
				{
					site[nn] = 1;
					//emptycount = emptycount + 1;
				}

			}
			//cout << "refresh" << endl;
		}
		





		t = t + deltat;
		tempt1 = tempt1 + deltat;
		tempt2 = tempt2 + deltat;
		tempt3 = tempt3 + deltat;

	}





	////This part is for test the matrix multiply
	//double a[5][5] = { 1,0.1,0.1,0.1,0.1,
	//	               0.1,1,0.1,0.1,0.1,
	//				   0.1,0.1,1,0.1,0.1,
	//				   0.1,0.1,0.1,1,0.1,
	//				   0.1,0.1,0.1,0.1,1};
	//double b[5][5] = { 1, 0.1, 0.1, 0.1, 0.1,
	//				   0.1, 1, 0.1, 0.1, 0.1,
	//				   0.1, 0.1, 1, 0.1, 0.1,
	//				   0.1, 0.1, 0.1, 1, 0.1,
	//				   0.1, 0.1, 0.1, 0.1, 1 };
	//double c[5][5] = {};
	//matrix_multiply(a, b, c);
	//for (int i = 0; i < 5; i++)
	//{
	//	for (int j = 0; j < 5; j++)
	//	{
	//		cout << c[i][j]<<' ';
	//	}
	//	cout << endl;
	//}
	timeavg = timeaccu / double(switchcount);
	fout3 << timeavg << endl;


	cout << timeaccu << " " << timeavg << endl;
	//system("pause");
	
	fout1.close();
	fout2.close();
	fout3.close();
	return 0;
}


int output()
{
	for (int i = 0; i<sitesize; i++)
	{
		cout << site[i]<<" ";
	}
	cout << endl;
	cout << "epsilon out matrix" << endl;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << epsilonout[i][j]<<' ';
		}
		cout << endl;
	}
	cout << "epsilon in matrix" << endl;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << epsilonin[i][j] << ' ';
		}
		cout << endl;
	}

	cout << endl;
	//system("pause");
	return 0;
}

int matrix_multiply(double a[5][5], double b[5][5],double c[5][5])
{

	double cc[5][5] = {};
		for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			for (int k = 0; k < 5; k++)
			{
				cc[i][j] = cc[i][j]+a[i][k] * b[k][j];
			}
		}
	}
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				c[i][j] = cc[i][j];
			}
		}
	return 0;
}



int int_T_matrix()
{

	for (int n = 0; n < sitesize - 1; n++)
	{
		if (n >= sitesize / 2 - affinitysize / 2.0 && n < sitesize / 2 + affinitysize / 2.0)//within
		{
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					T[n][i][j] = exp((-1.0 / 2.0) * (epsilonin[i][site[n]] + epsilonin[j][site[n + 1]]) + J[i][j]);
				}
			}
		}
		else//without
		{
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					T[n][i][j] = exp((-1.0 / 2.0) * (epsilonout[i][site[n]] + epsilonout[j][site[n + 1]]) + J[i][j]);
				}
			}
		}
	}
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			T[sitesize - 1][i][j] = exp((-1.0 / 2.0) * (epsilonout[i][site[sitesize - 1]] + epsilonout[j][site[0]]));
			//cout << T[sitesize-1][i][j] << endl;
		}
	}



	////this functino works to initial matrix T
	//if (k>sitesize/2-7 && k < sitesize/2+5)
	//{
	//	for (int n = 0; n < sitesize-1; n++)
	//	{
	//		for (int i = 0; i < 5; i++)
	//		{
	//			for (int j = 0; j < 5; j++)
	//			{
	//				T[n][i][j] = exp((-1.0 / 2.0) * (epsilonin[i][site[n]] + epsilonin[j][site[n + 1]]) + J[i][j]);
	//			}
	//		}
	//	}

	//	for (int i = 0; i < 5; i++)
	//	{
	//		for (int j = 0; j < 5; j++)
	//		{
	//			T[sitesize-1][i][j] = exp((-1.0 / 2.0) * (epsilonin[i][site[sitesize-1]] + epsilonin[j][site[0]]));
	//			//cout << T[sitesize-1][i][j] << endl;
	//		}
	//	}
	//	
	//}
	////outside nucleation region 1-15&25-sitesize
	//else
	//{
	//	for (int n = 0; n < sitesize-1; n++)// i might modify here to see if the output T matrix is right
	//	{
	//		//cout << "this is " << site[n] << " next is " << site[n + 1] << endl;
	//		//cout << "epsilon matrix" << endl;
	//		//for (int i = 0; i < 5; i++)
	//		//{
	//		//	for (int j = 0; j < 3; j++)
	//		//	{
	//		//		cout << epsilonout[i][j] << ' ';
	//		//	}
	//		//	cout << endl;
	//		//}
	//		//cout << endl;
	//		for (int i = 0; i < 5; i++)
	//		{
	//			for (int j = 0; j < 5; j++)
	//			{
	//				T[n][i][j] = exp((-1.0 / 2.0) * (epsilonout[i][site[n]] + epsilonout[j][site[n + 1]]) + J[i][j]);
	//				//cout << i << " " << j << " " << (epsilonout[i][site[n]] )  << endl;
	//			}
	//		}
	//	}

	//	for (int i = 0; i < 5; i++)
	//	{
	//		for (int j = 0; j < 5; j++)
	//		{
	//			T[sitesize-1][i][j] = exp((-1.0 / 2.0) * (epsilonout[i][site[sitesize-1]] + epsilonout[j][site[0]]));
	//			//cout << (-1.0 / 2.0) * (epsilonout[i][site[sitesize-1]] + epsilonout[j][site[0]]) << endl;
	//		}
	//	}
	//}


	///*for (int nn = 0; nn < sitesize; nn++)
	//{
	//	cout << "for matrix " << nn << endl;
	//	for (int i = 0; i < 5; i++)
	//	{
	//		for (int j = 0; j < 5; j++)
	//		{
	//			cout << T[nn][i][j] << ' ';
	//		}
	//		cout << endl;
	//	}

	//}
	//*/
	



	return 0;

}

double partition_function()
{
	
	//within nucleation region 15-25
	
	//For partition function:Z
	double tempZ = 0;;
	double tempT[5][5] = {};
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			tempT[i][j] = T[0][i][j];
		}
	}
	/*cout << "test matrix " << 0 << endl;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cout << tempT[i][j] << ' ';
		}
		cout << endl;
	}*/
	for (int n = 0; n < sitesize-1; n++)//multiply by n and n+1, so the max is sitesize-1
	{
		matrix_multiply(tempT, T[n + 1], tempT);

		/*cout << "test matrix " <<n<< endl;
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				cout << tempT[i][j] << ' ';
			}
			cout << endl;
		}*/


	}

	// For Trace of Matrix
	for (int i = 0; i < 5; i++)
	{
		tempZ = tempT[i][i] + tempZ;
	}
	
	return tempZ;
}

double probability_function(int n,int state)//n for i in the paper,state for sigma_i
{
	double P = 0;
	//first for G
	double G[5][5] = {};
	double tempT[5][5] = {};
	if (n == 0)
	{
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				G[i][j] = T[sitesize-1][i][state] * T[0][state][j];//modified
				tempT[i][j] = G[i][j];
			} 
		}
	}
	else
	{
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				G[i][j] = T[n - 1][i][state] * T[n][state][j];
			}
		}
	}
	//claculation of G finished


	if (n == 1)
	{
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				//tempT[i][j] = T[0][i][j];
				tempT[i][j] = G[i][j];
			}
		}
	}
	if (n > 1)
	{
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				tempT[i][j] = T[0][i][j];
			}
		}
		for (int nn = 1; nn <= n - 2; nn++)//modified not sure
		{
			matrix_multiply(tempT, T[nn], tempT);

			/*cout << "test matrix " << nn << endl;
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					cout << tempT[i][j] << ' ';
				}
				cout << endl;
			}*/

		}
	}
	//here multiply by matrix G only in the case that n>1;
	if (n>1)
		matrix_multiply(tempT, G, tempT);
	

	if (n == 0)
	{
		for (int nn = n; nn < sitesize - 2; nn++)//problems here
		{
			matrix_multiply(tempT, T[nn + 1], tempT);

		}
	}
	else
	{
		for (int nn = n; nn < sitesize - 1; nn++)// here i use sitesize-1, there might be a problem 
		{
			matrix_multiply(tempT, T[nn + 1], tempT);

			/*cout << "test matrix " << nn << endl;
			for (int i = 0; i < 5; i++)
			{
			for (int j = 0; j < 5; j++)
			{
			cout << tempT[i][j] << ' ';
			}
			cout << endl;
			}*/
		}
	}
	//for trace
	for (int i = 0; i < 5; i++)
	{
		P = tempT[i][i] + P;
	}
	//cout << P << endl;
	//cout << partition_function() << endl;
	//P = (float)P / partition_function();
	//cout << P << endl;
	
	return P;
}
