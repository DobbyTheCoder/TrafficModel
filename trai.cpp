/*
cpp file for the function definitions
declared in trai.h
*/

#include "trai.h"
#include<unistd.h>
using namespace std;

lane :: lane(){
	start = 0;
	end = 0;
	avgWait = 0;
	sum = 0;
}

int lane :: isfull(){
	if(end < maxCars)
		return 0;

	else if(end == maxCars && start > 0)
		return 2;

	else if(end+1 == start)
		return 1;
	else 
		return 1;
}

int lane :: isEmpty(){
	if(start == end)
		return 0;

	else if(start == maxCars && end > 0){
		end = 0;
		return 1;
	}

	else if(start < end || end < start)
		return 1;

	else
		return 0;
}

void lane :: ins(){
	int var0;
	var0 = isfull();
	if(var0 == 0){
		Car *a =  new Car[1];
	   	cars[end] = *a;
	    end++;
	}
	/*else{
		cout<<"Buffer Overflow"<<endl;
	}*/
}

void lane :: del(){
	int var0;
	var0 = isEmpty();
	if(var0 == 1){
		start++;
	}

	else if(var0 == 2)
		start = 0;

	//else if (var0 == 0)
	//	cout<<"Buffer Underflow"<<endl;
}

void lane :: inc_wait(){
	int i;

	if(start < end){
		for(i = start; i < getOccupied(); i++){
		cars[i].waitTime++;
		}
	}

	else if(end < start){
		for(i = start; i < maxCars ; i++){
			cars[i].waitTime++;
		}
		for(i = 0; i <= end; i++){
			cars[i].waitTime++;
		}
	}
}

int lane :: getWait(int random){
	return cars[random].waitTime;
}

int lane :: getOccupied(){
	return (end - start);
}

void Lane :: insertMultiple(int insNum)
{
	int i;
	for(i = 0; i < insNum; i++)
		ins();
}

void Lane :: deleteMultiple(int delNum){
	int i;
	for(i = 0; i < delNum; i++)
		del();
}

void Lane :: find_avgWait(){
	int i;

	if(start < end){
		for(i = start; i < getOccupied(); i++){
		sum += cars[i].waitTime;
		}

		avgWait = (float)sum/getOccupied();
	}

	else if(end < start){
		for(i = start; i < maxCars ; i++){
			avgWait += cars[i].waitTime;
			cout<<avgWait<<endl;
		}
		for(i = 0; i <= end; i++){
			avgWait += cars[i].waitTime;
			cout<<avgWait<<endl;
		}

		avgWait = avgWait/((maxCars-1-start) + end);
	}
}

float Lane :: get_avgWait(){
	return avgWait;
}




intersection::intersection(){
	srand((unsigned)time(0));
	A.laneName = 'a';
	B.laneName = 'b';
	C.laneName = 'c';
	D.laneName = 'd';
}

Lane intersection :: initialize_traffic(Lane a){
	a.insertMultiple(rand()%carGen);
	return a;
}

void intersection :: initialize_traffic_multiple(){
	A = initialize_traffic(A);
	B = initialize_traffic(B);
	C = initialize_traffic(C);
	D = initialize_traffic(D);
}

Lane intersection :: initialize_traffic_small(Lane a){
	a.insertMultiple(rand()%2);
	return a;
}

void intersection :: initialize_traffic_small_multiple(Lane l){
	if(l.laneName != A.laneName)
		A = initialize_traffic_small(A);
	if(l.laneName != B.laneName)
		B = initialize_traffic_small(B);
	if(l.laneName != C.laneName)
		C = initialize_traffic_small(C);
	if(l.laneName != D.laneName)
		D = initialize_traffic_small(D);
}

Lane intersection :: lane_go(Lane l, int goTime){
	int i;
	cout<<"Lane "<<l.laneName<<" = "<<l.getOccupied()<<" is moving..."<<endl;
	for(i = 1; i <= goTime; i++){
		sleep(1);
		l.deleteMultiple(carsPerSec);
		l = initialize_traffic_small(l);
		initialize_traffic_small_multiple(l);
		inc_wait(l);
	}
	avg_wait(l);
	cout<<endl;

	return l;
}

void intersection :: print(){
	cout<<"A: "<<A.getOccupied()<<endl;
	cout<<"B: "<<B.getOccupied()<<endl;
	cout<<"C: "<<C.getOccupied()<<endl;
	cout<<"D: "<<D.getOccupied()<<endl;
	cout<<endl;
}

void intersection :: store_lanes(Lane a, Lane b, Lane c, Lane d){
	a = A;
	b = B;
	c = C;
	d = D;
}

void intersection :: inc_wait(Lane l){
	if(l.laneName != A.laneName)
		A.inc_wait();
	if(l.laneName != B.laneName)
		B.inc_wait();
	if(l.laneName != C.laneName)
		C.inc_wait();
	if(l.laneName != D.laneName)
		D.inc_wait();
}

void intersection :: avg_wait(Lane l){
	if(l.laneName != A.laneName)
		A.find_avgWait();
	if(l.laneName != B.laneName)
		B.find_avgWait();
	if(l.laneName != C.laneName)
		C.find_avgWait();
	if(l.laneName != D.laneName)
		D.find_avgWait();
}

void intersection :: print_avg_wait(){
	cout<<"Avg wait for A: "<<A.get_avgWait()<<endl;
	cout<<"Avg wait for B: "<<B.get_avgWait()<<endl;
	cout<<"Avg wait for C: "<<C.get_avgWait()<<endl;
	cout<<"Avg wait for D: "<<D.get_avgWait()<<endl;

	float total;
	total = (A.get_avgWait() + B.get_avgWait() + C.get_avgWait() + D.get_avgWait())/4;
	fancyText("Total Avg: ", false);
	cout<<total<<endl;
}

void intersection :: default_algo(){
	initialize_traffic_multiple();
	print();
	int i;
	//for(i = 0; i < cycles; i++){			//define the number of cycles the algorithm should run for
		A = lane_go(A, defaultWait);
		print();
		B = lane_go(B, defaultWait);
		print();
		C = lane_go(C, defaultWait);
		print();
		D = lane_go(D, defaultWait);
		print();
		print_avg_wait();
	//}
}


void sleep(int time_sec){
	usleep(time_sec * 1000000);
}
