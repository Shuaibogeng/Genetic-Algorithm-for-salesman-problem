#include <iostream>
#include <stdlib.h> 
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>

using namespace std;

double getDistance2D( double tempMatrix[2][2] )
{
	// calculate the distance between 2 2D points.
	return sqrt(pow((tempMatrix[1][0]-tempMatrix[0][0]),2)+pow((tempMatrix[1][1]-tempMatrix[0][1]),2));
}

void printVec1D(vector<int>& pvec)
{
	// print an int 1D vector in a row.
	for(int i=0; i<=pvec.size()-1; ++i)
	{
		cout << pvec[i] << " ";
	}

	cout << "\n";	
}

void printDoubleVec1D(vector<double> pvec)
{
	// print an int 1D vector in a row.
	for(int i=0; i<=pvec.size()-1; ++i)
	{
		cout << pvec[i] << " ";
	}

	cout << "\n";	
}

vector<int> getRandomVec1D(int veclen)
{
	// generate a random non-repeating vector.

	// generate a vector in order.
	vector<int> pathvec(veclen);
	for(int i=0; i<veclen; ++i)
	{
		pathvec[i]=i+1;
		
	}

	// change the order of the vector.
	for(int i=veclen-1; i>=1; --i)
	{
		srand(time(0)+rand()); // to make sure the random number varies in each iteration
		swap(pathvec[i],pathvec[rand()%i]);
		// cout << rand() << rand()%i << endl;
	}

	return pathvec;


}



vector<int> findMissing1D(vector<int> fmvec)
{
	// find missing number for non-zero vector.
	// return the missing number list
	vector<int> fmvec01 = fmvec;
	for(int i=0; i<fmvec01.size(); i++)
	{
		fmvec01[abs(fmvec01[i])-1] = -abs(fmvec01[abs(fmvec01[i])-1]);
		// printVec1D(fmvec01);
	}

	vector<int> fmfind;
	for (int j=0; j<fmvec01.size(); j++)
	{
		if(fmvec01[j]>0)
			fmfind.push_back(j+1);
	}
	return fmfind;
}

vector<int> findMissingFrom1D(vector<int> p01, vector<int> o01)
{
	vector<int> missinglist01;
	for(int j=0; j<p01.size(); j++)
	{
		if(std::find(o01.begin(), o01.end(), p01[j])== o01.end())
		{
			missinglist01.push_back(p01[j]);
		}
	}

	return missinglist01;
}

vector<int> findRepeat1D(vector<int>& frvec)
{
	// find repeat number in a vector
	// return the index of the repeat numbers
	vector<int>& frvec01 = frvec;
	vector<int> frindex;

	for(int i=0; i<frvec01.size()-1; ++i)
	{
		for(int j=i+1; j<frvec01.size(); ++j)
		{
			if(frvec01[i]==frvec01[j])
			{
				frindex.push_back(j);
				break;
			}
		}
	}
	sort(frindex.begin(), frindex.end());
	return frindex;
}

vector<vector<int> > crossover(vector<int> p01, vector<int> p02)
{
	// take partially mapped crossover (PMX) method with 1 cut point
	int memberlen=p01.size();
	vector<vector<int> > offspring(2, vector<int>(memberlen));

	// generate the random cut point
	// srand(time(0)+rand());
	// int randomPoint = rand()%(p01.size()-1);
	int randomPoint=3;

	// keep p01 string after the cut point, and take p02 string before the cut point
	vector<int> o01=p01;
	for(int i=0; i<=randomPoint; i++)
	{
		o01[i]=p02[i];
	}
	// printVec1D(o01);
	
	// find the repeating point index and the missing numbers
	vector<int> changingpoints=findRepeat1D(o01);
	vector<int> missinglist=findMissingFrom1D(p01,o01);

	//put the missing numbers at repeating points
	for(int i=0; i<changingpoints.size(); i++)
	{
		o01[changingpoints[i]]=missinglist[i];
	}
	// printVec1D(o01);
	changingpoints.clear();
	missinglist.clear();
	for(int i=0; i<p01.size(); i++)
	{
		offspring[0][i]=o01[i];
	}


	vector<int> o02=p02;
	for(int i=0; i<=randomPoint; i++)
	{
		o02[i]=p01[i];
	}
	changingpoints=findRepeat1D(o02);
	missinglist=findMissingFrom1D(p02,o02);
	for(int i=0; i<changingpoints.size(); i++)
	{
		o02[changingpoints[i]]=missinglist[i];
	}
	// printVec1D(o02);
	changingpoints.clear();
	missinglist.clear();
	for(int i=0; i<p01.size(); i++)
	{
		offspring[1][i]=o02[i];
	}

	return offspring;
}



