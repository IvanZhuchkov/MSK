#include <iostream>
#include <ctime>
#include <random>
using namespace std;

struct memory {
	double length;
	int way[6];
};
struct signal {
	int fre;
	double x;
	double y;
};
double scal(signal a, signal b) {
	double r = a.x * b.x + a.y * b.y;
	return r;
}
double *indef(signal r) {
	signal a, b, c, d;
	a.x = 0;
	a.y = 1;
	b.x = 1;
	b.y = 0;
	c.x = 0;
	c.y = -1;
	d.x = -1;
	d.y = 0;
	double *buff=new double[4];
	buff[0] = scal(r, a);
	buff[1] = scal(r, b);
	buff[2] = scal(r, c);
	buff[3] = scal(r, d);
	return buff;
}
signal* generator() {
	normal_distribution<double> inter(0,0.5);
	default_random_engine e(time(0));
	signal data[10];
	signal *corrupteddata=new signal[10];
	int grid[2][4][4]{ {{1,0,0,1},{0,1,1,0},{0,1,1,0},{1,0,0,1}},{{1,1,0,0},{1,1,0,0},{0,0,1,1},{0,0,1,1} } };
	int i = 0;
	srand(time(0));
	int buff;
	double dbuff;
	buff = rand() % 4;
	data[0].fre = buff;
	for (i = 0; i < 9; i++) {
		buff = rand() % 4;
		if (grid[i % 2][data[i].fre][buff] == 0) {
			i = i - 1;
			continue;
		}
		else {
			data[i + 1].fre = buff;
		}
	}
	for (i = 0; i < 10; i++) {
		cout << data[i].fre+1 << " ";
	}
	cout << endl<<endl;
	for (i = 0; i < 10; i++) {
		if (data[i].fre == 0) {
			data[i].x = 0;
			data[i].y = 1;
		}
		if (data[i].fre == 1) {
			data[i].x = 1;
			data[i].y = 0;
		}
		if (data[i].fre == 2) {
			data[i].x = 0;
			data[i].y = -1;
		}
		if (data[i].fre == 3) {
			data[i].x = -1;
			data[i].y = 0;
		}
	}
	for (i = 0; i < 10; i++) {
		corrupteddata[i].x = data[i].x + inter(e);
		corrupteddata[i].y = data[i].y + inter(e);
		dbuff = sqrt(corrupteddata[i].x * corrupteddata[i].x + corrupteddata[i].y * corrupteddata[i].y);
		corrupteddata[i].x = corrupteddata[i].x / dbuff;
		corrupteddata[i].y = corrupteddata[i].y / dbuff;
		cout << corrupteddata[i].x << " "<< corrupteddata[i].y<<"  ";
	}
	cout << endl << endl;
	return corrupteddata;
}
int s_msk(signal* recieve) {
	int i=0,j=0;
	double* buff = new double[4];
	for (i = 0; i < 10; i++) {
		buff = indef(recieve[i]);
		for (j = 0; j < 4; j++) {
			if (buff[j] == max({ buff[0], buff[1], buff[2], buff[3] })) {
				cout << j + 1 <<" "<< buff[0] << " " << buff[1] << " " << buff[2] << " " << buff[3] << endl;
			}
		}
	}
	cout << endl;
	return 0;
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
memory **n_msk(signal * recieve, int i, memory **a) {
	int grid[2][4][4]{ {{1,0,0,1},{0,1,1,0},{0,1,1,0},{1,0,0,1}},{{1,1,0,0},{1,1,0,0},{0,0,1,1},{0,0,1,1} } };
	int j=0,k=0,s=0;
	int b[2];
	double **buff=new double*[6];
	for (i = 1; i < 6; i++) {
		buff[i - 1] = indef(recieve[i - 1]);
		buff[i - 1][0] = buff[i - 1][0] + a[i-1][0].length;
		buff[i - 1][1] = buff[i - 1][1] + a[i-1][1].length;
		buff[i - 1][2] = buff[i - 1][2] + a[i-1][2].length;
		buff[i - 1][3] = buff[i - 1][3] + a[i-1][3].length;
		cout << endl<<buff[i-1][0]<<endl;
		for (j = 0; j < 4; j++) {
			for (k = 0; k < 4; k++) {
				if (grid[(i - 1) % 2][k][j]) {
					b[s] = k;
					s++;
				}
			}
			s = 0;
			if (buff[i-1][b[0]] > buff[i-1][b[1]]) {
				cout << b[0] + 1 << "<- " << j + 1 << endl;
				a[i][j].length = buff[i-1][b[0]];
				cout << a[i][j].length << endl;
				for (k = 0; k < i; k++) {
					a[i][j].way[k] = a[i - 1][b[0]].way[k];
				}
				a[i][j].way[i] = b[0];
				
			}
			else {
				cout << b[1] + 1 << "<- " << j + 1 << endl;
				a[i][j].length = buff[i-1][b[1]];
				for (k = 0; k < i; k++) {
					a[i][j].way[k] = a[i - 1][b[1]].way[k];
				}
				a[i][j].way[i] = b[1];
				cout << a[i][j].length << endl;
			}

		}
	}
	return a;
}
int step(double ** track, int start, int n_step, memory *a, int& last, double temp_l) {
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
	double buff;
	signal* recieve;
	int i = 0, n_step = 0;
	memory **a = new memory*[6];
	for (i = 0; i < 6; i++) {
		a[i] = new memory[4];
	}
	memory **b;
	a[0][0].length = 0;
	a[0][1].length = 0;
	a[0][2].length = 0;
	a[0][3].length = 0;
	recieve = generator();
	s_msk(recieve);
	b=n_msk(recieve,1,a);
	buff = b[5][0].length;
	n_step = 0;
	for (i = 1; i < 6; i++) {
		if (buff < b[3][i].length) {
			buff = b[3][i].length;
			n_step = i;
		}
	}
	for (i = 1; i < 6; i++) {
		cout << b[5][n_step].way[i]+1 << " ";
	}
	/*for (i = 0; i < 4; i++) {
		if (track[0][i] == min({ track[0][0],track[0][1],track[0][2],track[0][3] })) {
			start = i;
		};
	}
	memory a[1000];
	int last = 1;
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
	}*/
	return 0;
}
