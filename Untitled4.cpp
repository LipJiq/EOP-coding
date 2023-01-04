#include <iostream>
#include <iomanip>

using namespace std;

void display(string name[5], int record[5][8]);
void calc(string name[5], int record[5][8]);
double highestScore (int record[]);
int main()
{
	string name[5] = {"Maryam", "Khairul", "Najla", "Sofea", "Iskandar"};
	int record[5][8] = {{120, 60,110, 65, 101, 80, 95, 88},
						{150, 70, 130, 72, 120, 74, 90, 92
						},
						{200, 72, 140, 74, 132, 75, 110, 86
						},
						{170, 82, 132, 86, 124, 85, 105, 90},
						{180, 62, 171, 70, 110, 80, 92, 85
						}};

	display(name, record);
	calc(name, record);
return 0;
}

void display(string name[5], int record[5][8])
{
	cout << "\nTrainee\t\t Time\t Score\t Time\t Score\t Time\t Score\t Time\t Score\n";
	
	for(int i = 0; i < 5; i++){
		cout << left << setw(15) << name[i] << "\t ";
		
		for(int j = 0; j < 8 ; j += 2){
			cout << record[i][j] << "\t ";
			cout <<  record[i][j+1] << "\t ";	
		}
		
		cout << endl;
	}
	
}

void calc(string name[5], int record[5][8])
{
	double averageTime[5];
	double averageScore[5];
	int totalScore;
	int totalTime;
	
	for(int i = 0; i < 5; i++){
		totalScore = 0;
		totalTime = 0;
		
		for(int j = 0; j < 8 ; j += 2){
			totalScore += record[i][j];	
			totalTime += record[i][j+1];
		}
		
		averageTime[i] = totalTime / 4.0;
		averageScore[i] = totalScore / 4.0;
	}
	
	cout << "\nParticipant\tAverage Time\t Average Calories\t Highest Calories Burned\n";
	for(int i = 0; i < 5; i++){
		cout << setw(15) << left << name[i] << "\t ";
		cout << fixed << showpoint;
		cout << setprecision(2) << averageTime[i] << "\t\t "
		 	 << averageScore[i] << "\t\t "
		  	 << highestScore(record[i])
		 	 << endl;
		
	}
}

double highestScore (int record[])
{
	int highest = record[1];
	
		for(int j = 3; j < 8 ; j += 2){
			if (highest <= record[j])
			highest = record[j];
		}
		
	return static_cast<double>(highest);
}