vector<vector<int> > creatRandomGroup(int groupsize, int memberlen)
{
	// creat a random group
	// return a 2D vector
	vector<vector<int> > group(groupsize, vector<int>(memberlen));
	for(int i=0; i<groupsize; i++)
	{
		vector<int> tempnumber=getRandomVec1D(8);
		for(int j=0; j<memberlen; j++)
		{
			group[i][j]=tempnumber[j];
		}
	}
	return group;
}

double getPathLength(vector<vector<double> > distanceMatrix01, vector<int> path01)
{
	// get the total length for a path
	double totalLength = 0.;
	for(int i=0; i<path01.size()-1; i++)
	{
		totalLength = totalLength+distanceMatrix01[path01[i]-1][path01[i+1]-1];
		// cout << vectest[i] << " " << vectest[i+1] << endl;
	}
	return totalLength;
}

vector<double> getFitnessList(vector<vector<double> > distanceMatrix01, vector<vector<int> > originalgroup)
{
	// get the fitness list for a group vector
	// the fitness is 1/pathlength
	vector<vector<int> > tempgroup01=originalgroup;
	vector<double> fitnesslist;
	for(int i=0; i<tempgroup01.size(); i++)
	{
		double fitness01=1.0/getPathLength(distanceMatrix01, tempgroup01[i]);
		fitnesslist.push_back(fitness01);
	}
	return fitnesslist;
}

void getBestPath(vector<vector<double> > distanceMatrix01, vector<vector<int> > originalgroup, vector<double> fitnesslist)
{
	// get the best (shortest) path
	vector<vector<int> > tempgroup01=originalgroup;
	int maxindex=max_element(fitnesslist.begin(),fitnesslist.end())-fitnesslist.begin();
	double bestpathlen= getPathLength(distanceMatrix01, tempgroup01[maxindex]);
	cout << "The best path for now is "  <<endl;
	printVec1D(tempgroup01[maxindex]);
	cout << "The length of the best path for now is " << bestpathlen << "." <<endl;
}

vector<vector<int> > halfSelection(vector<vector<int> > originalgroup, vector<double> fitnesslist)
{
	// keep the top half members, and abandon the last half ones
	vector<vector<int> > tempgroup01=originalgroup;
	vector<vector<int> > tempgroup02(originalgroup.size(), vector<int>(originalgroup[0].size()));
	// vector<double> fitnesslist;
	vector<double> tempfitnesslist01;
	vector<int> toplist((originalgroup.size()/2),0);
	// vector<int> emptymember(row,0);

	// for(int i=0; i<tempgroup01.size(); i++)
	// {
	// 	double fitness01=1.0/getPathLength(distanceMatrix01, tempgroup01[i]);
	// 	fitnesslist.push_back(fitness01);
	// }
	// printDoubleVec1D(fitnesslist);

	// find the index of the top half
	tempfitnesslist01=fitnesslist;
	for(int j=0; j<(originalgroup.size()/2); j++)
	{
		int maxindex=0;
		maxindex=max_element(tempfitnesslist01.begin(),tempfitnesslist01.end())-tempfitnesslist01.begin();
		toplist[j]=maxindex;
		tempfitnesslist01[maxindex]=0.;
	}
	// printVec1D(top20list);
	for(int k=0; k<(originalgroup.size()/2); k++)
	{
		tempgroup02[k]=originalgroup[toplist[k]];

	}
	return tempgroup02;
}

// vector<vector<int> > getSelectedGroup(vector<vector<double> > distanceMatrix01, vector<vector<int> > originalgroup, int elitesize)
// {
// 	// selection method: select top 20 members and copy them, and abandon the last 20 ones
// 	vector<vector<int> > tempgroup01=originalgroup;
// 	vector<vector<int> > tempgroup02=originalgroup;
// 	vector<double> fitnesslist;
// 	vector<double> tempfitnesslist01;
// 	vector<int> top20list;
// 	vector<int> last20list;

// 	for(int i=0; i<tempgroup01.size(); i++)
// 	{
// 		double fitness01=1.0/getPathLength(distanceMatrix01, tempgroup01[i]);
// 		fitnesslist.push_back(fitness01);
// 	}
// 	// printDoubleVec1D(fitnesslist);
// 	tempfitnesslist01=fitnesslist;
// 	for(int j=0; j<elitesize; j++)
// 	{
// 		int maxindex=0;
// 		maxindex=max_element(tempfitnesslist01.begin(),tempfitnesslist01.end())-tempfitnesslist01.begin();
// 		top20list.push_back(maxindex);
// 		tempfitnesslist01[maxindex]=0.;
// 	}

