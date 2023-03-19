#include <iostream>
#include <ctime>
#include <random>
using namespace std;

struct memory {
	double length;
	int way[5];
};
double* generator() {
	normal_distribution<double> inter(0,0.25);
	default_random_engine e(time(0));
	int data[10];
	double corrupteddata[10];
	int grid[2][4][4]{ {{1,0,0,1},{0,1,1,0},{0,1,1,0},{1,0,0,1}},{{1,1,0,0},{1,1,0,0},{0,0,1,1},{0,0,1,1} } };
	int i = 0;
	srand(time(0));
	int buff;
	double dbuff;
	buff = rand() % 4;
	data[0] = buff;
	for (i = 0; i < 5; i++) {
		buff = rand() % 4;
		if (grid[i % 2][data[i]][buff] == 0) {
			i = i - 1;
			continue;
		}
		else {
			data[i + 1] = buff;
		}
	}
	for (i = 0; i < 5; i++) {
		cout << data[i]+1 << " ";
	}
	cout << endl<<endl;
	for (i = 0; i < 5; i++) {
		dbuff = data[i] + inter(e);
		if (dbuff < 0) {
			dbuff = 3 + dbuff;
		}
		corrupteddata[i] = ((int)(dbuff)%4)+(dbuff-(int)(dbuff));
		cout << corrupteddata[i] + 1 << " ";
	}
	cout << endl << endl;
	return corrupteddata;
}
double **identificator(double *recieve) {
	int i = 0, j=0;
	double **track = new double*[5];
	for (i = 0; i < 5; i++) {
		track[i] = new double[4];
	}
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 4; j++)
			track[i][0]=min<double>(recieve[i],abs(recieve[i]-4));
			track[i][1] = min<double>(abs(recieve[i] - 1), abs(1-recieve[i])) ;
			track[i][2] = min<double>(abs(recieve[i] - 2),abs(2-recieve[i])) ; 
			track[i][3] =  min<double>(min<double>(abs(recieve[i] - 3), abs(3-recieve[i])),recieve[i]+1);
	}
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 4; j++) {
			cout << track[i][j]<< " ";
		}
		cout << endl;
	}
	return track;
}
int step(double ** track, int start, int n_step, memory *a, static int& last, double temp_l) {
	int grid[2][4][4]{ {{1,0,0,1},{0,1,1,0},{0,1,1,0},{1,0,0,1}},{{1,1,0,0},{1,1,0,0},{0,0,1,1},{0,0,1,1} } };
	int i = 0;
	for (i = 0; i < 4; i++) {
		if (grid[n_step%2][start][i]) {
			a[0].way[n_step] = i;
			if (n_step == 3) {
				a[last].length = temp_l + track[n_step+1][i];
				copy(begin(a[0].way), end(a[0].way), begin(a[last].way));
				last++;
				continue;
			}
			step(track, i, n_step+1, a, last, temp_l + track[n_step+1][i]);
		}
		
	}
	return 0;
}

int main() {
	int grid[2][4][4]{ {{1,0,0,1},{0,1,1,0},{0,1,1,0},{1,0,0,1}},{{1,1,0,0},{1,1,0,0},{0,0,1,1},{0,0,1,1} } };
	double **track;
	int start;
	double buff;
	int t[8][8] = { 0 };
	int i = 0, n_step = 0;
	track = identificator(generator());
	for (i = 0; i < 4; i++) {
		if (track[0][i] == min({ track[0][0],track[0][1],track[0][2],track[0][3] })) {
			start = i;
		};
	}
	memory a[1000];
	static int last = 1;
	step(track, start, n_step,a,last,track[0][start]);
	for (i = 1; i < last; i++) {
		cout << endl;
		cout << a[i].length << " ";
		for (n_step = 0; n_step < 4; n_step++) {
			cout << a[i].way[n_step] + 1 << " ";
		}
	};
	buff = a[1].length;
	n_step = 1;
	for (i = 1; i < last; i++) {
		if (buff > a[i].length) {
			buff = a[i].length;
			n_step = i;
		}
	}

	cout<< endl << start+1 << " ";
	for (i = 0; i < 4; i++) {
		cout << a[n_step].way[i]+1<<" ";
	}
	return 0;
}
