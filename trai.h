//Header file for the traffic AI project

#ifndef _TRAI_H
#define _TRAI_H

#include<iostream>
#include<cstdlib>
#include<ctime>

#define maxCars   	   	100
#define carGen 			30
#define smallTraffic    8	//seconds
#define mediumTraffic   15	//seconds
#define largeTraffic    23	//seconds
#define defaultWait		2	//seconds
#define carsPerSec 		3
#define cycles     		5

typedef struct car{
	int waitTime;
	car() : waitTime(0) {}
}Car;

typedef struct lane{
	private:
		Car cars[maxCars];
		int isfull();
		int isEmpty();
		int end; //end of the queue
		int start; //start of the queue
		int occupied;//number of cars stored in the queue
		void ins();
		void del();
		float avgWait;
		int sum;

	public:
		lane();
		char laneName;
		void inc_wait();
		int getWait(int); //returns the value waitTime of a particular car.
		int getOccupied();
		void insertMultiple(int);
		void deleteMultiple(int);
		void find_avgWait();
		float get_avgWait();
}Lane;

class intersection{
private:
	Lane A, B, C, D;
	Lane initialize_traffic(Lane);
	void initialize_traffic_multiple();
	Lane initialize_traffic_small(Lane);
	void initialize_traffic_small_multiple(Lane);
	Lane lane_go(Lane, int);
	Lane compareLanes();
	friend void sleep();
	Lane array_of_lanes[4];
	void store_lanes(Lane, Lane, Lane, Lane);
	void inc_wait(Lane);
	void avg_wait(Lane);

public:
	intersection();
	void print();
	void algo();
	void default_algo();
	void print_avg_wait();
};

char* convertToCharArray(std::string);
void fancyText(std::string, bool);

#endif