// 	for(int k=0; k<elitesize; k++)
// 	{
// 		int minindex=0;
// 		minindex=min_element(fitnesslist.begin(),fitnesslist.end())-fitnesslist.begin();
// 		tempgroup02[minindex]=tempgroup02[top20list[k]];
// 		fitnesslist[minindex]=fitnesslist[top20list[k]];
// 	}
// 	return tempgroup02;
// }



vector<int> getMutation(double pmutation, vector<int> path01)
{
	// each offspring has the possiblity(pmutation) to mutate
	vector<int> tempvec1=path01;
	srand(time(0)+rand());
	int random01=rand()%100;
	if(random01<=100*pmutation)
	{
		int randompoint01=rand()%(path01.size());
		int randompoint02=rand()%(path01.size());
		swap(tempvec1[randompoint01],tempvec1[randompoint02]);
	}
	return tempvec1;
}



int main()
{
	int row=8;
	int groupSize=128;
	double pmutation=0.05;
	int iterationnumber=200;
	double pos01[8][2]={{0., 0.}, {3., 4.}, {1., 1.}, {5., 5.}, {6., 6.}, {2., 2.}, {7.,8.}, {4.,13.}}; // initialize the position list

	// initialize a new vector to store postion
	vector<vector<double> > posVec(row, vector<double>(2));
	// initialize a new vector to store distance matrix
	vector<vector<double> > distanceMatrix(row, vector<double>(row));
	

	// set positions
	for(int i=0; i<posVec.size(); i++)
	{
		for(int j=0;j<posVec[i].size(); j++)
		{
			posVec[i][j]=pos01[i][j];
		}
	}	

	// calculate distance matrix
	double vectemp01[2][2];
	for(int i=0; i<posVec.size(); i++)
	{
		vectemp01[0][0] = posVec[i][0];
		vectemp01[0][1] = posVec[i][1];
		for(int j=0;j<posVec.size(); j++)
		{
			vectemp01[1][0] = posVec[j][0];
			vectemp01[1][1] = posVec[j][1];
			distanceMatrix[i][j]=getDistance2D(vectemp01);
		}
	}

	// creat the inital group
	vector<vector<int> > group = creatRandomGroup(groupSize, row);

	// check the best path for now
	vector<double> fitnesslist=getFitnessList(distanceMatrix, group);
	getBestPath(distanceMatrix, group, fitnesslist);
	
	// do iteration
	for(int m=0; m<=iterationnumber; m++)
	{
		
		// do selection
		vector<vector<int> > tempgroup01=halfSelection(group, fitnesslist);

		// do crossover and mutation
		for(int i=0; i<(group.size()/2); i=i+2)
		{
			// printVec1D(tempgroup01[i+(group.size()/2)]);
			tempgroup01[i+(group.size()/2)]=crossover(tempgroup01[i], tempgroup01[i+1])[0];
			tempgroup01[i+(group.size()/2)]=getMutation(pmutation, tempgroup01[i+(group.size()/2)]);
			tempgroup01[i+(group.size()/2)+1]=crossover(tempgroup01[i], tempgroup01[i+1])[1];
			tempgroup01[i+(group.size()/2)+1]=getMutation(pmutation, tempgroup01[i+(group.size()/2)+1]);
		}

		// new group replaces the old one
		group=tempgroup01;


		// check the best path for each 10 interation
		if(m%10==0)
		{
			cout<< "Iteration: " << m <<endl;
			fitnesslist=getFitnessList(distanceMatrix, group);
			getBestPath(distanceMatrix, group, fitnesslist);
			// cout << group.size() << endl;
		}
	}
	
	// vector<int> p01={3,6,1,2,4,8,5,7};
	// vector<int> p02={7,2,8,3,5,1,4,6};

	// vector<int> o01=crossover(p01, p02)[0];
	// vector<int> o02=crossover(p01, p02)[1];
	
	// printVec1D(o01);
	// printVec1D(o02);


	// // vector<int> c01;
	
	// // for(int j=0; j<p02.size(); j++)
	// // {
	// // 	if(std::find(p01.begin(), p01.end(), p02[j])== p01.end())
	// // 	{
	// // 		c01.push_back(p02[j]);
	// // 	}
	// // }

	// // printVec1D(c01);


	return 0;
}